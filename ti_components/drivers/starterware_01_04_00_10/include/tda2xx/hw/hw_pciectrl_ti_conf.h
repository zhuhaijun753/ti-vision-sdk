/*
* hw_pciectrl_ti_conf.h
*
* Register-level header file for PCIECTRL_TI_CONF [default]
*
* Copyright (c) 2013 Texas Instruments Incorporated.
*
* Except for those rights granted to you in your license from TI,
* all rights reserved.
*
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
* NO WARRANTIES APPLY TO THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR
* STATUTORY.  EXAMPLES OF EXCLUDED WARRANTIES ARE IMPLIED WARRANTIES OF
* MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE AND WARRANTIES
* OF NON-INFRINGEMENT, BUT ALL OTHER WARRANTY EXCLUSIONS ALSO APPLY.
* FURTHERMORE, TI SHALL NOT, UNDER ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL,
* INCIDENTAL, CONSEQUENTIAL OR PUNITIVE DAMAGES, FOR ANY REASON WHATSOEVER.
*/

#ifndef HW_PCIECTRL_TI_CONF_H_
#define HW_PCIECTRL_TI_CONF_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Component offset
****************************************************************************************************/
#define PCIECTRL_TI_CONF_OFFSET 									(0x2000U)


/****************************************************************************************************
* Register Definitions 
****************************************************************************************************/

#define PCIECTRL_TI_CONF_REVISION                                   (0x0U)
#define PCIECTRL_TI_CONF_SYSCONFIG                                  (0x10U)
#define PCIECTRL_TI_CONF_IRQ_EOI                                    (0x18U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN                         (0x20U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN                             (0x24U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN                         (0x28U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN                         (0x2cU)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MSI                          (0x30U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MSI                              (0x34U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MSI                          (0x38U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MSI                          (0x3cU)
#define PCIECTRL_TI_CONF_DEVICE_TYPE                                (0x100U)
#define PCIECTRL_TI_CONF_DEVICE_CMD                                 (0x104U)
#define PCIECTRL_TI_CONF_PM_CTRL                                    (0x108U)
#define PCIECTRL_TI_CONF_PHY_CS                                     (0x10cU)
#define PCIECTRL_TI_CONF_INTX_ASSERT                                (0x124U)
#define PCIECTRL_TI_CONF_INTX_DEASSERT                              (0x128U)
#define PCIECTRL_TI_CONF_MSI_XMT                                    (0x12cU)
#define PCIECTRL_TI_CONF_DEBUG_CFG                                  (0x140U)
#define PCIECTRL_TI_CONF_DEBUG_DATA                                 (0x144U)
#define PCIECTRL_TI_CONF_DIAG_CTRL                                  (0x148U)

/****************************************************************************************************
* Field Definition Macros 
****************************************************************************************************/

#define PCIECTRL_TI_CONF_REVISION_Y_MINOR_SHIFT                                         (0U)
#define PCIECTRL_TI_CONF_REVISION_Y_MINOR_MASK                                          (0x0000003fU)

#define PCIECTRL_TI_CONF_REVISION_CUSTOM_SHIFT                                          (6U)
#define PCIECTRL_TI_CONF_REVISION_CUSTOM_MASK                                           (0x000000c0U)
#define PCIECTRL_TI_CONF_REVISION_CUSTOM_STANDARD                                        (0U)

#define PCIECTRL_TI_CONF_REVISION_X_MAJOR_SHIFT                                         (8U)
#define PCIECTRL_TI_CONF_REVISION_X_MAJOR_MASK                                          (0x00000700U)
#define PCIECTRL_TI_CONF_REVISION_X_MAJOR_C1                                             (2U)

#define PCIECTRL_TI_CONF_REVISION_R_RTL_SHIFT                                           (11U)
#define PCIECTRL_TI_CONF_REVISION_R_RTL_MASK                                            (0x0000f800U)

#define PCIECTRL_TI_CONF_REVISION_FUNC_SHIFT                                            (16U)
#define PCIECTRL_TI_CONF_REVISION_FUNC_MASK                                             (0x0fff0000U)

#define PCIECTRL_TI_CONF_REVISION_SCHEME_SHIFT                                          (30U)
#define PCIECTRL_TI_CONF_REVISION_SCHEME_MASK                                           (0xc0000000U)
#define PCIECTRL_TI_CONF_REVISION_SCHEME_H08                                             (1U)
#define PCIECTRL_TI_CONF_REVISION_SCHEME_LEGACY                                          (0U)

#define PCIECTRL_TI_CONF_REVISION_BU_SHIFT                                              (28U)
#define PCIECTRL_TI_CONF_REVISION_BU_MASK                                               (0x30000000U)
#define PCIECTRL_TI_CONF_REVISION_BU_WBU                                                 (1U)
#define PCIECTRL_TI_CONF_REVISION_BU_DSPS                                                (0U)

#define PCIECTRL_TI_CONF_SYSCONFIG_IDLEMODE_SHIFT                                       (2U)
#define PCIECTRL_TI_CONF_SYSCONFIG_IDLEMODE_MASK                                        (0x0000000cU)
#define PCIECTRL_TI_CONF_SYSCONFIG_IDLEMODE_FORCE                                        (0U)
#define PCIECTRL_TI_CONF_SYSCONFIG_IDLEMODE_NO                                           (1U)
#define PCIECTRL_TI_CONF_SYSCONFIG_IDLEMODE_SMART                                        (2U)
#define PCIECTRL_TI_CONF_SYSCONFIG_IDLEMODE_SMART_WAKEUP                                 (3U)

