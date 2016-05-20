/******************************************************************************
*
* hw_mcspi.h - register-level header file for MCSPI
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
#ifndef HW_MCSPI_H_
#define HW_MCSPI_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions 
****************************************************************************************************/
#define MCSPI_HL_REV                                                                                        (0x0U)
#define MCSPI_HL_HWINFO                                                                                     (0x4U)
#define MCSPI_HL_SYSCONFIG                                                                                  (0x10U)
#define MCSPI_REVISION                                                                                      (0x100U)
#define MCSPI_SYSCONFIG                                                                                     (0x110U)
#define MCSPI_SYSSTATUS                                                                                     (0x114U)
#define MCSPI_IRQSTATUS                                                                                     (0x118U)
#define MCSPI_IRQENABLE                                                                                     (0x11cU)
#define MCSPI_WAKEUPENABLE                                                                                  (0x120U)
#define MCSPI_SYST                                                                                          (0x124U)
#define MCSPI_MODULCTRL                                                                                     (0x128U)
#define MCSPI_CH0CONF                                                                                       (0x12cU)
#define MCSPI_CH0STAT                                                                                       (0x130U)
#define MCSPI_CH0CTRL                                                                                       (0x134U)
#define MCSPI_TX0                                                                                           (0x138U)
#define MCSPI_RX0                                                                                           (0x13cU)
#define MCSPI_CH1CONF                                                                                       (0x140U)
#define MCSPI_CH1STAT                                                                                       (0x144U)
#define MCSPI_CH1CTRL                                                                                       (0x148U)
#define MCSPI_TX1                                                                                           (0x14cU)
#define MCSPI_RX1                                                                                           (0x150U)
#define MCSPI_CH2CONF                                                                                       (0x154U)
#define MCSPI_CH2STAT                                                                                       (0x158U)
#define MCSPI_CH2CTRL                                                                                       (0x15cU)
#define MCSPI_TX2                                                                                           (0x160U)
#define MCSPI_RX2                                                                                           (0x164U)
#define MCSPI_CH3CONF                                                                                       (0x168U)
#define MCSPI_CH3STAT                                                                                       (0x16cU)
#define MCSPI_CH3CTRL                                                                                       (0x170U)
#define MCSPI_TX3                                                                                           (0x174U)
#define MCSPI_RX3                                                                                           (0x178U)
#define MCSPI_XFERLEVEL                                                                                     (0x17cU)

/****************************************************************************************************
* Field Definition Macros 
****************************************************************************************************/

#define MCSPI_HL_REV_REVISION_SHIFT                                                                         (0U)
#define MCSPI_HL_REV_REVISION_MASK                                                                          (0xffffffffU)

#define MCSPI_HL_HWINFO_USEFIFO_SHIFT                                                                       (0U)
#define MCSPI_HL_HWINFO_USEFIFO_MASK                                                                        (0x00000001U)
#define MCSPI_HL_HWINFO_USEFIFO_FIFOEN                                                                       (1U)
#define MCSPI_HL_HWINFO_USEFIFO_NOFIFO                                                                       (0U)

#define MCSPI_HL_HWINFO_FFNBYTE_SHIFT                                                                       (1U)
#define MCSPI_HL_HWINFO_FFNBYTE_MASK                                                                        (0x0000003eU)
#define MCSPI_HL_HWINFO_FFNBYTE_FF16BYTES                                                                    (1U)
#define MCSPI_HL_HWINFO_FFNBYTE_FF32BYTES                                                                    (2U)
#define MCSPI_HL_HWINFO_FFNBYTE_FF64BYTES                                                                    (4U)
#define MCSPI_HL_HWINFO_FFNBYTE_FF128BYTES                                                                   (8U)
#define MCSPI_HL_HWINFO_FFNBYTE_FF256BYTES                                                                   (16U)

#define MCSPI_HL_HWINFO_RSVD_SHIFT                                                                          (7U)
#define MCSPI_HL_HWINFO_RSVD_MASK                                                                           (0xffffff80U)

#define MCSPI_HL_HWINFO_RETMODE_SHIFT                                                                       (6U)
#define MCSPI_HL_HWINFO_RETMODE_MASK                                                                        (0x00000040U)
#define MCSPI_HL_HWINFO_RETMODE_NORETMODE                                                                    (0U)
#define MCSPI_HL_HWINFO_RETMODE_RETMODEEN                                                                    (1U)

#define MCSPI_HL_SYSCONFIG_IDLEMODE_SHIFT                                                                   (2U)
#define MCSPI_HL_SYSCONFIG_IDLEMODE_MASK                                                                    (0x0000000cU)
#define MCSPI_HL_SYSCONFIG_IDLEMODE_SMARTIDLEWAKEUP                                                          (3U)
#define MCSPI_HL_SYSCONFIG_IDLEMODE_FORCEIDLE                                                                (0U)
#define MCSPI_HL_SYSCONFIG_IDLEMODE_NOIDLE                                                                   (1U)
#define MCSPI_HL_SYSCONFIG_IDLEMODE_SMARTIDLE                                                                (2U)

#define MCSPI_HL_SYSCONFIG_RSVD_SHIFT                                                                       (4U)
#define MCSPI_HL_SYSCONFIG_RSVD_MASK                                                                        (0xfffffff0U)

#define MCSPI_HL_SYSCONFIG_SOFTRESET_SHIFT                                                                  (0U)
#define MCSPI_HL_SYSCONFIG_SOFTRESET_MASK                                                                   (0x00000001U)
#define MCSPI_HL_SYSCONFIG_SOFTRESET_RESETDONE                                                               (0U)
#define MCSPI_HL_SYSCONFIG_SOFTRESET_NOACTION                                                                (0U)
#define MCSPI_HL_SYSCONFIG_SOFTRESET_SOFTRESET                                                               (1U)
#define MCSPI_HL_SYSCONFIG_SOFTRESET_RESETONGOING                                                            (1U)

#define MCSPI_HL_SYSCONFIG_FREEEMU_SHIFT                                                                    (1U)
#define MCSPI_HL_SYSCONFIG_FREEEMU_MASK                                                                     (0x00000002U)
#define MCSPI_HL_SYSCONFIG_FREEEMU_EMUDIS                                                                    (1U)
#define MCSPI_HL_SYSCONFIG_FREEEMU_EMUEN                                                                     (0U)

#define MCSPI_REVISION_REVISION_SHIFT                                                                       (0U)
#define MCSPI_REVISION_REVISION_MASK                                                                        (0xffffffffU)

#define MCSPI_SYSCONFIG_SIDLEMODE_SHIFT                                                                     (3U)
#define MCSPI_SYSCONFIG_SIDLEMODE_MASK                                                                      (0x00000018U)
#define MCSPI_SYSCONFIG_SIDLEMODE_FORCE                                                                      (0U)
#define MCSPI_SYSCONFIG_SIDLEMODE_NO                                                                         (1U)
#define MCSPI_SYSCONFIG_SIDLEMODE_SMART                                                                      (2U)
#define MCSPI_SYSCONFIG_SIDLEMODE_SMART_IDLE_WAKEUP                                                          (3U)

#define MCSPI_SYSCONFIG_RESERVED_14_SHIFT                                                                   (10U)
#define MCSPI_SYSCONFIG_RESERVED_14_MASK                                                                    (0xfffffc00U)

#define MCSPI_SYSCONFIG_SOFTRESET_SHIFT                                                                     (1U)
#define MCSPI_SYSCONFIG_SOFTRESET_MASK                                                                      (0x00000002U)
#define MCSPI_SYSCONFIG_SOFTRESET_OFF                                                                        (0U)
#define MCSPI_SYSCONFIG_SOFTRESET_ON                                                                         (1U)

#define MCSPI_SYSCONFIG_CLOCKACTIVITY_SHIFT                                                                 (8U)
#define MCSPI_SYSCONFIG_CLOCKACTIVITY_MASK                                                                  (0x00000300U)
#define MCSPI_SYSCONFIG_CLOCKACTIVITY_NONE                                                                   (0U)
#define MCSPI_SYSCONFIG_CLOCKACTIVITY_OCP                                                                    (1U)
#define MCSPI_SYSCONFIG_CLOCKACTIVITY_FUNC                                                                   (2U)
#define MCSPI_SYSCONFIG_CLOCKACTIVITY_BOTH                                                                   (3U)

#define MCSPI_SYSCONFIG_AUTOIDLE_SHIFT                                                                      (0U)
#define MCSPI_SYSCONFIG_AUTOIDLE_MASK                                                                       (0x00000001U)
#define MCSPI_SYSCONFIG_AUTOIDLE_OFF                                                                         (0U)
#define MCSPI_SYSCONFIG_AUTOIDLE_ON                                                                          (1U)

#define MCSPI_SYSCONFIG_ENAWAKEUP_SHIFT                                                                     (2U)
#define MCSPI_SYSCONFIG_ENAWAKEUP_MASK                                                                      (0x00000004U)
#define MCSPI_SYSCONFIG_ENAWAKEUP_NOWAKEUP                                                                   (0U)
#define MCSPI_SYSCONFIG_ENAWAKEUP_ON                                                                         (1U)

#define MCSPI_SYSCONFIG_RESERVED_15_SHIFT                                                                   (5U)
#define MCSPI_SYSCONFIG_RESERVED_15_MASK                                                                    (0x000000e0U)

#define MCSPI_SYSSTATUS_RESERVED_16_SHIFT                                                                   (1U)
#define MCSPI_SYSSTATUS_RESERVED_16_MASK                                                                    (0xfffffffeU)

#define MCSPI_SYSSTATUS_RESETDONE_SHIFT                                                                     (0U)
#define MCSPI_SYSSTATUS_RESETDONE_MASK                                                                      (0x00000001U)
#define MCSPI_SYSSTATUS_RESETDONE_INPROGRESS                                                                 (0U)
#define MCSPI_SYSSTATUS_RESETDONE_COMPLETED                                                                  (1U)

#define MCSPI_IRQSTATUS_RESERVED_7_SHIFT                                                                    (15U)
#define MCSPI_IRQSTATUS_RESERVED_7_MASK                                                                     (0x00008000U)

#define MCSPI_IRQSTATUS_RX3_FULL_SHIFT                                                                      (14U)
#define MCSPI_IRQSTATUS_RX3_FULL_MASK                                                                       (0x00004000U)
#define MCSPI_IRQSTATUS_RX3_FULL_NOEVNT_R                                                                    (0U)
#define MCSPI_IRQSTATUS_RX3_FULL_EVNT_R                                                                      (1U)
#define MCSPI_IRQSTATUS_RX3_FULL_NOEFFECT_W                                                                  (0U)
#define MCSPI_IRQSTATUS_RX3_FULL_CLEARSRC_W                                                                  (1U)

#define MCSPI_IRQSTATUS_RESERVED_8_SHIFT                                                                    (18U)
#define MCSPI_IRQSTATUS_RESERVED_8_MASK                                                                     (0xfffc0000U)

#define MCSPI_IRQSTATUS_WKS_SHIFT                                                                           (16U)
#define MCSPI_IRQSTATUS_WKS_MASK                                                                            (0x00010000U)
#define MCSPI_IRQSTATUS_WKS_NOEVNT_R                                                                         (0U)
#define MCSPI_IRQSTATUS_WKS_EVNT_R                                                                           (1U)
#define MCSPI_IRQSTATUS_WKS_NOEFFECT_W                                                                       (0U)
#define MCSPI_IRQSTATUS_WKS_CLEARSRC_W                                                                       (1U)

#define MCSPI_IRQSTATUS_RESERVED_9_SHIFT                                                                    (11U)
#define MCSPI_IRQSTATUS_RESERVED_9_MASK                                                                     (0x00000800U)

#define MCSPI_IRQSTATUS_RX2_FULL_SHIFT                                                                      (10U)
#define MCSPI_IRQSTATUS_RX2_FULL_MASK                                                                       (0x00000400U)
#define MCSPI_IRQSTATUS_RX2_FULL_NOEVNT_R                                                                    (0U)
#define MCSPI_IRQSTATUS_RX2_FULL_EVNT_R                                                                      (1U)
#define MCSPI_IRQSTATUS_RX2_FULL_NOEFFECT_W                                                                  (0U)
#define MCSPI_IRQSTATUS_RX2_FULL_CLEARSRC_W                                                                  (1U)

