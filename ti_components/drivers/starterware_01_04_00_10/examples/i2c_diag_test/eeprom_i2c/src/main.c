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
#define EXIT(opt)      (('x' == opt) || ('X' == opt))

#if (defined (TDA2XX_BUILD))
#define SLAVE_ADDR_EEPROM_BASE                  (0x50)
#elif (defined (TDA3XX_FAMILY_BUILD)) || (defined (TDA2EX_BUILD))
#define SLAVE_ADDR_EEPROM_BASE                  (0x51)
#endif

#if (defined (TDA2XX_FAMILY_BUILD))
#define BASE_BOARD     ('1')
#define JAMR3_BOARD    ('2')
#define ALL_BOARD(opt) (('a' == opt) || ('A' == opt))
#define SLAVE_ADDR_EEPROM_JAMR3                 (0x51)
#endif

#define EEPROM_READ_SAVE_BLOCK      ('1')
#define EEPROM_VERIFY_BLOCK         ('2')

#define DATA_SIZE                   (64)

/***********************************************************************/
/*                   INTERNAL VARIABLE DEFINITION                      */
/***********************************************************************/
volatile uint8_t saveBlock[64] = {0};

/*******************************************************************************
**                   INTERNAL FUNCTION PROTOTYPE
*******************************************************************************/
void sampleDelay(uint32_t delay);
#if (defined (TDA2XX_FAMILY_BUILD))
void mainMenu(char *option);
#endif
void eepromOptMenu(char *option);
void eepromTest(hsI2cHandle i2cHandle, uint8_t slaveAddr);
void eepromBlockReadSave(hsI2cHandle i2cHandle, uint8_t slaveAddr,
                         uint32_t blockNum);
void eepromBlockVerify(hsI2cHandle i2cHandle, uint8_t slaveAddr,
                       uint32_t blockNum);

int main()
{
    hsI2cHandle           i2cHandle;
    lld_hsi2c_initParam_t initPar;
    hsI2cObjHandle        i2cObjHandle;
#if (defined (TDA2XX_FAMILY_BUILD))
    char mainMenuOption;
#endif
    volatile int8_t       appEnd = 1;

    /*Unlock the Control registers */
    PlatformUnlockMMR();

    PlatformUartConsoleSetPinMux();

    UARTStdioInit();

    /* I2C instance one configuration*/
    initPar.i2cBusFreq = I2C_NORMAL;

    initPar.opMode = HSI2C_OPMODE_POLLED;

    /*initPar.i2cOwnAddr   = 0xFE;*/
    initPar.is10BitAddr  = 0;
    initPar.isMasterMode = 1;

    lld_i2c_init(&i2cObjHandle, HSI2C_INST_0, &initPar);

    i2cHandle = lld_i2c_open(HSI2C_INST_0, NULL, NULL);

    while (1)
    {
#if (defined (TDA2XX_FAMILY_BUILD))
        mainMenu(&mainMenuOption);

        if (BASE_BOARD == mainMenuOption)
        {
            eepromTest(i2cHandle, (uint8_t) SLAVE_ADDR_EEPROM_BASE);
        }
        else if (JAMR3_BOARD == mainMenuOption)
        {
            eepromTest(i2cHandle, (uint8_t) SLAVE_ADDR_EEPROM_JAMR3);
        }
        else if (ALL_BOARD(mainMenuOption))
        {
            UARTPuts("\nEEPROM base board test...", -1);
            eepromTest(i2cHandle, (uint8_t) SLAVE_ADDR_EEPROM_BASE);
            UARTPuts("\nEEPROM JAMR3 board test...", -1);
            eepromTest(i2cHandle, (uint8_t) SLAVE_ADDR_EEPROM_JAMR3);
        }
        else
        {
            UARTPuts("\nEEPROM board diagnostic test exiting...", -1);
            break;
        }
#elif (defined (TDA3XX_FAMILY_BUILD))
        eepromTest(i2cHandle, (uint8_t) SLAVE_ADDR_EEPROM_BASE);
        break;
#endif
    }

    lld_i2c_close(&i2cHandle);
    lld_i2c_deinit(HSI2C_INST_0);

    while (appEnd) ;

    return 0;
}

#if (defined (TDA2XX_FAMILY_BUILD))
void mainMenu(char *option)
{
    while (1)
    {
        UARTPuts("\n\n**** EEPROM TEST ****", -1);
        UARTPuts("\nMenu:", -1);
        UARTPuts("\n1. Base  board test", -1);
        UARTPuts("\n2. JAMR3 board test", -1);
        UARTPuts("\na. Test  All", -1);
        UARTPuts("\nx. Exit", -1);
        UARTPuts("\nSelect test board : ", -1);

        /* Get option */
        UARTGets(option, 1);

        if (BASE_BOARD == *option || JAMR3_BOARD == *option
            || ALL_BOARD(*option) || EXIT(*option))
        {
            break;
        }
        else
        {
            UARTPuts("\nEnter Valid option\n", -1);
        }
    }
}

