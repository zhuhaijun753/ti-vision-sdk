/******************************************************************************
*
* hw_wkupaon_prm.h - register-level header file for PRCM
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
#ifndef HW_WKUPAON_PRM_H_
#define HW_WKUPAON_PRM_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions 
****************************************************************************************************/
#define RM_WKUPAON_L4_WKUP_CONTEXT                                                                          (0x0U)
#define PM_WKUPAON_WD_TIMER1_WKDEP                                                                          (0x4U)
#define RM_WKUPAON_WD_TIMER1_CONTEXT                                                                        (0x8U)
#define PM_WKUPAON_WD_TIMER2_WKDEP                                                                          (0xcU)
#define RM_WKUPAON_WD_TIMER2_CONTEXT                                                                        (0x10U)
#define PM_WKUPAON_GPIO1_WKDEP                                                                              (0x14U)
#define RM_WKUPAON_GPIO1_CONTEXT                                                                            (0x18U)
#define PM_WKUPAON_TIMER1_WKDEP                                                                             (0x1cU)
#define RM_WKUPAON_TIMER1_CONTEXT                                                                           (0x20U)
#define PM_WKUPAON_TIMER12_WKDEP                                                                            (0x24U)
#define RM_WKUPAON_TIMER12_CONTEXT                                                                          (0x28U)
#define RM_WKUPAON_COUNTER_32K_CONTEXT                                                                      (0x30U)
#define PM_WKUPAON_KBD_WKDEP                                                                                (0x54U)
#define RM_WKUPAON_KBD_CONTEXT                                                                              (0x58U)
#define PM_WKUPAON_UART10_WKDEP                                                                             (0x5cU)
#define RM_WKUPAON_UART10_CONTEXT                                                                           (0x60U)
#define PM_WKUPAON_DCAN1_WKDEP                                                                              (0x64U)
#define RM_WKUPAON_DCAN1_CONTEXT                                                                            (0x68U)

/****************************************************************************************************
* Field Definition Macros 
****************************************************************************************************/

#define RM_WKUPAON_L4_WKUP_CONTEXT_RESERVED_SHIFT                                                           (1U)
#define RM_WKUPAON_L4_WKUP_CONTEXT_RESERVED_MASK                                                            (0xfffffffeU)

#define RM_WKUPAON_L4_WKUP_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                                    (0U)
#define RM_WKUPAON_L4_WKUP_CONTEXT_LOSTCONTEXT_DFF_MASK                                                     (0x00000001U)
#define RM_WKUPAON_L4_WKUP_CONTEXT_LOSTCONTEXT_DFF_LOST                                                      (1U)
#define RM_WKUPAON_L4_WKUP_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                                (0U)

#define PM_WKUPAON_WD_TIMER1_WKDEP_WKUPDEP_WD_TIMER1_MPU_SHIFT                                              (0U)
#define PM_WKUPAON_WD_TIMER1_WKDEP_WKUPDEP_WD_TIMER1_MPU_MASK                                               (0x00000001U)
#define PM_WKUPAON_WD_TIMER1_WKDEP_WKUPDEP_WD_TIMER1_MPU_ENABLED                                             (1U)
#define PM_WKUPAON_WD_TIMER1_WKDEP_WKUPDEP_WD_TIMER1_MPU_DISABLED                                            (0U)

#define PM_WKUPAON_WD_TIMER1_WKDEP_WKUPDEP_WD_TIMER1_IPU2_SHIFT                                             (1U)
#define PM_WKUPAON_WD_TIMER1_WKDEP_WKUPDEP_WD_TIMER1_IPU2_MASK                                              (0x00000002U)
#define PM_WKUPAON_WD_TIMER1_WKDEP_WKUPDEP_WD_TIMER1_IPU2_ENABLED                                            (1U)
#define PM_WKUPAON_WD_TIMER1_WKDEP_WKUPDEP_WD_TIMER1_IPU2_DISABLED                                           (0U)

#define PM_WKUPAON_WD_TIMER1_WKDEP_WKUPDEP_WD_TIMER1_DSP1_SHIFT                                             (2U)
#define PM_WKUPAON_WD_TIMER1_WKDEP_WKUPDEP_WD_TIMER1_DSP1_MASK                                              (0x00000004U)
#define PM_WKUPAON_WD_TIMER1_WKDEP_WKUPDEP_WD_TIMER1_DSP1_ENABLED                                            (1U)
#define PM_WKUPAON_WD_TIMER1_WKDEP_WKUPDEP_WD_TIMER1_DSP1_DISABLED                                           (0U)

#define PM_WKUPAON_WD_TIMER1_WKDEP_RESERVED_SHIFT                                                           (3U)
#define PM_WKUPAON_WD_TIMER1_WKDEP_RESERVED_MASK                                                            (0x00000008U)

#define PM_WKUPAON_WD_TIMER1_WKDEP_WKUPDEP_WD_TIMER1_IPU1_SHIFT                                             (4U)
#define PM_WKUPAON_WD_TIMER1_WKDEP_WKUPDEP_WD_TIMER1_IPU1_MASK                                              (0x00000010U)
#define PM_WKUPAON_WD_TIMER1_WKDEP_WKUPDEP_WD_TIMER1_IPU1_ENABLED                                            (1U)
#define PM_WKUPAON_WD_TIMER1_WKDEP_WKUPDEP_WD_TIMER1_IPU1_DISABLED                                           (0U)

#define PM_WKUPAON_WD_TIMER1_WKDEP_WKUPDEP_WD_TIMER1_DSP2_SHIFT                                             (5U)
#define PM_WKUPAON_WD_TIMER1_WKDEP_WKUPDEP_WD_TIMER1_DSP2_MASK                                              (0x00000020U)
#define PM_WKUPAON_WD_TIMER1_WKDEP_WKUPDEP_WD_TIMER1_DSP2_ENABLED                                            (1U)
#define PM_WKUPAON_WD_TIMER1_WKDEP_WKUPDEP_WD_TIMER1_DSP2_DISABLED                                           (0U)

#define PM_WKUPAON_WD_TIMER1_WKDEP_WKUPDEP_WD_TIMER1_EVE1_SHIFT                                             (6U)
#define PM_WKUPAON_WD_TIMER1_WKDEP_WKUPDEP_WD_TIMER1_EVE1_MASK                                              (0x00000040U)
#define PM_WKUPAON_WD_TIMER1_WKDEP_WKUPDEP_WD_TIMER1_EVE1_ENABLED                                            (1U)
#define PM_WKUPAON_WD_TIMER1_WKDEP_WKUPDEP_WD_TIMER1_EVE1_DISABLED                                           (0U)

