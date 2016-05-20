/******************************************************************************
*
* hw_dsp_system.h - register-level header file for DSP
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
#ifndef HW_DSP_SYSTEM_H_
#define HW_DSP_SYSTEM_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions 
****************************************************************************************************/
#define DSP_REVISION                                                                                        (0x0U)
#define DSP_HWINFO                                                                                          (0x4U)
#define DSP_SYSCONFIG                                                                                       (0x8U)
#define DSP_STAT                                                                                            (0xcU)
#define DSP_DISC_CONFIG                                                                                     (0x10U)
#define DSP_BUS_CONFIG                                                                                      (0x14U)
#define DSP_MMU_CONFIG                                                                                      (0x18U)
#define DSP_IRQWAKEEN0                                                                                      (uint32_t)(0x20U)
#define DSP_IRQWAKEEN1                                                                                      (0x24U)
#define DSP_DMAWAKEEN0                                                                                      (uint32_t)(0x30U)
#define DSP_DMAWAKEEN1                                                                                      (0x34U)
#define DSP_EVTOUT_SET                                                                                      (0x40U)
#define DSP_EVTOUT_CLR                                                                                      (0x44U)
#define DSP_ERRINT_IRQSTATUS_RAW                                                                            (0x50U)
#define DSP_ERRINT_IRQSTATUS                                                                                (0x54U)
#define DSP_ERRINT_IRQENABLE_SET                                                                            (0x58U)
#define DSP_ERRINT_IRQENABLE_CLR                                                                            (0x5cU)
#define DSP_EDMAWAKE0_IRQSTATUS_RAW                                                                         (0x60U)
#define DSP_EDMAWAKE0_IRQSTATUS                                                                             (0x64U)
#define DSP_EDMAWAKE0_IRQENABLE_SET                                                                         (0x68U)
#define DSP_EDMAWAKE0_IRQENABLE_CLR                                                                         (0x6cU)
#define DSP_EDMAWAKE1_IRQSTATUS_RAW                                                                         (0x70U)
#define DSP_EDMAWAKE1_IRQSTATUS                                                                             (0x74U)
#define DSP_EDMAWAKE1_IRQENABLE_SET                                                                         (0x78U)
#define DSP_EDMAWAKE1_IRQENABLE_CLR                                                                         (0x7cU)
#define DSP_HW_DBGOUT_SEL                                                                                   (0xf8U)
#define DSP_HW_DBGOUT_VAL                                                                                   (0xfcU)

/****************************************************************************************************
* Field Definition Macros 
****************************************************************************************************/

#define DSP_REVISION_REVISION_SHIFT                                                                         (0U)
#define DSP_REVISION_REVISION_MASK                                                                          (0xffffffffU)

#define DSP_HWINFO_NUM_SHIFT                                                                                (0U)
#define DSP_HWINFO_NUM_MASK                                                                                 (0x0000000fU)

#define DSP_HWINFO_INFO_SHIFT                                                                               (4U)
#define DSP_HWINFO_INFO_MASK                                                                                (0xfffffff0U)

#define DSP_SYSCONFIG_SOFTRESET_SHIFT                                                                       (0U)
#define DSP_SYSCONFIG_SOFTRESET_MASK                                                                        (0x00000001U)

#define DSP_SYSCONFIG_FREE_EMU_SHIFT                                                                        (1U)
#define DSP_SYSCONFIG_FREE_EMU_MASK                                                                         (0x00000002U)

#define DSP_SYSCONFIG_IDLEMODE_SHIFT                                                                        (2U)
#define DSP_SYSCONFIG_IDLEMODE_MASK                                                                         (0x0000000cU)
#define DSP_SYSCONFIG_IDLEMODE_SMARTIDLEWKUP                                                                 (3U)
#define DSP_SYSCONFIG_IDLEMODE_FORCE_IDLE                                                                    (0U)
#define DSP_SYSCONFIG_IDLEMODE_NO_IDLE                                                                       (1U)
#define DSP_SYSCONFIG_IDLEMODE_SMART_IDLE                                                                    (2U)

