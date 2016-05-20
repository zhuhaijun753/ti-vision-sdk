/******************************************************************************
*
* hw_uart.h - register-level header file for UART
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
#ifndef HW_UART_H_
#define HW_UART_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions 
****************************************************************************************************/
#define UART_RHR                                                                                            (0x0U)
#define UART_THR                                                                                            (0x0U)
#define UART_IER                                                                                            (0x4U)
#define UART_IIR                                                                                            (0x8U)
#define UART_FCR                                                                                            (0x8U)
#define UART_LCR                                                                                            (0xcU)
#define UART_MCR                                                                                            (0x10U)
#define UART_LSR                                                                                            (0x14U)
#define UART_MSR                                                                                            (0x18U)
#define UART_SPR                                                                                            (0x1cU)
#define UART_MDR1                                                                                           (0x20U)
#define UART_MDR2                                                                                           (0x24U)
#define UART_SFLSR                                                                                          (0x28U)
#define UART_TXFLL                                                                                          (0x28U)
#define UART_RESUME                                                                                         (0x2cU)
#define UART_TXFLH                                                                                          (0x2cU)
#define UART_SFREGL                                                                                         (0x30U)
#define UART_RXFLL                                                                                          (0x30U)
#define UART_SFREGH                                                                                         (0x34U)
#define UART_RXFLH                                                                                          (0x34U)
#define UART_BLR                                                                                            (0x38U)
#define UART_ACREG                                                                                          (0x3cU)
#define UART_SCR                                                                                            (0x40U)
#define UART_SSR                                                                                            (0x44U)
#define UART_EBLR                                                                                           (0x48U)
#define UART_MVR                                                                                            (0x50U)
#define UART_SYSC                                                                                           (0x54U)
#define UART_SYSS                                                                                           (0x58U)
#define UART_WER                                                                                            (0x5cU)
#define UART_CFPS                                                                                           (0x60U)
#define UART_RXFIFO_LVL                                                                                     (0x64U)
#define UART_TXFIFO_LVL                                                                                     (0x68U)
#define UART_IER2                                                                                           (0x6cU)
#define UART_ISR2                                                                                           (0x70U)
#define UART_FREQ_SEL                                                                                       (0x74U)
#define UART_ABAUD_1ST_CHAR                                                                                 (0x78U)
#define UART_BAUD_2ND_CHAR                                                                                  (0x7cU)
#define UART_MDR3                                                                                           (0x80U)
#define UART_TX_DMA_THRESHOLD                                                                               (0x84U)
#define UART_DLL                                                                                            (0x0U)
#define UART_IER_IRDA                                                                                       (0x4U)
#define UART_IER_CIR                                                                                        (0x4U)
#define UART_DLH                                                                                            (0x4U)
#define UART_IIR_IRDA                                                                                       (0x8U)
#define UART_IIR_CIR                                                                                        (0x8U)
#define UART_EFR                                                                                            (0x8U)
#define UART_XON1_ADDR1                                                                                     (0x10U)
#define UART_LSR_IRDA                                                                                       (0x14U)
#define UART_LSR_CIR                                                                                        (0x14U)
#define UART_XON2_ADDR2                                                                                     (0x14U)
#define UART_XOFF1                                                                                          (0x18U)
#define UART_TCR                                                                                            (0x18U)
#define UART_XOFF2                                                                                          (0x1cU)
#define UART_TLR                                                                                            (0x1cU)
#define UART_UASR                                                                                           (0x38U)

/****************************************************************************************************
* Field Definition Macros 
****************************************************************************************************/

#define UART_RHR_RHR_SHIFT                                                                                  (0U)
#define UART_RHR_RHR_MASK                                                                                   (0x000000ffU)

#define UART_RHR_RESERVED_24_SHIFT                                                                          (8U)
#define UART_RHR_RESERVED_24_MASK                                                                           (0xffffff00U)

#define UART_THR_THR_SHIFT                                                                                  (0U)
#define UART_THR_THR_MASK                                                                                   (0x000000ffU)

#define UART_THR_RESERVED_24_SHIFT                                                                          (8U)
#define UART_THR_RESERVED_24_MASK                                                                           (0xffffff00U)

#define UART_IER_RHR_IT_SHIFT                                                                               (0U)
#define UART_IER_RHR_IT_MASK                                                                                (0x00000001U)
#define UART_IER_RHR_IT_RHR_IT_VALUE_1                                                                       (1U)
#define UART_IER_RHR_IT_RHR_IT_VALUE_0                                                                       (0U)

#define UART_IER_THR_IT_SHIFT                                                                               (1U)
#define UART_IER_THR_IT_MASK                                                                                (0x00000002U)
#define UART_IER_THR_IT_THR_IT_VALUE_1                                                                       (1U)
#define UART_IER_THR_IT_THR_IT_VALUE_0                                                                       (0U)

#define UART_IER_LINE_STS_IT_SHIFT                                                                          (2U)
#define UART_IER_LINE_STS_IT_MASK                                                                           (0x00000004U)
#define UART_IER_LINE_STS_IT_LINE_STS_IT_U_VALUE_1                                                           (1U)
#define UART_IER_LINE_STS_IT_LINE_STS_IT_U_VALUE_0                                                           (0U)

#define UART_IER_MODEM_STS_IT_SHIFT                                                                         (3U)
#define UART_IER_MODEM_STS_IT_MASK                                                                          (0x00000008U)
#define UART_IER_MODEM_STS_IT_MODEM_STS_IT_VALUE_1                                                           (1U)
#define UART_IER_MODEM_STS_IT_MODEM_STS_IT_VALUE_0                                                           (0U)

#define UART_IER_SLEEP_MODE_SHIFT                                                                           (4U)
#define UART_IER_SLEEP_MODE_MASK                                                                            (0x00000010U)
#define UART_IER_SLEEP_MODE_SLEEP_MODE_VALUE_1                                                               (1U)
#define UART_IER_SLEEP_MODE_SLEEP_MODE_VALUE_0                                                               (0U)

#define UART_IER_XOFF_IT_SHIFT                                                                              (5U)
#define UART_IER_XOFF_IT_MASK                                                                               (0x00000020U)
#define UART_IER_XOFF_IT_XOFF_IT_VALUE_1                                                                     (1U)
#define UART_IER_XOFF_IT_XOFF_IT_VALUE_0                                                                     (0U)

#define UART_IER_RTS_IT_SHIFT                                                                               (6U)
#define UART_IER_RTS_IT_MASK                                                                                (0x00000040U)
#define UART_IER_RTS_IT_RTS_IT_VALUE_1                                                                       (1U)
#define UART_IER_RTS_IT_RTS_IT_VALUE_0                                                                       (0U)

#define UART_IER_CTS_IT_SHIFT                                                                               (7U)
#define UART_IER_CTS_IT_MASK                                                                                (0x00000080U)
#define UART_IER_CTS_IT_CTS_IT_VALUE_1                                                                       (1U)
#define UART_IER_CTS_IT_CTS_IT_VALUE_0                                                                       (0U)

#define UART_IER_RESERVED_SHIFT                                                                             (8U)
#define UART_IER_RESERVED_MASK                                                                              (0xffffff00U)

#define UART_IIR_IT_PENDING_SHIFT                                                                           (0U)
#define UART_IIR_IT_PENDING_MASK                                                                            (0x00000001U)
#define UART_IIR_IT_PENDING_IT_PENDING_VALUE_0                                                               (0U)
#define UART_IIR_IT_PENDING_IT_PENDING_VALUE_1                                                               (1U)

#define UART_IIR_IT_TYPE_SHIFT                                                                              (1U)
#define UART_IIR_IT_TYPE_MASK                                                                               (0x0000003eU)
#define UART_IIR_IT_TYPE_IT_TYPE_VALUE_8                                                                     (8U)
#define UART_IIR_IT_TYPE_IT_TYPE_VALUE_6                                                                     (6U)
#define UART_IIR_IT_TYPE_IT_TYPE_VALUE_3                                                                     (3U)
#define UART_IIR_IT_TYPE_IT_TYPE_VALUE_10                                                                    (16U)
#define UART_IIR_IT_TYPE_IT_TYPE_VALUE_2                                                                     (2U)
#define UART_IIR_IT_TYPE_IT_TYPE_VALUE_1                                                                     (1U)
#define UART_IIR_IT_TYPE_IT_TYPE_VALUE_0                                                                     (0U)

#define UART_IIR_FCR_MIRROR_SHIFT                                                                           (6U)
#define UART_IIR_FCR_MIRROR_MASK                                                                            (0x000000c0U)

#define UART_IIR_RESERVED_24_SHIFT                                                                          (8U)
#define UART_IIR_RESERVED_24_MASK                                                                           (0xffffff00U)

#define UART_FCR_FIFO_EN_SHIFT                                                                              (0U)
#define UART_FCR_FIFO_EN_MASK                                                                               (0x00000001U)
#define UART_FCR_FIFO_EN_FIFO_EN_VALUE_1                                                                     (1U)
#define UART_FCR_FIFO_EN_FIFO_EN_VALUE_0                                                                     (0U)

#define UART_FCR_RX_FIFO_CLEAR_SHIFT                                                                        (1U)
#define UART_FCR_RX_FIFO_CLEAR_MASK                                                                         (0x00000002U)
#define UART_FCR_RX_FIFO_CLEAR_RX_FIFO_CLEAR_VALUE_1                                                         (1U)
#define UART_FCR_RX_FIFO_CLEAR_RX_FIFO_CLEAR_VALUE_0                                                         (0U)

#define UART_FCR_TX_FIFO_CLEAR_SHIFT                                                                        (2U)
#define UART_FCR_TX_FIFO_CLEAR_MASK                                                                         (0x00000004U)
#define UART_FCR_TX_FIFO_CLEAR_TX_FIFO_CLEAR_VALUE_1                                                         (1U)
#define UART_FCR_TX_FIFO_CLEAR_TX_FIFO_CLEAR_VALUE_0                                                         (0U)

#define UART_FCR_DMA_MODE_SHIFT                                                                             (3U)
#define UART_FCR_DMA_MODE_MASK                                                                              (0x00000008U)
#define UART_FCR_DMA_MODE_DMA_MODE_VALUE_1                                                                   (1U)
#define UART_FCR_DMA_MODE_DMA_MODE_VALUE_0                                                                   (0U)

#define UART_FCR_TX_FIFO_TRIG_SHIFT                                                                         (4U)
#define UART_FCR_TX_FIFO_TRIG_MASK                                                                          (0x00000030U)

