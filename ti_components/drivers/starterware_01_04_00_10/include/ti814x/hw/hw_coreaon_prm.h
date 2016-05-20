/******************************************************************************
*
* hw_coreaon_prm.h - register-level header file for PRCM
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
#ifndef HW_COREAON_PRM_H_
#define HW_COREAON_PRM_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions 
****************************************************************************************************/
#define PM_COREAON_SMARTREFLEX_MPU_WKDEP                                                                    (0x0U)
#define RM_COREAON_SMARTREFLEX_MPU_CONTEXT                                                                  (0x4U)
#define PM_COREAON_SMARTREFLEX_CORE_WKDEP                                                                   (0x10U)
#define RM_COREAON_SMARTREFLEX_CORE_CONTEXT                                                                 (0x14U)
#define PM_COREAON_SMARTREFLEX_GPU_WKDEP                                                                    (0x30U)
#define RM_COREAON_SMARTREFLEX_GPU_CONTEXT                                                                  (0x34U)
#define PM_COREAON_SMARTREFLEX_DSPEVE_WKDEP                                                                 (0x40U)
#define RM_COREAON_SMARTREFLEX_DSPEVE_CONTEXT                                                               (0x44U)
#define PM_COREAON_SMARTREFLEX_IVAHD_WKDEP                                                                  (0x50U)
#define RM_COREAON_SMARTREFLEX_IVAHD_CONTEXT                                                                (0x54U)
#define RM_COREAON_DUMMY_MODULE1_CONTEXT                                                                    (0x84U)
#define RM_COREAON_DUMMY_MODULE2_CONTEXT                                                                    (0x94U)
#define RM_COREAON_DUMMY_MODULE3_CONTEXT                                                                    (0xa4U)
#define RM_COREAON_DUMMY_MODULE4_CONTEXT                                                                    (0xb4U)

/****************************************************************************************************
* Field Definition Macros 
****************************************************************************************************/

#define PM_COREAON_SMARTREFLEX_MPU_WKDEP_WKUPDEP_SMARTREFLEX_MPU_MPU_SHIFT                                  (0U)
#define PM_COREAON_SMARTREFLEX_MPU_WKDEP_WKUPDEP_SMARTREFLEX_MPU_MPU_MASK                                   (0x00000001U)
#define PM_COREAON_SMARTREFLEX_MPU_WKDEP_WKUPDEP_SMARTREFLEX_MPU_MPU_ENABLED                                 (1U)
#define PM_COREAON_SMARTREFLEX_MPU_WKDEP_WKUPDEP_SMARTREFLEX_MPU_MPU_DISABLED                                (0U)

#define PM_COREAON_SMARTREFLEX_MPU_WKDEP_WKUPDEP_SMARTREFLEX_MPU_IPU2_SHIFT                                 (1U)
#define PM_COREAON_SMARTREFLEX_MPU_WKDEP_WKUPDEP_SMARTREFLEX_MPU_IPU2_MASK                                  (0x00000002U)
#define PM_COREAON_SMARTREFLEX_MPU_WKDEP_WKUPDEP_SMARTREFLEX_MPU_IPU2_ENABLED                                (1U)
#define PM_COREAON_SMARTREFLEX_MPU_WKDEP_WKUPDEP_SMARTREFLEX_MPU_IPU2_DISABLED                               (0U)

#define PM_COREAON_SMARTREFLEX_MPU_WKDEP_WKUPDEP_SMARTREFLEX_MPU_DSP1_SHIFT                                 (2U)
#define PM_COREAON_SMARTREFLEX_MPU_WKDEP_WKUPDEP_SMARTREFLEX_MPU_DSP1_MASK                                  (0x00000004U)
#define PM_COREAON_SMARTREFLEX_MPU_WKDEP_WKUPDEP_SMARTREFLEX_MPU_DSP1_ENABLED                                (1U)
#define PM_COREAON_SMARTREFLEX_MPU_WKDEP_WKUPDEP_SMARTREFLEX_MPU_DSP1_DISABLED                               (0U)

#define PM_COREAON_SMARTREFLEX_MPU_WKDEP_WKUPDEP_SMARTREFLEX_MPU_IPU1_SHIFT                                 (4U)
#define PM_COREAON_SMARTREFLEX_MPU_WKDEP_WKUPDEP_SMARTREFLEX_MPU_IPU1_MASK                                  (0x00000010U)
#define PM_COREAON_SMARTREFLEX_MPU_WKDEP_WKUPDEP_SMARTREFLEX_MPU_IPU1_ENABLED                                (1U)
#define PM_COREAON_SMARTREFLEX_MPU_WKDEP_WKUPDEP_SMARTREFLEX_MPU_IPU1_DISABLED                               (0U)

#define PM_COREAON_SMARTREFLEX_MPU_WKDEP_WKUPDEP_SMARTREFLEX_MPU_DSP2_SHIFT                                 (5U)
#define PM_COREAON_SMARTREFLEX_MPU_WKDEP_WKUPDEP_SMARTREFLEX_MPU_DSP2_MASK                                  (0x00000020U)
#define PM_COREAON_SMARTREFLEX_MPU_WKDEP_WKUPDEP_SMARTREFLEX_MPU_DSP2_ENABLED                                (1U)
#define PM_COREAON_SMARTREFLEX_MPU_WKDEP_WKUPDEP_SMARTREFLEX_MPU_DSP2_DISABLED                               (0U)