#endif

void eepromOptMenu(char *option)
{
    while (1)
    {
        UARTPuts("\n\n**** BLOCK TEST ****", -1);
        UARTPuts("\nMenu:", -1);
        UARTPuts("\n1. Block read and Save ", -1);
        UARTPuts("\n2. Block verify", -1);
        UARTPuts("\nx. Exit", -1);
        UARTPuts("\nSelect test type : ", -1);

        /* Get option */
        UARTGets(option, 1);

        if (EEPROM_READ_SAVE_BLOCK == *option || EEPROM_VERIFY_BLOCK == *option
            || EXIT(*option))
        {
            break;
        }
        else
        {
            UARTPuts("\nEnter Valid option\n", -1);
        }
    }
}

void eepromTest(hsI2cHandle i2cHandle, uint8_t slaveAddr)
{
    char     eepromOption;
    uint32_t blockNum = 0U;

    if (LLD_HSI2C_SUCCESS == lld_i2c_probe(i2cHandle, slaveAddr))
    {
        UARTPuts("\nProbing EEPROM with slave address ", -1);
        UARTPutHexNum(slaveAddr);
        UARTPuts(" successfull ", -1);

        while (1)
        {
            eepromOptMenu(&eepromOption);

            if (EEPROM_READ_SAVE_BLOCK == eepromOption ||
                EEPROM_VERIFY_BLOCK == eepromOption)
            {
                UARTPuts("\nEnter block to be tested : ", -1);

                /* Get block Num */
                blockNum = UARTGetNum();
            }

            if (EEPROM_READ_SAVE_BLOCK == eepromOption)
            {
                eepromBlockReadSave(i2cHandle, slaveAddr, blockNum);
            }
            else if (EEPROM_VERIFY_BLOCK == eepromOption)
            {
                eepromBlockVerify(i2cHandle, slaveAddr, blockNum);
            }
            else
            {
                UARTPuts("\nEEPROM block test exiting...\n\n", -1);
                break;
            }
        }
    }
    else
    {
        UARTPuts("\nFailed to probe EEPROM with slave addr ", -1);
        UARTPutHexNum(slaveAddr);
    }
}

void eepromBlockVerify(hsI2cHandle i2cHandle, uint8_t slaveAddr,
                       uint32_t blockNum)
{
    volatile uint32_t          retVal = LLD_HSI2C_SUCCESS;
    volatile uint32_t          count, dataMismatch = 0;
    lld_hsi2c_datatfr_params_t i2cXferParams;
    uint8_t  data[DATA_SIZE + 2];
    uint32_t blockAddr = 0;

    i2cXferParams.bufLen    = (DATA_SIZE + 2);
    i2cXferParams.buffer    = &data[0];
    i2cXferParams.slaveAddr = slaveAddr;
    i2cXferParams.timeout   = 0xFFFF;

    /*Calculate block addr*/
    blockAddr = 64 * (blockNum);
    data[0]   = (uint8_t) (((uint32_t) 0xFF00 & blockAddr) >> 8);
    data[1]   = (uint8_t) ((uint32_t) 0xFF & blockAddr);

    for (count = 2; count < (DATA_SIZE + 2); count++)
    {
        data[count] = count;
    }

    /*Write data to eeprom*/
    i2cXferParams.flags = LLD_HSI2C_WRITE | LLD_HSI2C_MASTER |
                          LLD_HSI2C_START | LLD_HSI2C_STOP;

    retVal = lld_i2c_transfer(i2cHandle, &i2cXferParams);

    /*Wait for EEPROM to complete write*/
    sampleDelay(30000);

    if ((LLD_HSI2C_SUCCESS != retVal))
    {
        UARTPuts("\nI2c write Data failed ", -1);
    }
    else
    {
        /*UARTPuts("\nI2c write Data successfull ", -1);*/
    }

    if (LLD_HSI2C_SUCCESS == retVal)
    {
        /*Clear data*/
        for (count = 2; count < (DATA_SIZE + 2); count++)
        {
            data[count] = 0;
        }

        i2cXferParams.bufLen    = 2;
        i2cXferParams.buffer    = &data[0];
        i2cXferParams.slaveAddr = slaveAddr;
        i2cXferParams.timeout   = 0xFFFF;

        /*Write base address to eeprom*/
        i2cXferParams.flags = LLD_HSI2C_WRITE | LLD_HSI2C_MASTER |
                              LLD_HSI2C_START | LLD_HSI2C_STOP;

        retVal = lld_i2c_transfer(i2cHandle, &i2cXferParams);

        /*Wait for EEPROM to complete write*/
        sampleDelay(1000);

        if (LLD_HSI2C_SUCCESS != retVal)
        {
            UARTPuts("\nI2c write address failed ", -1);
        }
        else
        {
            /*UARTPuts("\nI2c write address successfull ", -1);*/

            i2cXferParams.bufLen = DATA_SIZE;
            i2cXferParams.buffer = &data[2];

            i2cXferParams.flags = LLD_HSI2C_READ | LLD_HSI2C_MASTER |
                                  LLD_HSI2C_START | LLD_HSI2C_STOP;

            retVal = lld_i2c_transfer(i2cHandle, &i2cXferParams);

            if (LLD_HSI2C_SUCCESS != retVal)
            {
                UARTPuts("\nI2c read failed ", -1);
            }
            else
            {
                /*UARTPuts("\nI2c read successfull ", -1);*/

                for (count = 2; count < DATA_SIZE + 2; count++)
                {
                    if (data[count] != count)
                    {
                        dataMismatch = 1;
                        UARTPuts("\nI2c write and read data did not match ", -1);
                        UARTPutNum(count);
                    }
                }
            }
        }
    }

    if ((1 == dataMismatch) || LLD_HSI2C_SUCCESS != retVal)
    {
        UARTPuts("\nEEPROM block verify failed ", -1);
    }
    else
    {
        UARTPuts("\nEEPROM block verify Successful ", -1);
    }
}