#define PM_WKUPAON_WD_TIMER1_WKDEP_WKUPDEP_WD_TIMER1_EVE2_SHIFT                                             (7U)
#define PM_WKUPAON_WD_TIMER1_WKDEP_WKUPDEP_WD_TIMER1_EVE2_MASK                                              (0x00000080U)
#define PM_WKUPAON_WD_TIMER1_WKDEP_WKUPDEP_WD_TIMER1_EVE2_ENABLED                                            (1U)
#define PM_WKUPAON_WD_TIMER1_WKDEP_WKUPDEP_WD_TIMER1_EVE2_DISABLED                                           (0U)

#define PM_WKUPAON_WD_TIMER1_WKDEP_WKUPDEP_WD_TIMER1_EVE3_SHIFT                                             (8U)
#define PM_WKUPAON_WD_TIMER1_WKDEP_WKUPDEP_WD_TIMER1_EVE3_MASK                                              (0x00000100U)
#define PM_WKUPAON_WD_TIMER1_WKDEP_WKUPDEP_WD_TIMER1_EVE3_ENABLED                                            (1U)
#define PM_WKUPAON_WD_TIMER1_WKDEP_WKUPDEP_WD_TIMER1_EVE3_DISABLED                                           (0U)

#define PM_WKUPAON_WD_TIMER1_WKDEP_WKUPDEP_WD_TIMER1_EVE4_SHIFT                                             (9U)
#define PM_WKUPAON_WD_TIMER1_WKDEP_WKUPDEP_WD_TIMER1_EVE4_MASK                                              (0x00000200U)
#define PM_WKUPAON_WD_TIMER1_WKDEP_WKUPDEP_WD_TIMER1_EVE4_ENABLED                                            (1U)
#define PM_WKUPAON_WD_TIMER1_WKDEP_WKUPDEP_WD_TIMER1_EVE4_DISABLED                                           (0U)

#define PM_WKUPAON_WD_TIMER1_WKDEP_RESERVED1_SHIFT                                                          (10U)
#define PM_WKUPAON_WD_TIMER1_WKDEP_RESERVED1_MASK                                                           (0xfffffc00U)

#define RM_WKUPAON_WD_TIMER1_CONTEXT_RESERVED_SHIFT                                                         (1U)
#define RM_WKUPAON_WD_TIMER1_CONTEXT_RESERVED_MASK                                                          (0xfffffffeU)

#define RM_WKUPAON_WD_TIMER1_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                                  (0U)
#define RM_WKUPAON_WD_TIMER1_CONTEXT_LOSTCONTEXT_DFF_MASK                                                   (0x00000001U)
#define RM_WKUPAON_WD_TIMER1_CONTEXT_LOSTCONTEXT_DFF_LOST                                                    (1U)
#define RM_WKUPAON_WD_TIMER1_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                              (0U)

#define PM_WKUPAON_WD_TIMER2_WKDEP_WKUPDEP_WD_TIMER2_MPU_SHIFT                                              (0U)
#define PM_WKUPAON_WD_TIMER2_WKDEP_WKUPDEP_WD_TIMER2_MPU_MASK                                               (0x00000001U)
#define PM_WKUPAON_WD_TIMER2_WKDEP_WKUPDEP_WD_TIMER2_MPU_ENABLED                                             (1U)
#define PM_WKUPAON_WD_TIMER2_WKDEP_WKUPDEP_WD_TIMER2_MPU_DISABLED                                            (0U)

#define PM_WKUPAON_WD_TIMER2_WKDEP_WKUPDEP_WD_TIMER2_IPU2_SHIFT                                             (1U)
#define PM_WKUPAON_WD_TIMER2_WKDEP_WKUPDEP_WD_TIMER2_IPU2_MASK                                              (0x00000002U)
#define PM_WKUPAON_WD_TIMER2_WKDEP_WKUPDEP_WD_TIMER2_IPU2_ENABLED                                            (1U)
#define PM_WKUPAON_WD_TIMER2_WKDEP_WKUPDEP_WD_TIMER2_IPU2_DISABLED                                           (0U)

#define PM_WKUPAON_WD_TIMER2_WKDEP_WKUPDEP_WD_TIMER2_DSP1_SHIFT                                             (2U)
#define PM_WKUPAON_WD_TIMER2_WKDEP_WKUPDEP_WD_TIMER2_DSP1_MASK                                              (0x00000004U)
#define PM_WKUPAON_WD_TIMER2_WKDEP_WKUPDEP_WD_TIMER2_DSP1_ENABLED                                            (1U)
#define PM_WKUPAON_WD_TIMER2_WKDEP_WKUPDEP_WD_TIMER2_DSP1_DISABLED                                           (0U)

#define PM_WKUPAON_WD_TIMER2_WKDEP_RESERVED_SHIFT                                                           (3U)
#define PM_WKUPAON_WD_TIMER2_WKDEP_RESERVED_MASK                                                            (0x00000008U)

#define PM_WKUPAON_WD_TIMER2_WKDEP_WKUPDEP_WD_TIMER2_IPU1_SHIFT                                             (4U)
#define PM_WKUPAON_WD_TIMER2_WKDEP_WKUPDEP_WD_TIMER2_IPU1_MASK                                              (0x00000010U)
#define PM_WKUPAON_WD_TIMER2_WKDEP_WKUPDEP_WD_TIMER2_IPU1_ENABLED                                            (1U)
#define PM_WKUPAON_WD_TIMER2_WKDEP_WKUPDEP_WD_TIMER2_IPU1_DISABLED                                           (0U)

#define PM_WKUPAON_WD_TIMER2_WKDEP_WKUPDEP_WD_TIMER2_DSP2_SHIFT                                             (5U)
#define PM_WKUPAON_WD_TIMER2_WKDEP_WKUPDEP_WD_TIMER2_DSP2_MASK                                              (0x00000020U)
#define PM_WKUPAON_WD_TIMER2_WKDEP_WKUPDEP_WD_TIMER2_DSP2_ENABLED                                            (1U)
#define PM_WKUPAON_WD_TIMER2_WKDEP_WKUPDEP_WD_TIMER2_DSP2_DISABLED                                           (0U)

#define PM_WKUPAON_WD_TIMER2_WKDEP_WKUPDEP_WD_TIMER2_EVE1_SHIFT                                             (6U)
#define PM_WKUPAON_WD_TIMER2_WKDEP_WKUPDEP_WD_TIMER2_EVE1_MASK                                              (0x00000040U)
#define PM_WKUPAON_WD_TIMER2_WKDEP_WKUPDEP_WD_TIMER2_EVE1_ENABLED                                            (1U)
#define PM_WKUPAON_WD_TIMER2_WKDEP_WKUPDEP_WD_TIMER2_EVE1_DISABLED                                           (0U)

