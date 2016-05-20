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
 *  \file   wd_timer.c
 *
 *  \brief  WATCHDOG TIMER APIs.
 *
 *   This file contains the device abstraction layer APIs for Watchdog Timer.
 */

/****************************************************************
 *  INCLUDE FILES
 ****************************************************************/
#include "stdint.h"
#include "hw_types.h"
#include "wd_timer.h"

/*******************************************************************************
 *                       INTERNAL MACRO DEFINITIONS
 *******************************************************************************/
#define WD_TIMER_DISABLE_SEQ1           ((uint32_t) 0x0000AAAAU)
#define WD_TIMER_DISABLE_SEQ2           ((uint32_t) 0x00005555U)
#define WD_TIMER_ENABLE_SEQ1            ((uint32_t) 0x0000BBBBU)
#define WD_TIMER_ENABLE_SEQ2            ((uint32_t) 0x00004444U)

/*******************************************************************************
 *                        API FUNCTION DEFINITIONS
 *******************************************************************************/

/**
 * \fn   Starts/Enables the watchdog timer.
 *
 * \see  wd_timer.h
 *
 **/
void WDTIMEREnable(uint32_t baseAdd)
{
    /* Write the first value of the watchdog timer enabling sequence */
    HW_WR_REG32(baseAdd + WD_TIMER_WSPR, WD_TIMER_ENABLE_SEQ1);

    /* Wait until write is successful to WD_TIMER_WSPR register */
    while (WDTIMERWritePostedStatusGet(baseAdd, WD_TIMER_WRITE_PENDING_WSPR)
           != 0x0U)
    {
        /* Do nothing - Busy wait */
    }

    /* Write the second value of the watchdog timer enabling sequence */
    HW_WR_REG32(baseAdd + WD_TIMER_WSPR, WD_TIMER_ENABLE_SEQ2);

    /* Wait until write is successful to WD_TIMER_WSPR register */
    while (WDTIMERWritePostedStatusGet(baseAdd, WD_TIMER_WRITE_PENDING_WSPR)
           != 0x0U)
    {
        /* Do nothing - Busy wait */
    }
}

/**
 * \fn   Stops/Disables the watchdog timer.
 *
 * \see  wd_timer.h
 *
 **/
void WDTIMERDisable(uint32_t baseAdd)
{
    /* Write the first value of the watchdog timer disabling sequence */
    HW_WR_REG32(baseAdd + WD_TIMER_WSPR, WD_TIMER_DISABLE_SEQ1);

    /* Wait until write is successful to WD_TIMER_WSPR register */
    while (WDTIMERWritePostedStatusGet(baseAdd, WD_TIMER_WRITE_PENDING_WSPR)
           != 0x0U)
    {
        /* Do nothing - Busy wait */
    }

    /* Write the second value of the watchdog timer disabling sequence */
    HW_WR_REG32(baseAdd + WD_TIMER_WSPR, WD_TIMER_DISABLE_SEQ2);

    /* Wait until write is successful to WD_TIMER_WSPR register */
    while (WDTIMERWritePostedStatusGet(baseAdd, WD_TIMER_WRITE_PENDING_WSPR)
           != 0x0U)
    {
        /* Do nothing - Busy wait */
    }
}

/**
 * \fn   Return the revision id of the SOC used.
 *
 * \see  wd_timer.h
 *
 **/
uint32_t WDTIMERRevisionIDGet(uint32_t baseAdd)
{
    /* Return the revision id to the called function */
    return (HW_RD_REG32(baseAdd + WD_TIMER_WIDR));
}

/**
 * \fn   Reset the watchdog timer module.
 *
 * \see  wd_timer.h
 *
 **/
void WDTIMERReset(uint32_t baseAdd)
{
    /* Reset the Watchdog timer module */
    HW_WR_FIELD32(
        baseAdd + WD_TIMER_WDSC,
        WD_TIMER_WDSC_SOFTRESET,
        WD_TIMER_WDSC_SOFTRESET_RESETCMD);

    /* Wait until the reset is done */
    while (0x0U ==
           (HW_RD_FIELD32(baseAdd + WD_TIMER_WDST, WD_TIMER_WDST_RESETDONE)))
    {
        /* Do nothing - Busy wait */
    }
}

/**
 * \fn   This API will configure and enable the pre-scaler clock.
 *
 * \see  wd_timer.h
 *
 **/
