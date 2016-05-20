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
 *  \ingroup BSP_DRV_DEVICE_VID_DEC_API
 *  \defgroup BSP_DRV_DEVICE_VID_DEC_TVP5158_API TVP5158 Video Decoder API
 *
 *  This modules define API specific to TVP5158.
 *
 *  @{
 */

/**
 *  \file bsp_tvp5158.h
 *
 *  \brief TVP5158 Video Decoder API.
 */

#ifndef BSP_TVP5158_H_
#define BSP_TVP5158_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <devices/bsp_videoDecoder.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \addtogroup BSP_DRV_IOCTL_TVP5158
 *  @{
 */

/**
 *  \brief Set TVP5158 video noise filter parameters.
 *
 *  This IOCTL can be called separetly for each channel.
 *
 *  \param cmdArgs       [IN]   Bsp_Tvp5158VideoNfParams *
 *  \param cmdArgsStatus [OUT]  NULL
 *
 *  \return FVID2_SOK on success, else failure.
 */
#define IOCTL_BSP_TVP5158_SET_VIDEO_NF      (BSP_VID_DEC_IOCTL_BASE + 0x1000U)

/**
 *  \brief Set TVP5158 video noise filter parameters.
 *
 *  This IOCTL can be called separetly for each channel.
 *
 *  \param cmdArgs       [IN]   Bsp_Tvp5158AudioModeParams *
 *  \param cmdArgsStatus [OUT]  NULL
 *
 *  \return FVID2_SOK on success, else failure.
 */
#define IOCTL_BSP_TVP5158_SET_AUDIO_MODE    (BSP_VID_DEC_IOCTL_BASE + 0x1001U)

/* @} */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief Arguments for IOCTL_BSP_TVP5158_SET_VIDEO_NF.
 */
typedef struct
{
    UInt32 channelNum;
    /**< Channel number for which these parameters are to be applied. */
    UInt32 nfEnable;
    /**< TRUE: Noise filter ON, FALSE: Noise filter OFF. */
    UInt32 colorKillerEnable;
    /**< TRUE: Reduce color when noise is HIGH, FALSE: Do not reduce color. */
    UInt32 maxNoise;
    /**< Max noise level. */
} Bsp_Tvp5158VideoNfParams;

/**
 *  \brief Arguments for IOCTL_BSP_TVP5158_SET_AUDIO_MODE.
 *
 *  The audio mode is applicable for all channels associated with the
 *  device 'deviceNum'.
 */
typedef struct
{
    UInt32 deviceNum;
    /**< Device number for which to apply the audio parameters. */
    UInt32 samplingHz;
    /**< Audio sampling rate in Hz, Valid values: 8000, 16000. */
    UInt32 masterModeEnable;
    /**< TRUE: Master mode of operation, FALSE: Slave mode of operation. */
    UInt32 dspModeEnable;
    /**< TRUE: DSP data format mode, FALSE: I2S data format mode. */
    UInt32 ulawEnable;
    /**< TRUE: 8-bit ulaw data format mode, FALSE: 16-bit PCM data
     *   format mode. */
    UInt32 cascadeStage;
    /**< Cascade stage number, Valid values: 0..3. */
    UInt32 audioVolume;
    /**< Audio volume, Valid values: 0..8. Refer to TVP5158 datasheet
     *   for details. */
    UInt32 tdmChannelNum;
    /**< Number of TDM channels: 0: 2CH, 1: 4CH, 2: 8CH, 3: 12CH 4: 16CH. */
} Bsp_Tvp5158AudioModeParams;

/* ========================================================================== */
/*                         Functions                                          */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef BSP_TVP5158_H_ */

/* @} */
