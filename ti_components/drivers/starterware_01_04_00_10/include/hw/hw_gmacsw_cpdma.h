/******************************************************************************
*
* hw_gmacsw_cpdma.h - register-level header file for GMAC_SW
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
#ifndef HW_GMACSW_CPDMA_H_
#define HW_GMACSW_CPDMA_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions 
****************************************************************************************************/
#define GMAC_SW_DMA_INTSTAT_RAW                                                                             (0xb0U)
#define GMAC_SW_RX0_PENDTHRESH                                                                              (0xc0U)
#define GMAC_SW_TX_PRI6_RATE                                                                                (0x48U)
#define GMAC_SW_DMA_INTMASK_SET                                                                             (0xb8U)
#define GMAC_SW_CPDMA_IN_VECTOR                                                                             (0x90U)
#define GMAC_SW_RX3_PENDTHRESH                                                                              (0xccU)
#define GMAC_SW_TX_PRI3_RATE                                                                                (0x3cU)
#define GMAC_SW_DMA_INTSTAT_MASKED                                                                          (0xb4U)
#define GMAC_SW_TX_INTMASK_CLEAR                                                                            (0x8cU)
#define GMAC_SW_RX_BUFFER_OFFSET                                                                            (0x28U)
#define GMAC_SW_RX_INTMASK_SET                                                                              (0xa8U)
#define GMAC_SW_TX_PRI4_RATE                                                                                (0x40U)
#define GMAC_SW_RX6_FREEBUFFER                                                                              (0xf8U)
#define GMAC_SW_RX2_FREEBUFFER                                                                              (0xe8U)
#define GMAC_SW_CPDMA_SOFT_RESET                                                                            (0x1cU)
#define GMAC_SW_TX_PRI0_RATE                                                                                (0x30U)
#define GMAC_SW_TX_INTMASK_SET                                                                              (0x88U)
#define GMAC_SW_RX4_PENDTHRESH                                                                              (0xd0U)
#define GMAC_SW_EMCONTROL                                                                                   (0x2cU)
#define GMAC_SW_RX4_FREEBUFFER                                                                              (0xf0U)
#define GMAC_SW_DMACONTROL                                                                                  (0x20U)
#define GMAC_SW_TX_TEARDOWN                                                                                 (0x8U)
#define GMAC_SW_RX3_FREEBUFFER                                                                              (0xecU)
#define GMAC_SW_RX_IDVER                                                                                    (0x10U)
#define GMAC_SW_DMASTATUS                                                                                   (0x24U)
#define GMAC_SW_RX_INTSTAT_MASKED                                                                           (0xa4U)
#define GMAC_SW_TX_IDVER                                                                                    (0x0U)
#define GMAC_SW_TX_INTSTAT_RAW                                                                              (0x80U)
#define GMAC_SW_RX_TEARDOWN                                                                                 (0x18U)
#define GMAC_SW_RX7_PENDTHRESH                                                                              (0xdcU)
#define GMAC_SW_CPDMA_EOI_VECTOR                                                                            (0x94U)
#define GMAC_SW_RX_INTMASK_CLEAR                                                                            (0xacU)
#define GMAC_SW_TX_PRI7_RATE                                                                                (0x4cU)
#define GMAC_SW_DMA_INTMASK_CLEAR                                                                           (0xbcU)
#define GMAC_SW_TX_PRI1_RATE                                                                                (0x34U)
#define GMAC_SW_TX_PRI5_RATE                                                                                (0x44U)
#define GMAC_SW_RX0_FREEBUFFER                                                                              (0xe0U)
#define GMAC_SW_TX_PRI2_RATE                                                                                (0x38U)
#define GMAC_SW_RX7_FREEBUFFER                                                                              (0xfcU)
#define GMAC_SW_RX5_PENDTHRESH                                                                              (0xd4U)
#define GMAC_SW_RX5_FREEBUFFER                                                                              (0xf4U)
#define GMAC_SW_TX_CONTROL                                                                                  (0x4U)
#define GMAC_SW_TX_INTSTAT_MASKED                                                                           (0x84U)
#define GMAC_SW_RX_INTSTAT_RAW                                                                              (0xa0U)
#define GMAC_SW_RX1_FREEBUFFER                                                                              (0xe4U)
#define GMAC_SW_RX6_PENDTHRESH                                                                              (0xd8U)
#define GMAC_SW_RX_CONTROL                                                                                  (0x14U)
#define GMAC_SW_RX1_PENDTHRESH                                                                              (0xc4U)
#define GMAC_SW_RX2_PENDTHRESH                                                                              (0xc8U)

/****************************************************************************************************
* Field Definition Macros 
****************************************************************************************************/

#define GMAC_SW_DMA_INTSTAT_RAW_STAT_PEND_SHIFT                                                             (0U)
#define GMAC_SW_DMA_INTSTAT_RAW_STAT_PEND_MASK                                                              (0x00000001U)

#define GMAC_SW_DMA_INTSTAT_RAW_HOST_PEND_SHIFT                                                             (1U)
#define GMAC_SW_DMA_INTSTAT_RAW_HOST_PEND_MASK                                                              (0x00000002U)

#define GMAC_SW_DMA_INTSTAT_RAW_RESERVED1_SHIFT                                                             (2U)
#define GMAC_SW_DMA_INTSTAT_RAW_RESERVED1_MASK                                                              (0xfffffffcU)

#define GMAC_SW_RX0_PENDTHRESH_RX_PENDTHRESH_SHIFT                                                          (0U)
#define GMAC_SW_RX0_PENDTHRESH_RX_PENDTHRESH_MASK                                                           (0x000000ffU)

#define GMAC_SW_RX0_PENDTHRESH_RESERVED1_SHIFT                                                              (8U)
#define GMAC_SW_RX0_PENDTHRESH_RESERVED1_MASK                                                               (0xffffff00U)

#define GMAC_SW_TX_PRI6_RATE_PRIN_SEND_CNT_SHIFT                                                            (0U)
#define GMAC_SW_TX_PRI6_RATE_PRIN_SEND_CNT_MASK                                                             (0x00003fffU)

#define GMAC_SW_TX_PRI6_RATE_RESERVED2_SHIFT                                                                (14U)
#define GMAC_SW_TX_PRI6_RATE_RESERVED2_MASK                                                                 (0x0000c000U)

#define GMAC_SW_TX_PRI6_RATE_PRIN_IDLE_CNT_SHIFT                                                            (16U)
#define GMAC_SW_TX_PRI6_RATE_PRIN_IDLE_CNT_MASK                                                             (0x3fff0000U)

#define GMAC_SW_TX_PRI6_RATE_RESERVED1_SHIFT                                                                (30U)
#define GMAC_SW_TX_PRI6_RATE_RESERVED1_MASK                                                                 (0xc0000000U)

#define GMAC_SW_DMA_INTMASK_SET_STAT_INT_MASK_SHIFT                                                         (0U)
#define GMAC_SW_DMA_INTMASK_SET_STAT_INT_MASK_MASK                                                          (0x00000001U)

#define GMAC_SW_DMA_INTMASK_SET_HOST_ERR_INT_MASK_SHIFT                                                     (1U)
#define GMAC_SW_DMA_INTMASK_SET_HOST_ERR_INT_MASK_MASK                                                      (0x00000002U)

