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
/*  \file uart.h
 *
 *  \brief      This file contains the function prototypes for the device
 *              abstraction layer for UART. It also contains some
 *              related macro definitions and some files to be included.
 */

#ifndef UART_CONSOLE_H_
#define UART_CONSOLE_H_

#include "uart.h"
#include "hw_uart.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ZebuConfig 0

#define BAUD_RATE_115200          (115200U)
#define BAUD_RATE_3686400         (3686400U)
#define UART_MODULE_INPUT_CLK     (48000000U)

/* For UARTConsole to work on Zebu change the baud rate and oper mode */
#if ZebuConfig
#define BAUD_RATE                 (BAUD_RATE_3686400)
#else
#define BAUD_RATE                 (BAUD_RATE_115200)
#endif

#if ZebuConfig
#define OPER_MODE                 (UART13x_OPER_MODE)
#else
#define OPER_MODE                 (UART16x_OPER_MODE)
#endif

#define UART_LCR_NB_STOP_1BIT   (0x0U)
#define UART_LCR_CHAR_LENGTH_8BIT   (0x3U)

void UARTConsolePutc(uint8_t data);
uint8_t UARTConsoleGetc(void);
void UARTConsoleInit(UART_INST_t num);
uint32_t UART_Init(UART_INST_t num);
void UARTConsoleWaitUntilTransmitComplete(void);
#ifdef __cplusplus
}
#endif
#endif