#define DSP_SYSCONFIG_STANDBYMODE_SHIFT                                                                     (4U)
#define DSP_SYSCONFIG_STANDBYMODE_MASK                                                                      (0x00000030U)
#define DSP_SYSCONFIG_STANDBYMODE_SMART_STANDBY_WKUP                                                         (3U)
#define DSP_SYSCONFIG_STANDBYMODE_SMART_STAND_BY                                                             (2U)
#define DSP_SYSCONFIG_STANDBYMODE_FORCE_STANDBY                                                              (0U)
#define DSP_SYSCONFIG_STANDBYMODE_NO_STANDBY                                                                 (1U)

#define DSP_SYSCONFIG_RESERVED_SHIFT                                                                        (9U)
#define DSP_SYSCONFIG_RESERVED_MASK                                                                         (0xfffffe00U)

#define DSP_SYSCONFIG_DSP_IDLEREQ_SHIFT                                                                     (8U)
#define DSP_SYSCONFIG_DSP_IDLEREQ_MASK                                                                      (0x00000100U)
#define DSP_SYSCONFIG_DSP_IDLEREQ_NOREQ                                                                      (0U)
#define DSP_SYSCONFIG_DSP_IDLEREQ_IDLEREQ                                                                    (1U)

#define DSP_SYSCONFIG_RESERVED_2_SHIFT                                                                      (6U)
#define DSP_SYSCONFIG_RESERVED_2_MASK                                                                       (0x000000c0U)

#define DSP_STAT_C66X_STAT_SHIFT                                                                            (0U)
#define DSP_STAT_C66X_STAT_MASK                                                                             (0x00000001U)
#define DSP_STAT_C66X_STAT_IDLE                                                                              (0U)
#define DSP_STAT_C66X_STAT_ACTIVE                                                                            (1U)

#define DSP_STAT_TC0_STAT_SHIFT                                                                             (1U)
#define DSP_STAT_TC0_STAT_MASK                                                                              (0x00000002U)
#define DSP_STAT_TC0_STAT_IDLE                                                                               (0U)
#define DSP_STAT_TC0_STAT_ACTIVE                                                                             (1U)

#define DSP_STAT_TC1_STAT_SHIFT                                                                             (2U)
#define DSP_STAT_TC1_STAT_MASK                                                                              (0x00000004U)
#define DSP_STAT_TC1_STAT_IDLE                                                                               (0U)
#define DSP_STAT_TC1_STAT_ACTIVE                                                                             (1U)

#define DSP_STAT_RESERVED_SHIFT                                                                             (3U)
#define DSP_STAT_RESERVED_MASK                                                                              (0x00000008U)

#define DSP_STAT_OCPI_DISC_STAT_SHIFT                                                                       (4U)
#define DSP_STAT_OCPI_DISC_STAT_MASK                                                                        (0x00000030U)
#define DSP_STAT_OCPI_DISC_STAT_OCP_INITIATOR_DISCONNECT                                                     (0U)
#define DSP_STAT_OCPI_DISC_STAT_OCP_TRYING_TO_DISCONNECT                                                     (1U)
#define DSP_STAT_OCPI_DISC_STAT_OCP_INITIATOR_ACTIVE                                                         (2U)

#define DSP_STAT_RESERVED_2_SHIFT                                                                           (6U)
#define DSP_STAT_RESERVED_2_MASK                                                                            (0xffffffc0U)

#define DSP_DISC_CONFIG_OCPI_DISC_SHIFT                                                                     (0U)
#define DSP_DISC_CONFIG_OCPI_DISC_MASK                                                                      (0x00000001U)
#define DSP_DISC_CONFIG_OCPI_DISC_WRITE0                                                                     (0U)
#define DSP_DISC_CONFIG_OCPI_DISC_WRITE1                                                                     (1U)
#define DSP_DISC_CONFIG_OCPI_DISC_READ0                                                                      (0U)
#define DSP_DISC_CONFIG_OCPI_DISC_READ1                                                                      (1U)

#define DSP_DISC_CONFIG_RESERVED_SHIFT                                                                      (1U)
#define DSP_DISC_CONFIG_RESERVED_MASK                                                                       (0xfffffffeU)