#define GMAC_SW_DMA_INTMASK_SET_RESERVED1_SHIFT                                                             (2U)
#define GMAC_SW_DMA_INTMASK_SET_RESERVED1_MASK                                                              (0xfffffffcU)

#define GMAC_SW_CPDMA_IN_VECTOR_DMA_IN_VECTOR_SHIFT                                                         (0U)
#define GMAC_SW_CPDMA_IN_VECTOR_DMA_IN_VECTOR_MASK                                                          (0xffffffffU)

#define GMAC_SW_RX3_PENDTHRESH_RX_PENDTHRESH_SHIFT                                                          (0U)
#define GMAC_SW_RX3_PENDTHRESH_RX_PENDTHRESH_MASK                                                           (0x000000ffU)

#define GMAC_SW_RX3_PENDTHRESH_RESERVED1_SHIFT                                                              (8U)
#define GMAC_SW_RX3_PENDTHRESH_RESERVED1_MASK                                                               (0xffffff00U)

#define GMAC_SW_TX_PRI3_RATE_PRIN_SEND_CNT_SHIFT                                                            (0U)
#define GMAC_SW_TX_PRI3_RATE_PRIN_SEND_CNT_MASK                                                             (0x00003fffU)

#define GMAC_SW_TX_PRI3_RATE_RESERVED2_SHIFT                                                                (14U)
#define GMAC_SW_TX_PRI3_RATE_RESERVED2_MASK                                                                 (0x0000c000U)

#define GMAC_SW_TX_PRI3_RATE_PRIN_IDLE_CNT_SHIFT                                                            (16U)
#define GMAC_SW_TX_PRI3_RATE_PRIN_IDLE_CNT_MASK                                                             (0x3fff0000U)

#define GMAC_SW_TX_PRI3_RATE_RESERVED1_SHIFT                                                                (30U)
#define GMAC_SW_TX_PRI3_RATE_RESERVED1_MASK                                                                 (0xc0000000U)

#define GMAC_SW_DMA_INTSTAT_MASKED_STAT_PEND_SHIFT                                                          (0U)
#define GMAC_SW_DMA_INTSTAT_MASKED_STAT_PEND_MASK                                                           (0x00000001U)

#define GMAC_SW_DMA_INTSTAT_MASKED_HOST_PEND_SHIFT                                                          (1U)
#define GMAC_SW_DMA_INTSTAT_MASKED_HOST_PEND_MASK                                                           (0x00000002U)

#define GMAC_SW_DMA_INTSTAT_MASKED_RESERVED1_SHIFT                                                          (2U)
#define GMAC_SW_DMA_INTSTAT_MASKED_RESERVED1_MASK                                                           (0xfffffffcU)

#define GMAC_SW_TX_INTMASK_CLEAR_TX0_MASK_SHIFT                                                             (0U)
#define GMAC_SW_TX_INTMASK_CLEAR_TX0_MASK_MASK                                                              (0x00000001U)

#define GMAC_SW_TX_INTMASK_CLEAR_TX1_MASK_SHIFT                                                             (1U)
#define GMAC_SW_TX_INTMASK_CLEAR_TX1_MASK_MASK                                                              (0x00000002U)

#define GMAC_SW_TX_INTMASK_CLEAR_TX2_MASK_SHIFT                                                             (2U)
#define GMAC_SW_TX_INTMASK_CLEAR_TX2_MASK_MASK                                                              (0x00000004U)

#define GMAC_SW_TX_INTMASK_CLEAR_TX3_MASK_SHIFT                                                             (3U)
#define GMAC_SW_TX_INTMASK_CLEAR_TX3_MASK_MASK                                                              (0x00000008U)

#define GMAC_SW_TX_INTMASK_CLEAR_TX4_MASK_SHIFT                                                             (4U)
#define GMAC_SW_TX_INTMASK_CLEAR_TX4_MASK_MASK                                                              (0x00000010U)

#define GMAC_SW_TX_INTMASK_CLEAR_TX5_MASK_SHIFT                                                             (5U)
#define GMAC_SW_TX_INTMASK_CLEAR_TX5_MASK_MASK                                                              (0x00000020U)

#define GMAC_SW_TX_INTMASK_CLEAR_TX6_MASK_SHIFT                                                             (6U)
#define GMAC_SW_TX_INTMASK_CLEAR_TX6_MASK_MASK                                                              (0x00000040U)

#define GMAC_SW_TX_INTMASK_CLEAR_TX7_MASK_SHIFT                                                             (7U)
#define GMAC_SW_TX_INTMASK_CLEAR_TX7_MASK_MASK                                                              (0x00000080U)

#define GMAC_SW_TX_INTMASK_CLEAR_RESERVED1_SHIFT                                                            (8U)
#define GMAC_SW_TX_INTMASK_CLEAR_RESERVED1_MASK                                                             (0xffffff00U)

#define GMAC_SW_RX_BUFFER_OFFSET_RX_BUFFER_OFFSET_SHIFT                                                     (0U)
#define GMAC_SW_RX_BUFFER_OFFSET_RX_BUFFER_OFFSET_MASK                                                      (0x0000ffffU)

#define GMAC_SW_RX_BUFFER_OFFSET_RESERVED1_SHIFT                                                            (16U)
#define GMAC_SW_RX_BUFFER_OFFSET_RESERVED1_MASK                                                             (0xffff0000U)

#define GMAC_SW_RX_INTMASK_SET_RX0_PEND_MASK_SHIFT                                                          (0U)
#define GMAC_SW_RX_INTMASK_SET_RX0_PEND_MASK_MASK                                                           (0x00000001U)

#define GMAC_SW_RX_INTMASK_SET_RX1_PEND_MASK_SHIFT                                                          (1U)
#define GMAC_SW_RX_INTMASK_SET_RX1_PEND_MASK_MASK                                                           (0x00000002U)

#define GMAC_SW_RX_INTMASK_SET_RX2_PEND_MASK_SHIFT                                                          (2U)
#define GMAC_SW_RX_INTMASK_SET_RX2_PEND_MASK_MASK                                                           (0x00000004U)

#define GMAC_SW_RX_INTMASK_SET_RX3_PEND_MASK_SHIFT                                                          (3U)
#define GMAC_SW_RX_INTMASK_SET_RX3_PEND_MASK_MASK                                                           (0x00000008U)

#define GMAC_SW_RX_INTMASK_SET_RX4_PEND_MASK_SHIFT                                                          (4U)
#define GMAC_SW_RX_INTMASK_SET_RX4_PEND_MASK_MASK                                                           (0x00000010U)

#define GMAC_SW_RX_INTMASK_SET_RX5_PEND_MASK_SHIFT                                                          (5U)
#define GMAC_SW_RX_INTMASK_SET_RX5_PEND_MASK_MASK                                                           (0x00000020U)

#define GMAC_SW_RX_INTMASK_SET_RX6_PEND_MASK_SHIFT                                                          (6U)
#define GMAC_SW_RX_INTMASK_SET_RX6_PEND_MASK_MASK                                                           (0x00000040U)

#define GMAC_SW_RX_INTMASK_SET_RX7_PEND_MASK_SHIFT                                                          (7U)
#define GMAC_SW_RX_INTMASK_SET_RX7_PEND_MASK_MASK                                                           (0x00000080U)

