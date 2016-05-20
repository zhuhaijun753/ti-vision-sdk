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
#include "i2clib/lld_hsi2c.h"
#include "soc_defines.h"
#include "platform.h"
#include "uartStdio.h"
#include "interrupt.h"
#include "soc.h"

/***********************************************************************/
/*                    INTERNAL MACRO DEFINITION                        */
/***********************************************************************/
#define PMIC_REGISTER                 (0x23)
#define PMIC_VOLATGE_VALUE            (0x44)

#define PMIC_SLAVE_ADDR               (0x58)
#define PMIC_ID_SLAVE_ADDR            (0x59)

/*******************************************************************************
**                   INTERNAL FUNCTION PROTOTYPE
*******************************************************************************/
void sampleDelay(uint32_t delay);

uint32_t setPMICVoltage(hsI2cHandle i2cHandle);
uint32_t verifyPMICVolatge(hsI2cHandle i2cHandle);
void     readPMICId(hsI2cHandle i2cHandle);
uint8_t readId(hsI2cHandle i2cHandle, uint8_t addrMsb, uint8_t addrLsb);

int main()
{
    hsI2cHandle           i2cHandle;
    lld_hsi2c_initParam_t initPar;
    hsI2cObjHandle        i2cObjHandle;

    /*Unlock the Control registers */
    PlatformUnlockMMR();

    PlatformUartConsoleSetPinMux();

    UARTStdioInit();

    Intc_Init();
    Intc_IntEnable(0);

    initPar.i2cBusFreq   = I2C_NORMAL;
    initPar.opMode       = HSI2C_OPMODE_POLLED;
    initPar.is10BitAddr  = 0;
    initPar.isMasterMode = 1;

    lld_i2c_init(&i2cObjHandle, HSI2C_INST_0, &initPar);

    i2cHandle = lld_i2c_open(HSI2C_INST_0, NULL, NULL);

    readPMICId(i2cHandle);

    setPMICVoltage(i2cHandle);

    verifyPMICVolatge(i2cHandle);

    lld_i2c_close(&i2cHandle);

    lld_i2c_deinit(HSI2C_INST_0);

    UARTPuts("\nPMIC test  successful  ", -1);
    return 0;
}

void sampleDelay(uint32_t delay)
{
    volatile uint32_t delay1 = delay;
    while (delay1--) ;
}

void readPMICId(hsI2cHandle i2cHandle)
{
    uint8_t value = 0;

    UARTPuts("\n PMIC Data: ", -1);

    /* Read and print vendor ID LSB data*/
    value = readId(i2cHandle, 0x02, 0x4F);
    UARTPuts("\n VENDOR_ID_LSB: ", -1);
    UARTPutHexNum(value);

    /* Read and print vendor ID MSB data*/
    value = readId(i2cHandle, 0x02, 0x50);
    UARTPuts("\n VENDOR_ID_MSB: ", -1);
    UARTPutHexNum(value);

    /* Read and print product ID LSB data*/
    value = readId(i2cHandle, 0x02, 0x51);
    UARTPuts("\n PRODUCT_ID_LSB: ", -1);
    UARTPutHexNum(value);

    /* Read and print product ID MSB data*/
    value = readId(i2cHandle, 0x02, 0x52);
    UARTPuts("\n PRODUCT_ID_MSB: ", -1);
    UARTPutHexNum(value);
}

