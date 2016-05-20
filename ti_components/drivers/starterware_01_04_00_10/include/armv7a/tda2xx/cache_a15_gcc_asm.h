/**
 *  \file     cache_a15_gcc_asm.h
 *
 *  \brief    This file contains the function declarations for ASM APIs needed
 *            by the A15 Cache HAL.
 *
 *  \copyright Copyright (C) 2015 Texas Instruments Incorporated -
 *             http://www.ti.com/
 */

/* ======================================================================
 *   Copyright (C) 2015 Texas Instruments Incorporated
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

#ifndef CACHE_A15_GCC_ASM_H_
#define CACHE_A15_GCC_ASM_H_

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
/*                 Internal Function Declarations                             */
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
 * \brief   This function contains the assembly code for getting the mask
 *          corresponding to enabled A15 cache.
 *
 * \param   None.
 *
 * \return  enabledCache     Mask corresponding to enabled cache.
 */
extern uint32_t CACHEA15GetEnabledASM(void);

#ifdef __cplusplus
}

#endif

#endif