#define PM_WKUPAON_WD_TIMER2_WKDEP_WKUPDEP_WD_TIMER2_EVE2_SHIFT                                             (7U)
#define PM_WKUPAON_WD_TIMER2_WKDEP_WKUPDEP_WD_TIMER2_EVE2_MASK                                              (0x00000080U)
#define PM_WKUPAON_WD_TIMER2_WKDEP_WKUPDEP_WD_TIMER2_EVE2_ENABLED                                            (1U)
#define PM_WKUPAON_WD_TIMER2_WKDEP_WKUPDEP_WD_TIMER2_EVE2_DISABLED                                           (0U)

#define PM_WKUPAON_WD_TIMER2_WKDEP_WKUPDEP_WD_TIMER2_EVE3_SHIFT                                             (8U)
#define PM_WKUPAON_WD_TIMER2_WKDEP_WKUPDEP_WD_TIMER2_EVE3_MASK                                              (0x00000100U)
#define PM_WKUPAON_WD_TIMER2_WKDEP_WKUPDEP_WD_TIMER2_EVE3_ENABLED                                            (1U)
#define PM_WKUPAON_WD_TIMER2_WKDEP_WKUPDEP_WD_TIMER2_EVE3_DISABLED                                           (0U)

#define PM_WKUPAON_WD_TIMER2_WKDEP_WKUPDEP_WD_TIMER2_EVE4_SHIFT                                             (9U)
#define PM_WKUPAON_WD_TIMER2_WKDEP_WKUPDEP_WD_TIMER2_EVE4_MASK                                              (0x00000200U)
#define PM_WKUPAON_WD_TIMER2_WKDEP_WKUPDEP_WD_TIMER2_EVE4_ENABLED                                            (1U)
#define PM_WKUPAON_WD_TIMER2_WKDEP_WKUPDEP_WD_TIMER2_EVE4_DISABLED                                           (0U)

#define PM_WKUPAON_WD_TIMER2_WKDEP_RESERVED1_SHIFT                                                          (10U)
#define PM_WKUPAON_WD_TIMER2_WKDEP_RESERVED1_MASK                                                           (0xfffffc00U)

#define RM_WKUPAON_WD_TIMER2_CONTEXT_RESERVED_SHIFT                                                         (1U)
#define RM_WKUPAON_WD_TIMER2_CONTEXT_RESERVED_MASK                                                          (0xfffffffeU)

#define RM_WKUPAON_WD_TIMER2_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                                  (0U)
#define RM_WKUPAON_WD_TIMER2_CONTEXT_LOSTCONTEXT_DFF_MASK                                                   (0x00000001U)
#define RM_WKUPAON_WD_TIMER2_CONTEXT_LOSTCONTEXT_DFF_LOST                                                    (1U)
#define RM_WKUPAON_WD_TIMER2_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                              (0U)

#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ1_MPU_SHIFT                                                 (0U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ1_MPU_MASK                                                  (0x00000001U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ1_MPU_ENABLED                                                (1U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ1_MPU_DISABLED                                               (0U)

#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ1_IPU2_SHIFT                                                (1U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ1_IPU2_MASK                                                 (0x00000002U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ1_IPU2_ENABLED                                               (1U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ1_IPU2_DISABLED                                              (0U)

#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ1_DSP1_SHIFT                                                (2U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ1_DSP1_MASK                                                 (0x00000004U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ1_DSP1_ENABLED                                               (1U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ1_DSP1_DISABLED                                              (0U)

#define PM_WKUPAON_GPIO1_WKDEP_RESERVED_SHIFT                                                               (3U)
#define PM_WKUPAON_GPIO1_WKDEP_RESERVED_MASK                                                                (0x00000008U)

#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ1_IPU1_SHIFT                                                (4U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ1_IPU1_MASK                                                 (0x00000010U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ1_IPU1_ENABLED                                               (1U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ1_IPU1_DISABLED                                              (0U)

#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ1_DSP2_SHIFT                                                (5U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ1_DSP2_MASK                                                 (0x00000020U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ1_DSP2_ENABLED                                               (1U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ1_DSP2_DISABLED                                              (0U)

#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ1_EVE1_SHIFT                                                (6U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ1_EVE1_MASK                                                 (0x00000040U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ1_EVE1_ENABLED                                               (1U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ1_EVE1_DISABLED                                              (0U)

#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ1_EVE2_SHIFT                                                (7U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ1_EVE2_MASK                                                 (0x00000080U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ1_EVE2_ENABLED                                               (1U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ1_EVE2_DISABLED                                              (0U)

#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ1_EVE3_SHIFT                                                (8U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ1_EVE3_MASK                                                 (0x00000100U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ1_EVE3_ENABLED                                               (1U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ1_EVE3_DISABLED                                              (0U)

#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ1_EVE4_SHIFT                                                (9U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ1_EVE4_MASK                                                 (0x00000200U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ1_EVE4_ENABLED                                               (1U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ1_EVE4_DISABLED                                              (0U)

#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ2_MPU_SHIFT                                                 (10U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ2_MPU_MASK                                                  (0x00000400U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ2_MPU_ENABLED                                                (1U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ2_MPU_DISABLED                                               (0U)

#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ2_IPU2_SHIFT                                                (11U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ2_IPU2_MASK                                                 (0x00000800U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ2_IPU2_ENABLED                                               (1U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ2_IPU2_DISABLED                                              (0U)

#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ2_DSP1_SHIFT                                                (12U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ2_DSP1_MASK                                                 (0x00001000U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ2_DSP1_ENABLED                                               (1U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ2_DSP1_DISABLED                                              (0U)

#define PM_WKUPAON_GPIO1_WKDEP_RESERVED1_SHIFT                                                              (13U)
#define PM_WKUPAON_GPIO1_WKDEP_RESERVED1_MASK                                                               (0x00002000U)

#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ2_IPU1_SHIFT                                                (14U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ2_IPU1_MASK                                                 (0x00004000U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ2_IPU1_ENABLED                                               (1U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ2_IPU1_DISABLED                                              (0U)

#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ2_DSP2_SHIFT                                                (15U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ2_DSP2_MASK                                                 (0x00008000U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ2_DSP2_ENABLED                                               (1U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ2_DSP2_DISABLED                                              (0U)

#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ2_EVE1_SHIFT                                                (16U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ2_EVE1_MASK                                                 (0x00010000U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ2_EVE1_ENABLED                                               (1U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ2_EVE1_DISABLED                                              (0U)

#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ2_EVE2_SHIFT                                                (17U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ2_EVE2_MASK                                                 (0x00020000U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ2_EVE2_ENABLED                                               (1U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ2_EVE2_DISABLED                                              (0U)

#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ2_EVE3_SHIFT                                                (18U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ2_EVE3_MASK                                                 (0x00040000U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ2_EVE3_ENABLED                                               (1U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ2_EVE3_DISABLED                                              (0U)

#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ2_EVE4_SHIFT                                                (19U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ2_EVE4_MASK                                                 (0x00080000U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ2_EVE4_ENABLED                                               (1U)
#define PM_WKUPAON_GPIO1_WKDEP_WKUPDEP_GPIO1_IRQ2_EVE4_DISABLED                                              (0U)