#define PCIECTRL_TI_CONF_SYSCONFIG_STANDBYMODE_SHIFT                                    (4U)
#define PCIECTRL_TI_CONF_SYSCONFIG_STANDBYMODE_MASK                                     (0x00000030U)
#define PCIECTRL_TI_CONF_SYSCONFIG_STANDBYMODE_FORCE                                     (0U)
#define PCIECTRL_TI_CONF_SYSCONFIG_STANDBYMODE_NO                                        (1U)
#define PCIECTRL_TI_CONF_SYSCONFIG_STANDBYMODE_SMART                                     (2U)
#define PCIECTRL_TI_CONF_SYSCONFIG_STANDBYMODE_SMART_WAKEUP                              (3U)

#define PCIECTRL_TI_CONF_SYSCONFIG_MCOHERENT_EN_SHIFT                                   (16U)
#define PCIECTRL_TI_CONF_SYSCONFIG_MCOHERENT_EN_MASK                                    (0x00010000U)
#define PCIECTRL_TI_CONF_SYSCONFIG_MCOHERENT_EN_DIS                                      (0U)
#define PCIECTRL_TI_CONF_SYSCONFIG_MCOHERENT_EN                                          (1U)

#define PCIECTRL_TI_CONF_IRQ_EOI_LINE_NUMBER_SHIFT                                      (0U)
#define PCIECTRL_TI_CONF_IRQ_EOI_LINE_NUMBER_MASK                                       (0x0000000fU)
#define PCIECTRL_TI_CONF_IRQ_EOI_LINE_NUMBER_READ0                                       (0U)
#define PCIECTRL_TI_CONF_IRQ_EOI_LINE_NUMBER_MAIN                                        (0U)
#define PCIECTRL_TI_CONF_IRQ_EOI_LINE_NUMBER_MSI                                         (1U)

#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_SYS_SHIFT                               (0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_SYS_MASK                                (0x00000001U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_SYS_NONE                                 (0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_SYS_PENDING                              (1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_SYS_NOACTION                             (0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_SYS_SET                                  (1U)

#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_FATAL_SHIFT                             (1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_FATAL_MASK                              (0x00000002U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_FATAL_NONE                               (0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_FATAL_PENDING                            (1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_FATAL_NOACTION                           (0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_FATAL_SET                                (1U)

#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_NONFATAL_SHIFT                          (2U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_NONFATAL_MASK                           (0x00000004U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_NONFATAL_NONE                            (0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_NONFATAL_PENDING                         (1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_NONFATAL_NOACTION                        (0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_NONFATAL_SET                             (1U)

#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_COR_SHIFT                               (3U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_COR_MASK                                (0x00000008U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_COR_NONE                                 (0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_COR_PENDING                              (1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_COR_NOACTION                             (0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_COR_SET                                  (1U)

#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_AXI_SHIFT                               (4U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_AXI_MASK                                (0x00000010U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_AXI_NONE                                 (0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_AXI_PENDING                              (1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_AXI_NOACTION                             (0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_AXI_SET                                  (1U)

#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_ECRC_SHIFT                              (5U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_ECRC_MASK                               (0x00000020U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_ECRC_NONE                                (0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_ECRC_PENDING                             (1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_ECRC_NOACTION                            (0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_ERR_ECRC_SET                                 (1U)

#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_PME_TURN_OFF_SHIFT                          (8U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_PME_TURN_OFF_MASK                           (0x00000100U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_PME_TURN_OFF_NONE                            (0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_PME_TURN_OFF_PENDING                         (1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_PME_TURN_OFF_NOACTION                        (0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_PME_TURN_OFF_SET                             (1U)

#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_PME_TO_ACK_SHIFT                            (9U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_PME_TO_ACK_MASK                             (0x00000200U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_PME_TO_ACK_NONE                              (0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_PME_TO_ACK_PENDING                           (1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_PME_TO_ACK_NOACTION                          (0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_PME_TO_ACK_SET                               (1U)

#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_PM_PME_SHIFT                                (10U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_PM_PME_MASK                                 (0x00000400U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_PM_PME_NONE                                  (0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_PM_PME_PENDING                               (1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_PM_PME_NOACTION                              (0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_PM_PME_SET                                   (1U)

#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_LINK_REQ_RST_SHIFT                          (11U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_LINK_REQ_RST_MASK                           (0x00000800U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_LINK_REQ_RST_NONE                            (0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_LINK_REQ_RST_PENDING                         (1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_LINK_REQ_RST_NOACTION                        (0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_LINK_REQ_RST_SET                             (1U)

#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_LINK_UP_EVT_SHIFT                           (12U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_LINK_UP_EVT_MASK                            (0x00001000U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_LINK_UP_EVT_NONE                             (0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_LINK_UP_EVT_PENDING                          (1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_LINK_UP_EVT_NOACTION                         (0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_LINK_UP_EVT_SET                              (1U)

#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_CFG_BME_EVT_SHIFT                           (13U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_CFG_BME_EVT_MASK                            (0x00002000U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_CFG_BME_EVT_NONE                             (0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_CFG_BME_EVT_PENDING                          (1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_CFG_BME_EVT_NOACTION                         (0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_CFG_BME_EVT_SET                              (1U)

#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_CFG_MSE_EVT_SHIFT                           (14U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_CFG_MSE_EVT_MASK                            (0x00004000U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_CFG_MSE_EVT_NONE                             (0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_CFG_MSE_EVT_PENDING                          (1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_CFG_MSE_EVT_NOACTION                         (0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MAIN_CFG_MSE_EVT_SET                              (1U)

