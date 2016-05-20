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
 *  \file vps_m2mInt.h
 *
 *  \brief VPS Mem-Mem driver common header file.
 *
 */

#ifndef VPS_M2MINT_H_
#define VPS_M2MINT_H_

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
 *  struct VpsMdrv_SyncMode
 *  \brief Enum to indicate whether Sync on Channel (SOCH) or
 *  Sync on Client (SOC) to be used between each channel descriptors while
 *  chaining.
 */
typedef enum
{
    VPSMDRV_SYNC_MODE_SOCH,
    /**< Use Sync on Channel. */
    VPSMDRV_SYNC_MODE_SOC,
    /**< Use Sync on Client. */
    VPSMDRV_SYNC_MODE_MAX
    /**< Should be the last value of this enumeration.
     *   Will be used by driver for validating the input parameters. */
} VpsMdrv_SyncMode;

/**
 *  struct VpsMdrv_QueObjType
 *  \brief To know whether the queue objects contain the frames or
 *  coefficient descriptors. So that it can be returned to appropriate
 *  queue after callback.
 */
typedef enum
{
    VPSMDRV_QOBJ_TYPE_FRAMES,
    /**< Container contains process list to be processed. */
    VPSMDRV_QOBJ_TYPE_COEFF,
    /**< Container contains the coefficients. */
    VPSMDRV_QOBJ_TYPE_MAX
    /**< Should be the last value of this enumeration. */
} VpsMdrv_QueObjType;

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif /* VPS_M2MINT_H_ */
