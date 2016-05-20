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

#ifdef BUILD_A15
#define I2C_INT_NUM                   (56U)
#ifdef TDA2EX_BUILD
#define I2C5_INT_NUM                  (60U)
#else
#define I2C2_INT_NUM                  (57U)
#endif
#endif

/***********************************************************************/
/*                   INTERNAL VARIABLE DEFINITION                      */
/***********************************************************************/
volatile uint32_t intStatus = 1;
uint8_t           data_tx[4];
uint8_t           data_rx[4];
unsigned int      SLAVE_ADDR_1;

/*******************************************************************************
**                   INTERNAL FUNCTION PROTOTYPE
*******************************************************************************/

void test_EEPROM(hsI2cHandle i2cHandle);
void test_TEMP(hsI2cHandle i2cHandle);
void get_temp();
void read_PMIC_id(hsI2cHandle i2cHandle);
void set_PMIC(hsI2cHandle i2cHandle);
void test_GPIO_EXP(hsI2cHandle i2cHandle);
void test_GPIO_EXP2(hsI2cHandle i2cHandle2);

void SetupI2CTransmit(void);

uint32_t I2C_2_ReadTest(hsI2cHandle i2cHandle2);
uint32_t I2CWriteTest(hsI2cHandle i2cHandle);
uint32_t I2CReadTest(hsI2cHandle i2cHandle, unsigned int len1,
                     unsigned int len2);
void i2c_callback(hsI2cHandle i2cHandle, LLD_hsi2cErrorCode_t status,
                  void *appData);
void i2c2_callback(hsI2cHandle i2cHandle2, LLD_hsi2cErrorCode_t status,
                   void *appData);

void sampleDelay(uint32_t delay);
void sampleDelay1(int32_t delay);

int main()
{
    hsI2cHandle           i2cHandle, i2cHandle2;
    lld_hsi2c_initParam_t initPar, initPar2;
    hsI2cObjHandle        i2cObjHandle;
    LLD_Hsi2cInstId_t     i2cInstId;

    /*Unlock the Control registers */
    PlatformUnlockMMR();

    PlatformUART1SetPinMux();

    UARTStdioInit();

    Intc_Init();
    Intc_IntEnable(0);

    initPar.i2cIntNum  = I2C_INT_NUM;
    initPar.i2cBusFreq = I2C_NORMAL;

#ifdef TDA2EX_BUILD
    initPar2.i2cIntNum = I2C5_INT_NUM;
    i2cInstId          = HSI2C_INST_4;
    PlatformI2C5SetPinMux();
#else
    initPar2.i2cIntNum = I2C2_INT_NUM;
    i2cInstId          = HSI2C_INST_1;
    PlatformI2C2SetPinMux();
#endif
    initPar2.i2cBusFreq = I2C_NORMAL;

    initPar.opMode  = HSI2C_OPMODE_INTERRUPT;
    initPar2.opMode = HSI2C_OPMODE_INTERRUPT;

    /*initPar.i2cOwnAddr   = 0xFE;*/
    initPar.is10BitAddr  = 0;
    initPar.isMasterMode = 1;

    initPar2.is10BitAddr  = 0;
    initPar2.isMasterMode = 1;

    lld_i2c_init(&i2cObjHandle, HSI2C_INST_0, &initPar);
    lld_i2c_init(&i2cObjHandle, i2cInstId, &initPar2);

    i2cHandle  = lld_i2c_open(HSI2C_INST_0, i2c_callback, NULL);
    i2cHandle2 = lld_i2c_open(i2cInstId, i2c2_callback, NULL);

    Intc_IntRegister(initPar.i2cIntNum, initPar.i2cIsr, i2cHandle);
    Intc_IntPrioritySet(initPar.i2cIntNum, 1, 0);
    Intc_SystemEnable(initPar.i2cIntNum);

    Intc_IntRegister(initPar2.i2cIntNum, initPar2.i2cIsr, i2cHandle2);
    Intc_IntPrioritySet(initPar2.i2cIntNum, 1, 0);
    Intc_SystemEnable(initPar2.i2cIntNum);
    test_EEPROM(i2cHandle);
    UARTPuts("\n \n", -1);
    test_TEMP(i2cHandle);
    UARTPuts("\n \n", -1);
    read_PMIC_id(i2cHandle);
    UARTPuts("\n \n", -1);
    set_PMIC(i2cHandle);
    UARTPuts("\n \n", -1);
    test_GPIO_EXP(i2cHandle);
    UARTPuts("\n \n", -1);
    test_GPIO_EXP2(i2cHandle2);
    lld_i2c_close(&i2cHandle);
    lld_i2c_close(&i2cHandle2);

    lld_i2c_deinit(HSI2C_INST_0);
    lld_i2c_deinit(i2cInstId);

    /*UARTPuts("\nI2c Test successfull ", -1);*/
    return 0;
}