#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_ERR_SYS_SHIFT                                   (0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_ERR_SYS_MASK                                    (0x00000001U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_ERR_SYS_NONE                                     (0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_ERR_SYS_PENDING                                  (1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_ERR_SYS_NOACTION                                 (0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_ERR_SYS_CLEAR                                    (1U)

#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_ERR_FATAL_SHIFT                                 (1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_ERR_FATAL_MASK                                  (0x00000002U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_ERR_FATAL_NONE                                   (0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_ERR_FATAL_PENDING                                (1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_ERR_FATAL_NOACTION                               (0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_ERR_FATAL_CLEAR                                  (1U)

#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_ERR_NONFATAL_SHIFT                              (2U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_ERR_NONFATAL_MASK                               (0x00000004U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_ERR_NONFATAL_NONE                                (0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_ERR_NONFATAL_PENDING                             (1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_ERR_NONFATAL_NOACTION                            (0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_ERR_NONFATAL_CLEAR                               (1U)

#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_ERR_COR_SHIFT                                   (3U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_ERR_COR_MASK                                    (0x00000008U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_ERR_COR_NONE                                     (0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_ERR_COR_PENDING                                  (1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_ERR_COR_NOACTION                                 (0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_ERR_COR_CLEAR                                    (1U)

#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_ERR_AXI_SHIFT                                   (4U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_ERR_AXI_MASK                                    (0x00000010U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_ERR_AXI_NONE                                     (0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_ERR_AXI_PENDING                                  (1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_ERR_AXI_NOACTION                                 (0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_ERR_AXI_CLEAR                                    (1U)

#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_ERR_ECRC_SHIFT                                  (5U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_ERR_ECRC_MASK                                   (0x00000020U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_ERR_ECRC_NONE                                    (0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_ERR_ECRC_PENDING                                 (1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_ERR_ECRC_NOACTION                                (0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_ERR_ECRC_CLEAR                                   (1U)

#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_PME_TURN_OFF_SHIFT                              (8U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_PME_TURN_OFF_MASK                               (0x00000100U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_PME_TURN_OFF_NONE                                (0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_PME_TURN_OFF_PENDING                             (1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_PME_TURN_OFF_NOACTION                            (0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_PME_TURN_OFF_CLEAR                               (1U)

#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_PME_TO_ACK_SHIFT                                (9U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_PME_TO_ACK_MASK                                 (0x00000200U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_PME_TO_ACK_NONE                                  (0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_PME_TO_ACK_PENDING                               (1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_PME_TO_ACK_NOACTION                              (0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_PME_TO_ACK_CLEAR                                 (1U)

#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_PM_PME_SHIFT                                    (10U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_PM_PME_MASK                                     (0x00000400U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_PM_PME_NONE                                      (0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_PM_PME_PENDING                                   (1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_PM_PME_NOACTION                                  (0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_PM_PME_CLEAR                                     (1U)

#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_LINK_REQ_RST_SHIFT                              (11U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_LINK_REQ_RST_MASK                               (0x00000800U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_LINK_REQ_RST_NONE                                (0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_LINK_REQ_RST_PENDING                             (1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_LINK_REQ_RST_NOACTION                            (0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_LINK_REQ_RST_CLEAR                               (1U)

#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_LINK_UP_EVT_SHIFT                               (12U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_LINK_UP_EVT_MASK                                (0x00001000U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_LINK_UP_EVT_NONE                                 (0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_LINK_UP_EVT_PENDING                              (1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_LINK_UP_EVT_NOACTION                             (0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_LINK_UP_EVT_CLEAR                                (1U)

#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_CFG_BME_EVT_SHIFT                               (13U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_CFG_BME_EVT_MASK                                (0x00002000U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_CFG_BME_EVT_NONE                                 (0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_CFG_BME_EVT_PENDING                              (1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_CFG_BME_EVT_NOACTION                             (0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_CFG_BME_EVT_CLEAR                                (1U)

#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_CFG_MSE_EVT_SHIFT                               (14U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_CFG_MSE_EVT_MASK                                (0x00004000U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_CFG_MSE_EVT_NONE                                 (0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_CFG_MSE_EVT_PENDING                              (1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_CFG_MSE_EVT_NOACTION                             (0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MAIN_CFG_MSE_EVT_CLEAR                                (1U)

#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_ERR_SYS_EN_SHIFT                            (0U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_ERR_SYS_EN_MASK                             (0x00000001U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_ERR_SYS_EN_DISABLED                          (0U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_ERR_SYS_EN_ENABLED                           (1U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_ERR_SYS_EN_NOACTION                          (0U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_ERR_SYS_EN                                   (1U)

#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_ERR_FATAL_EN_SHIFT                          (1U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_ERR_FATAL_EN_MASK                           (0x00000002U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_ERR_FATAL_EN_DISABLED                        (0U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_ERR_FATAL_EN_ENABLED                         (1U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_ERR_FATAL_EN_NOACTION                        (0U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_ERR_FATAL_EN                                 (1U)

#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_ERR_NONFATAL_EN_SHIFT                       (2U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_ERR_NONFATAL_EN_MASK                        (0x00000004U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_ERR_NONFATAL_EN_DISABLED                     (0U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_ERR_NONFATAL_EN_ENABLED                      (1U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_ERR_NONFATAL_EN_NOACTION                     (0U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_ERR_NONFATAL_EN                              (1U)

#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_ERR_COR_EN_SHIFT                            (3U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_ERR_COR_EN_MASK                             (0x00000008U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_ERR_COR_EN_DISABLED                          (0U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_ERR_COR_EN_ENABLED                           (1U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_ERR_COR_EN_NOACTION                          (0U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_ERR_COR_EN                                   (1U)

