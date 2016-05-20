/**
 *  \file  dsp_wugen.h
 *
 *  \brief This file contains the API prototypes for configuring DSP_WUGEN for
 *         DSP
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

#ifndef DSP_WUGEN_IRQ_H
#define DSP_WUGEN_IRQ_H

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

/* None */

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
 * \brief   This API is used to initialize DSP_WUGEN. All wakeup events will be
 *          disabled after initialization.
 *
 * \param   None
 *
 * \return  None.
 *
 **/
void DSP_WUGEN_IRQ_Init(void);

/**
 * \brief  Disables all wakeup events for DSP.
 *
 * \param    None
 *
 * \return   None
 *
 **/
void DSP_WUGEN_IRQ_DisableAll(void);

/**
 * \brief   This API is used to initialize DSP_WUGEN. All DMA wakeup events will
 *          be disabled after initialization.
 *
 * \param   None
 *
 * \return  None.
 *
 **/
void DSP_WUGEN_DMAEVENT_Init(void);

/**
 * \brief  Disables all DMA wakeup events for DSP.
 *
 * \param    None
 *
 * \return   None
 *
 **/
void DSP_WUGEN_DMAEVENT_DisableAll(void);

/**
 * \brief  Configure wakeup events by looking up the DSP interrupt settings.
 *
 * \param    None
 *
 * \return   None
 *
 **/
void DSP_WUGEN_IRQ_Interrupt_Lookup(void);

/**
 * \brief   This API enables the DSP wakeup event for requested interrupt.
 *
 * \param   intrNum  - Interrupt number
 *
 * \return  None.
 *
 **/
void DSP_WUGEN_IRQ_Enable(uint16_t intrNum);

/**
 * \brief   This API disables the DSP wakeup event for requested interrupt.
 *
 * \param   intrNum  - Interrupt number
 *
 * \return  None.
 *
 **/
void DSP_WUGEN_IRQ_Disable(uint16_t intrNum);

/**
 * \brief   This API enables the DSP wakeup event for requested DMA event.
 *
 * \param   intrNum  - Interrupt number
 *
 * \return  None.
 *
 **/
void DSP_WUGEN_DMAEVENT_Enable(uint16_t dmaEvtNum);

/**
 * \brief   This API disables the DSP wakeup event for requested DMA event.
 *
 * \param   intrNum  - Interrupt number
 *
 * \return  None.
 *
 **/
void DSP_WUGEN_DMAEVENT_Disable(uint16_t dmaEvtNum);

#ifdef __cplusplus
}
#endif
#endif