#define PM_WKUPAON_GPIO1_WKDEP_RESERVED2_SHIFT                                                              (20U)
#define PM_WKUPAON_GPIO1_WKDEP_RESERVED2_MASK                                                               (0xfff00000U)

#define RM_WKUPAON_GPIO1_CONTEXT_RESERVED_SHIFT                                                             (1U)
#define RM_WKUPAON_GPIO1_CONTEXT_RESERVED_MASK                                                              (0xfffffffeU)

#define RM_WKUPAON_GPIO1_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                                      (0U)
#define RM_WKUPAON_GPIO1_CONTEXT_LOSTCONTEXT_DFF_MASK                                                       (0x00000001U)
#define RM_WKUPAON_GPIO1_CONTEXT_LOSTCONTEXT_DFF_LOST                                                        (1U)
#define RM_WKUPAON_GPIO1_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                                  (0U)

#define PM_WKUPAON_TIMER1_WKDEP_WKUPDEP_TIMER1_MPU_SHIFT                                                    (0U)
#define PM_WKUPAON_TIMER1_WKDEP_WKUPDEP_TIMER1_MPU_MASK                                                     (0x00000001U)
#define PM_WKUPAON_TIMER1_WKDEP_WKUPDEP_TIMER1_MPU_ENABLED                                                   (1U)
#define PM_WKUPAON_TIMER1_WKDEP_WKUPDEP_TIMER1_MPU_DISABLED                                                  (0U)

#define PM_WKUPAON_TIMER1_WKDEP_WKUPDEP_TIMER1_IPU2_SHIFT                                                   (1U)
#define PM_WKUPAON_TIMER1_WKDEP_WKUPDEP_TIMER1_IPU2_MASK                                                    (0x00000002U)
#define PM_WKUPAON_TIMER1_WKDEP_WKUPDEP_TIMER1_IPU2_ENABLED                                                  (1U)
#define PM_WKUPAON_TIMER1_WKDEP_WKUPDEP_TIMER1_IPU2_DISABLED                                                 (0U)

#define PM_WKUPAON_TIMER1_WKDEP_WKUPDEP_TIMER1_DSP1_SHIFT                                                   (2U)
#define PM_WKUPAON_TIMER1_WKDEP_WKUPDEP_TIMER1_DSP1_MASK                                                    (0x00000004U)
#define PM_WKUPAON_TIMER1_WKDEP_WKUPDEP_TIMER1_DSP1_ENABLED                                                  (1U)
#define PM_WKUPAON_TIMER1_WKDEP_WKUPDEP_TIMER1_DSP1_DISABLED                                                 (0U)

#define PM_WKUPAON_TIMER1_WKDEP_RESERVED_SHIFT                                                              (3U)
#define PM_WKUPAON_TIMER1_WKDEP_RESERVED_MASK                                                               (0x00000008U)

#define PM_WKUPAON_TIMER1_WKDEP_WKUPDEP_TIMER1_IPU1_SHIFT                                                   (4U)
#define PM_WKUPAON_TIMER1_WKDEP_WKUPDEP_TIMER1_IPU1_MASK                                                    (0x00000010U)
#define PM_WKUPAON_TIMER1_WKDEP_WKUPDEP_TIMER1_IPU1_ENABLED                                                  (1U)
#define PM_WKUPAON_TIMER1_WKDEP_WKUPDEP_TIMER1_IPU1_DISABLED                                                 (0U)

#define PM_WKUPAON_TIMER1_WKDEP_WKUPDEP_TIMER1_DSP2_SHIFT                                                   (5U)
#define PM_WKUPAON_TIMER1_WKDEP_WKUPDEP_TIMER1_DSP2_MASK                                                    (0x00000020U)
#define PM_WKUPAON_TIMER1_WKDEP_WKUPDEP_TIMER1_DSP2_ENABLED                                                  (1U)
#define PM_WKUPAON_TIMER1_WKDEP_WKUPDEP_TIMER1_DSP2_DISABLED                                                 (0U)

#define PM_WKUPAON_TIMER1_WKDEP_WKUPDEP_TIMER1_EVE1_SHIFT                                                   (6U)
#define PM_WKUPAON_TIMER1_WKDEP_WKUPDEP_TIMER1_EVE1_MASK                                                    (0x00000040U)
#define PM_WKUPAON_TIMER1_WKDEP_WKUPDEP_TIMER1_EVE1_ENABLED                                                  (1U)
#define PM_WKUPAON_TIMER1_WKDEP_WKUPDEP_TIMER1_EVE1_DISABLED                                                 (0U)

#define PM_WKUPAON_TIMER1_WKDEP_WKUPDEP_TIMER1_EVE2_SHIFT                                                   (7U)
#define PM_WKUPAON_TIMER1_WKDEP_WKUPDEP_TIMER1_EVE2_MASK                                                    (0x00000080U)
#define PM_WKUPAON_TIMER1_WKDEP_WKUPDEP_TIMER1_EVE2_ENABLED                                                  (1U)
#define PM_WKUPAON_TIMER1_WKDEP_WKUPDEP_TIMER1_EVE2_DISABLED                                                 (0U)

#define PM_WKUPAON_TIMER1_WKDEP_WKUPDEP_TIMER1_EVE3_SHIFT                                                   (8U)
#define PM_WKUPAON_TIMER1_WKDEP_WKUPDEP_TIMER1_EVE3_MASK                                                    (0x00000100U)
#define PM_WKUPAON_TIMER1_WKDEP_WKUPDEP_TIMER1_EVE3_ENABLED                                                  (1U)
#define PM_WKUPAON_TIMER1_WKDEP_WKUPDEP_TIMER1_EVE3_DISABLED                                                 (0U)

#define PM_WKUPAON_TIMER1_WKDEP_WKUPDEP_TIMER1_EVE4_SHIFT                                                   (9U)
#define PM_WKUPAON_TIMER1_WKDEP_WKUPDEP_TIMER1_EVE4_MASK                                                    (0x00000200U)
#define PM_WKUPAON_TIMER1_WKDEP_WKUPDEP_TIMER1_EVE4_ENABLED                                                  (1U)
#define PM_WKUPAON_TIMER1_WKDEP_WKUPDEP_TIMER1_EVE4_DISABLED                                                 (0U)

#define PM_WKUPAON_TIMER1_WKDEP_RESERVED1_SHIFT                                                             (10U)
#define PM_WKUPAON_TIMER1_WKDEP_RESERVED1_MASK                                                              (0xfffffc00U)

#define RM_WKUPAON_TIMER1_CONTEXT_RESERVED_SHIFT                                                            (1U)
#define RM_WKUPAON_TIMER1_CONTEXT_RESERVED_MASK                                                             (0xfffffffeU)

