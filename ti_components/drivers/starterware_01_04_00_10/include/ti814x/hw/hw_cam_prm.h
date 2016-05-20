/******************************************************************************
*
* hw_cam_prm.h - register-level header file for PRCM
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
#ifndef HW_CAM_PRM_H_
#define HW_CAM_PRM_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions 
****************************************************************************************************/
#define PM_CAM_PWRSTCTRL                                                                                    (0x0U)
#define PM_CAM_PWRSTST                                                                                      (0x4U)
#define PM_CAM_VIP1_WKDEP                                                                                   (0x20U)
#define RM_CAM_VIP1_CONTEXT                                                                                 (0x24U)
#define PM_CAM_VIP2_WKDEP                                                                                   (0x28U)
#define RM_CAM_VIP2_CONTEXT                                                                                 (0x2cU)
#define PM_CAM_VIP3_WKDEP                                                                                   (0x30U)
#define RM_CAM_VIP3_CONTEXT                                                                                 (0x34U)
#define RM_CAM_LVDSRX_CONTEXT                                                                               (0x3cU)
#define RM_CAM_CSI1_CONTEXT                                                                                 (0x44U)
#define RM_CAM_CSI2_CONTEXT                                                                                 (0x4cU)

/****************************************************************************************************
* Field Definition Macros 
****************************************************************************************************/

#define PM_CAM_PWRSTCTRL_VIP_BANK_ONSTATE_SHIFT                                                             (16U)
#define PM_CAM_PWRSTCTRL_VIP_BANK_ONSTATE_MASK                                                              (0x00030000U)
#define PM_CAM_PWRSTCTRL_VIP_BANK_ONSTATE_MEM_ON                                                             (3U)

#define PM_CAM_PWRSTCTRL_POWERSTATE_SHIFT                                                                   (0U)
#define PM_CAM_PWRSTCTRL_POWERSTATE_MASK                                                                    (0x00000003U)
#define PM_CAM_PWRSTCTRL_POWERSTATE_OFF                                                                      (0U)
#define PM_CAM_PWRSTCTRL_POWERSTATE_INACT                                                                    (2U)
#define PM_CAM_PWRSTCTRL_POWERSTATE_RESERVED                                                                 (1U)
#define PM_CAM_PWRSTCTRL_POWERSTATE_ON                                                                       (3U)

#define PM_CAM_PWRSTCTRL_RESERVED2_SHIFT                                                                    (18U)
#define PM_CAM_PWRSTCTRL_RESERVED2_MASK                                                                     (0xfffc0000U)

#define PM_CAM_PWRSTCTRL_LOWPOWERSTATECHANGE_SHIFT                                                          (4U)
#define PM_CAM_PWRSTCTRL_LOWPOWERSTATECHANGE_MASK                                                           (0x00000010U)
#define PM_CAM_PWRSTCTRL_LOWPOWERSTATECHANGE_EN                                                              (1U)
#define PM_CAM_PWRSTCTRL_LOWPOWERSTATECHANGE_DIS                                                             (0U)

#define PM_CAM_PWRSTCTRL_RESERVED_SHIFT                                                                     (2U)
#define PM_CAM_PWRSTCTRL_RESERVED_MASK                                                                      (0x0000000cU)

#define PM_CAM_PWRSTCTRL_RESERVED1_SHIFT                                                                    (5U)
#define PM_CAM_PWRSTCTRL_RESERVED1_MASK                                                                     (0x0000ffe0U)

#define PM_CAM_PWRSTST_POWERSTATEST_SHIFT                                                                   (0U)
#define PM_CAM_PWRSTST_POWERSTATEST_MASK                                                                    (0x00000003U)
#define PM_CAM_PWRSTST_POWERSTATEST_ON                                                                       (3U)
#define PM_CAM_PWRSTST_POWERSTATEST_OFF                                                                      (0U)
#define PM_CAM_PWRSTST_POWERSTATEST_RESERVED                                                                 (1U)
#define PM_CAM_PWRSTST_POWERSTATEST_INACTIVE                                                                 (2U)

