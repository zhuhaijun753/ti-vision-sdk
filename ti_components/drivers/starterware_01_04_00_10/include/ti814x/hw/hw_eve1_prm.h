/******************************************************************************
*
* hw_eve1_prm.h - register-level header file for PRCM
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
#ifndef HW_EVE1_PRM_H_
#define HW_EVE1_PRM_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions 
****************************************************************************************************/
#define PM_EVE1_PWRSTCTRL                                                                                   (0x0U)
#define PM_EVE1_PWRSTST                                                                                     (0x4U)
#define RM_EVE1_RSTCTRL                                                                                     (0x10U)
#define RM_EVE1_RSTST                                                                                       (0x14U)
#define PM_EVE1_EVE1_WKDEP                                                                                  (0x20U)
#define RM_EVE1_EVE1_CONTEXT                                                                                (0x24U)

/****************************************************************************************************
* Field Definition Macros 
****************************************************************************************************/

#define PM_EVE1_PWRSTCTRL_EVE1_BANK_ONSTATE_SHIFT                                                           (16U)
#define PM_EVE1_PWRSTCTRL_EVE1_BANK_ONSTATE_MASK                                                            (0x00030000U)
#define PM_EVE1_PWRSTCTRL_EVE1_BANK_ONSTATE_MEM_ON                                                           (3U)

#define PM_EVE1_PWRSTCTRL_POWERSTATE_SHIFT                                                                  (0U)
#define PM_EVE1_PWRSTCTRL_POWERSTATE_MASK                                                                   (0x00000003U)
#define PM_EVE1_PWRSTCTRL_POWERSTATE_OFF                                                                     (0U)
#define PM_EVE1_PWRSTCTRL_POWERSTATE_INACT                                                                   (2U)
#define PM_EVE1_PWRSTCTRL_POWERSTATE_ON                                                                      (3U)
#define PM_EVE1_PWRSTCTRL_POWERSTATE_RESERVED                                                                (1U)

#define PM_EVE1_PWRSTCTRL_LOWPOWERSTATECHANGE_SHIFT                                                         (4U)
#define PM_EVE1_PWRSTCTRL_LOWPOWERSTATECHANGE_MASK                                                          (0x00000010U)
#define PM_EVE1_PWRSTCTRL_LOWPOWERSTATECHANGE_EN                                                             (1U)
#define PM_EVE1_PWRSTCTRL_LOWPOWERSTATECHANGE_DIS                                                            (0U)

#define PM_EVE1_PWRSTCTRL_RESERVED2_SHIFT                                                                   (18U)
#define PM_EVE1_PWRSTCTRL_RESERVED2_MASK                                                                    (0xfffc0000U)

#define PM_EVE1_PWRSTCTRL_RESERVED_SHIFT                                                                    (2U)
#define PM_EVE1_PWRSTCTRL_RESERVED_MASK                                                                     (0x0000000cU)

#define PM_EVE1_PWRSTCTRL_RESERVED1_SHIFT                                                                   (5U)
#define PM_EVE1_PWRSTCTRL_RESERVED1_MASK                                                                    (0x0000ffe0U)

#define PM_EVE1_PWRSTST_POWERSTATEST_SHIFT                                                                  (0U)
#define PM_EVE1_PWRSTST_POWERSTATEST_MASK                                                                   (0x00000003U)
#define PM_EVE1_PWRSTST_POWERSTATEST_ON                                                                      (3U)
#define PM_EVE1_PWRSTST_POWERSTATEST_OFF                                                                     (0U)
#define PM_EVE1_PWRSTST_POWERSTATEST_RET                                                                     (1U)
#define PM_EVE1_PWRSTST_POWERSTATEST_INACTIVE                                                                (2U)

#define PM_EVE1_PWRSTST_INTRANSITION_SHIFT                                                                  (20U)
#define PM_EVE1_PWRSTST_INTRANSITION_MASK                                                                   (0x00100000U)
#define PM_EVE1_PWRSTST_INTRANSITION_NO                                                                      (0U)
#define PM_EVE1_PWRSTST_INTRANSITION_ONGOING                                                                 (1U)