#define MCSPI_IRQSTATUS_TX3_EMPTY_SHIFT                                                                     (12U)
#define MCSPI_IRQSTATUS_TX3_EMPTY_MASK                                                                      (0x00001000U)
#define MCSPI_IRQSTATUS_TX3_EMPTY_NOEVNT_R                                                                   (0U)
#define MCSPI_IRQSTATUS_TX3_EMPTY_EVNT_R                                                                     (1U)
#define MCSPI_IRQSTATUS_TX3_EMPTY_NOEFFECT_W                                                                 (0U)
#define MCSPI_IRQSTATUS_TX3_EMPTY_CLEARSRC_W                                                                 (1U)

#define MCSPI_IRQSTATUS_RX1_FULL_SHIFT                                                                      (6U)
#define MCSPI_IRQSTATUS_RX1_FULL_MASK                                                                       (0x00000040U)
#define MCSPI_IRQSTATUS_RX1_FULL_NOEVNT_R                                                                    (0U)
#define MCSPI_IRQSTATUS_RX1_FULL_EVNT_R                                                                      (1U)
#define MCSPI_IRQSTATUS_RX1_FULL_NOEFFECT_W                                                                  (0U)
#define MCSPI_IRQSTATUS_RX1_FULL_CLEARSRC_W                                                                  (1U)

#define MCSPI_IRQSTATUS_TX3_UNDERFLOW_SHIFT                                                                 (13U)
#define MCSPI_IRQSTATUS_TX3_UNDERFLOW_MASK                                                                  (0x00002000U)
#define MCSPI_IRQSTATUS_TX3_UNDERFLOW_NOEVNT_R                                                               (0U)
#define MCSPI_IRQSTATUS_TX3_UNDERFLOW_EVNT_R                                                                 (1U)
#define MCSPI_IRQSTATUS_TX3_UNDERFLOW_NOEFFECT_W                                                             (0U)
#define MCSPI_IRQSTATUS_TX3_UNDERFLOW_CLEARSRC_W                                                             (1U)

#define MCSPI_IRQSTATUS_TX2_EMPTY_SHIFT                                                                     (8U)
#define MCSPI_IRQSTATUS_TX2_EMPTY_MASK                                                                      (0x00000100U)
#define MCSPI_IRQSTATUS_TX2_EMPTY_NOEVNT_R                                                                   (0U)
#define MCSPI_IRQSTATUS_TX2_EMPTY_EVNT_R                                                                     (1U)
#define MCSPI_IRQSTATUS_TX2_EMPTY_NOEFFECT_W                                                                 (0U)
#define MCSPI_IRQSTATUS_TX2_EMPTY_CLEARSRC_W                                                                 (1U)

#define MCSPI_IRQSTATUS_TX2_UNDERFLOW_SHIFT                                                                 (9U)
#define MCSPI_IRQSTATUS_TX2_UNDERFLOW_MASK                                                                  (0x00000200U)
#define MCSPI_IRQSTATUS_TX2_UNDERFLOW_NOEVNT_R                                                               (0U)
#define MCSPI_IRQSTATUS_TX2_UNDERFLOW_EVNT_R                                                                 (1U)
#define MCSPI_IRQSTATUS_TX2_UNDERFLOW_NOEFFECT_W                                                             (0U)
#define MCSPI_IRQSTATUS_TX2_UNDERFLOW_CLEARSRC_W                                                             (1U)

#define MCSPI_IRQSTATUS_TX1_EMPTY_SHIFT                                                                     (4U)
#define MCSPI_IRQSTATUS_TX1_EMPTY_MASK                                                                      (0x00000010U)
#define MCSPI_IRQSTATUS_TX1_EMPTY_NOEVNT_R                                                                   (0U)
#define MCSPI_IRQSTATUS_TX1_EMPTY_EVNT_R                                                                     (1U)
#define MCSPI_IRQSTATUS_TX1_EMPTY_NOEFFECT_W                                                                 (0U)
#define MCSPI_IRQSTATUS_TX1_EMPTY_CLEARSRC_W                                                                 (1U)

#define MCSPI_IRQSTATUS_TX0_UNDERFLOW_SHIFT                                                                 (1U)
#define MCSPI_IRQSTATUS_TX0_UNDERFLOW_MASK                                                                  (0x00000002U)
#define MCSPI_IRQSTATUS_TX0_UNDERFLOW_NOEVNT_R                                                               (0U)
#define MCSPI_IRQSTATUS_TX0_UNDERFLOW_EVNT_R                                                                 (1U)
#define MCSPI_IRQSTATUS_TX0_UNDERFLOW_NOEFFECT_W                                                             (0U)
#define MCSPI_IRQSTATUS_TX0_UNDERFLOW_CLEARSRC_W                                                             (1U)

#define MCSPI_IRQSTATUS_TX1_UNDERFLOW_SHIFT                                                                 (5U)
#define MCSPI_IRQSTATUS_TX1_UNDERFLOW_MASK                                                                  (0x00000020U)
#define MCSPI_IRQSTATUS_TX1_UNDERFLOW_NOEVNT_R                                                               (0U)
#define MCSPI_IRQSTATUS_TX1_UNDERFLOW_EVNT_R                                                                 (1U)
#define MCSPI_IRQSTATUS_TX1_UNDERFLOW_NOEFFECT_W                                                             (0U)
#define MCSPI_IRQSTATUS_TX1_UNDERFLOW_CLEARSRC_W                                                             (1U)

#define MCSPI_IRQSTATUS_RESERVED_10_SHIFT                                                                   (7U)
#define MCSPI_IRQSTATUS_RESERVED_10_MASK                                                                    (0x00000080U)

#define MCSPI_IRQSTATUS_RX0_FULL_SHIFT                                                                      (2U)
#define MCSPI_IRQSTATUS_RX0_FULL_MASK                                                                       (0x00000004U)
#define MCSPI_IRQSTATUS_RX0_FULL_NOEVNT_R                                                                    (0U)
#define MCSPI_IRQSTATUS_RX0_FULL_EVNT_R                                                                      (1U)
#define MCSPI_IRQSTATUS_RX0_FULL_NOEFFECT_W                                                                  (0U)
#define MCSPI_IRQSTATUS_RX0_FULL_CLEARSRC_W                                                                  (1U)

#define MCSPI_IRQSTATUS_RX0_OVERFLOW_SHIFT                                                                  (3U)
#define MCSPI_IRQSTATUS_RX0_OVERFLOW_MASK                                                                   (0x00000008U)
#define MCSPI_IRQSTATUS_RX0_OVERFLOW_NOEVNT_R                                                                (0U)
#define MCSPI_IRQSTATUS_RX0_OVERFLOW_EVNT_R                                                                  (1U)
#define MCSPI_IRQSTATUS_RX0_OVERFLOW_NOEFFECT_W                                                              (0U)
#define MCSPI_IRQSTATUS_RX0_OVERFLOW_CLEARSRC_W                                                              (1U)

#define MCSPI_IRQSTATUS_TX0_EMPTY_SHIFT                                                                     (0U)
#define MCSPI_IRQSTATUS_TX0_EMPTY_MASK                                                                      (0x00000001U)
#define MCSPI_IRQSTATUS_TX0_EMPTY_NOEVNT_R                                                                   (0U)
#define MCSPI_IRQSTATUS_TX0_EMPTY_EVNT_R                                                                     (1U)
#define MCSPI_IRQSTATUS_TX0_EMPTY_NOEFFECT_W                                                                 (0U)
#define MCSPI_IRQSTATUS_TX0_EMPTY_CLEARSRC_W                                                                 (1U)

#define MCSPI_IRQSTATUS_EOW_SHIFT                                                                           (17U)
#define MCSPI_IRQSTATUS_EOW_MASK                                                                            (0x00020000U)
#define MCSPI_IRQSTATUS_EOW_NOEVNT_R                                                                         (0U)
#define MCSPI_IRQSTATUS_EOW_EVNT_R                                                                           (1U)
#define MCSPI_IRQSTATUS_EOW_CLEARSRC_W                                                                       (1U)
#define MCSPI_IRQSTATUS_EOW_NOEFFECT_W                                                                       (0U)

#define MCSPI_IRQENABLE_RESERVED_3_SHIFT                                                                    (7U)
#define MCSPI_IRQENABLE_RESERVED_3_MASK                                                                     (0x00000080U)

#define MCSPI_IRQENABLE_TX2_UNDERFLOW_ENABLE_SHIFT                                                          (9U)
#define MCSPI_IRQENABLE_TX2_UNDERFLOW_ENABLE_MASK                                                           (0x00000200U)
#define MCSPI_IRQENABLE_TX2_UNDERFLOW_ENABLE_IRQDISABLED                                                     (0U)
#define MCSPI_IRQENABLE_TX2_UNDERFLOW_ENABLE_IRQENABLED                                                      (1U)

#define MCSPI_IRQENABLE_RESERVED_4_SHIFT                                                                    (15U)
#define MCSPI_IRQENABLE_RESERVED_4_MASK                                                                     (0x00008000U)

#define MCSPI_IRQENABLE_TX0_EMPTY_ENABLE_SHIFT                                                              (0U)
#define MCSPI_IRQENABLE_TX0_EMPTY_ENABLE_MASK                                                               (0x00000001U)
#define MCSPI_IRQENABLE_TX0_EMPTY_ENABLE_IRQDISABLED                                                         (0U)
#define MCSPI_IRQENABLE_TX0_EMPTY_ENABLE_IRQENABLED                                                          (1U)

#define MCSPI_IRQENABLE_RX0_FULL_ENABLE_SHIFT                                                               (2U)
#define MCSPI_IRQENABLE_RX0_FULL_ENABLE_MASK                                                                (0x00000004U)
#define MCSPI_IRQENABLE_RX0_FULL_ENABLE_IRQDISABLED                                                          (0U)
#define MCSPI_IRQENABLE_RX0_FULL_ENABLE_IRQENABLED                                                           (1U)

#define MCSPI_IRQENABLE_TX1_EMPTY_ENABLE_SHIFT                                                              (4U)
#define MCSPI_IRQENABLE_TX1_EMPTY_ENABLE_MASK                                                               (0x00000010U)
#define MCSPI_IRQENABLE_TX1_EMPTY_ENABLE_IRQDISABLED                                                         (0U)
#define MCSPI_IRQENABLE_TX1_EMPTY_ENABLE_IRQENABLED                                                          (1U)

#define MCSPI_IRQENABLE_RX1_FULL_ENABLE_SHIFT                                                               (6U)
#define MCSPI_IRQENABLE_RX1_FULL_ENABLE_MASK                                                                (0x00000040U)
#define MCSPI_IRQENABLE_RX1_FULL_ENABLE_IRQDISABLED                                                          (0U)
#define MCSPI_IRQENABLE_RX1_FULL_ENABLE_IRQENABLED                                                           (1U)

#define MCSPI_IRQENABLE_TX3_EMPTY_ENABLE_SHIFT                                                              (12U)
#define MCSPI_IRQENABLE_TX3_EMPTY_ENABLE_MASK                                                               (0x00001000U)
#define MCSPI_IRQENABLE_TX3_EMPTY_ENABLE_IRQDISABLED                                                         (0U)
#define MCSPI_IRQENABLE_TX3_EMPTY_ENABLE_IRQENABLED                                                          (1U)

#define MCSPI_IRQENABLE_TX0_UNDERFLOW_ENABLE_SHIFT                                                          (1U)
#define MCSPI_IRQENABLE_TX0_UNDERFLOW_ENABLE_MASK                                                           (0x00000002U)
#define MCSPI_IRQENABLE_TX0_UNDERFLOW_ENABLE_IRQDISABLED                                                     (0U)
#define MCSPI_IRQENABLE_TX0_UNDERFLOW_ENABLE_IRQENABLED                                                      (1U)

#define MCSPI_IRQENABLE_RX0_OVERFLOW_ENABLE_SHIFT                                                           (3U)
#define MCSPI_IRQENABLE_RX0_OVERFLOW_ENABLE_MASK                                                            (0x00000008U)
#define MCSPI_IRQENABLE_RX0_OVERFLOW_ENABLE_IRQDISABLED                                                      (0U)
#define MCSPI_IRQENABLE_RX0_OVERFLOW_ENABLE_IRQENABLED                                                       (1U)