#define PM_CAM_PWRSTST_INTRANSITION_SHIFT                                                                   (20U)
#define PM_CAM_PWRSTST_INTRANSITION_MASK                                                                    (0x00100000U)
#define PM_CAM_PWRSTST_INTRANSITION_NO                                                                       (0U)
#define PM_CAM_PWRSTST_INTRANSITION_ONGOING                                                                  (1U)

#define PM_CAM_PWRSTST_LOGICSTATEST_SHIFT                                                                   (2U)
#define PM_CAM_PWRSTST_LOGICSTATEST_MASK                                                                    (0x00000004U)
#define PM_CAM_PWRSTST_LOGICSTATEST_ON                                                                       (1U)
#define PM_CAM_PWRSTST_LOGICSTATEST_OFF                                                                      (0U)

#define PM_CAM_PWRSTST_VIP_BANK_STATEST_SHIFT                                                               (4U)
#define PM_CAM_PWRSTST_VIP_BANK_STATEST_MASK                                                                (0x00000030U)
#define PM_CAM_PWRSTST_VIP_BANK_STATEST_MEM_ON                                                               (3U)
#define PM_CAM_PWRSTST_VIP_BANK_STATEST_RESERVED1                                                            (1U)
#define PM_CAM_PWRSTST_VIP_BANK_STATEST_MEM_OFF                                                              (0U)
#define PM_CAM_PWRSTST_VIP_BANK_STATEST_RESERVED                                                             (2U)

#define PM_CAM_PWRSTST_RESERVED_SHIFT                                                                       (3U)
#define PM_CAM_PWRSTST_RESERVED_MASK                                                                        (0x00000008U)

#define PM_CAM_PWRSTST_RESERVED1_SHIFT                                                                      (6U)
#define PM_CAM_PWRSTST_RESERVED1_MASK                                                                       (0x000fffc0U)

#define PM_CAM_PWRSTST_RESERVED2_SHIFT                                                                      (21U)
#define PM_CAM_PWRSTST_RESERVED2_MASK                                                                       (0x00e00000U)

#define PM_CAM_PWRSTST_LASTPOWERSTATEENTERED_SHIFT                                                          (24U)
#define PM_CAM_PWRSTST_LASTPOWERSTATEENTERED_MASK                                                           (0x03000000U)
#define PM_CAM_PWRSTST_LASTPOWERSTATEENTERED_ON                                                              (3U)
#define PM_CAM_PWRSTST_LASTPOWERSTATEENTERED_OFF                                                             (0U)
#define PM_CAM_PWRSTST_LASTPOWERSTATEENTERED_RET                                                             (1U)
#define PM_CAM_PWRSTST_LASTPOWERSTATEENTERED_INACTIVE                                                        (2U)

#define PM_CAM_PWRSTST_RESERVED3_SHIFT                                                                      (26U)
#define PM_CAM_PWRSTST_RESERVED3_MASK                                                                       (0xfc000000U)

#define PM_CAM_VIP1_WKDEP_WKUPDEP_VIP1_MPU_SHIFT                                                            (0U)
#define PM_CAM_VIP1_WKDEP_WKUPDEP_VIP1_MPU_MASK                                                             (0x00000001U)
#define PM_CAM_VIP1_WKDEP_WKUPDEP_VIP1_MPU_ENABLED                                                           (1U)
#define PM_CAM_VIP1_WKDEP_WKUPDEP_VIP1_MPU_DISABLED                                                          (0U)

#define PM_CAM_VIP1_WKDEP_WKUPDEP_VIP1_DSP1_SHIFT                                                           (2U)
#define PM_CAM_VIP1_WKDEP_WKUPDEP_VIP1_DSP1_MASK                                                            (0x00000004U)
#define PM_CAM_VIP1_WKDEP_WKUPDEP_VIP1_DSP1_ENABLED                                                          (1U)
#define PM_CAM_VIP1_WKDEP_WKUPDEP_VIP1_DSP1_DISABLED                                                         (0U)

