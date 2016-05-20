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
#ifndef SBL_TDA2XX_WD_TIMER_H_
#define SBL_TDA2XX_WD_TIMER_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <wd_timer.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* ========================================================================== */
/*                            Global Variables Declarations                   */
/* ========================================================================== */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief  This function get called on begining of sbl boot. Refresh the
 *          WD_TIMER to 3 mins, configure the DLY event to 2 mins &
 *            register the ISR handler.
 *
 *
 * \param   none
 *
 * \returns none
 *
 *
 **/
void SBLWdtimerBegin(void);

/**
 * \brief  This DLY event isr handler. Refresh the WD_TIMER to 3 mins &
 *          set the DLY to 2 mins
 *
 *
 * \param
 *
 * \returns none
 *
 *
 **/
void SBLWdtimerIsr(void *ptr);

/**
 * \brief  This function get at the end of boot process. Un-register the DLY
 *          event isr & disable the interrupt. Again refresh the WD_TIMER OVF
 *          value to 3 mins. Application will be responsible to refresh the
 *          WD_TIMER
 *
 * \param none
 *
 * \returns none
 *
 *
 **/

void SBLWdtimerEnd(void);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef SBL_TDA2XX_WD_TIMER_H_*/

