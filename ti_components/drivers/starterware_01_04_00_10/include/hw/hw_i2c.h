/******************************************************************************
*
* hw_i2c.h - register-level header file for I2C
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
#ifndef HW_I2C_H_
#define HW_I2C_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions 
****************************************************************************************************/
#define I2C_REVNB_LO                                                                                        (0x0U)
#define I2C_REVNB_HI                                                                                        (0x4U)
#define I2C_SYSC                                                                                            (0x10U)
#define I2C_IRQSTATUS_RAW                                                                                   (0x24U)
#define I2C_IRQSTATUS                                                                                       (0x28U)
#define I2C_IRQENABLE_SET                                                                                   (0x2cU)
#define I2C_IRQENABLE_CLR                                                                                   (0x30U)
#define I2C_WE                                                                                              (0x34U)
#define I2C_DMARXENABLE_SET                                                                                 (0x38U)
#define I2C_DMATXENABLE_SET                                                                                 (0x3cU)
#define I2C_DMARXENABLE_CLR                                                                                 (0x40U)
#define I2C_DMATXENABLE_CLR                                                                                 (0x44U)
#define I2C_DMARXWAKE_EN                                                                                    (0x48U)
#define I2C_DMATXWAKE_EN                                                                                    (0x4cU)
#define I2C_SYSS                                                                                            (0x90U)
#define I2C_BUF                                                                                             (0x94U)
#define I2C_CNT                                                                                             (0x98U)
#define I2C_DATA                                                                                            (0x9cU)
#define I2C_CON                                                                                             (0xa4U)
#define I2C_OA                                                                                              (0xa8U)
#define I2C_SA                                                                                              (0xacU)
#define I2C_PSC                                                                                             (0xb0U)
#define I2C_SCLL                                                                                            (0xb4U)
#define I2C_SCLH                                                                                            (0xb8U)
#define I2C_SYSTEST                                                                                         (0xbcU)
#define I2C_BUFSTAT                                                                                         (0xc0U)
#define I2C_OA1                                                                                             (0xc4U)
#define I2C_OA2                                                                                             (0xc8U)
#define I2C_OA3                                                                                             (0xccU)
#define I2C_ACTOA                                                                                           (0xd0U)
#define I2C_SBLOCK                                                                                          (0xd4U)

/****************************************************************************************************
* Field Definition Macros 
****************************************************************************************************/

#define I2C_REVNB_LO_REVISION_SHIFT                                                                         (0U)
#define I2C_REVNB_LO_REVISION_MASK                                                                          (0x0000ffffU)

#define I2C_REVNB_HI_REVISION_SHIFT                                                                         (0U)
#define I2C_REVNB_HI_REVISION_MASK                                                                          (0x0000ffffU)

#define I2C_SYSC_AUTOIDLE_SHIFT                                                                             (0U)
#define I2C_SYSC_AUTOIDLE_MASK                                                                              (0x00000001U)
#define I2C_SYSC_AUTOIDLE_DISABLE                                                                            (0U)
#define I2C_SYSC_AUTOIDLE_ENABLE                                                                             (1U)

#define I2C_SYSC_SRST_SHIFT                                                                                 (1U)
#define I2C_SYSC_SRST_MASK                                                                                  (0x00000002U)
#define I2C_SYSC_SRST_NMODE                                                                                  (0U)
#define I2C_SYSC_SRST_RSTMODE                                                                                (1U)

#define I2C_SYSC_RESERVED_SHIFT                                                                             (5U)
#define I2C_SYSC_RESERVED_MASK                                                                              (0x000000e0U)

#define I2C_SYSC_ENAWAKEUP_SHIFT                                                                            (2U)
#define I2C_SYSC_ENAWAKEUP_MASK                                                                             (0x00000004U)
#define I2C_SYSC_ENAWAKEUP_DISABLE                                                                           (0U)
#define I2C_SYSC_ENAWAKEUP_ENABLE                                                                            (1U)

#define I2C_SYSC_RESERVED1_SHIFT                                                                            (10U)
#define I2C_SYSC_RESERVED1_MASK                                                                             (0x0000fc00U)

#define I2C_SYSC_IDLEMODE_SHIFT                                                                             (3U)
#define I2C_SYSC_IDLEMODE_MASK                                                                              (0x00000018U)
#define I2C_SYSC_IDLEMODE_FORCEIDLE                                                                          (0U)
#define I2C_SYSC_IDLEMODE_SMARTIDLE_WAKEUP                                                                   (3U)
#define I2C_SYSC_IDLEMODE_NOIDLE                                                                             (1U)
#define I2C_SYSC_IDLEMODE_SMARTIDLE                                                                          (2U)

#define I2C_SYSC_CLKACTIVITY_SHIFT                                                                          (8U)
#define I2C_SYSC_CLKACTIVITY_MASK                                                                           (0x00000300U)
#define I2C_SYSC_CLKACTIVITY_BOOTHOFF                                                                        (0U)
#define I2C_SYSC_CLKACTIVITY_OCPON                                                                           (1U)
#define I2C_SYSC_CLKACTIVITY_SYSON                                                                           (2U)
#define I2C_SYSC_CLKACTIVITY_BOOTHON                                                                         (3U)

#define I2C_IRQSTATUS_RAW_AL_SHIFT                                                                          (0U)
#define I2C_IRQSTATUS_RAW_AL_MASK                                                                           (0x00000001U)
#define I2C_IRQSTATUS_RAW_AL_CLEAR                                                                           (0U)
#define I2C_IRQSTATUS_RAW_AL_SET                                                                             (1U)

#define I2C_IRQSTATUS_RAW_NACK_SHIFT                                                                        (1U)
#define I2C_IRQSTATUS_RAW_NACK_MASK                                                                         (0x00000002U)
#define I2C_IRQSTATUS_RAW_NACK_CLEAR                                                                         (0U)
#define I2C_IRQSTATUS_RAW_NACK_SET                                                                           (1U)

#define I2C_IRQSTATUS_RAW_ARDY_SHIFT                                                                        (2U)
#define I2C_IRQSTATUS_RAW_ARDY_MASK                                                                         (0x00000004U)
#define I2C_IRQSTATUS_RAW_ARDY_CLEAR                                                                         (0U)
#define I2C_IRQSTATUS_RAW_ARDY_SET                                                                           (1U)

#define I2C_IRQSTATUS_RAW_RRDY_SHIFT                                                                        (3U)
#define I2C_IRQSTATUS_RAW_RRDY_MASK                                                                         (0x00000008U)
#define I2C_IRQSTATUS_RAW_RRDY_CLEAR                                                                         (0U)
#define I2C_IRQSTATUS_RAW_RRDY_SET                                                                           (1U)

#define I2C_IRQSTATUS_RAW_XRDY_SHIFT                                                                        (4U)
#define I2C_IRQSTATUS_RAW_XRDY_MASK                                                                         (0x00000010U)
#define I2C_IRQSTATUS_RAW_XRDY_CLEAR                                                                         (0U)
#define I2C_IRQSTATUS_RAW_XRDY_SET                                                                           (1U)

#define I2C_IRQSTATUS_RAW_GC_SHIFT                                                                          (5U)
#define I2C_IRQSTATUS_RAW_GC_MASK                                                                           (0x00000020U)
#define I2C_IRQSTATUS_RAW_GC_CLEAR                                                                           (0U)
#define I2C_IRQSTATUS_RAW_GC_SET                                                                             (1U)

#define I2C_IRQSTATUS_RAW_STC_SHIFT                                                                         (6U)
#define I2C_IRQSTATUS_RAW_STC_MASK                                                                          (0x00000040U)
#define I2C_IRQSTATUS_RAW_STC_CLEAR                                                                          (0U)
#define I2C_IRQSTATUS_RAW_STC_SET                                                                            (1U)