#define PM_CAM_VIP1_WKDEP_WKUPDEP_VIP1_IPU2_SHIFT                                                           (1U)
#define PM_CAM_VIP1_WKDEP_WKUPDEP_VIP1_IPU2_MASK                                                            (0x00000002U)
#define PM_CAM_VIP1_WKDEP_WKUPDEP_VIP1_IPU2_ENABLED                                                          (1U)
#define PM_CAM_VIP1_WKDEP_WKUPDEP_VIP1_IPU2_DISABLED                                                         (0U)

#define PM_CAM_VIP1_WKDEP_WKUPDEP_VIP1_IPU1_SHIFT                                                           (4U)
#define PM_CAM_VIP1_WKDEP_WKUPDEP_VIP1_IPU1_MASK                                                            (0x00000010U)
#define PM_CAM_VIP1_WKDEP_WKUPDEP_VIP1_IPU1_ENABLED                                                          (1U)
#define PM_CAM_VIP1_WKDEP_WKUPDEP_VIP1_IPU1_DISABLED                                                         (0U)

#define PM_CAM_VIP1_WKDEP_WKUPDEP_VIP1_DSP2_SHIFT                                                           (5U)
#define PM_CAM_VIP1_WKDEP_WKUPDEP_VIP1_DSP2_MASK                                                            (0x00000020U)
#define PM_CAM_VIP1_WKDEP_WKUPDEP_VIP1_DSP2_ENABLED                                                          (1U)
#define PM_CAM_VIP1_WKDEP_WKUPDEP_VIP1_DSP2_DISABLED                                                         (0U)

#define PM_CAM_VIP1_WKDEP_WKUPDEP_VIP1_EVE1_SHIFT                                                           (6U)
#define PM_CAM_VIP1_WKDEP_WKUPDEP_VIP1_EVE1_MASK                                                            (0x00000040U)
#define PM_CAM_VIP1_WKDEP_WKUPDEP_VIP1_EVE1_ENABLED                                                          (1U)
#define PM_CAM_VIP1_WKDEP_WKUPDEP_VIP1_EVE1_DISABLED                                                         (0U)

#define PM_CAM_VIP1_WKDEP_WKUPDEP_VIP1_EVE2_SHIFT                                                           (7U)
#define PM_CAM_VIP1_WKDEP_WKUPDEP_VIP1_EVE2_MASK                                                            (0x00000080U)
#define PM_CAM_VIP1_WKDEP_WKUPDEP_VIP1_EVE2_ENABLED                                                          (1U)
#define PM_CAM_VIP1_WKDEP_WKUPDEP_VIP1_EVE2_DISABLED                                                         (0U)

#define PM_CAM_VIP1_WKDEP_WKUPDEP_VIP1_EVE3_SHIFT                                                           (8U)
#define PM_CAM_VIP1_WKDEP_WKUPDEP_VIP1_EVE3_MASK                                                            (0x00000100U)
#define PM_CAM_VIP1_WKDEP_WKUPDEP_VIP1_EVE3_ENABLED                                                          (1U)
#define PM_CAM_VIP1_WKDEP_WKUPDEP_VIP1_EVE3_DISABLED                                                         (0U)

#define PM_CAM_VIP1_WKDEP_WKUPDEP_VIP1_EVE4_SHIFT                                                           (9U)
#define PM_CAM_VIP1_WKDEP_WKUPDEP_VIP1_EVE4_MASK                                                            (0x00000200U)
#define PM_CAM_VIP1_WKDEP_WKUPDEP_VIP1_EVE4_ENABLED                                                          (1U)
#define PM_CAM_VIP1_WKDEP_WKUPDEP_VIP1_EVE4_DISABLED                                                         (0U)

#define PM_CAM_VIP1_WKDEP_RESERVED_SHIFT                                                                    (10U)
#define PM_CAM_VIP1_WKDEP_RESERVED_MASK                                                                     (0xfffffc00U)

#define PM_CAM_VIP1_WKDEP_RESERVED1_SHIFT                                                                   (3U)
#define PM_CAM_VIP1_WKDEP_RESERVED1_MASK                                                                    (0x00000008U)