#define UART_FCR_RX_FIFO_TRIG_SHIFT                                                                         (6U)
#define UART_FCR_RX_FIFO_TRIG_MASK                                                                          (0x000000c0U)

#define UART_FCR_RESERVED_24_SHIFT                                                                          (8U)
#define UART_FCR_RESERVED_24_MASK                                                                           (0xffffff00U)

#define UART_LCR_CHAR_LENGTH_SHIFT                                                                          (0U)
#define UART_LCR_CHAR_LENGTH_MASK                                                                           (0x00000003U)
#define UART_LCR_CHAR_LENGTH_CHAR_LENGTH_VALUE_3                                                             (uint32_t)(3U)
#define UART_LCR_CHAR_LENGTH_CHAR_LENGTH_VALUE_2                                                             (uint32_t)(2U)
#define UART_LCR_CHAR_LENGTH_CHAR_LENGTH_VALUE_1                                                             (uint32_t)(1U)
#define UART_LCR_CHAR_LENGTH_CHAR_LENGTH_VALUE_0                                                             (uint32_t)(0U)

#define UART_LCR_NB_STOP_SHIFT                                                                              (2U)
#define UART_LCR_NB_STOP_MASK                                                                               (0x00000004U)
#define UART_LCR_NB_STOP_NB_STOP_VALUE_1                                                                     (uint32_t)(1U)
#define UART_LCR_NB_STOP_NB_STOP_VALUE_0                                                                     (uint32_t)(0U)

#define UART_LCR_PARITY_EN_SHIFT                                                                            (3U)
#define UART_LCR_PARITY_EN_MASK                                                                             (0x00000008U)
#define UART_LCR_PARITY_EN_PARITY_EN_VALUE_1                                                                 (uint32_t)(1U)
#define UART_LCR_PARITY_EN_PARITY_EN_VALUE_0                                                                 (uint32_t)(0U)

#define UART_LCR_PARITY_TYPE1_SHIFT                                                                         (4U)
#define UART_LCR_PARITY_TYPE1_MASK                                                                          (0x00000010U)
#define UART_LCR_PARITY_TYPE1_PARITY_TYPE1_VALUE_1                                                           (1U)
#define UART_LCR_PARITY_TYPE1_PARITY_TYPE1_VALUE_0                                                           (0U)

#define UART_LCR_PARITY_TYPE2_SHIFT                                                                         (5U)
#define UART_LCR_PARITY_TYPE2_MASK                                                                          (0x00000020U)

#define UART_LCR_BREAK_EN_SHIFT                                                                             (6U)
#define UART_LCR_BREAK_EN_MASK                                                                              (0x00000040U)
#define UART_LCR_BREAK_EN_BREAK_EN_VALUE_1                                                                   (uint32_t)(1U)
#define UART_LCR_BREAK_EN_BREAK_EN_VALUE_0                                                                   (uint32_t)(0U)

#define UART_LCR_DIV_EN_SHIFT                                                                               (7U)
#define UART_LCR_DIV_EN_MASK                                                                                (0x00000080U)
#define UART_LCR_DIV_EN_DIV_EN_VALUE_0                                                                       (0U)
#define UART_LCR_DIV_EN_DIV_EN_VALUE_1                                                                       (1U)

#define UART_LCR_RESERVED_24_SHIFT                                                                          (8U)
#define UART_LCR_RESERVED_24_MASK                                                                           (0xffffff00U)

#define UART_MCR_LOOPBACK_EN_SHIFT                                                                          (4U)
#define UART_MCR_LOOPBACK_EN_MASK                                                                           (0x00000010U)
#define UART_MCR_LOOPBACK_EN_LOOPBACK_EN_VALUE_1                                                             (1U)
#define UART_MCR_LOOPBACK_EN_LOOPBACK_EN_VALUE_0                                                             (0U)

#define UART_MCR_XON_EN_SHIFT                                                                               (5U)
#define UART_MCR_XON_EN_MASK                                                                                (0x00000020U)
#define UART_MCR_XON_EN_XON_EN_VALUE_1                                                                       (1U)
#define UART_MCR_XON_EN_XON_EN_VALUE_0                                                                       (0U)

#define UART_MCR_TCR_TLR_SHIFT                                                                              (6U)
#define UART_MCR_TCR_TLR_MASK                                                                               (0x00000040U)
#define UART_MCR_TCR_TLR_TCR_TLR_VALUE_1                                                                     (1U)
#define UART_MCR_TCR_TLR_TCR_TLR_VALUE_0                                                                     (0U)

#define UART_MCR_RESERVED_SHIFT                                                                             (7U)
#define UART_MCR_RESERVED_MASK                                                                              (0x00000080U)

#define UART_MCR_DTR_SHIFT                                                                                  (0U)
#define UART_MCR_DTR_MASK                                                                                   (0x00000001U)
#define UART_MCR_DTR_DTR_VALUE_1                                                                             (1U)
#define UART_MCR_DTR_DTR_VALUE_0                                                                             (0U)

#define UART_MCR_RTS_SHIFT                                                                                  (1U)
#define UART_MCR_RTS_MASK                                                                                   (0x00000002U)
#define UART_MCR_RTS_RTS_VALUE_1                                                                             (1U)
#define UART_MCR_RTS_RTS_VALUE_0                                                                             (0U)

#define UART_MCR_RI_STS_CH_SHIFT                                                                            (2U)
#define UART_MCR_RI_STS_CH_MASK                                                                             (0x00000004U)
#define UART_MCR_RI_STS_CH_RI_STS_CH_VALUE_1                                                                 (1U)
#define UART_MCR_RI_STS_CH_RI_STS_CH_VALUE_0                                                                 (0U)

#define UART_MCR_CD_STS_CH_SHIFT                                                                            (3U)
#define UART_MCR_CD_STS_CH_MASK                                                                             (0x00000008U)
#define UART_MCR_CD_STS_CH_CD_STS_CH_VALUE_1                                                                 (1U)
#define UART_MCR_CD_STS_CH_CD_STS_CH_VALUE_0                                                                 (0U)

#define UART_MCR_RESERVED_24_SHIFT                                                                          (8U)
#define UART_MCR_RESERVED_24_MASK                                                                           (0xffffff00U)

#define UART_LSR_RX_FIFO_E_SHIFT                                                                            (0U)
#define UART_LSR_RX_FIFO_E_MASK                                                                             (0x00000001U)
#define UART_LSR_RX_FIFO_E_RX_FIFO_E_VALUE_1                                                                 (1U)
#define UART_LSR_RX_FIFO_E_RX_FIFO_E_VALUE_0                                                                 (0U)

#define UART_LSR_RX_OE_SHIFT                                                                                (1U)
#define UART_LSR_RX_OE_MASK                                                                                 (0x00000002U)
#define UART_LSR_RX_OE_RX_OE_VALUE_1                                                                         (1U)
#define UART_LSR_RX_OE_RX_OE_VALUE_0                                                                         (0U)

#define UART_LSR_RX_PE_SHIFT                                                                                (2U)
#define UART_LSR_RX_PE_MASK                                                                                 (0x00000004U)
#define UART_LSR_RX_PE_RX_PE_VALUE_1                                                                         (1U)
#define UART_LSR_RX_PE_RX_PE_VALUE_0                                                                         (0U)

#define UART_LSR_RX_FE_SHIFT                                                                                (3U)
#define UART_LSR_RX_FE_MASK                                                                                 (0x00000008U)
#define UART_LSR_RX_FE_RX_FE_VALUE_1                                                                         (1U)
#define UART_LSR_RX_FE_RX_FE_VALUE_0                                                                         (0U)

#define UART_LSR_RX_BI_SHIFT                                                                                (4U)
#define UART_LSR_RX_BI_MASK                                                                                 (0x00000010U)
#define UART_LSR_RX_BI_RX_BI_VALUE_1                                                                         (1U)
#define UART_LSR_RX_BI_RX_BI_VALUE_0                                                                         (0U)

#define UART_LSR_TX_FIFO_E_SHIFT                                                                            (5U)
#define UART_LSR_TX_FIFO_E_MASK                                                                             (0x00000020U)
#define UART_LSR_TX_FIFO_E_TX_FIFO_E_VALUE_1                                                                 (1U)
#define UART_LSR_TX_FIFO_E_TX_FIFO_E_VALUE_0                                                                 (0U)

#define UART_LSR_TX_SR_E_SHIFT                                                                              (6U)
#define UART_LSR_TX_SR_E_MASK                                                                               (0x00000040U)
#define UART_LSR_TX_SR_E_TX_SR_E_VALUE_1                                                                     (1U)
#define UART_LSR_TX_SR_E_TX_SR_E_VALUE_0                                                                     (0U)

#define UART_LSR_RX_FIFO_STS_SHIFT                                                                          (7U)
#define UART_LSR_RX_FIFO_STS_MASK                                                                           (0x00000080U)
#define UART_LSR_RX_FIFO_STS_RX_FIFO_STS_VALUE_1                                                             (1U)
#define UART_LSR_RX_FIFO_STS_RX_FIFO_STS_VALUE_0                                                             (0U)

#define UART_LSR_RESERVED_24_SHIFT                                                                          (8U)
#define UART_LSR_RESERVED_24_MASK                                                                           (0xffffff00U)

#define UART_MSR_CTS_STS_SHIFT                                                                              (0U)
#define UART_MSR_CTS_STS_MASK                                                                               (0x00000001U)
#define UART_MSR_CTS_STS_CTS_STS_VALUE_1                                                                     (1U)

#define UART_MSR_DSR_STS_SHIFT                                                                              (1U)
#define UART_MSR_DSR_STS_MASK                                                                               (0x00000002U)
#define UART_MSR_DSR_STS_DSR_STS_VALUE_1                                                                     (1U)

#define UART_MSR_RI_STS_SHIFT                                                                               (2U)
#define UART_MSR_RI_STS_MASK                                                                                (0x00000004U)

#define UART_MSR_DCD_STS_SHIFT                                                                              (3U)
#define UART_MSR_DCD_STS_MASK                                                                               (0x00000008U)

#define UART_MSR_NCTS_STS_SHIFT                                                                             (4U)
#define UART_MSR_NCTS_STS_MASK                                                                              (0x00000010U)

#define UART_MSR_NDSR_STS_SHIFT                                                                             (5U)
#define UART_MSR_NDSR_STS_MASK                                                                              (0x00000020U)

#define UART_MSR_NRI_STS_SHIFT                                                                              (6U)
#define UART_MSR_NRI_STS_MASK                                                                               (0x00000040U)

