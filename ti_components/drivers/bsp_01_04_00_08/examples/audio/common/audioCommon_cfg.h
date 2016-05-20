/******************************************************************************
 *                                                                            *
 * Copyright (c) 2014 Texas Instruments Incorporated - http://www.ti.com/     *
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

/** \file     audioLoopbackSample_cfg.h
 *
 *  \brief    Provides audio loopback example configuration
 *
 *  This file contains the implementation of the sample appliation for the
 *  demonstration of audio playing through the audio interface layer.
 *
 *             (C) Copyright 2014, Texas Instruments, Inc
 */

/* ========================================================================== */
/*                            INCLUDE FILES                                   */
/* ========================================================================== */

/* Compiler switch to use JAMR audio.
 * !!! NOTE - this is defined by useJAMR field in .cfg file. !!! */
#include <xdc/cfg/global.h>
#if (USE_JAMR)
    #define USE_JAMR_AUDIO
#endif

#if defined (USE_JAMR_AUDIO) && defined (BUILD_DSP) && (defined (TDA2XX_BUILD) || defined (DRA7XX_BUILD))
    #define AUDIO_CTRL_BUS          "i2c1"
    #define MCASP_DEVICE_NAME       "/mcasp5"
    #define I2C_AUDIO_INT_NUM       83
    #define I2C2_INT_NUM            52
#elif !defined (USE_JAMR_AUDIO) && defined (BUILD_DSP) && (defined (TDA2XX_BUILD) || defined (DRA7XX_BUILD))
    #define AUDIO_CTRL_BUS          "i2c0"
    #define EXPANDER_CTRL_BUS       "i2c1"
    #define MCASP_DEVICE_NAME       "/mcasp2"
    #define I2C_AUDIO_INT_NUM       82
    #define I2C2_INT_NUM            52
    #define I2C_EXPANDER_INT_NUM    83
#elif defined (USE_JAMR_AUDIO) && defined (BUILD_M4) && (defined (TDA2XX_BUILD) || defined (DRA7XX_BUILD))
    #define AUDIO_CTRL_BUS          "i2c1"
    #define MCASP_DEVICE_NAME       "/mcasp5"
    #define I2C_AUDIO_INT_NUM       42
    #define I2C2_INT_NUM            52
#elif !defined (USE_JAMR_AUDIO) && defined (BUILD_M4) && (defined (TDA2XX_BUILD) || defined (DRA7XX_BUILD))
    #define AUDIO_CTRL_BUS          "i2c0"
    #define EXPANDER_CTRL_BUS       "i2c1"
    #define MCASP_DEVICE_NAME       "/mcasp2"
    #define I2C_AUDIO_INT_NUM       41
    #define I2C2_INT_NUM            52
    #define I2C_EXPANDER_INT_NUM    42
#elif defined (USE_JAMR_AUDIO) && defined (BUILD_DSP) && defined (TDA2EX_BUILD)
    #define AUDIO_CTRL_BUS          "i2c4"
    #define MCASP_DEVICE_NAME       "/mcasp5"
    #define I2C_AUDIO_INT_NUM       83
    #define I2C2_INT_NUM            52
#elif !defined (USE_JAMR_AUDIO) && defined (BUILD_DSP) && defined (TDA2EX_BUILD)
    #define AUDIO_CTRL_BUS          "i2c0"
    #define EXPANDER_CTRL_BUS       "i2c4"
    #define MCASP_DEVICE_NAME       "/mcasp2"
    #define I2C_AUDIO_INT_NUM       82
    #define I2C2_INT_NUM            52
    #define I2C_EXPANDER_INT_NUM    83
#elif defined (USE_JAMR_AUDIO) && defined (BUILD_M4) && defined (TDA2EX_BUILD)
    #define AUDIO_CTRL_BUS          "i2c4"
    #define MCASP_DEVICE_NAME       "/mcasp5"
    #define I2C_AUDIO_INT_NUM       42
    #define I2C2_INT_NUM            52
#elif !defined (USE_JAMR_AUDIO) && defined (BUILD_M4) && defined (TDA2EX_BUILD)
    #define AUDIO_CTRL_BUS          "i2c0"
    #define EXPANDER_CTRL_BUS       "i2c4"
    #define MCASP_DEVICE_NAME       "/mcasp2"
    #define I2C_AUDIO_INT_NUM       41
    #define I2C2_INT_NUM            52
    #define I2C_EXPANDER_INT_NUM    42
#elif !defined (USE_JAMR_AUDIO) && defined (BUILD_DSP) && defined (TI814X_FAMILY_BUILD)
    #define AUDIO_CTRL_BUS          "i2c0"
    #define MCASP_DEVICE_NAME       "/mcasp2"
    #define I2C_AUDIO_INT_NUM       58
    #define I2C2_INT_NUM            52
#elif defined (USE_JAMR_AUDIO) && defined (BUILD_DSP) && defined (TI814X_FAMILY_BUILD)
    #define AUDIO_CTRL_BUS          "i2c2"
    #define MCASP_DEVICE_NAME       "/mcasp5"
    #define I2C_AUDIO_INT_NUM       89
    #define I2C2_INT_NUM            52
#endif