#define RM_WKUPAON_TIMER1_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                                     (0U)
#define RM_WKUPAON_TIMER1_CONTEXT_LOSTCONTEXT_DFF_MASK                                                      (0x00000001U)
#define RM_WKUPAON_TIMER1_CONTEXT_LOSTCONTEXT_DFF_LOST                                                       (1U)
#define RM_WKUPAON_TIMER1_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                                 (0U)

#define PM_WKUPAON_TIMER12_WKDEP_WKUPDEP_TIMER12_MPU_SHIFT                                                  (0U)
#define PM_WKUPAON_TIMER12_WKDEP_WKUPDEP_TIMER12_MPU_MASK                                                   (0x00000001U)
#define PM_WKUPAON_TIMER12_WKDEP_WKUPDEP_TIMER12_MPU_ENABLED                                                 (1U)
#define PM_WKUPAON_TIMER12_WKDEP_WKUPDEP_TIMER12_MPU_DISABLED                                                (0U)

#define PM_WKUPAON_TIMER12_WKDEP_WKUPDEP_TIMER12_IPU2_SHIFT                                                 (1U)
#define PM_WKUPAON_TIMER12_WKDEP_WKUPDEP_TIMER12_IPU2_MASK                                                  (0x00000002U)
#define PM_WKUPAON_TIMER12_WKDEP_WKUPDEP_TIMER12_IPU2_ENABLED                                                (1U)
#define PM_WKUPAON_TIMER12_WKDEP_WKUPDEP_TIMER12_IPU2_DISABLED                                               (0U)

#define PM_WKUPAON_TIMER12_WKDEP_WKUPDEP_TIMER12_DSP1_SHIFT                                                 (2U)
#define PM_WKUPAON_TIMER12_WKDEP_WKUPDEP_TIMER12_DSP1_MASK                                                  (0x00000004U)
#define PM_WKUPAON_TIMER12_WKDEP_WKUPDEP_TIMER12_DSP1_ENABLED                                                (1U)
#define PM_WKUPAON_TIMER12_WKDEP_WKUPDEP_TIMER12_DSP1_DISABLED                                               (0U)

#define PM_WKUPAON_TIMER12_WKDEP_RESERVED_SHIFT                                                             (3U)
#define PM_WKUPAON_TIMER12_WKDEP_RESERVED_MASK                                                              (0x00000008U)

#define PM_WKUPAON_TIMER12_WKDEP_WKUPDEP_TIMER12_IPU1_SHIFT                                                 (4U)
#define PM_WKUPAON_TIMER12_WKDEP_WKUPDEP_TIMER12_IPU1_MASK                                                  (0x00000010U)
#define PM_WKUPAON_TIMER12_WKDEP_WKUPDEP_TIMER12_IPU1_ENABLED                                                (1U)
#define PM_WKUPAON_TIMER12_WKDEP_WKUPDEP_TIMER12_IPU1_DISABLED                                               (0U)

#define PM_WKUPAON_TIMER12_WKDEP_WKUPDEP_TIMER12_DSP2_SHIFT                                                 (5U)
#define PM_WKUPAON_TIMER12_WKDEP_WKUPDEP_TIMER12_DSP2_MASK                                                  (0x00000020U)
#define PM_WKUPAON_TIMER12_WKDEP_WKUPDEP_TIMER12_DSP2_ENABLED                                                (1U)
#define PM_WKUPAON_TIMER12_WKDEP_WKUPDEP_TIMER12_DSP2_DISABLED                                               (0U)

#define PM_WKUPAON_TIMER12_WKDEP_WKUPDEP_TIMER12_EVE1_SHIFT                                                 (6U)
#define PM_WKUPAON_TIMER12_WKDEP_WKUPDEP_TIMER12_EVE1_MASK                                                  (0x00000040U)
#define PM_WKUPAON_TIMER12_WKDEP_WKUPDEP_TIMER12_EVE1_ENABLED                                                (1U)
#define PM_WKUPAON_TIMER12_WKDEP_WKUPDEP_TIMER12_EVE1_DISABLED                                               (0U)

#define PM_WKUPAON_TIMER12_WKDEP_WKUPDEP_TIMER12_EVE2_SHIFT                                                 (7U)
#define PM_WKUPAON_TIMER12_WKDEP_WKUPDEP_TIMER12_EVE2_MASK                                                  (0x00000080U)
#define PM_WKUPAON_TIMER12_WKDEP_WKUPDEP_TIMER12_EVE2_ENABLED                                                (1U)
#define PM_WKUPAON_TIMER12_WKDEP_WKUPDEP_TIMER12_EVE2_DISABLED                                               (0U)

#define PM_WKUPAON_TIMER12_WKDEP_WKUPDEP_TIMER12_EVE3_SHIFT                                                 (8U)
#define PM_WKUPAON_TIMER12_WKDEP_WKUPDEP_TIMER12_EVE3_MASK                                                  (0x00000100U)
#define PM_WKUPAON_TIMER12_WKDEP_WKUPDEP_TIMER12_EVE3_ENABLED                                                (1U)
#define PM_WKUPAON_TIMER12_WKDEP_WKUPDEP_TIMER12_EVE3_DISABLED                                               (0U)

#define PM_WKUPAON_TIMER12_WKDEP_WKUPDEP_TIMER12_EVE4_SHIFT                                                 (9U)
#define PM_WKUPAON_TIMER12_WKDEP_WKUPDEP_TIMER12_EVE4_MASK                                                  (0x00000200U)
#define PM_WKUPAON_TIMER12_WKDEP_WKUPDEP_TIMER12_EVE4_ENABLED                                                (1U)
#define PM_WKUPAON_TIMER12_WKDEP_WKUPDEP_TIMER12_EVE4_DISABLED                                               (0U)

#define PM_WKUPAON_TIMER12_WKDEP_RESERVED1_SHIFT                                                            (10U)
#define PM_WKUPAON_TIMER12_WKDEP_RESERVED1_MASK                                                             (0xfffffc00U)

#define RM_WKUPAON_TIMER12_CONTEXT_RESERVED_SHIFT                                                           (1U)
#define RM_WKUPAON_TIMER12_CONTEXT_RESERVED_MASK                                                            (0xfffffffeU)

#define RM_WKUPAON_TIMER12_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                                    (0U)
#define RM_WKUPAON_TIMER12_CONTEXT_LOSTCONTEXT_DFF_MASK                                                     (0x00000001U)
#define RM_WKUPAON_TIMER12_CONTEXT_LOSTCONTEXT_DFF_LOST                                                      (1U)
#define RM_WKUPAON_TIMER12_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                                (0U)

#define RM_WKUPAON_COUNTER_32K_CONTEXT_RESERVED_SHIFT                                                       (1U)
#define RM_WKUPAON_COUNTER_32K_CONTEXT_RESERVED_MASK                                                        (0xfffffffeU)