#define UART_MSR_NCD_STS_SHIFT                                                                              (7U)
#define UART_MSR_NCD_STS_MASK                                                                               (0x00000080U)

#define UART_MSR_RESERVED_24_SHIFT                                                                          (8U)
#define UART_MSR_RESERVED_24_MASK                                                                           (0xffffff00U)

#define UART_SPR_SPR_WORD_SHIFT                                                                             (0U)
#define UART_SPR_SPR_WORD_MASK                                                                              (0x000000ffU)

#define UART_SPR_RESERVED_24_SHIFT                                                                          (8U)
#define UART_SPR_RESERVED_24_MASK                                                                           (0xffffff00U)

#define UART_MDR1_MODE_SELECT_SHIFT                                                                         (0U)
#define UART_MDR1_MODE_SELECT_MASK                                                                          (0x00000007U)
#define UART_MDR1_MODE_SELECT_MODE_SELECT_VALUE_7                                                            (7U)
#define UART_MDR1_MODE_SELECT_MODE_SELECT_VALUE_6                                                            (6U)
#define UART_MDR1_MODE_SELECT_MODE_SELECT_VALUE_5                                                            (5U)
#define UART_MDR1_MODE_SELECT_MODE_SELECT_VALUE_4                                                            (4U)
#define UART_MDR1_MODE_SELECT_MODE_SELECT_VALUE_3                                                            (3U)
#define UART_MDR1_MODE_SELECT_MODE_SELECT_VALUE_2                                                            (2U)
#define UART_MDR1_MODE_SELECT_MODE_SELECT_VALUE_1                                                            (1U)
#define UART_MDR1_MODE_SELECT_MODE_SELECT_VALUE_0                                                            (0U)

#define UART_MDR1_IR_SLEEP_SHIFT                                                                            (3U)
#define UART_MDR1_IR_SLEEP_MASK                                                                             (0x00000008U)
#define UART_MDR1_IR_SLEEP_IR_SLEEP_VALUE_1                                                                  (1U)
#define UART_MDR1_IR_SLEEP_IR_SLEEP_VALUE_0                                                                  (0U)

#define UART_MDR1_SET_TXIR_SHIFT                                                                            (4U)
#define UART_MDR1_SET_TXIR_MASK                                                                             (0x00000010U)
#define UART_MDR1_SET_TXIR_SET_TXIR_VALUE_1                                                                  (1U)
#define UART_MDR1_SET_TXIR_SET_TXIR_VALUE_0                                                                  (0U)

#define UART_MDR1_SCT_SHIFT                                                                                 (5U)
#define UART_MDR1_SCT_MASK                                                                                  (0x00000020U)
#define UART_MDR1_SCT_SCT_VALUE_1                                                                            (1U)
#define UART_MDR1_SCT_SCT_VALUE_0                                                                            (0U)

#define UART_MDR1_SIP_MODE_SHIFT                                                                            (6U)
#define UART_MDR1_SIP_MODE_MASK                                                                             (0x00000040U)
#define UART_MDR1_SIP_MODE_SIP_MODE_VALUE_1                                                                  (1U)
#define UART_MDR1_SIP_MODE_SIP_MODE_VALUE_0                                                                  (0U)

#define UART_MDR1_FRAME_END_MODE_SHIFT                                                                      (7U)
#define UART_MDR1_FRAME_END_MODE_MASK                                                                       (0x00000080U)
#define UART_MDR1_FRAME_END_MODE_FRAME_END_MODE_VALUE_1                                                      (1U)
#define UART_MDR1_FRAME_END_MODE_FRAME_END_MODE_VALUE_0                                                      (0U)

#define UART_MDR1_RESERVED_24_SHIFT                                                                         (8U)
#define UART_MDR1_RESERVED_24_MASK                                                                          (0xffffff00U)

#define UART_MDR2_IRTX_UNDERRUN_SHIFT                                                                       (0U)
#define UART_MDR2_IRTX_UNDERRUN_MASK                                                                        (0x00000001U)
#define UART_MDR2_IRTX_UNDERRUN_IRTX_UNDERRUN_VALUE_1                                                        (1U)
#define UART_MDR2_IRTX_UNDERRUN_IRTX_UNDERRUN_VALUE_0                                                        (0U)

#define UART_MDR2_STS_FIFO_TRIG_SHIFT                                                                       (1U)
#define UART_MDR2_STS_FIFO_TRIG_MASK                                                                        (0x00000006U)
#define UART_MDR2_STS_FIFO_TRIG_STS_FIFO_TRIG_VALUE_3                                                        (3U)
#define UART_MDR2_STS_FIFO_TRIG_STS_FIFO_TRIG_VALUE_2                                                        (2U)
#define UART_MDR2_STS_FIFO_TRIG_STS_FIFO_TRIG_VALUE_1                                                        (1U)
#define UART_MDR2_STS_FIFO_TRIG_STS_FIFO_TRIG_VALUE_0                                                        (0U)

#define UART_MDR2_UART_PULSE_SHIFT                                                                          (3U)
#define UART_MDR2_UART_PULSE_MASK                                                                           (0x00000008U)
#define UART_MDR2_UART_PULSE_UART_PULSE_VALUE_1                                                              (1U)
#define UART_MDR2_UART_PULSE_UART_PULSE_VALUE_0                                                              (0U)

#define UART_MDR2_CIR_PULSE_MODE_SHIFT                                                                      (4U)
#define UART_MDR2_CIR_PULSE_MODE_MASK                                                                       (0x00000030U)
#define UART_MDR2_CIR_PULSE_MODE_CIR_PULSE_MODE_VALUE_3                                                      (3U)
#define UART_MDR2_CIR_PULSE_MODE_CIR_PULSE_MODE_VALUE_2                                                      (2U)
#define UART_MDR2_CIR_PULSE_MODE_CIR_PULSE_MODE_VALUE_1                                                      (1U)
#define UART_MDR2_CIR_PULSE_MODE_CIR_PULSE_MODE_VALUE_0                                                      (0U)

#define UART_MDR2_IRRXINVERT_SHIFT                                                                          (6U)
#define UART_MDR2_IRRXINVERT_MASK                                                                           (0x00000040U)
#define UART_MDR2_IRRXINVERT_IRRXINVERT_VALUE_1                                                              (1U)
#define UART_MDR2_IRRXINVERT_IRRXINVERT_VALUE_0                                                              (0U)

#define UART_MDR2_SET_TXIR_ALT_SHIFT                                                                        (7U)
#define UART_MDR2_SET_TXIR_ALT_MASK                                                                         (0x00000080U)
#define UART_MDR2_SET_TXIR_ALT_SET_TXIR_ALT_VALUE_0                                                          (0U)
#define UART_MDR2_SET_TXIR_ALT_SET_TXIR_ALT_VALUE_1                                                          (1U)

#define UART_MDR2_RESERVED_24_SHIFT                                                                         (8U)
#define UART_MDR2_RESERVED_24_MASK                                                                          (0xffffff00U)

#define UART_SFLSR_RESERVED0_SHIFT                                                                          (0U)
#define UART_SFLSR_RESERVED0_MASK                                                                           (0x00000001U)

#define UART_SFLSR_CRC_ERROR_SHIFT                                                                          (1U)
#define UART_SFLSR_CRC_ERROR_MASK                                                                           (0x00000002U)
#define UART_SFLSR_CRC_ERROR_CRC_ERROR_VALUE_1                                                               (1U)

#define UART_SFLSR_ABORT_DETECT_SHIFT                                                                       (2U)
#define UART_SFLSR_ABORT_DETECT_MASK                                                                        (0x00000004U)
#define UART_SFLSR_ABORT_DETECT_ABORT_DETECT_VALUE_1                                                         (1U)

#define UART_SFLSR_FRAME_TOO_LONG_ERROR_SHIFT                                                               (3U)
#define UART_SFLSR_FRAME_TOO_LONG_ERROR_MASK                                                                (0x00000008U)
#define UART_SFLSR_FRAME_TOO_LONG_ERROR_FRAME_TOO_LONG_ERROR_VALUE_1                                         (1U)

#define UART_SFLSR_OE_ERROR_SHIFT                                                                           (4U)
#define UART_SFLSR_OE_ERROR_MASK                                                                            (0x00000010U)
#define UART_SFLSR_OE_ERROR_OE_ERROR_VALUE_1                                                                 (1U)

#define UART_SFLSR_RESERVED5_SHIFT                                                                          (5U)
#define UART_SFLSR_RESERVED5_MASK                                                                           (0x000000e0U)

#define UART_SFLSR_RESERVED_24_SHIFT                                                                        (8U)
#define UART_SFLSR_RESERVED_24_MASK                                                                         (0xffffff00U)

#define UART_TXFLL_TXFLL_SHIFT                                                                              (0U)
#define UART_TXFLL_TXFLL_MASK                                                                               (0x000000ffU)

#define UART_TXFLL_RESERVED_24_SHIFT                                                                        (8U)
#define UART_TXFLL_RESERVED_24_MASK                                                                         (0xffffff00U)

#define UART_RESUME_RESUME_SHIFT                                                                            (0U)
#define UART_RESUME_RESUME_MASK                                                                             (0x000000ffU)

#define UART_RESUME_RESERVED_24_SHIFT                                                                       (8U)
#define UART_RESUME_RESERVED_24_MASK                                                                        (0xffffff00U)

#define UART_TXFLH_TXFLH_SHIFT                                                                              (0U)
#define UART_TXFLH_TXFLH_MASK                                                                               (0x0000001fU)

#define UART_TXFLH_RESERVED_SHIFT                                                                           (5U)
#define UART_TXFLH_RESERVED_MASK                                                                            (0x000000e0U)

#define UART_TXFLH_RESERVED_24_SHIFT                                                                        (8U)
#define UART_TXFLH_RESERVED_24_MASK                                                                         (0xffffff00U)

#define UART_SFREGL_SFREGL_SHIFT                                                                            (0U)
#define UART_SFREGL_SFREGL_MASK                                                                             (0x000000ffU)

#define UART_SFREGL_RESERVED_24_SHIFT                                                                       (8U)
#define UART_SFREGL_RESERVED_24_MASK                                                                        (0xffffff00U)

#define UART_RXFLL_RXFLL_SHIFT                                                                              (0U)
#define UART_RXFLL_RXFLL_MASK                                                                               (0x000000ffU)

#define UART_RXFLL_RESERVED_24_SHIFT                                                                        (8U)
#define UART_RXFLL_RESERVED_24_MASK                                                                         (0xffffff00U)