#define GMAC_SW_RX_INTMASK_SET_RX0_THRESH_PEND_MASK_SHIFT                                                   (8U)
#define GMAC_SW_RX_INTMASK_SET_RX0_THRESH_PEND_MASK_MASK                                                    (0x00000100U)

#define GMAC_SW_RX_INTMASK_SET_RX1_THRESH_PEND_MASK_SHIFT                                                   (9U)
#define GMAC_SW_RX_INTMASK_SET_RX1_THRESH_PEND_MASK_MASK                                                    (0x00000200U)

#define GMAC_SW_RX_INTMASK_SET_RX2_THRESH_PEND_MASK_SHIFT                                                   (10U)
#define GMAC_SW_RX_INTMASK_SET_RX2_THRESH_PEND_MASK_MASK                                                    (0x00000400U)

#define GMAC_SW_RX_INTMASK_SET_RX3_THRESH_PEND_MASK_SHIFT                                                   (11U)
#define GMAC_SW_RX_INTMASK_SET_RX3_THRESH_PEND_MASK_MASK                                                    (0x00000800U)

#define GMAC_SW_RX_INTMASK_SET_RX4_THRESH_PEND_MASK_SHIFT                                                   (12U)
#define GMAC_SW_RX_INTMASK_SET_RX4_THRESH_PEND_MASK_MASK                                                    (0x00001000U)

#define GMAC_SW_RX_INTMASK_SET_RX5_THRESH_PEND_MASK_SHIFT                                                   (13U)
#define GMAC_SW_RX_INTMASK_SET_RX5_THRESH_PEND_MASK_MASK                                                    (0x00002000U)

#define GMAC_SW_RX_INTMASK_SET_RX6_THRESH_PEND_MASK_SHIFT                                                   (14U)
#define GMAC_SW_RX_INTMASK_SET_RX6_THRESH_PEND_MASK_MASK                                                    (0x00004000U)

#define GMAC_SW_RX_INTMASK_SET_RX7_THRESH_PEND_MASK_SHIFT                                                   (15U)
#define GMAC_SW_RX_INTMASK_SET_RX7_THRESH_PEND_MASK_MASK                                                    (0x00008000U)

#define GMAC_SW_RX_INTMASK_SET_RESERVED1_SHIFT                                                              (16U)
#define GMAC_SW_RX_INTMASK_SET_RESERVED1_MASK                                                               (0xffff0000U)

#define GMAC_SW_TX_PRI4_RATE_PRIN_SEND_CNT_SHIFT                                                            (0U)
#define GMAC_SW_TX_PRI4_RATE_PRIN_SEND_CNT_MASK                                                             (0x00003fffU)

#define GMAC_SW_TX_PRI4_RATE_RESERVED2_SHIFT                                                                (14U)
#define GMAC_SW_TX_PRI4_RATE_RESERVED2_MASK                                                                 (0x0000c000U)

#define GMAC_SW_TX_PRI4_RATE_PRIN_IDLE_CNT_SHIFT                                                            (16U)
#define GMAC_SW_TX_PRI4_RATE_PRIN_IDLE_CNT_MASK                                                             (0x3fff0000U)

#define GMAC_SW_TX_PRI4_RATE_RESERVED1_SHIFT                                                                (30U)
#define GMAC_SW_TX_PRI4_RATE_RESERVED1_MASK                                                                 (0xc0000000U)

#define GMAC_SW_RX6_FREEBUFFER_RX_FREEBUFFER_SHIFT                                                          (0U)
#define GMAC_SW_RX6_FREEBUFFER_RX_FREEBUFFER_MASK                                                           (0x0000ffffU)

#define GMAC_SW_RX6_FREEBUFFER_RESERVED1_SHIFT                                                              (16U)
#define GMAC_SW_RX6_FREEBUFFER_RESERVED1_MASK                                                               (0xffff0000U)

#define GMAC_SW_RX2_FREEBUFFER_RX_FREEBUFFER_SHIFT                                                          (0U)
#define GMAC_SW_RX2_FREEBUFFER_RX_FREEBUFFER_MASK                                                           (0x0000ffffU)

#define GMAC_SW_RX2_FREEBUFFER_RESERVED1_SHIFT                                                              (16U)
#define GMAC_SW_RX2_FREEBUFFER_RESERVED1_MASK                                                               (0xffff0000U)

#define GMAC_SW_CPDMA_SOFT_RESET_SOFT_RESET_SHIFT                                                           (0U)
#define GMAC_SW_CPDMA_SOFT_RESET_SOFT_RESET_MASK                                                            (0x00000001U)

#define GMAC_SW_CPDMA_SOFT_RESET_RESERVED1_SHIFT                                                            (1U)
#define GMAC_SW_CPDMA_SOFT_RESET_RESERVED1_MASK                                                             (0xfffffffeU)

#define GMAC_SW_TX_PRI0_RATE_PRIN_SEND_CNT_SHIFT                                                            (0U)
#define GMAC_SW_TX_PRI0_RATE_PRIN_SEND_CNT_MASK                                                             (0x00003fffU)

#define GMAC_SW_TX_PRI0_RATE_RESERVED2_SHIFT                                                                (14U)
#define GMAC_SW_TX_PRI0_RATE_RESERVED2_MASK                                                                 (0x0000c000U)

#define GMAC_SW_TX_PRI0_RATE_PRIN_IDLE_CNT_SHIFT                                                            (16U)
#define GMAC_SW_TX_PRI0_RATE_PRIN_IDLE_CNT_MASK                                                             (0x3fff0000U)

#define GMAC_SW_TX_PRI0_RATE_RESERVED1_SHIFT                                                                (30U)
#define GMAC_SW_TX_PRI0_RATE_RESERVED1_MASK                                                                 (0xc0000000U)

#define GMAC_SW_TX_INTMASK_SET_TX0_MASK_SHIFT                                                               (0U)
#define GMAC_SW_TX_INTMASK_SET_TX0_MASK_MASK                                                                (0x00000001U)

#define GMAC_SW_TX_INTMASK_SET_TX1_MASK_SHIFT                                                               (1U)
#define GMAC_SW_TX_INTMASK_SET_TX1_MASK_MASK                                                                (0x00000002U)

#define GMAC_SW_TX_INTMASK_SET_TX2_MASK_SHIFT                                                               (2U)
#define GMAC_SW_TX_INTMASK_SET_TX2_MASK_MASK                                                                (0x00000004U)

#define GMAC_SW_TX_INTMASK_SET_TX3_MASK_SHIFT                                                               (3U)
#define GMAC_SW_TX_INTMASK_SET_TX3_MASK_MASK                                                                (0x00000008U)

#define GMAC_SW_TX_INTMASK_SET_TX4_MASK_SHIFT                                                               (4U)
#define GMAC_SW_TX_INTMASK_SET_TX4_MASK_MASK                                                                (0x00000010U)

#define GMAC_SW_TX_INTMASK_SET_TX5_MASK_SHIFT                                                               (5U)
#define GMAC_SW_TX_INTMASK_SET_TX5_MASK_MASK                                                                (0x00000020U)

#define GMAC_SW_TX_INTMASK_SET_TX6_MASK_SHIFT                                                               (6U)
#define GMAC_SW_TX_INTMASK_SET_TX6_MASK_MASK                                                                (0x00000040U)