void i2c_callback(hsI2cHandle i2cHandle, LLD_hsi2cErrorCode_t status,
                  void *appData)
{
    intStatus = 0;

    if (LLD_HSI2C_SUCCESS == status)
    {
        /*UARTPuts("\nISR Called. I2C TX/RX Successfull", -1);*/
    }
    else
    {
        UARTPuts("\nISR Called. I2C TX/RX Failed", -1);
    }
}

void i2c2_callback(hsI2cHandle i2cHandle2, LLD_hsi2cErrorCode_t status,
                   void *appData)
{
    intStatus = 0;

    if (LLD_HSI2C_SUCCESS == status)
    {
        /*UARTPuts("\nISR Called. I2C TX/RX Successfull", -1);*/
    }
    else
    {
        UARTPuts("\nISR Called. I2C TX/RX Failed", -1);
    }
}

void sampleDelay(uint32_t delay)
{
    volatile uint32_t delay1 = delay;
    while (delay1--) ;
}

void sampleDelay1(int32_t delay)
{
    volatile int32_t i, j;

    for (i = 0; i < delay; i++)
    {
        for (j = 0; j < 100; j++) ;
    }
}

uint32_t I2CWriteTest(hsI2cHandle i2cHandle)
{
    uint32_t retVal = LLD_HSI2C_SUCCESS;
    lld_hsi2c_datatfr_params_t i2cXferParams;

    i2cXferParams.bufLen = 3;
    i2cXferParams.buffer = &data_tx[0];

    i2cXferParams.flags = LLD_HSI2C_WRITE | LLD_HSI2C_MASTER |
                          LLD_HSI2C_START | LLD_HSI2C_STOP;
    i2cXferParams.slaveAddr = (uint8_t) SLAVE_ADDR_1;
    i2cXferParams.timeout   = 4000;

    retVal = lld_i2c_transfer(i2cHandle, &i2cXferParams);

    while (intStatus) ;
    intStatus = 1;

    if (LLD_HSI2C_SUCCESS != retVal)
    {
        UARTPuts("\nI2c write failed ", -1);
    }
    else
    {
        /*UARTPuts("\nI2c write successfull ", -1);*/
    }

    return retVal;
}

uint32_t I2CReadTest(hsI2cHandle i2cHandle, unsigned int len1,
                     unsigned int len2)
{
    uint32_t retVal = LLD_HSI2C_SUCCESS;
    lld_hsi2c_datatfr_params_t i2cXferParams;

    i2cXferParams.bufLen = len1;
    i2cXferParams.buffer = &data_tx[0];

    i2cXferParams.flags = LLD_HSI2C_WRITE | LLD_HSI2C_MASTER |
                          LLD_HSI2C_START /*| LLD_HSI2C_STOP*/;
    i2cXferParams.slaveAddr = (uint8_t) SLAVE_ADDR_1;
    i2cXferParams.timeout   = 4000;

    retVal = lld_i2c_transfer(i2cHandle, &i2cXferParams);

    while (intStatus) ;
    intStatus = 1;

    if (LLD_HSI2C_SUCCESS != retVal)
    {
        UARTPuts("\nI2c write failed ", -1);
    }
    else
    {
        /*UARTPuts("\nI2c write successfull ", -1);*/
    }

    i2cXferParams.slaveAddr = (uint8_t) SLAVE_ADDR_1;
    i2cXferParams.bufLen    = len2;
    i2cXferParams.buffer    = &data_rx[0];
    i2cXferParams.flags     = LLD_HSI2C_READ | LLD_HSI2C_MASTER |
                              LLD_HSI2C_START | LLD_HSI2C_STOP |
                              LLD_HSI2C_IGNORE_BUS_BUSY;
    retVal = lld_i2c_transfer(i2cHandle, &i2cXferParams);

    while (intStatus) ;
    intStatus = 1;

    if (LLD_HSI2C_SUCCESS != retVal)
    {
        UARTPuts("\nI2c read failed ", -1);
    }
    else
    {
        /*UARTPuts("\nI2c read successfull ", -1);*/
    }

    return retVal;
}