#define PM_COREAON_SMARTREFLEX_MPU_WKDEP_WKUPDEP_SMARTREFLEX_MPU_EVE1_SHIFT                                 (6U)
#define PM_COREAON_SMARTREFLEX_MPU_WKDEP_WKUPDEP_SMARTREFLEX_MPU_EVE1_MASK                                  (0x00000040U)
#define PM_COREAON_SMARTREFLEX_MPU_WKDEP_WKUPDEP_SMARTREFLEX_MPU_EVE1_ENABLED                                (1U)
#define PM_COREAON_SMARTREFLEX_MPU_WKDEP_WKUPDEP_SMARTREFLEX_MPU_EVE1_DISABLED                               (0U)

#define PM_COREAON_SMARTREFLEX_MPU_WKDEP_WKUPDEP_SMARTREFLEX_MPU_EVE2_SHIFT                                 (7U)
#define PM_COREAON_SMARTREFLEX_MPU_WKDEP_WKUPDEP_SMARTREFLEX_MPU_EVE2_MASK                                  (0x00000080U)
#define PM_COREAON_SMARTREFLEX_MPU_WKDEP_WKUPDEP_SMARTREFLEX_MPU_EVE2_ENABLED                                (1U)
#define PM_COREAON_SMARTREFLEX_MPU_WKDEP_WKUPDEP_SMARTREFLEX_MPU_EVE2_DISABLED                               (0U)

#define PM_COREAON_SMARTREFLEX_MPU_WKDEP_WKUPDEP_SMARTREFLEX_MPU_EVE3_SHIFT                                 (8U)
#define PM_COREAON_SMARTREFLEX_MPU_WKDEP_WKUPDEP_SMARTREFLEX_MPU_EVE3_MASK                                  (0x00000100U)
#define PM_COREAON_SMARTREFLEX_MPU_WKDEP_WKUPDEP_SMARTREFLEX_MPU_EVE3_ENABLED                                (1U)
#define PM_COREAON_SMARTREFLEX_MPU_WKDEP_WKUPDEP_SMARTREFLEX_MPU_EVE3_DISABLED                               (0U)

#define PM_COREAON_SMARTREFLEX_MPU_WKDEP_WKUPDEP_SMARTREFLEX_MPU_EVE4_SHIFT                                 (9U)
#define PM_COREAON_SMARTREFLEX_MPU_WKDEP_WKUPDEP_SMARTREFLEX_MPU_EVE4_MASK                                  (0x00000200U)
#define PM_COREAON_SMARTREFLEX_MPU_WKDEP_WKUPDEP_SMARTREFLEX_MPU_EVE4_ENABLED                                (1U)
#define PM_COREAON_SMARTREFLEX_MPU_WKDEP_WKUPDEP_SMARTREFLEX_MPU_EVE4_DISABLED                               (0U)

#define PM_COREAON_SMARTREFLEX_MPU_WKDEP_RESERVED_SHIFT                                                     (10U)
#define PM_COREAON_SMARTREFLEX_MPU_WKDEP_RESERVED_MASK                                                      (0xfffffc00U)

#define PM_COREAON_SMARTREFLEX_MPU_WKDEP_RESERVED1_SHIFT                                                    (3U)
#define PM_COREAON_SMARTREFLEX_MPU_WKDEP_RESERVED1_MASK                                                     (0x00000008U)

#define RM_COREAON_SMARTREFLEX_MPU_CONTEXT_RESERVED_SHIFT                                                   (1U)
#define RM_COREAON_SMARTREFLEX_MPU_CONTEXT_RESERVED_MASK                                                    (0xfffffffeU)

#define RM_COREAON_SMARTREFLEX_MPU_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                            (0U)
#define RM_COREAON_SMARTREFLEX_MPU_CONTEXT_LOSTCONTEXT_DFF_MASK                                             (0x00000001U)
#define RM_COREAON_SMARTREFLEX_MPU_CONTEXT_LOSTCONTEXT_DFF_LOST                                              (1U)
#define RM_COREAON_SMARTREFLEX_MPU_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                        (0U)

#define PM_COREAON_SMARTREFLEX_CORE_WKDEP_WKUPDEP_SMARTREFLEX_CORE_MPU_SHIFT                                (0U)
#define PM_COREAON_SMARTREFLEX_CORE_WKDEP_WKUPDEP_SMARTREFLEX_CORE_MPU_MASK                                 (0x00000001U)
#define PM_COREAON_SMARTREFLEX_CORE_WKDEP_WKUPDEP_SMARTREFLEX_CORE_MPU_ENABLED                               (1U)
#define PM_COREAON_SMARTREFLEX_CORE_WKDEP_WKUPDEP_SMARTREFLEX_CORE_MPU_DISABLED                              (0U)

#define PM_COREAON_SMARTREFLEX_CORE_WKDEP_WKUPDEP_SMARTREFLEX_CORE_IPU2_SHIFT                               (1U)
#define PM_COREAON_SMARTREFLEX_CORE_WKDEP_WKUPDEP_SMARTREFLEX_CORE_IPU2_MASK                                (0x00000002U)
#define PM_COREAON_SMARTREFLEX_CORE_WKDEP_WKUPDEP_SMARTREFLEX_CORE_IPU2_ENABLED                              (1U)
#define PM_COREAON_SMARTREFLEX_CORE_WKDEP_WKUPDEP_SMARTREFLEX_CORE_IPU2_DISABLED                             (0U)

