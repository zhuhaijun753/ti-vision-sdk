/**
 *  \file     edid_programmer_main.c
 *
 *  \brief    This file contains EDID programmer.
 *
 *  \details  This file contains EDID programmer.
 *
 *  \copyright Copyright (C) 2013 Texas Instruments Incorporated -
 *             http://www.ti.com/
 */

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

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stdio.h>
#include "i2clib/lld_hsi2c.h"
#include "soc_defines.h"
#include "platform.h"
#include "uartStdio.h"
#include "interrupt.h"
#include "soc.h"

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */
#define EEPROM_I2C_ADDR             (0x50U)

#ifdef BUILD_A15
#ifdef TDA2EX_BUILD
#define I2C5_INT_NUM                (61U)
#else
#define I2C2_INT_NUM                (56U)
#endif
#endif

#ifdef BUILD_M4
#define I2C2_INT_NUM                (41U)
#endif

#define POLLED_MODE                 (1)
#define PAGE_SIZE                   (8)

#define PRGRM                       ('1')
#define VERIFY                      ('2')
#define EXIT(opt)                   (('x' == opt) || ('X' == opt))

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static uint8_t       gPageData[PAGE_SIZE + 2];
static uint8_t       gEepromReadData[256] = {0};

static const uint8_t gEdid1080p60[] =
{
    0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x4D, 0x29, 0x09, 0x05,
    0x0A, 0x00, 0x00, 0x00, 0x1A, 0x14, 0x01, 0x03, 0x80, 0x52, 0x2E, 0x78,
    0x2A, 0x1B, 0xBE, 0xA2, 0x55, 0x34, 0xB3, 0x26, 0x14, 0x4A, 0x52, 0xAF,
    0xCE, 0x00, 0x81, 0x80, 0x90, 0x40, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x3A, 0x80, 0x18, 0x71, 0x38,
    0x2D, 0x40, 0x58, 0x2C, 0x45, 0x00, 0x34, 0xCD, 0x31, 0x00, 0x00, 0x1E,
    0x66, 0x21, 0x50, 0xB0, 0x51, 0x00, 0x1B, 0x30, 0x40, 0x70, 0x36, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0xFC, 0x00, 0x48,
    0x44, 0x4D, 0x49, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A,
    0x00, 0x00, 0x00, 0xFD, 0x00, 0x37, 0x4C, 0x0F, 0x44, 0x0A, 0x0F, 0x00,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x01, 0x6E, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF
};

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

static int32_t programEdid(hsI2cHandle i2cHandle);
static int32_t verifyEdid(hsI2cHandle i2cHandle);

static void sampleDelay(int32_t delay);
static void mainMenu(char *option);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int main(void)
{
    hsI2cHandle           i2cHandle;
    lld_hsi2c_initParam_t initPar;
    hsI2cObjHandle        i2cObjHandle;
    int32_t retVal = LLD_HSI2C_SUCCESS;
    char mainMenuOption;
    LLD_Hsi2cInstId_t     i2cInstId;

    PlatformUartConsoleSetPinMux();
    UARTStdioInit();
    UARTPuts("\nI2C EDID Programmer tests ", -1);

#if (defined (TDA2XX_BUILD))
    PlatformI2C2SetPinMux();
#elif (defined (TDA2EX_BUILD))
    PlatformI2C5SetPinMux();
#endif

#ifdef TDA2EX_BUILD
    initPar.i2cIntNum = I2C5_INT_NUM;
    i2cInstId         = HSI2C_INST_4;
#else
    initPar.i2cIntNum = I2C2_INT_NUM;
    i2cInstId         = HSI2C_INST_1;
#endif

    initPar.i2cBusFreq = I2C_NORMAL;
    initPar.opMode     = HSI2C_OPMODE_INTERRUPT;
#if POLLED_MODE
    initPar.opMode = HSI2C_OPMODE_POLLED;
#endif
    initPar.i2cOwnAddr   = 0xFE;
    initPar.is10BitAddr  = 0;
    initPar.isMasterMode = 1;

    lld_i2c_init(&i2cObjHandle, i2cInstId, &initPar);
    i2cHandle = lld_i2c_open(i2cInstId, NULL, NULL);
    if (NULL == i2cHandle)
    {
        UARTPuts("\nI2C open failed!!", -1);
        return (-1);
    }

    do
    {
        /* Probe for EEPROM */
        retVal = lld_i2c_probe(i2cHandle, EEPROM_I2C_ADDR);
        if (retVal != LLD_HSI2C_SUCCESS)
        {
            UARTPuts("\nI2c Probe failed!!", -1);
#if (defined (TDA2XX_FAMILY_BUILD))
            UARTPuts("\nPlease ensure vision app board is connected and "
                     "both SW1-1 and SW1-2 on Vision app board is ON!!", -1);
#elif (defined (TDA3XX_FAMILY_BUILD))
            UARTPuts("\nPlease ensure SW80000-1 & SW80000-2 on board is ON!!",
                     -1);
#endif
            sampleDelay(10000);
        }
    } while (retVal != LLD_HSI2C_SUCCESS);

    while (1)
    {
        mainMenu(&mainMenuOption);

        if (PRGRM == mainMenuOption)
        {
            UARTPuts("\nProcessing wait...", -1);
            retVal = programEdid(i2cHandle);
            if (retVal == LLD_HSI2C_SUCCESS)
            {
                UARTPuts("\nEDID programming successful!!", -1);
            }
            else
            {
                UARTPuts("\nEDID programming failed!!", -1);
            }
        }
        else if (VERIFY == mainMenuOption)
        {
            UARTPuts("\nProcessing wait...", -1);
            retVal = verifyEdid(i2cHandle);
            if (retVal == LLD_HSI2C_SUCCESS)
            {
                UARTPuts("\nEDID verification successful!!", -1);
            }
            else
            {
                UARTPuts("\nEDID verification failed!!", -1);
            }
        }
        else
        {
            break;
        }
    }

    lld_i2c_close(&i2cHandle);
    lld_i2c_deinit(i2cInstId);

    UARTPuts("\nEDID porgramming Ended!!", -1);

    return (0);
}