#define I2C_IRQSTATUS_RAW_AERR_SHIFT                                                                        (7U)
#define I2C_IRQSTATUS_RAW_AERR_MASK                                                                         (0x00000080U)
#define I2C_IRQSTATUS_RAW_AERR_CLEAR                                                                         (0U)
#define I2C_IRQSTATUS_RAW_AERR_SET                                                                           (1U)

#define I2C_IRQSTATUS_RAW_BF_SHIFT                                                                          (8U)
#define I2C_IRQSTATUS_RAW_BF_MASK                                                                           (0x00000100U)
#define I2C_IRQSTATUS_RAW_BF_CLEAR                                                                           (0U)
#define I2C_IRQSTATUS_RAW_BF_SET                                                                             (1U)

#define I2C_IRQSTATUS_RAW_AAS_SHIFT                                                                         (9U)
#define I2C_IRQSTATUS_RAW_AAS_MASK                                                                          (0x00000200U)
#define I2C_IRQSTATUS_RAW_AAS_CLEAR                                                                          (0U)
#define I2C_IRQSTATUS_RAW_AAS_SET                                                                            (1U)

#define I2C_IRQSTATUS_RAW_XUDF_SHIFT                                                                        (10U)
#define I2C_IRQSTATUS_RAW_XUDF_MASK                                                                         (0x00000400U)
#define I2C_IRQSTATUS_RAW_XUDF_CLEAR                                                                         (0U)
#define I2C_IRQSTATUS_RAW_XUDF_SET                                                                           (1U)

#define I2C_IRQSTATUS_RAW_ROVR_SHIFT                                                                        (11U)
#define I2C_IRQSTATUS_RAW_ROVR_MASK                                                                         (0x00000800U)
#define I2C_IRQSTATUS_RAW_ROVR_CLEAR                                                                         (0U)
#define I2C_IRQSTATUS_RAW_ROVR_SET                                                                           (1U)

#define I2C_IRQSTATUS_RAW_BB_SHIFT                                                                          (12U)
#define I2C_IRQSTATUS_RAW_BB_MASK                                                                           (0x00001000U)
#define I2C_IRQSTATUS_RAW_BB_CLEAR                                                                           (0U)
#define I2C_IRQSTATUS_RAW_BB_SET                                                                             (1U)

#define I2C_IRQSTATUS_RAW_RDR_SHIFT                                                                         (13U)
#define I2C_IRQSTATUS_RAW_RDR_MASK                                                                          (0x00002000U)
#define I2C_IRQSTATUS_RAW_RDR_CLEAR                                                                          (0U)
#define I2C_IRQSTATUS_RAW_RDR_SET                                                                            (1U)

#define I2C_IRQSTATUS_RAW_XDR_SHIFT                                                                         (14U)
#define I2C_IRQSTATUS_RAW_XDR_MASK                                                                          (0x00004000U)
#define I2C_IRQSTATUS_RAW_XDR_CLEAR                                                                          (0U)
#define I2C_IRQSTATUS_RAW_XDR_SET                                                                            (1U)

#define I2C_IRQSTATUS_RAW_RESERVED_11_SHIFT                                                                 (15U)
#define I2C_IRQSTATUS_RAW_RESERVED_11_MASK                                                                  (0x00008000U)

#define I2C_IRQSTATUS_AL_SHIFT                                                                              (0U)
#define I2C_IRQSTATUS_AL_MASK                                                                               (0x00000001U)
#define I2C_IRQSTATUS_AL_CLEAR                                                                               (0U)
#define I2C_IRQSTATUS_AL_SET                                                                                 (1U)

#define I2C_IRQSTATUS_NACK_SHIFT                                                                            (1U)
#define I2C_IRQSTATUS_NACK_MASK                                                                             (0x00000002U)
#define I2C_IRQSTATUS_NACK_CLEAR                                                                             (0U)
#define I2C_IRQSTATUS_NACK_SET                                                                               (1U)

#define I2C_IRQSTATUS_ARDY_SHIFT                                                                            (2U)
#define I2C_IRQSTATUS_ARDY_MASK                                                                             (0x00000004U)
#define I2C_IRQSTATUS_ARDY_CLEAR                                                                             (0U)
#define I2C_IRQSTATUS_ARDY_SET                                                                               (1U)

#define I2C_IRQSTATUS_RRDY_SHIFT                                                                            (3U)
#define I2C_IRQSTATUS_RRDY_MASK                                                                             (0x00000008U)
#define I2C_IRQSTATUS_RRDY_CLEAR                                                                             (0U)
#define I2C_IRQSTATUS_RRDY_SET                                                                               (1U)

#define I2C_IRQSTATUS_XRDY_SHIFT                                                                            (4U)
#define I2C_IRQSTATUS_XRDY_MASK                                                                             (0x00000010U)
#define I2C_IRQSTATUS_XRDY_CLEAR                                                                             (0U)
#define I2C_IRQSTATUS_XRDY_SET                                                                               (1U)

#define I2C_IRQSTATUS_GC_SHIFT                                                                              (5U)
#define I2C_IRQSTATUS_GC_MASK                                                                               (0x00000020U)
#define I2C_IRQSTATUS_GC_CLEAR                                                                               (0U)
#define I2C_IRQSTATUS_GC_SET                                                                                 (1U)

#define I2C_IRQSTATUS_STC_SHIFT                                                                             (6U)
#define I2C_IRQSTATUS_STC_MASK                                                                              (0x00000040U)
#define I2C_IRQSTATUS_STC_CLEAR                                                                              (0U)
#define I2C_IRQSTATUS_STC_SET                                                                                (1U)

#define I2C_IRQSTATUS_AERR_SHIFT                                                                            (7U)
#define I2C_IRQSTATUS_AERR_MASK                                                                             (0x00000080U)
#define I2C_IRQSTATUS_AERR_CLEAR                                                                             (0U)
#define I2C_IRQSTATUS_AERR_SET                                                                               (1U)

#define I2C_IRQSTATUS_BF_SHIFT                                                                              (8U)
#define I2C_IRQSTATUS_BF_MASK                                                                               (0x00000100U)
#define I2C_IRQSTATUS_BF_CLEAR                                                                               (0U)
#define I2C_IRQSTATUS_BF_SET                                                                                 (1U)

#define I2C_IRQSTATUS_AAS_SHIFT                                                                             (9U)
#define I2C_IRQSTATUS_AAS_MASK                                                                              (0x00000200U)
#define I2C_IRQSTATUS_AAS_CLEAR                                                                              (0U)
#define I2C_IRQSTATUS_AAS_SET                                                                                (1U)

#define I2C_IRQSTATUS_XUDF_SHIFT                                                                            (10U)
#define I2C_IRQSTATUS_XUDF_MASK                                                                             (0x00000400U)
#define I2C_IRQSTATUS_XUDF_CLEAR                                                                             (0U)
#define I2C_IRQSTATUS_XUDF_SET                                                                               (1U)

#define I2C_IRQSTATUS_ROVR_SHIFT                                                                            (11U)
#define I2C_IRQSTATUS_ROVR_MASK                                                                             (0x00000800U)
#define I2C_IRQSTATUS_ROVR_CLEAR                                                                             (0U)
#define I2C_IRQSTATUS_ROVR_SET                                                                               (1U)

#define I2C_IRQSTATUS_BB_SHIFT                                                                              (12U)
#define I2C_IRQSTATUS_BB_MASK                                                                               (0x00001000U)
#define I2C_IRQSTATUS_BB_CLEAR                                                                               (0U)
#define I2C_IRQSTATUS_BB_SET                                                                                 (1U)

#define I2C_IRQSTATUS_RDR_SHIFT                                                                             (13U)
#define I2C_IRQSTATUS_RDR_MASK                                                                              (0x00002000U)
#define I2C_IRQSTATUS_RDR_CLEAR                                                                              (0U)
#define I2C_IRQSTATUS_RDR_SET                                                                                (1U)

