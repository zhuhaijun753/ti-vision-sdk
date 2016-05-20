/**
 *  \file  ipu_wugen.h
 *
 *  \brief This file contains the API prototypes for configuring MPU_WUGEN for
 *         ARM Cortex-M4
 *
 *  \copyright Copyright (C) 2014 Texas Instruments Incorporated -
 *             http://www.ti.com/
 */

/* =============================================================================
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
 * ===========================================================================*/

#ifndef IPU_WUGEN_H
#define IPU_WUGEN_H

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define IPU_WUGEN_NUM_INTR_INTERNAL   (16U)
/**< \brief Number of Internal Interrupts IPU can service */

#define IPU_WUGEN_FIRST_EXTERNAL_INT_NUM    (23U)
/**< \brief First interrupt number which is external */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief   This API is used to initialize MPU_WUGEN. All wakeup events will be
 *          disabled after initialization.
 *
 * \param   None
 *
 * \return  None.
 *
 **/
void IPU_WUGEN_Init(void);

/**
 * \brief  Disables all wakeup events for CPU.
 *
 * \param    None
 *
 * \return   None
 *
 **/
void IPU_WUGEN_DisableAll(void);

/**
 * \brief  Configure wakeup events by looking up the CPU0 interrupt settings.
 *
 * \param    None
 *
 * \return   None
 *
 **/
void IPU_WUGEN_Interrupt_Lookup(void);

/**
 * \brief   This API enables the CPU0 wakeup event for requested interrupt.
 *
 * \param   intrNum  - Interrupt number
 *
 * \return  None.
 *
 **/
void IPU_WUGEN_Enable(uint16_t intrNum);

/**
 * \brief   This API disables the CPU0 wakeup event for requested interrupt.
 *
 * \param   intrNum  - Interrupt number
 *
 * \return  None.
 *
 **/
void IPU_WUGEN_Disable(uint16_t intrNum);

#ifdef __cplusplus
}
#endif
#endif