uint32_t I2C_2_ReadTest(hsI2cHandle i2cHandle2)
{
    uint32_t retVal = LLD_HSI2C_SUCCESS;
    lld_hsi2c_datatfr_params_t i2cXferParams;

    i2cXferParams.timeout   = 4000;
    i2cXferParams.slaveAddr = (uint8_t) SLAVE_ADDR_1;
    i2cXferParams.bufLen    = 2;
    i2cXferParams.buffer    = &data_rx[0];
    i2cXferParams.flags     = LLD_HSI2C_READ | LLD_HSI2C_MASTER |
                              LLD_HSI2C_START | LLD_HSI2C_STOP |
                              LLD_HSI2C_IGNORE_BUS_BUSY;
    retVal = lld_i2c_transfer(i2cHandle2, &i2cXferParams);

    while (intStatus) ;
    intStatus = 1;

    if (LLD_HSI2C_SUCCESS != retVal)
    {
        UARTPuts("\nI2c read failed ", -1);
    }
    else
    {
        UARTPuts("\nI2c read successfull ", -1);
    }
    return retVal;
}

void test_EEPROM(hsI2cHandle i2cHandle)
{
#ifdef TDA2EX_BUILD
    SLAVE_ADDR_1 = 0x51;
#else
    SLAVE_ADDR_1 = 0x50;
#endif
    if (LLD_HSI2C_SUCCESS == lld_i2c_probe(i2cHandle, SLAVE_ADDR_1))
    {
        UARTPuts("\n eeprom_test: ", -1);
        /*write a byte data to EEPROM*/
        data_tx[0] = 0x00;       /*address byte msb*/
        data_tx[1] = 0x45;       /*address byte lsb*/
        data_tx[2] = 0xFE;       /*data*/
        I2CWriteTest(i2cHandle);
        sampleDelay(8000);
        UARTPuts("\n write Test successfull ", -1);
        /*read a byte data from EEPROM*/
        data_tx[0] = 0x00;     /*address byte msb*/
        data_tx[1] = 0x45;     /*address byte lsb*/
        data_rx[0] = 0x00;

        I2CReadTest(i2cHandle, 2, 1);

        if (data_rx[0] == data_tx[2])
        {
            UARTPuts("\nI2c read/write successfull ", -1);
            UARTPutHexNum(data_rx[0]);
        }
        /*  sampleDelay(8000);  */
        UARTPuts("\n EEPROM read Test successfull ", -1);
    }
    else
    {
        UARTPuts("\n slave id Test fail ", -1);
    }
}

void test_TEMP(hsI2cHandle i2cHandle)
{
    SLAVE_ADDR_1 = 0x48;

    if (LLD_HSI2C_SUCCESS == lld_i2c_probe(i2cHandle, SLAVE_ADDR_1))
    {
        UARTPuts("\n temperature_test: ", -1);

        /*read a byte data from EEPROM*/
        data_tx[0] = 0x00;     /*address byte msb*/

        I2CReadTest(i2cHandle, 1, 2);
        /*  sampleDelay(8000);  */
        UARTPuts("\n TEMPERATURE read Test success ", -1);
        get_temp();
    }
    else
    {
        UARTPuts("\n slave id Test fail ", -1);
    }
}

void get_temp()
{
    unsigned int temp, temp1;
    temp  = data_rx[0];
    temp  = temp << 4;
    temp1 = data_rx[1] >> 4;
    temp  = temp | temp1;

    temp1 = temp * 625; /*convert the hex number to tempurature degrees*/
    temp1 = temp1 / 10000;
    UARTPuts("\n temperature is: ", -1);
    UARTPutNum(temp1);
    UARTPuts(" degree C ", -1);
}