#define I2C_IRQSTATUS_XDR_SHIFT                                                                             (14U)
#define I2C_IRQSTATUS_XDR_MASK                                                                              (0x00004000U)
#define I2C_IRQSTATUS_XDR_CLEAR                                                                              (0U)
#define I2C_IRQSTATUS_XDR_SET                                                                                (1U)

#define I2C_IRQSTATUS_RESERVED_11_SHIFT                                                                     (15U)
#define I2C_IRQSTATUS_RESERVED_11_MASK                                                                      (0x00008000U)

#define I2C_IRQENABLE_SET_AL_IE_SHIFT                                                                       (0U)
#define I2C_IRQENABLE_SET_AL_IE_MASK                                                                        (0x00000001U)
#define I2C_IRQENABLE_SET_AL_IE_DISABLE                                                                      (0U)
#define I2C_IRQENABLE_SET_AL_IE_ENABLE                                                                       (1U)

#define I2C_IRQENABLE_SET_NACK_IE_SHIFT                                                                     (1U)
#define I2C_IRQENABLE_SET_NACK_IE_MASK                                                                      (0x00000002U)
#define I2C_IRQENABLE_SET_NACK_IE_DISABLE                                                                    (0U)
#define I2C_IRQENABLE_SET_NACK_IE_ENABLE                                                                     (1U)

#define I2C_IRQENABLE_SET_ARDY_IE_SHIFT                                                                     (2U)
#define I2C_IRQENABLE_SET_ARDY_IE_MASK                                                                      (0x00000004U)
#define I2C_IRQENABLE_SET_ARDY_IE_DISABLE                                                                    (0U)
#define I2C_IRQENABLE_SET_ARDY_IE_ENABLE                                                                     (1U)

#define I2C_IRQENABLE_SET_RRDY_IE_SHIFT                                                                     (3U)
#define I2C_IRQENABLE_SET_RRDY_IE_MASK                                                                      (0x00000008U)
#define I2C_IRQENABLE_SET_RRDY_IE_DISABLE                                                                    (0U)
#define I2C_IRQENABLE_SET_RRDY_IE_ENABLE                                                                     (1U)

#define I2C_IRQENABLE_SET_XRDY_IE_SHIFT                                                                     (4U)
#define I2C_IRQENABLE_SET_XRDY_IE_MASK                                                                      (0x00000010U)
#define I2C_IRQENABLE_SET_XRDY_IE_DISABLE                                                                    (0U)
#define I2C_IRQENABLE_SET_XRDY_IE_ENABLE                                                                     (1U)

#define I2C_IRQENABLE_SET_GC_IE_SHIFT                                                                       (5U)
#define I2C_IRQENABLE_SET_GC_IE_MASK                                                                        (0x00000020U)
#define I2C_IRQENABLE_SET_GC_IE_DISABLE                                                                      (0U)
#define I2C_IRQENABLE_SET_GC_IE_ENABLE                                                                       (1U)

#define I2C_IRQENABLE_SET_STC_IE_SHIFT                                                                      (6U)
#define I2C_IRQENABLE_SET_STC_IE_MASK                                                                       (0x00000040U)
#define I2C_IRQENABLE_SET_STC_IE_DISABLE                                                                     (0U)
#define I2C_IRQENABLE_SET_STC_IE_ENABLE                                                                      (1U)

#define I2C_IRQENABLE_SET_AERR_IE_SHIFT                                                                     (7U)
#define I2C_IRQENABLE_SET_AERR_IE_MASK                                                                      (0x00000080U)
#define I2C_IRQENABLE_SET_AERR_IE_DISABLE                                                                    (0U)
#define I2C_IRQENABLE_SET_AERR_IE_ENABLE                                                                     (1U)

#define I2C_IRQENABLE_SET_BF_IE_SHIFT                                                                       (8U)
#define I2C_IRQENABLE_SET_BF_IE_MASK                                                                        (0x00000100U)
#define I2C_IRQENABLE_SET_BF_IE_DISABLE                                                                      (0U)
#define I2C_IRQENABLE_SET_BF_IE_ENABLE                                                                       (1U)

#define I2C_IRQENABLE_SET_ASS_IE_SHIFT                                                                      (9U)
#define I2C_IRQENABLE_SET_ASS_IE_MASK                                                                       (0x00000200U)
#define I2C_IRQENABLE_SET_ASS_IE_DISABLE                                                                     (0U)
#define I2C_IRQENABLE_SET_ASS_IE_ENABLE                                                                      (1U)

#define I2C_IRQENABLE_SET_XUDF_SHIFT                                                                        (10U)
#define I2C_IRQENABLE_SET_XUDF_MASK                                                                         (0x00000400U)
#define I2C_IRQENABLE_SET_XUDF_DISABLE                                                                       (0U)
#define I2C_IRQENABLE_SET_XUDF_ENABLE                                                                        (1U)

#define I2C_IRQENABLE_SET_ROVR_SHIFT                                                                        (11U)
#define I2C_IRQENABLE_SET_ROVR_MASK                                                                         (0x00000800U)
#define I2C_IRQENABLE_SET_ROVR_DISABLE                                                                       (0U)
#define I2C_IRQENABLE_SET_ROVR_ENABLE                                                                        (1U)

#define I2C_IRQENABLE_SET_RESERVED1_SHIFT                                                                   (12U)
#define I2C_IRQENABLE_SET_RESERVED1_MASK                                                                    (0x00001000U)

#define I2C_IRQENABLE_SET_RDR_IE_SHIFT                                                                      (13U)
#define I2C_IRQENABLE_SET_RDR_IE_MASK                                                                       (0x00002000U)
#define I2C_IRQENABLE_SET_RDR_IE_DISABLE                                                                     (0U)
#define I2C_IRQENABLE_SET_RDR_IE_ENABLE                                                                      (1U)

#define I2C_IRQENABLE_SET_XDR_IE_SHIFT                                                                      (14U)
#define I2C_IRQENABLE_SET_XDR_IE_MASK                                                                       (0x00004000U)
#define I2C_IRQENABLE_SET_XDR_IE_DISABLE                                                                     (0U)
#define I2C_IRQENABLE_SET_XDR_IE_ENABLE                                                                      (1U)

#define I2C_IRQENABLE_SET_RESERVED_5_SHIFT                                                                  (15U)
#define I2C_IRQENABLE_SET_RESERVED_5_MASK                                                                   (0x00008000U)

#define I2C_IRQENABLE_CLR_AL_IE_SHIFT                                                                       (0U)
#define I2C_IRQENABLE_CLR_AL_IE_MASK                                                                        (0x00000001U)
#define I2C_IRQENABLE_CLR_AL_IE_DISABLE                                                                      (0U)
#define I2C_IRQENABLE_CLR_AL_IE_ENABLE                                                                       (1U)

#define I2C_IRQENABLE_CLR_NACK_IE_SHIFT                                                                     (1U)
#define I2C_IRQENABLE_CLR_NACK_IE_MASK                                                                      (0x00000002U)
#define I2C_IRQENABLE_CLR_NACK_IE_DISABLE                                                                    (0U)
#define I2C_IRQENABLE_CLR_NACK_IE_ENABLE                                                                     (1U)

#define I2C_IRQENABLE_CLR_ARDY_IE_SHIFT                                                                     (2U)
#define I2C_IRQENABLE_CLR_ARDY_IE_MASK                                                                      (0x00000004U)
#define I2C_IRQENABLE_CLR_ARDY_IE_DISABLE                                                                    (0U)
#define I2C_IRQENABLE_CLR_ARDY_IE_ENABLE                                                                     (1U)

#define I2C_IRQENABLE_CLR_RRDY_IE_SHIFT                                                                     (3U)
#define I2C_IRQENABLE_CLR_RRDY_IE_MASK                                                                      (0x00000008U)
#define I2C_IRQENABLE_CLR_RRDY_IE_DISABLE                                                                    (0U)
#define I2C_IRQENABLE_CLR_RRDY_IE_ENABLE                                                                     (1U)