#define MCSPI_IRQENABLE_RX3_FULL_ENABLE_SHIFT                                                               (14U)
#define MCSPI_IRQENABLE_RX3_FULL_ENABLE_MASK                                                                (0x00004000U)
#define MCSPI_IRQENABLE_RX3_FULL_ENABLE_IRQDISABLED                                                          (0U)
#define MCSPI_IRQENABLE_RX3_FULL_ENABLE_IRQENABLED                                                           (1U)

#define MCSPI_IRQENABLE_RESERVED_5_SHIFT                                                                    (18U)
#define MCSPI_IRQENABLE_RESERVED_5_MASK                                                                     (0xfffc0000U)

#define MCSPI_IRQENABLE_RESERVED_6_SHIFT                                                                    (11U)
#define MCSPI_IRQENABLE_RESERVED_6_MASK                                                                     (0x00000800U)

#define MCSPI_IRQENABLE_WKE_SHIFT                                                                           (16U)
#define MCSPI_IRQENABLE_WKE_MASK                                                                            (0x00010000U)
#define MCSPI_IRQENABLE_WKE_IRQDISABLED                                                                      (0U)
#define MCSPI_IRQENABLE_WKE_IRQENABLED                                                                       (1U)

#define MCSPI_IRQENABLE_TX2_EMPTY_ENABLE_SHIFT                                                              (8U)
#define MCSPI_IRQENABLE_TX2_EMPTY_ENABLE_MASK                                                               (0x00000100U)
#define MCSPI_IRQENABLE_TX2_EMPTY_ENABLE_IRQDISABLED                                                         (0U)
#define MCSPI_IRQENABLE_TX2_EMPTY_ENABLE_IRQENABLED                                                          (1U)

#define MCSPI_IRQENABLE_RX2_FULL_ENABLE_SHIFT                                                               (10U)
#define MCSPI_IRQENABLE_RX2_FULL_ENABLE_MASK                                                                (0x00000400U)
#define MCSPI_IRQENABLE_RX2_FULL_ENABLE_IRQDISABLED                                                          (0U)
#define MCSPI_IRQENABLE_RX2_FULL_ENABLE_IRQENABLED                                                           (1U)

#define MCSPI_IRQENABLE_TX3_UNDERFLOW_ENABLE_SHIFT                                                          (13U)
#define MCSPI_IRQENABLE_TX3_UNDERFLOW_ENABLE_MASK                                                           (0x00002000U)
#define MCSPI_IRQENABLE_TX3_UNDERFLOW_ENABLE_IRQDISABLED                                                     (0U)
#define MCSPI_IRQENABLE_TX3_UNDERFLOW_ENABLE_IRQENABLED                                                      (1U)

#define MCSPI_IRQENABLE_TX1_UNDERFLOW_ENABLE_SHIFT                                                          (5U)
#define MCSPI_IRQENABLE_TX1_UNDERFLOW_ENABLE_MASK                                                           (0x00000020U)
#define MCSPI_IRQENABLE_TX1_UNDERFLOW_ENABLE_IRQDISABLED                                                     (0U)
#define MCSPI_IRQENABLE_TX1_UNDERFLOW_ENABLE_IRQENABLED                                                      (1U)

#define MCSPI_IRQENABLE_EOW_ENABLE_SHIFT                                                                    (17U)
#define MCSPI_IRQENABLE_EOW_ENABLE_MASK                                                                     (0x00020000U)
#define MCSPI_IRQENABLE_EOW_ENABLE_IRQENABLED                                                                (1U)
#define MCSPI_IRQENABLE_EOW_ENABLE_IRQDISABLED                                                               (0U)

#define MCSPI_WAKEUPENABLE_RESERVED_18_SHIFT                                                                (1U)
#define MCSPI_WAKEUPENABLE_RESERVED_18_MASK                                                                 (0xfffffffeU)

#define MCSPI_WAKEUPENABLE_WKEN_SHIFT                                                                       (0U)
#define MCSPI_WAKEUPENABLE_WKEN_MASK                                                                        (0x00000001U)
#define MCSPI_WAKEUPENABLE_WKEN_NOWAKEUP                                                                     (0U)
#define MCSPI_WAKEUPENABLE_WKEN_WAKEUP                                                                       (1U)

#define MCSPI_SYST_SPIEN_2_SHIFT                                                                            (2U)
#define MCSPI_SYST_SPIEN_2_MASK                                                                             (0x00000004U)

#define MCSPI_SYST_WAKD_SHIFT                                                                               (7U)
#define MCSPI_SYST_WAKD_MASK                                                                                (0x00000080U)
#define MCSPI_SYST_WAKD_DRIVENLOW                                                                            (0U)
#define MCSPI_SYST_WAKD_DRIVENHIGH                                                                           (1U)

#define MCSPI_SYST_SPIDAT_0_SHIFT                                                                           (4U)
#define MCSPI_SYST_SPIDAT_0_MASK                                                                            (0x00000010U)

#define MCSPI_SYST_SPIEN_1_SHIFT                                                                            (1U)
#define MCSPI_SYST_SPIEN_1_MASK                                                                             (0x00000002U)

#define MCSPI_SYST_RESERVED_17_SHIFT                                                                        (12U)
#define MCSPI_SYST_RESERVED_17_MASK                                                                         (0xfffff000U)

#define MCSPI_SYST_SPIDATDIR1_SHIFT                                                                         (9U)
#define MCSPI_SYST_SPIDATDIR1_MASK                                                                          (0x00000200U)
#define MCSPI_SYST_SPIDATDIR1_OUT                                                                            (0U)
#define MCSPI_SYST_SPIDATDIR1_IN                                                                             (1U)

#define MCSPI_SYST_SSB_SHIFT                                                                                (11U)
#define MCSPI_SYST_SSB_MASK                                                                                 (0x00000800U)
#define MCSPI_SYST_SSB_OFF                                                                                   (0U)
#define MCSPI_SYST_SSB_SETTHEMALL                                                                            (1U)

#define MCSPI_SYST_SPICLK_SHIFT                                                                             (6U)
#define MCSPI_SYST_SPICLK_MASK                                                                              (0x00000040U)

#define MCSPI_SYST_SPIDATDIR0_SHIFT                                                                         (8U)
#define MCSPI_SYST_SPIDATDIR0_MASK                                                                          (0x00000100U)
#define MCSPI_SYST_SPIDATDIR0_OUT                                                                            (0U)
#define MCSPI_SYST_SPIDATDIR0_IN                                                                             (1U)

#define MCSPI_SYST_SPIENDIR_SHIFT                                                                           (10U)
#define MCSPI_SYST_SPIENDIR_MASK                                                                            (0x00000400U)
#define MCSPI_SYST_SPIENDIR_OUT                                                                              (0U)
#define MCSPI_SYST_SPIENDIR_IN                                                                               (1U)

#define MCSPI_SYST_SPIEN_3_SHIFT                                                                            (3U)
#define MCSPI_SYST_SPIEN_3_MASK                                                                             (0x00000008U)

#define MCSPI_SYST_SPIEN_0_SHIFT                                                                            (0U)
#define MCSPI_SYST_SPIEN_0_MASK                                                                             (0x00000001U)

#define MCSPI_SYST_SPIDAT_1_SHIFT                                                                           (5U)
#define MCSPI_SYST_SPIDAT_1_MASK                                                                            (0x00000020U)

#define MCSPI_MODULCTRL_MS_SHIFT                                                                            (2U)
#define MCSPI_MODULCTRL_MS_MASK                                                                             (0x00000004U)
#define MCSPI_MODULCTRL_MS_MASTER                                                                            (0U)
#define MCSPI_MODULCTRL_MS_SLAVE                                                                             (1U)

#define MCSPI_MODULCTRL_RESERVED_11_SHIFT                                                                   (9U)
#define MCSPI_MODULCTRL_RESERVED_11_MASK                                                                    (0xfffffe00U)

#define MCSPI_MODULCTRL_SYSTEM_TEST_SHIFT                                                                   (3U)
#define MCSPI_MODULCTRL_SYSTEM_TEST_MASK                                                                    (0x00000008U)
#define MCSPI_MODULCTRL_SYSTEM_TEST_OFF                                                                      (0U)
#define MCSPI_MODULCTRL_SYSTEM_TEST_ON                                                                       (1U)

#define MCSPI_MODULCTRL_SINGLE_SHIFT                                                                        (0U)
#define MCSPI_MODULCTRL_SINGLE_MASK                                                                         (0x00000001U)
#define MCSPI_MODULCTRL_SINGLE_MULTI                                                                         (0U)
#define MCSPI_MODULCTRL_SINGLE_SINGLE                                                                        (1U)

#define MCSPI_MODULCTRL_PIN34_SHIFT                                                                         (1U)
#define MCSPI_MODULCTRL_PIN34_MASK                                                                          (0x00000002U)
#define MCSPI_MODULCTRL_PIN34_3PINMODE                                                                       (1U)
#define MCSPI_MODULCTRL_PIN34_4PINMODE                                                                       (0U)

#define MCSPI_MODULCTRL_INITDLY_SHIFT                                                                       (4U)
#define MCSPI_MODULCTRL_INITDLY_MASK                                                                        (0x00000070U)
#define MCSPI_MODULCTRL_INITDLY_4CLKDLY                                                                      (1U)
#define MCSPI_MODULCTRL_INITDLY_NODELAY                                                                      (0U)
#define MCSPI_MODULCTRL_INITDLY_8CLKDLY                                                                      (2U)
#define MCSPI_MODULCTRL_INITDLY_16CLKDLY                                                                     (3U)
#define MCSPI_MODULCTRL_INITDLY_32CLKDLY                                                                     (4U)

#define MCSPI_MODULCTRL_MOA_SHIFT                                                                           (7U)
#define MCSPI_MODULCTRL_MOA_MASK                                                                            (0x00000080U)
#define MCSPI_MODULCTRL_MOA_MULTIACCES                                                                       (1U)
#define MCSPI_MODULCTRL_MOA_NOMULTIACCESS                                                                    (0U)

#define MCSPI_MODULCTRL_FDAA_SHIFT                                                                          (8U)
#define MCSPI_MODULCTRL_FDAA_MASK                                                                           (0x00000100U)
#define MCSPI_MODULCTRL_FDAA_SHADOWREGEN                                                                     (1U)
#define MCSPI_MODULCTRL_FDAA_NOSHADOWREG                                                                     (0U)

#define MCSPI_CH0CONF_CLKD_SHIFT                                                                            (2U)
#define MCSPI_CH0CONF_CLKD_MASK                                                                             (0x0000003cU)
#define MCSPI_CH0CONF_CLKD_DIVBY4K                                                                           (12U)
#define MCSPI_CH0CONF_CLKD_DIVBY8                                                                            (3U)
#define MCSPI_CH0CONF_CLKD_DIVBY8K                                                                           (13U)
#define MCSPI_CH0CONF_CLKD_DIVBY2K                                                                           (11U)
#define MCSPI_CH0CONF_CLKD_DIVBY1K                                                                           (10U)
#define MCSPI_CH0CONF_CLKD_DIVBY512                                                                          (9U)
#define MCSPI_CH0CONF_CLKD_DIVBY32K                                                                          (15U)
#define MCSPI_CH0CONF_CLKD_DIVBY4                                                                            (2U)
#define MCSPI_CH0CONF_CLKD_DIVBY1                                                                            (0U)
#define MCSPI_CH0CONF_CLKD_DIVBY64                                                                           (6U)
#define MCSPI_CH0CONF_CLKD_DIVBY256                                                                          (8U)
#define MCSPI_CH0CONF_CLKD_DIVBY128                                                                          (7U)
#define MCSPI_CH0CONF_CLKD_DIVBY32                                                                           (5U)
#define MCSPI_CH0CONF_CLKD_DIVBY16K                                                                          (14U)
#define MCSPI_CH0CONF_CLKD_DIVBY16                                                                           (4U)
#define MCSPI_CH0CONF_CLKD_DIVBY2                                                                            (1U)

#define MCSPI_CH0CONF_RESERVED_0_SHIFT                                                                      (30U)
#define MCSPI_CH0CONF_RESERVED_0_MASK                                                                       (0xc0000000U)

