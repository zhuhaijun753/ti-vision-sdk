/******************************************************************************
*
* hw_rtc_prm.h - register-level header file for PRCM
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
#ifndef HW_RTC_PRM_H_
#define HW_RTC_PRM_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions 
****************************************************************************************************/
#define PM_RTC_RTCSS_WKDEP                                                                                  (0x0U)
#define RM_RTC_RTCSS_CONTEXT                                                                                (0x4U)

/****************************************************************************************************
* Field Definition Macros 
****************************************************************************************************/

#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ1_MPU_SHIFT                                                       (0U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ1_MPU_MASK                                                        (0x00000001U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ1_MPU_ENABLED                                                      (1U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ1_MPU_DISABLED                                                     (0U)

#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ1_IPU2_SHIFT                                                      (1U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ1_IPU2_MASK                                                       (0x00000002U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ1_IPU2_ENABLED                                                     (1U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ1_IPU2_DISABLED                                                    (0U)

#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ1_DSP1_SHIFT                                                      (2U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ1_DSP1_MASK                                                       (0x00000004U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ1_DSP1_ENABLED                                                     (1U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ1_DSP1_DISABLED                                                    (0U)

#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ1_IPU1_SHIFT                                                      (4U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ1_IPU1_MASK                                                       (0x00000010U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ1_IPU1_ENABLED                                                     (1U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ1_IPU1_DISABLED                                                    (0U)

#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ1_DSP2_SHIFT                                                      (5U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ1_DSP2_MASK                                                       (0x00000020U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ1_DSP2_ENABLED                                                     (1U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ1_DSP2_DISABLED                                                    (0U)

#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ1_EVE1_SHIFT                                                      (6U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ1_EVE1_MASK                                                       (0x00000040U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ1_EVE1_ENABLED                                                     (1U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ1_EVE1_DISABLED                                                    (0U)

#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ1_EVE2_SHIFT                                                      (7U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ1_EVE2_MASK                                                       (0x00000080U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ1_EVE2_ENABLED                                                     (1U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ1_EVE2_DISABLED                                                    (0U)

#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ1_EVE3_SHIFT                                                      (8U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ1_EVE3_MASK                                                       (0x00000100U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ1_EVE3_ENABLED                                                     (1U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ1_EVE3_DISABLED                                                    (0U)

#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ1_EVE4_SHIFT                                                      (9U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ1_EVE4_MASK                                                       (0x00000200U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ1_EVE4_ENABLED                                                     (1U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ1_EVE4_DISABLED                                                    (0U)

#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ2_MPU_SHIFT                                                       (10U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ2_MPU_MASK                                                        (0x00000400U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ2_MPU_ENABLED                                                      (1U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ2_MPU_DISABLED                                                     (0U)

#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ2_IPU2_SHIFT                                                      (11U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ2_IPU2_MASK                                                       (0x00000800U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ2_IPU2_ENABLED                                                     (1U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ2_IPU2_DISABLED                                                    (0U)

#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ2_DSP1_SHIFT                                                      (12U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ2_DSP1_MASK                                                       (0x00001000U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ2_DSP1_ENABLED                                                     (1U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ2_DSP1_DISABLED                                                    (0U)

#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ2_IPU1_SHIFT                                                      (14U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ2_IPU1_MASK                                                       (0x00004000U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ2_IPU1_ENABLED                                                     (1U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ2_IPU1_DISABLED                                                    (0U)

#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ2_DSP2_SHIFT                                                      (15U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ2_DSP2_MASK                                                       (0x00008000U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ2_DSP2_ENABLED                                                     (1U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ2_DSP2_DISABLED                                                    (0U)

#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ2_EVE1_SHIFT                                                      (16U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ2_EVE1_MASK                                                       (0x00010000U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ2_EVE1_ENABLED                                                     (1U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ2_EVE1_DISABLED                                                    (0U)

#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ2_EVE2_SHIFT                                                      (17U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ2_EVE2_MASK                                                       (0x00020000U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ2_EVE2_ENABLED                                                     (1U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ2_EVE2_DISABLED                                                    (0U)

#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ2_EVE3_SHIFT                                                      (18U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ2_EVE3_MASK                                                       (0x00040000U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ2_EVE3_ENABLED                                                     (1U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ2_EVE3_DISABLED                                                    (0U)

#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ2_EVE4_SHIFT                                                      (19U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ2_EVE4_MASK                                                       (0x00080000U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ2_EVE4_ENABLED                                                     (1U)
#define PM_RTC_RTCSS_WKDEP_WKUPDEP_RTC_IRQ2_EVE4_DISABLED                                                    (0U)

#define PM_RTC_RTCSS_WKDEP_RESERVED_SHIFT                                                                   (3U)
#define PM_RTC_RTCSS_WKDEP_RESERVED_MASK                                                                    (0x00000008U)

#define PM_RTC_RTCSS_WKDEP_RESERVED1_SHIFT                                                                  (13U)
#define PM_RTC_RTCSS_WKDEP_RESERVED1_MASK                                                                   (0x00002000U)

#define PM_RTC_RTCSS_WKDEP_RESERVED2_SHIFT                                                                  (20U)
#define PM_RTC_RTCSS_WKDEP_RESERVED2_MASK                                                                   (0xfff00000U)

#define RM_RTC_RTCSS_CONTEXT_RESERVED_SHIFT                                                                 (1U)
#define RM_RTC_RTCSS_CONTEXT_RESERVED_MASK                                                                  (0xfffffffeU)

#define RM_RTC_RTCSS_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                                          (0U)
#define RM_RTC_RTCSS_CONTEXT_LOSTCONTEXT_DFF_MASK                                                           (0x00000001U)
#define RM_RTC_RTCSS_CONTEXT_LOSTCONTEXT_DFF_LOST                                                            (1U)
#define RM_RTC_RTCSS_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                                      (0U)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_RTC_PRM_H_ */
