/**
 *  \file  intctl.h
 *
 *  \brief INTCTL library function configures the MPU interrupt handler
 *                 with basic functions like routing (to fiq or irq) ,enabling ,
 *                 prioritizing, masking each interrupt.
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

#ifndef INTCTL_H
#define INTCTL_H

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/**
 * \brief Identify the kind of interrupt: either FIQ/IRQ
 */
typedef  enum INTCTL_InterruptKind_label{
    INTCTL_IRQ = 0,                                       /**< IRQ */
    INTCTL_FIQ = 1                                        /**< FIQ */
} INTCTL_InterruptKind_t,*pINTCTL_InterruptKind_t;

/**
 * \brief Priority level of the interrupt. 0=highest priority ,as the
 *        level increases priority decreases.
 */
typedef enum INTCTL_InterruptPriority
{
  INTCTL_NMI = 1,                              /**< interrupt priority NMI */
  INTCTL_INT4 = 2,                             /**< interrupt priority INT4   */
  INTCTL_INT5 = 3,                             /**< interrupt priority INT5   */
  INTCTL_INT6 = 4,                             /**< interrupt priority INT6   */
  INTCTL_INT7 = 5,                             /**< interrupt priority INT7   */
  INTCTL_INT8 = 6,                             /**< interrupt priority INT8   */
  INTCTL_INT9 = 7,                             /**< interrupt priority INT9   */
  INTCTL_INT10 = 8,                            /**< interrupt priority INT10  */
  INTCTL_INT11 = 9,                            /**< interrupt priority INT11  */
  INTCTL_INT12 = 10,                           /**< interrupt priority INT12  */
  INTCTL_INT13 = 11,                           /**< interrupt priority INT13  */
  INTCTL_INT14 = 12,                           /**< interrupt priority INT14  */
  INTCTL_INT15 = 13,                           /**< interrupt priority INT15  */
  INTCTL_INT_MAX = INTCTL_INT15                /**< maximum interrupt priority*/
} INTCTL_Priority_t;

/**
 * \brief Enumerated Type used to specify either enable or disable the interrupt
 */
typedef  enum INTCTL_Enable_label{
    INTCTL_DISABLE = 0,                       /**< interrupt disable */
    INTCTL_ENABLE  = 1                        /**< interrupt enable */
} INTCTL_Enable_t,*pINTCTL_Enable_t;

/**
 * \brief Enumerated Type used to specify either Set or Clear the interrupt
 */
typedef  enum INTCTL_SetNClear_label{
    INTCTL_CLEAR = 0,                            /**< set interrupt */
    INTCTL_SET   = 1                             /**< clear interrupt */
} INTCTL_SetNClear_t,*pINTCTL_SetNClear_t;

/**
 * \brief Enumerated Type used to specify either functional clock or OCP clock
 */
typedef  enum INTCTL_funcNocp_clk_label{
    INTCTL_OCPCLK  = 0,                               /**< OCP clock */
    INTCTL_FUNCCLK = 1                                /**< functional clock */
} INTCTL_funcNocp_clk_t,*pINTCTL_funcNocp_clk_t;


/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief   Set priority level of interrupt
 *
 * \param   baseAddress      Base address of the module
 *          itNumber         predefined order number is the IT position
 *                           into the Interrupt Level Register  range 0 .. 95
 *          interruptKind    Specifies IRQ or FIQ interrupt needs to be generate
 *          priority         Priority level of the interrupt 0=highest priority
 *
 * \return  Returns whether the passed parameter is OK or NOT
 *                    STW_SOK                  No errors
 *                    STW_EFAIL                Bad Parameter passed
 *
 **/
extern int32_t EVE_INTCTL_LevelInit (const uint32_t                baseAddress,
                                     const uint8_t                 itNumber,
                                     const INTCTL_InterruptKind_t interruptKind,
                                     const INTCTL_Priority_t      priority);

/**
 * \brief   Enable or disable interrupt
 *
 * \param   baseAddress      Base address of the module
 *          itNumber         The interrupt to process
 *          enableNdisable   Enables or Disables the specified interrupt
 *
 * \return  Returns whether the passed parameter is OK or NOT
 *                    STW_SOK                  No errors
 *                    STW_EFAIL                Bad Parameter passed
 *
 **/
extern int32_t EVE_INTCTL_OneITEnable (const uint32_t           baseAddress,
                                        const uint8_t            itNumber,
                                        const INTCTL_Enable_t   enableNdisable);

/**
 * \brief   Enable or disable interrupt
 *
 * \param   baseAddress       Base address of the module
 *          interruptPriority Priority level of the interrupt 0=highest priority
 *          interruptNumber   Number of the active and acknowledged Interrupt
 *
 * \return  Returns whether the passed parameter is OK or NOT
 *                    STW_SOK                  No errors
 *                    STW_EFAIL                Bad Parameter passed
 *
 **/
extern int32_t EVE_INTCTL_Ack (const uint32_t                 baseAddress,
                                const INTCTL_Priority_t       interruptPriority,
                                uint16_t *const                interruptNumber);

/**
 * \brief   Valid current active interrupt
 *
 * \param   baseAddress       Base address of the module
 *          interruptPriority Priority level of the interrupt 0=highest priority
 *
 * \return  Returns whether the passed parameter is OK or NOT
 *                    STW_SOK                  No errors
 *                    STW_EFAIL                Bad Parameter passed
 *
 **/
extern int32_t EVE_INTCTL_NextValid (const uint32_t           baseAddress,
                                     const INTCTL_Priority_t interruptPriority);

#endif  /* INTCTL_H */