#define UART_SFREGH_SFREGH_SHIFT                                                                            (0U)
#define UART_SFREGH_SFREGH_MASK                                                                             (0x0000000fU)

#define UART_SFREGH_RESERVED_SHIFT                                                                          (4U)
#define UART_SFREGH_RESERVED_MASK                                                                           (0x000000f0U)

#define UART_SFREGH_RESERVED_24_SHIFT                                                                       (8U)
#define UART_SFREGH_RESERVED_24_MASK                                                                        (0xffffff00U)

#define UART_RXFLH_RXFLH_SHIFT                                                                              (0U)
#define UART_RXFLH_RXFLH_MASK                                                                               (0x0000000fU)

#define UART_RXFLH_RESERVED_SHIFT                                                                           (4U)
#define UART_RXFLH_RESERVED_MASK                                                                            (0x000000f0U)

#define UART_RXFLH_RESERVED_24_SHIFT                                                                        (8U)
#define UART_RXFLH_RESERVED_24_MASK                                                                         (0xffffff00U)

#define UART_BLR_RESERVED_SHIFT                                                                             (0U)
#define UART_BLR_RESERVED_MASK                                                                              (0x0000003fU)

#define UART_BLR_XBOF_TYPE_SHIFT                                                                            (6U)
#define UART_BLR_XBOF_TYPE_MASK                                                                             (0x00000040U)
#define UART_BLR_XBOF_TYPE_XBOF_TYPE_VALUE_1                                                                 (1U)
#define UART_BLR_XBOF_TYPE_XBOF_TYPE_VALUE_0                                                                 (0U)

#define UART_BLR_STS_FIFO_RESET_SHIFT                                                                       (7U)
#define UART_BLR_STS_FIFO_RESET_MASK                                                                        (0x00000080U)

#define UART_BLR_RESERVED_24_SHIFT                                                                          (8U)
#define UART_BLR_RESERVED_24_MASK                                                                           (0xffffff00U)

#define UART_ACREG_EOT_EN_SHIFT                                                                             (0U)
#define UART_ACREG_EOT_EN_MASK                                                                              (0x00000001U)

#define UART_ACREG_ABORT_EN_SHIFT                                                                           (1U)
#define UART_ACREG_ABORT_EN_MASK                                                                            (0x00000002U)

#define UART_ACREG_SCTX_EN_SHIFT                                                                            (2U)
#define UART_ACREG_SCTX_EN_MASK                                                                             (0x00000004U)

#define UART_ACREG_SEND_SIP_SHIFT                                                                           (3U)
#define UART_ACREG_SEND_SIP_MASK                                                                            (0x00000008U)
#define UART_ACREG_SEND_SIP_SEND_SIP_VALUE_1                                                                 (1U)
#define UART_ACREG_SEND_SIP_SEND_SIP_VALUE_0                                                                 (0U)

#define UART_ACREG_DIS_TX_UNDERRUN_SHIFT                                                                    (4U)
#define UART_ACREG_DIS_TX_UNDERRUN_MASK                                                                     (0x00000010U)
#define UART_ACREG_DIS_TX_UNDERRUN_DIS_TX_UNDERRUN_VALUE_1                                                   (1U)
#define UART_ACREG_DIS_TX_UNDERRUN_DIS_TX_UNDERRUN_VALUE_0                                                   (0U)

#define UART_ACREG_DIS_IR_RX_SHIFT                                                                          (5U)
#define UART_ACREG_DIS_IR_RX_MASK                                                                           (0x00000020U)
#define UART_ACREG_DIS_IR_RX_DIS_IR_RX_VALUE_1                                                               (1U)
#define UART_ACREG_DIS_IR_RX_DIS_IR_RX_VALUE_0                                                               (0U)

#define UART_ACREG_SD_MOD_SHIFT                                                                             (6U)
#define UART_ACREG_SD_MOD_MASK                                                                              (0x00000040U)
#define UART_ACREG_SD_MOD_SD_MOD_VALUE_1                                                                     (1U)
#define UART_ACREG_SD_MOD_SD_MOD_VALUE_0                                                                     (0U)

#define UART_ACREG_PULSE_TYPE_SHIFT                                                                         (7U)
#define UART_ACREG_PULSE_TYPE_MASK                                                                          (0x00000080U)
#define UART_ACREG_PULSE_TYPE_PULSE_TYPE_VALUE_1                                                             (1U)
#define UART_ACREG_PULSE_TYPE_PULSE_TYPE_VALUE_0                                                             (0U)

#define UART_ACREG_RESERVED_24_SHIFT                                                                        (8U)
#define UART_ACREG_RESERVED_24_MASK                                                                         (0xffffff00U)

#define UART_SCR_DMA_MODE_CTL_SHIFT                                                                         (0U)
#define UART_SCR_DMA_MODE_CTL_MASK                                                                          (0x00000001U)
#define UART_SCR_DMA_MODE_CTL_DMA_MODE_CTL_VALUE_1                                                           (1U)
#define UART_SCR_DMA_MODE_CTL_DMA_MODE_CTL_VALUE_0                                                           (0U)

#define UART_SCR_DMA_MODE_2_SHIFT                                                                           (1U)
#define UART_SCR_DMA_MODE_2_MASK                                                                            (0x00000006U)
#define UART_SCR_DMA_MODE_2_DMA_MODE_2_VALUE_3                                                               (3U)
#define UART_SCR_DMA_MODE_2_DMA_MODE_2_VALUE_2                                                               (2U)
#define UART_SCR_DMA_MODE_2_DMA_MODE_2_VALUE_1                                                               (1U)
#define UART_SCR_DMA_MODE_2_DMA_MODE_2_VALUE_0                                                               (0U)

#define UART_SCR_TX_EMPTY_CTL_IT_SHIFT                                                                      (3U)
#define UART_SCR_TX_EMPTY_CTL_IT_MASK                                                                       (0x00000008U)
#define UART_SCR_TX_EMPTY_CTL_IT_TX_EMPTY_CTL_IT_VALUE_1                                                     (1U)
#define UART_SCR_TX_EMPTY_CTL_IT_TX_EMPTY_CTL_IT_VALUE_0                                                     (0U)

#define UART_SCR_RX_CTS_DSR_WAKE_UP_ENABLE_SHIFT                                                            (4U)
#define UART_SCR_RX_CTS_DSR_WAKE_UP_ENABLE_MASK                                                             (0x00000010U)
#define UART_SCR_RX_CTS_DSR_WAKE_UP_ENABLE_RX_CTS_DSR_WAKE_UP_ENABLE_VALUE_1                                 (1U)
#define UART_SCR_RX_CTS_DSR_WAKE_UP_ENABLE_RX_CTS_DSR_WAKE_UP_ENABLE_VALUE_0                                 (0U)

#define UART_SCR_DSR_IT_SHIFT                                                                               (5U)
#define UART_SCR_DSR_IT_MASK                                                                                (0x00000020U)
#define UART_SCR_DSR_IT_DSR_IT_VALUE_1                                                                       (1U)
#define UART_SCR_DSR_IT_DSR_IT_VALUE_0                                                                       (0U)

#define UART_SCR_TX_TRIG_GRANU1_SHIFT                                                                       (6U)
#define UART_SCR_TX_TRIG_GRANU1_MASK                                                                        (0x00000040U)
#define UART_SCR_TX_TRIG_GRANU1_TX_TRIG_GRANU1_VALUE_1                                                       (1U)
#define UART_SCR_TX_TRIG_GRANU1_TX_TRIG_GRANU1_VALUE_0                                                       (0U)

#define UART_SCR_RX_TRIG_GRANU1_SHIFT                                                                       (7U)
#define UART_SCR_RX_TRIG_GRANU1_MASK                                                                        (0x00000080U)
#define UART_SCR_RX_TRIG_GRANU1_RX_TRIG_GRANU1_VALUE_1                                                       (1U)
#define UART_SCR_RX_TRIG_GRANU1_RX_TRIG_GRANU1_VALUE_0                                                       (0U)

#define UART_SCR_RESERVED_24_SHIFT                                                                          (8U)
#define UART_SCR_RESERVED_24_MASK                                                                           (0xffffff00U)

#define UART_SSR_TX_FIFO_FULL_SHIFT                                                                         (0U)
#define UART_SSR_TX_FIFO_FULL_MASK                                                                          (0x00000001U)
#define UART_SSR_TX_FIFO_FULL_TX_FIFO_FULL_VALUE_1                                                           (1U)
#define UART_SSR_TX_FIFO_FULL_TX_FIFO_FULL_VALUE_0                                                           (0U)

#define UART_SSR_RX_CTS_DSR_WAKE_UP_STS_SHIFT                                                               (1U)
#define UART_SSR_RX_CTS_DSR_WAKE_UP_STS_MASK                                                                (0x00000002U)
#define UART_SSR_RX_CTS_DSR_WAKE_UP_STS_RX_CTS_DSR_WAKE_UP_STS_VALUE_1                                       (1U)
#define UART_SSR_RX_CTS_DSR_WAKE_UP_STS_RX_CTS_DSR_WAKE_UP_STS_VALUE_0                                       (0U)

#define UART_SSR_RESERVED_SHIFT                                                                             (3U)
#define UART_SSR_RESERVED_MASK                                                                              (0x000000f8U)

#define UART_SSR_RESERVED_24_SHIFT                                                                          (8U)
#define UART_SSR_RESERVED_24_MASK                                                                           (0xffffff00U)

#define UART_SSR_DMA_COUNTER_RST_SHIFT                                                                      (2U)
#define UART_SSR_DMA_COUNTER_RST_MASK                                                                       (0x00000004U)
#define UART_SSR_DMA_COUNTER_RST_DMA_COUNTER_RST_VALUE_0                                                     (0U)
#define UART_SSR_DMA_COUNTER_RST_DMA_COUNTER_RST_VALUE_1                                                     (1U)

#define UART_EBLR_EBLR_SHIFT                                                                                (0U)
#define UART_EBLR_EBLR_MASK                                                                                 (0x000000ffU)

#define UART_EBLR_RESERVED_24_SHIFT                                                                         (8U)
#define UART_EBLR_RESERVED_24_MASK                                                                          (0xffffff00U)

#define UART_MVR_MINOR_SHIFT                                                                                (0U)
#define UART_MVR_MINOR_MASK                                                                                 (0x0000003fU)

#define UART_MVR_CUSTOM_SHIFT                                                                               (6U)
#define UART_MVR_CUSTOM_MASK                                                                                (0x000000c0U)

