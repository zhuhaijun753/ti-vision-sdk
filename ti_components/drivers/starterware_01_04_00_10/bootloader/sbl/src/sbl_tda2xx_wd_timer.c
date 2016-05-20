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
/**
 *   Component:     sbl
 *
 *   Filename:      sbl_tda2xx_wd_timer.h
 *
 *   Description:  This file contain WD_TIMER functions to refresh the
 *                     WD_TIMER on  DLY Event. ROM bootloader configures
 *                     the WD_TIMER to 3 mins, In sbl on begin WD_TIMER
 *                     refresed to 3 mins & DLY event set to 2 mins. On DLY
 *                     event, registered ISR refresh the WD_TIMER to 3 mins.
 *                     On completing the boot, sbl de-registered DLY ISR &
 *                     refresh the WD_TIMER to 3 mins. Application will be
 *                     responsible to refresh the WD_TIMER
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <soc.h>
#include <wd_timer.h>
#include <interrupt.h>
#include <sbl_tda2xx_wd_timer.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/*MPU System interrupt number*/
#define WD_TIMER_DELAY_INT    (uint16_t) (80)

/*WD_TIMER OVF Value for 3 mins at 36KHZ FCLK*/
#define SBL_WD_TIMER_OVF_VALUE  (0xFFA81BFFU)

/*WD_TIMER DLY event value for 2 mins*/
#define SBL_WD_TIMER_DLY_VALUE   (0xFFA81BFFU + 0x3A9800U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void SBLWdtimerBegin(void)
{
    uint32_t SBLWdtimerIsrTmp = (uint32_t) &SBLWdtimerIsr;
    /*stop the wdtimer*/
    WDTIMERDisable(SOC_WD_TIMER2_BASE);

    /*write the counter value for 3 mins */
    WDTIMERCounterSet(SOC_WD_TIMER2_BASE, SBL_WD_TIMER_OVF_VALUE);

    /*write the counter load value for 3 mins*/
    WDTIMERReloadSet(SOC_WD_TIMER2_BASE, SBL_WD_TIMER_OVF_VALUE);

    /*enable prescaler & set the prescaler value*/
    WDTIMERPreScalerClkEnable(SOC_WD_TIMER2_BASE, WD_TIMER_PRESCALER_CLK_DIV_1);

    /*set the DLY interrupt count value to 2 Min*/
    WDTIMERDelaySet(SOC_WD_TIMER2_BASE, SBL_WD_TIMER_DLY_VALUE);

    /*enable DLY interrupt*/
    WDTIMERIntEnable(SOC_WD_TIMER2_BASE, WD_TIMER_INT_ENABLE_DELAY);

    /* Registering wdtimer DLY event interrupt.  */
    Intc_IntRegister(WD_TIMER_DELAY_INT, (IntrFuncPtr) SBLWdtimerIsrTmp, 0);

    /* Setting the priority for wdtimer DLY event in AINTC. */
    Intc_IntPrioritySet(WD_TIMER_DELAY_INT, (uint16_t) 1, (uint8_t) 0);

    /* Enabling the wdtimer DLY interrupt in AINTC. */
    Intc_SystemEnable(WD_TIMER_DELAY_INT);

    /*start the timer*/
    WDTIMEREnable(SOC_WD_TIMER2_BASE);
}

void SBLWdtimerIsr(void *ptr)
{
    /*stop the wdtimer*/
    WDTIMERDisable(SOC_WD_TIMER2_BASE);

    /*clear DLY interrupt status bit*/
    WDTIMERIntStatusClear(SOC_WD_TIMER2_BASE, WD_TIMER_INT_ENABLE_DELAY);

    /*enable DLY interrupt*/
    WDTIMERIntEnable(SOC_WD_TIMER2_BASE, WD_TIMER_INT_ENABLE_DELAY);

    /*trigger reload*/
    WDTIMERTriggerSet(SOC_WD_TIMER2_BASE, (uint32_t) 0x1010);
    WDTIMERTriggerSet(SOC_WD_TIMER2_BASE, (uint32_t) 0x0101);

    /*start the wdtimer*/
    WDTIMEREnable(SOC_WD_TIMER2_BASE);
}

void SBLWdtimerEnd(void)
{
    /*stop the wdtimer*/
    WDTIMERDisable(SOC_WD_TIMER2_BASE);

    /*trigger reload*/
    WDTIMERTriggerSet(SOC_WD_TIMER2_BASE, (uint32_t) 0x1010);
    WDTIMERTriggerSet(SOC_WD_TIMER2_BASE, (uint32_t) 0x0101);

    /*disable DLY interrupt*/
    WDTIMERIntDisable(SOC_WD_TIMER2_BASE, WD_TIMER_INT_ENABLE_DELAY);

    /* Disabling the wdtimer DLY interrupt in AINTC. */
    Intc_SystemDisable(WD_TIMER_DELAY_INT);

    /*Unregister the wdtimer DLY interrupt from system vector table*/
    Intc_IntUnregister(WD_TIMER_DELAY_INT);

    /*start the wdtimer*/
    WDTIMEREnable(SOC_WD_TIMER2_BASE);
}

