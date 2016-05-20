/******************************************************************************
*
* hw_emu_prm.h - register-level header file for PRCM
*
* Copyright (c) 2008-2013 Texas Instruments Incorporated.  All rights reserved.
* Software License Agreement
*
* Texas Instruments (TI) is supplying this software for use solely and
* exclusively on TI devices. The software is owned by TI and/or its
* suppliers, and is protected under applicable patent and copyright laws.
*
* You may not combine this software with any open-source software if such
* combination would cause this software to become subject to any of the
* license terms applicable to such open source software.
*
* THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
* NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
* NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
* CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
* DAMAGES, FOR ANY REASON WHATSOEVER.
* 
******************************************************************************
*/
#ifndef HW_EMU_PRM_H_
#define HW_EMU_PRM_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions 
****************************************************************************************************/
#define PM_EMU_PWRSTCTRL                                                                                    (0x0U)
#define PM_EMU_PWRSTST                                                                                      (0x4U)
#define RM_EMU_DEBUGSS_CONTEXT                                                                              (0x24U)

/****************************************************************************************************
* Field Definition Macros 
****************************************************************************************************/

#define PM_EMU_PWRSTCTRL_EMU_BANK_ONSTATE_SHIFT                                                             (16U)
#define PM_EMU_PWRSTCTRL_EMU_BANK_ONSTATE_MASK                                                              (0x00030000U)
#define PM_EMU_PWRSTCTRL_EMU_BANK_ONSTATE_MEM_ON                                                             (3U)

#define PM_EMU_PWRSTCTRL_POWERSTATE_SHIFT                                                                   (0U)
#define PM_EMU_PWRSTCTRL_POWERSTATE_MASK                                                                    (0x00000003U)
#define PM_EMU_PWRSTCTRL_POWERSTATE_OFF                                                                      (0U)

#define PM_EMU_PWRSTCTRL_RESERVED2_SHIFT                                                                    (18U)
#define PM_EMU_PWRSTCTRL_RESERVED2_MASK                                                                     (0xfffc0000U)

#define PM_EMU_PWRSTCTRL_RESERVED_SHIFT                                                                     (2U)
#define PM_EMU_PWRSTCTRL_RESERVED_MASK                                                                      (0x0000fffcU)

#define PM_EMU_PWRSTST_POWERSTATEST_SHIFT                                                                   (0U)
#define PM_EMU_PWRSTST_POWERSTATEST_MASK                                                                    (0x00000003U)
#define PM_EMU_PWRSTST_POWERSTATEST_ON                                                                       (3U)
#define PM_EMU_PWRSTST_POWERSTATEST_OFF                                                                      (0U)

#define PM_EMU_PWRSTST_INTRANSITION_SHIFT                                                                   (20U)
#define PM_EMU_PWRSTST_INTRANSITION_MASK                                                                    (0x00100000U)
#define PM_EMU_PWRSTST_INTRANSITION_NO                                                                       (0U)
#define PM_EMU_PWRSTST_INTRANSITION_ONGOING                                                                  (1U)

#define PM_EMU_PWRSTST_LOGICSTATEST_SHIFT                                                                   (2U)
#define PM_EMU_PWRSTST_LOGICSTATEST_MASK                                                                    (0x00000004U)
#define PM_EMU_PWRSTST_LOGICSTATEST_ON                                                                       (1U)
#define PM_EMU_PWRSTST_LOGICSTATEST_OFF                                                                      (0U)

#define PM_EMU_PWRSTST_EMU_BANK_STATEST_SHIFT                                                               (4U)
#define PM_EMU_PWRSTST_EMU_BANK_STATEST_MASK                                                                (0x00000030U)
#define PM_EMU_PWRSTST_EMU_BANK_STATEST_MEM_ON                                                               (3U)
#define PM_EMU_PWRSTST_EMU_BANK_STATEST_RESERVED1                                                            (1U)
#define PM_EMU_PWRSTST_EMU_BANK_STATEST_MEM_OFF                                                              (0U)
#define PM_EMU_PWRSTST_EMU_BANK_STATEST_RESERVED2                                                            (2U)

#define PM_EMU_PWRSTST_RESERVED_SHIFT                                                                       (3U)
#define PM_EMU_PWRSTST_RESERVED_MASK                                                                        (0x00000008U)

#define PM_EMU_PWRSTST_RESERVED1_SHIFT                                                                      (6U)
#define PM_EMU_PWRSTST_RESERVED1_MASK                                                                       (0x000fffc0U)

#define PM_EMU_PWRSTST_RESERVED2_SHIFT                                                                      (21U)
#define PM_EMU_PWRSTST_RESERVED2_MASK                                                                       (0x00e00000U)

#define PM_EMU_PWRSTST_LASTPOWERSTATEENTERED_SHIFT                                                          (24U)
#define PM_EMU_PWRSTST_LASTPOWERSTATEENTERED_MASK                                                           (0x03000000U)
#define PM_EMU_PWRSTST_LASTPOWERSTATEENTERED_ON                                                              (3U)
#define PM_EMU_PWRSTST_LASTPOWERSTATEENTERED_OFF                                                             (0U)
#define PM_EMU_PWRSTST_LASTPOWERSTATEENTERED_RET                                                             (1U)
#define PM_EMU_PWRSTST_LASTPOWERSTATEENTERED_INACTIVE                                                        (2U)

#define PM_EMU_PWRSTST_RESERVED3_SHIFT                                                                      (26U)
#define PM_EMU_PWRSTST_RESERVED3_MASK                                                                       (0xfc000000U)

#define RM_EMU_DEBUGSS_CONTEXT_RESERVED_SHIFT                                                               (1U)
#define RM_EMU_DEBUGSS_CONTEXT_RESERVED_MASK                                                                (0x000000feU)

#define RM_EMU_DEBUGSS_CONTEXT_RESERVED1_SHIFT                                                              (9U)
#define RM_EMU_DEBUGSS_CONTEXT_RESERVED1_MASK                                                               (0xfffffe00U)

#define RM_EMU_DEBUGSS_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                                        (0U)
#define RM_EMU_DEBUGSS_CONTEXT_LOSTCONTEXT_DFF_MASK                                                         (0x00000001U)
#define RM_EMU_DEBUGSS_CONTEXT_LOSTCONTEXT_DFF_LOST                                                          (1U)
#define RM_EMU_DEBUGSS_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                                    (0U)

#define RM_EMU_DEBUGSS_CONTEXT_LOSTMEM_EMU_BANK_SHIFT                                                       (8U)
#define RM_EMU_DEBUGSS_CONTEXT_LOSTMEM_EMU_BANK_MASK                                                        (0x00000100U)
#define RM_EMU_DEBUGSS_CONTEXT_LOSTMEM_EMU_BANK_LOST                                                         (1U)
#define RM_EMU_DEBUGSS_CONTEXT_LOSTMEM_EMU_BANK_MAINTAINED                                                   (0U)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_EMU_PRM_H_ */