#define UART_MVR_MAJOR_SHIFT                                                                                (8U)
#define UART_MVR_MAJOR_MASK                                                                                 (0x00000700U)

#define UART_MVR_RTL_SHIFT                                                                                  (11U)
#define UART_MVR_RTL_MASK                                                                                   (0x0000f800U)

#define UART_MVR_FUNC_SHIFT                                                                                 (16U)
#define UART_MVR_FUNC_MASK                                                                                  (0x0fff0000U)

#define UART_MVR_RESERVED_SHIFT                                                                             (28U)
#define UART_MVR_RESERVED_MASK                                                                              (0x30000000U)

#define UART_MVR_SCHEME_SHIFT                                                                               (30U)
#define UART_MVR_SCHEME_MASK                                                                                (0xc0000000U)

#define UART_SYSC_AUTOIDLE_SHIFT                                                                            (0U)
#define UART_SYSC_AUTOIDLE_MASK                                                                             (0x00000001U)
#define UART_SYSC_AUTOIDLE_AUTOIDLE_VALUE_1                                                                  (1U)
#define UART_SYSC_AUTOIDLE_AUTOIDLE_VALUE_0                                                                  (0U)

#define UART_SYSC_SOFTRESET_SHIFT                                                                           (1U)
#define UART_SYSC_SOFTRESET_MASK                                                                            (0x00000002U)
#define UART_SYSC_SOFTRESET_SOFTRESET_VALUE_1                                                                (1U)
#define UART_SYSC_SOFTRESET_SOFTRESET_VALUE_0                                                                (0U)

#define UART_SYSC_ENAWAKEUP_SHIFT                                                                           (2U)
#define UART_SYSC_ENAWAKEUP_MASK                                                                            (0x00000004U)
#define UART_SYSC_ENAWAKEUP_ENAWAKEUP_VALUE_1                                                                (1U)
#define UART_SYSC_ENAWAKEUP_ENAWAKEUP_VALUE_0                                                                (0U)

#define UART_SYSC_IDLEMODE_SHIFT                                                                            (3U)
#define UART_SYSC_IDLEMODE_MASK                                                                             (0x00000018U)
#define UART_SYSC_IDLEMODE_IDLEMODE_VALUE_3                                                                  (3U)
#define UART_SYSC_IDLEMODE_IDLEMODE_VALUE_2                                                                  (2U)
#define UART_SYSC_IDLEMODE_IDLEMODE_VALUE_1                                                                  (1U)
#define UART_SYSC_IDLEMODE_IDLEMODE_VALUE_0                                                                  (0U)

#define UART_SYSC_RESERVED_SHIFT                                                                            (5U)
#define UART_SYSC_RESERVED_MASK                                                                             (0x000000e0U)

#define UART_SYSC_RESERVED_24_SHIFT                                                                         (8U)
#define UART_SYSC_RESERVED_24_MASK                                                                          (0xffffff00U)

#define UART_SYSS_RESETDONE_SHIFT                                                                           (0U)
#define UART_SYSS_RESETDONE_MASK                                                                            (0x00000001U)
#define UART_SYSS_RESETDONE_RESETDONE_VALUE_1                                                                (1U)
#define UART_SYSS_RESETDONE_RESETDONE_VALUE_0                                                                (0U)

#define UART_SYSS_RESERVED_SHIFT                                                                            (1U)
#define UART_SYSS_RESERVED_MASK                                                                             (0x000000feU)

#define UART_SYSS_RESERVED_24_SHIFT                                                                         (8U)
#define UART_SYSS_RESERVED_24_MASK                                                                          (0xffffff00U)

#define UART_WER_EVENT_0_CTS_ACTIVITY_SHIFT                                                                 (0U)
#define UART_WER_EVENT_0_CTS_ACTIVITY_MASK                                                                  (0x00000001U)
#define UART_WER_EVENT_0_CTS_ACTIVITY_EVENT_0_CTS_ACTIVITY_VALUE_1                                           (1U)
#define UART_WER_EVENT_0_CTS_ACTIVITY_EVENT_0_CTS_ACTIVITY_VALUE_0                                           (0U)

#define UART_WER_EVENT_1_DSR_ACTIVITY_SHIFT                                                                 (1U)
#define UART_WER_EVENT_1_DSR_ACTIVITY_MASK                                                                  (0x00000002U)
#define UART_WER_EVENT_1_DSR_ACTIVITY_EVENT_1_DSR_ACTIVITY_VALUE_1                                           (1U)
#define UART_WER_EVENT_1_DSR_ACTIVITY_EVENT_1_DSR_ACTIVITY_VALUE_0                                           (0U)

#define UART_WER_EVENT_2_RI_ACTIVITY_SHIFT                                                                  (2U)
#define UART_WER_EVENT_2_RI_ACTIVITY_MASK                                                                   (0x00000004U)
#define UART_WER_EVENT_2_RI_ACTIVITY_EVENT_2_RI_ACTIVITY_VALUE_1                                             (1U)
#define UART_WER_EVENT_2_RI_ACTIVITY_EVENT_2_RI_ACTIVITY_VALUE_0                                             (0U)

#define UART_WER_EVENT_3_DCD_CD_ACTIVITY_SHIFT                                                              (3U)
#define UART_WER_EVENT_3_DCD_CD_ACTIVITY_MASK                                                               (0x00000008U)
#define UART_WER_EVENT_3_DCD_CD_ACTIVITY_EVENT_3_DCD_CD_ACTIVITY_VALUE_1                                     (1U)
#define UART_WER_EVENT_3_DCD_CD_ACTIVITY_EVENT_3_DCD_CD_ACTIVITY_VALUE_0                                     (0U)

#define UART_WER_EVENT_4_RX_ACTIVITY_SHIFT                                                                  (4U)
#define UART_WER_EVENT_4_RX_ACTIVITY_MASK                                                                   (0x00000010U)
#define UART_WER_EVENT_4_RX_ACTIVITY_EVENT_4_RX_ACTIVITY_VALUE_1                                             (1U)
#define UART_WER_EVENT_4_RX_ACTIVITY_EVENT_4_RX_ACTIVITY_VALUE_0                                             (0U)

#define UART_WER_EVENT_5_RHR_INTERRUPT_SHIFT                                                                (5U)
#define UART_WER_EVENT_5_RHR_INTERRUPT_MASK                                                                 (0x00000020U)
#define UART_WER_EVENT_5_RHR_INTERRUPT_EVENT_5_RHR_INTERRUPT_VALUE_1                                         (1U)
#define UART_WER_EVENT_5_RHR_INTERRUPT_EVENT_5_RHR_INTERRUPT_VALUE_0                                         (0U)

#define UART_WER_EVENT_6_RECEIVER_LINE_STATUS_INTERRUPT_SHIFT                                               (6U)
#define UART_WER_EVENT_6_RECEIVER_LINE_STATUS_INTERRUPT_MASK                                                (0x00000040U)
#define UART_WER_EVENT_6_RECEIVER_LINE_STATUS_INTERRUPT_EVENT_6_RECEIVER_LINE_STATUS_INTERRUPT_VALUE_1       (1U)
#define UART_WER_EVENT_6_RECEIVER_LINE_STATUS_INTERRUPT_EVENT_6_RECEIVER_LINE_STATUS_INTERRUPT_VALUE_0       (0U)

#define UART_WER_EVENT_7_TX_WAKEUP_EN_SHIFT                                                                 (7U)
#define UART_WER_EVENT_7_TX_WAKEUP_EN_MASK                                                                  (0x00000080U)
#define UART_WER_EVENT_7_TX_WAKEUP_EN_EVENT_7_TX_WAKEUP_EN_VALUE_0                                           (0U)
#define UART_WER_EVENT_7_TX_WAKEUP_EN_EVENT_7_TX_WAKEUP_EN_VALUE_1                                           (1U)

#define UART_WER_RESERVED_24_SHIFT                                                                          (8U)
#define UART_WER_RESERVED_24_MASK                                                                           (0xffffff00U)

#define UART_CFPS_CFPS_SHIFT                                                                                (0U)
#define UART_CFPS_CFPS_MASK                                                                                 (0x000000ffU)

#define UART_CFPS_RESERVED_24_SHIFT                                                                         (8U)
#define UART_CFPS_RESERVED_24_MASK                                                                          (0xffffff00U)

#define UART_RXFIFO_LVL_RXFIFO_LVL_SHIFT                                                                    (0U)
#define UART_RXFIFO_LVL_RXFIFO_LVL_MASK                                                                     (0x000000ffU)

#define UART_RXFIFO_LVL_RESERVED24_SHIFT                                                                    (8U)
#define UART_RXFIFO_LVL_RESERVED24_MASK                                                                     (0xffffff00U)

#define UART_TXFIFO_LVL_TXFIFO_LVL_SHIFT                                                                    (0U)
#define UART_TXFIFO_LVL_TXFIFO_LVL_MASK                                                                     (0x000000ffU)

#define UART_TXFIFO_LVL_RESERVED24_SHIFT                                                                    (8U)
#define UART_TXFIFO_LVL_RESERVED24_MASK                                                                     (0xffffff00U)

#define UART_IER2_EN_RXFIFO_EMPTY_SHIFT                                                                     (0U)
#define UART_IER2_EN_RXFIFO_EMPTY_MASK                                                                      (0x00000001U)

#define UART_IER2_EN_TXFIFO_EMPTY_SHIFT                                                                     (1U)
#define UART_IER2_EN_TXFIFO_EMPTY_MASK                                                                      (0x00000002U)

#define UART_IER2_RESERVED_SHIFT                                                                            (2U)
#define UART_IER2_RESERVED_MASK                                                                             (0x000000fcU)

#define UART_IER2_RESERVED1_SHIFT                                                                           (8U)
#define UART_IER2_RESERVED1_MASK                                                                            (0xffffff00U)

#define UART_ISR2_RXFIFO_EMPTY_STS_SHIFT                                                                    (0U)
#define UART_ISR2_RXFIFO_EMPTY_STS_MASK                                                                     (0x00000001U)
#define UART_ISR2_RXFIFO_EMPTY_STS_RXFIFO_EMPTY_STS_VALUE_0                                                  (0U)
#define UART_ISR2_RXFIFO_EMPTY_STS_RXFIFO_EMPTY_STS_VALUE_1                                                  (1U)