#define I2C_IRQENABLE_CLR_XRDY_IE_SHIFT                                                                     (4U)
#define I2C_IRQENABLE_CLR_XRDY_IE_MASK                                                                      (0x00000010U)
#define I2C_IRQENABLE_CLR_XRDY_IE_DISABLE                                                                    (0U)
#define I2C_IRQENABLE_CLR_XRDY_IE_ENABLE                                                                     (1U)

#define I2C_IRQENABLE_CLR_GC_IE_SHIFT                                                                       (5U)
#define I2C_IRQENABLE_CLR_GC_IE_MASK                                                                        (0x00000020U)
#define I2C_IRQENABLE_CLR_GC_IE_DISABLE                                                                      (0U)
#define I2C_IRQENABLE_CLR_GC_IE_ENABLE                                                                       (1U)

#define I2C_IRQENABLE_CLR_STC_IE_SHIFT                                                                      (6U)
#define I2C_IRQENABLE_CLR_STC_IE_MASK                                                                       (0x00000040U)
#define I2C_IRQENABLE_CLR_STC_IE_DISABLE                                                                     (0U)
#define I2C_IRQENABLE_CLR_STC_IE_ENABLE                                                                      (1U)

#define I2C_IRQENABLE_CLR_AERR_IE_SHIFT                                                                     (7U)
#define I2C_IRQENABLE_CLR_AERR_IE_MASK                                                                      (0x00000080U)
#define I2C_IRQENABLE_CLR_AERR_IE_DISABLE                                                                    (0U)
#define I2C_IRQENABLE_CLR_AERR_IE_ENABLE                                                                     (1U)

#define I2C_IRQENABLE_CLR_BF_IE_SHIFT                                                                       (8U)
#define I2C_IRQENABLE_CLR_BF_IE_MASK                                                                        (0x00000100U)
#define I2C_IRQENABLE_CLR_BF_IE_DISABLE                                                                      (0U)
#define I2C_IRQENABLE_CLR_BF_IE_ENABLE                                                                       (1U)

#define I2C_IRQENABLE_CLR_ASS_IE_SHIFT                                                                      (9U)
#define I2C_IRQENABLE_CLR_ASS_IE_MASK                                                                       (0x00000200U)
#define I2C_IRQENABLE_CLR_ASS_IE_DISABLE                                                                     (0U)
#define I2C_IRQENABLE_CLR_ASS_IE_ENABLE                                                                      (1U)

#define I2C_IRQENABLE_CLR_XUDF_SHIFT                                                                        (10U)
#define I2C_IRQENABLE_CLR_XUDF_MASK                                                                         (0x00000400U)
#define I2C_IRQENABLE_CLR_XUDF_DISABLE                                                                       (0U)
#define I2C_IRQENABLE_CLR_XUDF_ENABLE                                                                        (1U)

#define I2C_IRQENABLE_CLR_ROVR_SHIFT                                                                        (11U)
#define I2C_IRQENABLE_CLR_ROVR_MASK                                                                         (0x00000800U)
#define I2C_IRQENABLE_CLR_ROVR_DISABLE                                                                       (0U)
#define I2C_IRQENABLE_CLR_ROVR_ENABLE                                                                        (1U)

#define I2C_IRQENABLE_CLR_RESERVED1_SHIFT                                                                   (12U)
#define I2C_IRQENABLE_CLR_RESERVED1_MASK                                                                    (0x00001000U)

#define I2C_IRQENABLE_CLR_RDR_IE_SHIFT                                                                      (13U)
#define I2C_IRQENABLE_CLR_RDR_IE_MASK                                                                       (0x00002000U)
#define I2C_IRQENABLE_CLR_RDR_IE_DISABLE                                                                     (0U)
#define I2C_IRQENABLE_CLR_RDR_IE_ENABLE                                                                      (1U)

#define I2C_IRQENABLE_CLR_XDR_IE_SHIFT                                                                      (14U)
#define I2C_IRQENABLE_CLR_XDR_IE_MASK                                                                       (0x00004000U)
#define I2C_IRQENABLE_CLR_XDR_IE_DISABLE                                                                     (0U)
#define I2C_IRQENABLE_CLR_XDR_IE_ENABLE                                                                      (1U)

#define I2C_IRQENABLE_CLR_RESERVED_5_SHIFT                                                                  (15U)
#define I2C_IRQENABLE_CLR_RESERVED_5_MASK                                                                   (0x00008000U)

#define I2C_WE_AL_SHIFT                                                                                     (0U)
#define I2C_WE_AL_MASK                                                                                      (0x00000001U)
#define I2C_WE_AL_ENABLE                                                                                     (1U)
#define I2C_WE_AL_DISABLE                                                                                    (0U)

#define I2C_WE_NACK_SHIFT                                                                                   (1U)
#define I2C_WE_NACK_MASK                                                                                    (0x00000002U)
#define I2C_WE_NACK_DISABLE                                                                                  (0U)
#define I2C_WE_NACK_ENABLE                                                                                   (1U)

#define I2C_WE_ARDY_SHIFT                                                                                   (2U)
#define I2C_WE_ARDY_MASK                                                                                    (0x00000004U)
#define I2C_WE_ARDY_ENABLE                                                                                   (1U)
#define I2C_WE_ARDY_DISABLE                                                                                  (0U)

#define I2C_WE_DRDY_SHIFT                                                                                   (3U)
#define I2C_WE_DRDY_MASK                                                                                    (0x00000008U)
#define I2C_WE_DRDY_DISABLE                                                                                  (0U)
#define I2C_WE_DRDY_ENABLE                                                                                   (1U)

#define I2C_WE_RESERVED1_SHIFT                                                                              (4U)
#define I2C_WE_RESERVED1_MASK                                                                               (0x00000010U)

#define I2C_WE_GC_SHIFT                                                                                     (5U)
#define I2C_WE_GC_MASK                                                                                      (0x00000020U)
#define I2C_WE_GC_DISABLE                                                                                    (0U)
#define I2C_WE_GC_ENABLE                                                                                     (1U)

#define I2C_WE_STC_SHIFT                                                                                    (6U)
#define I2C_WE_STC_MASK                                                                                     (0x00000040U)
#define I2C_WE_STC_DISABLE                                                                                   (0U)
#define I2C_WE_STC_ENABLE                                                                                    (1U)

#define I2C_WE_RESERVED2_SHIFT                                                                              (7U)
#define I2C_WE_RESERVED2_MASK                                                                               (0x00000080U)

#define I2C_WE_BF_SHIFT                                                                                     (8U)
#define I2C_WE_BF_MASK                                                                                      (0x00000100U)
#define I2C_WE_BF_DISABLE                                                                                    (0U)
#define I2C_WE_BF_ENABLE                                                                                     (1U)

#define I2C_WE_AAS_SHIFT                                                                                    (9U)
#define I2C_WE_AAS_MASK                                                                                     (0x00000200U)
#define I2C_WE_AAS_DISABLE                                                                                   (0U)
#define I2C_WE_AAS_ENABLE                                                                                    (1U)

#define I2C_WE_XUDF_SHIFT                                                                                   (10U)
#define I2C_WE_XUDF_MASK                                                                                    (0x00000400U)
#define I2C_WE_XUDF_DISABLE                                                                                  (0U)
#define I2C_WE_XUDF_ENABLE                                                                                   (1U)

#define I2C_WE_ROVR_SHIFT                                                                                   (11U)
#define I2C_WE_ROVR_MASK                                                                                    (0x00000800U)
#define I2C_WE_ROVR_DISABLE                                                                                  (0U)
#define I2C_WE_ROVR_ENABLE                                                                                   (1U)

#define I2C_WE_RESERVED3_SHIFT                                                                              (12U)
#define I2C_WE_RESERVED3_MASK                                                                               (0x00001000U)