#define RM_CAM_VIP1_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                                           (0U)
#define RM_CAM_VIP1_CONTEXT_LOSTCONTEXT_DFF_MASK                                                            (0x00000001U)
#define RM_CAM_VIP1_CONTEXT_LOSTCONTEXT_DFF_LOST                                                             (1U)
#define RM_CAM_VIP1_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                                       (0U)

#define RM_CAM_VIP1_CONTEXT_LOSTMEM_VIP_BANK_SHIFT                                                          (8U)
#define RM_CAM_VIP1_CONTEXT_LOSTMEM_VIP_BANK_MASK                                                           (0x00000100U)
#define RM_CAM_VIP1_CONTEXT_LOSTMEM_VIP_BANK_LOST                                                            (1U)
#define RM_CAM_VIP1_CONTEXT_LOSTMEM_VIP_BANK_MAINTAINED                                                      (0U)

#define RM_CAM_VIP1_CONTEXT_RESERVED1_SHIFT                                                                 (9U)
#define RM_CAM_VIP1_CONTEXT_RESERVED1_MASK                                                                  (0xfffffe00U)

#define RM_CAM_VIP1_CONTEXT_RESERVED_SHIFT                                                                  (1U)
#define RM_CAM_VIP1_CONTEXT_RESERVED_MASK                                                                   (0x000000feU)

#define PM_CAM_VIP2_WKDEP_WKUPDEP_VIP2_MPU_SHIFT                                                            (0U)
#define PM_CAM_VIP2_WKDEP_WKUPDEP_VIP2_MPU_MASK                                                             (0x00000001U)
#define PM_CAM_VIP2_WKDEP_WKUPDEP_VIP2_MPU_ENABLED                                                           (1U)
#define PM_CAM_VIP2_WKDEP_WKUPDEP_VIP2_MPU_DISABLED                                                          (0U)

#define PM_CAM_VIP2_WKDEP_WKUPDEP_VIP2_DSP1_SHIFT                                                           (2U)
#define PM_CAM_VIP2_WKDEP_WKUPDEP_VIP2_DSP1_MASK                                                            (0x00000004U)
#define PM_CAM_VIP2_WKDEP_WKUPDEP_VIP2_DSP1_ENABLED                                                          (1U)
#define PM_CAM_VIP2_WKDEP_WKUPDEP_VIP2_DSP1_DISABLED                                                         (0U)

#define PM_CAM_VIP2_WKDEP_WKUPDEP_VIP2_IPU2_SHIFT                                                           (1U)
#define PM_CAM_VIP2_WKDEP_WKUPDEP_VIP2_IPU2_MASK                                                            (0x00000002U)
#define PM_CAM_VIP2_WKDEP_WKUPDEP_VIP2_IPU2_ENABLED                                                          (1U)
#define PM_CAM_VIP2_WKDEP_WKUPDEP_VIP2_IPU2_DISABLED                                                         (0U)

#define PM_CAM_VIP2_WKDEP_WKUPDEP_VIP2_IPU1_SHIFT                                                           (4U)
#define PM_CAM_VIP2_WKDEP_WKUPDEP_VIP2_IPU1_MASK                                                            (0x00000010U)
#define PM_CAM_VIP2_WKDEP_WKUPDEP_VIP2_IPU1_ENABLED                                                          (1U)
#define PM_CAM_VIP2_WKDEP_WKUPDEP_VIP2_IPU1_DISABLED                                                         (0U)

#define PM_CAM_VIP2_WKDEP_WKUPDEP_VIP2_DSP2_SHIFT                                                           (5U)
#define PM_CAM_VIP2_WKDEP_WKUPDEP_VIP2_DSP2_MASK                                                            (0x00000020U)
#define PM_CAM_VIP2_WKDEP_WKUPDEP_VIP2_DSP2_ENABLED                                                          (1U)
#define PM_CAM_VIP2_WKDEP_WKUPDEP_VIP2_DSP2_DISABLED                                                         (0U)

