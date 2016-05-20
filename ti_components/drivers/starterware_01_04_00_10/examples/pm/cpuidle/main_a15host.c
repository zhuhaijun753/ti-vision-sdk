/**
 *  \file main_a15host.c
 *
 *  \brief A15 CPU Idle Example Application
 *
 *  \copyright Copyright (C) 2014 Texas Instruments Incorporated -
 *             http://www.ti.com/
 */

/* ======================================================================
 *   Copyright (C) 2014 Texas Instruments Incorporated
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

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "stdio.h"
#include "string.h"
#include "stdint.h"
#include "soc_defines.h"
#include "platform.h"
#include "soc.h"
#include "uartStdio.h"
#include "hw_types.h"
#include "interrupt.h"
#include "irq_xbar.h"
#include "timer.h"
#include "hw_ctrl_core.h"
#include "hw_l4per_cm_core.h"
#include <wd_timer.h>
#include "pmlib_cpuidle.h"
#include "pmhal_pdm.h"
#include "pmhal_cm.h"
#include "pmhal_mm.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define TIMER_INITIAL_COUNT             (0xFFF00000U)
#define TIMER_RLD_COUNT                 (0xFFF00000U)
#define MPU_IRQ_40                      (40)

// TODO: Use PRCM HAL APIs in the test
#define PM_MPU_PWRSTCTRL 0x4AE06300
#define CM_MPU_CLKSTCTRL 0x4A005300

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

static void TimerPRCMConfigure(void);
static void TimerIntcInit(void);
static void TimerIntcDeInit(void);
static void TimerSetUp(void);
static void TimerIsr(void *handle);
static void TimerRun(void);
static void TimerStop(void);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static volatile uint32_t gCntValue = 10;
static volatile uint32_t gXbarInst = 35;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

static void CpuIdleTest(void)
{
    pmErrCode_t status;
    uint32_t    i;

    /*Set PRCM for Timer4 */
    /*This is done in SBL, adding here to make the app standalone */
    TimerPRCMConfigure();
    TimerRun();

    /* Set MPU_PD to Retention */
    PMHALPdmSetPDState(PMHAL_PRCM_PD_MPU, PMHAL_PRCM_PD_STATE_RETENTION,
                       PM_TIMEOUT_NOWAIT);
    PMHALCMSetCdClockMode((pmhalPrcmCdId_t) PMHAL_PRCM_CD_MPU,
                          PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO,
                          PM_TIMEOUT_NOWAIT);

    PMLIBCpu1ForcedOff();

    for (i = 0; i < 10; i++)
    {
        UARTPuts("\nEnter Idle", -1);

        status = PMLIBCpuIdle(PMHAL_PRCM_PD_STATE_RETENTION);
        {
            /* For Profiling */
            int32_t timeCnt = 0;
            int32_t cycles  = 0;
            timeCnt = (int32_t) TIMERCounterGet(SOC_TIMER4_BASE);
            UARTPuts("\nTime Taken to Wakeup:", -1);
            cycles = timeCnt - (int32_t) TIMER_RLD_COUNT;
            UARTPutNum((int32_t) cycles);
        }

        if (status == PM_SUCCESS)
        {
            UARTPuts("\nEnter Targeted Power State successfully", -1);
        }
        else
        {
            UARTPuts("\nEnter Targeted Power State failed", -1);
            break;
        }
        UARTPuts("\nExit Idle", -1);
    }
    TimerStop();
    UARTPuts("\nTest Completed!!", -1);
}

int main(void)
{
    UART_PAD_CONFIG();
    UARTStdioInit();
    UARTPuts("\nPM CPUIdle Test App", -1);

    /*stop the wdtimer*/
    WDTIMERDisable(SOC_WD_TIMER2_BASE);

    /* Function to Test CPU Idle */
    CpuIdleTest();

    return 0;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

static void TimerRun(void)
{
    /* Register Timer4 interrupts on to INTC */
    TimerIntcInit();

    /* Perform the necessary configurations for Timer4 */
    TimerSetUp();

    /* Enable the Timer4 interrupts */
    TIMERIntEnable(SOC_TIMER4_BASE, TIMER_INT_OVF_EN_FLAG);

    /* Enable the Timer4 wakeup event */
    TIMERWakeEnable(SOC_TIMER4_BASE, TIMER_WAKE_OVF_FLAG);

    /* Set the Timer4 to Smart-idle mode */
    TIMERIdleModeConfigure(SOC_TIMER4_BASE, TIMER_SMART_IDLE);

    /* Start the Timer */
    TIMEREnable(SOC_TIMER4_BASE);
}

static void TimerStop(void)
{
    /* Stop the Timer */
    TIMERDisable(SOC_TIMER4_BASE);

    /* Disable the Timer4 wakeup event */
    TIMERWakeDisable(SOC_TIMER4_BASE, TIMER_WAKE_OVF_FLAG);

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
    Intc_IntRegister(MPU_IRQ_40, TimerIsr, NULL);

    /* Set the priority */
    Intc_IntPrioritySet(MPU_IRQ_40, 1, 0);

    /* Enable the system interrupt */
    Intc_SystemEnable(MPU_IRQ_40);
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
    Intc_SystemDisable(MPU_IRQ_40);

    /* Unregister the interrupt */
    Intc_IntUnregister(MPU_IRQ_40);
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