#define I2C_WE_RDR_SHIFT                                                                                    (13U)
#define I2C_WE_RDR_MASK                                                                                     (0x00002000U)
#define I2C_WE_RDR_DISABLE                                                                                   (0U)
#define I2C_WE_RDR_ENABLE                                                                                    (1U)

#define I2C_WE_XDR_SHIFT                                                                                    (14U)
#define I2C_WE_XDR_MASK                                                                                     (0x00004000U)
#define I2C_WE_XDR_DISABLE                                                                                   (0U)
#define I2C_WE_XDR_ENABLE                                                                                    (1U)

#define I2C_WE_RESERVED_SHIFT                                                                               (15U)
#define I2C_WE_RESERVED_MASK                                                                                (0x00008000U)

#define I2C_DMARXENABLE_SET_DMARX_ENABLE_SET_SHIFT                                                          (0U)
#define I2C_DMARXENABLE_SET_DMARX_ENABLE_SET_MASK                                                           (0x00000001U)

#define I2C_DMARXENABLE_SET_RESERVED_SHIFT                                                                  (1U)
#define I2C_DMARXENABLE_SET_RESERVED_MASK                                                                   (0x0000fffeU)

#define I2C_DMATXENABLE_SET_DMATX_ENABLE_SET_SHIFT                                                          (0U)
#define I2C_DMATXENABLE_SET_DMATX_ENABLE_SET_MASK                                                           (0x00000001U)

#define I2C_DMATXENABLE_SET_RESERVED_SHIFT                                                                  (1U)
#define I2C_DMATXENABLE_SET_RESERVED_MASK                                                                   (0x0000fffeU)

#define I2C_DMARXENABLE_CLR_DMARX_ENABLE_CLEAR_SHIFT                                                        (0U)
#define I2C_DMARXENABLE_CLR_DMARX_ENABLE_CLEAR_MASK                                                         (0x00000001U)

#define I2C_DMARXENABLE_CLR_RESERVED_SHIFT                                                                  (1U)
#define I2C_DMARXENABLE_CLR_RESERVED_MASK                                                                   (0x0000fffeU)

#define I2C_DMATXENABLE_CLR_DMATX_ENABLE_CLEAR_SHIFT                                                        (0U)
#define I2C_DMATXENABLE_CLR_DMATX_ENABLE_CLEAR_MASK                                                         (0x00000001U)

#define I2C_DMATXENABLE_CLR_RESERVED_SHIFT                                                                  (1U)
#define I2C_DMATXENABLE_CLR_RESERVED_MASK                                                                   (0x0000fffeU)

#define I2C_DMARXWAKE_EN_AL_SHIFT                                                                           (0U)
#define I2C_DMARXWAKE_EN_AL_MASK                                                                            (0x00000001U)
#define I2C_DMARXWAKE_EN_AL_ENABLE                                                                           (1U)
#define I2C_DMARXWAKE_EN_AL_DISABLE                                                                          (0U)

#define I2C_DMARXWAKE_EN_NACK_SHIFT                                                                         (1U)
#define I2C_DMARXWAKE_EN_NACK_MASK                                                                          (0x00000002U)
#define I2C_DMARXWAKE_EN_NACK_DISABLE                                                                        (0U)
#define I2C_DMARXWAKE_EN_NACK_ENABLE                                                                         (1U)

#define I2C_DMARXWAKE_EN_ARDY_SHIFT                                                                         (2U)
#define I2C_DMARXWAKE_EN_ARDY_MASK                                                                          (0x00000004U)
#define I2C_DMARXWAKE_EN_ARDY_ENABLE                                                                         (1U)
#define I2C_DMARXWAKE_EN_ARDY_DISABLE                                                                        (0U)

#define I2C_DMARXWAKE_EN_DRDY_SHIFT                                                                         (3U)
#define I2C_DMARXWAKE_EN_DRDY_MASK                                                                          (0x00000008U)
#define I2C_DMARXWAKE_EN_DRDY_DISABLE                                                                        (0U)
#define I2C_DMARXWAKE_EN_DRDY_ENABLE                                                                         (1U)

#define I2C_DMARXWAKE_EN_RESERVED1_SHIFT                                                                    (4U)
#define I2C_DMARXWAKE_EN_RESERVED1_MASK                                                                     (0x00000010U)

#define I2C_DMARXWAKE_EN_GC_SHIFT                                                                           (5U)
#define I2C_DMARXWAKE_EN_GC_MASK                                                                            (0x00000020U)
#define I2C_DMARXWAKE_EN_GC_DISABLE                                                                          (0U)
#define I2C_DMARXWAKE_EN_GC_ENABLE                                                                           (1U)

#define I2C_DMARXWAKE_EN_STC_SHIFT                                                                          (6U)
#define I2C_DMARXWAKE_EN_STC_MASK                                                                           (0x00000040U)
#define I2C_DMARXWAKE_EN_STC_DISABLE                                                                         (0U)
#define I2C_DMARXWAKE_EN_STC_ENABLE                                                                          (1U)

#define I2C_DMARXWAKE_EN_RESERVED2_SHIFT                                                                    (7U)
#define I2C_DMARXWAKE_EN_RESERVED2_MASK                                                                     (0x00000080U)

#define I2C_DMARXWAKE_EN_BF_SHIFT                                                                           (8U)
#define I2C_DMARXWAKE_EN_BF_MASK                                                                            (0x00000100U)
#define I2C_DMARXWAKE_EN_BF_DISABLE                                                                          (0U)
#define I2C_DMARXWAKE_EN_BF_ENABLE                                                                           (1U)

#define I2C_DMARXWAKE_EN_AAS_SHIFT                                                                          (9U)
#define I2C_DMARXWAKE_EN_AAS_MASK                                                                           (0x00000200U)
#define I2C_DMARXWAKE_EN_AAS_DISABLE                                                                         (0U)
#define I2C_DMARXWAKE_EN_AAS_ENABLE                                                                          (1U)

#define I2C_DMARXWAKE_EN_XUDF_SHIFT                                                                         (10U)
#define I2C_DMARXWAKE_EN_XUDF_MASK                                                                          (0x00000400U)
#define I2C_DMARXWAKE_EN_XUDF_DISABLE                                                                        (0U)
#define I2C_DMARXWAKE_EN_XUDF_ENABLE                                                                         (1U)

#define I2C_DMARXWAKE_EN_ROVR_SHIFT                                                                         (11U)
#define I2C_DMARXWAKE_EN_ROVR_MASK                                                                          (0x00000800U)
#define I2C_DMARXWAKE_EN_ROVR_DISABLE                                                                        (0U)
#define I2C_DMARXWAKE_EN_ROVR_ENABLE                                                                         (1U)

#define I2C_DMARXWAKE_EN_RESERVED3_SHIFT                                                                    (12U)
#define I2C_DMARXWAKE_EN_RESERVED3_MASK                                                                     (0x00001000U)

#define I2C_DMARXWAKE_EN_RDR_SHIFT                                                                          (13U)
#define I2C_DMARXWAKE_EN_RDR_MASK                                                                           (0x00002000U)
#define I2C_DMARXWAKE_EN_RDR_DISABLE                                                                         (0U)
#define I2C_DMARXWAKE_EN_RDR_ENABLE                                                                          (1U)

#define I2C_DMARXWAKE_EN_XDR_SHIFT                                                                          (14U)
#define I2C_DMARXWAKE_EN_XDR_MASK                                                                           (0x00004000U)
#define I2C_DMARXWAKE_EN_XDR_DISABLE                                                                         (0U)
#define I2C_DMARXWAKE_EN_XDR_ENABLE                                                                          (1U)

#define I2C_DMARXWAKE_EN_RESERVED_SHIFT                                                                     (15U)
#define I2C_DMARXWAKE_EN_RESERVED_MASK                                                                      (0x00008000U)