#define DSP_BUS_CONFIG_TC0_DBS_SHIFT                                                                        (0U)
#define DSP_BUS_CONFIG_TC0_DBS_MASK                                                                         (0x00000003U)
#define DSP_BUS_CONFIG_TC0_DBS_BYTE_16                                                                       (0U)
#define DSP_BUS_CONFIG_TC0_DBS_BYTE_32                                                                       (1U)
#define DSP_BUS_CONFIG_TC0_DBS_BYTE_64                                                                       (2U)
#define DSP_BUS_CONFIG_TC0_DBS_BYTE_128                                                                      (3U)

#define DSP_BUS_CONFIG_RESERVED_SHIFT                                                                       (2U)
#define DSP_BUS_CONFIG_RESERVED_MASK                                                                        (0x0000000cU)

#define DSP_BUS_CONFIG_TC1_DBS_SHIFT                                                                        (4U)
#define DSP_BUS_CONFIG_TC1_DBS_MASK                                                                         (0x00000030U)
#define DSP_BUS_CONFIG_TC1_DBS_BYTE_16                                                                       (0U)
#define DSP_BUS_CONFIG_TC1_DBS_BYTE_32                                                                       (1U)
#define DSP_BUS_CONFIG_TC1_DBS_BYTE_64                                                                       (2U)
#define DSP_BUS_CONFIG_TC1_DBS_BYTE_128                                                                      (3U)

#define DSP_BUS_CONFIG_RESERVED_2_SHIFT                                                                     (6U)
#define DSP_BUS_CONFIG_RESERVED_2_MASK                                                                      (0x000000c0U)

#define DSP_BUS_CONFIG_TC0_L2PRES_SHIFT                                                                     (8U)
#define DSP_BUS_CONFIG_TC0_L2PRES_MASK                                                                      (0x00000300U)
#define DSP_BUS_CONFIG_TC0_L2PRES_LOW                                                                        (0U)
#define DSP_BUS_CONFIG_TC0_L2PRES_MED                                                                        (1U)
#define DSP_BUS_CONFIG_TC0_L2PRES_HIGH                                                                       (3U)

#define DSP_BUS_CONFIG_TC1_L2PRES_SHIFT                                                                     (12U)
#define DSP_BUS_CONFIG_TC1_L2PRES_MASK                                                                      (0x00003000U)
#define DSP_BUS_CONFIG_TC1_L2PRES_LOW                                                                        (0U)
#define DSP_BUS_CONFIG_TC1_L2PRES_MED                                                                        (1U)
#define DSP_BUS_CONFIG_TC1_L2PRES_HIGH                                                                       (3U)

#define DSP_BUS_CONFIG_CFG_L2PRES_SHIFT                                                                     (16U)
#define DSP_BUS_CONFIG_CFG_L2PRES_MASK                                                                      (0x00030000U)
#define DSP_BUS_CONFIG_CFG_L2PRES_LOW                                                                        (0U)
#define DSP_BUS_CONFIG_CFG_L2PRES_MED                                                                        (1U)
#define DSP_BUS_CONFIG_CFG_L2PRES_HIGH                                                                       (3U)

#define DSP_BUS_CONFIG_SDMA_L2PRES_SHIFT                                                                    (20U)
#define DSP_BUS_CONFIG_SDMA_L2PRES_MASK                                                                     (0x00300000U)
#define DSP_BUS_CONFIG_SDMA_L2PRES_LOW                                                                       (0U)
#define DSP_BUS_CONFIG_SDMA_L2PRES_MED                                                                       (1U)
#define DSP_BUS_CONFIG_SDMA_L2PRES_HIGH                                                                      (3U)

#define DSP_BUS_CONFIG_NOPOSTOVERRIDE_SHIFT                                                                 (24U)
#define DSP_BUS_CONFIG_NOPOSTOVERRIDE_MASK                                                                  (0x01000000U)
#define DSP_BUS_CONFIG_NOPOSTOVERRIDE_MIX                                                                    (0U)
#define DSP_BUS_CONFIG_NOPOSTOVERRIDE_NOPOST                                                                 (1U)