#define RM_WKUPAON_COUNTER_32K_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                                (0U)
#define RM_WKUPAON_COUNTER_32K_CONTEXT_LOSTCONTEXT_DFF_MASK                                                 (0x00000001U)
#define RM_WKUPAON_COUNTER_32K_CONTEXT_LOSTCONTEXT_DFF_LOST                                                  (1U)
#define RM_WKUPAON_COUNTER_32K_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                            (0U)

#define PM_WKUPAON_KBD_WKDEP_WKUPDEP_KBD_MPU_SHIFT                                                          (0U)
#define PM_WKUPAON_KBD_WKDEP_WKUPDEP_KBD_MPU_MASK                                                           (0x00000001U)
#define PM_WKUPAON_KBD_WKDEP_WKUPDEP_KBD_MPU_ENABLED                                                         (1U)
#define PM_WKUPAON_KBD_WKDEP_WKUPDEP_KBD_MPU_DISABLED                                                        (0U)

#define PM_WKUPAON_KBD_WKDEP_WKUPDEP_KBD_IPU2_SHIFT                                                         (1U)
#define PM_WKUPAON_KBD_WKDEP_WKUPDEP_KBD_IPU2_MASK                                                          (0x00000002U)
#define PM_WKUPAON_KBD_WKDEP_WKUPDEP_KBD_IPU2_ENABLED                                                        (1U)
#define PM_WKUPAON_KBD_WKDEP_WKUPDEP_KBD_IPU2_DISABLED                                                       (0U)

#define PM_WKUPAON_KBD_WKDEP_WKUPDEP_KBD_DSP1_SHIFT                                                         (2U)
#define PM_WKUPAON_KBD_WKDEP_WKUPDEP_KBD_DSP1_MASK                                                          (0x00000004U)
#define PM_WKUPAON_KBD_WKDEP_WKUPDEP_KBD_DSP1_ENABLED                                                        (1U)
#define PM_WKUPAON_KBD_WKDEP_WKUPDEP_KBD_DSP1_DISABLED                                                       (0U)

#define PM_WKUPAON_KBD_WKDEP_RESERVED_SHIFT                                                                 (3U)
#define PM_WKUPAON_KBD_WKDEP_RESERVED_MASK                                                                  (0x00000008U)

#define PM_WKUPAON_KBD_WKDEP_WKUPDEP_KBD_IPU1_SHIFT                                                         (4U)
#define PM_WKUPAON_KBD_WKDEP_WKUPDEP_KBD_IPU1_MASK                                                          (0x00000010U)
#define PM_WKUPAON_KBD_WKDEP_WKUPDEP_KBD_IPU1_ENABLED                                                        (1U)
#define PM_WKUPAON_KBD_WKDEP_WKUPDEP_KBD_IPU1_DISABLED                                                       (0U)

#define PM_WKUPAON_KBD_WKDEP_WKUPDEP_KBD_DSP2_SHIFT                                                         (5U)
#define PM_WKUPAON_KBD_WKDEP_WKUPDEP_KBD_DSP2_MASK                                                          (0x00000020U)
#define PM_WKUPAON_KBD_WKDEP_WKUPDEP_KBD_DSP2_ENABLED                                                        (1U)
#define PM_WKUPAON_KBD_WKDEP_WKUPDEP_KBD_DSP2_DISABLED                                                       (0U)

#define PM_WKUPAON_KBD_WKDEP_WKUPDEP_KBD_EVE1_SHIFT                                                         (6U)
#define PM_WKUPAON_KBD_WKDEP_WKUPDEP_KBD_EVE1_MASK                                                          (0x00000040U)
#define PM_WKUPAON_KBD_WKDEP_WKUPDEP_KBD_EVE1_ENABLED                                                        (1U)
#define PM_WKUPAON_KBD_WKDEP_WKUPDEP_KBD_EVE1_DISABLED                                                       (0U)

#define PM_WKUPAON_KBD_WKDEP_WKUPDEP_KBD_EVE2_SHIFT                                                         (7U)
#define PM_WKUPAON_KBD_WKDEP_WKUPDEP_KBD_EVE2_MASK                                                          (0x00000080U)
#define PM_WKUPAON_KBD_WKDEP_WKUPDEP_KBD_EVE2_ENABLED                                                        (1U)
#define PM_WKUPAON_KBD_WKDEP_WKUPDEP_KBD_EVE2_DISABLED                                                       (0U)

#define PM_WKUPAON_KBD_WKDEP_WKUPDEP_KBD_EVE3_SHIFT                                                         (8U)
#define PM_WKUPAON_KBD_WKDEP_WKUPDEP_KBD_EVE3_MASK                                                          (0x00000100U)
#define PM_WKUPAON_KBD_WKDEP_WKUPDEP_KBD_EVE3_ENABLED                                                        (1U)
#define PM_WKUPAON_KBD_WKDEP_WKUPDEP_KBD_EVE3_DISABLED                                                       (0U)

#define PM_WKUPAON_KBD_WKDEP_WKUPDEP_KBD_EVE4_SHIFT                                                         (9U)
#define PM_WKUPAON_KBD_WKDEP_WKUPDEP_KBD_EVE4_MASK                                                          (0x00000200U)
#define PM_WKUPAON_KBD_WKDEP_WKUPDEP_KBD_EVE4_ENABLED                                                        (1U)
#define PM_WKUPAON_KBD_WKDEP_WKUPDEP_KBD_EVE4_DISABLED                                                       (0U)

#define PM_WKUPAON_KBD_WKDEP_RESERVED1_SHIFT                                                                (10U)
#define PM_WKUPAON_KBD_WKDEP_RESERVED1_MASK                                                                 (0xfffffc00U)

#define RM_WKUPAON_KBD_CONTEXT_RESERVED_SHIFT                                                               (1U)
#define RM_WKUPAON_KBD_CONTEXT_RESERVED_MASK                                                                (0xfffffffeU)

#define RM_WKUPAON_KBD_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                                        (0U)
#define RM_WKUPAON_KBD_CONTEXT_LOSTCONTEXT_DFF_MASK                                                         (0x00000001U)
#define RM_WKUPAON_KBD_CONTEXT_LOSTCONTEXT_DFF_LOST                                                          (1U)
#define RM_WKUPAON_KBD_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                                    (0U)

#define PM_WKUPAON_UART10_WKDEP_WKUPDEP_UART10_MPU_SHIFT                                                    (0U)
#define PM_WKUPAON_UART10_WKDEP_WKUPDEP_UART10_MPU_MASK                                                     (0x00000001U)
#define PM_WKUPAON_UART10_WKDEP_WKUPDEP_UART10_MPU_ENABLED                                                   (1U)
#define PM_WKUPAON_UART10_WKDEP_WKUPDEP_UART10_MPU_DISABLED                                                  (0U)

