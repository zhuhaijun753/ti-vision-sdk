/* ======================================================================
 *   Copyright (C) 2013 Texas Instruments Incorporated
 *
 *   All rights reserved. Property of Texas Instruments Incorporated.
 *   Restricted rights to use, duplicate or disclose this code are
 *   granted through contract.
 *
 *   The program may not be used without the written permission
 *   of Texas Instruments Incorporated or against the terms and conditions
 *   stipulated in the agreement under which this program has been
 *   supplied.
 * ==================================================================== */
/*
 * \file   uartConfig.h
 *
 * \brief  This file contains the various macros and prototypes of the functions
 **required
 *         to test the UART1 and UART3.
 */

#ifndef UARTCONFIG_H_
#define UARTCONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "uart.h"

/****************************************************************************
**                    MACRO DEFINITIONS
****************************************************************************/

#define BAUD_RATE_9600              (9600U)
#define BAUD_RATE_14400             (14400U)
#define BAUD_RATE_19200             (19200U)
#define BAUD_RATE_38400             (38400U)
#define BAUD_RATE_57600             (57600U)
#define BAUD_RATE_115200            (115200U)
#define BAUD_RATE_230400            (230400U)
#define BAUD_RATE_460800            (460800U)
#define BAUD_RATE_921600            (921600U)

#define UART_WORD_LENGTH_5          (UART_FRAME_WORD_LENGTH_5)
#define UART_WORD_LENGTH_6          (UART_FRAME_WORD_LENGTH_6)
#define UART_WORD_LENGTH_7          (UART_FRAME_WORD_LENGTH_7)
#define UART_WORD_LENGTH_8          (UART_FRAME_WORD_LENGTH_8)

#define UART_STOP_BIT_1             (UART_FRAME_NUM_STB_1)
#define UART_STOP_BIT_1_5_2         (UART_FRAME_NUM_STB_1_5_2)

#define UART_NO_PARITY              (UART_PARITY_NONE)
#define UART_PARITY_ODD             (UART_ODD_PARITY)
#define UART_PARTY_EVEN             (UART_EVEN_PARITY)

#define UART_13x_MODE               (UART13x_OPER_MODE)
#define UART_16x_MODE               (UART16x_OPER_MODE)

#define UART_MODULE_INPUT_CLK       (48000000U)

/* Macros for Testcase IDs */
#define UART_1      (1U)
#define UART_2      (2U)
#define UART_3      (3U)
#define UART_4      (4U)
#define UART_5      (5U)
#define UART_6      (6U)
#define UART_7      (7U)
#define UART_8      (8U)
#define UART_9      (9U)
#define UART_10     (10U)
#define UART_11     (11U)
#define UART_12     (12U)
#define UART_13     (13U)
#define UART_14     (14U)
#define UART_15     (15U)
#define UART_16     (16U)
#define UART_17     (17U)
#define UART_18     (18U)
#define UART_19     (19U)

/****************************************************************************
**                    FUNCTION PROTOTYPES
****************************************************************************/

extern void UARTConfigInit(uint32_t baseAddr, uint32_t baudRate,
                           uint32_t wordLength,
                           uint32_t stopBit, uint32_t parity,
                           uint32_t mode);
extern void UARTConfigPutc(uint32_t baseAddr, uint8_t byteTx);
extern uint8_t UARTConfigGetc(uint32_t baseAddr);
extern uint32_t UARTConfigPuts(uint32_t baseAddr, char *pTxBuffer,
                               int32_t numBytesToWrite);
extern uint32_t UARTConfigGets(uint32_t baseAddr, char *pRxBuffer,
                               int32_t numBytesToRead);
extern void UARTConfigPutNum(uint32_t baseAddr, int32_t value);
extern int32_t UARTConfigGetNum(uint32_t baseAddr);
extern void UARTConfigPutHexNum(uint32_t baseAddr, uint32_t hexValue);
extern uint32_t UARTConfigGetHexNum(uint32_t baseAddr);

#ifdef __cplusplus
}
#endif
#endif
