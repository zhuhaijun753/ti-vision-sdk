/* ======================================================================
 *   Copyright (C) 2013 Texas Instruments Incorporated
 *
 *   All rights reserved. Property of Texas Instruments Incorporated.
 *   Restricted rights to use, duplicate or disclose this code are
 *   granted through contract.
 *
 *   The program may not be used without the written permission
 *   of Texas Instruments Incorporated or against the terms and conditions
 *   stipulated in the agreement under which this program has been
 *   supplied.
 * ==================================================================== */
/*
 * main_a15.c
 */

#include "uartStdio.h"
#include "stdint.h"
#include "stdio.h"
#include "interrupt.h"
#include "soc_defines.h"
#include "platform.h"
#include "irq_xbar.h"
#include "soc.h"
#include "timer.h"
#include "sample.h"
#include "common/stw_types.h"
#include "hw_ctrl_core.h"
#include "hw_l4per_cm_core.h"

/******************************************************************************
**                      INTERNAL MACRO DEFINITIONS
*******************************************************************************/
#define TIMER_INITIAL_COUNT             (0xFFF00000U)
#define TIMER_RLD_COUNT                 (0xFFF00000U)

/******************************************************************************
**                      INTERNAL FUNCTION PROTOTYPES
*******************************************************************************/
static void TimerPRCMConfigure(void);
static void TimerIntcInit(void);
static void TimerIntcDeInit(void);
static void TimerSetUp(void);
static void TimerIsr(void *handle);
static void TimerRun(void);
static void DisableNMI(void);

/******************************************************************************
**                      INTERNAL VARIABLE DEFINITIONS
*******************************************************************************/
static volatile uint32_t gCntValue     = 10;
static volatile uint32_t gIsrSemaphore = 0;
static volatile uint32_t gXbarInst     = 1;
static volatile uint32_t gNumSuccess   = 0;

/****************************************************************************/
/*                      NOTE TO THE USER                                    */
/****************************************************************************/
/*
** Crossbar Instance 5 does not allow crossbar input,
** instance 132 and 133 are not connected to INTC;
** therefore these three instances cannot be used.
*/

/******************************************************************************
**                          FUNCTION DEFINITIONS
*******************************************************************************/

int main(void)
{
    /* Do Pad Config for UART */
    PlatformUART1SetPinMux();

    /*Set PRCM for Timer4 */
    /*This is done in SBL, adding here to make the app standalone */
    TimerPRCMConfigure();

    /* Initialize the UART Instance */
    UARTStdioInit();
    UARTPuts("\nTimer Application Running on A15", -1);

    /* Run the Timer MPU_IRQ_XBAR_COUNT times,
     * increment gXbarInst in each iteration */
    for (gXbarInst = 1; gXbarInst <= MPU_IRQ_XBAR_COUNT; gXbarInst++)
    {
        TimerRun();
    }

    if (gNumSuccess == (MPU_IRQ_XBAR_COUNT - 3))
    {
        UARTPuts("\nAll Xbar instances for A15 are verified successfully", -1);
    }
    return 0;
}

static void TimerRun(void)
{
    /* Disable the NMI */
    DisableNMI();

    /* Check if IRQ pin is available */
    while (intrA15[gXbarInst - 1] == -1)
    {
        gXbarInst++;
    }

    /* Register Timer4 interrupts on to INTC */
    TimerIntcInit();

    /* Perform the necessary configurations for Timer4 */
    TimerSetUp();

    /* Enable the Timer4 interrupts */
    TIMERIntEnable(SOC_TIMER4_BASE, TIMER_INT_OVF_EN_FLAG);

    /* Start the Timer */
    TIMEREnable(SOC_TIMER4_BASE);

    UARTPuts("\ncntValue:", -1);

    while (gCntValue)
    {
        if (gIsrSemaphore)
        {
            gIsrSemaphore--;
            UARTPuts(" ", -1);
            UARTPutNum((int) (gCntValue));
        }
    }

    /* Stop the Timer */
    TIMERDisable(SOC_TIMER4_BASE);

    if (gCntValue == 0)
    {
        UARTPuts("\n|RESULT|SUCCESS|", -1);
    }
    else
    {
        UARTPuts("\n|RESULT|FAIL|", -1);
    }

    /* Unregister Timer4 interrupts */
    TimerIntcDeInit();
}