#define PM_COREAON_SMARTREFLEX_CORE_WKDEP_WKUPDEP_SMARTREFLEX_CORE_DSP1_SHIFT                               (2U)
#define PM_COREAON_SMARTREFLEX_CORE_WKDEP_WKUPDEP_SMARTREFLEX_CORE_DSP1_MASK                                (0x00000004U)
#define PM_COREAON_SMARTREFLEX_CORE_WKDEP_WKUPDEP_SMARTREFLEX_CORE_DSP1_ENABLED                              (1U)
#define PM_COREAON_SMARTREFLEX_CORE_WKDEP_WKUPDEP_SMARTREFLEX_CORE_DSP1_DISABLED                             (0U)

#define PM_COREAON_SMARTREFLEX_CORE_WKDEP_WKUPDEP_SMARTREFLEX_CORE_IPU1_SHIFT                               (4U)
#define PM_COREAON_SMARTREFLEX_CORE_WKDEP_WKUPDEP_SMARTREFLEX_CORE_IPU1_MASK                                (0x00000010U)
#define PM_COREAON_SMARTREFLEX_CORE_WKDEP_WKUPDEP_SMARTREFLEX_CORE_IPU1_ENABLED                              (1U)
#define PM_COREAON_SMARTREFLEX_CORE_WKDEP_WKUPDEP_SMARTREFLEX_CORE_IPU1_DISABLED                             (0U)

#define PM_COREAON_SMARTREFLEX_CORE_WKDEP_WKUPDEP_SMARTREFLEX_CORE_DSP2_SHIFT                               (5U)
#define PM_COREAON_SMARTREFLEX_CORE_WKDEP_WKUPDEP_SMARTREFLEX_CORE_DSP2_MASK                                (0x00000020U)
#define PM_COREAON_SMARTREFLEX_CORE_WKDEP_WKUPDEP_SMARTREFLEX_CORE_DSP2_ENABLED                              (1U)
#define PM_COREAON_SMARTREFLEX_CORE_WKDEP_WKUPDEP_SMARTREFLEX_CORE_DSP2_DISABLED                             (0U)

#define PM_COREAON_SMARTREFLEX_CORE_WKDEP_WKUPDEP_SMARTREFLEX_CORE_EVE1_SHIFT                               (6U)
#define PM_COREAON_SMARTREFLEX_CORE_WKDEP_WKUPDEP_SMARTREFLEX_CORE_EVE1_MASK                                (0x00000040U)
#define PM_COREAON_SMARTREFLEX_CORE_WKDEP_WKUPDEP_SMARTREFLEX_CORE_EVE1_ENABLED                              (1U)
#define PM_COREAON_SMARTREFLEX_CORE_WKDEP_WKUPDEP_SMARTREFLEX_CORE_EVE1_DISABLED                             (0U)

#define PM_COREAON_SMARTREFLEX_CORE_WKDEP_WKUPDEP_SMARTREFLEX_CORE_EVE2_SHIFT                               (7U)
#define PM_COREAON_SMARTREFLEX_CORE_WKDEP_WKUPDEP_SMARTREFLEX_CORE_EVE2_MASK                                (0x00000080U)
#define PM_COREAON_SMARTREFLEX_CORE_WKDEP_WKUPDEP_SMARTREFLEX_CORE_EVE2_ENABLED                              (1U)
#define PM_COREAON_SMARTREFLEX_CORE_WKDEP_WKUPDEP_SMARTREFLEX_CORE_EVE2_DISABLED                             (0U)

#define PM_COREAON_SMARTREFLEX_CORE_WKDEP_WKUPDEP_SMARTREFLEX_CORE_EVE3_SHIFT                               (8U)
#define PM_COREAON_SMARTREFLEX_CORE_WKDEP_WKUPDEP_SMARTREFLEX_CORE_EVE3_MASK                                (0x00000100U)
#define PM_COREAON_SMARTREFLEX_CORE_WKDEP_WKUPDEP_SMARTREFLEX_CORE_EVE3_ENABLED                              (1U)
#define PM_COREAON_SMARTREFLEX_CORE_WKDEP_WKUPDEP_SMARTREFLEX_CORE_EVE3_DISABLED                             (0U)

#define PM_COREAON_SMARTREFLEX_CORE_WKDEP_WKUPDEP_SMARTREFLEX_CORE_EVE4_SHIFT                               (9U)
#define PM_COREAON_SMARTREFLEX_CORE_WKDEP_WKUPDEP_SMARTREFLEX_CORE_EVE4_MASK                                (0x00000200U)
#define PM_COREAON_SMARTREFLEX_CORE_WKDEP_WKUPDEP_SMARTREFLEX_CORE_EVE4_ENABLED                              (1U)
#define PM_COREAON_SMARTREFLEX_CORE_WKDEP_WKUPDEP_SMARTREFLEX_CORE_EVE4_DISABLED                             (0U)

#define PM_COREAON_SMARTREFLEX_CORE_WKDEP_RESERVED_SHIFT                                                    (10U)
#define PM_COREAON_SMARTREFLEX_CORE_WKDEP_RESERVED_MASK                                                     (0xfffffc00U)

#define PM_COREAON_SMARTREFLEX_CORE_WKDEP_RESERVED1_SHIFT                                                   (3U)
#define PM_COREAON_SMARTREFLEX_CORE_WKDEP_RESERVED1_MASK                                                    (0x00000008U)

#define RM_COREAON_SMARTREFLEX_CORE_CONTEXT_RESERVED_SHIFT                                                  (1U)
#define RM_COREAON_SMARTREFLEX_CORE_CONTEXT_RESERVED_MASK                                                   (0xfffffffeU)