#define GMAC_SW_TX_INTMASK_SET_TX7_MASK_SHIFT                                                               (7U)
#define GMAC_SW_TX_INTMASK_SET_TX7_MASK_MASK                                                                (0x00000080U)

#define GMAC_SW_TX_INTMASK_SET_RESERVED1_SHIFT                                                              (8U)
#define GMAC_SW_TX_INTMASK_SET_RESERVED1_MASK                                                               (0xffffff00U)

#define GMAC_SW_RX4_PENDTHRESH_RX_PENDTHRESH_SHIFT                                                          (0U)
#define GMAC_SW_RX4_PENDTHRESH_RX_PENDTHRESH_MASK                                                           (0x000000ffU)

#define GMAC_SW_RX4_PENDTHRESH_RESERVED1_SHIFT                                                              (8U)
#define GMAC_SW_RX4_PENDTHRESH_RESERVED1_MASK                                                               (0xffffff00U)

#define GMAC_SW_EMCONTROL_FREE_SHIFT                                                                        (0U)
#define GMAC_SW_EMCONTROL_FREE_MASK                                                                         (0x00000001U)

#define GMAC_SW_EMCONTROL_SOFT_SHIFT                                                                        (1U)
#define GMAC_SW_EMCONTROL_SOFT_MASK                                                                         (0x00000002U)

#define GMAC_SW_EMCONTROL_RESERVED1_SHIFT                                                                   (2U)
#define GMAC_SW_EMCONTROL_RESERVED1_MASK                                                                    (0xfffffffcU)

#define GMAC_SW_RX4_FREEBUFFER_RX_FREEBUFFER_SHIFT                                                          (0U)
#define GMAC_SW_RX4_FREEBUFFER_RX_FREEBUFFER_MASK                                                           (0x0000ffffU)

#define GMAC_SW_RX4_FREEBUFFER_RESERVED1_SHIFT                                                              (16U)
#define GMAC_SW_RX4_FREEBUFFER_RESERVED1_MASK                                                               (0xffff0000U)

#define GMAC_SW_DMACONTROL_TX_PTYPE_SHIFT                                                                   (0U)
#define GMAC_SW_DMACONTROL_TX_PTYPE_MASK                                                                    (0x00000001U)

#define GMAC_SW_DMACONTROL_RX_OWNERSHIP_SHIFT                                                               (1U)
#define GMAC_SW_DMACONTROL_RX_OWNERSHIP_MASK                                                                (0x00000002U)

#define GMAC_SW_DMACONTROL_RX_OFFLEN_BLOCK_SHIFT                                                            (2U)
#define GMAC_SW_DMACONTROL_RX_OFFLEN_BLOCK_MASK                                                             (0x00000004U)

#define GMAC_SW_DMACONTROL_CMD_IDLE_SHIFT                                                                   (3U)
#define GMAC_SW_DMACONTROL_CMD_IDLE_MASK                                                                    (0x00000008U)

#define GMAC_SW_DMACONTROL_RX_CEF_SHIFT                                                                     (4U)
#define GMAC_SW_DMACONTROL_RX_CEF_MASK                                                                      (0x00000010U)

#define GMAC_SW_DMACONTROL_RESERVED2_SHIFT                                                                  (5U)
#define GMAC_SW_DMACONTROL_RESERVED2_MASK                                                                   (0x000000e0U)

#define GMAC_SW_DMACONTROL_TX_RLIM_SHIFT                                                                    (8U)
#define GMAC_SW_DMACONTROL_TX_RLIM_MASK                                                                     (0x0000ff00U)

#define GMAC_SW_DMACONTROL_RESERVED1_SHIFT                                                                  (16U)
#define GMAC_SW_DMACONTROL_RESERVED1_MASK                                                                   (0xffff0000U)

#define GMAC_SW_TX_TEARDOWN_TX_TDN_CH_SHIFT                                                                 (0U)
#define GMAC_SW_TX_TEARDOWN_TX_TDN_CH_MASK                                                                  (0x00000007U)

#define GMAC_SW_TX_TEARDOWN_RESERVED1_SHIFT                                                                 (3U)
#define GMAC_SW_TX_TEARDOWN_RESERVED1_MASK                                                                  (0x7ffffff8U)

#define GMAC_SW_TX_TEARDOWN_TX_TDN_RDY_SHIFT                                                                (31U)
#define GMAC_SW_TX_TEARDOWN_TX_TDN_RDY_MASK                                                                 (0x80000000U)

#define GMAC_SW_RX3_FREEBUFFER_RX_FREEBUFFER_SHIFT                                                          (0U)
#define GMAC_SW_RX3_FREEBUFFER_RX_FREEBUFFER_MASK                                                           (0x0000ffffU)

#define GMAC_SW_RX3_FREEBUFFER_RESERVED1_SHIFT                                                              (16U)
#define GMAC_SW_RX3_FREEBUFFER_RESERVED1_MASK                                                               (0xffff0000U)

#define GMAC_SW_RX_IDVER_RX_MINOR_VER_SHIFT                                                                 (0U)
#define GMAC_SW_RX_IDVER_RX_MINOR_VER_MASK                                                                  (0x000000ffU)

#define GMAC_SW_RX_IDVER_RX_MAJOR_VER_SHIFT                                                                 (8U)
#define GMAC_SW_RX_IDVER_RX_MAJOR_VER_MASK                                                                  (0x0000ff00U)

#define GMAC_SW_RX_IDVER_RX_IDENT_SHIFT                                                                     (16U)
#define GMAC_SW_RX_IDVER_RX_IDENT_MASK                                                                      (0xffff0000U)

#define GMAC_SW_DMASTATUS_RESERVED4_SHIFT                                                                   (0U)
#define GMAC_SW_DMASTATUS_RESERVED4_MASK                                                                    (0x000000ffU)

#define GMAC_SW_DMASTATUS_RX_ERR_CH_SHIFT                                                                   (8U)
#define GMAC_SW_DMASTATUS_RX_ERR_CH_MASK                                                                    (0x00000700U)

#define GMAC_SW_DMASTATUS_RESERVED3_SHIFT                                                                   (11U)
#define GMAC_SW_DMASTATUS_RESERVED3_MASK                                                                    (0x00000800U)

#define GMAC_SW_DMASTATUS_RX_HOST_ERR_CODE_SHIFT                                                            (12U)
#define GMAC_SW_DMASTATUS_RX_HOST_ERR_CODE_MASK                                                             (0x0000f000U)

#define GMAC_SW_DMASTATUS_TX_ERR_CH_SHIFT                                                                   (16U)
#define GMAC_SW_DMASTATUS_TX_ERR_CH_MASK                                                                    (0x00070000U)

#define GMAC_SW_DMASTATUS_RESERVED2_SHIFT                                                                   (19U)
#define GMAC_SW_DMASTATUS_RESERVED2_MASK                                                                    (0x00080000U)

#define GMAC_SW_DMASTATUS_TX_HOST_ERR_CODE_SHIFT                                                            (20U)
#define GMAC_SW_DMASTATUS_TX_HOST_ERR_CODE_MASK                                                             (0x00f00000U)

#define GMAC_SW_DMASTATUS_RESERVED1_SHIFT                                                                   (24U)
#define GMAC_SW_DMASTATUS_RESERVED1_MASK                                                                    (0x7f000000U)

