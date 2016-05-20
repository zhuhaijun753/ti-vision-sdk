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
 * main_a8.c
 */

#include "uartStdio.h"
#include "stdint.h"
#include "stdio.h"
#include "interrupt.h"
#include "soc_defines.h"
#include "platform.h"
#include "soc.h"
#include "timer.h"
#include "common/stw_types.h"

/******************************************************************************
**                      INTERNAL MACRO DEFINITIONS
*******************************************************************************/
#define TIMER_INITIAL_COUNT             (0xFFF00000U)
#define TIMER_RLD_COUNT                 (0xFFF00000U)

/******************************************************************************
**                      INTERNAL FUNCTION PROTOTYPES
*******************************************************************************/
static void TimerAintcConfigure(void);
static void TimerSetUp(void);
static void TimerIsr(void *handle);

/******************************************************************************
**                      INTERNAL VARIABLE DEFINITIONS
*******************************************************************************/
static volatile uint32_t gCntValue     = 10;
static volatile uint32_t gIsrSemaphore = 0;

/******************************************************************************
**                          FUNCTION DEFINITIONS
*******************************************************************************/
int main(void)
{
    /* Initialize the UART Instance */
    UARTStdioInit();
    UARTPuts("\n Timer Application", -1);

    /* Register Timer4 interrupts on to AINTC */
    TimerAintcConfigure();

    /* Perform the necessary configurations for Timer4 */
    TimerSetUp();

    /* Enable the Timer4 interrupts */
    TIMERIntEnable(SOC_TIMER4_BASE, TIMER_INT_OVF_EN_FLAG);

    UARTPuts("\nTencounter: ", -1);

    /* Start the Timer */
    TIMEREnable(SOC_TIMER4_BASE);

    while (gCntValue)
    {
        if (gIsrSemaphore)
        {
            gIsrSemaphore--;
            UARTPuts("\n gCntValue:", -1);
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

    return 0;
}

/*
** Do the necessary Timer configurations on to AINTC.
*/
static void TimerAintcConfigure(void)
{
    /* Initialize the ARM interrupt control */
    Intc_Init();

    /* Enable the ARM interrupt */
    Intc_IntEnable(0);

    /* Registering TimerIsr */
    Intc_IntRegister(92, (IntrFuncPtr) TimerIsr, NULL);

    /* Set the priority */
    Intc_IntPrioritySet(92, 1, 0);

    /* Enable the system interrupt */
    Intc_SystemEnable(92);
}

/*
** Setup the timer for one-shot and compare mode.
*/
static void TimerSetUp(void)
{
    /*Reset the timer module */
    TIMERReset(SOC_TIMER4_BASE);

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

    gIsrSemaphore++;
    gCntValue--;

    if (gCntValue == 0)
    {
        UARTPuts("\n gCntValue:", -1);
        UARTPutNum((int) (gCntValue));
        gIsrSemaphore = 0;
    }

    /* Enable the Timer interrupts */
    TIMERIntEnable(SOC_TIMER4_BASE, TIMER_INT_OVF_EN_FLAG);
}