#define RM_COREAON_SMARTREFLEX_CORE_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                           (0U)
#define RM_COREAON_SMARTREFLEX_CORE_CONTEXT_LOSTCONTEXT_DFF_MASK                                            (0x00000001U)
#define RM_COREAON_SMARTREFLEX_CORE_CONTEXT_LOSTCONTEXT_DFF_LOST                                             (1U)
#define RM_COREAON_SMARTREFLEX_CORE_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                       (0U)

#define PM_COREAON_SMARTREFLEX_GPU_WKDEP_WKUPDEP_SMARTREFLEX_GPU_MPU_SHIFT                                  (0U)
#define PM_COREAON_SMARTREFLEX_GPU_WKDEP_WKUPDEP_SMARTREFLEX_GPU_MPU_MASK                                   (0x00000001U)
#define PM_COREAON_SMARTREFLEX_GPU_WKDEP_WKUPDEP_SMARTREFLEX_GPU_MPU_ENABLED                                 (1U)
#define PM_COREAON_SMARTREFLEX_GPU_WKDEP_WKUPDEP_SMARTREFLEX_GPU_MPU_DISABLED                                (0U)

#define PM_COREAON_SMARTREFLEX_GPU_WKDEP_WKUPDEP_SMARTREFLEX_GPU_DSP1_SHIFT                                 (2U)
#define PM_COREAON_SMARTREFLEX_GPU_WKDEP_WKUPDEP_SMARTREFLEX_GPU_DSP1_MASK                                  (0x00000004U)
#define PM_COREAON_SMARTREFLEX_GPU_WKDEP_WKUPDEP_SMARTREFLEX_GPU_DSP1_ENABLED                                (1U)
#define PM_COREAON_SMARTREFLEX_GPU_WKDEP_WKUPDEP_SMARTREFLEX_GPU_DSP1_DISABLED                               (0U)

#define PM_COREAON_SMARTREFLEX_GPU_WKDEP_WKUPDEP_SMARTREFLEX_GPU_IPU2_SHIFT                                 (1U)
#define PM_COREAON_SMARTREFLEX_GPU_WKDEP_WKUPDEP_SMARTREFLEX_GPU_IPU2_MASK                                  (0x00000002U)
#define PM_COREAON_SMARTREFLEX_GPU_WKDEP_WKUPDEP_SMARTREFLEX_GPU_IPU2_ENABLED                                (1U)
#define PM_COREAON_SMARTREFLEX_GPU_WKDEP_WKUPDEP_SMARTREFLEX_GPU_IPU2_DISABLED                               (0U)

#define PM_COREAON_SMARTREFLEX_GPU_WKDEP_WKUPDEP_SMARTREFLEX_GPU_IPU1_SHIFT                                 (4U)
#define PM_COREAON_SMARTREFLEX_GPU_WKDEP_WKUPDEP_SMARTREFLEX_GPU_IPU1_MASK                                  (0x00000010U)
#define PM_COREAON_SMARTREFLEX_GPU_WKDEP_WKUPDEP_SMARTREFLEX_GPU_IPU1_ENABLED                                (1U)
#define PM_COREAON_SMARTREFLEX_GPU_WKDEP_WKUPDEP_SMARTREFLEX_GPU_IPU1_DISABLED                               (0U)

#define PM_COREAON_SMARTREFLEX_GPU_WKDEP_WKUPDEP_SMARTREFLEX_GPU_DSP2_SHIFT                                 (5U)
#define PM_COREAON_SMARTREFLEX_GPU_WKDEP_WKUPDEP_SMARTREFLEX_GPU_DSP2_MASK                                  (0x00000020U)
#define PM_COREAON_SMARTREFLEX_GPU_WKDEP_WKUPDEP_SMARTREFLEX_GPU_DSP2_ENABLED                                (1U)
#define PM_COREAON_SMARTREFLEX_GPU_WKDEP_WKUPDEP_SMARTREFLEX_GPU_DSP2_DISABLED                               (0U)

#define PM_COREAON_SMARTREFLEX_GPU_WKDEP_WKUPDEP_SMARTREFLEX_GPU_EVE1_SHIFT                                 (6U)
#define PM_COREAON_SMARTREFLEX_GPU_WKDEP_WKUPDEP_SMARTREFLEX_GPU_EVE1_MASK                                  (0x00000040U)
#define PM_COREAON_SMARTREFLEX_GPU_WKDEP_WKUPDEP_SMARTREFLEX_GPU_EVE1_ENABLED                                (1U)
#define PM_COREAON_SMARTREFLEX_GPU_WKDEP_WKUPDEP_SMARTREFLEX_GPU_EVE1_DISABLED                               (0U)

#define PM_COREAON_SMARTREFLEX_GPU_WKDEP_WKUPDEP_SMARTREFLEX_GPU_EVE2_SHIFT                                 (7U)
#define PM_COREAON_SMARTREFLEX_GPU_WKDEP_WKUPDEP_SMARTREFLEX_GPU_EVE2_MASK                                  (0x00000080U)
#define PM_COREAON_SMARTREFLEX_GPU_WKDEP_WKUPDEP_SMARTREFLEX_GPU_EVE2_ENABLED                                (1U)
#define PM_COREAON_SMARTREFLEX_GPU_WKDEP_WKUPDEP_SMARTREFLEX_GPU_EVE2_DISABLED                               (0U)

