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
#include <stdio.h>
#include "hsi2c.h"
#include "soc.h"
#include "soc_defines.h"
#include "platform.h"

/***********************************************************************/
/*                    INTERNAL MACRO DEFINITION                        */
/***********************************************************************/

/* I2C address of PCF8575 expander. */
#define HSI2C_SLAVE_ADDR            ((uint8_t) 0x26U)

/* Turn on the LEDs. */
#define HSI2C_EXP_PORT0_LED_ON      ((uint8_t) 0x00U)

/* Turn off the LEDs. */
#define HSI2C_EXP_PORT0_LED_OFF     (0xF0U)

/* Number of times led toggles. */
#define HSI2C_LED_TOGGLE_NO         (1)

/* Led toggle check value*/
#define HSI2C_LED_TOGGLE_END        (0)

#define HAL_LED_BLINK 1

/***********************************************************************/
/*                   INTERNAL VARIABLE DEFINITION                      */
/***********************************************************************/
uint8_t dataToSlave;

/*******************************************************************************
**                   INTERNAL FUNCTION PROTOTYPE
*******************************************************************************/

void SetupI2C(void);
void sampleDelay(int32_t delay);
void SetupI2CTransmit(void);
void I2CRead(void);

int main()
{
    /*
    ** Configures I2C to Master mode to generate start codition
    ** on I2C bus and to transmit data at a bus speed of  100khz
    */

#if HAL_LED_BLINK

    uint32_t num;

    SetupI2C();

    dataToSlave = HSI2C_EXP_PORT0_LED_ON;
    /*
     * **Transmits command byte and data to I/0 expander
     * **through I2C bus
     */
    SetupI2CTransmit();
    UARTPuts("\nI2c write successful", -1);
    sampleDelay(0xFFF);
    UARTPuts("\nI2c read ", -1);
    I2CRead();
    sampleDelay(0xFFF);

    dataToSlave = HSI2C_EXP_PORT0_LED_OFF;     /*data to OFF LED*/

    SetupI2CTransmit();
    UARTPuts("\nI2c write successful", -1);
    sampleDelay(0xFFF);

    UARTPuts("\nI2c read ", -1);
    I2CRead();
    sampleDelay(0xFFF);

#endif
    return 0;
}

void SetupI2C(void)
{
    /*Pad Mux need to be configured in Supervisor mode*/
    /*PlatformI2CSetPinMux();*/
    /*PlatformI2CClockEnable();*/

    PlatformI2C2SetPinMux();

    /* Do a software reset */
    I2CSoftReset(SOC_I2C2_BASE);

    /* Enable i2c module */
    I2CMasterEnable(SOC_I2C2_BASE);

    while (!I2CSystemStatusGet(SOC_I2C2_BASE)) ;

    /* Put i2c in reset/disabled state */
    I2CMasterDisable(SOC_I2C2_BASE);

    /* Configure i2c bus speed to 100khz */
    I2CMasterInitExpClk(SOC_I2C2_BASE, 24000000,
                        8000000, 100000);

    I2COwnAddressSet(SOC_I2C2_BASE, 0,
                     I2C_OWN_ADDR_0);

    I2CSyscInit(SOC_I2C2_BASE, 0x08);

    /*Set Rx and Tx FIFO threshold value and reset the fifo*/
    I2CFIFOThresholdConfig(SOC_I2C2_BASE, 0, I2C_TX_MODE);

    I2CFIFOThresholdConfig(SOC_I2C2_BASE, 0, I2C_RX_MODE);

    /* Set i2c slave address */
    I2CMasterSlaveAddrSet(SOC_I2C2_BASE, HSI2C_SLAVE_ADDR);

    /* Bring i2c out of reset */
    I2CMasterEnable(SOC_I2C2_BASE);

    /* Enable free run mode */
    I2CMasterEnableFreeRun(SOC_I2C2_BASE);
}

