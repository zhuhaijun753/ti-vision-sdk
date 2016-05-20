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

#define UART_INST_NUM                    (3U)

#if !(defined (TDA3XX_FAMILY_BUILD))
#define HSI2C_SLAVE_ADDR 0x21
#define SEL_UART3_SPI2   0x0E
#define UART_SEL1_3      0x0C

uint32_t dataToSlave = 0;
#endif

#if !(defined (TDA3XX_FAMILY_BUILD))

void sampleDelay(int32_t delay)
{
    volatile int32_t i, j;

    for (i = 0; i < delay; i++)
    {
        for (j = 0; j < 1000; j++) ;
    }
}

void SetupI2C(void)
{
    /* Do a software reset */
    I2CSoftReset(SOC_I2C1_BASE);

    /* Enable i2c module */
    I2CMasterEnable(SOC_I2C1_BASE);

    while (!I2CSystemStatusGet(SOC_I2C1_BASE)) ;

    /* Put i2c in reset/disabled state */
    I2CMasterDisable(SOC_I2C1_BASE);

    /* Configure i2c bus speed to 100khz */
    I2CMasterInitExpClk(SOC_I2C1_BASE, 24000000, 8000000, 100000);

    I2COwnAddressSet(SOC_I2C1_BASE, 0, I2C_OWN_ADDR_0);

    I2CSyscInit(SOC_I2C1_BASE, 0x08);

    /* Set Rx and Tx FIFO threshold value and reset the fifo */
    I2CFIFOThresholdConfig(SOC_I2C1_BASE, 0, I2C_TX_MODE);

    I2CFIFOThresholdConfig(SOC_I2C1_BASE, 0, I2C_RX_MODE);

    /* Set i2c slave address */
    I2CMasterSlaveAddrSet(SOC_I2C1_BASE, HSI2C_SLAVE_ADDR);

    /* Bring i2c out of reset */
    I2CMasterEnable(SOC_I2C1_BASE);

    /* Enable free run mode */
    I2CMasterEnableFreeRun(SOC_I2C1_BASE);
}

uint32_t I2CRead()
{
    uint8_t  i2cReadByte[2];
    uint32_t i2cReadVal;

    /* Set i2cReadByte count */
    I2CSetDataCount(SOC_I2C1_BASE, 2);

    /*
    ** Configure i2c as master-Receiver and to generate stop condition
    */
    I2CMasterControl(SOC_I2C1_BASE,
                     I2C_CFG_MST_RX | I2C_CFG_STOP | I2C_CFG_START);

    /* Wait for receive interrupt to occur */
    while (I2CMasterIntRawStatusEx(SOC_I2C1_BASE,
                                   I2C_INT_RECV_READY) != I2C_INT_RECV_READY) ;

    /* Disable transmit ready */
    I2CMasterIntClearEx(SOC_I2C1_BASE, I2C_INT_RECV_READY);

    /* Read i2cReadByte */
    i2cReadByte[0] = I2CMasterDataGet(SOC_I2C1_BASE);

    sampleDelay(50);

    /* Wait for receive interrupt to occur */
    while (I2CMasterIntRawStatusEx(SOC_I2C1_BASE,
                                   I2C_INT_RECV_READY) != I2C_INT_RECV_READY) ;

    /* Disable transmit ready */
    I2CMasterIntClearEx(SOC_I2C1_BASE, I2C_INT_RECV_READY);

    i2cReadByte[1] = I2CMasterDataGet(SOC_I2C1_BASE);

    I2CFlushFifo(SOC_I2C1_BASE);

    /* Clear all interrupt status */
    I2CMasterIntClearEx(SOC_I2C1_BASE, I2C_INT_ALL);

    /* Clear i2cReadByte buffer length */
    I2CSetDataCount(SOC_I2C1_BASE, 0);

    i2cReadVal = (i2cReadByte[0] | (i2cReadByte[1] << 8));

    return i2cReadVal;
}

