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
 *  \ingroup BSP_DRV_VPS_CAPTURE_API
 *  \defgroup BSP_DRV_VPS_CAPTURE_VIP_API VPS VIP Capture API
 *
 *  This modules define APIs to capture video data using VIP in VPS.
 *  @{
 */

/**
 *  \file vps_captureVip.h
 *
 *  \brief Video Capture API specific to VIP.
 */

#ifndef VPS_CAPTURE_VIP_H_
#define VPS_CAPTURE_VIP_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <vps/vps_dataTypes.h>
#include <vps/vps_captureVipDataTypes.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* VIP Capture IOCTL's */

/**
 *  \ingroup BSP_DRV_IOCTL_VPS_CAPTURE
 *  \defgroup BSP_DRV_IOCTL_VPS_CAPTURE_VIP VIP Capture IOCTL's
 *  @{
 */

/**
 *  \brief Set VIP parameters.
 *
 *  This IOCTL can be used to set the VIP hardware specific parameters.
 *  This IOCTL should be called after creating any VIP capture driver instance
 *  and before queueing or starting the capture driver. Starting the capture
 *  driver without calling this IOCTL will result in error.
 *
 *  Once the capture is started this IOCTL can't be invoked and will result in
 *  error.
 *
 *  Once the capture is stopped, application could call this IOCTL to
 *  reconfigure the VIP block with a different set of parameters.
 *
 *  \param cmdArgs       [IN]  const Vps_CaptVipParams *
 *  \param cmdArgsStatus [OUT] NULL
 *
 *  \return FVID2_SOK on success, else failure.
 */
#define IOCTL_VPS_CAPT_SET_VIP_PARAMS   (VPS_CAPT_VIP_IOCTL_BASE + 0x0000U)

/**
 *  \brief Get VIP parameters.
 *
 *  This IOCTL can be used to get the VIP hardware parameters.
 *  This IOCTL could be called at anytime after creating VIP capture
 *  driver instance.
 *
 *  \param cmdArgs       [IN]  Vps_CaptVipParams *
 *  \param cmdArgsStatus [OUT] NULL
 *
 *  \return FVID2_SOK on success, else failure.
 */
#define IOCTL_VPS_CAPT_GET_VIP_PARAMS   (VPS_CAPT_VIP_IOCTL_BASE + 0x0001U)

/**
 *  \brief Reset Video Port.
 *
 *  IMPORTANT: Cannot be used with ref \ref VPS_CAPT_INST_ALL handle
 *
 *  This IOCTL executes the reset sequence for video port associated
 *  with the given handle.
 *
 *  This will reset all the blocks used for that instance.
 *
 *  \param cmdArgs       [IN]  NULL
 *  \param cmdArgsStatus [OUT] NULL
 *
 *  \return FVID2_SOK on success, else failure.
 */
#define IOCTL_VPS_CAPT_RESET_VIP        (VPS_CAPT_VIP_IOCTL_BASE + 0x0002U)

/**
 *  \brief Set the VIP-VPDMA MAX SIZE_1/2/3 registers.
 *
 *  This IOCTL shall set the MAX_SIZE1, MAX_SIZE2, and MAX_SIZE3
 *  registers with the user-config information.
 *
 *  Note: This IOCTL should be called with the global capture handle.
 *
 *  \param cmdArgs       [IN]  const Vps_VpdmaMaxSizeParams *
 *  \param cmdArgsStatus [OUT] NULL
 *
 *  \return FVID2_SOK on success, else failure.
 */
#define IOCTL_VPS_CAPT_SET_VIP_MAX_SIZE (VPS_CAPT_VIP_IOCTL_BASE + 0x0003U)

/**
 *  \brief Stop VIP
 *
 *  This IOCTL can be used to stop the VIP instance in which the overflow
 * has occured. This will not execute the complete reset sequence on VIP. It
 * just sets the reset bit so that overflow stops and application comes out
 * of the ISR This can be called from the ISR context as this just sets a
 * bit in the register.
 *
 *  \param cmdArgs       [IN]  NULL
 *  \param cmdArgsStatus NULL
 *
 *  \return FVID2_SOK on success, else failure.
 */

#define IOCTL_VPS_CAPT_RESET_VIP_PORT     (VPS_CAPT_VIP_IOCTL_BASE + 0x0004U)

/* @} */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief Capture output format information
 */
typedef struct
{
    Fvid2_Format outFmt;
    /**<
     *   <b>width</b>:<br>
     *   Output width, in pixels.
     *   This represents the scaler output width to be programmed if scaler
     *   is used. Otherwise output width is equal to the capture source width
     *   or is limited by max width parameter. <br>
     *
     *   <b>height</b>:<br>
     *   Output height, in lines.
     *   This represents the scaler output height to be programmed if scaler
     *   is used. Otherwise output height is equal to the capture source height
     *   or is limited by max height parameter. <br>
     *
     *   <b>dataFormat</b>:<br>
     *   Output Data format, valid options are<br>
     *   FVID2_DF_YUV422I_YUYV,<br>
     *   FVID2_DF_YUV420SP_UV,<br>
     *   FVID2_DF_YUV422SP_UV,<br>
     *   FVID2_DF_RGB24_888,<br>
     *   FVID2_DF_RAW_VBI.<br>
     *   For valid values see #Fvid2_DataFormat.<br>
     *
     *   If FVID2_DF_YUV422SP_UV is used as output format, it must
     *   be the first output format (output format at the
     *   index 0 in outStreamInfo in #Vps_CaptCreateParams).
     *
     *   <b>pitch</b>:<br>
     *   Pitch in bytes between two lines.
     *   Pitch can be specified separately for every plane.
     *   And should be aligned to VPS_BUFFER_ALIGNMENT.<br>
     *
     *   <b>fieldMerged</b>:<br>
     *   Valid only in case of FVID2_BUF_FMT_FRAME buffer format and
     *   interlaced capture mode. <br>
     *   TRUE - Fields are merged. Driver programs difference between each line
     *   as pitch * 2. Application has to provide bottom field address
     *   as top field address + pitch (next line).
     *   FALSE - Fields are separated. Driver programs difference between
     *   each line as pitch * 1 only. Top and bottom field buffers could be
     *   in entirely different buffer location.
     *
     *   <b>chNum, scanFormat, bpp</b>: Not used, set to 0 or default. */
    UInt32             bufFmt;
    /**< Frame capture or field capture for interlaced scan format.
     *   For valid values see #Fvid2_BufferFormat. */
    UInt32             memType;
    /**< Tiled or non-tiled memory selection for output.
     *   For valid values see #Vps_VpdmaMemoryType.
     *
     *   For FVID2_DF_YUV422I_YUYV, FVID2_DF_RGB24_888, FVID2_DF_RAW_VBI
     *   output, always VPS_VPDMA_MT_NONTILEDMEM will be used internally.
     *
     *   User can control tiled or non-tiled for FVID2_DF_YUV420SP_UV,
     *   FVID2_DF_YUV422SP_UV. */

    UInt32             maxOutWidth[FVID2_MAX_PLANES];
    /**< Set limit on the max possible width of the output frame
     *   For valid values see #Vps_VpdmaMaxOutWidth. */
    UInt32             maxOutHeight[FVID2_MAX_PLANES];
    /**< Set limit on the max possible height of the output frame
     *   For valid values see #Vps_VpdmaMaxOutHeight. */

    UInt32             scEnable;
    /**< TRUE: Use scaler before writing video data to memory,
     *   FALSE: Scaler is not used in capture path
     *   MUST be FALSE for line-multiplexed, pixel multiplexed modes. */

    Vps_SubFrameParams subFrmPrms;
    /**< Sub frame parameters. */
} Vps_CaptVipOutInfo;

/**
 *  \brief VIP parameters used in set/get VIP params IOCTL.
 */
typedef struct
{
    Fvid2_Format inFmt;
    /**<
     *   <b>width</b>:<br>
     *   Input source width, MUST be >= actual or expected
     *   video source input width.
     *   This represents the scaler input width to be programmed if scaler
     *   is used.<br>
     *
     *   <b>height</b>:<br>
     *   Input source height, MUST be >= actual or expected
     *   video source input height.
     *   This represents the scaler input height to be programmed if scaler
     *   is used.<br>
     *   Height should be field height in case source is interlaced<br>
     *   Height should be frame height in case source is progressive<br>
     *
     *   <b>dataFormat</b>:<br>
     *   Input source color data format, valid values are given below<br>
     *   FVID2_DF_YUV422P, ('P' is not relavent for input data format)<br>
     *   FVID2_DF_YUV444P, ('P' is not relavent for input data format)<br>
     *   FVID2_DF_RGB24_888.<br>
     *   For valid values see #Fvid2_DataFormat.<br>
     *
     *   <b>scanFormat</b>:<br>
     *   Input source scan format - interlaced or progressive.
     *   For valid values see #Fvid2_ScanFormat.<br>
     *
     *   <b>chNum, pitch, fieldMerged, bpp</b>: Not used, set to 0 or default.
     * */
    Vps_CaptVipOutInfo   outStreamInfo[VPS_CAPT_VIP_STREAM_ID_MAX];
    /**< Output format for each stream. The number of valid entries should
     *   match the numStream parameter provided at create time. */

    Vps_CaptVipScParams *scPrms;
    /**< Scaler parameters to use when
     *   Vps_CaptCreateParams.outStreamInfo[x].scEnable = TRUE
     *   Parameters are ignored when outStreamInfo[x].scEnable = FALSE.
     *
     *   Note: Upscaling is not supported in the inline scaling in capture
     *   path because of hardware limitation. */
    Vps_VipPortConfig   *vipPortCfg;
    /**< VIP Parser port config, set NULL to ignore these parameters. */
    Vps_CscConfig       *cscCfg;
    /**< CSC config, set NULL to ignore these parameters. */
} Vps_CaptVipParams;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief Vps_CaptVipOutInfo structure init function.
 *
 *  \param vipOutInfo   [IN] Pointer to #Vps_CaptVipOutInfo structure.
 *
 */
static inline void VpsCaptVipOutInfo_init(Vps_CaptVipOutInfo *vipOutInfo);

/**
 *  \brief Vps_CaptVipParams structure init function.
 *
 *  \param vipPrms      [IN] Pointer to #Vps_CaptVipParams structure.
 *
 */
static inline void VpsCaptVipParams_init(Vps_CaptVipParams *vipPrms);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

static inline void VpsCaptVipOutInfo_init(Vps_CaptVipOutInfo *vipOutInfo)
{
    UInt32 plId;

    if (NULL != vipOutInfo)
    {
        Fvid2Format_init(&vipOutInfo->outFmt);
        vipOutInfo->bufFmt  = FVID2_BUF_FMT_FIELD;
        vipOutInfo->memType = VPS_VPDMA_MT_NONTILEDMEM;
        for (plId = 0U; plId < FVID2_MAX_PLANES; plId++)
        {
            vipOutInfo->maxOutWidth[plId]  = VPS_VPDMA_MAX_OUT_WIDTH_UNLIMITED;
            vipOutInfo->maxOutHeight[plId] = VPS_VPDMA_MAX_OUT_HEIGHT_UNLIMITED;
        }
        vipOutInfo->scEnable = FALSE;
        VpsSubFrameParams_init(&vipOutInfo->subFrmPrms);
    }

    return;
}

static inline void VpsCaptVipParams_init(Vps_CaptVipParams *vipPrms)
{
    UInt32 streamId;

    if (NULL != vipPrms)
    {
        Fvid2Format_init(&vipPrms->inFmt);
        for (streamId = 0U; streamId < VPS_CAPT_VIP_STREAM_ID_MAX; streamId++)
        {
            VpsCaptVipOutInfo_init(&vipPrms->outStreamInfo[streamId]);
        }
        vipPrms->scPrms     = NULL;
        vipPrms->vipPortCfg = NULL;
        vipPrms->cscCfg     = NULL;
    }

    return;
}

#ifdef __cplusplus
}
#endif

#endif /* #ifndef VPS_CAPTURE_VIP_H_ */

/* @} */