void I2CRead()
{
    uint8_t data[2];

    /* Set data count */
    I2CSetDataCount(SOC_I2C2_BASE, 2);

    /*
    ** Configure i2c as master-Receiver and to generate stop condition
    */
    I2CMasterControl(SOC_I2C2_BASE,
                     I2C_CFG_MST_RX | I2C_CFG_STOP | I2C_CFG_START);

    /*Wait for receive interrupt to occur*/
    while (I2CMasterIntRawStatusEx(SOC_I2C2_BASE,
                                   I2C_INT_RECV_READY) != I2C_INT_RECV_READY) ;
    /*Disable transmit ready*/
    I2CMasterIntClearEx(SOC_I2C2_BASE, I2C_INT_RECV_READY);

    /* Read data */
    data[0] = I2CMasterDataGet(SOC_I2C2_BASE);

    sampleDelay(50);

    /*Wait for receive interrupt to occur*/
    while (I2CMasterIntRawStatusEx(SOC_I2C2_BASE,
                                   I2C_INT_RECV_READY) != I2C_INT_RECV_READY) ;
    /*Disable transmit ready*/
    I2CMasterIntClearEx(SOC_I2C2_BASE, I2C_INT_RECV_READY);

    data[1] = I2CMasterDataGet(SOC_I2C2_BASE);

    /*while (I2CMasterIntRawStatusEx(SOC_I2C2_BASE, I2C_INT_ADRR_READY_ACESS) !=
     *I2C_INT_ADRR_READY_ACESS) ;*/

    I2CFlushFifo(SOC_I2C2_BASE);

    /*Clear all interrupt status*/
    /*I2CMasterIntRawStatusClearEx(SOC_I2C2_BASE, I2C_INT_ALL);*/
    I2CMasterIntClearEx(SOC_I2C2_BASE, I2C_INT_ALL);

    /*Clear data buffer length*/
    I2CSetDataCount(SOC_I2C2_BASE, 0);

    UARTPuts("\nI2c read data 1= ", -1);
    UARTPutHexNum(data[0]);
    UARTPuts(" 2= ", -1);
    UARTPutHexNum(data[1]);
    /*printf("Data0 = %x\n",data[0]);
     * printf("Data1 = %x\n",data[1]);
     * printf("************\n");*/
}

void SetupI2CTransmit(void)
{
    /* Set data count */
    I2CSetDataCount(SOC_I2C2_BASE, 2);

    /*
    ** Configure i2c as master-transmitter and to generate stop condition
    */
    I2CMasterControl(SOC_I2C2_BASE,
                     I2C_CFG_MST_TX | I2C_CON_STP_STP | I2C_CFG_START);

    /*Generate start conndition*/
    /*I2CMasterStart(SOC_I2C2_BASE);*/

    /*Wait for transmit interrupt to occur*/
    while (I2CMasterIntRawStatusEx(SOC_I2C2_BASE,
                                   I2C_INT_TRANSMIT_READY) != 0x10) ;

    /*Disable transmit ready and stop condition interrupt*/
    I2CMasterIntClearEx(SOC_I2C2_BASE,
                        I2C_INT_TRANSMIT_READY | I2C_INT_STOP_CONDITION);

    /* Send first command word and then the data */
    I2CMasterDataPut(SOC_I2C2_BASE, dataToSlave);

    /*Wait for transmit interrupt to occur*/
    while (I2CMasterIntRawStatusEx(SOC_I2C2_BASE,
                                   I2C_INT_TRANSMIT_READY) != 0x10) ;

    /*Disable transmit ready and stop condition interrupt*/
    I2CMasterIntClearEx(SOC_I2C2_BASE,
                        I2C_INT_TRANSMIT_READY | I2C_INT_STOP_CONDITION);

    I2CMasterDataPut(SOC_I2C2_BASE, dataToSlave);

    sampleDelay(50);

    I2CFlushFifo(SOC_I2C2_BASE);

    /*Clear all interrupt status*/
    I2CMasterIntClearEx(SOC_I2C2_BASE, I2C_INT_ALL);

    /*Clear data buffer length*/
    I2CSetDataCount(SOC_I2C2_BASE, 0);
}

void sampleDelay(int32_t delay)
{
    volatile int32_t i, j;

    for (i = 0; i < delay; i++)
    {
        for (j = 0; j < 100; j++) ;
    }
}