void eepromBlockReadSave(hsI2cHandle i2cHandle, uint8_t slaveAddr,
                         uint32_t blockNum)
{
    volatile uint32_t          retVal = LLD_HSI2C_SUCCESS;
    volatile uint32_t          count;
    lld_hsi2c_datatfr_params_t i2cXferParams;
    uint8_t  data[DATA_SIZE + 2];
    uint32_t blockAddr = 0;

    i2cXferParams.bufLen    = 2;
    i2cXferParams.buffer    = &data[0];
    i2cXferParams.slaveAddr = slaveAddr;
    i2cXferParams.timeout   = 0xFFFF;

    /*Calculate block addr*/
    blockAddr = 64 * (blockNum);
    data[0]   = (uint8_t) (((uint32_t) 0xFF00 & blockAddr) >> 8);
    data[1]   = (uint8_t) ((uint32_t) 0xFF & blockAddr);

    /*Clear data*/
    for (count = 2; count < (DATA_SIZE + 2); count++)
    {
        data[count] = 0;
    }

    /*Write base address to eeprom*/
    i2cXferParams.flags = LLD_HSI2C_WRITE | LLD_HSI2C_MASTER |
                          LLD_HSI2C_START | LLD_HSI2C_STOP;

    retVal = lld_i2c_transfer(i2cHandle, &i2cXferParams);

    /*Wait for EEPROM to complete write*/
    sampleDelay(1000);

    if (LLD_HSI2C_SUCCESS != retVal)
    {
        UARTPuts("\nI2c write address failed ", -1);
    }
    else
    {
        /*UARTPuts("\nI2c write address successfull ", -1);*/

        i2cXferParams.bufLen = DATA_SIZE;
        i2cXferParams.buffer = &data[2];

        i2cXferParams.flags = LLD_HSI2C_READ | LLD_HSI2C_MASTER |
                              LLD_HSI2C_START | LLD_HSI2C_STOP;

        retVal = lld_i2c_transfer(i2cHandle, &i2cXferParams);

        if (LLD_HSI2C_SUCCESS != retVal)
        {
            UARTPuts("\nI2c read failed ", -1);
        }
        else
        {
            /*UARTPuts("\nI2c read successfull ", -1);*/

            UARTPuts("\nBlock Data: ", -1);
            for (count = 2; count < DATA_SIZE + 2; count++)
            {
                saveBlock[count - 2] = data[count];
                UARTPutHexNum((uint32_t) saveBlock[count - 2]);
                UARTPuts(" ", -1);
                if (0 == ((count - 2) % 8))
                {
                    UARTPuts("\n", -1);
                }
            }
        }
    }

    if (LLD_HSI2C_SUCCESS == retVal)
    {
        UARTPuts("\nI2c Block read and save test successfull ", -1);
    }
    else
    {
        UARTPuts("\nI2c Block read and save test failed ", -1);
    }
}

void sampleDelay(uint32_t delay)
{
    volatile uint32_t delay1 = delay;
    while (delay1--) ;
}