#define MCSPI_CH0CONF_PHA_SHIFT                                                                             (0U)
#define MCSPI_CH0CONF_PHA_MASK                                                                              (0x00000001U)
#define MCSPI_CH0CONF_PHA_ODD                                                                                (0U)
#define MCSPI_CH0CONF_PHA_EVEN                                                                               (1U)

#define MCSPI_CH0CONF_TURBO_SHIFT                                                                           (19U)
#define MCSPI_CH0CONF_TURBO_MASK                                                                            (0x00080000U)
#define MCSPI_CH0CONF_TURBO_TURBO                                                                            (1U)
#define MCSPI_CH0CONF_TURBO_OFF                                                                              (0U)

#define MCSPI_CH0CONF_SPIENSLV_SHIFT                                                                        (21U)
#define MCSPI_CH0CONF_SPIENSLV_MASK                                                                         (0x00600000U)
#define MCSPI_CH0CONF_SPIENSLV_SPIEN2                                                                        (2U)
#define MCSPI_CH0CONF_SPIENSLV_SPIEN3                                                                        (3U)
#define MCSPI_CH0CONF_SPIENSLV_SPIEN0                                                                        (0U)
#define MCSPI_CH0CONF_SPIENSLV_SPIEN1                                                                        (1U)

#define MCSPI_CH0CONF_DPE0_SHIFT                                                                            (16U)
#define MCSPI_CH0CONF_DPE0_MASK                                                                             (0x00010000U)
#define MCSPI_CH0CONF_DPE0_DISABLED                                                                          (1U)
#define MCSPI_CH0CONF_DPE0_ENABLED                                                                           (0U)

#define MCSPI_CH0CONF_IS_SHIFT                                                                              (18U)
#define MCSPI_CH0CONF_IS_MASK                                                                               (0x00040000U)
#define MCSPI_CH0CONF_IS_LINE0                                                                               (0U)
#define MCSPI_CH0CONF_IS_LINE1                                                                               (1U)

#define MCSPI_CH0CONF_DMAR_SHIFT                                                                            (15U)
#define MCSPI_CH0CONF_DMAR_MASK                                                                             (0x00008000U)
#define MCSPI_CH0CONF_DMAR_DISABLED                                                                          (0U)
#define MCSPI_CH0CONF_DMAR_ENABLED                                                                           (1U)

#define MCSPI_CH0CONF_FORCE_SHIFT                                                                           (20U)
#define MCSPI_CH0CONF_FORCE_MASK                                                                            (0x00100000U)
#define MCSPI_CH0CONF_FORCE_DEASSERT                                                                         (0U)
#define MCSPI_CH0CONF_FORCE_ASSERT                                                                           (1U)

#define MCSPI_CH0CONF_WL_SHIFT                                                                              (7U)
#define MCSPI_CH0CONF_WL_MASK                                                                               (0x00000f80U)
#define MCSPI_CH0CONF_WL_21BITS                                                                              (20U)
#define MCSPI_CH0CONF_WL_26BITS                                                                              (25U)
#define MCSPI_CH0CONF_WL_18BITS                                                                              (17U)
#define MCSPI_CH0CONF_WL_20BITS                                                                              (19U)
#define MCSPI_CH0CONF_WL_5BITS                                                                               (4U)
#define MCSPI_CH0CONF_WL_6BITS                                                                               (5U)
#define MCSPI_CH0CONF_WL_11BITS                                                                              (10U)
#define MCSPI_CH0CONF_WL_8BITS                                                                               (7U)
#define MCSPI_CH0CONF_WL_13BITS                                                                              (12U)
#define MCSPI_CH0CONF_WL_29BITS                                                                              (28U)
#define MCSPI_CH0CONF_WL_12BITS                                                                              (11U)
#define MCSPI_CH0CONF_WL_32BITS                                                                              (31U)
#define MCSPI_CH0CONF_WL_31BITS                                                                              (30U)
#define MCSPI_CH0CONF_WL_30BITS                                                                              (29U)
#define MCSPI_CH0CONF_WL_9BITS                                                                               (8U)
#define MCSPI_CH0CONF_WL_7BITS                                                                               (6U)
#define MCSPI_CH0CONF_WL_10BITS                                                                              (9U)
#define MCSPI_CH0CONF_WL_16BITS                                                                              (15U)
#define MCSPI_CH0CONF_WL_17BITS                                                                              (16U)
#define MCSPI_CH0CONF_WL_14BITS                                                                              (13U)
#define MCSPI_CH0CONF_WL_15BITS                                                                              (14U)
#define MCSPI_CH0CONF_WL_RSVD1                                                                               (1U)
#define MCSPI_CH0CONF_WL_RSVD0                                                                               (0U)
#define MCSPI_CH0CONF_WL_27BITS                                                                              (26U)
#define MCSPI_CH0CONF_WL_23BITS                                                                              (22U)
#define MCSPI_CH0CONF_WL_RSVD2                                                                               (2U)
#define MCSPI_CH0CONF_WL_19BITS                                                                              (18U)
#define MCSPI_CH0CONF_WL_4BITS                                                                               (3U)
#define MCSPI_CH0CONF_WL_25BITS                                                                              (24U)
#define MCSPI_CH0CONF_WL_24BITS                                                                              (23U)
#define MCSPI_CH0CONF_WL_22BITS                                                                              (21U)
#define MCSPI_CH0CONF_WL_28BITS                                                                              (27U)

#define MCSPI_CH0CONF_DPE1_SHIFT                                                                            (17U)
#define MCSPI_CH0CONF_DPE1_MASK                                                                             (0x00020000U)
#define MCSPI_CH0CONF_DPE1_ENABLED                                                                           (0U)
#define MCSPI_CH0CONF_DPE1_DISABLED                                                                          (1U)

#define MCSPI_CH0CONF_EPOL_SHIFT                                                                            (6U)
#define MCSPI_CH0CONF_EPOL_MASK                                                                             (0x00000040U)
#define MCSPI_CH0CONF_EPOL_ACTIVELOW                                                                         (1U)
#define MCSPI_CH0CONF_EPOL_ACTIVEHIGH                                                                        (0U)

#define MCSPI_CH0CONF_DMAW_SHIFT                                                                            (14U)
#define MCSPI_CH0CONF_DMAW_MASK                                                                             (0x00004000U)
#define MCSPI_CH0CONF_DMAW_ENABLED                                                                           (1U)
#define MCSPI_CH0CONF_DMAW_DISABLED                                                                          (0U)

#define MCSPI_CH0CONF_TRM_SHIFT                                                                             (12U)
#define MCSPI_CH0CONF_TRM_MASK                                                                              (0x00003000U)
#define MCSPI_CH0CONF_TRM_TRANSONLY                                                                          (2U)
#define MCSPI_CH0CONF_TRM_RSVD                                                                               (3U)
#define MCSPI_CH0CONF_TRM_TRANSRECEI                                                                         (0U)
#define MCSPI_CH0CONF_TRM_RECEIVONLY                                                                         (1U)

#define MCSPI_CH0CONF_POL_SHIFT                                                                             (1U)
#define MCSPI_CH0CONF_POL_MASK                                                                              (0x00000002U)
#define MCSPI_CH0CONF_POL_ACTIVELOW                                                                          (1U)
#define MCSPI_CH0CONF_POL_ACTIVEHIGH                                                                         (0U)

#define MCSPI_CH0CONF_SBE_SHIFT                                                                             (23U)
#define MCSPI_CH0CONF_SBE_MASK                                                                              (0x00800000U)
#define MCSPI_CH0CONF_SBE_DISABLED                                                                           (0U)
#define MCSPI_CH0CONF_SBE_ENABLED                                                                            (1U)

#define MCSPI_CH0CONF_SBPOL_SHIFT                                                                           (24U)
#define MCSPI_CH0CONF_SBPOL_MASK                                                                            (0x01000000U)
#define MCSPI_CH0CONF_SBPOL_LOWLEVEL                                                                         (0U)
#define MCSPI_CH0CONF_SBPOL_HIGHLEVEL                                                                        (1U)

#define MCSPI_CH0CONF_TCS0_SHIFT                                                                            (25U)
#define MCSPI_CH0CONF_TCS0_MASK                                                                             (0x06000000U)
#define MCSPI_CH0CONF_TCS0_THREECYCLEDLY                                                                     (3U)
#define MCSPI_CH0CONF_TCS0_TWOCYCLEDLY                                                                       (2U)
#define MCSPI_CH0CONF_TCS0_ONECYCLEDLY                                                                       (1U)
#define MCSPI_CH0CONF_TCS0_ZEROCYCLEDLY                                                                      (0U)

#define MCSPI_CH0CONF_FFER_SHIFT                                                                            (28U)
#define MCSPI_CH0CONF_FFER_MASK                                                                             (0x10000000U)
#define MCSPI_CH0CONF_FFER_FFENABLED                                                                         (1U)
#define MCSPI_CH0CONF_FFER_FFDISABLED                                                                        (0U)

#define MCSPI_CH0CONF_FFEW_SHIFT                                                                            (27U)
#define MCSPI_CH0CONF_FFEW_MASK                                                                             (0x08000000U)
#define MCSPI_CH0CONF_FFEW_FFENABLED                                                                         (1U)
#define MCSPI_CH0CONF_FFEW_FFDISABLED                                                                        (0U)

#define MCSPI_CH0CONF_CLKG_SHIFT                                                                            (29U)
#define MCSPI_CH0CONF_CLKG_MASK                                                                             (0x20000000U)
#define MCSPI_CH0CONF_CLKG_ONECYCLE                                                                          (1U)
#define MCSPI_CH0CONF_CLKG_POWERTWO                                                                          (0U)

#define MCSPI_CH0STAT_RXS_SHIFT                                                                             (0U)
#define MCSPI_CH0STAT_RXS_MASK                                                                              (0x00000001U)
#define MCSPI_CH0STAT_RXS_EMPTY                                                                              (0U)
#define MCSPI_CH0STAT_RXS_FULL                                                                               (1U)

#define MCSPI_CH0STAT_EOT_SHIFT                                                                             (2U)
#define MCSPI_CH0STAT_EOT_MASK                                                                              (0x00000004U)
#define MCSPI_CH0STAT_EOT_COMPLETED                                                                          (1U)
#define MCSPI_CH0STAT_EOT_INPROGRESS                                                                         (0U)

#define MCSPI_CH0STAT_RESERVED_2_SHIFT                                                                      (7U)
#define MCSPI_CH0STAT_RESERVED_2_MASK                                                                       (0xffffff80U)

#define MCSPI_CH0STAT_TXS_SHIFT                                                                             (1U)
#define MCSPI_CH0STAT_TXS_MASK                                                                              (0x00000002U)
#define MCSPI_CH0STAT_TXS_EMPTY                                                                              (1U)
#define MCSPI_CH0STAT_TXS_FULL                                                                               (0U)

#define MCSPI_CH0STAT_RXFFF_SHIFT                                                                           (6U)
#define MCSPI_CH0STAT_RXFFF_MASK                                                                            (0x00000040U)
#define MCSPI_CH0STAT_RXFFF_FULL                                                                             (1U)
#define MCSPI_CH0STAT_RXFFF_NOTFULL                                                                          (0U)

#define MCSPI_CH0STAT_TXFFF_SHIFT                                                                           (4U)
#define MCSPI_CH0STAT_TXFFF_MASK                                                                            (0x00000010U)
#define MCSPI_CH0STAT_TXFFF_FULL                                                                             (1U)
#define MCSPI_CH0STAT_TXFFF_NOTFULL                                                                          (0U)

#define MCSPI_CH0STAT_RXFFE_SHIFT                                                                           (5U)
#define MCSPI_CH0STAT_RXFFE_MASK                                                                            (0x00000020U)
#define MCSPI_CH0STAT_RXFFE_EMPTY                                                                            (1U)
#define MCSPI_CH0STAT_RXFFE_NOTEMPTY                                                                         (0U)

#define MCSPI_CH0STAT_TXFFE_SHIFT                                                                           (3U)
#define MCSPI_CH0STAT_TXFFE_MASK                                                                            (0x00000008U)
#define MCSPI_CH0STAT_TXFFE_EMPTY                                                                            (1U)
#define MCSPI_CH0STAT_TXFFE_NOTEMPTY                                                                         (0U)