#define PM_WKUPAON_UART10_WKDEP_WKUPDEP_UART10_IPU2_SHIFT                                                   (1U)
#define PM_WKUPAON_UART10_WKDEP_WKUPDEP_UART10_IPU2_MASK                                                    (0x00000002U)
#define PM_WKUPAON_UART10_WKDEP_WKUPDEP_UART10_IPU2_ENABLED                                                  (1U)
#define PM_WKUPAON_UART10_WKDEP_WKUPDEP_UART10_IPU2_DISABLED                                                 (0U)

#define PM_WKUPAON_UART10_WKDEP_WKUPDEP_UART10_DSP1_SHIFT                                                   (2U)
#define PM_WKUPAON_UART10_WKDEP_WKUPDEP_UART10_DSP1_MASK                                                    (0x00000004U)
#define PM_WKUPAON_UART10_WKDEP_WKUPDEP_UART10_DSP1_ENABLED                                                  (1U)
#define PM_WKUPAON_UART10_WKDEP_WKUPDEP_UART10_DSP1_DISABLED                                                 (0U)

#define PM_WKUPAON_UART10_WKDEP_WKUPDEP_UART10_SDMA_SHIFT                                                   (3U)
#define PM_WKUPAON_UART10_WKDEP_WKUPDEP_UART10_SDMA_MASK                                                    (0x00000008U)
#define PM_WKUPAON_UART10_WKDEP_WKUPDEP_UART10_SDMA_ENABLED                                                  (1U)
#define PM_WKUPAON_UART10_WKDEP_WKUPDEP_UART10_SDMA_DISABLED                                                 (0U)

#define PM_WKUPAON_UART10_WKDEP_WKUPDEP_UART10_IPU1_SHIFT                                                   (4U)
#define PM_WKUPAON_UART10_WKDEP_WKUPDEP_UART10_IPU1_MASK                                                    (0x00000010U)
#define PM_WKUPAON_UART10_WKDEP_WKUPDEP_UART10_IPU1_ENABLED                                                  (1U)
#define PM_WKUPAON_UART10_WKDEP_WKUPDEP_UART10_IPU1_DISABLED                                                 (0U)

#define PM_WKUPAON_UART10_WKDEP_WKUPDEP_UART10_DSP2_SHIFT                                                   (5U)
#define PM_WKUPAON_UART10_WKDEP_WKUPDEP_UART10_DSP2_MASK                                                    (0x00000020U)
#define PM_WKUPAON_UART10_WKDEP_WKUPDEP_UART10_DSP2_ENABLED                                                  (1U)
#define PM_WKUPAON_UART10_WKDEP_WKUPDEP_UART10_DSP2_DISABLED                                                 (0U)

#define PM_WKUPAON_UART10_WKDEP_WKUPDEP_UART10_EVE1_SHIFT                                                   (6U)
#define PM_WKUPAON_UART10_WKDEP_WKUPDEP_UART10_EVE1_MASK                                                    (0x00000040U)
#define PM_WKUPAON_UART10_WKDEP_WKUPDEP_UART10_EVE1_ENABLED                                                  (1U)
#define PM_WKUPAON_UART10_WKDEP_WKUPDEP_UART10_EVE1_DISABLED                                                 (0U)

#define PM_WKUPAON_UART10_WKDEP_WKUPDEP_UART10_EVE2_SHIFT                                                   (7U)
#define PM_WKUPAON_UART10_WKDEP_WKUPDEP_UART10_EVE2_MASK                                                    (0x00000080U)
#define PM_WKUPAON_UART10_WKDEP_WKUPDEP_UART10_EVE2_ENABLED                                                  (1U)
#define PM_WKUPAON_UART10_WKDEP_WKUPDEP_UART10_EVE2_DISABLED                                                 (0U)

#define PM_WKUPAON_UART10_WKDEP_WKUPDEP_UART10_EVE3_SHIFT                                                   (8U)
#define PM_WKUPAON_UART10_WKDEP_WKUPDEP_UART10_EVE3_MASK                                                    (0x00000100U)
#define PM_WKUPAON_UART10_WKDEP_WKUPDEP_UART10_EVE3_ENABLED                                                  (1U)
#define PM_WKUPAON_UART10_WKDEP_WKUPDEP_UART10_EVE3_DISABLED                                                 (0U)

#define PM_WKUPAON_UART10_WKDEP_WKUPDEP_UART10_EVE4_SHIFT                                                   (9U)
#define PM_WKUPAON_UART10_WKDEP_WKUPDEP_UART10_EVE4_MASK                                                    (0x00000200U)
#define PM_WKUPAON_UART10_WKDEP_WKUPDEP_UART10_EVE4_ENABLED                                                  (1U)
#define PM_WKUPAON_UART10_WKDEP_WKUPDEP_UART10_EVE4_DISABLED                                                 (0U)

#define PM_WKUPAON_UART10_WKDEP_RESERVED_SHIFT                                                              (10U)
#define PM_WKUPAON_UART10_WKDEP_RESERVED_MASK                                                               (0xfffffc00U)

#define RM_WKUPAON_UART10_CONTEXT_LOSTMEM_RETAINED_BANK_SHIFT                                               (8U)
#define RM_WKUPAON_UART10_CONTEXT_LOSTMEM_RETAINED_BANK_MASK                                                (0x00000100U)
#define RM_WKUPAON_UART10_CONTEXT_LOSTMEM_RETAINED_BANK_LOST                                                 (1U)
#define RM_WKUPAON_UART10_CONTEXT_LOSTMEM_RETAINED_BANK_MAINTAINED                                           (0U)

#define RM_WKUPAON_UART10_CONTEXT_RESERVED2_SHIFT                                                           (9U)
#define RM_WKUPAON_UART10_CONTEXT_RESERVED2_MASK                                                            (0xfffffe00U)

#define RM_WKUPAON_UART10_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                                     (0U)
#define RM_WKUPAON_UART10_CONTEXT_LOSTCONTEXT_DFF_MASK                                                      (0x00000001U)
#define RM_WKUPAON_UART10_CONTEXT_LOSTCONTEXT_DFF_LOST                                                       (1U)
#define RM_WKUPAON_UART10_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                                 (0U)

#define RM_WKUPAON_UART10_CONTEXT_RESERVED_SHIFT                                                            (1U)
#define RM_WKUPAON_UART10_CONTEXT_RESERVED_MASK                                                             (0x000000feU)

#define PM_WKUPAON_DCAN1_WKDEP_WKUPDEP_DCAN1_MPU_SHIFT                                                      (0U)
#define PM_WKUPAON_DCAN1_WKDEP_WKUPDEP_DCAN1_MPU_MASK                                                       (0x00000001U)
#define PM_WKUPAON_DCAN1_WKDEP_WKUPDEP_DCAN1_MPU_ENABLED                                                     (1U)
#define PM_WKUPAON_DCAN1_WKDEP_WKUPDEP_DCAN1_MPU_DISABLED                                                    (0U)