#define PM_COREAON_SMARTREFLEX_GPU_WKDEP_WKUPDEP_SMARTREFLEX_GPU_EVE3_SHIFT                                 (8U)
#define PM_COREAON_SMARTREFLEX_GPU_WKDEP_WKUPDEP_SMARTREFLEX_GPU_EVE3_MASK                                  (0x00000100U)
#define PM_COREAON_SMARTREFLEX_GPU_WKDEP_WKUPDEP_SMARTREFLEX_GPU_EVE3_ENABLED                                (1U)
#define PM_COREAON_SMARTREFLEX_GPU_WKDEP_WKUPDEP_SMARTREFLEX_GPU_EVE3_DISABLED                               (0U)

#define PM_COREAON_SMARTREFLEX_GPU_WKDEP_WKUPDEP_SMARTREFLEX_GPU_EVE4_SHIFT                                 (9U)
#define PM_COREAON_SMARTREFLEX_GPU_WKDEP_WKUPDEP_SMARTREFLEX_GPU_EVE4_MASK                                  (0x00000200U)
#define PM_COREAON_SMARTREFLEX_GPU_WKDEP_WKUPDEP_SMARTREFLEX_GPU_EVE4_ENABLED                                (1U)
#define PM_COREAON_SMARTREFLEX_GPU_WKDEP_WKUPDEP_SMARTREFLEX_GPU_EVE4_DISABLED                               (0U)

#define PM_COREAON_SMARTREFLEX_GPU_WKDEP_RESERVED_SHIFT                                                     (10U)
#define PM_COREAON_SMARTREFLEX_GPU_WKDEP_RESERVED_MASK                                                      (0xfffffc00U)

#define PM_COREAON_SMARTREFLEX_GPU_WKDEP_RESERVED1_SHIFT                                                    (3U)
#define PM_COREAON_SMARTREFLEX_GPU_WKDEP_RESERVED1_MASK                                                     (0x00000008U)

#define RM_COREAON_SMARTREFLEX_GPU_CONTEXT_RESERVED_SHIFT                                                   (1U)
#define RM_COREAON_SMARTREFLEX_GPU_CONTEXT_RESERVED_MASK                                                    (0xfffffffeU)

#define RM_COREAON_SMARTREFLEX_GPU_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                            (0U)
#define RM_COREAON_SMARTREFLEX_GPU_CONTEXT_LOSTCONTEXT_DFF_MASK                                             (0x00000001U)
#define RM_COREAON_SMARTREFLEX_GPU_CONTEXT_LOSTCONTEXT_DFF_LOST                                              (1U)
#define RM_COREAON_SMARTREFLEX_GPU_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                        (0U)

#define PM_COREAON_SMARTREFLEX_DSPEVE_WKDEP_WKUPDEP_SMARTREFLEX_DSPEVE_MPU_SHIFT                            (0U)
#define PM_COREAON_SMARTREFLEX_DSPEVE_WKDEP_WKUPDEP_SMARTREFLEX_DSPEVE_MPU_MASK                             (0x00000001U)
#define PM_COREAON_SMARTREFLEX_DSPEVE_WKDEP_WKUPDEP_SMARTREFLEX_DSPEVE_MPU_ENABLED                           (1U)
#define PM_COREAON_SMARTREFLEX_DSPEVE_WKDEP_WKUPDEP_SMARTREFLEX_DSPEVE_MPU_DISABLED                          (0U)

#define PM_COREAON_SMARTREFLEX_DSPEVE_WKDEP_WKUPDEP_SMARTREFLEX_DSPEVE_DSP1_SHIFT                           (2U)
#define PM_COREAON_SMARTREFLEX_DSPEVE_WKDEP_WKUPDEP_SMARTREFLEX_DSPEVE_DSP1_MASK                            (0x00000004U)
#define PM_COREAON_SMARTREFLEX_DSPEVE_WKDEP_WKUPDEP_SMARTREFLEX_DSPEVE_DSP1_ENABLED                          (1U)
#define PM_COREAON_SMARTREFLEX_DSPEVE_WKDEP_WKUPDEP_SMARTREFLEX_DSPEVE_DSP1_DISABLED                         (0U)

#define PM_COREAON_SMARTREFLEX_DSPEVE_WKDEP_WKUPDEP_SMARTREFLEX_DSPEVE_IPU2_SHIFT                           (1U)
#define PM_COREAON_SMARTREFLEX_DSPEVE_WKDEP_WKUPDEP_SMARTREFLEX_DSPEVE_IPU2_MASK                            (0x00000002U)
#define PM_COREAON_SMARTREFLEX_DSPEVE_WKDEP_WKUPDEP_SMARTREFLEX_DSPEVE_IPU2_ENABLED                          (1U)
#define PM_COREAON_SMARTREFLEX_DSPEVE_WKDEP_WKUPDEP_SMARTREFLEX_DSPEVE_IPU2_DISABLED                         (0U)

#define PM_COREAON_SMARTREFLEX_DSPEVE_WKDEP_WKUPDEP_SMARTREFLEX_DSPEVE_SDMA_SHIFT                           (3U)
#define PM_COREAON_SMARTREFLEX_DSPEVE_WKDEP_WKUPDEP_SMARTREFLEX_DSPEVE_SDMA_MASK                            (0x00000008U)
#define PM_COREAON_SMARTREFLEX_DSPEVE_WKDEP_WKUPDEP_SMARTREFLEX_DSPEVE_SDMA_ENABLED                          (1U)
#define PM_COREAON_SMARTREFLEX_DSPEVE_WKDEP_WKUPDEP_SMARTREFLEX_DSPEVE_SDMA_DISABLED                         (0U)