#define MCSPI_CH0CTRL_RESERVED_1_SHIFT                                                                      (1U)
#define MCSPI_CH0CTRL_RESERVED_1_MASK                                                                       (0x000000feU)

#define MCSPI_CH0CTRL_EN_SHIFT                                                                              (0U)
#define MCSPI_CH0CTRL_EN_MASK                                                                               (0x00000001U)
#define MCSPI_CH0CTRL_EN_ACT                                                                                 (1U)
#define MCSPI_CH0CTRL_EN_NACT                                                                                (0U)

#define MCSPI_CH0CTRL_EXTCLK_SHIFT                                                                          (8U)
#define MCSPI_CH0CTRL_EXTCLK_MASK                                                                           (0x0000ff00U)
#define MCSPI_CH0CTRL_EXTCLK_EXTZERO                                                                         (0U)
#define MCSPI_CH0CTRL_EXTCLK_EXTONE                                                                          (1U)
#define MCSPI_CH0CTRL_EXTCLK_EXT4080                                                                         (255U)

#define MCSPI_CH0CTRL_RESERVED_2_SHIFT                                                                      (16U)
#define MCSPI_CH0CTRL_RESERVED_2_MASK                                                                       (0xffff0000U)

#define MCSPI_TX0_TDATA_SHIFT                                                                               (0U)
#define MCSPI_TX0_TDATA_MASK                                                                                (0xffffffffU)

#define MCSPI_RX0_RDATA_SHIFT                                                                               (0U)
#define MCSPI_RX0_RDATA_MASK                                                                                (0xffffffffU)

#define MCSPI_CH1CONF_CLKD_SHIFT                                                                            (2U)
#define MCSPI_CH1CONF_CLKD_MASK                                                                             (0x0000003cU)
#define MCSPI_CH1CONF_CLKD_DIVBY4K                                                                           (12U)
#define MCSPI_CH1CONF_CLKD_DIVBY8                                                                            (3U)
#define MCSPI_CH1CONF_CLKD_DIVBY8K                                                                           (13U)
#define MCSPI_CH1CONF_CLKD_DIVBY2K                                                                           (11U)
#define MCSPI_CH1CONF_CLKD_DIVBY1K                                                                           (10U)
#define MCSPI_CH1CONF_CLKD_DIVBY512                                                                          (9U)
#define MCSPI_CH1CONF_CLKD_DIVBY32K                                                                          (15U)
#define MCSPI_CH1CONF_CLKD_DIVBY4                                                                            (2U)
#define MCSPI_CH1CONF_CLKD_DIVBY1                                                                            (0U)
#define MCSPI_CH1CONF_CLKD_DIVBY64                                                                           (6U)
#define MCSPI_CH1CONF_CLKD_DIVBY256                                                                          (8U)
#define MCSPI_CH1CONF_CLKD_DIVBY128                                                                          (7U)
#define MCSPI_CH1CONF_CLKD_DIVBY32                                                                           (5U)
#define MCSPI_CH1CONF_CLKD_DIVBY16K                                                                          (14U)
#define MCSPI_CH1CONF_CLKD_DIVBY16                                                                           (4U)
#define MCSPI_CH1CONF_CLKD_DIVBY2                                                                            (1U)

#define MCSPI_CH1CONF_RESERVED_0_SHIFT                                                                      (30U)
#define MCSPI_CH1CONF_RESERVED_0_MASK                                                                       (0xc0000000U)

#define MCSPI_CH1CONF_PHA_SHIFT                                                                             (0U)
#define MCSPI_CH1CONF_PHA_MASK                                                                              (0x00000001U)
#define MCSPI_CH1CONF_PHA_ODD                                                                                (0U)
#define MCSPI_CH1CONF_PHA_EVEN                                                                               (1U)

#define MCSPI_CH1CONF_TURBO_SHIFT                                                                           (19U)
#define MCSPI_CH1CONF_TURBO_MASK                                                                            (0x00080000U)
#define MCSPI_CH1CONF_TURBO_TURBO                                                                            (1U)
#define MCSPI_CH1CONF_TURBO_OFF                                                                              (0U)

#define MCSPI_CH1CONF_RESERVED_1_SHIFT                                                                      (21U)
#define MCSPI_CH1CONF_RESERVED_1_MASK                                                                       (0x00600000U)

#define MCSPI_CH1CONF_DPE0_SHIFT                                                                            (16U)
#define MCSPI_CH1CONF_DPE0_MASK                                                                             (0x00010000U)
#define MCSPI_CH1CONF_DPE0_DISABLED                                                                          (1U)
#define MCSPI_CH1CONF_DPE0_ENABLED                                                                           (0U)

#define MCSPI_CH1CONF_IS_SHIFT                                                                              (18U)
#define MCSPI_CH1CONF_IS_MASK                                                                               (0x00040000U)
#define MCSPI_CH1CONF_IS_LINE0                                                                               (0U)
#define MCSPI_CH1CONF_IS_LINE1                                                                               (1U)

#define MCSPI_CH1CONF_DMAR_SHIFT                                                                            (15U)
#define MCSPI_CH1CONF_DMAR_MASK                                                                             (0x00008000U)
#define MCSPI_CH1CONF_DMAR_DISABLED                                                                          (0U)
#define MCSPI_CH1CONF_DMAR_ENABLED                                                                           (1U)

#define MCSPI_CH1CONF_FORCE_SHIFT                                                                           (20U)
#define MCSPI_CH1CONF_FORCE_MASK                                                                            (0x00100000U)
#define MCSPI_CH1CONF_FORCE_DEASSERT                                                                         (0U)
#define MCSPI_CH1CONF_FORCE_ASSERT                                                                           (1U)

#define MCSPI_CH1CONF_WL_SHIFT                                                                              (7U)
#define MCSPI_CH1CONF_WL_MASK                                                                               (0x00000f80U)
#define MCSPI_CH1CONF_WL_21BITS                                                                              (20U)
#define MCSPI_CH1CONF_WL_26BITS                                                                              (25U)
#define MCSPI_CH1CONF_WL_18BITS                                                                              (17U)
#define MCSPI_CH1CONF_WL_20BITS                                                                              (19U)
#define MCSPI_CH1CONF_WL_5BITS                                                                               (4U)
#define MCSPI_CH1CONF_WL_6BITS                                                                               (5U)
#define MCSPI_CH1CONF_WL_11BITS                                                                              (10U)
#define MCSPI_CH1CONF_WL_8BITS                                                                               (7U)
#define MCSPI_CH1CONF_WL_13BITS                                                                              (12U)
#define MCSPI_CH1CONF_WL_29BITS                                                                              (28U)
#define MCSPI_CH1CONF_WL_12BITS                                                                              (11U)
#define MCSPI_CH1CONF_WL_32BITS                                                                              (31U)
#define MCSPI_CH1CONF_WL_31BITS                                                                              (30U)
#define MCSPI_CH1CONF_WL_30BITS                                                                              (29U)
#define MCSPI_CH1CONF_WL_9BITS                                                                               (8U)
#define MCSPI_CH1CONF_WL_7BITS                                                                               (6U)
#define MCSPI_CH1CONF_WL_10BITS                                                                              (9U)
#define MCSPI_CH1CONF_WL_16BITS                                                                              (15U)
#define MCSPI_CH1CONF_WL_17BITS                                                                              (16U)
#define MCSPI_CH1CONF_WL_14BITS                                                                              (13U)
#define MCSPI_CH1CONF_WL_15BITS                                                                              (14U)
#define MCSPI_CH1CONF_WL_RSVD1                                                                               (1U)
#define MCSPI_CH1CONF_WL_RSVD0                                                                               (0U)
#define MCSPI_CH1CONF_WL_27BITS                                                                              (26U)
#define MCSPI_CH1CONF_WL_23BITS                                                                              (22U)
#define MCSPI_CH1CONF_WL_RSVD2                                                                               (2U)
#define MCSPI_CH1CONF_WL_19BITS                                                                              (18U)
#define MCSPI_CH1CONF_WL_4BITS                                                                               (3U)
#define MCSPI_CH1CONF_WL_25BITS                                                                              (24U)
#define MCSPI_CH1CONF_WL_24BITS                                                                              (23U)
#define MCSPI_CH1CONF_WL_22BITS                                                                              (21U)
#define MCSPI_CH1CONF_WL_28BITS                                                                              (27U)

#define MCSPI_CH1CONF_DPE1_SHIFT                                                                            (17U)
#define MCSPI_CH1CONF_DPE1_MASK                                                                             (0x00020000U)
#define MCSPI_CH1CONF_DPE1_ENABLED                                                                           (0U)
#define MCSPI_CH1CONF_DPE1_DISABLED                                                                          (1U)

#define MCSPI_CH1CONF_EPOL_SHIFT                                                                            (6U)
#define MCSPI_CH1CONF_EPOL_MASK                                                                             (0x00000040U)
#define MCSPI_CH1CONF_EPOL_ACTIVELOW                                                                         (1U)
#define MCSPI_CH1CONF_EPOL_ACTIVEHIGH                                                                        (0U)

#define MCSPI_CH1CONF_DMAW_SHIFT                                                                            (14U)
#define MCSPI_CH1CONF_DMAW_MASK                                                                             (0x00004000U)
#define MCSPI_CH1CONF_DMAW_ENABLED                                                                           (1U)
#define MCSPI_CH1CONF_DMAW_DISABLED                                                                          (0U)

#define MCSPI_CH1CONF_TRM_SHIFT                                                                             (12U)
#define MCSPI_CH1CONF_TRM_MASK                                                                              (0x00003000U)
#define MCSPI_CH1CONF_TRM_TRANSONLY                                                                          (2U)
#define MCSPI_CH1CONF_TRM_RSVD                                                                               (3U)
#define MCSPI_CH1CONF_TRM_TRANSRECEI                                                                         (0U)
#define MCSPI_CH1CONF_TRM_RECEIVONLY                                                                         (1U)

#define MCSPI_CH1CONF_POL_SHIFT                                                                             (1U)
#define MCSPI_CH1CONF_POL_MASK                                                                              (0x00000002U)
#define MCSPI_CH1CONF_POL_ACTIVELOW                                                                          (1U)
#define MCSPI_CH1CONF_POL_ACTIVEHIGH                                                                         (0U)

#define MCSPI_CH1CONF_SBE_SHIFT                                                                             (23U)
#define MCSPI_CH1CONF_SBE_MASK                                                                              (0x00800000U)
#define MCSPI_CH1CONF_SBE_DISABLED                                                                           (0U)
#define MCSPI_CH1CONF_SBE_ENABLED                                                                            (1U)

#define MCSPI_CH1CONF_SBPOL_SHIFT                                                                           (24U)
#define MCSPI_CH1CONF_SBPOL_MASK                                                                            (0x01000000U)
#define MCSPI_CH1CONF_SBPOL_LOWLEVEL                                                                         (0U)
#define MCSPI_CH1CONF_SBPOL_HIGHLEVEL                                                                        (1U)

#define MCSPI_CH1CONF_TCS1_SHIFT                                                                            (25U)
#define MCSPI_CH1CONF_TCS1_MASK                                                                             (0x06000000U)
#define MCSPI_CH1CONF_TCS1_THREECYCLEDLY                                                                     (3U)
#define MCSPI_CH1CONF_TCS1_TWOCYCLEDLY                                                                       (2U)
#define MCSPI_CH1CONF_TCS1_ONECYCLEDLY                                                                       (1U)
#define MCSPI_CH1CONF_TCS1_ZEROCYCLEDLY                                                                      (0U)

#define MCSPI_CH1CONF_FFER_SHIFT                                                                            (28U)
#define MCSPI_CH1CONF_FFER_MASK                                                                             (0x10000000U)
#define MCSPI_CH1CONF_FFER_FFENABLED                                                                         (1U)
#define MCSPI_CH1CONF_FFER_FFDISABLED                                                                        (0U)

#define MCSPI_CH1CONF_FFEW_SHIFT                                                                            (27U)
#define MCSPI_CH1CONF_FFEW_MASK                                                                             (0x08000000U)
#define MCSPI_CH1CONF_FFEW_FFENABLED                                                                         (1U)
#define MCSPI_CH1CONF_FFEW_FFDISABLED                                                                        (0U)