#define I2C_DMATXWAKE_EN_AL_SHIFT                                                                           (0U)
#define I2C_DMATXWAKE_EN_AL_MASK                                                                            (0x00000001U)
#define I2C_DMATXWAKE_EN_AL_ENABLE                                                                           (1U)
#define I2C_DMATXWAKE_EN_AL_DISABLE                                                                          (0U)

#define I2C_DMATXWAKE_EN_NACK_SHIFT                                                                         (1U)
#define I2C_DMATXWAKE_EN_NACK_MASK                                                                          (0x00000002U)
#define I2C_DMATXWAKE_EN_NACK_DISABLE                                                                        (0U)
#define I2C_DMATXWAKE_EN_NACK_ENABLE                                                                         (1U)

#define I2C_DMATXWAKE_EN_ARDY_SHIFT                                                                         (2U)
#define I2C_DMATXWAKE_EN_ARDY_MASK                                                                          (0x00000004U)
#define I2C_DMATXWAKE_EN_ARDY_ENABLE                                                                         (1U)
#define I2C_DMATXWAKE_EN_ARDY_DISABLE                                                                        (0U)

#define I2C_DMATXWAKE_EN_DRDY_SHIFT                                                                         (3U)
#define I2C_DMATXWAKE_EN_DRDY_MASK                                                                          (0x00000008U)
#define I2C_DMATXWAKE_EN_DRDY_DISABLE                                                                        (0U)
#define I2C_DMATXWAKE_EN_DRDY_ENABLE                                                                         (1U)

#define I2C_DMATXWAKE_EN_RESERVED1_SHIFT                                                                    (4U)
#define I2C_DMATXWAKE_EN_RESERVED1_MASK                                                                     (0x00000010U)

#define I2C_DMATXWAKE_EN_GC_SHIFT                                                                           (5U)
#define I2C_DMATXWAKE_EN_GC_MASK                                                                            (0x00000020U)
#define I2C_DMATXWAKE_EN_GC_DISABLE                                                                          (0U)
#define I2C_DMATXWAKE_EN_GC_ENABLE                                                                           (1U)

#define I2C_DMATXWAKE_EN_STC_SHIFT                                                                          (6U)
#define I2C_DMATXWAKE_EN_STC_MASK                                                                           (0x00000040U)
#define I2C_DMATXWAKE_EN_STC_DISABLE                                                                         (0U)
#define I2C_DMATXWAKE_EN_STC_ENABLE                                                                          (1U)

#define I2C_DMATXWAKE_EN_RESERVED2_SHIFT                                                                    (7U)
#define I2C_DMATXWAKE_EN_RESERVED2_MASK                                                                     (0x00000080U)

#define I2C_DMATXWAKE_EN_BF_SHIFT                                                                           (8U)
#define I2C_DMATXWAKE_EN_BF_MASK                                                                            (0x00000100U)
#define I2C_DMATXWAKE_EN_BF_DISABLE                                                                          (0U)
#define I2C_DMATXWAKE_EN_BF_ENABLE                                                                           (1U)

#define I2C_DMATXWAKE_EN_AAS_SHIFT                                                                          (9U)
#define I2C_DMATXWAKE_EN_AAS_MASK                                                                           (0x00000200U)
#define I2C_DMATXWAKE_EN_AAS_DISABLE                                                                         (0U)
#define I2C_DMATXWAKE_EN_AAS_ENABLE                                                                          (1U)

#define I2C_DMATXWAKE_EN_XUDF_SHIFT                                                                         (10U)
#define I2C_DMATXWAKE_EN_XUDF_MASK                                                                          (0x00000400U)
#define I2C_DMATXWAKE_EN_XUDF_DISABLE                                                                        (0U)
#define I2C_DMATXWAKE_EN_XUDF_ENABLE                                                                         (1U)

#define I2C_DMATXWAKE_EN_ROVR_SHIFT                                                                         (11U)
#define I2C_DMATXWAKE_EN_ROVR_MASK                                                                          (0x00000800U)
#define I2C_DMATXWAKE_EN_ROVR_DISABLE                                                                        (0U)
#define I2C_DMATXWAKE_EN_ROVR_ENABLE                                                                         (1U)

#define I2C_DMATXWAKE_EN_RESERVED3_SHIFT                                                                    (12U)
#define I2C_DMATXWAKE_EN_RESERVED3_MASK                                                                     (0x00001000U)

#define I2C_DMATXWAKE_EN_RDR_SHIFT                                                                          (13U)
#define I2C_DMATXWAKE_EN_RDR_MASK                                                                           (0x00002000U)
#define I2C_DMATXWAKE_EN_RDR_DISABLE                                                                         (0U)
#define I2C_DMATXWAKE_EN_RDR_ENABLE                                                                          (1U)

#define I2C_DMATXWAKE_EN_XDR_SHIFT                                                                          (14U)
#define I2C_DMATXWAKE_EN_XDR_MASK                                                                           (0x00004000U)
#define I2C_DMATXWAKE_EN_XDR_DISABLE                                                                         (0U)
#define I2C_DMATXWAKE_EN_XDR_ENABLE                                                                          (1U)

#define I2C_DMATXWAKE_EN_RESERVED_SHIFT                                                                     (15U)
#define I2C_DMATXWAKE_EN_RESERVED_MASK                                                                      (0x00008000U)

#define I2C_SYSS_RDONE_SHIFT                                                                                (0U)
#define I2C_SYSS_RDONE_MASK                                                                                 (0x00000001U)
#define I2C_SYSS_RDONE_RSTONGOING                                                                            (0U)
#define I2C_SYSS_RDONE_RSTCOMP                                                                               (1U)

#define I2C_SYSS_RESERVED_SHIFT                                                                             (1U)
#define I2C_SYSS_RESERVED_MASK                                                                              (0x0000fffeU)

#define I2C_BUF_TXTRSH_SHIFT                                                                                (0U)
#define I2C_BUF_TXTRSH_MASK                                                                                 (0x0000003fU)

#define I2C_BUF_TXFIFO_CLR_SHIFT                                                                            (6U)
#define I2C_BUF_TXFIFO_CLR_MASK                                                                             (0x00000040U)
#define I2C_BUF_TXFIFO_CLR_NMODE                                                                             (0U)
#define I2C_BUF_TXFIFO_CLR_RSTMODE                                                                           (1U)

#define I2C_BUF_XDMA_EN_SHIFT                                                                               (7U)
#define I2C_BUF_XDMA_EN_MASK                                                                                (0x00000080U)
#define I2C_BUF_XDMA_EN_DISABLE                                                                              (0U)
#define I2C_BUF_XDMA_EN_ENABLE                                                                               (1U)

#define I2C_BUF_RXTRSH_SHIFT                                                                                (8U)
#define I2C_BUF_RXTRSH_MASK                                                                                 (0x00003f00U)

#define I2C_BUF_RXFIFO_CLR_SHIFT                                                                            (14U)
#define I2C_BUF_RXFIFO_CLR_MASK                                                                             (0x00004000U)
#define I2C_BUF_RXFIFO_CLR_NMODE                                                                             (0U)
#define I2C_BUF_RXFIFO_CLR_RSTMODE                                                                           (1U)

#define I2C_BUF_RDMA_EN_SHIFT                                                                               (15U)
#define I2C_BUF_RDMA_EN_MASK                                                                                (0x00008000U)
#define I2C_BUF_RDMA_EN_DISABLE                                                                              (0U)
#define I2C_BUF_RDMA_EN_ENABLE                                                                               (1U)

#define I2C_CNT_DCOUNT_SHIFT                                                                                (0U)
#define I2C_CNT_DCOUNT_MASK                                                                                 (0x0000ffffU)

#define I2C_DATA_DATA_SHIFT                                                                                 (0U)
#define I2C_DATA_DATA_MASK                                                                                  (0x000000ffU)

