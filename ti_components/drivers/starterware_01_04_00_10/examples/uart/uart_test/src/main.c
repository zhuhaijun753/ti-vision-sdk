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
 * main.c
 */

#include "stdint.h"
#include "stdio.h"
#include "soc.h"
#include "hw_types.h"
#include "soc_defines.h"
#include "platform.h"
#include "uartConfig.h"
#include "hw_ctrl_core_pad_io.h"
#include <common/stw_dataTypes.h>
#include <common/stw_types.h>
#include "i2clib/lld_hsi2c.h"
#include "boards/stw_board.h"
#include "devices/stw_device.h"
#include "stw_boardPriv.h"
#include "pmhal_prcm.h"
#include "pm/pmhal/pmhal_mm.h"

#define TESTCASE_ID     UART_17

#if (TESTCASE_ID == UART_1)
#define BAUD_RATE       BAUD_RATE_9600
#endif

#if (TESTCASE_ID == UART_2)
#define BAUD_RATE       BAUD_RATE_14400
#endif

#if (TESTCASE_ID == UART_3)
#define BAUD_RATE       BAUD_RATE_19200
#endif

#if (TESTCASE_ID == UART_4)
#define BAUD_RATE       BAUD_RATE_38400
#endif

#if (TESTCASE_ID == UART_5)
#define BAUD_RATE       BAUD_RATE_57600
#endif

#if (TESTCASE_ID == UART_6)
#define BAUD_RATE       BAUD_RATE_115200
#endif

#if (TESTCASE_ID == UART_7)
#define BAUD_RATE       BAUD_RATE_230400
#endif

#if (TESTCASE_ID == UART_8)
#define BAUD_RATE       BAUD_RATE_460800
#define UART_MODE       UART_13x_MODE
#endif

#if (TESTCASE_ID == UART_9)
#define BAUD_RATE       BAUD_RATE_921600
#define UART_MODE       UART_13x_MODE
#endif

#if (TESTCASE_ID == UART_10)
#define WORD_LENGTH     UART_WORD_LENGTH_5
#endif

#if (TESTCASE_ID == UART_11)
#define WORD_LENGTH     UART_WORD_LENGTH_6
#endif

#if (TESTCASE_ID == UART_12)
#define WORD_LENGTH     UART_WORD_LENGTH_7
#endif

#if (TESTCASE_ID == UART_13)
#define WORD_LENGTH     UART_WORD_LENGTH_8
#endif

#if (TESTCASE_ID == UART_14)
#define STOP_BIT        UART_STOP_BIT_1
#endif

#if (TESTCASE_ID == UART_15)
#define STOP_BIT        UART_STOP_BIT_1_5_2
#define WORD_LENGTH     UART_WORD_LENGTH_5
#endif

#if (TESTCASE_ID == UART_16)
#define STOP_BIT        UART_STOP_BIT_1_5_2
#endif

#if (TESTCASE_ID == UART_17)
#define PARITY      UART_NO_PARITY
#endif

#if (TESTCASE_ID == UART_18)
#define PARITY      UART_PARITY_ODD
#endif

#if (TESTCASE_ID == UART_19)
#define PARITY      UART_PARTY_EVEN
#endif

#ifndef BAUD_RATE
#define BAUD_RATE       BAUD_RATE_115200
#endif

#ifndef WORD_LENGTH
#define WORD_LENGTH     UART_WORD_LENGTH_8
#endif

#ifndef STOP_BIT
#define STOP_BIT        UART_STOP_BIT_1
#endif

#ifndef PARITY
#define PARITY          UART_NO_PARITY
#endif

#ifndef UART_MODE
#define UART_MODE       UART_16x_MODE
#endif

#define UART_INST_NUM                    (1U)

int main(void)
{
    char     dataBuffer[100];
    uint32_t uartInstId;
    pmhalPrcmModuleId_t pmModInstId;
    uint32_t uartBaseAddr;
    int32_t  retVal = STW_SOK;

    uartInstId   = 1;
    uartBaseAddr = SOC_UART1_BASE;
    pmModInstId  = PMHAL_PRCM_MOD_UART1;

#if defined (TDA3XX_FAMILY_BUILD)
    uartInstId   = 3;
    uartBaseAddr = SOC_UART3_BASE;
    pmModInstId  = PMHAL_PRCM_MOD_UART3;
#endif

    /*Enable the module - uart*/
    retVal = PMHALModuleModeSet(pmModInstId,
                                PMHAL_PRCM_MODULE_MODE_ENABLED,
                                PM_TIMEOUT_INFINITE);
    if (retVal != PM_SUCCESS)
    {
        return STW_EFAIL;
    }

    /* PinMux Configuration for UART*/
    BOARDConfigConsolePinMux(uartInstId);

    /* Set the UART Parameters */
    UARTConfigInit(uartBaseAddr, BAUD_RATE, WORD_LENGTH, STOP_BIT, PARITY,
                   UART_MODE);

    /* UART receive and transmit operation */
    UARTConfigPuts(uartBaseAddr, "\nUART Test", -1);

    UARTConfigPuts(uartBaseAddr, "\nEnter some data to transmit:", -1);

    UARTConfigGets(uartBaseAddr, &dataBuffer[0], -1);

    UARTConfigPuts(uartBaseAddr, "\nData Received:", -1);

    UARTConfigPuts(uartBaseAddr, &dataBuffer[0], -1);

    UARTConfigPuts(uartBaseAddr, "\nUART Test Completed", -1);

    return 0;
}

