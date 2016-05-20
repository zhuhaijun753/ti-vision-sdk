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
 *  \addtogroup BSP_DRV_VPS_CAPTURE_VIP_API VPS VIP Capture API
 *
 *  This modules define datatypes to capture video data using VIP in VPS.
 *  @{
 */

/**
 *  \file vps_captureVipDataTypes.h
 *
 *  \brief Video Capture API specific to VIP.
 */

#ifndef VPS_CAPTURE_VIP_DATATYPES_H_
#define VPS_CAPTURE_VIP_DATATYPES_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <vps/vps_dataTypes.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief VIP 1 instance ID. */
#define VPS_VIP1                        (0U)
/** \brief VIP 2 instance ID. */
#define VPS_VIP2                        (1U)
/** \brief VIP 3 instance ID. */
#define VPS_VIP3                        (2U)

#if defined (TDA2XX_FAMILY_BUILD)
  #ifdef TDA2EX_BUILD
/** \brief Maximum number of VIP instances. */
#define VPS_VIP_MAX                     (1U)
  #else
/** \brief Maximum number of VIP instances. */
#define VPS_VIP_MAX                     (3U)
  #endif
#else
/** \brief Maximum number of VIP instances. */
#define VPS_VIP_MAX                     (1U)
#endif

/** \brief VIP Slice 0 ID. */
#define VPS_VIP_S0                      (uint32_t) (0U)
/** \brief VIP Slice 1 ID. */
#define VPS_VIP_S1                      (uint32_t) (1U)
/** \brief Maximum number of slice per VIP. */
#define VPS_VIP_SLICE_MAX               (uint32_t) (2U)

/** \brief VIP PORT A ID. */
#define VPS_VIP_PORTA                   (uint32_t) (0U)
/** \brief VIP PORT B ID. */
#define VPS_VIP_PORTB                   (uint32_t) (1U)
/** \brief Maximum number of port per slice. */
#define VPS_VIP_PORT_MAX                (uint32_t) (2U)

/**
 *  \brief Maximum stream's that can be captured per channel.
 *
 *  Stream's corresponds to different types of output that are possible
 *  for a given capture input source.
 *
 *  The stream output type is setup by user during Fvid2_create()
 *
 *  Example streams are,
 *
 *  For a 1080P input source,
 *  Stream 0: YUV420 non-scaled output
 *  Stream 1: YUV422 scaled output
 *  Stream 2: RAW VBI output
 *
 *  Refer to user guide for more details about what valid stream
 *  combinations are possible.
 */
#define VPS_CAPT_VIP_STREAM_ID_MAX (4U)

/**
 * There are 3 32-bit MAX_SIZE registers supported for TDA2XX platform family.
 * These registers provide two parameters width[31:16] and height[15:0].
 * The VPDMA transmits to external buffer the maximum out width number of
 * pixels and maximum out height number of pixel lines.
 * If the VIP receives data exceeding the maximum out width/height then it
 * continues to capture the data. VPDMA will not transfer it to the
 * external buffer.
 * This register (if used) should have valid range of values.
 * The valid range for maximum out width shall be [1, 4096]
 * The valid range for maximum out height shall be [1, 2048]
 * Example: For a YUV420SP capture,
 * For luma, the maximum out [width, height] can go up to [2048, 2048].
 * For chroma, the maximum out [width, height] can go up to [2048, 1024].
 * Example: For a YUV422I capture,
 * For luma, the maximum out [width, height] can go up to [4096, 2048].
 */
/** \brief Minimum allowable width for MAX_SIZE register. */
#define VPS_VIP_MAXSIZE_MIN_WIDTH       (1U)
/** \brief Maximum allowable width for MAX_SIZE register. */
#define VPS_VIP_MAXSIZE_MAX_WIDTH       (4096U)
/** \brief Minimum allowable height for MAX_SIZE register. */
#define VPS_VIP_MAXSIZE_MIN_HEIGHT      (1U)
/** \brief Maximum allowable height for MAX_SIZE register. */
#define VPS_VIP_MAXSIZE_MAX_HEIGHT      (2048U)

/**
 *  \brief Macro to generate VIP capture driver instance ID to be passed
 *  during create parameter.
 *
 *  vipId   -   VPS_VIP1, VPS_VIP2 or VPS_VIP3<br>
 *  sliceId -   VPS_VIP_S0 or VPS_VIP_S1<br>
 *  portId  -   VPS_VIP_PORTA or VPS_VIP_PORTB
 */
#define VPS_CAPT_VIP_MAKE_INST_ID(vipId, sliceId, portId) \
    ((portId) +                                           \
     ((sliceId) * (VPS_VIP_PORT_MAX)) +                   \
     ((vipId) * (VPS_VIP_SLICE_MAX * VPS_VIP_PORT_MAX)))

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief Capture scaler information.
 *
 *  Only valid when Vps_CaptVipOutInfo.scEnable is or can be TRUE.
 *
 *  Note, upscaling is not supported for capture path
 */
typedef struct
{
    Fvid2_CropConfig   inCropCfg;
    /**< Scaler input crop config. */
    Vps_ScConfig       scCfg;
    /**< Scaler config. */
    Vps_ScCoeffParams *scCoeffCfg;
    /**< Scaler coeff config. */
    UInt32             enableCoeffLoad;
    /**< Enable scaler coefficient load during IOCTL_VPS_CAPT_SET_SC_PARAMS
     *   If this is set to TRUE, it may result in the instance getting
     *   stopped, reset, and restarted to load new coefficients as per the
     *   provided new scaling factor. This may result in some frame loss.
     *   The scaler coefficients are loaded only if there is a change in either
     *   the horizontal or vertical scaling set. The best scaler coefficients to
     *   be used are determined internally when scCoeffConfig in this structure
     *   is set to NULL.
     *   If the user has provided scaler coefficients or coefficient sets to be
     *   used, these are used instead of internally calculating the best scaler
     *   coefficients. */
} Vps_CaptVipScParams;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief Get VIP instance ID from VIP capture driver instance ID.
 *
 *  \param vipInstId    [IN] Valid capture driver instance generated by
 *                           #VPS_CAPT_VIP_MAKE_INST_ID().
 *
 *  \return VIP instance ID (VPS_VIP1, VPS_VIP2 or VPS_VIP3)
 */
static inline UInt32 Vps_captGetVipId(UInt32 vipInstId);

/**
 *  \brief Get VIP slice ID from VIP capture driver instance ID.
 *
 *  \param vipInstId    [IN] Valid capture driver instance generated by
 *                           #VPS_CAPT_VIP_MAKE_INST_ID().
 *
 *  \return VIP slice ID (VPS_VIP_S0 or VPS_VIP_S1)
 */
static inline UInt32 Vps_captGetVipSliceId(UInt32 vipInstId);

/**
 *  \brief Get VIP port ID from VIP capture driver instance ID.
 *
 *  \param vipInstId    [IN] Valid capture driver instance generated by
 *                           #VPS_CAPT_VIP_MAKE_INST_ID().
 *
 *  \return VIP port ID (VPS_VIP_PORTA or VPS_VIP_PORTB)
 */
static inline UInt32 Vps_captGetPortId(UInt32 vipInstId);

/**
 *  \brief Vps_CaptVipScParams structure init function.
 *
 *  \param vipScPrms    [IN] Pointer to #Vps_CaptVipScParams structure.
 *
 */
static inline void VpsCaptVipScParams_init(Vps_CaptVipScParams *vipScPrms);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

static inline UInt32 Vps_captGetVipId(UInt32 vipInstId)
{
    return (vipInstId / (VPS_VIP_SLICE_MAX * VPS_VIP_PORT_MAX));
}

static inline UInt32 Vps_captGetVipSliceId(UInt32 vipInstId)
{
    return ((vipInstId % (VPS_VIP_SLICE_MAX * VPS_VIP_PORT_MAX)) /
            VPS_VIP_PORT_MAX);
}

static inline UInt32 Vps_captGetPortId(UInt32 vipInstId)
{
    return (vipInstId % VPS_VIP_PORT_MAX);
}

static inline void VpsCaptVipScParams_init(Vps_CaptVipScParams *vipScPrms)
{
    if (NULL != vipScPrms)
    {
        Fvid2CropConfig_init(&vipScPrms->inCropCfg);
        VpsScConfig_init(&vipScPrms->scCfg);
        vipScPrms->scCoeffCfg      = NULL;
        vipScPrms->enableCoeffLoad = (UInt32) FALSE;
    }

    return;
}

#ifdef __cplusplus
}
#endif

#endif /* #ifndef VPS_CAPTURE_VIP_DATATYPES_H_ */

/* @} */