#define MCSPI_CH1CONF_CLKG_SHIFT                                                                            (29U)
#define MCSPI_CH1CONF_CLKG_MASK                                                                             (0x20000000U)
#define MCSPI_CH1CONF_CLKG_ONECYCLE                                                                          (1U)
#define MCSPI_CH1CONF_CLKG_POWERTWO                                                                          (0U)

#define MCSPI_CH1STAT_RXS_SHIFT                                                                             (0U)
#define MCSPI_CH1STAT_RXS_MASK                                                                              (0x00000001U)
#define MCSPI_CH1STAT_RXS_EMPTY                                                                              (0U)
#define MCSPI_CH1STAT_RXS_FULL                                                                               (1U)

#define MCSPI_CH1STAT_EOT_SHIFT                                                                             (2U)
#define MCSPI_CH1STAT_EOT_MASK                                                                              (0x00000004U)
#define MCSPI_CH1STAT_EOT_COMPLETED                                                                          (1U)
#define MCSPI_CH1STAT_EOT_INPROGRESS                                                                         (0U)

#define MCSPI_CH1STAT_RESERVED_2_SHIFT                                                                      (7U)
#define MCSPI_CH1STAT_RESERVED_2_MASK                                                                       (0xffffff80U)

#define MCSPI_CH1STAT_TXS_SHIFT                                                                             (1U)
#define MCSPI_CH1STAT_TXS_MASK                                                                              (0x00000002U)
#define MCSPI_CH1STAT_TXS_EMPTY                                                                              (1U)
#define MCSPI_CH1STAT_TXS_FULL                                                                               (0U)

#define MCSPI_CH1STAT_RXFFE_SHIFT                                                                           (5U)
#define MCSPI_CH1STAT_RXFFE_MASK                                                                            (0x00000020U)
#define MCSPI_CH1STAT_RXFFE_EMPTY                                                                            (1U)
#define MCSPI_CH1STAT_RXFFE_NOTEMPTY                                                                         (0U)

#define MCSPI_CH1STAT_RXFFF_SHIFT                                                                           (6U)
#define MCSPI_CH1STAT_RXFFF_MASK                                                                            (0x00000040U)
#define MCSPI_CH1STAT_RXFFF_FULL                                                                             (1U)
#define MCSPI_CH1STAT_RXFFF_NOTFULL                                                                          (0U)

#define MCSPI_CH1STAT_TXFFE_SHIFT                                                                           (3U)
#define MCSPI_CH1STAT_TXFFE_MASK                                                                            (0x00000008U)
#define MCSPI_CH1STAT_TXFFE_EMPTY                                                                            (1U)
#define MCSPI_CH1STAT_TXFFE_NOTEMPTY                                                                         (0U)

#define MCSPI_CH1STAT_TXFFF_SHIFT                                                                           (4U)
#define MCSPI_CH1STAT_TXFFF_MASK                                                                            (0x00000010U)
#define MCSPI_CH1STAT_TXFFF_FULL                                                                             (1U)
#define MCSPI_CH1STAT_TXFFF_NOTFULL                                                                          (0U)

#define MCSPI_CH1CTRL_RESERVED_1_SHIFT                                                                      (1U)
#define MCSPI_CH1CTRL_RESERVED_1_MASK                                                                       (0x000000feU)

#define MCSPI_CH1CTRL_EN_SHIFT                                                                              (0U)
#define MCSPI_CH1CTRL_EN_MASK                                                                               (0x00000001U)
#define MCSPI_CH1CTRL_EN_ACT                                                                                 (1U)
#define MCSPI_CH1CTRL_EN_NACT                                                                                (0U)

#define MCSPI_CH1CTRL_EXTCLK_SHIFT                                                                          (8U)
#define MCSPI_CH1CTRL_EXTCLK_MASK                                                                           (0x0000ff00U)
#define MCSPI_CH1CTRL_EXTCLK_EXTZERO                                                                         (0U)
#define MCSPI_CH1CTRL_EXTCLK_EXTONE                                                                          (1U)
#define MCSPI_CH1CTRL_EXTCLK_EXT4080                                                                         (255U)

#define MCSPI_CH1CTRL_RESERVED_2_SHIFT                                                                      (16U)
#define MCSPI_CH1CTRL_RESERVED_2_MASK                                                                       (0xffff0000U)

#define MCSPI_TX1_TDATA_SHIFT                                                                               (0U)
#define MCSPI_TX1_TDATA_MASK                                                                                (0xffffffffU)

#define MCSPI_RX1_RDATA_SHIFT                                                                               (0U)
#define MCSPI_RX1_RDATA_MASK                                                                                (0xffffffffU)

#define MCSPI_CH2CONF_CLKD_SHIFT                                                                            (2U)
#define MCSPI_CH2CONF_CLKD_MASK                                                                             (0x0000003cU)
#define MCSPI_CH2CONF_CLKD_DIVBY4K                                                                           (12U)
#define MCSPI_CH2CONF_CLKD_DIVBY8                                                                            (3U)
#define MCSPI_CH2CONF_CLKD_DIVBY8K                                                                           (13U)
#define MCSPI_CH2CONF_CLKD_DIVBY2K                                                                           (11U)
#define MCSPI_CH2CONF_CLKD_DIVBY1K                                                                           (10U)
#define MCSPI_CH2CONF_CLKD_DIVBY512                                                                          (9U)
#define MCSPI_CH2CONF_CLKD_DIVBY32K                                                                          (15U)
#define MCSPI_CH2CONF_CLKD_DIVBY4                                                                            (2U)
#define MCSPI_CH2CONF_CLKD_DIVBY1                                                                            (0U)
#define MCSPI_CH2CONF_CLKD_DIVBY64                                                                           (6U)
#define MCSPI_CH2CONF_CLKD_DIVBY256                                                                          (8U)
#define MCSPI_CH2CONF_CLKD_DIVBY128                                                                          (7U)
#define MCSPI_CH2CONF_CLKD_DIVBY32                                                                           (5U)
#define MCSPI_CH2CONF_CLKD_DIVBY16K                                                                          (14U)
#define MCSPI_CH2CONF_CLKD_DIVBY16                                                                           (4U)
#define MCSPI_CH2CONF_CLKD_DIVBY2                                                                            (1U)

#define MCSPI_CH2CONF_RESERVED_0_SHIFT                                                                      (30U)
#define MCSPI_CH2CONF_RESERVED_0_MASK                                                                       (0xc0000000U)

#define MCSPI_CH2CONF_PHA_SHIFT                                                                             (0U)
#define MCSPI_CH2CONF_PHA_MASK                                                                              (0x00000001U)
#define MCSPI_CH2CONF_PHA_ODD                                                                                (0U)
#define MCSPI_CH2CONF_PHA_EVEN                                                                               (1U)

#define MCSPI_CH2CONF_TURBO_SHIFT                                                                           (19U)
#define MCSPI_CH2CONF_TURBO_MASK                                                                            (0x00080000U)
#define MCSPI_CH2CONF_TURBO_TURBO                                                                            (1U)
#define MCSPI_CH2CONF_TURBO_OFF                                                                              (0U)

#define MCSPI_CH2CONF_RESERVED_1_SHIFT                                                                      (21U)
#define MCSPI_CH2CONF_RESERVED_1_MASK                                                                       (0x00600000U)

#define MCSPI_CH2CONF_DPE0_SHIFT                                                                            (16U)
#define MCSPI_CH2CONF_DPE0_MASK                                                                             (0x00010000U)
#define MCSPI_CH2CONF_DPE0_DISABLED                                                                          (1U)
#define MCSPI_CH2CONF_DPE0_ENABLED                                                                           (0U)

#define MCSPI_CH2CONF_IS_SHIFT                                                                              (18U)
#define MCSPI_CH2CONF_IS_MASK                                                                               (0x00040000U)
#define MCSPI_CH2CONF_IS_LINE0                                                                               (0U)
#define MCSPI_CH2CONF_IS_LINE1                                                                               (1U)

#define MCSPI_CH2CONF_DMAR_SHIFT                                                                            (15U)
#define MCSPI_CH2CONF_DMAR_MASK                                                                             (0x00008000U)
#define MCSPI_CH2CONF_DMAR_DISABLED                                                                          (0U)
#define MCSPI_CH2CONF_DMAR_ENABLED                                                                           (1U)

#define MCSPI_CH2CONF_FORCE_SHIFT                                                                           (20U)
#define MCSPI_CH2CONF_FORCE_MASK                                                                            (0x00100000U)
#define MCSPI_CH2CONF_FORCE_DEASSERT                                                                         (0U)
#define MCSPI_CH2CONF_FORCE_ASSERT                                                                           (1U)

#define MCSPI_CH2CONF_WL_SHIFT                                                                              (7U)
#define MCSPI_CH2CONF_WL_MASK                                                                               (0x00000f80U)
#define MCSPI_CH2CONF_WL_21BITS                                                                              (20U)
#define MCSPI_CH2CONF_WL_26BITS                                                                              (25U)
#define MCSPI_CH2CONF_WL_18BITS                                                                              (17U)
#define MCSPI_CH2CONF_WL_20BITS                                                                              (19U)
#define MCSPI_CH2CONF_WL_5BITS                                                                               (4U)
#define MCSPI_CH2CONF_WL_6BITS                                                                               (5U)
#define MCSPI_CH2CONF_WL_11BITS                                                                              (10U)
#define MCSPI_CH2CONF_WL_8BITS                                                                               (7U)
#define MCSPI_CH2CONF_WL_13BITS                                                                              (12U)
#define MCSPI_CH2CONF_WL_29BITS                                                                              (28U)
#define MCSPI_CH2CONF_WL_12BITS                                                                              (11U)
#define MCSPI_CH2CONF_WL_32BITS                                                                              (31U)
#define MCSPI_CH2CONF_WL_31BITS                                                                              (30U)
#define MCSPI_CH2CONF_WL_30BITS                                                                              (29U)
#define MCSPI_CH2CONF_WL_9BITS                                                                               (8U)
#define MCSPI_CH2CONF_WL_7BITS                                                                               (6U)
#define MCSPI_CH2CONF_WL_10BITS                                                                              (9U)
#define MCSPI_CH2CONF_WL_16BITS                                                                              (15U)
#define MCSPI_CH2CONF_WL_17BITS                                                                              (16U)
#define MCSPI_CH2CONF_WL_14BITS                                                                              (13U)
#define MCSPI_CH2CONF_WL_15BITS                                                                              (14U)
#define MCSPI_CH2CONF_WL_RSVD1                                                                               (1U)
#define MCSPI_CH2CONF_WL_RSVD0                                                                               (0U)
#define MCSPI_CH2CONF_WL_27BITS                                                                              (26U)
#define MCSPI_CH2CONF_WL_23BITS                                                                              (22U)
#define MCSPI_CH2CONF_WL_RSVD2                                                                               (2U)
#define MCSPI_CH2CONF_WL_19BITS                                                                              (18U)
#define MCSPI_CH2CONF_WL_4BITS                                                                               (3U)
#define MCSPI_CH2CONF_WL_25BITS                                                                              (24U)
#define MCSPI_CH2CONF_WL_24BITS                                                                              (23U)
#define MCSPI_CH2CONF_WL_22BITS                                                                              (21U)
#define MCSPI_CH2CONF_WL_28BITS                                                                              (27U)

#define MCSPI_CH2CONF_DPE1_SHIFT                                                                            (17U)
#define MCSPI_CH2CONF_DPE1_MASK                                                                             (0x00020000U)
#define MCSPI_CH2CONF_DPE1_ENABLED                                                                           (0U)
#define MCSPI_CH2CONF_DPE1_DISABLED                                                                          (1U)

#define MCSPI_CH2CONF_EPOL_SHIFT                                                                            (6U)
#define MCSPI_CH2CONF_EPOL_MASK                                                                             (0x00000040U)
#define MCSPI_CH2CONF_EPOL_ACTIVELOW                                                                         (1U)
#define MCSPI_CH2CONF_EPOL_ACTIVEHIGH                                                                        (0U)

#define MCSPI_CH2CONF_DMAW_SHIFT                                                                            (14U)
#define MCSPI_CH2CONF_DMAW_MASK                                                                             (0x00004000U)
#define MCSPI_CH2CONF_DMAW_ENABLED                                                                           (1U)
#define MCSPI_CH2CONF_DMAW_DISABLED                                                                          (0U)

