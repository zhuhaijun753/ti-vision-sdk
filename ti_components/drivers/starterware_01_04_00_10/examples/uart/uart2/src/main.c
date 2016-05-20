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
#include "hsi2c.h"
#include "hw_types.h"
#include "soc_defines.h"
#include "platform.h"
#include "uartConfig.h"
#include "hw_ctrl_core_pad_io.h"
#include "hw_l4per_cm_core.h"
#include <common/stw_dataTypes.h>
#include <common/stw_types.h>
#include <common/stw_utils.h>
#include "i2clib/lld_hsi2c.h"
#include <devices/stw_device.h>
#include "boards/stw_board.h"
#include "stwutils_app.h"
#include "stw_boardPriv.h"
#include "pmhal_prcm.h"
#include "pm/pmhal/pmhal_mm.h"

#define UART_INST_NUM                    (2U)

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

    if (uartInstId == DEVICE_UART_INST_ID_2)
    {
        /*Enable the module - uart2*/
        retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_UART2,
                                    PMHAL_PRCM_MODULE_MODE_ENABLED,
                                    PM_TIMEOUT_INFINITE);
        if (retVal != PM_SUCCESS)
        {
            UARTPuts("\n Uart2 Module enable - error", -1);
            return STW_EFAIL;
        }

        /* PinMux Configuration for UART */
        BOARDConfigModulePinMux(DEVICE_ID_UART, uartInstId, BOARD_MODE_DEFAULT);
    }
    else
    {
        retVal = STW_EFAIL;
    }

    return retVal;
}

int main(void)
{
    char               dataBuffer[100];
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

    /* IO Expander mux config for UART2 */
    BOARDSelectDevice(DEVICE_ID_UART, uartInstId);

    /* Set the UART Parameters */
    UARTConfigInit(SOC_UART2_BASE, BAUD_RATE_115200, UART_WORD_LENGTH_8,
                   UART_STOP_BIT_1, UART_NO_PARITY, UART_16x_MODE);

    /* UART receive and transmit operation */
    UARTConfigPuts(SOC_UART2_BASE, "\nUART2 Test", -1);

    UARTConfigPuts(SOC_UART2_BASE, "\nEnter some data to transmit:", -1);

    UARTConfigGets(SOC_UART2_BASE, &dataBuffer[0], -1);

    UARTConfigPuts(SOC_UART2_BASE, "\nData Received:", -1);

    UARTConfigPuts(SOC_UART2_BASE, &dataBuffer[0], -1);

    UARTConfigPuts(SOC_UART2_BASE, "\nUART2 Test Completed", -1);

    return 0;
}