#define UART_ISR2_TXFIFO_EMPTY_STS_SHIFT                                                                    (1U)
#define UART_ISR2_TXFIFO_EMPTY_STS_MASK                                                                     (0x00000002U)
#define UART_ISR2_TXFIFO_EMPTY_STS_TXFIFO_EMPTY_STS_VALUE_0                                                  (0U)
#define UART_ISR2_TXFIFO_EMPTY_STS_TXFIFO_EMPTY_STS_VALUE_1                                                  (1U)

#define UART_ISR2_RESERVED_SHIFT                                                                            (2U)
#define UART_ISR2_RESERVED_MASK                                                                             (0x000000fcU)

#define UART_ISR2_RESERVED1_SHIFT                                                                           (8U)
#define UART_ISR2_RESERVED1_MASK                                                                            (0xffffff00U)

#define UART_FREQ_SEL_FREQ_SEL_SHIFT                                                                        (0U)
#define UART_FREQ_SEL_FREQ_SEL_MASK                                                                         (0x000000ffU)

#define UART_FREQ_SEL_RESERVED2_SHIFT                                                                       (8U)
#define UART_FREQ_SEL_RESERVED2_MASK                                                                        (0xffffff00U)

#define UART_ABAUD_1ST_CHAR_RESERVED_SHIFT                                                                  (0U)
#define UART_ABAUD_1ST_CHAR_RESERVED_MASK                                                                   (0xffffffffU)

#define UART_BAUD_2ND_CHAR_RESERVED_SHIFT                                                                   (0U)
#define UART_BAUD_2ND_CHAR_RESERVED_MASK                                                                    (0xffffffffU)

#define UART_MDR3_DISABLE_CIR_RX_DEMOD_SHIFT                                                                (0U)
#define UART_MDR3_DISABLE_CIR_RX_DEMOD_MASK                                                                 (0x00000001U)
#define UART_MDR3_DISABLE_CIR_RX_DEMOD_DISABLE_CIR_RX_DEMOD_VALUE_0                                          (0U)
#define UART_MDR3_DISABLE_CIR_RX_DEMOD_DISABLE_CIR_RX_DEMOD_VALUE_1                                          (1U)

#define UART_MDR3_NONDEFAULT_FREQ_SHIFT                                                                     (1U)
#define UART_MDR3_NONDEFAULT_FREQ_MASK                                                                      (0x00000002U)

#define UART_MDR3_SET_DMA_TX_THRESHOLD_SHIFT                                                                (2U)
#define UART_MDR3_SET_DMA_TX_THRESHOLD_MASK                                                                 (0x00000004U)

#define UART_MDR3_RESERVED1_SHIFT                                                                           (3U)
#define UART_MDR3_RESERVED1_MASK                                                                            (0x000000f8U)

#define UART_MDR3_RESERVED2_SHIFT                                                                           (8U)
#define UART_MDR3_RESERVED2_MASK                                                                            (0xffffff00U)

#define UART_TX_DMA_THRESHOLD_TX_DMA_THRESHOLD_SHIFT                                                        (0U)
#define UART_TX_DMA_THRESHOLD_TX_DMA_THRESHOLD_MASK                                                         (0x0000001fU)

#define UART_TX_DMA_THRESHOLD_RESERVED_SHIFT                                                                (5U)
#define UART_TX_DMA_THRESHOLD_RESERVED_MASK                                                                 (0x000000e0U)

#define UART_TX_DMA_THRESHOLD_RESERVED1_SHIFT                                                               (8U)
#define UART_TX_DMA_THRESHOLD_RESERVED1_MASK                                                                (0xffffff00U)

#define UART_DLL_CLOCK_LSB_SHIFT                                                                            (0U)
#define UART_DLL_CLOCK_LSB_MASK                                                                             (0x000000ffU)

#define UART_DLL_RESERVED_SHIFT                                                                             (8U)
#define UART_DLL_RESERVED_MASK                                                                              (0xffffff00U)

#define UART_IER_IRDA_RHR_IT_SHIFT                                                                          (0U)
#define UART_IER_IRDA_RHR_IT_MASK                                                                           (0x00000001U)
#define UART_IER_IRDA_RHR_IT_RHR_IT_VALUE_1                                                                  (1U)
#define UART_IER_IRDA_RHR_IT_RHR_IT_VALUE_0                                                                  (0U)

#define UART_IER_IRDA_THR_IT_SHIFT                                                                          (1U)
#define UART_IER_IRDA_THR_IT_MASK                                                                           (0x00000002U)
#define UART_IER_IRDA_THR_IT_THR_IT_VALUE_1                                                                  (1U)
#define UART_IER_IRDA_THR_IT_THR_IT_VALUE_0                                                                  (0U)

#define UART_IER_IRDA_LAST_RX_BYTE_IT_SHIFT                                                                 (2U)
#define UART_IER_IRDA_LAST_RX_BYTE_IT_MASK                                                                  (0x00000004U)
#define UART_IER_IRDA_LAST_RX_BYTE_IT_LAST_RX_BYTE_IT_VALUE_1                                                (1U)
#define UART_IER_IRDA_LAST_RX_BYTE_IT_LAST_RX_BYTE_IT_VALUE_0                                                (0U)

#define UART_IER_IRDA_RX_OVERRUN_IT_SHIFT                                                                   (3U)
#define UART_IER_IRDA_RX_OVERRUN_IT_MASK                                                                    (0x00000008U)
#define UART_IER_IRDA_RX_OVERRUN_IT_RX_OVERRUN_IT_VALUE_1                                                    (1U)
#define UART_IER_IRDA_RX_OVERRUN_IT_RX_OVERRUN_IT_VALUE_0                                                    (0U)

#define UART_IER_IRDA_STS_FIFO_TRIG_IT_SHIFT                                                                (4U)
#define UART_IER_IRDA_STS_FIFO_TRIG_IT_MASK                                                                 (0x00000010U)
#define UART_IER_IRDA_STS_FIFO_TRIG_IT_STS_FIFO_TRIG_IT_VALUE_1                                              (1U)
#define UART_IER_IRDA_STS_FIFO_TRIG_IT_STS_FIFO_TRIG_IT_VALUE_0                                              (0U)

#define UART_IER_IRDA_TX_STATUS_IT_SHIFT                                                                    (5U)
#define UART_IER_IRDA_TX_STATUS_IT_MASK                                                                     (0x00000020U)
#define UART_IER_IRDA_TX_STATUS_IT_TX_STATUS_VALUE_1                                                         (1U)
#define UART_IER_IRDA_TX_STATUS_IT_TX_STATUS_VALUE_0                                                         (0U)

#define UART_IER_IRDA_LINE_STS_IT_SHIFT                                                                     (6U)
#define UART_IER_IRDA_LINE_STS_IT_MASK                                                                      (0x00000040U)
#define UART_IER_IRDA_LINE_STS_IT_LINE_STS_IT_U_VALUE_1                                                      (1U)
#define UART_IER_IRDA_LINE_STS_IT_LINE_STS_IT_U_VALUE_0                                                      (0U)

#define UART_IER_IRDA_EOF_IT_SHIFT                                                                          (7U)
#define UART_IER_IRDA_EOF_IT_MASK                                                                           (0x00000080U)
#define UART_IER_IRDA_EOF_IT_EOF_IT_U_VALUE_1                                                                (1U)
#define UART_IER_IRDA_EOF_IT_EOF_IT_U_VALUE_0                                                                (0U)

#define UART_IER_IRDA_RESERVED_SHIFT                                                                        (8U)
#define UART_IER_IRDA_RESERVED_MASK                                                                         (0xffffff00U)

#define UART_IER_CIR_RHR_IT_SHIFT                                                                           (0U)
#define UART_IER_CIR_RHR_IT_MASK                                                                            (0x00000001U)
#define UART_IER_CIR_RHR_IT_RHR_IT_VALUE_1                                                                   (1U)
#define UART_IER_CIR_RHR_IT_RHR_IT_VALUE_0                                                                   (0U)

#define UART_IER_CIR_THR_IT_SHIFT                                                                           (1U)
#define UART_IER_CIR_THR_IT_MASK                                                                            (0x00000002U)
#define UART_IER_CIR_THR_IT_THR_IT_VALUE_1                                                                   (1U)
#define UART_IER_CIR_THR_IT_THR_IT_VALUE_0                                                                   (0U)

#define UART_IER_CIR_RX_STOP_IT_SHIFT                                                                       (2U)
#define UART_IER_CIR_RX_STOP_IT_MASK                                                                        (0x00000004U)
#define UART_IER_CIR_RX_STOP_IT_RX_STOP_IT_U_VALUE_1                                                         (1U)
#define UART_IER_CIR_RX_STOP_IT_RX_STOP_IT_U_VALUE_0                                                         (0U)

#define UART_IER_CIR_RX_OVERRUN_IT_SHIFT                                                                    (3U)
#define UART_IER_CIR_RX_OVERRUN_IT_MASK                                                                     (0x00000008U)
#define UART_IER_CIR_RX_OVERRUN_IT_RX_OVERRUN_IT_U_VALUE_1                                                   (1U)
#define UART_IER_CIR_RX_OVERRUN_IT_RX_OVERRUN_IT_U_VALUE_0                                                   (0U)

#define UART_IER_CIR_RESERVED_1_SHIFT                                                                       (4U)
#define UART_IER_CIR_RESERVED_1_MASK                                                                        (0x00000010U)

#define UART_IER_CIR_TX_STATUS_IT_SHIFT                                                                     (5U)
#define UART_IER_CIR_TX_STATUS_IT_MASK                                                                      (0x00000020U)
#define UART_IER_CIR_TX_STATUS_IT_TX_STATUS_IT_U_VALUE_1                                                     (1U)
#define UART_IER_CIR_TX_STATUS_IT_TX_STATUS_IT_U_VALUE_0                                                     (0U)

#define UART_IER_CIR_RESERVED_2_SHIFT                                                                       (6U)
#define UART_IER_CIR_RESERVED_2_MASK                                                                        (0x000000c0U)

#define UART_IER_CIR_RESERVED_3_SHIFT                                                                       (8U)
#define UART_IER_CIR_RESERVED_3_MASK                                                                        (0xffffff00U)

#define UART_DLH_CLOCK_MSB_SHIFT                                                                            (0U)
#define UART_DLH_CLOCK_MSB_MASK                                                                             (0x0000003fU)

#define UART_DLH_RESERVED_SHIFT                                                                             (6U)
#define UART_DLH_RESERVED_MASK                                                                              (0xffffffc0U)

