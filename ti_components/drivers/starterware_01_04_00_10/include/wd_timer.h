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
 *  \file   wd_timer.h
 *
 *  \brief  Watchdog timer APIs and macros.
 *
 *   This file contains the driver API prototypes and macro definitions.
 */

#ifndef WD_TIMER_H_
#define WD_TIMER_H_

#include "hw_types.h"
#include "hw_wd_timer.h"
#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************/
/*
** Values that can be passed to WDTIMERPreScalerClkEnable API as ptv.
*/
/* Divide functional clock by 1 */
#define WD_TIMER_PRESCALER_CLK_DIV_1        (uint32_t) (0x00000000U)

/* Divide functional clock by 2 */
#define WD_TIMER_PRESCALER_CLK_DIV_2        (uint32_t) (0x00000004U)

/* Divide functional clock by 4 */
#define WD_TIMER_PRESCALER_CLK_DIV_4        (uint32_t) (0x00000008U)

/* Divide functional clock by 8 */
#define WD_TIMER_PRESCALER_CLK_DIV_8        (uint32_t) (0x0000000CU)

/* Divide functional clock by 16 */
#define WD_TIMER_PRESCALER_CLK_DIV_16       (uint32_t) (0x00000010U)

/* Divide functional clock by 32 */
#define WD_TIMER_PRESCALER_CLK_DIV_32       (uint32_t) (0x00000014U)

/* Divide functional clock by 64 */
#define WD_TIMER_PRESCALER_CLK_DIV_64       (uint32_t) (0x00000018U)

/* Divide functional clock by 128 */
#define WD_TIMER_PRESCALER_CLK_DIV_128      (uint32_t) (0x0000001CU)

/*****************************************************************************/
/*
** Values that can be passed to WDTIMERIntRawStatusSet,
** WDTIMERIntStatusClear APIs as intFlags.
** These values can also be used to read the status obatined from
** WDTIMERIntRawStatusGet, WDTIMERIntStatusGet APIs.
** These values are combined together as:
** WD_TIMER_INT_ALL: (WD_TIMER_INT_DELAY | WD_TIMER_INT_OVERFLOW)
*/
/* Watchdog delay interrupt */
#define WD_TIMER_INT_DELAY              (WD_TIMER_WIRQSTATRAW_EVENT_DLY_MASK)

/* Watchdog overflow interrupt */
#define WD_TIMER_INT_OVERFLOW           (WD_TIMER_WIRQSTATRAW_EVENT_OVF_MASK)

/* Watchdog all interrupts */
#define WD_TIMER_INT_ALL                (WD_TIMER_INT_DELAY | \
                                         WD_TIMER_INT_OVERFLOW)

/*****************************************************************************/
/*
** Values that can be passed to WDTIMERIntEnable as intFlags.
** These values can also be used to read the status obtained from
** WDTIMERIntEnableStatusGet API.
** These values are combined together as:
** For e.g. (WD_TIMER_INT_ENABLE_DELAY | WD_TIMER_INT_ENABLE_OVRFLW)
*/
/* Enable delay interrupt */
#define WD_TIMER_INT_ENABLE_DELAY           (WD_TIMER_WIRQENSET_ENABLE_DLY_MASK)

/* Enable overflow interrupt */
#define WD_TIMER_INT_ENABLE_OVRFLW          (WD_TIMER_WIRQENSET_ENABLE_OVF_MASK)

/* Enable all interrupts */
#define WD_TIMER_INT_ENABLE_ALL             (WD_TIMER_INT_ENABLE_DELAY | \
                                             WD_TIMER_INT_ENABLE_OVRFLW)

/*****************************************************************************/
/*
** Values that can be passed to WDTIMERIntDisable as intFlags.
** These values are combined together as:
** For e.g. (WD_TIMER_INT_DISABLE_DELAY | WD_TIMER_INT_DISABLE_OVRFLW)
*/
/* Disable delay interrupt */
#define WD_TIMER_INT_DISABLE_DELAY      (WD_TIMER_WIRQENCLR_ENABLE_DLY_MASK)

