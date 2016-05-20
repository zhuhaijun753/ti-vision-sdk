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
 * \file   uartStdio.h
 *
 * \brief  This file contains the prototypes of the functions present in
 *         utils/src/uartStdio.c
 */

#ifndef UARTSTDIO_H_
#define UARTSTDIO_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************
**                    MACRO DEFINITIONS
****************************************************************************/

/****************************************************************************
**                    FUNCTION PROTOTYPES
****************************************************************************/

extern uint32_t UARTPuts(const char *pTxBuffer, int32_t numBytesToWrite);
extern uint32_t UARTGets(char *pRxBuffer, int32_t numBytesToRead);
extern int32_t UARTwrite(const char *pcBuf, uint32_t len);
extern void UARTprintf(const char *pcString, ...);
extern void UARTPutHexNum(uint32_t hexValue);
extern void UARTPutc(uint8_t byteTx);
extern uint32_t UARTGetHexNum(void);
extern uint8_t UARTGetc(void);
extern void UARTPutNum(int32_t value);
extern void UARTStdioInit(void);
extern int32_t UARTGetNum(void);
extern void UARTWaitUntilTransmitComplete(void);

#ifdef __cplusplus
}
#endif
#endif