#define PM_EVE1_PWRSTST_LOGICSTATEST_SHIFT                                                                  (2U)
#define PM_EVE1_PWRSTST_LOGICSTATEST_MASK                                                                   (0x00000004U)
#define PM_EVE1_PWRSTST_LOGICSTATEST_ON                                                                      (1U)
#define PM_EVE1_PWRSTST_LOGICSTATEST_OFF                                                                     (0U)

#define PM_EVE1_PWRSTST_EVE1_BANK_STATEST_SHIFT                                                             (4U)
#define PM_EVE1_PWRSTST_EVE1_BANK_STATEST_MASK                                                              (0x00000030U)
#define PM_EVE1_PWRSTST_EVE1_BANK_STATEST_MEM_ON                                                             (3U)
#define PM_EVE1_PWRSTST_EVE1_BANK_STATEST_RESEREVD1                                                          (1U)
#define PM_EVE1_PWRSTST_EVE1_BANK_STATEST_MEM_OFF                                                            (0U)
#define PM_EVE1_PWRSTST_EVE1_BANK_STATEST_RESERVED                                                           (2U)

#define PM_EVE1_PWRSTST_RESERVED_SHIFT                                                                      (3U)
#define PM_EVE1_PWRSTST_RESERVED_MASK                                                                       (0x00000008U)

#define PM_EVE1_PWRSTST_RESERVED1_SHIFT                                                                     (10U)
#define PM_EVE1_PWRSTST_RESERVED1_MASK                                                                      (0x000ffc00U)

#define PM_EVE1_PWRSTST_RESERVED2_SHIFT                                                                     (21U)
#define PM_EVE1_PWRSTST_RESERVED2_MASK                                                                      (0x00e00000U)

#define PM_EVE1_PWRSTST_RESERVED3_SHIFT                                                                     (26U)
#define PM_EVE1_PWRSTST_RESERVED3_MASK                                                                      (0xfc000000U)

#define PM_EVE1_PWRSTST_LASTPOWERSTATEENTERED_SHIFT                                                         (24U)
#define PM_EVE1_PWRSTST_LASTPOWERSTATEENTERED_MASK                                                          (0x03000000U)
#define PM_EVE1_PWRSTST_LASTPOWERSTATEENTERED_ON                                                             (3U)
#define PM_EVE1_PWRSTST_LASTPOWERSTATEENTERED_OFF                                                            (0U)
#define PM_EVE1_PWRSTST_LASTPOWERSTATEENTERED_RET                                                            (1U)
#define PM_EVE1_PWRSTST_LASTPOWERSTATEENTERED_INACTIVE                                                       (2U)

#define PM_EVE1_PWRSTST_RESERVED4_SHIFT                                                                     (6U)
#define PM_EVE1_PWRSTST_RESERVED4_MASK                                                                      (0x000003c0U)

#define RM_EVE1_RSTCTRL_RST_EVE1_LRST_SHIFT                                                                 (0U)
#define RM_EVE1_RSTCTRL_RST_EVE1_LRST_MASK                                                                  (0x00000001U)
#define RM_EVE1_RSTCTRL_RST_EVE1_LRST_ASSERT                                                                 (1U)
#define RM_EVE1_RSTCTRL_RST_EVE1_LRST_CLEAR                                                                  (0U)

#define RM_EVE1_RSTCTRL_RST_EVE1_SHIFT                                                                      (1U)
#define RM_EVE1_RSTCTRL_RST_EVE1_MASK                                                                       (0x00000002U)
#define RM_EVE1_RSTCTRL_RST_EVE1_ASSERT                                                                      (1U)
#define RM_EVE1_RSTCTRL_RST_EVE1_CLEAR                                                                       (0U)

#define RM_EVE1_RSTCTRL_RESERVED_SHIFT                                                                      (2U)
#define RM_EVE1_RSTCTRL_RESERVED_MASK                                                                       (0xfffffffcU)

#define RM_EVE1_RSTST_RST_EVE1_EMU_SHIFT                                                                    (2U)
#define RM_EVE1_RSTST_RST_EVE1_EMU_MASK                                                                     (0x00000004U)
#define RM_EVE1_RSTST_RST_EVE1_EMU_RESET_YES                                                                 (1U)
#define RM_EVE1_RSTST_RST_EVE1_EMU_RESET_NO                                                                  (0U)