#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_ERR_AXI_EN_SHIFT                            (4U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_ERR_AXI_EN_MASK                             (0x00000010U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_ERR_AXI_EN_DISABLED                          (0U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_ERR_AXI_EN_ENABLED                           (1U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_ERR_AXI_EN_NOACTION                          (0U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_ERR_AXI_EN                                   (1U)

#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_ERR_ECRC_EN_SHIFT                           (5U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_ERR_ECRC_EN_MASK                            (0x00000020U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_ERR_ECRC_EN_DISABLED                         (0U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_ERR_ECRC_EN_ENABLED                          (1U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_ERR_ECRC_EN_NOACTION                         (0U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_ERR_ECRC_EN                                  (1U)

#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_PME_TURN_OFF_EN_SHIFT                       (8U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_PME_TURN_OFF_EN_MASK                        (0x00000100U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_PME_TURN_OFF_EN_DISABLED                     (0U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_PME_TURN_OFF_EN_ENABLED                      (1U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_PME_TURN_OFF_EN_NOACTION                     (0U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_PME_TURN_OFF_EN                              (1U)

#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_PME_TO_ACK_EN_SHIFT                         (9U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_PME_TO_ACK_EN_MASK                          (0x00000200U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_PME_TO_ACK_EN_DISABLED                       (0U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_PME_TO_ACK_EN_ENABLED                        (1U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_PME_TO_ACK_EN_NOACTION                       (0U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_PME_TO_ACK_EN                                (1U)

#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_PM_PME_EN_SHIFT                             (10U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_PM_PME_EN_MASK                              (0x00000400U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_PM_PME_EN_DISABLED                           (0U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_PM_PME_EN_ENABLED                            (1U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_PM_PME_EN_NOACTION                           (0U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_PM_PME_EN                                    (1U)

#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_LINK_REQ_RST_EN_SHIFT                       (11U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_LINK_REQ_RST_EN_MASK                        (0x00000800U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_LINK_REQ_RST_EN_DISABLED                     (0U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_LINK_REQ_RST_EN_ENABLED                      (1U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_LINK_REQ_RST_EN_NOACTION                     (0U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_LINK_REQ_RST_EN                              (1U)

#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_LINK_UP_EVT_EN_SHIFT                        (12U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_LINK_UP_EVT_EN_MASK                         (0x00001000U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_LINK_UP_EVT_EN_DISABLED                      (0U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_LINK_UP_EVT_EN_ENABLED                       (1U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_LINK_UP_EVT_EN_NOACTION                      (0U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_LINK_UP_EVT_EN                               (1U)

#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_CFG_BME_EVT_EN_SHIFT                        (13U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_CFG_BME_EVT_EN_MASK                         (0x00002000U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_CFG_BME_EVT_EN_DISABLED                      (0U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_CFG_BME_EVT_EN_ENABLED                       (1U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_CFG_BME_EVT_EN_NOACTION                      (0U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_CFG_BME_EVT_EN                               (1U)

#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_CFG_MSE_EVT_EN_SHIFT                        (14U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_CFG_MSE_EVT_EN_MASK                         (0x00004000U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_CFG_MSE_EVT_EN_DISABLED                      (0U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_CFG_MSE_EVT_EN_ENABLED                       (1U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_CFG_MSE_EVT_EN_NOACTION                      (0U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MAIN_CFG_MSE_EVT_EN                               (1U)

#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_ERR_SYS_EN_SHIFT                            (0U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_ERR_SYS_EN_MASK                             (0x00000001U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_ERR_SYS_EN_DISABLED                          (0U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_ERR_SYS_EN_ENABLED                           (1U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_ERR_SYS_EN_NOACTION                          (0U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_ERR_SYS_EN_CLEAR                             (1U)

#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_ERR_FATAL_EN_SHIFT                          (1U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_ERR_FATAL_EN_MASK                           (0x00000002U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_ERR_FATAL_EN_DISABLED                        (0U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_ERR_FATAL_EN_ENABLED                         (1U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_ERR_FATAL_EN_NOACTION                        (0U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_ERR_FATAL_EN_CLEAR                           (1U)

#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_ERR_NONFATAL_EN_SHIFT                       (2U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_ERR_NONFATAL_EN_MASK                        (0x00000004U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_ERR_NONFATAL_EN_DISABLED                     (0U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_ERR_NONFATAL_EN_ENABLED                      (1U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_ERR_NONFATAL_EN_NOACTION                     (0U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_ERR_NONFATAL_EN_CLEAR                        (1U)

#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_ERR_COR_EN_SHIFT                            (3U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_ERR_COR_EN_MASK                             (0x00000008U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_ERR_COR_EN_DISABLED                          (0U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_ERR_COR_EN_ENABLED                           (1U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_ERR_COR_EN_NOACTION                          (0U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_ERR_COR_EN_CLEAR                             (1U)

#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_ERR_AXI_EN_SHIFT                            (4U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_ERR_AXI_EN_MASK                             (0x00000010U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_ERR_AXI_EN_DISABLED                          (0U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_ERR_AXI_EN_ENABLED                           (1U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_ERR_AXI_EN_NOACTION                          (0U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_ERR_AXI_EN_CLEAR                             (1U)

#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_ERR_ECRC_EN_SHIFT                           (5U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_ERR_ECRC_EN_MASK                            (0x00000020U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_ERR_ECRC_EN_DISABLED                         (0U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_ERR_ECRC_EN_ENABLED                          (1U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_ERR_ECRC_EN_NOACTION                         (0U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_ERR_ECRC_EN_CLEAR                            (1U)