#define GMAC_SW_DMASTATUS_IDLE_SHIFT                                                                        (31U)
#define GMAC_SW_DMASTATUS_IDLE_MASK                                                                         (0x80000000U)

#define GMAC_SW_RX_INTSTAT_MASKED_RX0_PEND_SHIFT                                                            (0U)
#define GMAC_SW_RX_INTSTAT_MASKED_RX0_PEND_MASK                                                             (0x00000001U)

#define GMAC_SW_RX_INTSTAT_MASKED_RX1_PEND_SHIFT                                                            (1U)
#define GMAC_SW_RX_INTSTAT_MASKED_RX1_PEND_MASK                                                             (0x00000002U)

#define GMAC_SW_RX_INTSTAT_MASKED_RX2_PEND_SHIFT                                                            (2U)
#define GMAC_SW_RX_INTSTAT_MASKED_RX2_PEND_MASK                                                             (0x00000004U)

#define GMAC_SW_RX_INTSTAT_MASKED_RX3_PEND_SHIFT                                                            (3U)
#define GMAC_SW_RX_INTSTAT_MASKED_RX3_PEND_MASK                                                             (0x00000008U)

#define GMAC_SW_RX_INTSTAT_MASKED_RX4_PEND_SHIFT                                                            (4U)
#define GMAC_SW_RX_INTSTAT_MASKED_RX4_PEND_MASK                                                             (0x00000010U)

#define GMAC_SW_RX_INTSTAT_MASKED_RX5_PEND_SHIFT                                                            (5U)
#define GMAC_SW_RX_INTSTAT_MASKED_RX5_PEND_MASK                                                             (0x00000020U)

#define GMAC_SW_RX_INTSTAT_MASKED_RX6_PEND_SHIFT                                                            (6U)
#define GMAC_SW_RX_INTSTAT_MASKED_RX6_PEND_MASK                                                             (0x00000040U)

#define GMAC_SW_RX_INTSTAT_MASKED_RX7_PEND_SHIFT                                                            (7U)
#define GMAC_SW_RX_INTSTAT_MASKED_RX7_PEND_MASK                                                             (0x00000080U)

#define GMAC_SW_RX_INTSTAT_MASKED_RX0_THRESH_PEND_SHIFT                                                     (8U)
#define GMAC_SW_RX_INTSTAT_MASKED_RX0_THRESH_PEND_MASK                                                      (0x00000100U)

#define GMAC_SW_RX_INTSTAT_MASKED_RX1_THRESH_PEND_SHIFT                                                     (9U)
#define GMAC_SW_RX_INTSTAT_MASKED_RX1_THRESH_PEND_MASK                                                      (0x00000200U)

#define GMAC_SW_RX_INTSTAT_MASKED_RX2_THRESH_PEND_SHIFT                                                     (10U)
#define GMAC_SW_RX_INTSTAT_MASKED_RX2_THRESH_PEND_MASK                                                      (0x00000400U)

#define GMAC_SW_RX_INTSTAT_MASKED_RX3_THRESH_PEND_SHIFT                                                     (11U)
#define GMAC_SW_RX_INTSTAT_MASKED_RX3_THRESH_PEND_MASK                                                      (0x00000800U)

#define GMAC_SW_RX_INTSTAT_MASKED_RX4_THRESH_PEND_SHIFT                                                     (12U)
#define GMAC_SW_RX_INTSTAT_MASKED_RX4_THRESH_PEND_MASK                                                      (0x00001000U)

#define GMAC_SW_RX_INTSTAT_MASKED_RX5_THRESH_PEND_SHIFT                                                     (13U)
#define GMAC_SW_RX_INTSTAT_MASKED_RX5_THRESH_PEND_MASK                                                      (0x00002000U)

#define GMAC_SW_RX_INTSTAT_MASKED_RX6_THRESH_PEND_SHIFT                                                     (14U)
#define GMAC_SW_RX_INTSTAT_MASKED_RX6_THRESH_PEND_MASK                                                      (0x00004000U)

#define GMAC_SW_RX_INTSTAT_MASKED_RX7_THRESH_PEND_SHIFT                                                     (15U)
#define GMAC_SW_RX_INTSTAT_MASKED_RX7_THRESH_PEND_MASK                                                      (0x00008000U)

#define GMAC_SW_RX_INTSTAT_MASKED_RESERVED1_SHIFT                                                           (16U)
#define GMAC_SW_RX_INTSTAT_MASKED_RESERVED1_MASK                                                            (0xffff0000U)

#define GMAC_SW_TX_IDVER_TX_MINOR_VER_SHIFT                                                                 (0U)
#define GMAC_SW_TX_IDVER_TX_MINOR_VER_MASK                                                                  (0x000000ffU)

#define GMAC_SW_TX_IDVER_TX_MAJOR_VER_SHIFT                                                                 (8U)
#define GMAC_SW_TX_IDVER_TX_MAJOR_VER_MASK                                                                  (0x0000ff00U)

#define GMAC_SW_TX_IDVER_TX_IDENT_SHIFT                                                                     (16U)
#define GMAC_SW_TX_IDVER_TX_IDENT_MASK                                                                      (0xffff0000U)

#define GMAC_SW_TX_INTSTAT_RAW_TX0_PEND_SHIFT                                                               (0U)
#define GMAC_SW_TX_INTSTAT_RAW_TX0_PEND_MASK                                                                (0x00000001U)

#define GMAC_SW_TX_INTSTAT_RAW_TX1_PEND_SHIFT                                                               (1U)
#define GMAC_SW_TX_INTSTAT_RAW_TX1_PEND_MASK                                                                (0x00000002U)

#define GMAC_SW_TX_INTSTAT_RAW_TX2_PEND_SHIFT                                                               (2U)
#define GMAC_SW_TX_INTSTAT_RAW_TX2_PEND_MASK                                                                (0x00000004U)

#define GMAC_SW_TX_INTSTAT_RAW_TX3_PEND_SHIFT                                                               (3U)
#define GMAC_SW_TX_INTSTAT_RAW_TX3_PEND_MASK                                                                (0x00000008U)

#define GMAC_SW_TX_INTSTAT_RAW_TX4_PEND_SHIFT                                                               (4U)
#define GMAC_SW_TX_INTSTAT_RAW_TX4_PEND_MASK                                                                (0x00000010U)

#define GMAC_SW_TX_INTSTAT_RAW_TX5_PEND_SHIFT                                                               (5U)
#define GMAC_SW_TX_INTSTAT_RAW_TX5_PEND_MASK                                                                (0x00000020U)

#define GMAC_SW_TX_INTSTAT_RAW_TX6_PEND_SHIFT                                                               (6U)
#define GMAC_SW_TX_INTSTAT_RAW_TX6_PEND_MASK                                                                (0x00000040U)

#define GMAC_SW_TX_INTSTAT_RAW_TX7_PEND_SHIFT                                                               (7U)
#define GMAC_SW_TX_INTSTAT_RAW_TX7_PEND_MASK                                                                (0x00000080U)

#define GMAC_SW_TX_INTSTAT_RAW_RESERVED1_SHIFT                                                              (8U)
#define GMAC_SW_TX_INTSTAT_RAW_RESERVED1_MASK                                                               (0xffffff00U)