#define MCSPI_CH2CONF_TRM_SHIFT                                                                             (12U)
#define MCSPI_CH2CONF_TRM_MASK                                                                              (0x00003000U)
#define MCSPI_CH2CONF_TRM_TRANSONLY                                                                          (2U)
#define MCSPI_CH2CONF_TRM_RSVD                                                                               (3U)
#define MCSPI_CH2CONF_TRM_TRANSRECEI                                                                         (0U)
#define MCSPI_CH2CONF_TRM_RECEIVONLY                                                                         (1U)

#define MCSPI_CH2CONF_POL_SHIFT                                                                             (1U)
#define MCSPI_CH2CONF_POL_MASK                                                                              (0x00000002U)
#define MCSPI_CH2CONF_POL_ACTIVELOW                                                                          (1U)
#define MCSPI_CH2CONF_POL_ACTIVEHIGH                                                                         (0U)

#define MCSPI_CH2CONF_SBE_SHIFT                                                                             (23U)
#define MCSPI_CH2CONF_SBE_MASK                                                                              (0x00800000U)
#define MCSPI_CH2CONF_SBE_DISABLED                                                                           (0U)
#define MCSPI_CH2CONF_SBE_ENABLED                                                                            (1U)

#define MCSPI_CH2CONF_SBPOL_SHIFT                                                                           (24U)
#define MCSPI_CH2CONF_SBPOL_MASK                                                                            (0x01000000U)
#define MCSPI_CH2CONF_SBPOL_LOWLEVEL                                                                         (0U)
#define MCSPI_CH2CONF_SBPOL_HIGHLEVEL                                                                        (1U)

#define MCSPI_CH2CONF_TCS2_SHIFT                                                                            (25U)
#define MCSPI_CH2CONF_TCS2_MASK                                                                             (0x06000000U)
#define MCSPI_CH2CONF_TCS2_THREECYCLEDLY                                                                     (3U)
#define MCSPI_CH2CONF_TCS2_TWOCYCLEDLY                                                                       (2U)
#define MCSPI_CH2CONF_TCS2_ONECYCLEDLY                                                                       (1U)
#define MCSPI_CH2CONF_TCS2_ZEROCYCLEDLY                                                                      (0U)

#define MCSPI_CH2CONF_FFER_SHIFT                                                                            (28U)
#define MCSPI_CH2CONF_FFER_MASK                                                                             (0x10000000U)
#define MCSPI_CH2CONF_FFER_FFENABLED                                                                         (1U)
#define MCSPI_CH2CONF_FFER_FFDISABLED                                                                        (0U)

#define MCSPI_CH2CONF_FFEW_SHIFT                                                                            (27U)
#define MCSPI_CH2CONF_FFEW_MASK                                                                             (0x08000000U)
#define MCSPI_CH2CONF_FFEW_FFENABLED                                                                         (1U)
#define MCSPI_CH2CONF_FFEW_FFDISABLED                                                                        (0U)

#define MCSPI_CH2CONF_CLKG_SHIFT                                                                            (29U)
#define MCSPI_CH2CONF_CLKG_MASK                                                                             (0x20000000U)
#define MCSPI_CH2CONF_CLKG_ONECYCLE                                                                          (1U)
#define MCSPI_CH2CONF_CLKG_POWERTWO                                                                          (0U)

#define MCSPI_CH2STAT_RXS_SHIFT                                                                             (0U)
#define MCSPI_CH2STAT_RXS_MASK                                                                              (0x00000001U)
#define MCSPI_CH2STAT_RXS_EMPTY                                                                              (0U)
#define MCSPI_CH2STAT_RXS_FULL                                                                               (1U)

#define MCSPI_CH2STAT_EOT_SHIFT                                                                             (2U)
#define MCSPI_CH2STAT_EOT_MASK                                                                              (0x00000004U)
#define MCSPI_CH2STAT_EOT_COMPLETED                                                                          (1U)
#define MCSPI_CH2STAT_EOT_INPROGRESS                                                                         (0U)

#define MCSPI_CH2STAT_RESERVED_2_SHIFT                                                                      (7U)
#define MCSPI_CH2STAT_RESERVED_2_MASK                                                                       (0xffffff80U)

#define MCSPI_CH2STAT_TXS_SHIFT                                                                             (1U)
#define MCSPI_CH2STAT_TXS_MASK                                                                              (0x00000002U)
#define MCSPI_CH2STAT_TXS_EMPTY                                                                              (1U)
#define MCSPI_CH2STAT_TXS_FULL                                                                               (0U)

#define MCSPI_CH2STAT_RXFFE_SHIFT                                                                           (5U)
#define MCSPI_CH2STAT_RXFFE_MASK                                                                            (0x00000020U)
#define MCSPI_CH2STAT_RXFFE_EMPTY                                                                            (1U)
#define MCSPI_CH2STAT_RXFFE_NOTEMPTY                                                                         (0U)

#define MCSPI_CH2STAT_RXFFF_SHIFT                                                                           (6U)
#define MCSPI_CH2STAT_RXFFF_MASK                                                                            (0x00000040U)
#define MCSPI_CH2STAT_RXFFF_FULL                                                                             (1U)
#define MCSPI_CH2STAT_RXFFF_NOTFULL                                                                          (0U)

#define MCSPI_CH2STAT_TXFFE_SHIFT                                                                           (3U)
#define MCSPI_CH2STAT_TXFFE_MASK                                                                            (0x00000008U)
#define MCSPI_CH2STAT_TXFFE_EMPTY                                                                            (1U)
#define MCSPI_CH2STAT_TXFFE_NOTEMPTY                                                                         (0U)

#define MCSPI_CH2STAT_TXFFF_SHIFT                                                                           (4U)
#define MCSPI_CH2STAT_TXFFF_MASK                                                                            (0x00000010U)
#define MCSPI_CH2STAT_TXFFF_FULL                                                                             (1U)
#define MCSPI_CH2STAT_TXFFF_NOTFULL                                                                          (0U)

#define MCSPI_CH2CTRL_RESERVED_1_SHIFT                                                                      (1U)
#define MCSPI_CH2CTRL_RESERVED_1_MASK                                                                       (0x000000feU)

#define MCSPI_CH2CTRL_EN_SHIFT                                                                              (0U)
#define MCSPI_CH2CTRL_EN_MASK                                                                               (0x00000001U)
#define MCSPI_CH2CTRL_EN_ACT                                                                                 (1U)
#define MCSPI_CH2CTRL_EN_NACT                                                                                (0U)

#define MCSPI_CH2CTRL_EXTCLK_SHIFT                                                                          (8U)
#define MCSPI_CH2CTRL_EXTCLK_MASK                                                                           (0x0000ff00U)
#define MCSPI_CH2CTRL_EXTCLK_EXTZERO                                                                         (0U)
#define MCSPI_CH2CTRL_EXTCLK_EXTONE                                                                          (1U)
#define MCSPI_CH2CTRL_EXTCLK_EXT4080                                                                         (255U)

#define MCSPI_CH2CTRL_RESERVED_2_SHIFT                                                                      (16U)
#define MCSPI_CH2CTRL_RESERVED_2_MASK                                                                       (0xffff0000U)

#define MCSPI_TX2_TDATA_SHIFT                                                                               (0U)
#define MCSPI_TX2_TDATA_MASK                                                                                (0xffffffffU)

#define MCSPI_RX2_RDATA_SHIFT                                                                               (0U)
#define MCSPI_RX2_RDATA_MASK                                                                                (0xffffffffU)

#define MCSPI_CH3CONF_CLKD_SHIFT                                                                            (2U)
#define MCSPI_CH3CONF_CLKD_MASK                                                                             (0x0000003cU)
#define MCSPI_CH3CONF_CLKD_DIVBY4K                                                                           (12U)
#define MCSPI_CH3CONF_CLKD_DIVBY8                                                                            (3U)
#define MCSPI_CH3CONF_CLKD_DIVBY8K                                                                           (13U)
#define MCSPI_CH3CONF_CLKD_DIVBY2K                                                                           (11U)
#define MCSPI_CH3CONF_CLKD_DIVBY1K                                                                           (10U)
#define MCSPI_CH3CONF_CLKD_DIVBY512                                                                          (9U)
#define MCSPI_CH3CONF_CLKD_DIVBY32K                                                                          (15U)
#define MCSPI_CH3CONF_CLKD_DIVBY4                                                                            (2U)
#define MCSPI_CH3CONF_CLKD_DIVBY1                                                                            (0U)
#define MCSPI_CH3CONF_CLKD_DIVBY64                                                                           (6U)
#define MCSPI_CH3CONF_CLKD_DIVBY256                                                                          (8U)
#define MCSPI_CH3CONF_CLKD_DIVBY128                                                                          (7U)
#define MCSPI_CH3CONF_CLKD_DIVBY32                                                                           (5U)
#define MCSPI_CH3CONF_CLKD_DIVBY16K                                                                          (14U)
#define MCSPI_CH3CONF_CLKD_DIVBY16                                                                           (4U)
#define MCSPI_CH3CONF_CLKD_DIVBY2                                                                            (1U)

#define MCSPI_CH3CONF_RESERVED_0_SHIFT                                                                      (30U)
#define MCSPI_CH3CONF_RESERVED_0_MASK                                                                       (0xc0000000U)

#define MCSPI_CH3CONF_PHA_SHIFT                                                                             (0U)
#define MCSPI_CH3CONF_PHA_MASK                                                                              (0x00000001U)
#define MCSPI_CH3CONF_PHA_ODD                                                                                (0U)
#define MCSPI_CH3CONF_PHA_EVEN                                                                               (1U)

#define MCSPI_CH3CONF_TURBO_SHIFT                                                                           (19U)
#define MCSPI_CH3CONF_TURBO_MASK                                                                            (0x00080000U)
#define MCSPI_CH3CONF_TURBO_TURBO                                                                            (1U)
#define MCSPI_CH3CONF_TURBO_OFF                                                                              (0U)

#define MCSPI_CH3CONF_RESERVED_1_SHIFT                                                                      (21U)
#define MCSPI_CH3CONF_RESERVED_1_MASK                                                                       (0x00600000U)

#define MCSPI_CH3CONF_DPE0_SHIFT                                                                            (16U)
#define MCSPI_CH3CONF_DPE0_MASK                                                                             (0x00010000U)
#define MCSPI_CH3CONF_DPE0_DISABLED                                                                          (1U)
#define MCSPI_CH3CONF_DPE0_ENABLED                                                                           (0U)

#define MCSPI_CH3CONF_IS_SHIFT                                                                              (18U)
#define MCSPI_CH3CONF_IS_MASK                                                                               (0x00040000U)
#define MCSPI_CH3CONF_IS_LINE0                                                                               (0U)
#define MCSPI_CH3CONF_IS_LINE1                                                                               (1U)

#define MCSPI_CH3CONF_DMAR_SHIFT                                                                            (15U)
#define MCSPI_CH3CONF_DMAR_MASK                                                                             (0x00008000U)
#define MCSPI_CH3CONF_DMAR_DISABLED                                                                          (0U)
#define MCSPI_CH3CONF_DMAR_ENABLED                                                                           (1U)

#define MCSPI_CH3CONF_FORCE_SHIFT                                                                           (20U)
#define MCSPI_CH3CONF_FORCE_MASK                                                                            (0x00100000U)
#define MCSPI_CH3CONF_FORCE_DEASSERT                                                                         (0U)
#define MCSPI_CH3CONF_FORCE_ASSERT                                                                           (1U)