#define UART_IIR_IRDA_RHR_IT_SHIFT                                                                          (0U)
#define UART_IIR_IRDA_RHR_IT_MASK                                                                           (0x00000001U)
#define UART_IIR_IRDA_RHR_IT_RHR_IT_VALUE_1                                                                  (1U)
#define UART_IIR_IRDA_RHR_IT_RHR_IT_VALUE_0                                                                  (0U)

#define UART_IIR_IRDA_THR_IT_SHIFT                                                                          (1U)
#define UART_IIR_IRDA_THR_IT_MASK                                                                           (0x00000002U)
#define UART_IIR_IRDA_THR_IT_THR_IT_VALUE_1                                                                  (1U)
#define UART_IIR_IRDA_THR_IT_THR_IT_VALUE_0                                                                  (0U)

#define UART_IIR_IRDA_RX_FIFO_LAST_BYTE_IT_SHIFT                                                            (2U)
#define UART_IIR_IRDA_RX_FIFO_LAST_BYTE_IT_MASK                                                             (0x00000004U)
#define UART_IIR_IRDA_RX_FIFO_LAST_BYTE_IT_RX_FIFO_LAST_BYTE_IT_U_VALUE_1                                    (1U)
#define UART_IIR_IRDA_RX_FIFO_LAST_BYTE_IT_RX_FIFO_LAST_BYTE_IT_U_VALUE_0                                    (0U)

#define UART_IIR_IRDA_RX_OE_IT_SHIFT                                                                        (3U)
#define UART_IIR_IRDA_RX_OE_IT_MASK                                                                         (0x00000008U)
#define UART_IIR_IRDA_RX_OE_IT_RX_OE_IT_U_VALUE_1                                                            (1U)
#define UART_IIR_IRDA_RX_OE_IT_RX_OE_IT_U_VALUE_0                                                            (0U)

#define UART_IIR_IRDA_STS_FIFO_IT_SHIFT                                                                     (4U)
#define UART_IIR_IRDA_STS_FIFO_IT_MASK                                                                      (0x00000010U)
#define UART_IIR_IRDA_STS_FIFO_IT_STS_FIFO_IT_U_VALUE_1                                                      (1U)
#define UART_IIR_IRDA_STS_FIFO_IT_STS_FIFO_IT_U_VALUE_0                                                      (0U)

#define UART_IIR_IRDA_TX_STATUS_IT_SHIFT                                                                    (5U)
#define UART_IIR_IRDA_TX_STATUS_IT_MASK                                                                     (0x00000020U)
#define UART_IIR_IRDA_TX_STATUS_IT_TX_STATUS_IT_U_VALUE_1                                                    (1U)
#define UART_IIR_IRDA_TX_STATUS_IT_TX_STATUS_IT_U_VALUE_0                                                    (0U)

#define UART_IIR_IRDA_LINE_STS_IT_SHIFT                                                                     (6U)
#define UART_IIR_IRDA_LINE_STS_IT_MASK                                                                      (0x00000040U)
#define UART_IIR_IRDA_LINE_STS_IT_LINE_STS_IT_U_VALUE_1                                                      (1U)
#define UART_IIR_IRDA_LINE_STS_IT_LINE_STS_IT_U_VALUE_0                                                      (0U)

#define UART_IIR_IRDA_EOF_IT_SHIFT                                                                          (7U)
#define UART_IIR_IRDA_EOF_IT_MASK                                                                           (0x00000080U)
#define UART_IIR_IRDA_EOF_IT_EOF_IT_U_VALUE_1                                                                (1U)
#define UART_IIR_IRDA_EOF_IT_EOF_IT_U_VALUE_0                                                                (0U)

#define UART_IIR_IRDA_RESERVED_SHIFT                                                                        (8U)
#define UART_IIR_IRDA_RESERVED_MASK                                                                         (0xffffff00U)

#define UART_IIR_CIR_RHR_IT_SHIFT                                                                           (0U)
#define UART_IIR_CIR_RHR_IT_MASK                                                                            (0x00000001U)
#define UART_IIR_CIR_RHR_IT_RHR_IT_VALUE_1                                                                   (1U)
#define UART_IIR_CIR_RHR_IT_RHR_IT_VALUE_0                                                                   (0U)

#define UART_IIR_CIR_THR_IT_SHIFT                                                                           (1U)
#define UART_IIR_CIR_THR_IT_MASK                                                                            (0x00000002U)
#define UART_IIR_CIR_THR_IT_THR_IT_VALUE_1                                                                   (1U)
#define UART_IIR_CIR_THR_IT_THR_IT_VALUE_0                                                                   (0U)

#define UART_IIR_CIR_RX_STOP_IT_SHIFT                                                                       (2U)
#define UART_IIR_CIR_RX_STOP_IT_MASK                                                                        (0x00000004U)
#define UART_IIR_CIR_RX_STOP_IT_RX_STOP_IT_U_VALUE_1                                                         (1U)
#define UART_IIR_CIR_RX_STOP_IT_RX_STOP_IT_U_VALUE_0                                                         (0U)

#define UART_IIR_CIR_RX_OE_IT_SHIFT                                                                         (3U)
#define UART_IIR_CIR_RX_OE_IT_MASK                                                                          (0x00000008U)
#define UART_IIR_CIR_RX_OE_IT_RX_OE_IT_U_VALUE_1                                                             (1U)
#define UART_IIR_CIR_RX_OE_IT_RX_OE_IT_U_VALUE_0                                                             (0U)

#define UART_IIR_CIR_RESERVED_1_SHIFT                                                                       (4U)
#define UART_IIR_CIR_RESERVED_1_MASK                                                                        (0x00000010U)

#define UART_IIR_CIR_TX_STATUS_IT_SHIFT                                                                     (5U)
#define UART_IIR_CIR_TX_STATUS_IT_MASK                                                                      (0x00000020U)
#define UART_IIR_CIR_TX_STATUS_IT_TX_STATUS_IT_U_VALUE_1                                                     (1U)
#define UART_IIR_CIR_TX_STATUS_IT_TX_STATUS_IT_U_VALUE_0                                                     (0U)

#define UART_IIR_CIR_RESERVED_2_SHIFT                                                                       (6U)
#define UART_IIR_CIR_RESERVED_2_MASK                                                                        (0x000000c0U)

#define UART_IIR_CIR_RESERVED_SHIFT                                                                         (8U)
#define UART_IIR_CIR_RESERVED_MASK                                                                          (0xffffff00U)

#define UART_EFR_SW_FLOW_CONTROL_SHIFT                                                                      (0U)
#define UART_EFR_SW_FLOW_CONTROL_MASK                                                                       (0x0000000fU)
#define UART_EFR_SW_FLOW_CONTROL_SW_FLOW_CONTROL_U_VALUE_15                                                  (15U)
#define UART_EFR_SW_FLOW_CONTROL_SW_FLOW_CONTROL_U_VALUE_14                                                  (14U)
#define UART_EFR_SW_FLOW_CONTROL_SW_FLOW_CONTROL_U_VALUE_13                                                  (13U)
#define UART_EFR_SW_FLOW_CONTROL_SW_FLOW_CONTROL_U_VALUE_12                                                  (12U)
#define UART_EFR_SW_FLOW_CONTROL_SW_FLOW_CONTROL_U_VALUE_11                                                  (11U)
#define UART_EFR_SW_FLOW_CONTROL_SW_FLOW_CONTROL_U_VALUE_10                                                  (10U)
#define UART_EFR_SW_FLOW_CONTROL_SW_FLOW_CONTROL_U_VALUE_9                                                   (9U)
#define UART_EFR_SW_FLOW_CONTROL_SW_FLOW_CONTROL_U_VALUE_8                                                   (8U)
#define UART_EFR_SW_FLOW_CONTROL_SW_FLOW_CONTROL_U_VALUE_7                                                   (7U)
#define UART_EFR_SW_FLOW_CONTROL_SW_FLOW_CONTROL_U_VALUE_6                                                   (6U)
#define UART_EFR_SW_FLOW_CONTROL_SW_FLOW_CONTROL_U_VALUE_5                                                   (5U)
#define UART_EFR_SW_FLOW_CONTROL_SW_FLOW_CONTROL_U_VALUE_4                                                   (4U)
#define UART_EFR_SW_FLOW_CONTROL_SW_FLOW_CONTROL_U_VALUE_3                                                   (3U)
#define UART_EFR_SW_FLOW_CONTROL_SW_FLOW_CONTROL_U_VALUE_2                                                   (2U)
#define UART_EFR_SW_FLOW_CONTROL_SW_FLOW_CONTROL_U_VALUE_1                                                   (1U)
#define UART_EFR_SW_FLOW_CONTROL_SW_FLOW_CONTROL_U_VALUE_0                                                   (0U)

#define UART_EFR_ENHANCED_EN_SHIFT                                                                          (4U)
#define UART_EFR_ENHANCED_EN_MASK                                                                           (0x00000010U)
#define UART_EFR_ENHANCED_EN_ENHANCED_EN_U_VALUE_1                                                           (1U)
#define UART_EFR_ENHANCED_EN_ENHANCED_EN_U_VALUE_0                                                           (0U)

#define UART_EFR_SPECIAL_CHAR_DETECT_SHIFT                                                                  (5U)
#define UART_EFR_SPECIAL_CHAR_DETECT_MASK                                                                   (0x00000020U)
#define UART_EFR_SPECIAL_CHAR_DETECT_SPECIAL_CHAR_DETECT_U_VALUE_1                                           (1U)
#define UART_EFR_SPECIAL_CHAR_DETECT_SPECIAL_CHAR_DETECT_U_VALUE_0                                           (0U)

#define UART_EFR_AUTO_RTS_EN_SHIFT                                                                          (6U)
#define UART_EFR_AUTO_RTS_EN_MASK                                                                           (0x00000040U)
#define UART_EFR_AUTO_RTS_EN_AUTO_RTS_EN_U_VALUE_1                                                           (1U)
#define UART_EFR_AUTO_RTS_EN_AUTO_RTS_EN_U_VALUE_0                                                           (0U)

#define UART_EFR_AUTO_CTS_EN_SHIFT                                                                          (7U)
#define UART_EFR_AUTO_CTS_EN_MASK                                                                           (0x00000080U)
#define UART_EFR_AUTO_CTS_EN_AUTO_CTS_EN_U_VALUE_1                                                           (1U)
#define UART_EFR_AUTO_CTS_EN_AUTO_CTS_EN_U_VALUE_0                                                           (0U)

#define UART_EFR_RESERVED_SHIFT                                                                             (8U)
#define UART_EFR_RESERVED_MASK                                                                              (0xffffff00U)

