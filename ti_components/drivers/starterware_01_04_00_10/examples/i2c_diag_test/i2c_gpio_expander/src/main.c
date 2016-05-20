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
#define IO_EXPANDER_SLAVE_ADDR                  (0x26)
#define JAMR3_IO_EXPANDER_SLAVE_ADDR            (0x21)

#define BASE_BOARD     ('1')
#define JAMR3_BOARD    ('2')
#define ALL_BOARD(opt) (('a' == opt) || ('A' == opt))
#define EXIT(opt)      (('x' == opt) || ('X' == opt))

/***********************************************************************/
/*                   INTERNAL VARIABLE DEFINITION                      */
/***********************************************************************/
volatile uint32_t intStatus = 1;
uint8_t           data_tx[4];
uint8_t           data_rx[4];

/*******************************************************************************
**                   INTERNAL FUNCTION PROTOTYPE
*******************************************************************************/
void mainMenu(char *option);
void sampleDelay(uint32_t delay);
void ioExpanderTest(hsI2cHandle i2cHandle, uint8_t slaveAddr);

void configPadMux(void)
{
    /*Unlock the Control registers */
    PlatformUnlockMMR();

    PlatformUART1SetPinMux();

    PlatformI2C4SetPinMux();

#if (defined (TDA2XX_BUILD))
    PlatformI2C2SetPinMux();
#elif (defined (TDA2EX_BUILD))
    PlatformI2C5SetPinMux();
#endif
}

int main()
{
    hsI2cHandle           i2cHandle, i2cHandle3;
    lld_hsi2c_initParam_t initPar, initPar3;
    hsI2cObjHandle        i2cObjHandle, i2cObjHandle3;
    volatile uint8_t      appDone = 1;
    char mainMenuOption;
    LLD_Hsi2cInstId_t     i2cInstId;

    /*Uart and I2C pad mux*/
    configPadMux();

    UARTStdioInit();

    /*Init and open I2C instance 1*/
    initPar.i2cBusFreq   = I2C_NORMAL;
    initPar.opMode       = HSI2C_OPMODE_POLLED;
    initPar.is10BitAddr  = 0;
    initPar.isMasterMode = 1;

#if (defined (TDA2XX_BUILD))
    i2cInstId = HSI2C_INST_1;
#elif (defined (TDA2EX_BUILD))
    i2cInstId = HSI2C_INST_4;
#endif

    lld_i2c_init(&i2cObjHandle, i2cInstId, &initPar);
    i2cHandle = lld_i2c_open(i2cInstId, NULL, NULL);

    /*Init and open I2C instance 2*/
    initPar3.i2cBusFreq   = I2C_NORMAL;
    initPar3.opMode       = HSI2C_OPMODE_POLLED;
    initPar3.is10BitAddr  = 0;
    initPar3.isMasterMode = 1;

    lld_i2c_init(&i2cObjHandle3, HSI2C_INST_3, &initPar3);
    i2cHandle3 = lld_i2c_open(HSI2C_INST_3, NULL, NULL);

    while (1)
    {
        mainMenu(&mainMenuOption);

        if (BASE_BOARD == mainMenuOption)
        {
            ioExpanderTest(i2cHandle, (uint8_t) IO_EXPANDER_SLAVE_ADDR);
        }
        else if (JAMR3_BOARD == mainMenuOption)
        {
            ioExpanderTest(i2cHandle3, (uint8_t) JAMR3_IO_EXPANDER_SLAVE_ADDR);
        }
        else if (ALL_BOARD(mainMenuOption))
        {
            UARTPuts("\n\nIO Expander base board test...", -1);
            ioExpanderTest(i2cHandle, (uint8_t) IO_EXPANDER_SLAVE_ADDR);

            UARTPuts("\n\nIO Expander JAMR3 board test...", -1);
            ioExpanderTest(i2cHandle3, (uint8_t) JAMR3_IO_EXPANDER_SLAVE_ADDR);
        }
        else
        {
            UARTPuts("\nIO Expander board diagnostic test exiting...", -1);
            break;
        }
    }

    lld_i2c_close(&i2cHandle);
    lld_i2c_deinit(i2cInstId);

    lld_i2c_close(&i2cHandle3);
    lld_i2c_deinit(HSI2C_INST_3);

    while (appDone) ;

    return 0;
}

void ioExpanderTest(hsI2cHandle i2cHandle, uint8_t slaveAddr)
{
    uint8_t                    data[2];
    volatile uint32_t          retVal = LLD_HSI2C_SUCCESS;
    lld_hsi2c_datatfr_params_t i2cXferParams;

    i2cXferParams.bufLen    = (uint32_t) 2;
    i2cXferParams.buffer    = &data[0];
    i2cXferParams.slaveAddr = slaveAddr;
    i2cXferParams.timeout   = 0xFFFF;

    if (LLD_HSI2C_SUCCESS == lld_i2c_probe(i2cHandle, slaveAddr))
    {
        UARTPuts("\nProbing IO Expander with slave address ", -1);
        UARTPutHexNum(slaveAddr);
        UARTPuts(" successful ", -1);

        /*Clear data*/
        data[0] = 0;
        data[1] = 0;

        /*Read data from IO exapnder*/
        i2cXferParams.flags = LLD_HSI2C_READ | LLD_HSI2C_MASTER |
                              LLD_HSI2C_START | LLD_HSI2C_STOP;

        retVal = lld_i2c_transfer(i2cHandle, &i2cXferParams);

        if ((LLD_HSI2C_SUCCESS != retVal))
        {
            UARTPuts("\nIO expander read failed ", -1);
        }
        else
        {
            /*UARTPuts("\nI2c read successfull ", -1);*/
            UARTPuts("\nData read from IO expander: Port0 = ", -1);
            UARTPutHexNum(data[0]);
            UARTPuts(" Port1 = ", -1);
            UARTPutHexNum(data[1]);

            /*Write data to IO expander*/
            i2cXferParams.flags = LLD_HSI2C_WRITE | LLD_HSI2C_MASTER |
                                  LLD_HSI2C_START | LLD_HSI2C_STOP;

            retVal = lld_i2c_transfer(i2cHandle, &i2cXferParams);

            if (LLD_HSI2C_SUCCESS != retVal)
            {
                UARTPuts("\nIO expander write failed ", -1);
            }
            else
            {
                /*UARTPuts("\nI2c write Data successfull ", -1);*/
            }
        }

        if (LLD_HSI2C_SUCCESS != retVal)
        {
            UARTPuts("\nIO expander test failed ", -1);
        }
        else
        {
            UARTPuts("\nIO expander test Successful ", -1);
        }
    }
    else
    {
        UARTPuts("\nFailed to probe IO Expander with slave addr ", -1);
        UARTPutHexNum(slaveAddr);
    }
}

void mainMenu(char *option)
{
    while (1)
    {
        UARTPuts("\n\n**** IO EXPANDER TEST ****", -1);
        UARTPuts("\nMenu:", -1);
        UARTPuts("\n1. Base  board I2C1 test", -1);
        UARTPuts("\n2. JAMR3 board I2C4 test", -1);
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

void sampleDelay(uint32_t delay)
{
    volatile uint32_t delay1 = delay;
    while (delay1--) ;
}