#define PM_WKUPAON_DCAN1_WKDEP_WKUPDEP_DCAN1_DSP1_SHIFT                                                     (2U)
#define PM_WKUPAON_DCAN1_WKDEP_WKUPDEP_DCAN1_DSP1_MASK                                                      (0x00000004U)
#define PM_WKUPAON_DCAN1_WKDEP_WKUPDEP_DCAN1_DSP1_ENABLED                                                    (1U)
#define PM_WKUPAON_DCAN1_WKDEP_WKUPDEP_DCAN1_DSP1_DISABLED                                                   (0U)

#define PM_WKUPAON_DCAN1_WKDEP_WKUPDEP_DCAN1_IPU2_SHIFT                                                     (1U)
#define PM_WKUPAON_DCAN1_WKDEP_WKUPDEP_DCAN1_IPU2_MASK                                                      (0x00000002U)
#define PM_WKUPAON_DCAN1_WKDEP_WKUPDEP_DCAN1_IPU2_ENABLED                                                    (1U)
#define PM_WKUPAON_DCAN1_WKDEP_WKUPDEP_DCAN1_IPU2_DISABLED                                                   (0U)

#define PM_WKUPAON_DCAN1_WKDEP_WKUPDEP_DCAN1_SDMA_SHIFT                                                     (3U)
#define PM_WKUPAON_DCAN1_WKDEP_WKUPDEP_DCAN1_SDMA_MASK                                                      (0x00000008U)
#define PM_WKUPAON_DCAN1_WKDEP_WKUPDEP_DCAN1_SDMA_ENABLED                                                    (1U)
#define PM_WKUPAON_DCAN1_WKDEP_WKUPDEP_DCAN1_SDMA_DISABLED                                                   (0U)

#define PM_WKUPAON_DCAN1_WKDEP_WKUPDEP_DCAN1_IPU1_SHIFT                                                     (4U)
#define PM_WKUPAON_DCAN1_WKDEP_WKUPDEP_DCAN1_IPU1_MASK                                                      (0x00000010U)
#define PM_WKUPAON_DCAN1_WKDEP_WKUPDEP_DCAN1_IPU1_ENABLED                                                    (1U)
#define PM_WKUPAON_DCAN1_WKDEP_WKUPDEP_DCAN1_IPU1_DISABLED                                                   (0U)

#define PM_WKUPAON_DCAN1_WKDEP_WKUPDEP_DCAN1_DSP2_SHIFT                                                     (5U)
#define PM_WKUPAON_DCAN1_WKDEP_WKUPDEP_DCAN1_DSP2_MASK                                                      (0x00000020U)
#define PM_WKUPAON_DCAN1_WKDEP_WKUPDEP_DCAN1_DSP2_ENABLED                                                    (1U)
#define PM_WKUPAON_DCAN1_WKDEP_WKUPDEP_DCAN1_DSP2_DISABLED                                                   (0U)

#define PM_WKUPAON_DCAN1_WKDEP_WKUPDEP_DCAN1_EVE1_SHIFT                                                     (6U)
#define PM_WKUPAON_DCAN1_WKDEP_WKUPDEP_DCAN1_EVE1_MASK                                                      (0x00000040U)
#define PM_WKUPAON_DCAN1_WKDEP_WKUPDEP_DCAN1_EVE1_ENABLED                                                    (1U)
#define PM_WKUPAON_DCAN1_WKDEP_WKUPDEP_DCAN1_EVE1_DISABLED                                                   (0U)

#define PM_WKUPAON_DCAN1_WKDEP_WKUPDEP_DCAN1_EVE2_SHIFT                                                     (7U)
#define PM_WKUPAON_DCAN1_WKDEP_WKUPDEP_DCAN1_EVE2_MASK                                                      (0x00000080U)
#define PM_WKUPAON_DCAN1_WKDEP_WKUPDEP_DCAN1_EVE2_ENABLED                                                    (1U)
#define PM_WKUPAON_DCAN1_WKDEP_WKUPDEP_DCAN1_EVE2_DISABLED                                                   (0U)

#define PM_WKUPAON_DCAN1_WKDEP_WKUPDEP_DCAN1_EVE3_SHIFT                                                     (8U)
#define PM_WKUPAON_DCAN1_WKDEP_WKUPDEP_DCAN1_EVE3_MASK                                                      (0x00000100U)
#define PM_WKUPAON_DCAN1_WKDEP_WKUPDEP_DCAN1_EVE3_ENABLED                                                    (1U)
#define PM_WKUPAON_DCAN1_WKDEP_WKUPDEP_DCAN1_EVE3_DISABLED                                                   (0U)

#define PM_WKUPAON_DCAN1_WKDEP_WKUPDEP_DCAN1_EVE4_SHIFT                                                     (9U)
#define PM_WKUPAON_DCAN1_WKDEP_WKUPDEP_DCAN1_EVE4_MASK                                                      (0x00000200U)
#define PM_WKUPAON_DCAN1_WKDEP_WKUPDEP_DCAN1_EVE4_ENABLED                                                    (1U)
#define PM_WKUPAON_DCAN1_WKDEP_WKUPDEP_DCAN1_EVE4_DISABLED                                                   (0U)

#define PM_WKUPAON_DCAN1_WKDEP_RESERVED_SHIFT                                                               (10U)
#define PM_WKUPAON_DCAN1_WKDEP_RESERVED_MASK                                                                (0xfffffc00U)

#define RM_WKUPAON_DCAN1_CONTEXT_LOSTMEM_DCAN_MEM_SHIFT                                                     (8U)
#define RM_WKUPAON_DCAN1_CONTEXT_LOSTMEM_DCAN_MEM_MASK                                                      (0x00000100U)
#define RM_WKUPAON_DCAN1_CONTEXT_LOSTMEM_DCAN_MEM_LOST                                                       (1U)
#define RM_WKUPAON_DCAN1_CONTEXT_LOSTMEM_DCAN_MEM_MAINTAINED                                                 (0U)

#define RM_WKUPAON_DCAN1_CONTEXT_RESERVED2_SHIFT                                                            (9U)
#define RM_WKUPAON_DCAN1_CONTEXT_RESERVED2_MASK                                                             (0xfffffe00U)

#define RM_WKUPAON_DCAN1_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                                      (0U)
#define RM_WKUPAON_DCAN1_CONTEXT_LOSTCONTEXT_DFF_MASK                                                       (0x00000001U)
#define RM_WKUPAON_DCAN1_CONTEXT_LOSTCONTEXT_DFF_LOST                                                        (1U)
#define RM_WKUPAON_DCAN1_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                                  (0U)

#define RM_WKUPAON_DCAN1_CONTEXT_RESERVED_SHIFT                                                             (1U)
#define RM_WKUPAON_DCAN1_CONTEXT_RESERVED_MASK                                                              (0x000000feU)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_WKUPAON_PRM_H_ */