#define RM_EVE1_RSTST_RST_EVE1_LRST_SHIFT                                                                   (0U)
#define RM_EVE1_RSTST_RST_EVE1_LRST_MASK                                                                    (0x00000001U)
#define RM_EVE1_RSTST_RST_EVE1_LRST_RESET_YES                                                                (1U)
#define RM_EVE1_RSTST_RST_EVE1_LRST_RESET_NO                                                                 (0U)

#define RM_EVE1_RSTST_RST_EVE1_SHIFT                                                                        (1U)
#define RM_EVE1_RSTST_RST_EVE1_MASK                                                                         (0x00000002U)
#define RM_EVE1_RSTST_RST_EVE1_RESET_YES                                                                     (1U)
#define RM_EVE1_RSTST_RST_EVE1_RESET_NO                                                                      (0U)

#define RM_EVE1_RSTST_RST_EVE1_EMU_REQ_SHIFT                                                                (3U)
#define RM_EVE1_RSTST_RST_EVE1_EMU_REQ_MASK                                                                 (0x00000008U)
#define RM_EVE1_RSTST_RST_EVE1_EMU_REQ_RESET_YES                                                             (1U)
#define RM_EVE1_RSTST_RST_EVE1_EMU_REQ_RESET_NO                                                              (0U)

#define RM_EVE1_RSTST_RESERVED_SHIFT                                                                        (4U)
#define RM_EVE1_RSTST_RESERVED_MASK                                                                         (0xfffffff0U)

#define PM_EVE1_EVE1_WKDEP_WKUPDEP_EVE1_MPU_SHIFT                                                           (0U)
#define PM_EVE1_EVE1_WKDEP_WKUPDEP_EVE1_MPU_MASK                                                            (0x00000001U)
#define PM_EVE1_EVE1_WKDEP_WKUPDEP_EVE1_MPU_ENABLED                                                          (1U)
#define PM_EVE1_EVE1_WKDEP_WKUPDEP_EVE1_MPU_DISABLED                                                         (0U)

#define PM_EVE1_EVE1_WKDEP_WKUPDEP_EVE1_DSP1_SHIFT                                                          (2U)
#define PM_EVE1_EVE1_WKDEP_WKUPDEP_EVE1_DSP1_MASK                                                           (0x00000004U)
#define PM_EVE1_EVE1_WKDEP_WKUPDEP_EVE1_DSP1_ENABLED                                                         (1U)
#define PM_EVE1_EVE1_WKDEP_WKUPDEP_EVE1_DSP1_DISABLED                                                        (0U)

#define PM_EVE1_EVE1_WKDEP_WKUPDEP_EVE1_IPU2_SHIFT                                                          (1U)
#define PM_EVE1_EVE1_WKDEP_WKUPDEP_EVE1_IPU2_MASK                                                           (0x00000002U)
#define PM_EVE1_EVE1_WKDEP_WKUPDEP_EVE1_IPU2_ENABLED                                                         (1U)
#define PM_EVE1_EVE1_WKDEP_WKUPDEP_EVE1_IPU2_DISABLED                                                        (0U)

#define PM_EVE1_EVE1_WKDEP_WKUPDEP_EVE1_SDMA_SHIFT                                                          (3U)
#define PM_EVE1_EVE1_WKDEP_WKUPDEP_EVE1_SDMA_MASK                                                           (0x00000008U)
#define PM_EVE1_EVE1_WKDEP_WKUPDEP_EVE1_SDMA_ENABLED                                                         (1U)
#define PM_EVE1_EVE1_WKDEP_WKUPDEP_EVE1_SDMA_DISABLED                                                        (0U)

#define PM_EVE1_EVE1_WKDEP_WKUPDEP_EVE1_IPU1_SHIFT                                                          (4U)
#define PM_EVE1_EVE1_WKDEP_WKUPDEP_EVE1_IPU1_MASK                                                           (0x00000010U)
#define PM_EVE1_EVE1_WKDEP_WKUPDEP_EVE1_IPU1_ENABLED                                                         (1U)
#define PM_EVE1_EVE1_WKDEP_WKUPDEP_EVE1_IPU1_DISABLED                                                        (0U)

