/**
 *  \file     mmu_a15_gcc_asm.h
 *
 *  \brief    This file contains the function declarations for ASM APIs needed
 *            by the A15 MMU HAL.
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

#ifndef MMU_A15_GCC_ASM_H_
#define MMU_A15_GCC_ASM_H_

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
 * \brief   This function contains the assembly code for initializing the A15
 *          MMU.
 *
 * \param   None.
 *
 * \return  None.
 */
extern void MMUA15InitASM(void);

/**
 * \brief   This function contains assembly instructions for disabling A15 MMU.
 *
 * \param   None.
 *
 * \return  None.
 */
extern void MMUA15DisableASM(void);

/**
 * \brief   This function contains assembly instructions for enabling A15 MMU.
 *
 * \param   mmuTable     MMU module table.
 *
 * \return  None.
 */
extern void MMUA15EnableASM(const mmuA15ModuleTable_t *mmuTable);

/**
 * \brief   This function contains assembly instructions that determine whether
 *          MMU is enabled or not.
 *
 * \param   None.
 *
 * \return  enabledStatus       MMU Enable Status.
 *                              1:Enabled 0:Disabled
 */
extern uint32_t MMUA15IsEnabledASM(void);

/**
 * \brief   This function contains assembly instructions for writing to MAIR
 *          register.
 *
 * \param   attrIndx  Attriute index.
 * \param   attr      Memory attributes.
 *
 * \return  None.
 */
extern void MMUA15WriteMAIRASM(uint32_t attrIndx, uint32_t attr);

/**
 * \brief   This function contain assembly instructions for invalidating the
 *          entire TLB entries for the specified memory range.
 *
 * \param   startAddr    Start Address.
 * \param   length       Length of memory region.
 *
 * \return  None.
 */
extern void MMUA15TLBInvalidateASM(uint32_t startAddr, uint32_t length);

/**
 * \brief   This function contain assembly instructions for invalidating the
 *          entire TLB.
 *
 * \param   None.
 *
 * \return  None.
 */
extern void MMUA15TLBInvalidateAllASM(void);

#ifdef __cplusplus
}

#endif

#endif