#define DSP_BUS_CONFIG_SDMA_PRI_SHIFT                                                                       (28U)
#define DSP_BUS_CONFIG_SDMA_PRI_MASK                                                                        (0x70000000U)

#define DSP_BUS_CONFIG_RESERVED_3_SHIFT                                                                     (31U)
#define DSP_BUS_CONFIG_RESERVED_3_MASK                                                                      (0x80000000U)

#define DSP_BUS_CONFIG_RESERVED_4_SHIFT                                                                     (10U)
#define DSP_BUS_CONFIG_RESERVED_4_MASK                                                                      (0x00000c00U)

#define DSP_BUS_CONFIG_RESERVED_5_SHIFT                                                                     (14U)
#define DSP_BUS_CONFIG_RESERVED_5_MASK                                                                      (0x0000c000U)

#define DSP_BUS_CONFIG_RESERVED_6_SHIFT                                                                     (18U)
#define DSP_BUS_CONFIG_RESERVED_6_MASK                                                                      (0x000c0000U)

#define DSP_BUS_CONFIG_RESERVED_7_SHIFT                                                                     (22U)
#define DSP_BUS_CONFIG_RESERVED_7_MASK                                                                      (0x00c00000U)

#define DSP_BUS_CONFIG_RESERVED_8_SHIFT                                                                     (25U)
#define DSP_BUS_CONFIG_RESERVED_8_MASK                                                                      (0x0e000000U)

#define DSP_MMU_CONFIG_MMU0_EN_SHIFT                                                                        (0U)
#define DSP_MMU_CONFIG_MMU0_EN_MASK                                                                         (0x00000001U)
#define DSP_MMU_CONFIG_MMU0_EN_DISABLED                                                                      (0U)
#define DSP_MMU_CONFIG_MMU0_EN_ENABLED                                                                       (1U)

#define DSP_MMU_CONFIG_RESERVED_SHIFT                                                                       (1U)
#define DSP_MMU_CONFIG_RESERVED_MASK                                                                        (0x0000000eU)

#define DSP_MMU_CONFIG_MMU1_EN_SHIFT                                                                        (4U)
#define DSP_MMU_CONFIG_MMU1_EN_MASK                                                                         (0x00000010U)
#define DSP_MMU_CONFIG_MMU1_EN_DISABLED                                                                      (0U)
#define DSP_MMU_CONFIG_MMU1_EN_ENABLED                                                                       (1U)

#define DSP_MMU_CONFIG_RESERVED_2_SHIFT                                                                     (5U)
#define DSP_MMU_CONFIG_RESERVED_2_MASK                                                                      (0x000000e0U)

#define DSP_MMU_CONFIG_MMU0_ABORT_SHIFT                                                                     (8U)
#define DSP_MMU_CONFIG_MMU0_ABORT_MASK                                                                      (0x00000100U)
#define DSP_MMU_CONFIG_MMU0_ABORT_NOABORT                                                                    (0U)
#define DSP_MMU_CONFIG_MMU0_ABORT_ABORT                                                                      (1U)

#define DSP_MMU_CONFIG_RESERVED_3_SHIFT                                                                     (9U)
#define DSP_MMU_CONFIG_RESERVED_3_MASK                                                                      (0x00000e00U)

#define DSP_MMU_CONFIG_MMU1_ABORT_SHIFT                                                                     (12U)
#define DSP_MMU_CONFIG_MMU1_ABORT_MASK                                                                      (0x00001000U)
#define DSP_MMU_CONFIG_MMU1_ABORT_NOABORT                                                                    (0U)
#define DSP_MMU_CONFIG_MMU1_ABORT_ABORT                                                                      (1U)

#define DSP_MMU_CONFIG_RESERVED_4_SHIFT                                                                     (13U)
#define DSP_MMU_CONFIG_RESERVED_4_MASK                                                                      (0xffffe000U)