#define GMAC_SW_RX_TEARDOWN_RX_TDN_CH_SHIFT                                                                 (0U)
#define GMAC_SW_RX_TEARDOWN_RX_TDN_CH_MASK                                                                  (0x00000007U)

#define GMAC_SW_RX_TEARDOWN_RESERVED1_SHIFT                                                                 (3U)
#define GMAC_SW_RX_TEARDOWN_RESERVED1_MASK                                                                  (0x7ffffff8U)

#define GMAC_SW_RX_TEARDOWN_RX_TDN_RDY_SHIFT                                                                (31U)
#define GMAC_SW_RX_TEARDOWN_RX_TDN_RDY_MASK                                                                 (0x80000000U)

#define GMAC_SW_RX7_PENDTHRESH_RX_PENDTHRESH_SHIFT                                                          (0U)
#define GMAC_SW_RX7_PENDTHRESH_RX_PENDTHRESH_MASK                                                           (0x000000ffU)

#define GMAC_SW_RX7_PENDTHRESH_RESERVED1_SHIFT                                                              (8U)
#define GMAC_SW_RX7_PENDTHRESH_RESERVED1_MASK                                                               (0xffffff00U)

#define GMAC_SW_CPDMA_EOI_VECTOR_DMA_EOI_VECTOR_SHIFT                                                       (0U)
#define GMAC_SW_CPDMA_EOI_VECTOR_DMA_EOI_VECTOR_MASK                                                        (0x0000001fU)

#define GMAC_SW_CPDMA_EOI_VECTOR_RESERVED1_SHIFT                                                            (5U)
#define GMAC_SW_CPDMA_EOI_VECTOR_RESERVED1_MASK                                                             (0xffffffe0U)

#define GMAC_SW_RX_INTMASK_CLEAR_RX0_PEND_MASK_SHIFT                                                        (0U)
#define GMAC_SW_RX_INTMASK_CLEAR_RX0_PEND_MASK_MASK                                                         (0x00000001U)

#define GMAC_SW_RX_INTMASK_CLEAR_RX1_PEND_MASK_SHIFT                                                        (1U)
#define GMAC_SW_RX_INTMASK_CLEAR_RX1_PEND_MASK_MASK                                                         (0x00000002U)

#define GMAC_SW_RX_INTMASK_CLEAR_RX2_PEND_MASK_SHIFT                                                        (2U)
#define GMAC_SW_RX_INTMASK_CLEAR_RX2_PEND_MASK_MASK                                                         (0x00000004U)

#define GMAC_SW_RX_INTMASK_CLEAR_RX3_PEND_MASK_SHIFT                                                        (3U)
#define GMAC_SW_RX_INTMASK_CLEAR_RX3_PEND_MASK_MASK                                                         (0x00000008U)

#define GMAC_SW_RX_INTMASK_CLEAR_RX4_PEND_MASK_SHIFT                                                        (4U)
#define GMAC_SW_RX_INTMASK_CLEAR_RX4_PEND_MASK_MASK                                                         (0x00000010U)

#define GMAC_SW_RX_INTMASK_CLEAR_RX5_PEND_MASK_SHIFT                                                        (5U)
#define GMAC_SW_RX_INTMASK_CLEAR_RX5_PEND_MASK_MASK                                                         (0x00000020U)

#define GMAC_SW_RX_INTMASK_CLEAR_RX6_PEND_MASK_SHIFT                                                        (6U)
#define GMAC_SW_RX_INTMASK_CLEAR_RX6_PEND_MASK_MASK                                                         (0x00000040U)

#define GMAC_SW_RX_INTMASK_CLEAR_RX7_PEND_MASK_SHIFT                                                        (7U)
#define GMAC_SW_RX_INTMASK_CLEAR_RX7_PEND_MASK_MASK                                                         (0x00000080U)

#define GMAC_SW_RX_INTMASK_CLEAR_RX0_THRESH_PEND_MASK_SHIFT                                                 (8U)
#define GMAC_SW_RX_INTMASK_CLEAR_RX0_THRESH_PEND_MASK_MASK                                                  (0x00000100U)

#define GMAC_SW_RX_INTMASK_CLEAR_RX1_THRESH_PEND_MASK_SHIFT                                                 (9U)
#define GMAC_SW_RX_INTMASK_CLEAR_RX1_THRESH_PEND_MASK_MASK                                                  (0x00000200U)

#define GMAC_SW_RX_INTMASK_CLEAR_RX2_THRESH_PEND_MASK_SHIFT                                                 (10U)
#define GMAC_SW_RX_INTMASK_CLEAR_RX2_THRESH_PEND_MASK_MASK                                                  (0x00000400U)

#define GMAC_SW_RX_INTMASK_CLEAR_RX3_THRESH_PEND_MASK_SHIFT                                                 (11U)
#define GMAC_SW_RX_INTMASK_CLEAR_RX3_THRESH_PEND_MASK_MASK                                                  (0x00000800U)

#define GMAC_SW_RX_INTMASK_CLEAR_RX4_THRESH_PEND_MASK_SHIFT                                                 (12U)
#define GMAC_SW_RX_INTMASK_CLEAR_RX4_THRESH_PEND_MASK_MASK                                                  (0x00001000U)

#define GMAC_SW_RX_INTMASK_CLEAR_RX5_THRESH_PEND_MASK_SHIFT                                                 (13U)
#define GMAC_SW_RX_INTMASK_CLEAR_RX5_THRESH_PEND_MASK_MASK                                                  (0x00002000U)

#define GMAC_SW_RX_INTMASK_CLEAR_RX6_THRESH_PEND_MASK_SHIFT                                                 (14U)
#define GMAC_SW_RX_INTMASK_CLEAR_RX6_THRESH_PEND_MASK_MASK                                                  (0x00004000U)

#define GMAC_SW_RX_INTMASK_CLEAR_RX7_THRESH_PEND_MASK_SHIFT                                                 (15U)
#define GMAC_SW_RX_INTMASK_CLEAR_RX7_THRESH_PEND_MASK_MASK                                                  (0x00008000U)

#define GMAC_SW_RX_INTMASK_CLEAR_RESERVED1_SHIFT                                                            (16U)
#define GMAC_SW_RX_INTMASK_CLEAR_RESERVED1_MASK                                                             (0xffff0000U)

#define GMAC_SW_TX_PRI7_RATE_PRIN_SEND_CNT_SHIFT                                                            (0U)
#define GMAC_SW_TX_PRI7_RATE_PRIN_SEND_CNT_MASK                                                             (0x00003fffU)

#define GMAC_SW_TX_PRI7_RATE_RESERVED2_SHIFT                                                                (14U)
#define GMAC_SW_TX_PRI7_RATE_RESERVED2_MASK                                                                 (0x0000c000U)

#define GMAC_SW_TX_PRI7_RATE_PRIN_IDLE_CNT_SHIFT                                                            (16U)
#define GMAC_SW_TX_PRI7_RATE_PRIN_IDLE_CNT_MASK                                                             (0x3fff0000U)

#define GMAC_SW_TX_PRI7_RATE_RESERVED1_SHIFT                                                                (30U)
#define GMAC_SW_TX_PRI7_RATE_RESERVED1_MASK                                                                 (0xc0000000U)