#define PM_COREAON_SMARTREFLEX_DSPEVE_WKDEP_WKUPDEP_SMARTREFLEX_DSPEVE_IPU1_SHIFT                           (4U)
#define PM_COREAON_SMARTREFLEX_DSPEVE_WKDEP_WKUPDEP_SMARTREFLEX_DSPEVE_IPU1_MASK                            (0x00000010U)
#define PM_COREAON_SMARTREFLEX_DSPEVE_WKDEP_WKUPDEP_SMARTREFLEX_DSPEVE_IPU1_ENABLED                          (1U)
#define PM_COREAON_SMARTREFLEX_DSPEVE_WKDEP_WKUPDEP_SMARTREFLEX_DSPEVE_IPU1_DISABLED                         (0U)

#define PM_COREAON_SMARTREFLEX_DSPEVE_WKDEP_WKUPDEP_SMARTREFLEX_DSPEVE_DSP2_SHIFT                           (5U)
#define PM_COREAON_SMARTREFLEX_DSPEVE_WKDEP_WKUPDEP_SMARTREFLEX_DSPEVE_DSP2_MASK                            (0x00000020U)
#define PM_COREAON_SMARTREFLEX_DSPEVE_WKDEP_WKUPDEP_SMARTREFLEX_DSPEVE_DSP2_ENABLED                          (1U)
#define PM_COREAON_SMARTREFLEX_DSPEVE_WKDEP_WKUPDEP_SMARTREFLEX_DSPEVE_DSP2_DISABLED                         (0U)

#define PM_COREAON_SMARTREFLEX_DSPEVE_WKDEP_WKUPDEP_SMARTREFLEX_DSPEVE_EVE1_SHIFT                           (6U)
#define PM_COREAON_SMARTREFLEX_DSPEVE_WKDEP_WKUPDEP_SMARTREFLEX_DSPEVE_EVE1_MASK                            (0x00000040U)
#define PM_COREAON_SMARTREFLEX_DSPEVE_WKDEP_WKUPDEP_SMARTREFLEX_DSPEVE_EVE1_ENABLED                          (1U)
#define PM_COREAON_SMARTREFLEX_DSPEVE_WKDEP_WKUPDEP_SMARTREFLEX_DSPEVE_EVE1_DISABLED                         (0U)

#define PM_COREAON_SMARTREFLEX_DSPEVE_WKDEP_WKUPDEP_SMARTREFLEX_DSPEVE_EVE2_SHIFT                           (7U)
#define PM_COREAON_SMARTREFLEX_DSPEVE_WKDEP_WKUPDEP_SMARTREFLEX_DSPEVE_EVE2_MASK                            (0x00000080U)
#define PM_COREAON_SMARTREFLEX_DSPEVE_WKDEP_WKUPDEP_SMARTREFLEX_DSPEVE_EVE2_ENABLED                          (1U)
#define PM_COREAON_SMARTREFLEX_DSPEVE_WKDEP_WKUPDEP_SMARTREFLEX_DSPEVE_EVE2_DISABLED                         (0U)

#define PM_COREAON_SMARTREFLEX_DSPEVE_WKDEP_WKUPDEP_SMARTREFLEX_DSPEVE_EVE3_SHIFT                           (8U)
#define PM_COREAON_SMARTREFLEX_DSPEVE_WKDEP_WKUPDEP_SMARTREFLEX_DSPEVE_EVE3_MASK                            (0x00000100U)
#define PM_COREAON_SMARTREFLEX_DSPEVE_WKDEP_WKUPDEP_SMARTREFLEX_DSPEVE_EVE3_ENABLED                          (1U)
#define PM_COREAON_SMARTREFLEX_DSPEVE_WKDEP_WKUPDEP_SMARTREFLEX_DSPEVE_EVE3_DISABLED                         (0U)

#define PM_COREAON_SMARTREFLEX_DSPEVE_WKDEP_WKUPDEP_SMARTREFLEX_DSPEVE_EVE4_SHIFT                           (9U)
#define PM_COREAON_SMARTREFLEX_DSPEVE_WKDEP_WKUPDEP_SMARTREFLEX_DSPEVE_EVE4_MASK                            (0x00000200U)
#define PM_COREAON_SMARTREFLEX_DSPEVE_WKDEP_WKUPDEP_SMARTREFLEX_DSPEVE_EVE4_ENABLED                          (1U)
#define PM_COREAON_SMARTREFLEX_DSPEVE_WKDEP_WKUPDEP_SMARTREFLEX_DSPEVE_EVE4_DISABLED                         (0U)

#define PM_COREAON_SMARTREFLEX_DSPEVE_WKDEP_RESERVED_SHIFT                                                  (10U)
#define PM_COREAON_SMARTREFLEX_DSPEVE_WKDEP_RESERVED_MASK                                                   (0xfffffc00U)

#define RM_COREAON_SMARTREFLEX_DSPEVE_CONTEXT_RESERVED_SHIFT                                                (1U)
#define RM_COREAON_SMARTREFLEX_DSPEVE_CONTEXT_RESERVED_MASK                                                 (0xfffffffeU)

#define RM_COREAON_SMARTREFLEX_DSPEVE_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                         (0U)
#define RM_COREAON_SMARTREFLEX_DSPEVE_CONTEXT_LOSTCONTEXT_DFF_MASK                                          (0x00000001U)
#define RM_COREAON_SMARTREFLEX_DSPEVE_CONTEXT_LOSTCONTEXT_DFF_LOST                                           (1U)
#define RM_COREAON_SMARTREFLEX_DSPEVE_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                     (0U)

