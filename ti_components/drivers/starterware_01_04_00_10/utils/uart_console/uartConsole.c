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
#include "stdint.h"
#include "common/stw_dataTypes.h"
#include "soc_defines.h"
#include "uartConsole.h"
#include "uart.h"
#include "hw_uart.h"
#include "soc.h"

uint32_t uart_base_address;

uint32_t UART_Init(UART_INST_t num)
{
    uint32_t divisorValue = 0, fifoConfig = 0;
    Bool     retVal       = TRUE;

    switch (num)
    {
        case UART1_INST:
            uart_base_address = SOC_UART1_BASE;
            break;
        case UART2_INST:
            uart_base_address = SOC_UART2_BASE;
            break;
        case UART3_INST:
            uart_base_address = SOC_UART3_BASE;
            break;
#ifndef TDA3XX_FAMILY_BUILD
        case UART4_INST:
            uart_base_address = SOC_UART4_BASE;
            break;
        case UART5_INST:
            uart_base_address = SOC_UART5_BASE;
            break;
        case UART6_INST:
            uart_base_address = SOC_UART6_BASE;
            break;
#ifdef TDA2XX_FAMILY_BUILD
        case UART7_INST:
            uart_base_address = SOC_UART7_BASE;
            break;
        case UART8_INST:
            uart_base_address = SOC_UART8_BASE;
            break;
        case UART9_INST:
            uart_base_address = SOC_UART9_BASE;
            break;
        case UART10_INST:
            uart_base_address = SOC_UART10_BASE;
            break;
#endif
#endif
        default:
            retVal = FALSE;
            break;
    }
    if (retVal != FALSE)
    {
        /* Performing a module reset. */
        UARTModuleReset(uart_base_address);

        /* Performing FIFO configurations. */
        /*
        ** - Transmit Trigger Level Granularity is 4
        ** - Receiver Trigger Level Granularity is 1
        ** - Transmit FIFO Space Setting is 56. Hence TX Trigger level
        **   is 8 (64 - 56). The TX FIFO size is 64 bytes.
        ** - The Receiver Trigger Level is 1.
        ** - Clear the Transmit FIFO.
        ** - Clear the Receiver FIFO.
        ** - DMA Mode enabling shall happen through SCR register.
        ** - DMA Mode 0 is enabled. DMA Mode 0 corresponds to No
        **   DMA Mode. Effectively DMA Mode is disabled.
        */
        fifoConfig = UART_FIFO_CONFIG(UART_TRIG_LVL_GRANULARITY_4,
                                      UART_TRIG_LVL_GRANULARITY_1,
                                      UART_FCR_TX_TRIG_LVL_56,
                                      1U,
                                      1U,
                                      1U,
                                      UART_DMA_EN_PATH_SCR,
                                      UART_DMA_MODE_0_ENABLE);

        /* Configuring the FIFO settings. */
        UARTFIFOConfig(uart_base_address, fifoConfig);

        /* Performing Baud Rate settings. */
        /* Computing the Divisor Value. */
        divisorValue = UARTDivisorValCompute(UART_MODULE_INPUT_CLK,
                                             BAUD_RATE,
                                             OPER_MODE,
                                             UART_MIR_OVERSAMPLING_RATE_42);
        /* Programming the Divisor Latches. */
        UARTDivisorLatchWrite(uart_base_address, divisorValue);

        /* Switching to Configuration Mode B. */
        UARTRegConfigModeEnable(uart_base_address, UART_REG_CONFIG_MODE_B);

        /* Programming the Line Characteristics. */
        UARTLineCharacConfig(uart_base_address,
                             (UART_FRAME_WORD_LENGTH_8 | UART_FRAME_NUM_STB_1),
                             UART_PARITY_NONE);

        /* Disabling write access to Divisor Latches. */
        UARTDivisorLatchDisable(uart_base_address);

        /* Disabling Break Control. */
        UARTBreakCtl(uart_base_address, UART_BREAK_COND_DISABLE);

        /* Uart enable */
        UARTOperatingModeSelect(uart_base_address, OPER_MODE);

        /* Debug */
        UARTOperatingModeSelect(uart_base_address, OPER_MODE);
    }
    return ((uint32_t) retVal);
}

/*
** A wrapper function for putting data on Uart Console.
*/
void UARTConsolePutc(uint8_t data)
{
    UARTCharPut(uart_base_address, data);
}

/*
** A wrapper function for getting data from Uart Console.
*/
uint8_t UARTConsoleGetc(void)
{
    return (uint8_t) UARTCharGet(uart_base_address);
}

/*
** A wrapper function performing UART console init operations.
*/
void UARTConsoleInit(UART_INST_t num)
{
    UART_Init(num);
}

/*
** A wrapper function performing UART wait operation.
*/
void UARTConsoleWaitUntilTransmitComplete(void)
{
    /*
    ** Waits indefinitely until the THR and Transmitter Shift Registers are
    ** empty.
    */
    while ((uint32_t) (TRUE) != UARTIsTransmitterEmpty(uart_base_address))
    {
        /* Do nothing - Busy wait */
    }
}