#define DSP_IRQWAKEEN0_ENABLE_SHIFT                                                                         (0U)
#define DSP_IRQWAKEEN0_ENABLE_MASK                                                                          (0xffffffffU)
#define DSP_IRQWAKEEN0_ENABLE_DISABLE                                                                        (0U)
#define DSP_IRQWAKEEN0_ENABLE_ENABLE                                                                         (1U)

#define DSP_IRQWAKEEN1_ENABLE_SHIFT                                                                         (0U)
#define DSP_IRQWAKEEN1_ENABLE_MASK                                                                          (0xffffffffU)
#define DSP_IRQWAKEEN1_ENABLE_DISABLE                                                                        (0U)
#define DSP_IRQWAKEEN1_ENABLE_ENABLE                                                                         (1U)

#define DSP_DMAWAKEEN0_ENABLE_SHIFT                                                                         (0U)
#define DSP_DMAWAKEEN0_ENABLE_MASK                                                                          (0xffffffffU)
#define DSP_DMAWAKEEN0_ENABLE_DISABLE                                                                        (0U)
#define DSP_DMAWAKEEN0_ENABLE_ENABLE                                                                         (1U)

#define DSP_DMAWAKEEN1_ENABLE_SHIFT                                                                         (0U)
#define DSP_DMAWAKEEN1_ENABLE_MASK                                                                          (0xffffffffU)
#define DSP_DMAWAKEEN1_ENABLE_DISABLE                                                                        (0U)
#define DSP_DMAWAKEEN1_ENABLE_ENABLE                                                                         (1U)

#define DSP_EVTOUT_SET_EVENT_SHIFT                                                                          (0U)
#define DSP_EVTOUT_SET_EVENT_MASK                                                                           (0xffffffffU)
#define DSP_EVTOUT_SET_EVENT_WRITE0                                                                          (0U)
#define DSP_EVTOUT_SET_EVENT_READ0                                                                           (0U)
#define DSP_EVTOUT_SET_EVENT_WRITE1                                                                          (1U)
#define DSP_EVTOUT_SET_EVENT_READ1                                                                           (1U)

#define DSP_EVTOUT_CLR_EVENT_SHIFT                                                                          (0U)
#define DSP_EVTOUT_CLR_EVENT_MASK                                                                           (0xffffffffU)
#define DSP_EVTOUT_CLR_EVENT_WRITE0                                                                          (0U)
#define DSP_EVTOUT_CLR_EVENT_WRITE1                                                                          (1U)
#define DSP_EVTOUT_CLR_EVENT_READ0                                                                           (0U)
#define DSP_EVTOUT_CLR_EVENT_READ1                                                                           (1U)

#define DSP_ERRINT_IRQSTATUS_RAW_EVENT_SHIFT                                                                (0U)
#define DSP_ERRINT_IRQSTATUS_RAW_EVENT_MASK                                                                 (0x007fffffU)
#define DSP_ERRINT_IRQSTATUS_RAW_EVENT_W0                                                                    (0U)
#define DSP_ERRINT_IRQSTATUS_RAW_EVENT_W1                                                                    (1U)
#define DSP_ERRINT_IRQSTATUS_RAW_EVENT_R0                                                                    (0U)
#define DSP_ERRINT_IRQSTATUS_RAW_EVENT_R1                                                                    (1U)

#define DSP_ERRINT_IRQSTATUS_RAW_RESERVED_SHIFT                                                             (23U)
#define DSP_ERRINT_IRQSTATUS_RAW_RESERVED_MASK                                                              (0xff800000U)

#define DSP_ERRINT_IRQSTATUS_EVENT_SHIFT                                                                    (0U)
#define DSP_ERRINT_IRQSTATUS_EVENT_MASK                                                                     (0x007fffffU)
#define DSP_ERRINT_IRQSTATUS_EVENT_W0                                                                        (0U)
#define DSP_ERRINT_IRQSTATUS_EVENT_W1                                                                        (1U)
#define DSP_ERRINT_IRQSTATUS_EVENT_R0                                                                        (0U)
#define DSP_ERRINT_IRQSTATUS_EVENT_R1                                                                        (1U)

#define DSP_ERRINT_IRQSTATUS_RESERVED_SHIFT                                                                 (23U)
#define DSP_ERRINT_IRQSTATUS_RESERVED_MASK                                                                  (0x07800000U)

