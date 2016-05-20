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

/** \file   audioSample_main.c
 *
 *  \brief    sample application for demonstration of audio driver usage
 *
 *  This file contains the implementation of the sample appliation for the
 *  demonstration of audio playing through the audio interface layer.
 *
 *             (C) Copyright 2009, Texas Instruments, Inc
 */

/* ========================================================================== */
/*                            INCLUDE FILES                                   */
/* ========================================================================== */

#include <xdc/std.h>
#include <string.h>
#include <xdc/runtime/Log.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/io/GIO.h>
#include <ti/sysbios/BIOS.h>
#include <xdc/runtime/System.h>
#include <ti/sysbios/io/IOM.h>
#include <ti/sysbios/knl/Swi.h>

#include <mcasp/bsp_mcasp.h>
#include <devices/bsp_aic31.h>
#include <audio/bsp_audio.h>
#include <ti/sdo/edma3/drv/edma3_drv.h>
#include <xdc/runtime/Error.h>
#include "platforms/bsp_platform.h"
#include <boards/bsp_board.h>
#include <devices/bsp_device.h>
#include <osal/bsp_osal.h>
#include <i2c/bsp_i2c.h>
#include <i2clib/lld_hsi2c.h>

#include <audioCommon_cfg.h>

/* ========================================================================== */
/*                           MACRO DEFINTIONS                                 */
/* ========================================================================== */

#define WR_MEM_32_VOLATILE(addr, data)    *(volatile uint32_t *) (addr) = \
    (uint32_t) (data)

#define RD_MEM_32_VOLATILE(addr)    *(volatile uint32_t *) (addr)

#if defined (TDA2XX_FAMILY_BUILD) && !defined (USE_JAMR_AUDIO)
I2c_DevInitParams     devI2cExpanderInitParams;
lld_hsi2c_initParam_t gI2cExpanderInitParams;
#endif
I2c_DevInitParams     devI2cAudioInitParams;
I2c_DevInitParams     devI2c2InitParams;
lld_hsi2c_initParam_t gI2cAudioInitParams;
lld_hsi2c_initParam_t gI2c2InitParams;

/*
 * Mcasp device params. To be filled in userMcaspInit function which
 * is called before driver creation
 */
Mcasp_Params          audioMcaspParams;

/*
 * Aic31 device params. To be filled in userAic31Init function which
 * is called before driver creation
 */
Aic31_Params          audioAic31Params;

/*
 * Audio device params. To be filled in userAudioInit function which
 * is called before driver creation
 */
Audio_Params          audioParams;

/* Handle to the EDMA driver instance                                         */
EDMA3_DRV_Handle      gEdmaHandle;

#if defined (BUILD_M4)
extern void Bsp_deviceI2cInit(void);
#endif
/* ========================================================================== */
/*                           FUNCTION DEFINITIONS                             */
/* ========================================================================== */
/**
 *  \brief  void main(void)
 *
 *   Main function of the sample application. This function enables
 *   the mcasp instance in the power sleep controller and also
 *   enables the pinmux for the mcasp 1 instance.
 *
 *  \param  None
 *  \return None
 */
Int32 main(void)
{
    Log_info0("\r\nAudio Sample Main\n");

    BIOS_start();

    return (0);
}

/*
 * Aic31 init function called when creating the driver.
 */
void audioUserAic31Init(void)
{
    Aic31_init();
    audioAic31Params = Aic31_PARAMS;
    audioAic31Params.acCtrlBusName    = AUDIO_CTRL_BUS;
    audioAic31Params.acType           = ICodec_CodecType_AIC31;
    audioAic31Params.acControlBusType = ICodec_ControlBusType_I2C;
#if defined (AIC_MASTER)
    audioAic31Params.acOpMode     = ICodec_OpMode_MASTER;
    audioAic31Params.isClkSrcMCLK = TRUE;
    audioAic31Params.acSlotWidth  = ICodec_SlotWidth_32;
#else /* McASP MASTER*/
    audioAic31Params.isClkSrcMCLK = (UInt32) TRUE;
    audioAic31Params.acOpMode     = ICodec_OpMode_SLAVE;
    #if defined (DSP_MODE)
    audioAic31Params.acSlotWidth = ICodec_SlotWidth_16;
    #else /* I2S MODE*/
    audioAic31Params.acSlotWidth = ICodec_SlotWidth_32;
    #endif
#endif

#if defined (DSP_MODE)
    audioAic31Params.acSerialDataType = ICodec_DataType_DSP;
#else /* I2S MODE*/
    audioAic31Params.acSerialDataType = ICodec_DataType_I2S;
#endif

    audioAic31Params.acDataPath = ICodec_DataPath_TXRX;
}

/*
 * Mcasp init function called when creating the driver.
 */
void audioUserMcaspInit(void)
{
#ifdef TDA2XX_FAMILY_BUILD
    Bsp_PlatformInitParams platInitPrms;
    Bsp_BoardInitParams    boardInitPrms;

    BspPlatformInitParams_init(&platInitPrms);
    BspBoardInitParams_init(&boardInitPrms);

    /* Call the EVM specific initialization function                          */
    Bsp_platformInit(&platInitPrms);
    Bsp_boardInit(&boardInitPrms);
#if defined (BUILD_M4)
    Bsp_deviceI2cInit();
#endif
    /* Set the pin Mux */
    Bsp_boardSetPinMux(BSP_DRV_ID_MCASP, BSP_DEVICE_MCASP_INST_ID_2,
                       BSP_BOARD_MODE_DEFAULT);
    Bsp_boardSetPinMux(BSP_DRV_ID_MCASP, BSP_DEVICE_MCASP_INST_ID_5,
                       BSP_BOARD_MODE_DEFAULT);
    Bsp_boardSetPinMux(BSP_DRV_ID_I2C, BSP_DEVICE_I2C_INST_ID_1,
                       BSP_BOARD_MODE_DEFAULT);
#endif

    Mcasp_init();
    audioMcaspParams             = Mcasp_PARAMS;
    audioMcaspParams.hwiNumber   = 9;
    audioMcaspParams.enablecache = (UInt32) TRUE;
    audioMcaspParams.isDataBufferPayloadStructure = (UInt32) FALSE;
}