#define PM_CAM_VIP2_WKDEP_WKUPDEP_VIP2_EVE1_SHIFT                                                           (6U)
#define PM_CAM_VIP2_WKDEP_WKUPDEP_VIP2_EVE1_MASK                                                            (0x00000040U)
#define PM_CAM_VIP2_WKDEP_WKUPDEP_VIP2_EVE1_ENABLED                                                          (1U)
#define PM_CAM_VIP2_WKDEP_WKUPDEP_VIP2_EVE1_DISABLED                                                         (0U)

#define PM_CAM_VIP2_WKDEP_WKUPDEP_VIP2_EVE2_SHIFT                                                           (7U)
#define PM_CAM_VIP2_WKDEP_WKUPDEP_VIP2_EVE2_MASK                                                            (0x00000080U)
#define PM_CAM_VIP2_WKDEP_WKUPDEP_VIP2_EVE2_ENABLED                                                          (1U)
#define PM_CAM_VIP2_WKDEP_WKUPDEP_VIP2_EVE2_DISABLED                                                         (0U)

#define PM_CAM_VIP2_WKDEP_WKUPDEP_VIP2_EVE3_SHIFT                                                           (8U)
#define PM_CAM_VIP2_WKDEP_WKUPDEP_VIP2_EVE3_MASK                                                            (0x00000100U)
#define PM_CAM_VIP2_WKDEP_WKUPDEP_VIP2_EVE3_ENABLED                                                          (1U)
#define PM_CAM_VIP2_WKDEP_WKUPDEP_VIP2_EVE3_DISABLED                                                         (0U)

#define PM_CAM_VIP2_WKDEP_WKUPDEP_VIP2_EVE4_SHIFT                                                           (9U)
#define PM_CAM_VIP2_WKDEP_WKUPDEP_VIP2_EVE4_MASK                                                            (0x00000200U)
#define PM_CAM_VIP2_WKDEP_WKUPDEP_VIP2_EVE4_ENABLED                                                          (1U)
#define PM_CAM_VIP2_WKDEP_WKUPDEP_VIP2_EVE4_DISABLED                                                         (0U)

#define PM_CAM_VIP2_WKDEP_RESERVED_SHIFT                                                                    (10U)
#define PM_CAM_VIP2_WKDEP_RESERVED_MASK                                                                     (0xfffffc00U)

#define PM_CAM_VIP2_WKDEP_RESERVED1_SHIFT                                                                   (3U)
#define PM_CAM_VIP2_WKDEP_RESERVED1_MASK                                                                    (0x00000008U)

#define RM_CAM_VIP2_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                                           (0U)
#define RM_CAM_VIP2_CONTEXT_LOSTCONTEXT_DFF_MASK                                                            (0x00000001U)
#define RM_CAM_VIP2_CONTEXT_LOSTCONTEXT_DFF_LOST                                                             (1U)
#define RM_CAM_VIP2_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                                       (0U)

#define RM_CAM_VIP2_CONTEXT_RESERVED_SHIFT                                                                  (1U)
#define RM_CAM_VIP2_CONTEXT_RESERVED_MASK                                                                   (0x000000feU)

#define RM_CAM_VIP2_CONTEXT_LOSTMEM_VIP_BANK_SHIFT                                                          (8U)
#define RM_CAM_VIP2_CONTEXT_LOSTMEM_VIP_BANK_MASK                                                           (0x00000100U)
#define RM_CAM_VIP2_CONTEXT_LOSTMEM_VIP_BANK_LOST                                                            (1U)
#define RM_CAM_VIP2_CONTEXT_LOSTMEM_VIP_BANK_MAINTAINED                                                      (0U)

#define RM_CAM_VIP2_CONTEXT_RESERVED1_SHIFT                                                                 (9U)
#define RM_CAM_VIP2_CONTEXT_RESERVED1_MASK                                                                  (0xfffffe00U)