void WDTIMERPreScalerClkEnable(uint32_t baseAdd, uint32_t ptv)
{
    uint32_t regVal;

    /* Clear the ptv field of WD_TIMER_WCLR register */
    HW_WR_FIELD32(baseAdd + WD_TIMER_WCLR, WD_TIMER_WCLR_PTV, 0U);

    /* Wait until write is successful to WD_TIMER_WCLR register */
    while (WDTIMERWritePostedStatusGet(baseAdd, WD_TIMER_WRITE_PENDING_WCLR)
           != 0x0U)
    {
        /* Do nothing - Busy wait */
    }

    /*
    ** Set the ptv field of WD_TIMER_WCLR register with the ptv value and also
    ** enable the pre-scaler clock
    */
    regVal = HW_RD_REG32(baseAdd + WD_TIMER_WCLR);

    HW_SET_FIELD32(regVal, WD_TIMER_WCLR_PTV, ptv >> WD_TIMER_WCLR_PTV_SHIFT);
    HW_SET_FIELD32(regVal, WD_TIMER_WCLR_PRE, WD_TIMER_WCLR_PRE_ENABLED);

    HW_WR_REG32(baseAdd + WD_TIMER_WCLR, regVal);

    /* Wait until write is successful to WD_TIMER_WCLR register */
    while (WDTIMERWritePostedStatusGet(baseAdd, WD_TIMER_WRITE_PENDING_WCLR)
           != 0x0U)
    {
        /* Do nothing - Busy wait */
    }
}

/**
 * \fn   This API will disable the pre-scaler clock.
 *
 * \see  wd_timer.h
 *
 **/
void WDTIMERPreScalerClkDisable(uint32_t baseAdd)
{
    /* Disable Pre-scaler clock */
    HW_WR_FIELD32(
        baseAdd + WD_TIMER_WCLR,
        WD_TIMER_WCLR_PRE,
        WD_TIMER_WCLR_PRE_DISABLED);

    /* Wait until write is successful to WD_TIMER_WCLR register */
    while (WDTIMERWritePostedStatusGet(baseAdd, WD_TIMER_WRITE_PENDING_WCLR)
           != 0x0U)
    {
        /* Do nothing - Busy wait */
    }
}

/**
 * \fn   Set/Write the Counter register with the counter value.
 *
 * \see  wd_timer.h
 *
 **/
void WDTIMERCounterSet(uint32_t baseAdd, uint32_t countVal)
{
    /* Set the WD_TIMER_WCRR register with the countVal */
    HW_WR_REG32(baseAdd + WD_TIMER_WCRR, countVal);

    /* Wait until write is successful to WD_TIMER_WCRR register */
    while (WDTIMERWritePostedStatusGet(baseAdd, WD_TIMER_WRITE_PENDING_WCRR)
           != 0x0U)
    {
        /* Do nothing - Busy wait */
    }
}

/**
 * \fn   Get/Read the counter value from the counter register.
 *
 * \see  wd_timer.h
 *
 **/
uint32_t WDTIMERCounterGet(uint32_t baseAdd)
{
    /* Read the counter value from WD_TIMER_WCRR register */
    /* Delay cannot be added in DAL layer,Application should
     * add delay of 2 timer interface clock cycles + 1 timer functional clock
     * cycle before reading WCRR register */
    return (HW_RD_REG32(baseAdd + WD_TIMER_WCRR));
}

/**
 * \fn   Set the reload count value in the Watchdog timer load register.
 *
 * \see  wd_timer.h
 *
 **/
void WDTIMERReloadSet(uint32_t baseAdd, uint32_t reloadVal)
{
    /* Load the WD_TIMER_WLDR register with the re-load value */
    HW_WR_REG32(baseAdd + WD_TIMER_WLDR, reloadVal);

    /* Wait until write is successful to the WD_TIMER_WLDR register */
    while (WDTIMERWritePostedStatusGet(baseAdd, WD_TIMER_WRITE_PENDING_WLDR)
           != 0x0U)
    {
        /* Do nothing - Busy wait */
    }
}

/**
 * \fn   Get the reload count value from the Watchdog timer load register.
 *
 * \see  wd_timer.h
 *
 **/
uint32_t WDTIMERReloadGet(uint32_t baseAdd)
{
    /* Return the contents of WD_TIMER_WLDR */
    return (HW_RD_REG32(baseAdd + WD_TIMER_WLDR));
}

/**
 * \fn   Set/enable the trigger write access.
 *
 * \see  wd_timer.h
 *
 **/
void WDTIMERTriggerSet(uint32_t baseAdd, uint32_t trigVal)
{
    /* Set the WD_TIMER_WTGR register with the trigVal*/
    HW_WR_REG32(baseAdd + WD_TIMER_WTGR, trigVal);

    /* Wait till write is successful to WD_TIMER_WTGR register */
    while (WDTIMERWritePostedStatusGet(baseAdd, WD_TIMER_WRITE_PENDING_WTGR)
           != 0x0U)
    {
        /* Do nothing - Busy wait */
    }
}