#define GMAC_SW_DMA_INTMASK_CLEAR_STAT_INT_MASK_SHIFT                                                       (0U)
#define GMAC_SW_DMA_INTMASK_CLEAR_STAT_INT_MASK_MASK                                                        (0x00000001U)

#define GMAC_SW_DMA_INTMASK_CLEAR_HOST_ERR_INT_MASK_SHIFT                                                   (1U)
#define GMAC_SW_DMA_INTMASK_CLEAR_HOST_ERR_INT_MASK_MASK                                                    (0x00000002U)

#define GMAC_SW_DMA_INTMASK_CLEAR_RESERVED1_SHIFT                                                           (2U)
#define GMAC_SW_DMA_INTMASK_CLEAR_RESERVED1_MASK                                                            (0xfffffffcU)

#define GMAC_SW_TX_PRI1_RATE_PRIN_SEND_CNT_SHIFT                                                            (0U)
#define GMAC_SW_TX_PRI1_RATE_PRIN_SEND_CNT_MASK                                                             (0x00003fffU)

#define GMAC_SW_TX_PRI1_RATE_RESERVED2_SHIFT                                                                (14U)
#define GMAC_SW_TX_PRI1_RATE_RESERVED2_MASK                                                                 (0x0000c000U)

#define GMAC_SW_TX_PRI1_RATE_PRIN_IDLE_CNT_SHIFT                                                            (16U)
#define GMAC_SW_TX_PRI1_RATE_PRIN_IDLE_CNT_MASK                                                             (0x3fff0000U)

#define GMAC_SW_TX_PRI1_RATE_RESERVED1_SHIFT                                                                (30U)
#define GMAC_SW_TX_PRI1_RATE_RESERVED1_MASK                                                                 (0xc0000000U)

#define GMAC_SW_TX_PRI5_RATE_PRIN_SEND_CNT_SHIFT                                                            (0U)
#define GMAC_SW_TX_PRI5_RATE_PRIN_SEND_CNT_MASK                                                             (0x00003fffU)

#define GMAC_SW_TX_PRI5_RATE_RESERVED2_SHIFT                                                                (14U)
#define GMAC_SW_TX_PRI5_RATE_RESERVED2_MASK                                                                 (0x0000c000U)

#define GMAC_SW_TX_PRI5_RATE_PRIN_IDLE_CNT_SHIFT                                                            (16U)
#define GMAC_SW_TX_PRI5_RATE_PRIN_IDLE_CNT_MASK                                                             (0x3fff0000U)

#define GMAC_SW_TX_PRI5_RATE_RESERVED1_SHIFT                                                                (30U)
#define GMAC_SW_TX_PRI5_RATE_RESERVED1_MASK                                                                 (0xc0000000U)

#define GMAC_SW_RX0_FREEBUFFER_RX_FREEBUFFER_SHIFT                                                          (0U)
#define GMAC_SW_RX0_FREEBUFFER_RX_FREEBUFFER_MASK                                                           (0x0000ffffU)

#define GMAC_SW_RX0_FREEBUFFER_RESERVED1_SHIFT                                                              (16U)
#define GMAC_SW_RX0_FREEBUFFER_RESERVED1_MASK                                                               (0xffff0000U)

#define GMAC_SW_TX_PRI2_RATE_PRIN_SEND_CNT_SHIFT                                                            (0U)
#define GMAC_SW_TX_PRI2_RATE_PRIN_SEND_CNT_MASK                                                             (0x00003fffU)

#define GMAC_SW_TX_PRI2_RATE_RESERVED2_SHIFT                                                                (14U)
#define GMAC_SW_TX_PRI2_RATE_RESERVED2_MASK                                                                 (0x0000c000U)

#define GMAC_SW_TX_PRI2_RATE_PRIN_IDLE_CNT_SHIFT                                                            (16U)
#define GMAC_SW_TX_PRI2_RATE_PRIN_IDLE_CNT_MASK                                                             (0x3fff0000U)

#define GMAC_SW_TX_PRI2_RATE_RESERVED1_SHIFT                                                                (30U)
#define GMAC_SW_TX_PRI2_RATE_RESERVED1_MASK                                                                 (0xc0000000U)

#define GMAC_SW_RX7_FREEBUFFER_RX_FREEBUFFER_SHIFT                                                          (0U)
#define GMAC_SW_RX7_FREEBUFFER_RX_FREEBUFFER_MASK                                                           (0x0000ffffU)

#define GMAC_SW_RX7_FREEBUFFER_RESERVED1_SHIFT                                                              (16U)
#define GMAC_SW_RX7_FREEBUFFER_RESERVED1_MASK                                                               (0xffff0000U)

#define GMAC_SW_RX5_PENDTHRESH_RX_PENDTHRESH_SHIFT                                                          (0U)
#define GMAC_SW_RX5_PENDTHRESH_RX_PENDTHRESH_MASK                                                           (0x000000ffU)

#define GMAC_SW_RX5_PENDTHRESH_RESERVED1_SHIFT                                                              (8U)
#define GMAC_SW_RX5_PENDTHRESH_RESERVED1_MASK                                                               (0xffffff00U)

#define GMAC_SW_RX5_FREEBUFFER_RX_FREEBUFFER_SHIFT                                                          (0U)
#define GMAC_SW_RX5_FREEBUFFER_RX_FREEBUFFER_MASK                                                           (0x0000ffffU)

#define GMAC_SW_RX5_FREEBUFFER_RESERVED1_SHIFT                                                              (16U)
#define GMAC_SW_RX5_FREEBUFFER_RESERVED1_MASK                                                               (0xffff0000U)

#define GMAC_SW_TX_CONTROL_TX_EN_SHIFT                                                                      (0U)
#define GMAC_SW_TX_CONTROL_TX_EN_MASK                                                                       (0x00000001U)

#define GMAC_SW_TX_CONTROL_RESERVED1_SHIFT                                                                  (1U)
#define GMAC_SW_TX_CONTROL_RESERVED1_MASK                                                                   (0xfffffffeU)

#define GMAC_SW_TX_INTSTAT_MASKED_TX0_PEND_SHIFT                                                            (0U)
#define GMAC_SW_TX_INTSTAT_MASKED_TX0_PEND_MASK                                                             (0x00000001U)

#define GMAC_SW_TX_INTSTAT_MASKED_TX1_PEND_SHIFT                                                            (1U)
#define GMAC_SW_TX_INTSTAT_MASKED_TX1_PEND_MASK                                                             (0x00000002U)

#define GMAC_SW_TX_INTSTAT_MASKED_TX2_PEND_SHIFT                                                            (2U)
#define GMAC_SW_TX_INTSTAT_MASKED_TX2_PEND_MASK                                                             (0x00000004U)

#define GMAC_SW_TX_INTSTAT_MASKED_TX3_PEND_SHIFT                                                            (3U)
#define GMAC_SW_TX_INTSTAT_MASKED_TX3_PEND_MASK                                                             (0x00000008U)

#define GMAC_SW_TX_INTSTAT_MASKED_TX4_PEND_SHIFT                                                            (4U)
#define GMAC_SW_TX_INTSTAT_MASKED_TX4_PEND_MASK                                                             (0x00000010U)

#define GMAC_SW_TX_INTSTAT_MASKED_TX5_PEND_SHIFT                                                            (5U)
#define GMAC_SW_TX_INTSTAT_MASKED_TX5_PEND_MASK                                                             (0x00000020U)