/*
** Do the necessary Timer configurations on to INTC.
*/
static void TimerIntcInit(void)
{
    irq_xbar_ret_type_t status = invalid_mpu_id;
    uint8_t connectionStatus   = 0;

    /*Unlock the Crossbar register */
    PlatformUnlockMMR();

    /* Connect the Xbar with interrupt source */
    status = IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_MPUSS,
                            gXbarInst, TIMER4_IRQ);

    if (status == irq_xbar_success)
    {
        /* Check if xbar is indeed connected correctly */
        IRQXBARIsConnected(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_MPUSS,
                           gXbarInst, TIMER4_IRQ, &connectionStatus);
        if (connectionStatus == 1)
        {
            UARTPuts("\nXBar is sucessfully connected to inst:", -1);
            UARTPutNum(gXbarInst);
        }
        else
        {
            UARTPuts("\nWrong XBar Connection", -1);
        }
    }
    else
    {
        UARTPuts("\nXBar not able to connect", -1);
    }

    /* Initialize the interrupt control */
    Intc_Init();

    /* Enable the interrupt */
    Intc_IntEnable(0);

    /* Registering TimerIsr */
    Intc_IntRegister(intrA15[gXbarInst - 1], TimerIsr, NULL);

    /* Set the priority */
    Intc_IntPrioritySet(intrA15[gXbarInst - 1], 1, 0);

    /* Enable the system interrupt */
    Intc_SystemEnable(intrA15[gXbarInst - 1]);
}

/*
** Disable the interrupt configurations on INTC.
*/
static void TimerIntcDeInit(void)
{
    /* Restore the initial state of gCntValue */
    gCntValue = 10;

    /* Disconnect the XBar */
    IRQXBARDisconnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE, CPU_MPUSS,
                      gXbarInst);

    /* Disable the timer interrupt */
    Intc_SystemDisable(intrA15[gXbarInst - 1]);

    /* Unregister the interrupt */
    Intc_IntUnregister(intrA15[gXbarInst - 1]);
}

/*
** Setup the timer for one-shot and compare mode.
*/
static void TimerSetUp(void)
{
    /*Reset the timer module */
    TIMERReset(SOC_TIMER4_BASE);

    /* Enable free run in emulation mode */
    TIMEREmuModeConfigure(SOC_TIMER4_BASE, TIMER_FREE);

    /* Load the counter with the initial count value */
    TIMERCounterSet(SOC_TIMER4_BASE, TIMER_INITIAL_COUNT);

    /* Load the load register with the reload count value */
    TIMERReloadSet(SOC_TIMER4_BASE, TIMER_RLD_COUNT);

    /* Configure the Timer for Auto-reload and compare mode */
    TIMERModeConfigure(SOC_TIMER4_BASE, TIMER_AUTORLD_NOCMP_ENABLE);

    /* Configure the posted mode of TIMER */
    TIMERPostedModeConfig(SOC_TIMER4_BASE, TIMER_NONPOSTED);

    /* Configure the read mode of TIMER */
    TIMERReadModeConfig(SOC_TIMER4_BASE, TIMER_READ_MODE_NONPOSTED);
}

/*
** Timer interrupt service routine. This will send a character to serial
** console.
*/
static void TimerIsr(void *handle)
{
    /* Disable the Timer interrupts */
    TIMERIntDisable(SOC_TIMER4_BASE, TIMER_INT_OVF_EN_FLAG);

    /* Clear the status of the interrupt flags */
    TIMERIntStatusClear(SOC_TIMER4_BASE, TIMER_INT_OVF_IT_FLAG);

    gIsrSemaphore++;
    gCntValue--;

    if (gCntValue == 0)
    {
        UARTPuts(" ", -1);
        UARTPutNum((int) (gCntValue));
        gIsrSemaphore = 0;
        gNumSuccess++;
    }

    /* Enable the Timer interrupts */
    TIMERIntEnable(SOC_TIMER4_BASE, TIMER_INT_OVF_EN_FLAG);
}

/*
** Timer4 PRCM configuration. This will explicitly enable the Timer4 module.
*/
static void TimerPRCMConfigure(void)
{
    HW_WR_REG32(SOC_L4PER_CM_CORE_BASE + CM_L4PER_TIMER4_CLKCTRL, 0x2);

    while ((HW_RD_REG32(SOC_L4PER_CM_CORE_BASE +
                        CM_L4PER_TIMER4_CLKCTRL) & (0x00030000)) != 0x0) ;
}

/*
** Disable the non maskable interrupt.
** This will allow configuration of MPU_IRQ_133.
*/
static void DisableNMI(void)
{
    uint32_t tmpRegVal;
    tmpRegVal = HW_RD_REG32(SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                            CTRL_CORE_NMI_DESTINATION_2);
    tmpRegVal &= 0xFFFFFF00;
    HW_WR_REG32(SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                CTRL_CORE_NMI_DESTINATION_2, tmpRegVal);
}