#define I2C_DATA_RESERVED_SHIFT                                                                             (8U)
#define I2C_DATA_RESERVED_MASK                                                                              (0x0000ff00U)

#define I2C_CON_STT_SHIFT                                                                                   (0U)
#define I2C_CON_STT_MASK                                                                                    (0x00000001U)
#define I2C_CON_STT_NSTT                                                                                     (0U)
#define I2C_CON_STT_STT                                                                                      (1U)

#define I2C_CON_STP_SHIFT                                                                                   (1U)
#define I2C_CON_STP_MASK                                                                                    (0x00000002U)
#define I2C_CON_STP_NSTP                                                                                     (0U)
#define I2C_CON_STP_STP                                                                                      (1U)

#define I2C_CON_RESERVED1_SHIFT                                                                             (2U)
#define I2C_CON_RESERVED1_MASK                                                                              (0x0000000cU)

#define I2C_CON_XOA3_SHIFT                                                                                  (4U)
#define I2C_CON_XOA3_MASK                                                                                   (0x00000010U)
#define I2C_CON_XOA3_B07                                                                                     (0U)
#define I2C_CON_XOA3_B10                                                                                     (1U)

#define I2C_CON_XOA2_SHIFT                                                                                  (5U)
#define I2C_CON_XOA2_MASK                                                                                   (0x00000020U)
#define I2C_CON_XOA2_B07                                                                                     (0U)
#define I2C_CON_XOA2_B10                                                                                     (1U)

#define I2C_CON_XOA1_SHIFT                                                                                  (6U)
#define I2C_CON_XOA1_MASK                                                                                   (0x00000040U)
#define I2C_CON_XOA1_B07                                                                                     (0U)
#define I2C_CON_XOA1_B10                                                                                     (1U)

#define I2C_CON_XOA0_SHIFT                                                                                  (7U)
#define I2C_CON_XOA0_MASK                                                                                   (0x00000080U)
#define I2C_CON_XOA0_B07                                                                                     (0U)
#define I2C_CON_XOA0_B10                                                                                     (1U)

#define I2C_CON_XSA_SHIFT                                                                                   (8U)
#define I2C_CON_XSA_MASK                                                                                    (0x00000100U)
#define I2C_CON_XSA_B07                                                                                      (0U)
#define I2C_CON_XSA_B10                                                                                      (1U)

#define I2C_CON_TRX_SHIFT                                                                                   (9U)
#define I2C_CON_TRX_MASK                                                                                    (0x00000200U)
#define I2C_CON_TRX_RCV                                                                                      (0U)
#define I2C_CON_TRX_TRX                                                                                      (1U)

#define I2C_CON_MST_SHIFT                                                                                   (10U)
#define I2C_CON_MST_MASK                                                                                    (0x00000400U)
#define I2C_CON_MST_SLV                                                                                      (0U)
#define I2C_CON_MST_MST                                                                                      (1U)

#define I2C_CON_STB_SHIFT                                                                                   (11U)
#define I2C_CON_STB_MASK                                                                                    (0x00000800U)
#define I2C_CON_STB_NORMAL                                                                                   (0U)
#define I2C_CON_STB_STB                                                                                      (1U)

#define I2C_CON_OPMODE_SHIFT                                                                                (12U)
#define I2C_CON_OPMODE_MASK                                                                                 (0x00003000U)
#define I2C_CON_OPMODE_FSI2C                                                                                 (0U)
#define I2C_CON_OPMODE_HSI2C                                                                                 (1U)
#define I2C_CON_OPMODE_SCCB                                                                                  (2U)
#define I2C_CON_OPMODE_RESERVED                                                                              (3U)

#define I2C_CON_RESERVED_SHIFT                                                                              (14U)
#define I2C_CON_RESERVED_MASK                                                                               (0x00004000U)

#define I2C_CON_I2C_EN_SHIFT                                                                                (15U)
#define I2C_CON_I2C_EN_MASK                                                                                 (0x00008000U)
#define I2C_CON_I2C_EN_DISABLE                                                                               (0U)
#define I2C_CON_I2C_EN_ENABLE                                                                                (1U)

#define I2C_OA_OA_SHIFT                                                                                     (0U)
#define I2C_OA_OA_MASK                                                                                      (0x000003ffU)

#define I2C_OA_RESERVED_SHIFT                                                                               (10U)
#define I2C_OA_RESERVED_MASK                                                                                (0x00001c00U)

#define I2C_OA_MCODE_SHIFT                                                                                  (13U)
#define I2C_OA_MCODE_MASK                                                                                   (0x0000e000U)

#define I2C_SA_SA_SHIFT                                                                                     (0U)
#define I2C_SA_SA_MASK                                                                                      (0x000003ffU)

#define I2C_SA_RESERVED_SHIFT                                                                               (10U)
#define I2C_SA_RESERVED_MASK                                                                                (0x0000fc00U)

#define I2C_PSC_PSC_SHIFT                                                                                   (0U)
#define I2C_PSC_PSC_MASK                                                                                    (0x000000ffU)

#define I2C_PSC_RESERVED_SHIFT                                                                              (8U)
#define I2C_PSC_RESERVED_MASK                                                                               (0x0000ff00U)

#define I2C_SCLL_SCLL_SHIFT                                                                                 (0U)
#define I2C_SCLL_SCLL_MASK                                                                                  (0x000000ffU)

#define I2C_SCLL_HSSCLL_SHIFT                                                                               (8U)
#define I2C_SCLL_HSSCLL_MASK                                                                                (0x0000ff00U)

#define I2C_SCLH_SCLH_SHIFT                                                                                 (0U)
#define I2C_SCLH_SCLH_MASK                                                                                  (0x000000ffU)

#define I2C_SCLH_HSSCLH_SHIFT                                                                               (8U)
#define I2C_SCLH_HSSCLH_MASK                                                                                (0x0000ff00U)

#define I2C_SYSTEST_SDA_O_SHIFT                                                                             (0U)
#define I2C_SYSTEST_SDA_O_MASK                                                                              (0x00000001U)
#define I2C_SYSTEST_SDA_O_SDAOL                                                                              (0U)
#define I2C_SYSTEST_SDA_O_SDAOH                                                                              (1U)

#define I2C_SYSTEST_SDA_I_SHIFT                                                                             (1U)
#define I2C_SYSTEST_SDA_I_MASK                                                                              (0x00000002U)
#define I2C_SYSTEST_SDA_I_SDAIL                                                                              (0U)
#define I2C_SYSTEST_SDA_I_SDAIH                                                                              (1U)

#define I2C_SYSTEST_SCL_O_SHIFT                                                                             (2U)
#define I2C_SYSTEST_SCL_O_MASK                                                                              (0x00000004U)
#define I2C_SYSTEST_SCL_O_SCLOL                                                                              (0U)
#define I2C_SYSTEST_SCL_O_SCLOH                                                                              (1U)

#define I2C_SYSTEST_SDA_O_FUNC_SHIFT                                                                        (5U)
#define I2C_SYSTEST_SDA_O_FUNC_MASK                                                                         (0x00000020U)
#define I2C_SYSTEST_SDA_O_FUNC_SDAOL                                                                         (0U)
#define I2C_SYSTEST_SDA_O_FUNC_SDAOH                                                                         (1U)

#define I2C_SYSTEST_SDA_I_FUNC_SHIFT                                                                        (6U)
#define I2C_SYSTEST_SDA_I_FUNC_MASK                                                                         (0x00000040U)
#define I2C_SYSTEST_SDA_I_FUNC_SDAIL                                                                         (0U)
#define I2C_SYSTEST_SDA_I_FUNC_SDAIH                                                                         (1U)

#define I2C_SYSTEST_SCL_O_FUNC_SHIFT                                                                        (7U)
#define I2C_SYSTEST_SCL_O_FUNC_MASK                                                                         (0x00000080U)
#define I2C_SYSTEST_SCL_O_FUNC_SCLIL                                                                         (0U)
#define I2C_SYSTEST_SCL_O_FUNC_SCLIH                                                                         (1U)

