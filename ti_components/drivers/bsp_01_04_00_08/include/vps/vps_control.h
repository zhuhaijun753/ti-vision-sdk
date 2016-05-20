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
 *  \ingroup BSP_DRV_VPS_API
 *  \defgroup BSP_DRV_VPS_CTRL_API VPS Control driver API
 *
 *  @{
 */

/**
 *  \file vps_control.h
 *
 *  \brief VPS Control Driver.
 *  VPS Control Driver Interface file.
 */

#ifndef VPS_CONTROL_H_
#define VPS_CONTROL_H_

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

/**
 *  \name VPS control instance ID's
 *
 *  @{
 */

/** \brief VPS control driver instance 0 - only one instance is supported. */
#define VPS_CTRL_INST_0                 ((UInt32) 0U)

/* @} */

/*
 *  VPS control driver IOCTLs.
 */

/**
 *  \addtogroup BSP_DRV_IOCTL_VPS_CTRL
 *  @{
 */

/**
 *  \brief Enable/disable Lazy Loading for a scaler.
 *
 *  This IOCTL should be called only when the VPE instance corresponding to
 *  vpeInstId is not opened. Otherwise this IOCTL will return error.
 *
 *  \param cmdArgs       [IN]  const Vps_ScLazyLoadingParams *
 *  \param cmdStatusArgs [OUT] NULL
 *
 *  \return FVID_SOK on success, else failure
 *
 */
#define IOCTL_VPS_CTRL_SET_VPE_LAZY_LOADING (VPS_CTRL_IOCTL_BASE + 0x0000U)

/* @} */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  struct Vps_ScLazyLoadingParams
 *  \brief Application interface structure for setting Lazy Loading
 *  configuration for scaler.
 */
typedef struct
{
    UInt32 vpeInstId;
    /**< VPE driver instance ID. Applicable if multiple VPE instances are
     *   present. Refer VPE header file for specific values. */
    UInt32 scalerId;
    /**< Scaler ID - Used in case multiple scalers are present in a driver.
     *   Refer VPE header file for specific values. */
    UInt32 lazyLoadingEnable;
    /**< Indicates whether lazy loading is to be enabled.
     *   If TRUE, lazy loading is to be enabled.
     *   If FALSE, lazy loading is to be disabled. */
} Vps_ScLazyLoadingParams;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief Vps_ScLazyLoadingParams structure init function.
 *
 *  \param prms         [IN] Pointer to #Vps_ScLazyLoadingParams structure.
 *
 */
static inline void VpsScLazyLoadingParams_init(Vps_ScLazyLoadingParams *prms);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

static inline void VpsScLazyLoadingParams_init(Vps_ScLazyLoadingParams *prms)
{
    if (NULL != prms)
    {
        prms->scalerId          = 0U;
        prms->lazyLoadingEnable = TRUE;
    }

    return;
}

#ifdef __cplusplus
}
#endif

#endif /* #ifndef VPS_CONTROL_H_ */

/* @} */