#define PM_EVE1_EVE1_WKDEP_WKUPDEP_EVE1_DSP2_SHIFT                                                          (5U)
#define PM_EVE1_EVE1_WKDEP_WKUPDEP_EVE1_DSP2_MASK                                                           (0x00000020U)
#define PM_EVE1_EVE1_WKDEP_WKUPDEP_EVE1_DSP2_ENABLED                                                         (1U)
#define PM_EVE1_EVE1_WKDEP_WKUPDEP_EVE1_DSP2_DISABLED                                                        (0U)

#define PM_EVE1_EVE1_WKDEP_WKUPDEP_EVE1_EVE2_SHIFT                                                          (7U)
#define PM_EVE1_EVE1_WKDEP_WKUPDEP_EVE1_EVE2_MASK                                                           (0x00000080U)
#define PM_EVE1_EVE1_WKDEP_WKUPDEP_EVE1_EVE2_ENABLED                                                         (1U)
#define PM_EVE1_EVE1_WKDEP_WKUPDEP_EVE1_EVE2_DISABLED                                                        (0U)

#define PM_EVE1_EVE1_WKDEP_WKUPDEP_EVE1_EVE3_SHIFT                                                          (8U)
#define PM_EVE1_EVE1_WKDEP_WKUPDEP_EVE1_EVE3_MASK                                                           (0x00000100U)
#define PM_EVE1_EVE1_WKDEP_WKUPDEP_EVE1_EVE3_ENABLED                                                         (1U)
#define PM_EVE1_EVE1_WKDEP_WKUPDEP_EVE1_EVE3_DISABLED                                                        (0U)

#define PM_EVE1_EVE1_WKDEP_WKUPDEP_EVE1_EVE4_SHIFT                                                          (9U)
#define PM_EVE1_EVE1_WKDEP_WKUPDEP_EVE1_EVE4_MASK                                                           (0x00000200U)
#define PM_EVE1_EVE1_WKDEP_WKUPDEP_EVE1_EVE4_ENABLED                                                         (1U)
#define PM_EVE1_EVE1_WKDEP_WKUPDEP_EVE1_EVE4_DISABLED                                                        (0U)

#define PM_EVE1_EVE1_WKDEP_RESERVED_SHIFT                                                                   (10U)
#define PM_EVE1_EVE1_WKDEP_RESERVED_MASK                                                                    (0xfffffc00U)

#define PM_EVE1_EVE1_WKDEP_RESERVED1_SHIFT                                                                  (6U)
#define PM_EVE1_EVE1_WKDEP_RESERVED1_MASK                                                                   (0x00000040U)

#define RM_EVE1_EVE1_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                                          (0U)
#define RM_EVE1_EVE1_CONTEXT_LOSTCONTEXT_DFF_MASK                                                           (0x00000001U)
#define RM_EVE1_EVE1_CONTEXT_LOSTCONTEXT_DFF_LOST                                                            (1U)
#define RM_EVE1_EVE1_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                                      (0U)

#define RM_EVE1_EVE1_CONTEXT_LOSTMEM_EVE_BANK_SHIFT                                                         (8U)
#define RM_EVE1_EVE1_CONTEXT_LOSTMEM_EVE_BANK_MASK                                                          (0x00000100U)
#define RM_EVE1_EVE1_CONTEXT_LOSTMEM_EVE_BANK_LOST                                                           (1U)
#define RM_EVE1_EVE1_CONTEXT_LOSTMEM_EVE_BANK_MAINTAINED                                                     (0U)

#define RM_EVE1_EVE1_CONTEXT_RESERVED1_SHIFT                                                                (9U)
#define RM_EVE1_EVE1_CONTEXT_RESERVED1_MASK                                                                 (0xfffffe00U)

#define RM_EVE1_EVE1_CONTEXT_RESERVED_SHIFT                                                                 (1U)
#define RM_EVE1_EVE1_CONTEXT_RESERVED_MASK                                                                  (0x000000feU)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_EVE1_PRM_H_ */