void SetupI2CTransmit(void)
{
    /* Set data count */
    I2CSetDataCount(SOC_I2C1_BASE, 2);

    /*
    ** Configure i2c as master-transmitter and to generate stop condition
    */
    I2CMasterControl(SOC_I2C1_BASE,
                     I2C_CFG_MST_TX | I2C_CON_STP_STP | I2C_CFG_START);

    /* Wait for transmit interrupt to occur */
    while (I2CMasterIntRawStatusEx(SOC_I2C1_BASE,
                                   I2C_INT_TRANSMIT_READY) != 0x10) ;

    /* Disable transmit ready and stop condition interrupt */
    I2CMasterIntClearEx(SOC_I2C1_BASE,
                        I2C_INT_TRANSMIT_READY | I2C_INT_STOP_CONDITION);

    /* Send first command word and then the data */
    I2CMasterDataPut(SOC_I2C1_BASE, (dataToSlave & 0xFF));

    /* Wait for transmit interrupt to occur */
    while (I2CMasterIntRawStatusEx(SOC_I2C1_BASE,
                                   I2C_INT_TRANSMIT_READY) != 0x10) ;

    /* Disable transmit ready and stop condition interrupt */
    I2CMasterIntClearEx(SOC_I2C1_BASE,
                        I2C_INT_TRANSMIT_READY | I2C_INT_STOP_CONDITION);

    I2CMasterDataPut(SOC_I2C1_BASE, ((dataToSlave >> 8) & 0xFF));

    sampleDelay(50);

    I2CFlushFifo(SOC_I2C1_BASE);

    /*Clear all interrupt status*/
    I2CMasterIntClearEx(SOC_I2C1_BASE, I2C_INT_ALL);

    /*Clear data buffer length*/
    I2CSetDataCount(SOC_I2C1_BASE, 0);
}

#endif

int main(void)
{
    char     dataBuffer[100];
    int32_t  retVal = STW_SOK;
#if !(defined (TDA3XX_FAMILY_BUILD))
    uint32_t i2cReadValue = 0;
#endif

    /*Enable the module - uart3*/
    retVal = PMHALModuleModeSet(PMHAL_PRCM_MOD_UART3,
                                PMHAL_PRCM_MODULE_MODE_ENABLED,
                                PM_TIMEOUT_INFINITE);

    if (retVal != PM_SUCCESS)
    {
        UARTPuts("\n Uart3 Module enable - error", -1);
        return STW_EFAIL;
    }
    /* PinMux Configuration for UART*/
    BOARDConfigConsolePinMux(DEVICE_UART_INST_ID_3);

#if defined (TDA2XX_FAMILY_BUILD)

    /*
    ** In order to select UART3 set UART_SEL1_3 pin to high
    ** and SEL_UART3_SPI2 pin to low using I2C
    */

    /* Set up I2C communication with I/O expander U57 using I2C1 */
    SetupI2C();

    /* Read the pins of I/O expander */
    i2cReadValue = I2CRead();

    /* Set UART_SEL1_3 pin to high */
    dataToSlave = ((i2cReadValue & 0xEFFF) | (0x1 << UART_SEL1_3));

    /* Set SEL_UART3_SPI2 pin to high */
    dataToSlave = ((dataToSlave & 0xBFFF) | (0x0 << SEL_UART3_SPI2));

    /* Transmit data to I/O expander through bus */
    SetupI2CTransmit();
#else /*TDA3XX_FAMILY_BUILD*/

    /* No need to configure IO Expander mux */

#endif

    /* Set the UART Parameters */
    UARTConfigInit(SOC_UART3_BASE, BAUD_RATE_115200, UART_WORD_LENGTH_8,
                   UART_STOP_BIT_1, UART_NO_PARITY, UART_16x_MODE);

    /* UART receive and transmit operation */
    UARTConfigPuts(SOC_UART3_BASE, "\nUART3 Test", -1);

    UARTConfigPuts(SOC_UART3_BASE, "\nEnter some data to transmit:", -1);

    UARTConfigGets(SOC_UART3_BASE, &dataBuffer[0], -1);

    UARTConfigPuts(SOC_UART3_BASE, "\nData Received:", -1);

    UARTConfigPuts(SOC_UART3_BASE, &dataBuffer[0], -1);

    UARTConfigPuts(SOC_UART3_BASE, "\nUART3 Test Completed", -1);

    return 0;
}