#define DSP_ERRINT_IRQENABLE_SET_ENABLE_SHIFT                                                               (0U)
#define DSP_ERRINT_IRQENABLE_SET_ENABLE_MASK                                                                (0x007fffffU)
#define DSP_ERRINT_IRQENABLE_SET_ENABLE_W0                                                                   (0U)
#define DSP_ERRINT_IRQENABLE_SET_ENABLE_W1                                                                   (1U)
#define DSP_ERRINT_IRQENABLE_SET_ENABLE_R0                                                                   (0U)
#define DSP_ERRINT_IRQENABLE_SET_ENABLE_R1                                                                   (1U)

#define DSP_ERRINT_IRQENABLE_SET_RESERVED_SHIFT                                                             (23U)
#define DSP_ERRINT_IRQENABLE_SET_RESERVED_MASK                                                              (0x07800000U)

#define DSP_ERRINT_IRQENABLE_CLR_ENABLE_SHIFT                                                               (0U)
#define DSP_ERRINT_IRQENABLE_CLR_ENABLE_MASK                                                                (0x007fffffU)
#define DSP_ERRINT_IRQENABLE_CLR_ENABLE_W0                                                                   (0U)
#define DSP_ERRINT_IRQENABLE_CLR_ENABLE_W1                                                                   (1U)
#define DSP_ERRINT_IRQENABLE_CLR_ENABLE_R0                                                                   (0U)
#define DSP_ERRINT_IRQENABLE_CLR_ENABLE_R1                                                                   (1U)

#define DSP_ERRINT_IRQENABLE_CLR_RESERVED_SHIFT                                                             (23U)
#define DSP_ERRINT_IRQENABLE_CLR_RESERVED_MASK                                                              (0x07800000U)

#define DSP_EDMAWAKE0_IRQSTATUS_RAW_EVENT_SHIFT                                                             (0U)
#define DSP_EDMAWAKE0_IRQSTATUS_RAW_EVENT_MASK                                                              (0xffffffffU)
#define DSP_EDMAWAKE0_IRQSTATUS_RAW_EVENT_W0                                                                 (0U)
#define DSP_EDMAWAKE0_IRQSTATUS_RAW_EVENT_W1                                                                 (1U)
#define DSP_EDMAWAKE0_IRQSTATUS_RAW_EVENT_R0                                                                 (0U)
#define DSP_EDMAWAKE0_IRQSTATUS_RAW_EVENT_R1                                                                 (1U)

#define DSP_EDMAWAKE0_IRQSTATUS_EVENT_SHIFT                                                                 (0U)
#define DSP_EDMAWAKE0_IRQSTATUS_EVENT_MASK                                                                  (0xffffffffU)
#define DSP_EDMAWAKE0_IRQSTATUS_EVENT_W0                                                                     (0U)
#define DSP_EDMAWAKE0_IRQSTATUS_EVENT_W1                                                                     (1U)
#define DSP_EDMAWAKE0_IRQSTATUS_EVENT_R0                                                                     (0U)
#define DSP_EDMAWAKE0_IRQSTATUS_EVENT_R1                                                                     (1U)

#define DSP_EDMAWAKE0_IRQENABLE_SET_ENABLE_SHIFT                                                            (0U)
#define DSP_EDMAWAKE0_IRQENABLE_SET_ENABLE_MASK                                                             (0xffffffffU)
#define DSP_EDMAWAKE0_IRQENABLE_SET_ENABLE_W0                                                                (0U)
#define DSP_EDMAWAKE0_IRQENABLE_SET_ENABLE_W1                                                                (1U)
#define DSP_EDMAWAKE0_IRQENABLE_SET_ENABLE_R0                                                                (0U)
#define DSP_EDMAWAKE0_IRQENABLE_SET_ENABLE_R1                                                                (1U)