#define PM_COREAON_SMARTREFLEX_IVAHD_WKDEP_WKUPDEP_SMARTREFLEX_IVAHD_MPU_SHIFT                              (0U)
#define PM_COREAON_SMARTREFLEX_IVAHD_WKDEP_WKUPDEP_SMARTREFLEX_IVAHD_MPU_MASK                               (0x00000001U)
#define PM_COREAON_SMARTREFLEX_IVAHD_WKDEP_WKUPDEP_SMARTREFLEX_IVAHD_MPU_ENABLED                             (1U)
#define PM_COREAON_SMARTREFLEX_IVAHD_WKDEP_WKUPDEP_SMARTREFLEX_IVAHD_MPU_DISABLED                            (0U)

#define PM_COREAON_SMARTREFLEX_IVAHD_WKDEP_WKUPDEP_SMARTREFLEX_IVAHD_DSP1_SHIFT                             (2U)
#define PM_COREAON_SMARTREFLEX_IVAHD_WKDEP_WKUPDEP_SMARTREFLEX_IVAHD_DSP1_MASK                              (0x00000004U)
#define PM_COREAON_SMARTREFLEX_IVAHD_WKDEP_WKUPDEP_SMARTREFLEX_IVAHD_DSP1_ENABLED                            (1U)
#define PM_COREAON_SMARTREFLEX_IVAHD_WKDEP_WKUPDEP_SMARTREFLEX_IVAHD_DSP1_DISABLED                           (0U)

#define PM_COREAON_SMARTREFLEX_IVAHD_WKDEP_WKUPDEP_SMARTREFLEX_IVAHD_IPU2_SHIFT                             (1U)
#define PM_COREAON_SMARTREFLEX_IVAHD_WKDEP_WKUPDEP_SMARTREFLEX_IVAHD_IPU2_MASK                              (0x00000002U)
#define PM_COREAON_SMARTREFLEX_IVAHD_WKDEP_WKUPDEP_SMARTREFLEX_IVAHD_IPU2_ENABLED                            (1U)
#define PM_COREAON_SMARTREFLEX_IVAHD_WKDEP_WKUPDEP_SMARTREFLEX_IVAHD_IPU2_DISABLED                           (0U)

#define PM_COREAON_SMARTREFLEX_IVAHD_WKDEP_WKUPDEP_SMARTREFLEX_IVAHD_IPU1_SHIFT                             (4U)
#define PM_COREAON_SMARTREFLEX_IVAHD_WKDEP_WKUPDEP_SMARTREFLEX_IVAHD_IPU1_MASK                              (0x00000010U)
#define PM_COREAON_SMARTREFLEX_IVAHD_WKDEP_WKUPDEP_SMARTREFLEX_IVAHD_IPU1_ENABLED                            (1U)
#define PM_COREAON_SMARTREFLEX_IVAHD_WKDEP_WKUPDEP_SMARTREFLEX_IVAHD_IPU1_DISABLED                           (0U)

#define PM_COREAON_SMARTREFLEX_IVAHD_WKDEP_WKUPDEP_SMARTREFLEX_IVAHD_DSP2_SHIFT                             (5U)
#define PM_COREAON_SMARTREFLEX_IVAHD_WKDEP_WKUPDEP_SMARTREFLEX_IVAHD_DSP2_MASK                              (0x00000020U)
#define PM_COREAON_SMARTREFLEX_IVAHD_WKDEP_WKUPDEP_SMARTREFLEX_IVAHD_DSP2_ENABLED                            (1U)
#define PM_COREAON_SMARTREFLEX_IVAHD_WKDEP_WKUPDEP_SMARTREFLEX_IVAHD_DSP2_DISABLED                           (0U)

#define PM_COREAON_SMARTREFLEX_IVAHD_WKDEP_WKUPDEP_SMARTREFLEX_IVAHD_EVE1_SHIFT                             (6U)
#define PM_COREAON_SMARTREFLEX_IVAHD_WKDEP_WKUPDEP_SMARTREFLEX_IVAHD_EVE1_MASK                              (0x00000040U)
#define PM_COREAON_SMARTREFLEX_IVAHD_WKDEP_WKUPDEP_SMARTREFLEX_IVAHD_EVE1_ENABLED                            (1U)
#define PM_COREAON_SMARTREFLEX_IVAHD_WKDEP_WKUPDEP_SMARTREFLEX_IVAHD_EVE1_DISABLED                           (0U)

#define PM_COREAON_SMARTREFLEX_IVAHD_WKDEP_WKUPDEP_SMARTREFLEX_IVAHD_EVE2_SHIFT                             (7U)
#define PM_COREAON_SMARTREFLEX_IVAHD_WKDEP_WKUPDEP_SMARTREFLEX_IVAHD_EVE2_MASK                              (0x00000080U)
#define PM_COREAON_SMARTREFLEX_IVAHD_WKDEP_WKUPDEP_SMARTREFLEX_IVAHD_EVE2_ENABLED                            (1U)
#define PM_COREAON_SMARTREFLEX_IVAHD_WKDEP_WKUPDEP_SMARTREFLEX_IVAHD_EVE2_DISABLED                           (0U)

