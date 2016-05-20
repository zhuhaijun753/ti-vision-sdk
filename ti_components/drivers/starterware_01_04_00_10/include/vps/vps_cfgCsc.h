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
 *  \addtogroup BSP_DRV_VPS_COMMON_CSC VPS - CSC Config API
 *
 *  @{
 */

/**
 *  \file vps_cfgCsc.h
 *
 *  \brief VPS - CSC Config API
 */

#ifndef VPS_CFG_CSC_H_
#define VPS_CFG_CSC_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <common/bsp_types.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Num of coefficients in each set */
#define VPS_CSC_NUM_COEFF           (3U)

/**
 *  \brief Enum for specifying per-defined CSC co-effs
 */
typedef enum
{
    VPS_CSC_MODE_SDTV_LIMITED_RANGE_R2Y,
    /**< Select coefficient for SDTV limited range. */
    VPS_CSC_MODE_SDTV_LIMITED_RANGE_Y2R,
    /**< Select coefficient for SDTV limited range. */
    VPS_CSC_MODE_SDTV_FULL_RANGE_R2Y,
    /**< Select coefficient for SDTV full range. */
    VPS_CSC_MODE_SDTV_FULL_RANGE_Y2R,
    /**< Select coefficient for SDTV full range. */
    VPS_CSC_MODE_HDTV_LIMITED_RANGE_R2Y,
    /**< Select coefficient for HDTV limited range. */
    VPS_CSC_MODE_HDTV_LIMITED_RANGE_Y2R,
    /**< Select coefficient for HDTV limited range. */
    VPS_CSC_MODE_HDTV_FULL_RANGE_R2Y,
    /**< Select coefficient for HDTV full range. */
    VPS_CSC_MODE_HDTV_FULL_RANGE_Y2R,
    /**< Select coefficient for HDTV full range. */
    VPS_CSC_MODE_MAX,
    /**< Should be the last value of this enumeration.
     *   Will be used by driver for validating the input parameters. */
    VPS_CSC_MODE_AUTO,
    /**< Core will select coefficients as per input parameters assuming
     *   full range colorspace */
    VPS_CSC_MODE_NONE
    /**< Used when user coefficients are provided. */
} Vps_CscMode;

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  struct Vps_CscCoeff
 * \brief Set the Coefficients for Color Space Conversion.
 */
typedef struct
{
    UInt32 mulCoeff[VPS_CSC_NUM_COEFF][VPS_CSC_NUM_COEFF];
    /**< Multiplication coefficients in the format
     *  {{A0, B0, C0},
     *   {A1, B1, C1},
     *   {A2, B2, C2}}
     */
    UInt32 addCoeff[VPS_CSC_NUM_COEFF];
    /**< Addition Coefficients
     *   {D0, D1, D2}}
     */
} Vps_CscCoeff;

/**
 *  struct Vps_CscConfig
 *  \brief Configuration parameters for CSC.
 */
typedef struct
{
    UInt32        bypass;
    /**< Flag to indicate whether CSC to be bypassed or not. */
    UInt32        mode;
    /**< Used to select one of pre-calculated coefficient sets. Used only
     *   if coeff is null. For valid values see #Vps_CscMode. */
    Vps_CscCoeff *coeff;
    /**< Set of user provided coefficients. Null if pre-calculated
     *   coefficients is to be used. */
} Vps_CscConfig;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief Vps_CscConfig structure init function.
 *
 *  \param cscCfg       [IN] Pointer to #Vps_CscConfig structure.
 *
 */
static inline void VpsCscConfig_init(Vps_CscConfig *cscCfg);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

static inline void VpsCscConfig_init(Vps_CscConfig *cscCfg)
{
    if (NULL != cscCfg)
    {
        cscCfg->bypass = (UInt32) TRUE;
        cscCfg->mode   = VPS_CSC_MODE_AUTO;
        cscCfg->coeff  = NULL;
    }

    return;
}

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef VPS_CFG_CSC_H_ */

/* @} */
