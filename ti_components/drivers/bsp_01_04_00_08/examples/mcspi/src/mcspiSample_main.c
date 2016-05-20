/******************************************************************************
 *                                                                            *
 * Copyright (c) 2012 Texas Instruments Incorporated - http://www.ti.com/     *
 *                                                                            *
 * All rights reserved. Property of Texas Instruments Incorporated.           *
 * Restricted rights to use, duplicate or disclose this code are              *
 * granted through contract.                                                  *
 *                                                                            *
 * The program may not be used without the written permission                 *
 * of Texas Instruments Incorporated or against the terms and conditions      *
 * stipulated in the agreement under which this program has been              *
 * supplied.                                                                  *
 *                                                                            *
 *****************************************************************************/

/**
 *  \file   mcspiSample_main.c
 *
 *  \brief  Sample application to demostrate the usage of McSPI driver.
 *
 *  (C) Copyright 2010, Texas Instruments, Inc
 *
 *  \author     PSG
 *
 *  \version    0.1    Created for DM814x/C6A811x platform.
 *
 */

/* ========================================================================== */
/*                          INCLUDE FILES                                     */
/* ========================================================================== */

#include <xdc/std.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/io/GIO.h>
#include <ti/sysbios/io/IOM.h>
#include <xdc/runtime/Log.h>
#include <ti/sysbios/knl/Task.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>
#include <ti/sdo/edma3/drv/edma3_drv.h>

#include "mcspi/bsp_mcspi.h"
#include "platforms/bsp_platform.h"

/* ========================================================================== */
/*                       IMPORTED FUNCTIONS                                   */
/* ========================================================================== */

extern void start_spi_sample(void);
extern void spi_initParams(void);

void spiSampleTask(UArg arg1, UArg arg2);

/* ========================================================================== */
/*                          LOCAL FUNCTION PROTOTYPE                          */
/* ========================================================================== */

static void tskHeartBeat(void);

/* ========================================================================== */
/*                             GLOBAL VARIABLES                               */
/* ========================================================================== */

Mcspi_Params mcspiPrms;

/* Global function prototypes */
void user_mcspi_init(void);

/* ========================================================================== */
/*                           FUNCTION DEFINITIONS                             */
/* ========================================================================== */

/**
 * \brief      Entry point for the main task. This creates the required channels
 *             and calls the required functions for demonstrating the SPI
 *             driver
 *
 * \param      arg1  [IN]   unused
 * \param      arg2  [IN]   unused
 *
 * \return     None
 */

void spiSampleTask(UArg arg1, UArg arg2)
{
    Bsp_PlatformInitParams platInitPrms;

    /* isPinMuxSettingReq parameter will be initialised to TRUE */
    BspPlatformInitParams_init(&platInitPrms);

    /* Initialize pinmux and evm related configurations */
    Bsp_platformInit(&platInitPrms);

    /* call the function for the SPI application test                     */
    start_spi_sample();

    /* Start the Heart Beat Print                                         */
    tskHeartBeat();

    return;
}

/**
 * \brief     Main entry function for the spi sample application. it creates
 *            the spi sample task(used to demonstrate the spi functionality).
 *
 * \param     None
 *
 * \return    None
 *
 */
Int32 main(void)
{
    BIOS_start();

    return (0);
}

/*
 * McSPI0 init function called when creating the driver.
 */
void user_mcspi_init(void)
{
    Mcspi_init();

    mcspiPrms = Mcspi_PARAMS;

    mcspiPrms.instNum         = 0;
    mcspiPrms.opMode          = MCSPI_OPMODE_DMAINTERRUPT;
    mcspiPrms.hwiNumber       = 7;
    mcspiPrms.enableCache     = (UInt32)TRUE;
    mcspiPrms.edma3EventQueue = 0;

    mcspiPrms.spiHWCfgData.masterOrSlave         = MCSPI_COMMMODE_MASTER;
    mcspiPrms.spiHWCfgData.singleOrMultiChEnable = MCSPI_SINGLE_CHANNEL;
    mcspiPrms.spiHWCfgData.pinOpModes    = MCSPI_PINOPMODE_4PIN;
    mcspiPrms.spiHWCfgData.fifoRxTrigLvl = 1;
    mcspiPrms.spiHWCfgData.fifoTxTrigLvl = 1;
    mcspiPrms.spiHWCfgData.configChfmt[0].charLength = MCSPI_LEN_8BIT;
    mcspiPrms.spiHWCfgData.configChfmt[0].multiWordAccessEnable  = (UInt32)FALSE;
    mcspiPrms.spiHWCfgData.configChfmt[0].spiChipSelectEnablePol = (UInt32)FALSE;
    mcspiPrms.spiHWCfgData.configChfmt[0].clockMode           = MCSPI_MODE0;
    mcspiPrms.spiHWCfgData.configChfmt[0].clockRatioExtension = 0;
    mcspiPrms.spiHWCfgData.configChfmt[0].spiWordInitDelay    = MCSPI_NO_DELAY;
    mcspiPrms.spiHWCfgData.configChfmt[0].trasmitReceiveMode  = MCSPI_BOTH_RXTX;
    mcspiPrms.spiHWCfgData.configChfmt[0].granularityEnable   = (UInt32)FALSE;
    mcspiPrms.spiHWCfgData.configChfmt[0].busFreq             = 48000000;
    mcspiPrms.spiHWCfgData.configChfmt[0].spienHighPolarity   = (UInt32)FALSE;
    mcspiPrms.spiHWCfgData.configChfmt[0].slaveModeChipSelect = MCSPI_SPIEN_3;
    mcspiPrms.spiHWCfgData.configChfmt[0].spiDat0Dir          = MCSPI_IN;
    mcspiPrms.spiHWCfgData.configChfmt[0].spiDat1Dir          = MCSPI_OUT;

    if (MCSPI_OPMODE_POLLED == mcspiPrms.opMode)
    {
        System_printf("\r\nMcspi is configured in polled mode\r\n");
    }
    else if (MCSPI_OPMODE_INTERRUPT == mcspiPrms.opMode)
    {
        System_printf("\r\nMcspi is configured in interrupt mode\r\n");
        System_printf("\r\nInterrupt mode is not supported!!\r\n");
    }
    else if (MCSPI_OPMODE_DMAINTERRUPT == mcspiPrms.opMode)
    {
        System_printf("\r\nMcspi is configured in dma mode\r\n");
    }
    else
    {
        System_printf("\r\nError: unknown mode of operation!!!!!!!!!!\r\n");
    }
}

Ptr NULLIOM_Params = NULL;

void user_prcm_init(void)
{
    /* Do Nothing */
}

/**
 * \brief      Function to print an log to the console every one second(Approx)
 *
 * \param      None
 *
 * \return     None
 *
 */
static void tskHeartBeat(void)
{
    static Uint32 counter = 0;

    while (counter < 0xFFFFFFFF)
    {
        Task_sleep(10U);

        System_printf("\r\n\r\n!!! PSP HrtBt %d", counter);
        counter++;
    }
}

/* ========================================================================== */
/*                                END OF FILE                                 */
/* ========================================================================== */