#define DSP_EDMAWAKE0_IRQENABLE_CLR_ENABLE_SHIFT                                                            (0U)
#define DSP_EDMAWAKE0_IRQENABLE_CLR_ENABLE_MASK                                                             (0xffffffffU)
#define DSP_EDMAWAKE0_IRQENABLE_CLR_ENABLE_W0                                                                (0U)
#define DSP_EDMAWAKE0_IRQENABLE_CLR_ENABLE_W1                                                                (1U)
#define DSP_EDMAWAKE0_IRQENABLE_CLR_ENABLE_R0                                                                (0U)
#define DSP_EDMAWAKE0_IRQENABLE_CLR_ENABLE_R1                                                                (1U)

#define DSP_EDMAWAKE1_IRQSTATUS_RAW_EVENT_SHIFT                                                             (0U)
#define DSP_EDMAWAKE1_IRQSTATUS_RAW_EVENT_MASK                                                              (0xffffffffU)
#define DSP_EDMAWAKE1_IRQSTATUS_RAW_EVENT_W0                                                                 (0U)
#define DSP_EDMAWAKE1_IRQSTATUS_RAW_EVENT_W1                                                                 (1U)
#define DSP_EDMAWAKE1_IRQSTATUS_RAW_EVENT_R0                                                                 (0U)
#define DSP_EDMAWAKE1_IRQSTATUS_RAW_EVENT_R1                                                                 (1U)

#define DSP_EDMAWAKE1_IRQSTATUS_EVENT_SHIFT                                                                 (0U)
#define DSP_EDMAWAKE1_IRQSTATUS_EVENT_MASK                                                                  (0xffffffffU)
#define DSP_EDMAWAKE1_IRQSTATUS_EVENT_W0                                                                     (0U)
#define DSP_EDMAWAKE1_IRQSTATUS_EVENT_W1                                                                     (1U)
#define DSP_EDMAWAKE1_IRQSTATUS_EVENT_R0                                                                     (0U)
#define DSP_EDMAWAKE1_IRQSTATUS_EVENT_R1                                                                     (1U)

#define DSP_EDMAWAKE1_IRQENABLE_SET_ENABLE_SHIFT                                                            (0U)
#define DSP_EDMAWAKE1_IRQENABLE_SET_ENABLE_MASK                                                             (0xffffffffU)
#define DSP_EDMAWAKE1_IRQENABLE_SET_ENABLE_W0                                                                (0U)
#define DSP_EDMAWAKE1_IRQENABLE_SET_ENABLE_W1                                                                (1U)
#define DSP_EDMAWAKE1_IRQENABLE_SET_ENABLE_R0                                                                (0U)
#define DSP_EDMAWAKE1_IRQENABLE_SET_ENABLE_R1                                                                (1U)

#define DSP_EDMAWAKE1_IRQENABLE_CLR_ENABLE_SHIFT                                                            (0U)
#define DSP_EDMAWAKE1_IRQENABLE_CLR_ENABLE_MASK                                                             (0xffffffffU)
#define DSP_EDMAWAKE1_IRQENABLE_CLR_ENABLE_W0                                                                (0U)
#define DSP_EDMAWAKE1_IRQENABLE_CLR_ENABLE_W1                                                                (1U)
#define DSP_EDMAWAKE1_IRQENABLE_CLR_ENABLE_R0                                                                (0U)
#define DSP_EDMAWAKE1_IRQENABLE_CLR_ENABLE_R1                                                                (1U)

#define DSP_HW_DBGOUT_SEL_GROUP_SHIFT                                                                       (0U)
#define DSP_HW_DBGOUT_SEL_GROUP_MASK                                                                        (0x0000000fU)
#define DSP_HW_DBGOUT_SEL_GROUP_DISABLED                                                                     (0U)
#define DSP_HW_DBGOUT_SEL_GROUP_G1                                                                           (1U)
#define DSP_HW_DBGOUT_SEL_GROUP_G2                                                                           (2U)
#define DSP_HW_DBGOUT_SEL_GROUP_GN                                                                           (2U)

#define DSP_HW_DBGOUT_VAL_VALUE_SHIFT                                                                       (0U)
#define DSP_HW_DBGOUT_VAL_VALUE_MASK                                                                        (0xffffffffU)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_DSP_SYSTEM_H_ */