/* Disable overflow interrupt */
#define WD_TIMER_INT_DISABLE_OVRFLW     (WD_TIMER_WIRQENCLR_ENABLE_OVF_MASK)

/* Disable all interrupts */
#define WD_TIMER_INT_DISABLE_ALL        (WD_TIMER_INT_DISABLE_DELAY | \
                                         WD_TIMER_INT_DISABLE_OVRFLW)

/*****************************************************************************/
/*
** Values that can be used to read the status obtained from
** WDTIMERWritePostedStatusGet API.
** These values can also be combined while reading.
** For e.g. (WD_TIMER_WRITE_PENDING_WCLR | WD_TIMER_WRITE_PENDING_WCRR)
*/
/* Write pending for register WD_TIMER_WCLR */
#define WD_TIMER_WRITE_PENDING_WCLR \
    ((uint32_t) WD_TIMER_WWPS_W_PEND_WCLR_MASK)

/* Write pending for register WD_TIMER_WCRR */
#define WD_TIMER_WRITE_PENDING_WCRR \
    ((uint32_t) WD_TIMER_WWPS_W_PEND_WCRR_MASK)

/* Write pending for register WD_TIMER_WLDR */
#define WD_TIMER_WRITE_PENDING_WLDR \
    ((uint32_t) WD_TIMER_WWPS_W_PEND_WLDR_MASK)

/* Write pending for register WD_TIMER_WTGR */
#define WD_TIMER_WRITE_PENDING_WTGR \
    ((uint32_t) WD_TIMER_WWPS_W_PEND_WTGR_MASK)

/* Write pending for register WD_TIMER_WSPR */
#define WD_TIMER_WRITE_PENDING_WSPR \
    ((uint32_t) WD_TIMER_WWPS_W_PEND_WSPR_MASK)

/* Write pending for register WD_TIMER_WDLY */
#define WD_TIMER_WRITE_PENDING_WDLY \
    ((uint32_t) WD_TIMER_WWPS_W_PEND_WDLY_MASK)

/*****************************************************************************/
/*
** Watchdog timer API prototypes
*/

/**
 * \brief   Starts/Enables the watchdog timer.
 *
 * \param   baseAdd       Base Address of the Watchdog Timer Module Registers.
 *
 * \return  None.
 *
 **/
void WDTIMEREnable(uint32_t baseAdd);

/**
 * \brief   Stops/Disables the watchdog timer.
 *
 * \param   baseAdd       Base Address of the Watchdog Timer Module Registers.
 *
 * \return  None.
 *
 **/
void WDTIMERDisable(uint32_t baseAdd);

/**
 * \brief   Return the revision id of the SOC used.
 *
 * \param   baseAdd       Base Address of the Watchdog Timer Module Registers.
 *
 * \return  Returns the revision id  of the SOC used.
 *
 **/
uint32_t WDTIMERRevisionIDGet(uint32_t baseAdd);

/**
 * \brief   Reset the watchdog timer module.
 *
 * \param   baseAdd       Base Address of the Watchdog Timer Module Registers.
 *
 * \return  None.
 *
 **/
void WDTIMERReset(uint32_t baseAdd);

/**
 * \brief   This API will configure and enable the pre-scaler clock.
 *
 * \param   baseAdd      Base Address of the Watchdog Timer Module Register.
 * \param   ptv          Pre-scale clock Timer value.
 *
 * 'ptv' can take the following values \n
 *   WD_TIMER_PRESCALER_CLK_DIV_1   - WD_TIMER Functional clock divide by 1 \n
 *   WD_TIMER_PRESCALER_CLK_DIV_2   - WD_TIMER Functional clock divide by 2 \n
 *   WD_TIMER_PRESCALER_CLK_DIV_4   - WD_TIMER Functional clock divide by 4 \n
 *   WD_TIMER_PRESCALER_CLK_DIV_8   - WD_TIMER Functional clock divide by 8 \n
 *   WD_TIMER_PRESCALER_CLK_DIV_16  - WD_TIMER Functional clock divide by 16 \n
 *   WD_TIMER_PRESCALER_CLK_DIV_32  - WD_TIMER Functional clock divide by 32 \n
 *   WD_TIMER_PRESCALER_CLK_DIV_64  - WD_TIMER Functional clock divide by 64 \n
 *   WD_TIMER_PRESCALER_CLK_DIV_128 - WD_TIMER Functional clock divide by 128\n
 *
 * \return  None.
 *
 **/
