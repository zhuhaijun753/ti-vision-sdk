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
 *  \ingroup BSP_DRV_VPS_COMMON_API
 *  \addtogroup BSP_DRV_VPS_COMMON_DEI VPS - De-interlacer Config API
 *
 *  @{
 */

/**
 *  \file vps_advCfgDei.h
 *
 *  \brief VPS - De-interlacer Advanced Configurations options.
 */

#ifndef VPS_ADV_CFG_DEI_H_
#define VPS_ADV_CFG_DEI_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief MDT configuration related macros. */
#define VPS_DEI_MDT_MAX_SF_SC_THR       (3U)

/** \brief EDI configuration related macros. */
#define VPS_DEI_EDI_MAX_LUT             (16U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  struct Vps_DeiMdtConfig
 *  \brief DEI Motion Dection (MDT) configuration.
 */
typedef struct
{
    UInt32 spatMaxBypass;
    /**< Bypass spatial maximum filtering. */
    UInt32 tempMaxBypass;
    /**< Bypass temporal maximum filtering. */
    UInt32 mvstmMaxCorThr;
    /**< This threshold is for the coring for the spatial-maximum maximum
     *   output of motion values. It is used for increasing noise
     *   robustness. Increasing this threshold leads to more robustness
     *   to noise, but with the potential of introducing ghosting effect.
     *   Note that this threshold is used for motion values for EDI only,
     *   and it is in addition mdt_mv_cor_thr. */
    UInt32 mvCorThr;
    /**< This is the coring threshold for motion value, mv.
     *   MDT will become more noise robust if this value increases.
     *   But the picture may be washed out if this value is set to
     *   high. This threshold can be interpreted as the noise threshold
     *   for calculating motion values for all blocks. */
    UInt32 sfScThr[VPS_DEI_MDT_MAX_SF_SC_THR];
    /**< Spatial frequency threshold. It is used for adaptive scaling
     *   of motion values according to how busy the texture is. If
     *   the texture is flat, motion values need to be scaled up to
     *   reflect the sensitivity of motion values with respect to
     *   the detection error. Increasing the thresholds will make the
     *   motion value scaling more sensitive to the frequency of the
     *   texture. Note that 0<= sfScThr[0] <= sfScThr[1] <= sfScThr[2]
     *   must hold. */
} Vps_DeiMdtConfig;

/**
 *  struct Vps_DeiEdiConfig
 *  \brief Edge Directed Interpolation (EDI) configuration.
 */
typedef struct
{
    UInt32 inpMode;
    /**< Interpolation mode. For valid values see #Vps_DeiEdiMode. */
    UInt32 tempInpEnable;
    /**< 3D processing (temporal interpolation). */
    UInt32 tempInpChromaEnable;
    /**< 3D processing for chroma. */
    UInt32 corScaleFactor;
    /**< Scaling factor for correlation along detected edge. */
    UInt32 detCorLowerThr;
    /**< Lower threshold used for correlation along detected edge */
    UInt32 chroma3DCorThr;
    /**< Correlation threshold used in 3D processing for chroma. Because
     *   the motion values used for chroma 3D processing are based on
     *   luma only. Extra protection is needed. Temporal interpolation is
     *   only performed for chroma, when there is strong spatial or
     *   temporal correlation for the chroma pixel being processed. When
     *   the pixel difference is less than this threshold, it is
     *   assumed that there exists strong correlation between these
     *   two pixels. Thus, increasing this value leads to more chroma
     *   pixels being processed in 3D. */
    UInt32 lut[VPS_DEI_EDI_MAX_LUT];
    /**< The EDI lookup table maps motion values to the coefficient
     *   of temporal filter. Increasing the values leads to favoring
     *   2D interpolated results.
     *   Following must hold: 0<=lut0<=lut1<=lut2<=…<=lut15. */
} Vps_DeiEdiConfig;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef VPS_ADV_CFG_DEI_H_ */

/* @} */