Ptr NULLIOM_Params = NULL;

void user_prcm_init(void)
{
    /* Nothing to execute */
}

#if defined (TDA2XX_FAMILY_BUILD) && !defined (USE_JAMR_AUDIO)
/*
 * I2c init function called when creating the driver.
 */
void user_i2cExpander_init(void)
{
    gI2cExpanderInitParams.i2cIntNum  = I2C_EXPANDER_INT_NUM;
    gI2cExpanderInitParams.i2cBusFreq = I2C_NORMAL;

    /* configure I2c mode */
    gI2cExpanderInitParams.opMode       = HSI2C_OPMODE_INTERRUPT;
    gI2cExpanderInitParams.i2cOwnAddr   = 0x10;
    gI2cExpanderInitParams.is10BitAddr  = 0;
    gI2cExpanderInitParams.isMasterMode = 1;
    devI2cExpanderInitParams.initParams = &gI2cExpanderInitParams;
    devI2cExpanderInitParams.hsi2c_sem  = hsi2c_sem0;

    if (HSI2C_OPMODE_POLLED == gI2cExpanderInitParams.opMode)
    {
        System_printf("I2c is configured in polled mode \n");
    }
    else if (HSI2C_OPMODE_INTERRUPT == gI2cExpanderInitParams.opMode)
    {
        System_printf("I2c is configured in interrupt mode \n");
    }
    else
    {
        System_printf("Error: unknown mode of operation!!!!!!!!!!\n");
    }
}

#endif

void user_i2cAudio_init(void)
{
    /* hwiNumber mapped to eventID */
    gI2cAudioInitParams.i2cIntNum = I2C_AUDIO_INT_NUM;

    gI2cAudioInitParams.i2cBusFreq = I2C_NORMAL;

    /* configure I2c mode */
    gI2cAudioInitParams.opMode       = HSI2C_OPMODE_INTERRUPT;
    gI2cAudioInitParams.i2cOwnAddr   = 0xCC;
    gI2cAudioInitParams.is10BitAddr  = 0;
    gI2cAudioInitParams.isMasterMode = 1;
    devI2cAudioInitParams.initParams = &gI2cAudioInitParams;
    devI2cAudioInitParams.hsi2c_sem  = hsi2c_sem1;

    if (HSI2C_OPMODE_POLLED == gI2cAudioInitParams.opMode)
    {
        System_printf("I2c is configured in polled mode \n");
    }
    else if (HSI2C_OPMODE_INTERRUPT == gI2cAudioInitParams.opMode)
    {
        System_printf("I2c is configured in interrupt mode \n");
    }
    else
    {
        System_printf("Error: unknown mode of operation!!!!!!!!!!\n");
    }
}

void user_i2c2_init(void)
{
    /* hwiNumber mapped to eventID */
    gI2c2InitParams.i2cIntNum = I2C2_INT_NUM;

    gI2c2InitParams.i2cBusFreq = I2C_NORMAL;

    /* configure I2c mode */
    gI2c2InitParams.opMode       = HSI2C_OPMODE_INTERRUPT;
    gI2c2InitParams.i2cOwnAddr   = 0xCC;
    gI2c2InitParams.is10BitAddr  = 0;
    gI2c2InitParams.isMasterMode = 1;
    devI2c2InitParams.initParams = &gI2c2InitParams;
    devI2c2InitParams.hsi2c_sem  = hsi2c_sem1;

    if (HSI2C_OPMODE_POLLED == gI2c2InitParams.opMode)
    {
        System_printf("I2c is configured in polled mode \n");
    }
    else if (HSI2C_OPMODE_INTERRUPT == gI2c2InitParams.opMode)
    {
        System_printf("I2c is configured in interrupt mode \n");
    }
    else
    {
        System_printf("Error: unknown mode of operation!!!!!!!!!!\n");
    }
}

/*
 * Audio init function called when creating the driver.
 */
void audioUserAudioInit(void)
{
    Error_Block eb;

    Error_init(&eb);

    Audio_init();

    audioParams              = Audio_PARAMS;
    audioParams.adDevType    = AUDIO_DEVICETYPE_MCASP;
    audioParams.adDevName    = MCASP_DEVICE_NAME;
    audioParams.acNumCodecs  = 1;
    audioParams.acDevName[0] = "/aic310";
#ifdef TI814X_BUILD
    /* PRCM Enable for I2C0 */
    WR_MEM_32_VOLATILE(0x08181564, 0x2);
    while (RD_MEM_32_VOLATILE(0x08181564) != 0x2) ;

    /* PRCM Enable for MCASP2 */
    WR_MEM_32_VOLATILE(0x08181548, 0x2);
    while (RD_MEM_32_VOLATILE(0x08181548) != 0x2) ;
#endif
}

/* ========================================================================== */
/*                                END OF FILE                                 */
/* ========================================================================== */