#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_PME_TURN_OFF_EN_SHIFT                       (8U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_PME_TURN_OFF_EN_MASK                        (0x00000100U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_PME_TURN_OFF_EN_DISABLED                     (0U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_PME_TURN_OFF_EN_ENABLED                      (1U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_PME_TURN_OFF_EN_NOACTION                     (0U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_PME_TURN_OFF_EN_CLEAR                        (1U)

#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_PME_TO_ACK_EN_SHIFT                         (9U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_PME_TO_ACK_EN_MASK                          (0x00000200U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_PME_TO_ACK_EN_DISABLED                       (0U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_PME_TO_ACK_EN_ENABLED                        (1U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_PME_TO_ACK_EN_NOACTION                       (0U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_PME_TO_ACK_EN_CLEAR                          (1U)

#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_PM_PME_EN_SHIFT                             (10U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_PM_PME_EN_MASK                              (0x00000400U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_PM_PME_EN_DISABLED                           (0U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_PM_PME_EN_ENABLED                            (1U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_PM_PME_EN_NOACTION                           (0U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_PM_PME_EN_CLEAR                              (1U)

#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_LINK_REQ_RST_EN_SHIFT                       (11U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_LINK_REQ_RST_EN_MASK                        (0x00000800U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_LINK_REQ_RST_EN_DISABLED                     (0U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_LINK_REQ_RST_EN_ENABLED                      (1U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_LINK_REQ_RST_EN_NOACTION                     (0U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_LINK_REQ_RST_EN_CLEAR                        (1U)

#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_LINK_UP_EVT_EN_SHIFT                        (12U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_LINK_UP_EVT_EN_MASK                         (0x00001000U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_LINK_UP_EVT_EN_DISABLED                      (0U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_LINK_UP_EVT_EN_ENABLED                       (1U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_LINK_UP_EVT_EN_NOACTION                      (0U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_LINK_UP_EVT_EN_CLEAR                         (1U)

#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_CFG_BME_EVT_EN_SHIFT                        (13U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_CFG_BME_EVT_EN_MASK                         (0x00002000U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_CFG_BME_EVT_EN_DISABLED                      (0U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_CFG_BME_EVT_EN_ENABLED                       (1U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_CFG_BME_EVT_EN_NOACTION                      (0U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_CFG_BME_EVT_EN_CLEAR                         (1U)

#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_CFG_MSE_EVT_EN_SHIFT                        (14U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_CFG_MSE_EVT_EN_MASK                         (0x00004000U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_CFG_MSE_EVT_EN_DISABLED                      (0U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_CFG_MSE_EVT_EN_ENABLED                       (1U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_CFG_MSE_EVT_EN_NOACTION                      (0U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MAIN_CFG_MSE_EVT_EN_CLEAR                         (1U)

#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MSI_INTA_SHIFT                                   (0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MSI_INTA_MASK                                    (0x00000001U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MSI_INTA_NONE                                     (0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MSI_INTA_PENDING                                  (1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MSI_INTA_NOACTION                                 (0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MSI_INTA_SET                                      (1U)

#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MSI_INTB_SHIFT                                   (1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MSI_INTB_MASK                                    (0x00000002U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MSI_INTB_NONE                                     (0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MSI_INTB_PENDING                                  (1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MSI_INTB_NOACTION                                 (0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MSI_INTB_SET                                      (1U)

#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MSI_INTC_SHIFT                                   (2U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MSI_INTC_MASK                                    (0x00000004U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MSI_INTC_NONE                                     (0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MSI_INTC_PENDING                                  (1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MSI_INTC_NOACTION                                 (0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MSI_INTC_SET                                      (1U)

#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MSI_INTD_SHIFT                                   (3U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MSI_INTD_MASK                                    (0x00000008U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MSI_INTD_NONE                                     (0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MSI_INTD_PENDING                                  (1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MSI_INTD_NOACTION                                 (0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MSI_INTD_SET                                      (1U)

#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MSI_SHIFT                                        (4U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MSI_MASK                                         (0x00000010U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MSI_NONE                                          (0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MSI_PENDING                                       (1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MSI_NOACTION                                      (0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_RAW_MSI_SET                                           (1U)

#define PCIECTRL_TI_CONF_IRQSTATUS_MSI_INTA_SHIFT                                       (0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MSI_INTA_MASK                                        (0x00000001U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MSI_INTA_NONE                                         (0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MSI_INTA_PENDING                                      (1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MSI_INTA_NOACTION                                     (0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MSI_INTA_CLEAR                                        (1U)

#define PCIECTRL_TI_CONF_IRQSTATUS_MSI_INTB_SHIFT                                       (1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MSI_INTB_MASK                                        (0x00000002U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MSI_INTB_NONE                                         (0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MSI_INTB_PENDING                                      (1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MSI_INTB_NOACTION                                     (0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MSI_INTB_CLEAR                                        (1U)

#define PCIECTRL_TI_CONF_IRQSTATUS_MSI_INTC_SHIFT                                       (2U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MSI_INTC_MASK                                        (0x00000004U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MSI_INTC_NONE                                         (0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MSI_INTC_PENDING                                      (1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MSI_INTC_NOACTION                                     (0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MSI_INTC_CLEAR                                        (1U)

#define PCIECTRL_TI_CONF_IRQSTATUS_MSI_INTD_SHIFT                                       (3U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MSI_INTD_MASK                                        (0x00000008U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MSI_INTD_NONE                                         (0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MSI_INTD_PENDING                                      (1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MSI_INTD_NOACTION                                     (0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MSI_INTD_CLEAR                                        (1U)

