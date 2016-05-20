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
#ifndef TI814X_BUILD
#include "hw_ctrl_core_pad_io.h"
#endif
#include <common/stw_dataTypes.h>
#include <common/stw_types.h>
#include <common/stw_utils.h>
#include "i2clib/lld_hsi2c.h"
#include <devices/stw_device.h>
#include "boards/stw_board.h"
#include "stwutils_app.h"

#define UART_INST_NUM                    (1U)

#if defined (TDA3XX_FAMILY_BUILD)
static int32_t uartBoardInfoGet(uint32_t *uartInstId)
{
    int32_t  status = STW_EFAIL;
    uint32_t dataModId;
    uint32_t dataModInstNum;

    dataModId = BOARDGetDeviceDataModId(DEVICE_ID_UART, UART_INST_NUM);

    if (DEVICE_ID_INVALID == dataModId)
    {
        console_print_string("\nDevice is not available on this board ");
    }
    else if (DEVICE_ID_UART == dataModId)
    {
        dataModInstNum = BOARDGetDeviceDataModInstNum(DEVICE_ID_UART,
                                                      UART_INST_NUM);

        if (INVALID_INST_NUM == dataModInstNum)
        {
            console_print_string("\nInvalid board data ");
        }
        else
        {
            *uartInstId = dataModInstNum;
            status      = STW_SOK;
        }
    }
    else
    {
        console_print_string("\nInvalid board data ");
    }

    return status;
}

int32_t uartModuleInit(uint32_t uartInstId)
{
    int32_t retVal = STW_SOK;

    /* PinMux Configuration for UART */
    BOARDConfigModulePinMux(DEVICE_ID_UART, uartInstId, BOARD_MODE_DEFAULT);

    return retVal;
}

#endif

int main(void)
{
    char               dataBuffer[100];
#if defined (TDA3XX_FAMILY_BUILD)
    stwAppInitParams_t stwAppInitParams;
    int32_t            retVal;
    uint32_t           uartInstId;

    stwAppInitParams.isI2cInitReq  = TRUE;
    stwAppInitParams.isUartInitReq = TRUE;
    retVal = StwUtils_appDefaultInit(stwAppInitParams);
    if (retVal != STW_SOK)
    {
        console_print_string("\nSystem Init Failed ");
    }

    retVal = uartBoardInfoGet(&uartInstId);
    if (retVal != STW_SOK)
    {
        console_print_string("\nUart Board Get Info Failed ");
    }

    retVal = uartModuleInit(uartInstId);
    if (retVal != STW_SOK)
    {
        console_print_string("\nUart Module Init Failed ");
    }

    /* IO Expander mux config for UART1*/
    BOARDSelectDevice(DEVICE_ID_UART, uartInstId);
#else
    PlatformUartConsoleSetPinMux();
#endif

    /* Set the UART Parameters */
    UARTConfigInit(SOC_UART1_BASE, BAUD_RATE_115200, UART_WORD_LENGTH_8,
                   UART_STOP_BIT_1, UART_NO_PARITY, UART_16x_MODE);

    /* UART receive and transmit operation */
    UARTConfigPuts(SOC_UART1_BASE, "\nUART1 Test", -1);

    UARTConfigPuts(SOC_UART1_BASE, "\nEnter some data to transmit:", -1);

    UARTConfigGets(SOC_UART1_BASE, &dataBuffer[0], -1);

    UARTConfigPuts(SOC_UART1_BASE, "\nData Received:", -1);

    UARTConfigPuts(SOC_UART1_BASE, &dataBuffer[0], -1);

    UARTConfigPuts(SOC_UART1_BASE, "\nUART1 Test Completed", -1);

    return 0;
}