/**
 * \fn   Load the delay register of Watchdog timer with the delay value.
 *
 * \see  wd_timer.h
 *
 **/
void WDTIMERDelaySet(uint32_t baseAdd, uint32_t delayVal)
{
    /* Set the WD_TIMER_WDLY register with the delayVal */
    HW_WR_REG32(baseAdd + WD_TIMER_WDLY, delayVal);

    /* Wait until write is successful to the WD_TIMER_WDLY register */
    while (WDTIMERWritePostedStatusGet(baseAdd, WD_TIMER_WRITE_PENDING_WDLY)
           != 0x0U)
    {
        /* Do nothing - Busy wait */
    }
}

/**
 * \fn   Return the delay register value of Watchdog timer.
 *
 * \see  wd_timer.h
 *
 **/
uint32_t WDTIMERDelayGet(uint32_t baseAdd)
{
    /* Return the WD_TIMER_WDLY register value */
    return (HW_RD_REG32(baseAdd + WD_TIMER_WDLY));
}

/**
 * \fn   Set IRQ status by software.
 *
 * \see  wd_timer.h
 *
 **/
void WDTIMERIntRawStatusSet(uint32_t baseAdd, uint32_t intFlags)
{
    /* Set the status in the WD_TIMER_WIRQSTATRAW register */
    HW_WR_REG32(
        baseAdd + WD_TIMER_WIRQSTATRAW,
        intFlags & (WD_TIMER_INT_OVERFLOW | WD_TIMER_INT_DELAY));
}

/**
 * \fn   Return the Raw IRQ status.
 *
 * \see  wd_timer.h
 *
 **/
uint32_t WDTIMERIntRawStatusGet(uint32_t baseAdd)
{
    /* Return the status of the WD_TIMER_WIRQSTATRAW register */
    return (HW_RD_REG32(baseAdd + WD_TIMER_WIRQSTATRAW));
}

/**
 * \fn   Read the status of WD_TIMER_WIRQSTAT register.
 *
 * \see  wd_timer.h
 *
 **/
uint32_t WDTIMERIntStatusGet(uint32_t baseAdd)
{
    /* Return the status of WD_TIMER_WIRQSTAT register */
    return (HW_RD_REG32(baseAdd + WD_TIMER_WIRQSTAT));
}

/**
 * \fn   Clear IRQ status.
 *
 * \see  wd_timer.h
 *
 **/
void WDTIMERIntStatusClear(uint32_t baseAdd, uint32_t intFlags)
{
    /* Clear the status in the WD_TIMER_WIRQSTAT register */
    HW_WR_REG32(
        baseAdd + WD_TIMER_WIRQSTAT,
        intFlags & (WD_TIMER_INT_OVERFLOW | WD_TIMER_INT_DELAY));
}

/**
 * \fn   Enable Watchdog timer interrupts.
 *
 * \see  wd_timer.h
 *
 **/
void WDTIMERIntEnable(uint32_t baseAdd, uint32_t intFlags)
{
    /* Enable the watchdog timer interrupts */
    HW_WR_REG32(
        baseAdd + WD_TIMER_WIRQENSET,
        intFlags & (WD_TIMER_INT_ENABLE_OVRFLW | WD_TIMER_INT_ENABLE_DELAY));
}

/**
 * \fn   Used to check whether interrupts of Watchdog timer are enabled
 *          or disabled.
 *
 * \see  wd_timer.h
 *
 **/
uint32_t WDTIMERIntEnableStatusGet(uint32_t baseAdd)
{
    /* Return the status of WD_TIMER_WIRQENSET register */
    return (HW_RD_REG32(baseAdd + WD_TIMER_WIRQENSET));
}

/**
 * \fn   Disable Watchdog timer interrupts.
 *
 * \see  wd_timer.h
 *
 **/
void WDTIMERIntDisable(uint32_t baseAdd, uint32_t intFlags)
{
    /* Disable the Watchdog timer interrupts */
    HW_WR_REG32(
        baseAdd + WD_TIMER_WIRQENCLR,
        intFlags & (WD_TIMER_INT_DISABLE_DELAY | WD_TIMER_INT_DISABLE_OVRFLW));
}

/**
 * \fn   Read the status of WD_TIMER_WWPS register.
 *
 * \see  wd_timer.h
 *
 **/
uint32_t WDTIMERWritePostedStatusGet(uint32_t baseAdd, uint32_t flags)
{
    /* Return the status of WD_TIMER_WWPS register addressed by flags */
    return (HW_RD_REG32(baseAdd + WD_TIMER_WWPS) & flags);
}

/************************* END OF WATCHDOG TIMER DAL **************************/