#define PCIECTRL_TI_CONF_IRQSTATUS_MSI_SHIFT                                            (4U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MSI_MASK                                             (0x00000010U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MSI_NONE                                              (0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MSI_PENDING                                           (1U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MSI_NOACTION                                          (0U)
#define PCIECTRL_TI_CONF_IRQSTATUS_MSI_CLEAR                                             (1U)

#define PCIECTRL_TI_CONF_IRQENABLE_SET_MSI_INTA_EN_SHIFT                                (0U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MSI_INTA_EN_MASK                                 (0x00000001U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MSI_INTA_EN_DISABLED                              (0U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MSI_INTA_EN_ENABLED                               (1U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MSI_INTA_EN_NOACTION                              (0U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MSI_INTA_EN                                       (1U)

#define PCIECTRL_TI_CONF_IRQENABLE_SET_MSI_INTB_EN_SHIFT                                (1U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MSI_INTB_EN_MASK                                 (0x00000002U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MSI_INTB_EN_DISABLED                              (0U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MSI_INTB_EN_ENABLED                               (1U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MSI_INTB_EN_NOACTION                              (0U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MSI_INTB_EN                                       (1U)

#define PCIECTRL_TI_CONF_IRQENABLE_SET_MSI_INTC_EN_SHIFT                                (2U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MSI_INTC_EN_MASK                                 (0x00000004U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MSI_INTC_EN_DISABLED                              (0U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MSI_INTC_EN_ENABLED                               (1U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MSI_INTC_EN_NOACTION                              (0U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MSI_INTC_EN                                       (1U)

#define PCIECTRL_TI_CONF_IRQENABLE_SET_MSI_INTD_EN_SHIFT                                (3U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MSI_INTD_EN_MASK                                 (0x00000008U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MSI_INTD_EN_DISABLED                              (0U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MSI_INTD_EN_ENABLED                               (1U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MSI_INTD_EN_NOACTION                              (0U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MSI_INTD_EN                                       (1U)

#define PCIECTRL_TI_CONF_IRQENABLE_SET_MSI_EN_SHIFT                                     (4U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MSI_EN_MASK                                      (0x00000010U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MSI_EN_NONE                                       (0U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MSI_EN_PENDING                                    (1U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MSI_EN_NOACTION                                   (0U)
#define PCIECTRL_TI_CONF_IRQENABLE_SET_MSI_EN_CLEAR                                      (1U)

#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MSI_INTA_EN_SHIFT                                (0U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MSI_INTA_EN_MASK                                 (0x00000001U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MSI_INTA_EN_DISABLED                              (0U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MSI_INTA_EN_ENABLED                               (1U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MSI_INTA_EN_NOACTION                              (0U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MSI_INTA_EN_CLEAR                                 (1U)

#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MSI_INTB_EN_SHIFT                                (1U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MSI_INTB_EN_MASK                                 (0x00000002U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MSI_INTB_EN_DISABLED                              (0U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MSI_INTB_EN_ENABLED                               (1U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MSI_INTB_EN_NOACTION                              (0U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MSI_INTB_EN_CLEAR                                 (1U)

#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MSI_INTC_EN_SHIFT                                (2U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MSI_INTC_EN_MASK                                 (0x00000004U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MSI_INTC_EN_DISABLED                              (0U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MSI_INTC_EN_ENABLED                               (1U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MSI_INTC_EN_NOACTION                              (0U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MSI_INTC_EN_CLEAR                                 (1U)

#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MSI_INTD_EN_SHIFT                                (3U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MSI_INTD_EN_MASK                                 (0x00000008U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MSI_INTD_EN_DISABLED                              (0U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MSI_INTD_EN_ENABLED                               (1U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MSI_INTD_EN_NOACTION                              (0U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MSI_INTD_EN_CLEAR                                 (1U)

#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MSI_EN_SHIFT                                     (4U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MSI_EN_MASK                                      (0x00000010U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MSI_EN_DISABLED                                   (0U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MSI_EN_ENABLED                                    (1U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MSI_EN_NOACTION                                   (0U)
#define PCIECTRL_TI_CONF_IRQENABLE_CLR_MSI_EN_CLEAR                                      (1U)

#define PCIECTRL_TI_CONF_DEVICE_TYPE_SHIFT                                              (0U)
#define PCIECTRL_TI_CONF_DEVICE_TYPE_MASK                                               (0x0000000fU)
#define PCIECTRL_TI_CONF_DEVICE_TYPE_EP                                                  (0U)
#define PCIECTRL_TI_CONF_DEVICE_TYPE_LEG_EP                                              (1U)
#define PCIECTRL_TI_CONF_DEVICE_TYPE_RC                                                  (4U)

#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE_SHIFT                                   (2U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE_MASK                                    (0x000000fcU)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE_DETECT_QUIET                             (0U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE_DETECT_ACT                               (1U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE_POLL_ACTIVE                              (2U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE_POLL_COMPLIANCE                          (3U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE_POLL_CONFIG                              (4U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE_PRE_DETECT_QUIET                         (5U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE_DETECT_WAIT                              (6U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE_CFG_LINKWD_START                         (7U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE_CFG_LINKWD_ACEPT                         (8U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE_CFG_LANENUM_WAIT                         (9U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE_CFG_LANENUM_ACEPT                        (10U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE_CFG_COMPLETE                             (11U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE_CFG_IDLE                                 (12U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE_RCVRY_LOCK                               (13U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE_RCVRY_SPEED                              (14U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE_RCVRY_RCVRCFG                            (15U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE_RCVRY_IDLE                               (16U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE_L0                                       (17U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE_L0S                                      (18U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE_L123_SEND_EIDLE                          (19U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE_L1_IDLE                                  (20U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE_L2_IDLE                                  (21U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE_L2_WAKE                                  (22U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE_DISABLED_ENTRY                           (23U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE_DISABLED_IDLE                            (24U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE_DISABLED                                 (25U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE_LPBK_ENTRY                               (26U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE_LPBK_ACTIVE                              (27U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE_LPBK_EXIT                                (28U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE_LPBK_EXIT_TIMEOUT                        (29U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE_HOT_RESET_ENTRY                          (30U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE_HOT_RESET                                (31U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE_RCVRY_EQ0                                (32U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE_RCVRY_EQ1                                (33U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE_RCVRY_EQ2                                (34U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_STATE_RCVRY_EQ3                                (35U)