uint8_t readId(hsI2cHandle i2cHandle, uint8_t addrMsb, uint8_t addrLsb)
{
    uint32_t retVal = LLD_HSI2C_SUCCESS;
    lld_hsi2c_datatfr_params_t i2cXferParams;
    uint8_t  data[4];

    i2cXferParams.bufLen = 2;
    i2cXferParams.buffer = &data[0];

    /*address byte msb*/
    data[0] = addrLsb;
    /*address byte lsb*/
    data[1] = addrMsb;

    i2cXferParams.flags = LLD_HSI2C_WRITE | LLD_HSI2C_MASTER |
                          LLD_HSI2C_START;
    i2cXferParams.slaveAddr = (uint8_t) PMIC_ID_SLAVE_ADDR;
    i2cXferParams.timeout   = 4000;

    retVal = lld_i2c_transfer(i2cHandle, &i2cXferParams);
    sampleDelay(1000);

    if (LLD_HSI2C_SUCCESS != retVal)
    {
        UARTPuts("\nI2c write failed ", -1);
    }
    else
    {
        /*UARTPuts("\nI2c write successfull ", -1);*/
    }

    i2cXferParams.bufLen = 1; /*read one byte of data*/
    i2cXferParams.flags  = LLD_HSI2C_READ | LLD_HSI2C_MASTER |
                           LLD_HSI2C_START | LLD_HSI2C_STOP |
                           LLD_HSI2C_IGNORE_BUS_BUSY;
    retVal = lld_i2c_transfer(i2cHandle, &i2cXferParams);

    if (LLD_HSI2C_SUCCESS != retVal)
    {
        UARTPuts("\nI2c read failed ", -1);
    }

    return data[0];
}

uint32_t setPMICVoltage(hsI2cHandle i2cHandle)
{
    uint32_t retVal = LLD_HSI2C_SUCCESS;
    lld_hsi2c_datatfr_params_t i2cXferParams;
    uint8_t  data[4];

    i2cXferParams.bufLen = 2;
    i2cXferParams.buffer = &data[0];

    data[0] = PMIC_REGISTER;      /*address byte*/
    data[1] = PMIC_VOLATGE_VALUE; /* making it to 1.12v*/

    i2cXferParams.flags = LLD_HSI2C_WRITE | LLD_HSI2C_MASTER |
                          LLD_HSI2C_START | LLD_HSI2C_STOP;
    i2cXferParams.slaveAddr = (uint8_t) PMIC_SLAVE_ADDR;
    i2cXferParams.timeout   = 4000;

    retVal = lld_i2c_transfer(i2cHandle, &i2cXferParams);

    sampleDelay(2000);

    if (LLD_HSI2C_SUCCESS != retVal)
    {
        UARTPuts("\nI2c write failed ", -1);
    }
    else
    {
        UARTPuts(
            "\nValue 0x44 written to PMIC register 0x23 to set voltage to 1.12V",
            -1);
    }
    return retVal;
}

uint32_t verifyPMICVolatge(hsI2cHandle i2cHandle)
{
    uint32_t retVal = LLD_HSI2C_SUCCESS;
    lld_hsi2c_datatfr_params_t i2cXferParams;
    uint8_t  data[4];

    i2cXferParams.bufLen = 1;
    i2cXferParams.buffer = &data[0];

    data[0] = PMIC_REGISTER; /*data byte*/

    i2cXferParams.flags = LLD_HSI2C_WRITE | LLD_HSI2C_MASTER |
                          LLD_HSI2C_START;
    i2cXferParams.slaveAddr = (uint8_t) PMIC_SLAVE_ADDR;
    i2cXferParams.timeout   = 4000;

    retVal = lld_i2c_transfer(i2cHandle, &i2cXferParams);
    sampleDelay(1000);

    if (LLD_HSI2C_SUCCESS != retVal)
    {
        UARTPuts("\nI2c write failed ", -1);
    }
    else
    {
        /*UARTPuts("\nI2c write successfull ", -1);*/
    }

    i2cXferParams.bufLen = 1; /*read one byte of data*/
    i2cXferParams.flags  = LLD_HSI2C_READ | LLD_HSI2C_MASTER |
                           LLD_HSI2C_START | LLD_HSI2C_STOP |
                           LLD_HSI2C_IGNORE_BUS_BUSY;
    retVal = lld_i2c_transfer(i2cHandle, &i2cXferParams);

    if (LLD_HSI2C_SUCCESS != retVal)
    {
        UARTPuts("\nI2c read failed ", -1);
    }
    else
    {
        if (PMIC_VOLATGE_VALUE == i2cXferParams.buffer[0])
        {
            UARTPuts("\nPMIC voltage set to 1.12V", -1);
        }
        else
        {
            UARTPuts("\nFailed to set PMIC voltage to 1.12V", -1);
        }
    }

    return retVal;
}