void read_PMIC_id(hsI2cHandle i2cHandle)
{
    SLAVE_ADDR_1 = 0x59;

    if (LLD_HSI2C_SUCCESS == lld_i2c_probe(i2cHandle, SLAVE_ADDR_1))
    {
        UARTPuts("\n pmic reading id: ", -1);

        /*   VENDOR_ID_LSB   */
        data_tx[1] = 0x02;     /*address byte msb*/
        data_tx[0] = 0x4F;
        I2CReadTest(i2cHandle, 2, 1);
        /*  sampleDelay(8000);  */
        UARTPuts("\n VENDOR_ID_LSB: ", -1);
        UARTPutHexNum(data_rx[0]);

        /*   VENDOR_ID_MSB   */
        data_tx[1] = 0x02;     /*address byte msb*/
        data_tx[0] = 0x50;
        I2CReadTest(i2cHandle, 2, 1);
        /*  sampleDelay(8000);  */
        UARTPuts("\n VENDOR_ID_MSB: ", -1);
        UARTPutHexNum(data_rx[0]);

        /*   PRODUCT_ID_LSB   */
        data_tx[1] = 0x02;     /*address byte msb*/
        data_tx[0] = 0x51;
        I2CReadTest(i2cHandle, 2, 1);
        /*  sampleDelay(8000);  */
        UARTPuts("\n PRODUCT_ID_LSB: ", -1);
        UARTPutHexNum(data_rx[0]);

        /*   PRODUCT_ID_MSB   */
        data_tx[1] = 0x02;     /*address byte msb*/
        data_tx[0] = 0x52;
        I2CReadTest(i2cHandle, 2, 1);
        /*  sampleDelay(8000);  */
        UARTPuts("\n PRODUCT_ID_MSB: ", -1);
        UARTPutHexNum(data_rx[0]);
        UARTPuts("\n PMIC ID read Test success ", -1);
    }
    else
    {
        UARTPuts("\n slave id Test fail ", -1);
    }
}

void set_PMIC(hsI2cHandle i2cHandle)
{
    SLAVE_ADDR_1 = 0x58;

    data_tx[0] = 0x23;  /*address byte*/
    data_tx[1] = 0x44;  /* making it to 1.12v*/

    I2CWriteTest(i2cHandle);
    /*  sampleDelay(8000);  */
    /*  sampleDelay(8000);  */
    /*  sampleDelay(8000);  */

    data_tx[0] = 0x23;
    I2CReadTest(i2cHandle, 1, 1);
    if (data_rx[0] == 0x44)
    {
        UARTPuts("\n PMIC WRITE/READ Test success ", -1);
        UARTPutHexNum(data_rx[0]);
    }
}

void test_GPIO_EXP(hsI2cHandle i2cHandle)
{
    uint32_t num;
    uint32_t HSI2C_LED_TOGGLE_NO = 10;

    SLAVE_ADDR_1 = 0x20;

    if (LLD_HSI2C_SUCCESS == lld_i2c_probe(i2cHandle, SLAVE_ADDR_1))
    {
        UARTPuts("\nTOGGLE LED'S ON GPIO_EXPANDER .. \n ", -1);
        for (num = HSI2C_LED_TOGGLE_NO; num != 0; num--)
        {
            data_tx[0] = 0x00;
            data_tx[1] = 0x00;
            I2CWriteTest(i2cHandle);
            sampleDelay1(0xFFF);

            data_tx[0] = 0xFF;
            data_tx[1] = 0xFF;
            I2CWriteTest(i2cHandle);
            sampleDelay1(0xFFF);
        }
        UARTPuts("\nTOGGLE LED'S DONE .. \n ", -1);
    }
    else
    {
        UARTPuts("\n slave id Test fail ", -1);
    }
}

void test_GPIO_EXP2(hsI2cHandle i2cHandle2)
{
    SLAVE_ADDR_1 = 0x26;

    if (LLD_HSI2C_SUCCESS == lld_i2c_probe(i2cHandle2, SLAVE_ADDR_1))
    {
        UARTPuts("\n testing GPIO_EXPANDER_2: \n ", -1);
        /*write a byte data to EEPROM*/
        data_tx[0] = 0x00;   /*address byte msb*/
        data_tx[1] = 0x00;   /*address byte lsb*/
        I2CWriteTest(i2cHandle2);
        /*  sampleDelay(8000);  */
        /*read a byte data from EEPROM*/
        I2C_2_ReadTest(i2cHandle2);
        if (data_rx[0] == 0x00 && data_rx[1] == 0x00)
        {
            UARTPuts("\nWRITE/READ Test successfull ", -1);
            UARTPutHexNum(data_rx[0]);
            UARTPutHexNum(data_rx[1]);
        }
        /*  sampleDelay(8000);  */

        data_tx[0] = 0xFF;   /*address byte msb*/
        data_tx[1] = 0xFF;   /*address byte lsb*/
        I2CWriteTest(i2cHandle2);
        /*  sampleDelay(8000);  */
        /*read a byte data from EEPROM*/
        I2C_2_ReadTest(i2cHandle2);
        if (data_rx[0] == 0xFF && data_rx[1] == 0xFF)
        {
            UARTPuts("\nWRITE/READ Test2 successfull ", -1);
            UARTPutHexNum(data_rx[0]);
            UARTPutHexNum(data_rx[1]);
        }
        /*  sampleDelay(8000);  */
    }
    else
    {
        UARTPuts("\n slave id Test fail ", -1);
    }
}