#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_EN_SHIFT                                      (0U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_EN_MASK                                       (0x00000001U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_EN_DISABLED                                    (0U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_LTSSM_EN_ENABLED                                     (1U)

#define PCIECTRL_TI_CONF_DEVICE_CMD_APP_REQ_RETRY_EN_SHIFT                              (1U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_APP_REQ_RETRY_EN_MASK                               (0x00000002U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_APP_REQ_RETRY_EN_DISABLED                            (0U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_APP_REQ_RETRY_EN_ENABLED                             (1U)

#define PCIECTRL_TI_CONF_DEVICE_CMD_DEV_NUM_SHIFT                                       (16U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_DEV_NUM_MASK                                        (0x001f0000U)

#define PCIECTRL_TI_CONF_DEVICE_CMD_BUS_NUM_SHIFT                                       (21U)
#define PCIECTRL_TI_CONF_DEVICE_CMD_BUS_NUM_MASK                                        (0x1fe00000U)

#define PCIECTRL_TI_CONF_PM_CTRL_PME_TURN_OFF_SHIFT                                     (0U)
#define PCIECTRL_TI_CONF_PM_CTRL_PME_TURN_OFF_MASK                                      (0x00000001U)
#define PCIECTRL_TI_CONF_PM_CTRL_PME_TURN_OFF_TRANSMIT                                   (1U)
#define PCIECTRL_TI_CONF_PM_CTRL_PME_TURN_OFF_NOACTION                                   (0U)

#define PCIECTRL_TI_CONF_PM_CTRL_PME_SHIFT                                              (1U)
#define PCIECTRL_TI_CONF_PM_CTRL_PME_MASK                                               (0x00000002U)
#define PCIECTRL_TI_CONF_PM_CTRL_PME_TRANSMIT                                            (1U)
#define PCIECTRL_TI_CONF_PM_CTRL_PME_NOACTION                                            (0U)

#define PCIECTRL_TI_CONF_PM_CTRL_L23_READY_SHIFT                                        (8U)
#define PCIECTRL_TI_CONF_PM_CTRL_L23_READY_MASK                                         (0x00000100U)
#define PCIECTRL_TI_CONF_PM_CTRL_L23_READY_NOT                                           (0U)
#define PCIECTRL_TI_CONF_PM_CTRL_L23_READY                                               (1U)

#define PCIECTRL_TI_CONF_PM_CTRL_REQ_ENTR_L1_SHIFT                                      (9U)
#define PCIECTRL_TI_CONF_PM_CTRL_REQ_ENTR_L1_MASK                                       (0x00000200U)
#define PCIECTRL_TI_CONF_PM_CTRL_REQ_ENTR_L1_INACTIVE                                    (0U)
#define PCIECTRL_TI_CONF_PM_CTRL_REQ_ENTR_L1_ACTIVE                                      (1U)

#define PCIECTRL_TI_CONF_PM_CTRL_REQ_EXIT_L1_SHIFT                                      (10U)
#define PCIECTRL_TI_CONF_PM_CTRL_REQ_EXIT_L1_MASK                                       (0x00000400U)
#define PCIECTRL_TI_CONF_PM_CTRL_REQ_EXIT_L1_INACTIVE                                    (0U)
#define PCIECTRL_TI_CONF_PM_CTRL_REQ_EXIT_L1_ACTIVE                                      (1U)

#define PCIECTRL_TI_CONF_PM_CTRL_AUX_PWR_DET_SHIFT                                      (11U)
#define PCIECTRL_TI_CONF_PM_CTRL_AUX_PWR_DET_MASK                                       (0x00000800U)
#define PCIECTRL_TI_CONF_PM_CTRL_AUX_PWR_DET_UNPOWERED                                   (0U)
#define PCIECTRL_TI_CONF_PM_CTRL_AUX_PWR_DET_POWERED                                     (1U)

#define PCIECTRL_TI_CONF_PHY_CS_LINK_UP_SHIFT                                           (16U)
#define PCIECTRL_TI_CONF_PHY_CS_LINK_UP_MASK                                            (0x00010000U)
#define PCIECTRL_TI_CONF_PHY_CS_LINK_UP_DOWN                                             (0U)
#define PCIECTRL_TI_CONF_PHY_CS_LINK_UP                                                  (1U)

#define PCIECTRL_TI_CONF_PHY_CS_REVERSE_LANES_SHIFT                                     (0U)
#define PCIECTRL_TI_CONF_PHY_CS_REVERSE_LANES_MASK                                      (0x00000001U)
#define PCIECTRL_TI_CONF_PHY_CS_REVERSE_LANES_STRAIGHT                                   (0U)
#define PCIECTRL_TI_CONF_PHY_CS_REVERSE_LANES_REVERSED                                   (1U)

