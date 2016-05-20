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
#include "lld_hsi2c_edma.h"
#include "soc_defines.h"
#include "platform.h"
#include "uartStdio.h"
#include "interrupt.h"
#include "lld_hsi2c_edma.h"

#ifndef TI814X_FAMILY_BUILD
#include "irq_xbar.h"
#endif

#include "soc.h"
#include "edma.h"
#include "interrupt.h"

#if defined BUILD_A8 && !defined BUILD_GCC
#include "timeProfile.h"
#endif

/***********************************************************************/
/*                    INTERNAL MACRO DEFINITION                        */
/***********************************************************************/
#if (defined (TDA2XX_BUILD)) || (defined (TI814X_FAMILY_BUILD))
#define SLAVE_ADDR                  (0x50)
#elif (defined (TDA3XX_FAMILY_BUILD)) || (defined (TDA2EX_BUILD))
#define SLAVE_ADDR                  (0x51)
#endif

#if defined (TDA2XX_FAMILY_BUILD)
#define I2C_INT_NUM                   (56U)
#define I2C_XBAR_CFG_REQUIRED         (0U)

#define EDMA_COMP_INT                 (26U)
#define EDMA_XBAR_CFG_REQUIRED        (1U)

#define EDMA_INT_IRQ_XBAR_CPU_ID       CPU_MPUSS
#define EDMA_INT_IRQ_XBAR_INST_NO      XBAR_INST_MPU_IRQ_26
#define EDMA_INT_IRQ_XBAR_INDEX        EDMA_TPCC_IRQ_REGION0

#elif defined (TDA3XX_FAMILY_BUILD)
#define I2C_INT_NUM                   (41U)
#define I2C_XBAR_CFG_REQUIRED         (0U)

#define EDMA_COMP_INT                 (34U)
#define EDMA_XBAR_CFG_REQUIRED        (1U)

#define EDMA_INT_IRQ_XBAR_CPU_ID       CPU_IPU1
#define EDMA_INT_IRQ_XBAR_INST_NO      XBAR_INST_IPU1_IRQ_34
#define EDMA_INT_IRQ_XBAR_INDEX        EDMA_TPCC_IRQ_REGION0

#elif defined (TI814X_FAMILY_BUILD)
#define I2C_INT_NUM                   (70U)
#define I2C_XBAR_CFG_REQUIRED         (0U)
#define EDMA_COMP_INT                 (12U)
#define EDMA_XBAR_CFG_REQUIRED        (0U)
#endif

#define EDMA3_EVENT_QUEUE             (0U)
#define EDMA_U_BASE                   (SOC_EDMA_TPCC_BASE)

#define DATA_SIZE                     (64)

/***********************************************************************/
/*                   INTERNAL VARIABLE DEFINITION                      */
/***********************************************************************/
volatile uint32_t intStatus = 1, txRxStatus = 0;
lld_hsi2c_opMode  currentOpMode;

/*******************************************************************************
**                   INTERNAL FUNCTION PROTOTYPE
*******************************************************************************/
int32_t I2CEepromReadWriteTest(hsI2cHandle i2cHandle, uint8_t slaveAddr,
                               uint32_t blockNum);
void i2c_callback(hsI2cHandle i2cHandle, LLD_hsi2cErrorCode_t status,
                  void *appData);
void sampleDelay(int32_t delay);
void configurI2cTestInterrupts(hsI2cHandle           i2cHandle,
                               lld_hsi2c_initParam_t initPar);

void configurI2cTestInterrupts(hsI2cHandle           i2cHandle,
                               lld_hsi2c_initParam_t initPar)
{
#ifndef BUILD_A8
    /*Unlock the Crossbar register */
    PlatformUnlockMMR();
#endif

#if I2C_XBAR_CFG_REQUIRED
    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                   I2C_INT_IRQ_XBAR_CPU_ID,
                   I2C_INT_IRQ_XBAR_INST_NO,
                   I2C_INT_IRQ_XBAR_INDEX);
#endif
#if EDMA_XBAR_CFG_REQUIRED
    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                   EDMA_INT_IRQ_XBAR_CPU_ID,
                   EDMA_INT_IRQ_XBAR_INST_NO,
                   EDMA_INT_IRQ_XBAR_INDEX);
#endif

    Intc_Init();
    Intc_IntEnable(0);
    /* Enable I2C interrupt */
    Intc_IntRegister(I2C_INT_NUM, initPar.i2cIsr, i2cHandle);
    Intc_IntPrioritySet(I2C_INT_NUM, 1, 0);
    Intc_SystemEnable(I2C_INT_NUM);
    /* Enable EDMA Interrupt */
    Intc_IntRegister(EDMA_COMP_INT, (IntrFuncPtr) EDMA_callbackFn, i2cHandle);
    Intc_IntPrioritySet(EDMA_COMP_INT, 1, 0);
    Intc_SystemEnable(EDMA_COMP_INT);
}

