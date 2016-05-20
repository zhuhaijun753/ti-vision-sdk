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
 *  \ingroup BSPUTILS_API
 *  \defgroup BSPUTILS_LVDS_API Application helper APIs for LVDS operations
 *  @{
 */

/**
 *  \file bsputils_lvds.h
 *
 *  \brief Header file to use application level LVDS helper functions.
 */

#ifndef BSPUTILS_LVDS_H_
#define BSPUTILS_LVDS_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <common/trace.h>
#include <common/bsp_common.h>
#include <fvid2/fvid2.h>
#include <platforms/bsp_platform.h>
#include <vps/vps.h>
#ifdef VPS_VIP_BUILD
#include <vps/vps_capture.h>
#endif  /* #ifdef VPS_VIP_BUILD */
#ifdef VPS_VPE_BUILD
#include <vps/vps_m2m.h>
#endif  /* #ifdef VPS_VPE_BUILD */
#ifdef VPS_DSS_BUILD
#include <vps/vps_display.h>
#endif  /* #ifdef VPS_DSS_BUILD */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  BspUtils_appInitSerDeSer
 *
 *  \brief BSP application utils function to setup MULDES board for LVDS
 *  Support.
 *
 *  \param devDrvId         [IN]    Device Driver ID.
 */
Int32 BspUtils_appInitSerDeSer(UInt32 devDrvId);

/**
 *  BspUtils_appDeInitSerDeSer
 *
 *  \brief BSP application utils function to undo stuff done in init.
 *  1. Deletion of semaphore created.
 */
Int32 BspUtils_appDeInitSerDeSer(UInt32 devDrvId);

/**
 *  BspUtils_appConfSerDeSer
 *
 *  \brief BSP application utils function to Configure a particular instance of
 *  De-Serializer and serializer for LVDS Support.
 *
 *  \param devDrvId         [IN]    Device Driver ID.
 *  \param devInstId        [IN]    Instance ID of the Device.
 */
Int32 BspUtils_appConfSerDeSer(UInt32 devDrvId, UInt32 devInstId);

/**
 *  BspUtils_appDeConfSerDeSer
 *
 *  \brief BSP application utils function to De-Configure a particular instance
 *           of De-Serializer and serializer for LVDS Support.
 *
 *  \param devDrvId         [IN]    Device Driver ID.
 *  \param devInstId        [IN]    Instance ID of the Device.
 */
Int32 BspUtils_appDeConfSerDeSer(UInt32 devDrvId, UInt32 devInstId);

/**
 *  BspUtils_appDumpDeSerReg
 *
 *  \brief BSP application utils function to print all the registers of
 *  deserializer.
 *
 *  \param devDrvId         [IN]   Device Driver ID.
 *  \param devInstId        [IN]   Instance ID of the Device.
 */
Int32 BspUtils_appDumpDeSerReg(UInt32 devDrvId, UInt32 devInstId);

#ifdef __cplusplus
}
#endif

#endif  /* #define BSPUTILS_LVDS_H_ */

/* @} */
