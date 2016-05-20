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
 * main.c
 */

#include "stdint.h"
#include "wd_timer.h"
#include "hw_types.h"
#include "soc.h"
#include "soc_defines.h"
#include "platform.h"
#include "uartStdio.h"

/******************************************************************************
**                      INTERNAL MACRO DEFINITIONS
*******************************************************************************/
#define INITIAL_COUNT_VALUE          (0xFFFE0000U)
#define RELOAD_COUNT_VALUE           (0xFFFE0000U)

#ifndef TI814X_BUILD
#define SOC_WD_TIMER_BASE SOC_WD_TIMER2_BASE
#else
#define SOC_WD_TIMER_BASE SOC_WATCHDOGTIMER_BASE
#endif

/******************************************************************************
**                      INTERNAL FUNCTION PROTOTYPES
*******************************************************************************/
static void WDTimerSetUp(void);

/******************************************************************************
**                          FUNCTION DEFINITIONS
*******************************************************************************/
int main(void)
{
    uint32_t triggerValue = 0;

#ifndef TI814X_BUILD
    /* Do Pad Config for UART */
    PlatformUART1SetPinMux();
#endif

    /* Initialize the UART Instance */
    UARTStdioInit();
#ifndef TI814X_BUILD
    UARTPuts("\nWD Timer Application Running on A15", -1);
#else
    UARTPuts("\nWD Timer Application Running on A8", -1);
#endif

    /* Reset the Watchdog Timer */
    WDTIMERReset(SOC_WD_TIMER_BASE);

    /* Disable the Watchdog timer */
    WDTIMERDisable(SOC_WD_TIMER_BASE);

    /* Perform the initial settings for the Watchdog Timer */
    WDTimerSetUp();

    /* Send the message to UART console */
    UARTPuts("\nProgram Reset!", -1);
    UARTPuts(
        "\nInput any key at least once in every 4 seconds to avoid a further reset.\n\r",
        -1);

    /* Enable the Watchdog Timer */
    WDTIMEREnable(SOC_WD_TIMER_BASE);

    while (1)
    {
        /* Wait for an input through UART. If no input is given,
        ** the WD Timer will timeout and reset will occur.
        */
        if (UARTGetc())
        {
            triggerValue += 1;

            /* Write into the trigger register. This will load the value from
             * the
             ** load register into the counter register and hence timer will
             ** start
             ** from the initial count.
             */
            WDTIMERTriggerSet(SOC_WD_TIMER_BASE, triggerValue);
        }
    }
}

/*
** This function will perform the necessary initialization for
** the Watchdog Timer.
*/
static void WDTimerSetUp(void)
{
    /* Configure and enable the pre-scaler clock */
    WDTIMERPreScalerClkEnable(SOC_WD_TIMER_BASE, WD_TIMER_PRESCALER_CLK_DIV_1);

    /* Set the count value into the counter register */
    WDTIMERCounterSet(SOC_WD_TIMER_BASE, INITIAL_COUNT_VALUE);

    /* Set the reload value into the load register */
    WDTIMERReloadSet(SOC_WD_TIMER_BASE, RELOAD_COUNT_VALUE);
}