#define PCIECTRL_TI_CONF_INTX_ASSERT_F0_SHIFT                                           (0U)
#define PCIECTRL_TI_CONF_INTX_ASSERT_F0_MASK                                            (0x00000001U)
#define PCIECTRL_TI_CONF_INTX_ASSERT_F0_ACTIVE                                           (0U)
#define PCIECTRL_TI_CONF_INTX_ASSERT_F0_INACTIVE                                         (1U)
#define PCIECTRL_TI_CONF_INTX_ASSERT_F0                                                  (1U)
#define PCIECTRL_TI_CONF_INTX_ASSERT_F0_NOACTION                                         (0U)

#define PCIECTRL_TI_CONF_INTX_DEASSERT_F0_SHIFT                                         (0U)
#define PCIECTRL_TI_CONF_INTX_DEASSERT_F0_MASK                                          (0x00000001U)
#define PCIECTRL_TI_CONF_INTX_DEASSERT_F0_ACTIVE                                         (0U)
#define PCIECTRL_TI_CONF_INTX_DEASSERT_F0_INACTIVE                                       (1U)
#define PCIECTRL_TI_CONF_INTX_DEASSERT_F0                                                (1U)
#define PCIECTRL_TI_CONF_INTX_DEASSERT_F0_NOACTION                                       (0U)

#define PCIECTRL_TI_CONF_MSI_XMT_REQ_GRANT_SHIFT                                        (0U)
#define PCIECTRL_TI_CONF_MSI_XMT_REQ_GRANT_MASK                                         (0x00000001U)
#define PCIECTRL_TI_CONF_MSI_XMT_REQ_GRANT                                               (1U)
#define PCIECTRL_TI_CONF_MSI_XMT_REQ_GRANT_PENDING                                       (1U)
#define PCIECTRL_TI_CONF_MSI_XMT_REQ_GRANT_DONE                                          (0U)
#define PCIECTRL_TI_CONF_MSI_XMT_REQ_GRANT_NO_ACTION                                     (0U)

#define PCIECTRL_TI_CONF_MSI_XMT_FUNC_NUM_SHIFT                                         (1U)
#define PCIECTRL_TI_CONF_MSI_XMT_FUNC_NUM_MASK                                          (0x0000000eU)

#define PCIECTRL_TI_CONF_MSI_XMT_VECTOR_SHIFT                                           (7U)
#define PCIECTRL_TI_CONF_MSI_XMT_VECTOR_MASK                                            (0x00000f80U)

#define PCIECTRL_TI_CONF_MSI_XMT_TC_SHIFT                                               (4U)
#define PCIECTRL_TI_CONF_MSI_XMT_TC_MASK                                                (0x00000070U)

#define PCIECTRL_TI_CONF_DEBUG_CFG_SEL_SHIFT                                            (0U)
#define PCIECTRL_TI_CONF_DEBUG_CFG_SEL_MASK                                             (0x0000003fU)
#define PCIECTRL_TI_CONF_DEBUG_CFG_SEL_TIELO                                             (0U)
#define PCIECTRL_TI_CONF_DEBUG_CFG_SEL_PIPE_L0                                           (1U)
#define PCIECTRL_TI_CONF_DEBUG_CFG_SEL_PIPE_L1                                           (2U)
#define PCIECTRL_TI_CONF_DEBUG_CFG_SEL_INFO_LO                                           (4U)
#define PCIECTRL_TI_CONF_DEBUG_CFG_SEL_INFO_HI                                           (5U)
#define PCIECTRL_TI_CONF_DEBUG_CFG_SEL_PM                                                (3U)

#define PCIECTRL_TI_CONF_DEBUG_DATA_SHIFT                                               (0U)
#define PCIECTRL_TI_CONF_DEBUG_DATA_MASK                                                (0xffffffffU)

#define PCIECTRL_TI_CONF_DIAG_CTRL_INV_LCRC_SHIFT                                       (0U)
#define PCIECTRL_TI_CONF_DIAG_CTRL_INV_LCRC_MASK                                        (0x00000001U)
#define PCIECTRL_TI_CONF_DIAG_CTRL_INV_LCRC_REQ                                          (1U)
#define PCIECTRL_TI_CONF_DIAG_CTRL_INV_LCRC_DONE                                         (0U)
#define PCIECTRL_TI_CONF_DIAG_CTRL_INV_LCRC_PENDING                                      (1U)

#define PCIECTRL_TI_CONF_DIAG_CTRL_INV_ECRC_SHIFT                                       (1U)
#define PCIECTRL_TI_CONF_DIAG_CTRL_INV_ECRC_MASK                                        (0x00000002U)
#define PCIECTRL_TI_CONF_DIAG_CTRL_INV_ECRC_REQ                                          (1U)
#define PCIECTRL_TI_CONF_DIAG_CTRL_INV_ECRC_DONE                                         (0U)
#define PCIECTRL_TI_CONF_DIAG_CTRL_INV_ECRC_PENDING                                      (1U)

#define PCIECTRL_TI_CONF_DIAG_CTRL_FAST_LINK_MODE_SHIFT                                 (2U)
#define PCIECTRL_TI_CONF_DIAG_CTRL_FAST_LINK_MODE_MASK                                  (0x00000004U)
#define PCIECTRL_TI_CONF_DIAG_CTRL_FAST_LINK_MODE_STANDARD                               (0U)
#define PCIECTRL_TI_CONF_DIAG_CTRL_FAST_LINK_MODE                                        (1U)

#ifdef __cplusplus
}
#endif
#endif  /* HW_PCIECTRL_TI_CONF_H_ */