static int32_t programEdid(hsI2cHandle i2cHandle)
{
    volatile int32_t           retVal = LLD_HSI2C_SUCCESS;
    volatile uint32_t          count;
    volatile uint32_t          gArrayIdx = 0;
    lld_hsi2c_datatfr_params_t i2cXferParams;
    volatile uint32_t          j = 0;

    /* Write data to eeprom */
    i2cXferParams.bufLen    = (PAGE_SIZE + 1);
    i2cXferParams.buffer    = &gPageData[0];
    i2cXferParams.slaveAddr = (uint8_t) EEPROM_I2C_ADDR;
    i2cXferParams.timeout   = 4000;
    i2cXferParams.flags     = LLD_HSI2C_WRITE | LLD_HSI2C_MASTER |
                              LLD_HSI2C_START | LLD_HSI2C_STOP;

    for (j = 0; j < 256; j += 8)
    {
        gPageData[0] = j;        /* page address */
        for (count = 1; count < (PAGE_SIZE + 1); count++)
        {
            gPageData[count] = gEdid1080p60[gArrayIdx++];
        }
        retVal += lld_i2c_transfer(i2cHandle, &i2cXferParams);
        /* Wait for EEPROM to complete write */
        sampleDelay(1000);
    }

    if (retVal == LLD_HSI2C_SUCCESS)
    {
        retVal = verifyEdid(i2cHandle);
        if (retVal != LLD_HSI2C_SUCCESS)
        {
#if (defined (TDA2XX_FAMILY_BUILD))
            UARTPuts("\nPlease check SW1-2 of vision board for "
                     "WP pin position is ON!!", -1);
#elif (defined (TDA3XX_FAMILY_BUILD))
            UARTPuts("\nPlease check SW80000-2 on board for "
                     "WP pin position is ON!!", -1);
#endif
        }
    }

    return (retVal);
}

static int32_t verifyEdid(hsI2cHandle i2cHandle)
{
    volatile int32_t           retVal   = LLD_HSI2C_SUCCESS;
    volatile uint32_t          j        = 0;
    uint32_t                   mismatch = 0;
    lld_hsi2c_datatfr_params_t i2cXferParams;

    for (j = 0; j < 256; j += 8)
    {
        /* Write page address */
        gPageData[0]            = j;
        i2cXferParams.bufLen    = 1;
        i2cXferParams.buffer    = &gPageData[0];
        i2cXferParams.slaveAddr = (uint8_t) EEPROM_I2C_ADDR;
        i2cXferParams.timeout   = 4000;
        i2cXferParams.flags     = LLD_HSI2C_WRITE | LLD_HSI2C_MASTER |
                                  LLD_HSI2C_START | LLD_HSI2C_STOP;
        retVal = lld_i2c_transfer(i2cHandle, &i2cXferParams);
        sampleDelay(1000);

        /* Read page */
        i2cXferParams.bufLen = PAGE_SIZE;
        i2cXferParams.buffer = &gEepromReadData[j];
        i2cXferParams.flags  = LLD_HSI2C_READ | LLD_HSI2C_MASTER |
                               LLD_HSI2C_START | LLD_HSI2C_STOP;
        retVal = lld_i2c_transfer(i2cHandle, &i2cXferParams);
        sampleDelay(1000);
    }

    for (j = 0; j < 256; j++)
    {
        if (gEepromReadData[j] != gEdid1080p60[j])
        {
            mismatch = 1;
            break;
        }
    }

    if (mismatch)
    {
        retVal = LLD_HSI2C_FAIL;
    }
    else
    {
        retVal = LLD_HSI2C_SUCCESS;
    }

    return (retVal);
}

static void mainMenu(char *option)
{
    while (1)
    {
        UARTPuts(
            "\n\n**** EDID PROGRAMMING ****",
            -1);
        UARTPuts("\nMenu:", -1);
        UARTPuts("\n1. Program EDID for 1080p", -1);
        UARTPuts("\n2. Verify EDID for 1080p", -1);
        UARTPuts("\nx. Exit", -1);
        UARTPuts("\nSelect option : ", -1);

        /* Get option */
        UARTGets((char *) option, 1);

        if ((PRGRM == *option) || (VERIFY == *option) || (EXIT(*option)))
        {
            break;
        }
        else
        {
            UARTPuts("\nEnter Valid option\n", -1);
        }
    }

    return;
}

static void sampleDelay(int32_t delay)
{
    volatile int32_t i, j;

    for (i = 0; i < delay; i++)
    {
        for (j = 0; j < 100; j++)
        {}
    }

    return;
}