void WDTIMERPreScalerClkEnable(uint32_t baseAdd, uint32_t ptv);

/**
 * \brief   This API will disable the pre-scaler clock.
 *
 * \param   baseAdd      Base Address of the Watchdog Timer Module Register.
 *
 * \return  None.
 *
 **/
void WDTIMERPreScalerClkDisable(uint32_t baseAdd);

/**
 * \brief   Set/Write the Counter register with the counter value.
 *
 * \param   baseAdd       Base Address of the Watchdog Timer Module Register.
 * \param   countVal      Count value for the Watchdog Timer.
 *
 * \return  None.
 *
 **/
void WDTIMERCounterSet(uint32_t baseAdd, uint32_t countVal);

/**
 * \brief   Get/Read the counter value from the counter register.
 *
 * \param   baseAdd       Base Address of the Watchdog Timer Module Register.
 *
 * \return  This API returns the count value present in the Watchdog Timer
 *            Counter register.
 *
 **/
uint32_t WDTIMERCounterGet(uint32_t baseAdd);

/**
 * \brief   Set the reload count value in the Watchdog timer load register.
 *
 * \param   baseAdd       Base Address of the Watchdog Timer Module Register.
 * \param   reloadVal     The reload count value of the Watchdog timer.
 *
 * \return  None.
 *
 * \note:   It is recommended to not use reload value as 0xFFFFFFFF.
 *
 **/
void WDTIMERReloadSet(uint32_t baseAdd, uint32_t reloadVal);

/**
 * \brief   Get the reload count value from the Watchdog timer load register.
 *
 * \param   baseAdd       Base Address of the Watchdog Timer Module Register.
 *
 * \return  This API returns the value present in Watchdog Timer Load Register.
 *
 **/
uint32_t WDTIMERReloadGet(uint32_t baseAdd);

/**
 * \brief   Set/enable the trigger write access.
 *
 * \param   baseAdd       Base Address of the Watchdog Timer Module Register.
 * \param   trigVal       Value to be written to the WTGR register.
 *
 * \return  None.
 *
 * \note    This API should be called if the Watchdog timer WD_TIMER_WCRR
 *          register has to be loaded with the WD_TIMER_WLDR register before
 *          overflow occurs. If this API has to be called more than once in an
 *          application then ensure each time this API is called, pass a
 *          different value to the parameter 'trigVal' to ensure proper working.
 *
 **/
void WDTIMERTriggerSet(uint32_t baseAdd, uint32_t trigVal);

/**
 * \brief   Load the delay register of Watchdog timer with the delay value.
 *
 * \param   baseAdd       Base Address of the Watchdog Timer Module Register.
 * \param   delayVal      Delay value.
 *
 * \return  None.
 *
 **/
void WDTIMERDelaySet(uint32_t baseAdd, uint32_t delayVal);

/**
 * \brief   Return the delay register value of Watchdog timer.
 *
 * \param   baseAdd       Base Address of the Watchdog Timer Module Register.
 *
 * \return  This API returns the delay register(WD_TIMER_WDLY) value of Watchdog
 *          timer.
 *
 **/
uint32_t WDTIMERDelayGet(uint32_t baseAdd);

/**
 * \brief   Set IRQ status by software.
 *
 * \param   baseAdd       Base Address of the Watchdog Timer Module Register.
 * \param   intFlags      Variable used to trigger the events.
 *
 * 'intFlags' can take the following values \n
 *    WD_TIMER_INT_DELAY - Set the status for delay interrupt \n
 *    WD_TIMER_INT_OVERFLOW - Set the status for overflow interrupt \n
 *
 * \return  None.
 *
 **/
void WDTIMERIntRawStatusSet(uint32_t baseAdd, uint32_t intFlags);

