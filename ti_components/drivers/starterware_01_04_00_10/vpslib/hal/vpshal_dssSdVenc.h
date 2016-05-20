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
 *  \file vpshal_dssSdVenc.h
 *
 *  \brief HAL Header file for SD-VENC
 *  This file exposes the HAL APIs of the SD-VENC module
 *
 */

#ifndef VPSHAL_SDVENC_H_
#define VPSHAL_SDVENC_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <hal/vpshal.h>

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C"
{
#endif

/**
 *  VpsHal_dssSdVencInit
 *  \brief SDVENC HAL init function.
 *  This function should be called before calling any of SD-VENC HAL API's.
 *
 *
 *  \return                   success    0
 *                            failure    error value
 *
 */

Int32 VpsHal_dssSdVencInit(void);

/**
 *  VpsHal_dssSdVencDeInit
 *  \brief SDVENC HAL Deinit function.
 *
 *  \return                success    0
 *                            failure    error value
 *
 */
Int32 VpsHal_dssSdVencDeInit(void);

/**
 *  VpsHal_dssSdVencConfigure
 *  \brief Configures SDVENC for a particular video standard
 *  This function will configure the SD-VENC for a particular video mode.
 *
 *  \return                   success    0
 *                            failure    error value
 *
 */
Int32 VpsHal_dssSdVencConfigure(UInt32 videoStandard);

/**
 *  VpsHal_dssGetDefAdvSdVencParams
 *  \brief Initialize the config object with default parameters.
 *  This function will initialize the Vps_DssDispcSdVencAdvConfig object with
 *  the default settings based on the config.videoStandard variable.
 *  The initialized object can be passed to the
 *  VpsHal_dssSetAdvSdVencParams function.
 *
 *  \param                  pointer to Vps_DssDispcSdVencAdvConfig structure
 *                          Vps_DssDispcSdVencAdvConfig->videoStandard
 *                          should be set to get proper default values
 *  \return                 success    0
 *                          failure    error value
 *
 */
Int32 VpsHal_dssGetDefAdvSdVencParams(Vps_DssDispcSdVencAdvConfig *config);

/**
 *  VpsHal_dssSetAdvSdVencParams
 *  \brief Configures SDVENC with the user passed configuration
 *  This function will configure the SD-VENC for user passed settings.
 *
 *  \param                  pointer to Vps_DssDispcSdVencAdvConfig structure
 *  \return                 success    0
 *                          failure    error value
 *
 */
Int32 VpsHal_dssSetAdvSdVencParams(const Vps_DssDispcSdVencAdvConfig *config);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef VPSHAL_SDVENC_H_ */