#define I2C_SYSTEST_SCL_I_FUNC_SHIFT                                                                        (8U)
#define I2C_SYSTEST_SCL_I_FUNC_MASK                                                                         (0x00000100U)
#define I2C_SYSTEST_SCL_I_FUNC_SCLIL                                                                         (0U)
#define I2C_SYSTEST_SCL_I_FUNC_SCLIH                                                                         (1U)

#define I2C_SYSTEST_SSB_SHIFT                                                                               (11U)
#define I2C_SYSTEST_SSB_MASK                                                                                (0x00000800U)
#define I2C_SYSTEST_SSB_NOACTION                                                                             (0U)
#define I2C_SYSTEST_SSB_SETSTATUS                                                                            (1U)

#define I2C_SYSTEST_TMODE_SHIFT                                                                             (12U)
#define I2C_SYSTEST_TMODE_MASK                                                                              (0x00003000U)
#define I2C_SYSTEST_TMODE_FUNCTIONAL                                                                         (0U)
#define I2C_SYSTEST_TMODE_RESERVED                                                                           (1U)
#define I2C_SYSTEST_TMODE_TEST                                                                               (2U)
#define I2C_SYSTEST_TMODE_LOOPBACK                                                                           (3U)

#define I2C_SYSTEST_ST_EN_SHIFT                                                                             (15U)
#define I2C_SYSTEST_ST_EN_MASK                                                                              (0x00008000U)
#define I2C_SYSTEST_ST_EN_DISABLE                                                                            (0U)
#define I2C_SYSTEST_ST_EN_ENABLE                                                                             (1U)

#define I2C_SYSTEST_SCL_I_SHIFT                                                                             (3U)
#define I2C_SYSTEST_SCL_I_MASK                                                                              (0x00000008U)
#define I2C_SYSTEST_SCL_I_SCLIL                                                                              (0U)
#define I2C_SYSTEST_SCL_I_SCLIH                                                                              (1U)

#define I2C_SYSTEST_FREE_SHIFT                                                                              (14U)
#define I2C_SYSTEST_FREE_MASK                                                                               (0x00004000U)
#define I2C_SYSTEST_FREE_STOP                                                                                (0U)
#define I2C_SYSTEST_FREE_FREE                                                                                (1U)

#define I2C_SYSTEST_RESERVED_1_SHIFT                                                                        (4U)
#define I2C_SYSTEST_RESERVED_1_MASK                                                                         (0x00000010U)
#define I2C_SYSTEST_RESERVED_1_SCCBOH                                                                        (1U)
#define I2C_SYSTEST_RESERVED_1_SCCBOL                                                                        (0U)

#define I2C_SYSTEST_RESERVED_2_SHIFT                                                                        (9U)
#define I2C_SYSTEST_RESERVED_2_MASK                                                                         (0x00000600U)

#define I2C_BUFSTAT_TXSTAT_SHIFT                                                                            (0U)
#define I2C_BUFSTAT_TXSTAT_MASK                                                                             (0x0000003fU)

#define I2C_BUFSTAT_RXSTAT_SHIFT                                                                            (8U)
#define I2C_BUFSTAT_RXSTAT_MASK                                                                             (0x00003f00U)

#define I2C_BUFSTAT_RESERVED_SHIFT                                                                          (6U)
#define I2C_BUFSTAT_RESERVED_MASK                                                                           (0x000000c0U)

#define I2C_BUFSTAT_FIFODEPTH_SHIFT                                                                         (14U)
#define I2C_BUFSTAT_FIFODEPTH_MASK                                                                          (0x0000c000U)

#define I2C_OA1_OA1_SHIFT                                                                                   (0U)
#define I2C_OA1_OA1_MASK                                                                                    (0x000003ffU)

#define I2C_OA1_RESERVED_SHIFT                                                                              (10U)
#define I2C_OA1_RESERVED_MASK                                                                               (0x0000fc00U)

#define I2C_OA2_OA2_SHIFT                                                                                   (0U)
#define I2C_OA2_OA2_MASK                                                                                    (0x000003ffU)

#define I2C_OA2_RESERVED_SHIFT                                                                              (10U)
#define I2C_OA2_RESERVED_MASK                                                                               (0x0000fc00U)

#define I2C_OA3_OA3_SHIFT                                                                                   (0U)
#define I2C_OA3_OA3_MASK                                                                                    (0x000003ffU)

#define I2C_OA3_RESERVED_SHIFT                                                                              (10U)
#define I2C_OA3_RESERVED_MASK                                                                               (0x0000fc00U)

#define I2C_ACTOA_OA0_ACT_SHIFT                                                                             (0U)
#define I2C_ACTOA_OA0_ACT_MASK                                                                              (0x00000001U)
#define I2C_ACTOA_OA0_ACT_INACTIVE                                                                           (0U)
#define I2C_ACTOA_OA0_ACT_ACTIVE                                                                             (1U)

#define I2C_ACTOA_RESERVED_SHIFT                                                                            (4U)
#define I2C_ACTOA_RESERVED_MASK                                                                             (0x0000fff0U)

#define I2C_ACTOA_OA1_ACT_SHIFT                                                                             (1U)
#define I2C_ACTOA_OA1_ACT_MASK                                                                              (0x00000002U)
#define I2C_ACTOA_OA1_ACT_ACTIVE                                                                             (1U)
#define I2C_ACTOA_OA1_ACT_INACTIVE                                                                           (0U)

#define I2C_ACTOA_OA2_ACT_SHIFT                                                                             (2U)
#define I2C_ACTOA_OA2_ACT_MASK                                                                              (0x00000004U)
#define I2C_ACTOA_OA2_ACT_ACTIVE                                                                             (1U)
#define I2C_ACTOA_OA2_ACT_INACTIVE                                                                           (0U)

#define I2C_ACTOA_OA3_ACT_SHIFT                                                                             (3U)
#define I2C_ACTOA_OA3_ACT_MASK                                                                              (0x00000008U)
#define I2C_ACTOA_OA3_ACT_ACTIVE                                                                             (1U)
#define I2C_ACTOA_OA3_ACT_INACTIVE                                                                           (0U)

#define I2C_SBLOCK_OA0_EN_SHIFT                                                                             (0U)
#define I2C_SBLOCK_OA0_EN_MASK                                                                              (0x00000001U)
#define I2C_SBLOCK_OA0_EN_LOCK                                                                               (1U)
#define I2C_SBLOCK_OA0_EN_UNLOCK                                                                             (0U)

#define I2C_SBLOCK_RESERVED_SHIFT                                                                           (4U)
#define I2C_SBLOCK_RESERVED_MASK                                                                            (0x0000fff0U)

#define I2C_SBLOCK_OA1_EN_SHIFT                                                                             (1U)
#define I2C_SBLOCK_OA1_EN_MASK                                                                              (0x00000002U)
#define I2C_SBLOCK_OA1_EN_LOCK                                                                               (1U)
#define I2C_SBLOCK_OA1_EN_UNLOCK                                                                             (0U)

#define I2C_SBLOCK_OA2_EN_SHIFT                                                                             (2U)
#define I2C_SBLOCK_OA2_EN_MASK                                                                              (0x00000004U)
#define I2C_SBLOCK_OA2_EN_LOCK                                                                               (1U)
#define I2C_SBLOCK_OA2_EN_UNLOCK                                                                             (0U)

#define I2C_SBLOCK_OA3_EN_SHIFT                                                                             (3U)
#define I2C_SBLOCK_OA3_EN_MASK                                                                              (0x00000008U)
#define I2C_SBLOCK_OA3_EN_LOCK                                                                               (1U)
#define I2C_SBLOCK_OA3_EN_UNLOCK                                                                             (0U)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_I2C_H_ */