#define GMAC_SW_TX_INTSTAT_MASKED_TX6_PEND_SHIFT                                                            (6U)
#define GMAC_SW_TX_INTSTAT_MASKED_TX6_PEND_MASK                                                             (0x00000040U)

#define GMAC_SW_TX_INTSTAT_MASKED_TX7_PEND_SHIFT                                                            (7U)
#define GMAC_SW_TX_INTSTAT_MASKED_TX7_PEND_MASK                                                             (0x00000080U)

#define GMAC_SW_TX_INTSTAT_MASKED_RESERVED1_SHIFT                                                           (8U)
#define GMAC_SW_TX_INTSTAT_MASKED_RESERVED1_MASK                                                            (0xffffff00U)

#define GMAC_SW_RX_INTSTAT_RAW_RX0_PEND_SHIFT                                                               (0U)
#define GMAC_SW_RX_INTSTAT_RAW_RX0_PEND_MASK                                                                (0x00000001U)

#define GMAC_SW_RX_INTSTAT_RAW_RX1_PEND_SHIFT                                                               (1U)
#define GMAC_SW_RX_INTSTAT_RAW_RX1_PEND_MASK                                                                (0x00000002U)

#define GMAC_SW_RX_INTSTAT_RAW_RX2_PEND_SHIFT                                                               (2U)
#define GMAC_SW_RX_INTSTAT_RAW_RX2_PEND_MASK                                                                (0x00000004U)

#define GMAC_SW_RX_INTSTAT_RAW_RX3_PEND_SHIFT                                                               (3U)
#define GMAC_SW_RX_INTSTAT_RAW_RX3_PEND_MASK                                                                (0x00000008U)

#define GMAC_SW_RX_INTSTAT_RAW_RX4_PEND_SHIFT                                                               (4U)
#define GMAC_SW_RX_INTSTAT_RAW_RX4_PEND_MASK                                                                (0x00000010U)

#define GMAC_SW_RX_INTSTAT_RAW_RX5_PEND_SHIFT                                                               (5U)
#define GMAC_SW_RX_INTSTAT_RAW_RX5_PEND_MASK                                                                (0x00000020U)

#define GMAC_SW_RX_INTSTAT_RAW_RX6_PEND_SHIFT                                                               (6U)
#define GMAC_SW_RX_INTSTAT_RAW_RX6_PEND_MASK                                                                (0x00000040U)

#define GMAC_SW_RX_INTSTAT_RAW_RX7_PEND_SHIFT                                                               (7U)
#define GMAC_SW_RX_INTSTAT_RAW_RX7_PEND_MASK                                                                (0x00000080U)

#define GMAC_SW_RX_INTSTAT_RAW_RX0_THRESH_PEND_SHIFT                                                        (8U)
#define GMAC_SW_RX_INTSTAT_RAW_RX0_THRESH_PEND_MASK                                                         (0x00000100U)

#define GMAC_SW_RX_INTSTAT_RAW_RX1_THRESH_PEND_SHIFT                                                        (9U)
#define GMAC_SW_RX_INTSTAT_RAW_RX1_THRESH_PEND_MASK                                                         (0x00000200U)

#define GMAC_SW_RX_INTSTAT_RAW_RX2_THRESH_PEND_SHIFT                                                        (10U)
#define GMAC_SW_RX_INTSTAT_RAW_RX2_THRESH_PEND_MASK                                                         (0x00000400U)

#define GMAC_SW_RX_INTSTAT_RAW_RX3_THRESH_PEND_SHIFT                                                        (11U)
#define GMAC_SW_RX_INTSTAT_RAW_RX3_THRESH_PEND_MASK                                                         (0x00000800U)

#define GMAC_SW_RX_INTSTAT_RAW_RX4_THRESH_PEND_SHIFT                                                        (12U)
#define GMAC_SW_RX_INTSTAT_RAW_RX4_THRESH_PEND_MASK                                                         (0x00001000U)

#define GMAC_SW_RX_INTSTAT_RAW_RX5_THRESH_PEND_SHIFT                                                        (13U)
#define GMAC_SW_RX_INTSTAT_RAW_RX5_THRESH_PEND_MASK                                                         (0x00002000U)

#define GMAC_SW_RX_INTSTAT_RAW_RX6_THRESH_PEND_SHIFT                                                        (14U)
#define GMAC_SW_RX_INTSTAT_RAW_RX6_THRESH_PEND_MASK                                                         (0x00004000U)

#define GMAC_SW_RX_INTSTAT_RAW_RX7_THRESH_PEND_SHIFT                                                        (15U)
#define GMAC_SW_RX_INTSTAT_RAW_RX7_THRESH_PEND_MASK                                                         (0x00008000U)

#define GMAC_SW_RX_INTSTAT_RAW_RESERVED1_SHIFT                                                              (16U)
#define GMAC_SW_RX_INTSTAT_RAW_RESERVED1_MASK                                                               (0xffff0000U)

#define GMAC_SW_RX1_FREEBUFFER_RX_FREEBUFFER_SHIFT                                                          (0U)
#define GMAC_SW_RX1_FREEBUFFER_RX_FREEBUFFER_MASK                                                           (0x0000ffffU)

#define GMAC_SW_RX1_FREEBUFFER_RESERVED1_SHIFT                                                              (16U)
#define GMAC_SW_RX1_FREEBUFFER_RESERVED1_MASK                                                               (0xffff0000U)

#define GMAC_SW_RX6_PENDTHRESH_RX_PENDTHRESH_SHIFT                                                          (0U)
#define GMAC_SW_RX6_PENDTHRESH_RX_PENDTHRESH_MASK                                                           (0x000000ffU)

#define GMAC_SW_RX6_PENDTHRESH_RESERVED1_SHIFT                                                              (8U)
#define GMAC_SW_RX6_PENDTHRESH_RESERVED1_MASK                                                               (0xffffff00U)

#define GMAC_SW_RX_CONTROL_RX_EN_SHIFT                                                                      (0U)
#define GMAC_SW_RX_CONTROL_RX_EN_MASK                                                                       (0x00000001U)

#define GMAC_SW_RX_CONTROL_RESERVED1_SHIFT                                                                  (1U)
#define GMAC_SW_RX_CONTROL_RESERVED1_MASK                                                                   (0xfffffffeU)

#define GMAC_SW_RX1_PENDTHRESH_RX_PENDTHRESH_SHIFT                                                          (0U)
#define GMAC_SW_RX1_PENDTHRESH_RX_PENDTHRESH_MASK                                                           (0x000000ffU)

#define GMAC_SW_RX1_PENDTHRESH_RESERVED1_SHIFT                                                              (8U)
#define GMAC_SW_RX1_PENDTHRESH_RESERVED1_MASK                                                               (0xffffff00U)

#define GMAC_SW_RX2_PENDTHRESH_RX_PENDTHRESH_SHIFT                                                          (0U)
#define GMAC_SW_RX2_PENDTHRESH_RX_PENDTHRESH_MASK                                                           (0x000000ffU)

#define GMAC_SW_RX2_PENDTHRESH_RESERVED1_SHIFT                                                              (8U)
#define GMAC_SW_RX2_PENDTHRESH_RESERVED1_MASK                                                               (0xffffff00U)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_GMACSW_CPDMA_H_ */