#define PM_CAM_VIP3_WKDEP_WKUPDEP_VIP3_MPU_SHIFT                                                            (0U)
#define PM_CAM_VIP3_WKDEP_WKUPDEP_VIP3_MPU_MASK                                                             (0x00000001U)
#define PM_CAM_VIP3_WKDEP_WKUPDEP_VIP3_MPU_ENABLED                                                           (1U)
#define PM_CAM_VIP3_WKDEP_WKUPDEP_VIP3_MPU_DISABLED                                                          (0U)

#define PM_CAM_VIP3_WKDEP_WKUPDEP_VIP3_DSP1_SHIFT                                                           (2U)
#define PM_CAM_VIP3_WKDEP_WKUPDEP_VIP3_DSP1_MASK                                                            (0x00000004U)
#define PM_CAM_VIP3_WKDEP_WKUPDEP_VIP3_DSP1_ENABLED                                                          (1U)
#define PM_CAM_VIP3_WKDEP_WKUPDEP_VIP3_DSP1_DISABLED                                                         (0U)

#define PM_CAM_VIP3_WKDEP_WKUPDEP_VIP3_IPU2_SHIFT                                                           (1U)
#define PM_CAM_VIP3_WKDEP_WKUPDEP_VIP3_IPU2_MASK                                                            (0x00000002U)
#define PM_CAM_VIP3_WKDEP_WKUPDEP_VIP3_IPU2_ENABLED                                                          (1U)
#define PM_CAM_VIP3_WKDEP_WKUPDEP_VIP3_IPU2_DISABLED                                                         (0U)

#define PM_CAM_VIP3_WKDEP_WKUPDEP_VIP3_IPU1_SHIFT                                                           (4U)
#define PM_CAM_VIP3_WKDEP_WKUPDEP_VIP3_IPU1_MASK                                                            (0x00000010U)
#define PM_CAM_VIP3_WKDEP_WKUPDEP_VIP3_IPU1_ENABLED                                                          (1U)
#define PM_CAM_VIP3_WKDEP_WKUPDEP_VIP3_IPU1_DISABLED                                                         (0U)

#define PM_CAM_VIP3_WKDEP_WKUPDEP_VIP3_DSP2_SHIFT                                                           (5U)
#define PM_CAM_VIP3_WKDEP_WKUPDEP_VIP3_DSP2_MASK                                                            (0x00000020U)
#define PM_CAM_VIP3_WKDEP_WKUPDEP_VIP3_DSP2_ENABLED                                                          (1U)
#define PM_CAM_VIP3_WKDEP_WKUPDEP_VIP3_DSP2_DISABLED                                                         (0U)

#define PM_CAM_VIP3_WKDEP_WKUPDEP_VIP3_EVE1_SHIFT                                                           (6U)
#define PM_CAM_VIP3_WKDEP_WKUPDEP_VIP3_EVE1_MASK                                                            (0x00000040U)
#define PM_CAM_VIP3_WKDEP_WKUPDEP_VIP3_EVE1_ENABLED                                                          (1U)
#define PM_CAM_VIP3_WKDEP_WKUPDEP_VIP3_EVE1_DISABLED                                                         (0U)

#define PM_CAM_VIP3_WKDEP_WKUPDEP_VIP3_EVE2_SHIFT                                                           (7U)
#define PM_CAM_VIP3_WKDEP_WKUPDEP_VIP3_EVE2_MASK                                                            (0x00000080U)
#define PM_CAM_VIP3_WKDEP_WKUPDEP_VIP3_EVE2_ENABLED                                                          (1U)
#define PM_CAM_VIP3_WKDEP_WKUPDEP_VIP3_EVE2_DISABLED                                                         (0U)

#define PM_CAM_VIP3_WKDEP_WKUPDEP_VIP3_EVE3_SHIFT                                                           (8U)
#define PM_CAM_VIP3_WKDEP_WKUPDEP_VIP3_EVE3_MASK                                                            (0x00000100U)
#define PM_CAM_VIP3_WKDEP_WKUPDEP_VIP3_EVE3_ENABLED                                                          (1U)
#define PM_CAM_VIP3_WKDEP_WKUPDEP_VIP3_EVE3_DISABLED                                                         (0U)