#define MCSPI_CH3CONF_WL_SHIFT                                                                              (7U)
#define MCSPI_CH3CONF_WL_MASK                                                                               (0x00000f80U)
#define MCSPI_CH3CONF_WL_21BITS                                                                              (20U)
#define MCSPI_CH3CONF_WL_26BITS                                                                              (25U)
#define MCSPI_CH3CONF_WL_18BITS                                                                              (17U)
#define MCSPI_CH3CONF_WL_20BITS                                                                              (19U)
#define MCSPI_CH3CONF_WL_5BITS                                                                               (4U)
#define MCSPI_CH3CONF_WL_6BITS                                                                               (5U)
#define MCSPI_CH3CONF_WL_11BITS                                                                              (10U)
#define MCSPI_CH3CONF_WL_8BITS                                                                               (7U)
#define MCSPI_CH3CONF_WL_13BITS                                                                              (12U)
#define MCSPI_CH3CONF_WL_29BITS                                                                              (28U)
#define MCSPI_CH3CONF_WL_12BITS                                                                              (11U)
#define MCSPI_CH3CONF_WL_32BITS                                                                              (31U)
#define MCSPI_CH3CONF_WL_31BITS                                                                              (30U)
#define MCSPI_CH3CONF_WL_30BITS                                                                              (29U)
#define MCSPI_CH3CONF_WL_9BITS                                                                               (8U)
#define MCSPI_CH3CONF_WL_7BITS                                                                               (6U)
#define MCSPI_CH3CONF_WL_10BITS                                                                              (9U)
#define MCSPI_CH3CONF_WL_16BITS                                                                              (15U)
#define MCSPI_CH3CONF_WL_17BITS                                                                              (16U)
#define MCSPI_CH3CONF_WL_14BITS                                                                              (13U)
#define MCSPI_CH3CONF_WL_15BITS                                                                              (14U)
#define MCSPI_CH3CONF_WL_RSVD1                                                                               (1U)
#define MCSPI_CH3CONF_WL_RSVD0                                                                               (0U)
#define MCSPI_CH3CONF_WL_27BITS                                                                              (26U)
#define MCSPI_CH3CONF_WL_23BITS                                                                              (22U)
#define MCSPI_CH3CONF_WL_RSVD2                                                                               (2U)
#define MCSPI_CH3CONF_WL_19BITS                                                                              (18U)
#define MCSPI_CH3CONF_WL_4BITS                                                                               (3U)
#define MCSPI_CH3CONF_WL_25BITS                                                                              (24U)
#define MCSPI_CH3CONF_WL_24BITS                                                                              (23U)
#define MCSPI_CH3CONF_WL_22BITS                                                                              (21U)
#define MCSPI_CH3CONF_WL_28BITS                                                                              (27U)

#define MCSPI_CH3CONF_DPE1_SHIFT                                                                            (17U)
#define MCSPI_CH3CONF_DPE1_MASK                                                                             (0x00020000U)
#define MCSPI_CH3CONF_DPE1_ENABLED                                                                           (0U)
#define MCSPI_CH3CONF_DPE1_DISABLED                                                                          (1U)

#define MCSPI_CH3CONF_EPOL_SHIFT                                                                            (6U)
#define MCSPI_CH3CONF_EPOL_MASK                                                                             (0x00000040U)
#define MCSPI_CH3CONF_EPOL_ACTIVELOW                                                                         (1U)
#define MCSPI_CH3CONF_EPOL_ACTIVEHIGH                                                                        (0U)

#define MCSPI_CH3CONF_DMAW_SHIFT                                                                            (14U)
#define MCSPI_CH3CONF_DMAW_MASK                                                                             (0x00004000U)
#define MCSPI_CH3CONF_DMAW_ENABLED                                                                           (1U)
#define MCSPI_CH3CONF_DMAW_DISABLED                                                                          (0U)

#define MCSPI_CH3CONF_TRM_SHIFT                                                                             (12U)
#define MCSPI_CH3CONF_TRM_MASK                                                                              (0x00003000U)
#define MCSPI_CH3CONF_TRM_TRANSONLY                                                                          (2U)
#define MCSPI_CH3CONF_TRM_RSVD                                                                               (3U)
#define MCSPI_CH3CONF_TRM_TRANSRECEI                                                                         (0U)
#define MCSPI_CH3CONF_TRM_RECEIVONLY                                                                         (1U)

#define MCSPI_CH3CONF_POL_SHIFT                                                                             (1U)
#define MCSPI_CH3CONF_POL_MASK                                                                              (0x00000002U)
#define MCSPI_CH3CONF_POL_ACTIVELOW                                                                          (1U)
#define MCSPI_CH3CONF_POL_ACTIVEHIGH                                                                         (0U)

#define MCSPI_CH3CONF_SBE_SHIFT                                                                             (23U)
#define MCSPI_CH3CONF_SBE_MASK                                                                              (0x00800000U)
#define MCSPI_CH3CONF_SBE_DISABLED                                                                           (0U)
#define MCSPI_CH3CONF_SBE_ENABLED                                                                            (1U)

#define MCSPI_CH3CONF_SBPOL_SHIFT                                                                           (24U)
#define MCSPI_CH3CONF_SBPOL_MASK                                                                            (0x01000000U)
#define MCSPI_CH3CONF_SBPOL_LOWLEVEL                                                                         (0U)
#define MCSPI_CH3CONF_SBPOL_HIGHLEVEL                                                                        (1U)

#define MCSPI_CH3CONF_TCS3_SHIFT                                                                            (25U)
#define MCSPI_CH3CONF_TCS3_MASK                                                                             (0x06000000U)
#define MCSPI_CH3CONF_TCS3_THREECYCLEDLY                                                                     (3U)
#define MCSPI_CH3CONF_TCS3_TWOCYCLEDLY                                                                       (2U)
#define MCSPI_CH3CONF_TCS3_ONECYCLEDLY                                                                       (1U)
#define MCSPI_CH3CONF_TCS3_ZEROCYCLEDLY                                                                      (0U)

#define MCSPI_CH3CONF_FFER_SHIFT                                                                            (28U)
#define MCSPI_CH3CONF_FFER_MASK                                                                             (0x10000000U)
#define MCSPI_CH3CONF_FFER_FFENABLED                                                                         (1U)
#define MCSPI_CH3CONF_FFER_FFDISABLED                                                                        (0U)

#define MCSPI_CH3CONF_FFEW_SHIFT                                                                            (27U)
#define MCSPI_CH3CONF_FFEW_MASK                                                                             (0x08000000U)
#define MCSPI_CH3CONF_FFEW_FFENABLED                                                                         (1U)
#define MCSPI_CH3CONF_FFEW_FFDISABLED                                                                        (0U)

#define MCSPI_CH3CONF_CLKG_SHIFT                                                                            (29U)
#define MCSPI_CH3CONF_CLKG_MASK                                                                             (0x20000000U)
#define MCSPI_CH3CONF_CLKG_ONECYCLE                                                                          (1U)
#define MCSPI_CH3CONF_CLKG_POWERTWO                                                                          (0U)

#define MCSPI_CH3STAT_RXS_SHIFT                                                                             (0U)
#define MCSPI_CH3STAT_RXS_MASK                                                                              (0x00000001U)
#define MCSPI_CH3STAT_RXS_EMPTY                                                                              (0U)
#define MCSPI_CH3STAT_RXS_FULL                                                                               (1U)

#define MCSPI_CH3STAT_EOT_SHIFT                                                                             (2U)
#define MCSPI_CH3STAT_EOT_MASK                                                                              (0x00000004U)
#define MCSPI_CH3STAT_EOT_COMPLETED                                                                          (1U)
#define MCSPI_CH3STAT_EOT_INPROGRESS                                                                         (0U)

#define MCSPI_CH3STAT_RESERVED_2_SHIFT                                                                      (7U)
#define MCSPI_CH3STAT_RESERVED_2_MASK                                                                       (0xffffff80U)

#define MCSPI_CH3STAT_TXS_SHIFT                                                                             (1U)
#define MCSPI_CH3STAT_TXS_MASK                                                                              (0x00000002U)
#define MCSPI_CH3STAT_TXS_EMPTY                                                                              (1U)
#define MCSPI_CH3STAT_TXS_FULL                                                                               (0U)

#define MCSPI_CH3STAT_RXFFE_SHIFT                                                                           (5U)
#define MCSPI_CH3STAT_RXFFE_MASK                                                                            (0x00000020U)
#define MCSPI_CH3STAT_RXFFE_EMPTY                                                                            (1U)
#define MCSPI_CH3STAT_RXFFE_NOTEMPTY                                                                         (0U)

#define MCSPI_CH3STAT_RXFFF_SHIFT                                                                           (6U)
#define MCSPI_CH3STAT_RXFFF_MASK                                                                            (0x00000040U)
#define MCSPI_CH3STAT_RXFFF_FULL                                                                             (1U)
#define MCSPI_CH3STAT_RXFFF_NOTFULL                                                                          (0U)

#define MCSPI_CH3STAT_TXFFE_SHIFT                                                                           (3U)
#define MCSPI_CH3STAT_TXFFE_MASK                                                                            (0x00000008U)
#define MCSPI_CH3STAT_TXFFE_EMPTY                                                                            (1U)
#define MCSPI_CH3STAT_TXFFE_NOTEMPTY                                                                         (0U)

#define MCSPI_CH3STAT_TXFFF_SHIFT                                                                           (4U)
#define MCSPI_CH3STAT_TXFFF_MASK                                                                            (0x00000010U)
#define MCSPI_CH3STAT_TXFFF_FULL                                                                             (1U)
#define MCSPI_CH3STAT_TXFFF_NOTFULL                                                                          (0U)

#define MCSPI_CH3CTRL_RESERVED_1_SHIFT                                                                      (1U)
#define MCSPI_CH3CTRL_RESERVED_1_MASK                                                                       (0x000000feU)

#define MCSPI_CH3CTRL_EN_SHIFT                                                                              (0U)
#define MCSPI_CH3CTRL_EN_MASK                                                                               (0x00000001U)
#define MCSPI_CH3CTRL_EN_ACT                                                                                 (1U)
#define MCSPI_CH3CTRL_EN_NACT                                                                                (0U)

#define MCSPI_CH3CTRL_EXTCLK_SHIFT                                                                          (8U)
#define MCSPI_CH3CTRL_EXTCLK_MASK                                                                           (0x0000ff00U)
#define MCSPI_CH3CTRL_EXTCLK_EXTZERO                                                                         (0U)
#define MCSPI_CH3CTRL_EXTCLK_EXTONE                                                                          (1U)
#define MCSPI_CH3CTRL_EXTCLK_EXT4080                                                                         (255U)

#define MCSPI_CH3CTRL_RESERVED_2_SHIFT                                                                      (16U)
#define MCSPI_CH3CTRL_RESERVED_2_MASK                                                                       (0xffff0000U)

#define MCSPI_TX3_TDATA_SHIFT                                                                               (0U)
#define MCSPI_TX3_TDATA_MASK                                                                                (0xffffffffU)

#define MCSPI_RX3_RDATA_SHIFT                                                                               (0U)
#define MCSPI_RX3_RDATA_MASK                                                                                (0xffffffffU)

#define MCSPI_XFERLEVEL_AEL_SHIFT                                                                           (0U)
#define MCSPI_XFERLEVEL_AEL_MASK                                                                            (0x000000ffU)
#define MCSPI_XFERLEVEL_AEL_256BYTES                                                                         (255U)
#define MCSPI_XFERLEVEL_AEL_255BYTES                                                                         (254U)
#define MCSPI_XFERLEVEL_AEL_2BYTES                                                                           (1U)
#define MCSPI_XFERLEVEL_AEL_1BYTE                                                                            (0U)

#define MCSPI_XFERLEVEL_WCNT_SHIFT                                                                          (16U)
#define MCSPI_XFERLEVEL_WCNT_MASK                                                                           (0xffff0000U)
#define MCSPI_XFERLEVEL_WCNT_65535WORD                                                                       (65535U)
#define MCSPI_XFERLEVEL_WCNT_65534WORD                                                                       (65534U)
#define MCSPI_XFERLEVEL_WCNT_1WORD                                                                           (1U)
#define MCSPI_XFERLEVEL_WCNT_DISABLE                                                                         (0U)

#define MCSPI_XFERLEVEL_AFL_SHIFT                                                                           (8U)
#define MCSPI_XFERLEVEL_AFL_MASK                                                                            (0x0000ff00U)
#define MCSPI_XFERLEVEL_AFL_256BYTES                                                                         (255U)
#define MCSPI_XFERLEVEL_AFL_255BYTES                                                                         (254U)
#define MCSPI_XFERLEVEL_AFL_2BYTES                                                                           (1U)
#define MCSPI_XFERLEVEL_AFL_1BYTE                                                                            (0U)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_MCSPI_H_ */