#define UART_XON1_ADDR1_XON_WORD1_SHIFT                                                                     (0U)
#define UART_XON1_ADDR1_XON_WORD1_MASK                                                                      (0x000000ffU)

#define UART_XON1_ADDR1_RESERVED_24_SHIFT                                                                   (8U)
#define UART_XON1_ADDR1_RESERVED_24_MASK                                                                    (0xffffff00U)

#define UART_LSR_IRDA_RX_FIFO_E_SHIFT                                                                       (0U)
#define UART_LSR_IRDA_RX_FIFO_E_MASK                                                                        (0x00000001U)
#define UART_LSR_IRDA_RX_FIFO_E_RX_FIFO_E_VALUE_1                                                            (1U)
#define UART_LSR_IRDA_RX_FIFO_E_RX_FIFO_E_VALUE_0                                                            (0U)

#define UART_LSR_IRDA_STS_FIFO_E_SHIFT                                                                      (1U)
#define UART_LSR_IRDA_STS_FIFO_E_MASK                                                                       (0x00000002U)
#define UART_LSR_IRDA_STS_FIFO_E_STS_FIFO_E_VALUE_1                                                          (1U)
#define UART_LSR_IRDA_STS_FIFO_E_STS_FIFO_E_VALUE_0                                                          (0U)

#define UART_LSR_IRDA_CRC_SHIFT                                                                             (2U)
#define UART_LSR_IRDA_CRC_MASK                                                                              (0x00000004U)
#define UART_LSR_IRDA_CRC_CRC_VALUE_1                                                                        (1U)
#define UART_LSR_IRDA_CRC_CRC_VALUE_0                                                                        (0U)

#define UART_LSR_IRDA_ABORT_SHIFT                                                                           (3U)
#define UART_LSR_IRDA_ABORT_MASK                                                                            (0x00000008U)
#define UART_LSR_IRDA_ABORT_ABORT_VALUE_1                                                                    (1U)
#define UART_LSR_IRDA_ABORT_ABORT_VALUE_0                                                                    (0U)

#define UART_LSR_IRDA_FRAME_TOO_LONG_SHIFT                                                                  (4U)
#define UART_LSR_IRDA_FRAME_TOO_LONG_MASK                                                                   (0x00000010U)
#define UART_LSR_IRDA_FRAME_TOO_LONG_FRAME_TOO_LONG_VALUE_1                                                  (1U)
#define UART_LSR_IRDA_FRAME_TOO_LONG_FRAME_TOO_LONG_VALUE_0                                                  (0U)

#define UART_LSR_IRDA_RX_LAST_BYTE_SHIFT                                                                    (5U)
#define UART_LSR_IRDA_RX_LAST_BYTE_MASK                                                                     (0x00000020U)
#define UART_LSR_IRDA_RX_LAST_BYTE_RX_LAST_BYTE_VALUE_1                                                      (1U)
#define UART_LSR_IRDA_RX_LAST_BYTE_RX_LAST_BYTE_VALUE_0                                                      (0U)

#define UART_LSR_IRDA_STS_FIFO_FULL_SHIFT                                                                   (6U)
#define UART_LSR_IRDA_STS_FIFO_FULL_MASK                                                                    (0x00000040U)
#define UART_LSR_IRDA_STS_FIFO_FULL_STS_FIFO_FULL_VALUE_1                                                    (1U)
#define UART_LSR_IRDA_STS_FIFO_FULL_STS_FIFO_FULL_VALUE_0                                                    (0U)

#define UART_LSR_IRDA_THR_EMPTY_SHIFT                                                                       (7U)
#define UART_LSR_IRDA_THR_EMPTY_MASK                                                                        (0x00000080U)
#define UART_LSR_IRDA_THR_EMPTY_THR_EMPTY_VALUE_1                                                            (1U)
#define UART_LSR_IRDA_THR_EMPTY_THR_EMPTY_VALUE_0                                                            (0U)

#define UART_LSR_IRDA_RESERVED_24_SHIFT                                                                     (8U)
#define UART_LSR_IRDA_RESERVED_24_MASK                                                                      (0xffffff00U)

#define UART_LSR_CIR_RX_FIFO_E_SHIFT                                                                        (0U)
#define UART_LSR_CIR_RX_FIFO_E_MASK                                                                         (0x00000001U)
#define UART_LSR_CIR_RX_FIFO_E_RX_FIFO_E_VALUE_1                                                             (1U)
#define UART_LSR_CIR_RX_FIFO_E_RX_FIFO_E_VALUE_0                                                             (0U)

#define UART_LSR_CIR_RESERVED_SHIFT                                                                         (1U)
#define UART_LSR_CIR_RESERVED_MASK                                                                          (0x0000001eU)

#define UART_LSR_CIR_RX_STOP_SHIFT                                                                          (5U)
#define UART_LSR_CIR_RX_STOP_MASK                                                                           (0x00000020U)
#define UART_LSR_CIR_RX_STOP_RX_STOP_VALUE_1                                                                 (1U)
#define UART_LSR_CIR_RX_STOP_RX_STOP_VALUE_0                                                                 (0U)

#define UART_LSR_CIR_RESERVED_1_SHIFT                                                                       (6U)
#define UART_LSR_CIR_RESERVED_1_MASK                                                                        (0x00000040U)

#define UART_LSR_CIR_THR_EMPTY_SHIFT                                                                        (7U)
#define UART_LSR_CIR_THR_EMPTY_MASK                                                                         (0x00000080U)
#define UART_LSR_CIR_THR_EMPTY_THR_EMPTY_VALUE_1                                                             (1U)
#define UART_LSR_CIR_THR_EMPTY_THR_EMPTY_VALUE_0                                                             (0U)

#define UART_LSR_CIR_RESERVED_24_SHIFT                                                                      (8U)
#define UART_LSR_CIR_RESERVED_24_MASK                                                                       (0xffffff00U)

#define UART_XON2_ADDR2_XON_WORD2_SHIFT                                                                     (0U)
#define UART_XON2_ADDR2_XON_WORD2_MASK                                                                      (0x000000ffU)

#define UART_XON2_ADDR2_RESERVED_24_SHIFT                                                                   (8U)
#define UART_XON2_ADDR2_RESERVED_24_MASK                                                                    (0xffffff00U)

#define UART_XOFF1_XOFF_WORD1_SHIFT                                                                         (0U)
#define UART_XOFF1_XOFF_WORD1_MASK                                                                          (0x000000ffU)

#define UART_XOFF1_RESERVED_24_SHIFT                                                                        (8U)
#define UART_XOFF1_RESERVED_24_MASK                                                                         (0xffffff00U)

#define UART_TCR_RX_FIFO_TRIG_HALT_SHIFT                                                                    (0U)
#define UART_TCR_RX_FIFO_TRIG_HALT_MASK                                                                     (0x0000000fU)

#define UART_TCR_RX_FIFO_TRIG_START_SHIFT                                                                   (4U)
#define UART_TCR_RX_FIFO_TRIG_START_MASK                                                                    (0x000000f0U)

#define UART_TCR_RESERVED_24_SHIFT                                                                          (8U)
#define UART_TCR_RESERVED_24_MASK                                                                           (0xffffff00U)

#define UART_XOFF2_XOFF_WORD2_SHIFT                                                                         (0U)
#define UART_XOFF2_XOFF_WORD2_MASK                                                                          (0x000000ffU)

#define UART_XOFF2_RESERVED_24_SHIFT                                                                        (8U)
#define UART_XOFF2_RESERVED_24_MASK                                                                         (0xffffff00U)

#define UART_TLR_TX_FIFO_TRIG_DMA_SHIFT                                                                     (0U)
#define UART_TLR_TX_FIFO_TRIG_DMA_MASK                                                                      (0x0000000fU)

#define UART_TLR_RX_FIFO_TRIG_DMA_SHIFT                                                                     (4U)
#define UART_TLR_RX_FIFO_TRIG_DMA_MASK                                                                      (0x000000f0U)

#define UART_TLR_RESERVED_24_SHIFT                                                                          (8U)
#define UART_TLR_RESERVED_24_MASK                                                                           (0xffffff00U)

#define UART_UASR_SPEED_SHIFT                                                                               (0U)
#define UART_UASR_SPEED_MASK                                                                                (0x0000001fU)
#define UART_UASR_SPEED_SPEED_VALUE_10                                                                       (10U)
#define UART_UASR_SPEED_SPEED_VALUE_9                                                                        (9U)
#define UART_UASR_SPEED_SPEED_VALUE_8                                                                        (8U)
#define UART_UASR_SPEED_SPEED_VALUE_7                                                                        (7U)
#define UART_UASR_SPEED_SPEED_VALUE_6                                                                        (6U)
#define UART_UASR_SPEED_SPEED_VALUE_5                                                                        (5U)
#define UART_UASR_SPEED_SPEED_VALUE_4                                                                        (4U)
#define UART_UASR_SPEED_SPEED_VALUE_3                                                                        (3U)
#define UART_UASR_SPEED_SPEED_VALUE_2                                                                        (2U)
#define UART_UASR_SPEED_SPEED_VALUE_1                                                                        (1U)
#define UART_UASR_SPEED_SPEED_VALUE_0                                                                        (0U)

#define UART_UASR_BIT_BY_CHAR_SHIFT                                                                         (5U)
#define UART_UASR_BIT_BY_CHAR_MASK                                                                          (0x00000020U)
#define UART_UASR_BIT_BY_CHAR_BIT_BY_CHAR_U_VALUE_1                                                          (1U)
#define UART_UASR_BIT_BY_CHAR_BIT_BY_CHAR_U_VALUE_0                                                          (0U)

#define UART_UASR_PARITY_TYPE_SHIFT                                                                         (6U)
#define UART_UASR_PARITY_TYPE_MASK                                                                          (0x000000c0U)
#define UART_UASR_PARITY_TYPE_PARITY_TYPE_U_VALUE_3                                                          (3U)
#define UART_UASR_PARITY_TYPE_PARITY_TYPE_U_VALUE_2                                                          (2U)
#define UART_UASR_PARITY_TYPE_PARITY_TYPE_U_VALUE_1                                                          (1U)
#define UART_UASR_PARITY_TYPE_PARITY_TYPE_U_VALUE_0                                                          (0U)

#define UART_UASR_RESERVED_24_SHIFT                                                                         (8U)
#define UART_UASR_RESERVED_24_MASK                                                                          (0xffffff00U)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_UART_H_ */