#define PM_CAM_VIP3_WKDEP_WKUPDEP_VIP3_EVE4_SHIFT                                                           (9U)
#define PM_CAM_VIP3_WKDEP_WKUPDEP_VIP3_EVE4_MASK                                                            (0x00000200U)
#define PM_CAM_VIP3_WKDEP_WKUPDEP_VIP3_EVE4_ENABLED                                                          (1U)
#define PM_CAM_VIP3_WKDEP_WKUPDEP_VIP3_EVE4_DISABLED                                                         (0U)

#define PM_CAM_VIP3_WKDEP_RESERVED_SHIFT                                                                    (10U)
#define PM_CAM_VIP3_WKDEP_RESERVED_MASK                                                                     (0xfffffc00U)

#define PM_CAM_VIP3_WKDEP_RESERVED1_SHIFT                                                                   (3U)
#define PM_CAM_VIP3_WKDEP_RESERVED1_MASK                                                                    (0x00000008U)

#define RM_CAM_VIP3_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                                           (0U)
#define RM_CAM_VIP3_CONTEXT_LOSTCONTEXT_DFF_MASK                                                            (0x00000001U)
#define RM_CAM_VIP3_CONTEXT_LOSTCONTEXT_DFF_LOST                                                             (1U)
#define RM_CAM_VIP3_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                                       (0U)

#define RM_CAM_VIP3_CONTEXT_RESERVED_SHIFT                                                                  (1U)
#define RM_CAM_VIP3_CONTEXT_RESERVED_MASK                                                                   (0x000000feU)

#define RM_CAM_VIP3_CONTEXT_LOSTMEM_VIP_BANK_SHIFT                                                          (8U)
#define RM_CAM_VIP3_CONTEXT_LOSTMEM_VIP_BANK_MASK                                                           (0x00000100U)
#define RM_CAM_VIP3_CONTEXT_LOSTMEM_VIP_BANK_LOST                                                            (1U)
#define RM_CAM_VIP3_CONTEXT_LOSTMEM_VIP_BANK_MAINTAINED                                                      (0U)

#define RM_CAM_VIP3_CONTEXT_RESERVED1_SHIFT                                                                 (9U)
#define RM_CAM_VIP3_CONTEXT_RESERVED1_MASK                                                                  (0xfffffe00U)

#define RM_CAM_LVDSRX_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                                         (0U)
#define RM_CAM_LVDSRX_CONTEXT_LOSTCONTEXT_DFF_MASK                                                          (0x00000001U)
#define RM_CAM_LVDSRX_CONTEXT_LOSTCONTEXT_DFF_LOST                                                           (1U)
#define RM_CAM_LVDSRX_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                                     (0U)

#define RM_CAM_LVDSRX_CONTEXT_RESERVED_SHIFT                                                                (1U)
#define RM_CAM_LVDSRX_CONTEXT_RESERVED_MASK                                                                 (0xfffffffeU)

#define RM_CAM_CSI1_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                                           (0U)
#define RM_CAM_CSI1_CONTEXT_LOSTCONTEXT_DFF_MASK                                                            (0x00000001U)
#define RM_CAM_CSI1_CONTEXT_LOSTCONTEXT_DFF_LOST                                                             (1U)
#define RM_CAM_CSI1_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                                       (0U)

#define RM_CAM_CSI1_CONTEXT_RESERVED_SHIFT                                                                  (1U)
#define RM_CAM_CSI1_CONTEXT_RESERVED_MASK                                                                   (0xfffffffeU)

#define RM_CAM_CSI2_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                                           (0U)
#define RM_CAM_CSI2_CONTEXT_LOSTCONTEXT_DFF_MASK                                                            (0x00000001U)
#define RM_CAM_CSI2_CONTEXT_LOSTCONTEXT_DFF_LOST                                                             (1U)
#define RM_CAM_CSI2_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                                       (0U)

#define RM_CAM_CSI2_CONTEXT_RESERVED_SHIFT                                                                  (1U)
#define RM_CAM_CSI2_CONTEXT_RESERVED_MASK                                                                   (0xfffffffeU)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_CAM_PRM_H_ */