int main()
{
    hsI2cHandle           i2cHandle;
    lld_hsi2c_initParam_t initPar;
    volatile uint32_t     Done = 1;
    hsI2cObjHandle        i2cObjHandle;
    int32_t retVal = LLD_HSI2C_SUCCESS;
    LLD_hsi2cEdmaParam    edmaParam;
    uint32_t userInput, fifoEnable;
#ifndef TAKE_USER_INPUT
    uint32_t busfreq, opMode, fifoStatus;
#endif

    PlatformUartConsoleSetPinMux();
    UARTStdioInit();
    UARTPuts("\nI2C tests ", -1);

#ifdef TDA2XX_FAMILY_BUILD
    UARTPuts("\nWe write to EEPROM on EVM, Makesure SW5 - 10 is on", -1);
#elif defined (TDA3XX_FAMILY_BUILD)
    UARTPuts("\nWe write to EEPROM on EVM, Makesure SW8001 - 2 is on", -1);
#endif

#ifdef TDA2XX_FAMILY_BUILD
    /*Configure the EDMA clock */
    PlatformEDMAWkupDepEnable();
#endif

    EDMAsetRegion(0);
    EDMA3Init(EDMA_U_BASE, EDMA3_EVENT_QUEUE);

#ifndef TAKE_USER_INPUT
    for (busfreq = 1; busfreq < 3; busfreq++)
    {
        for (opMode = 1; opMode < 4; opMode++)
        {
            for (fifoStatus = 1; fifoStatus < 3; fifoStatus++)
            {
#else
    do {
#endif
#ifdef TAKE_USER_INPUT
                UARTPuts(
                    "\nEnter Operating Mode\n1 For Polled Mode\
                          \n2 For Interrupt Mode\n3 For DMA Mode\n",
                    -1);
                userInput = UARTGetNum();
#else
                userInput = opMode;
#endif
                if (userInput == 1)
                {
                    currentOpMode = HSI2C_OPMODE_POLLED;
                    UARTPuts("\nconfigured in - POLLED Mode", -1);
                }
                else if (userInput == 2)
                {
                    currentOpMode = HSI2C_OPMODE_INTERRUPT;
                    UARTPuts("\nconfigured in - INTERRUPT Mode", -1);
                }
                else if (userInput == 3)
                {
                    currentOpMode = HSI2C_OPMODE_DMA;
                    UARTPuts("\nconfigured in - DMA Mode", -1);
                }
                else
                {
                    UARTPuts("\nInvalid Input: Defaulting to Interrupt mode",
                             -1);
                    currentOpMode = HSI2C_OPMODE_INTERRUPT;
                }
                initPar.opMode = currentOpMode;

#ifdef TAKE_USER_INPUT
                UARTPuts(
                    "\nEnter I2c Bus Speed\n1 For 100 Kbps\
                          \n2 For 400 Kbps\n",
                    -1);
                userInput = UARTGetNum();
                UARTPuts("\n", -1);
#else
                userInput = busfreq;
#endif
                if (userInput == 1)
                {
                    initPar.i2cBusFreq = I2C_NORMAL;
                    UARTPuts(" Frequency - 100 Kbps", -1);
                }
                else if (userInput == 2)
                {
                    initPar.i2cBusFreq = I2C_FAST;
                    UARTPuts(" Frequency - 400 Kbps", -1);
                }
                else
                {
                    UARTPuts("\nInvalid Input: Defaulting to 100 Kbps", -1);
                    initPar.i2cBusFreq = I2C_NORMAL;
                }

#ifdef TAKE_USER_INPUT
                UARTPuts("\nEnter FIFO Status\n1 For Enabled\n2 For Disabled\n",
                         -1);
                userInput = UARTGetNum();
                UARTPuts("\n", -1);
#else
                userInput = fifoStatus;
#endif
                if (userInput == 1)
                {
                    fifoEnable = 1U;
                    UARTPuts(" FIFO status - Enabled", -1);
                }
                else if (userInput == 2)
                {
                    fifoEnable = 0U;
                    UARTPuts(" FIFO status - Disabled", -1);
                }
                else
                {
                    UARTPuts("\nInvalid Input: Defaulting Fifo Disabled", -1);
                    fifoEnable = 0U;
                }

                edmaParam.baseAddr   = EDMA_U_BASE;
                edmaParam.eventQueue = EDMA3_EVENT_QUEUE;
                initPar.edmaParam    = (void *) &edmaParam;
                initPar.i2cOwnAddr   = 0xFE;
                initPar.is10BitAddr  = 0;
                initPar.isMasterMode = 1;
                initPar.i2cIntNum    = I2C_INT_NUM;

                lld_i2c_init(&i2cObjHandle, HSI2C_INST_0, &initPar);

                if (fifoEnable == 1U)
                {
                    /*Set FIFO threshold of 16bytes*/
                    lld_i2c_SetFifoThreshold(HSI2C_INST_0, 15, 15);
                }

                i2cHandle =
                    lld_i2c_open(HSI2C_INST_0,
                                 (lldHsi2cAppCallback) i2c_callback,
                                 NULL);

                configurI2cTestInterrupts(i2cHandle, initPar);

                /* Write to Block 1 of EEPROM */
                retVal = I2CEepromReadWriteTest(i2cHandle, SLAVE_ADDR, 1U);

                if (retVal == LLD_HSI2C_SUCCESS)
                {
                    UARTPuts("\nI2c Test successfull ", -1);
                }
                else
                {
                    UARTPuts("\nI2c Test Failed ", -1);
                    while (Done) ;
                }

                lld_i2c_close(&i2cHandle);

                lld_i2c_deinit(HSI2C_INST_0);

#ifndef TAKE_USER_INPUT
            }
        }
    }
#else
                UARTPuts("\nPress 1 to run again with different configuration",
                         -1);
                UARTPuts("\nPress Any other Key to exit\n", -1);
                userInput = UARTGetNum();
                if (userInput != 1)
                {
                    UARTPuts("\n", -1);
                    break;
                }
            }
            while (Done) ;
#endif

    while (Done) ;

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
        txRxStatus = 1;
        /*UARTPuts("\nISR Called. I2C TX/RX Failed", -1);*/
    }
}