#define PM_COREAON_SMARTREFLEX_IVAHD_WKDEP_WKUPDEP_SMARTREFLEX_IVAHD_EVE3_SHIFT                             (8U)
#define PM_COREAON_SMARTREFLEX_IVAHD_WKDEP_WKUPDEP_SMARTREFLEX_IVAHD_EVE3_MASK                              (0x00000100U)
#define PM_COREAON_SMARTREFLEX_IVAHD_WKDEP_WKUPDEP_SMARTREFLEX_IVAHD_EVE3_ENABLED                            (1U)
#define PM_COREAON_SMARTREFLEX_IVAHD_WKDEP_WKUPDEP_SMARTREFLEX_IVAHD_EVE3_DISABLED                           (0U)

#define PM_COREAON_SMARTREFLEX_IVAHD_WKDEP_WKUPDEP_SMARTREFLEX_IVAHD_EVE4_SHIFT                             (9U)
#define PM_COREAON_SMARTREFLEX_IVAHD_WKDEP_WKUPDEP_SMARTREFLEX_IVAHD_EVE4_MASK                              (0x00000200U)
#define PM_COREAON_SMARTREFLEX_IVAHD_WKDEP_WKUPDEP_SMARTREFLEX_IVAHD_EVE4_ENABLED                            (1U)
#define PM_COREAON_SMARTREFLEX_IVAHD_WKDEP_WKUPDEP_SMARTREFLEX_IVAHD_EVE4_DISABLED                           (0U)

#define PM_COREAON_SMARTREFLEX_IVAHD_WKDEP_RESERVED_SHIFT                                                   (10U)
#define PM_COREAON_SMARTREFLEX_IVAHD_WKDEP_RESERVED_MASK                                                    (0xfffffc00U)

#define PM_COREAON_SMARTREFLEX_IVAHD_WKDEP_RESERVED1_SHIFT                                                  (3U)
#define PM_COREAON_SMARTREFLEX_IVAHD_WKDEP_RESERVED1_MASK                                                   (0x00000008U)

#define RM_COREAON_SMARTREFLEX_IVAHD_CONTEXT_RESERVED_SHIFT                                                 (1U)
#define RM_COREAON_SMARTREFLEX_IVAHD_CONTEXT_RESERVED_MASK                                                  (0xfffffffeU)

#define RM_COREAON_SMARTREFLEX_IVAHD_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                          (0U)
#define RM_COREAON_SMARTREFLEX_IVAHD_CONTEXT_LOSTCONTEXT_DFF_MASK                                           (0x00000001U)
#define RM_COREAON_SMARTREFLEX_IVAHD_CONTEXT_LOSTCONTEXT_DFF_LOST                                            (1U)
#define RM_COREAON_SMARTREFLEX_IVAHD_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                      (0U)

#define RM_COREAON_DUMMY_MODULE1_CONTEXT_RESERVED_SHIFT                                                     (1U)
#define RM_COREAON_DUMMY_MODULE1_CONTEXT_RESERVED_MASK                                                      (0xfffffffeU)

#define RM_COREAON_DUMMY_MODULE1_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                              (0U)
#define RM_COREAON_DUMMY_MODULE1_CONTEXT_LOSTCONTEXT_DFF_MASK                                               (0x00000001U)
#define RM_COREAON_DUMMY_MODULE1_CONTEXT_LOSTCONTEXT_DFF_LOST                                                (1U)
#define RM_COREAON_DUMMY_MODULE1_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                          (0U)

#define RM_COREAON_DUMMY_MODULE2_CONTEXT_RESERVED_SHIFT                                                     (1U)
#define RM_COREAON_DUMMY_MODULE2_CONTEXT_RESERVED_MASK                                                      (0xfffffffeU)

#define RM_COREAON_DUMMY_MODULE2_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                              (0U)
#define RM_COREAON_DUMMY_MODULE2_CONTEXT_LOSTCONTEXT_DFF_MASK                                               (0x00000001U)
#define RM_COREAON_DUMMY_MODULE2_CONTEXT_LOSTCONTEXT_DFF_LOST                                                (1U)
#define RM_COREAON_DUMMY_MODULE2_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                          (0U)

#define RM_COREAON_DUMMY_MODULE3_CONTEXT_RESERVED_SHIFT                                                     (1U)
#define RM_COREAON_DUMMY_MODULE3_CONTEXT_RESERVED_MASK                                                      (0xfffffffeU)

#define RM_COREAON_DUMMY_MODULE3_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                              (0U)
#define RM_COREAON_DUMMY_MODULE3_CONTEXT_LOSTCONTEXT_DFF_MASK                                               (0x00000001U)
#define RM_COREAON_DUMMY_MODULE3_CONTEXT_LOSTCONTEXT_DFF_LOST                                                (1U)
#define RM_COREAON_DUMMY_MODULE3_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                          (0U)

#define RM_COREAON_DUMMY_MODULE4_CONTEXT_RESERVED_SHIFT                                                     (1U)
#define RM_COREAON_DUMMY_MODULE4_CONTEXT_RESERVED_MASK                                                      (0xfffffffeU)

#define RM_COREAON_DUMMY_MODULE4_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                              (0U)
#define RM_COREAON_DUMMY_MODULE4_CONTEXT_LOSTCONTEXT_DFF_MASK                                               (0x00000001U)
#define RM_COREAON_DUMMY_MODULE4_CONTEXT_LOSTCONTEXT_DFF_LOST                                                (1U)
#define RM_COREAON_DUMMY_MODULE4_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                          (0U)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_COREAON_PRM_H_ */