/**
 * \brief   Return the Raw IRQ status.
 *
 * \param   baseAdd       Base Address of the Watchdog Timer Module Register.
 *
 * \return  This API returns the status of the WD_TIMER_WIRQSTATRAW register.
 *
 **/
uint32_t WDTIMERIntRawStatusGet(uint32_t baseAdd);

/**
 * \brief   Read the status of WD_TIMER_WIRQSTAT register.
 *
 * \param   baseAdd       Base Address of the DMTimer Module Register.
 *
 * \return  This API returns the status of WD_TIMER_WIRQSTAT register.
 *
 **/
uint32_t WDTIMERIntStatusGet(uint32_t baseAdd);

/**
 * \brief   Clear IRQ status.
 *
 * \param   baseAdd       Base Address of the Watchdog Timer Module Register.
 * \param   intFlags      Variable used to clear the events.
 *
 * 'intFlags' can take the following values \n
 *    WD_TIMER_INT_DELAY - Clear the status for delay interrupt \n
 *    WD_TIMER_INT_OVERFLOW - Clear the status for overflow interrupt \n
 *
 * \return  None.
 *
 **/
void WDTIMERIntStatusClear(uint32_t baseAdd, uint32_t intFlags);

/**
 * \brief   Enable Watchdog timer interrupts.
 *
 * \param   baseAdd       Base Address of the Watchdog Timer Module Register.
 * \param   intFlags      Variable used to enable interrupts.
 *
 * 'intFlags' can take the following values \n
 *    WD_TIMER_INT_ENABLE_DELAY - Enable the delay interrupt \n
 *    WD_TIMER_INT_ENABLE_OVRFLW - Enable the overflow interrupt \n
 *
 * \return  None.
 *
 **/
void WDTIMERIntEnable(uint32_t baseAdd, uint32_t intFlags);

/**
 * \brief   Used to check whether interrupts of Watchdog timer are enabled
 *          or disabled.
 *
 * \param   baseAdd       Base Address of the Watchdog Timer Module Register.
 *
 * \return  This API returns the status of WD_TIMER_WIRQENSET register.
 *
 **/
uint32_t WDTIMERIntEnableStatusGet(uint32_t baseAdd);

/**
 * \brief   Disable Watchdog timer interrupts.
 *
 * \param   baseAdd       Base Address of the Watchdog Timer Module Register.
 * \param   intFlags      Variable used to enable interrupts.
 *
 * 'intFlags' can take the following values \n
 *    WD_TIMER_INT_DISABLE_DELAY - Disable the delay interrupt \n
 *    WD_TIMER_INT_DISABLE_OVRFLW - Disable the overflow interrupt \n
 *
 * \return  None.
 *
 **/
void WDTIMERIntDisable(uint32_t baseAdd, uint32_t intFlags);

/**
 * \brief   Read the status of WD_TIMER_WWPS register.
 *
 * \param   baseAdd       Base Address of the Watchdog Timer Module Register.
 * \param   flags         Status of the particular field to be returned.
 *
 * 'flags' can take the following values \n
 *    WD_TIMER_WRITE_PENDING_WCLR - Write pending for register WD_TIMER_WCLR \n
 *    WD_TIMER_WRITE_PENDING_WCRR - Write pending for register WD_TIMER_WCRR \n
 *    WD_TIMER_WRITE_PENDING_WLDR - Write pending for register WD_TIMER_WLDR \n
 *    WD_TIMER_WRITE_PENDING_WTGR - Write pending for register WD_TIMER_WTGR \n
 *    WD_TIMER_WRITE_PENDING_WSPR - Write pending for register WD_TIMER_WSPR \n
 *    WD_TIMER_WRITE_PENDING_WDLY - Write pending for register WD_TIMER_WDLY \n
 *
 * \return  Returns the status of Write posted status(WD_TIMER_WWPS) register.
 *
 **/
uint32_t WDTIMERWritePostedStatusGet(uint32_t baseAdd, uint32_t flags);

#ifdef __cplusplus
}
#endif

#endif

/********************************* END OF FILE ********************************/