int32_t I2CEepromReadWriteTest(hsI2cHandle i2cHandle, uint8_t slaveAddr,
                               uint32_t blockNum)
{
    volatile int32_t retVal = LLD_HSI2C_SUCCESS;
    volatile uint32_t count;
    lld_hsi2c_datatfr_params_t i2cXferParams;
    uint8_t data[DATA_SIZE + 2];
    uint32_t blockAddr = 0;

#if defined BUILD_A8 && !defined BUILD_GCC
    volatile uint32_t start, stop;
#endif
    do
    {
        i2cXferParams.bufLen    = (DATA_SIZE + 2);
        i2cXferParams.buffer    = &data[0];
        i2cXferParams.slaveAddr = (uint8_t) slaveAddr;
        i2cXferParams.timeout   = 4000;

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
        sampleDelay(1000);

        if (currentOpMode != HSI2C_OPMODE_POLLED)
        {
            /* For DMA And Polled Mode wait till completion interrupt is called
            **/
            while (intStatus) ;
            intStatus = 1;
            if (txRxStatus == 1)
            {
                retVal = LLD_HSI2C_FAIL;
            }
        }

        if (LLD_HSI2C_SUCCESS != retVal)
        {
            UARTPuts("\nI2c write Data failed ", -1);
            break;
        }

        /*Clear data*/
        for (count = 2; count < (DATA_SIZE + 2); count++)
        {
            data[count] = 0;
        }

        i2cXferParams.bufLen = 2;
        i2cXferParams.buffer = &data[0];

        /*Write base address to eeprom*/
        i2cXferParams.flags = LLD_HSI2C_WRITE | LLD_HSI2C_MASTER |
                              LLD_HSI2C_START | LLD_HSI2C_STOP;

        retVal = lld_i2c_transfer(i2cHandle, &i2cXferParams);

        /*Wait for EEPROM to complete write*/
        sampleDelay(1000);

        if (currentOpMode != HSI2C_OPMODE_POLLED)
        {
            /* For DMA And Polled Mode wait till completion interrupt call */
            while (intStatus) ;
            intStatus = 1;
            if (txRxStatus == 1)
            {
                retVal = LLD_HSI2C_FAIL;
            }
        }

        if (LLD_HSI2C_SUCCESS != retVal)
        {
            UARTPuts("\nI2c write Address failed ", -1);
            break;
        }

        i2cXferParams.bufLen = DATA_SIZE;
        i2cXferParams.buffer = &data[2];

        i2cXferParams.flags = LLD_HSI2C_READ | LLD_HSI2C_MASTER |
                              LLD_HSI2C_START | LLD_HSI2C_STOP;

#if defined BUILD_A8 && !defined BUILD_GCC
        /*Read data in 100kbps*/
        enableticks;
        start = getticks;
#endif
        retVal = lld_i2c_transfer(i2cHandle, &i2cXferParams);
        if (currentOpMode != HSI2C_OPMODE_POLLED)
        {
            /* For DMA And Polled Mode wait till completion interrupt call */
            while (intStatus) ;
            intStatus = 1;
            if (txRxStatus == 1)
            {
                retVal = LLD_HSI2C_FAIL;
            }
        }
        if (LLD_HSI2C_SUCCESS != retVal)
        {
            UARTPuts("\nI2c write Address failed ", -1);
            break;
        }

#if defined BUILD_A8 && !defined BUILD_GCC
        stop = getticks;
        printticks(ticks(start, stop), "\nTime taken for 100kbps");
#endif
        for (count = 2; count < DATA_SIZE + 2; count++)
        {
            if (data[count] != count)
            {
                UARTPuts("\nI2c write and read data did not match ", -1);
                UARTPutNum(count);
                retVal = LLD_HSI2C_FAIL;
            }
        }
    } while (0);
    txRxStatus = 0;
    return retVal;
}

void sampleDelay(int32_t delay)
{
    volatile int32_t i, j;

    for (i = 0; i < delay; i++)
    {
        for (j = 0; j < 100; j++) ;
    }
}

