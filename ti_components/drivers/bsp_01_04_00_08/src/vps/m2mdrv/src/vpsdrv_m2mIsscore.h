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

/**
 *  \file vpsdrv_m2mIntfCore.h
 *
 *  \brief VPS M2M driver internal header file.
 */

#ifndef VPSDRV_M2MISSCORE_H_
#define VPSDRV_M2MISSCORE_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

#ifdef VPS_ISS_BUILD
Int32 vpsMdrvIssSubmitReq(
    VpsMDrv_IntfHandleObj *hObj,
    VpsMDrv_IntfQueueObj  *qObj);

Int32 vpsMdrvIssControl(
    VpsMDrv_IntfHandleObj *hObj,
    UInt32                 cmd,
    Ptr                    cmdArgs,
    Ptr                    cmdStatArgs);
#endif /* VPS_ISS_BUILD */

#ifdef VPS_SIMCOP_BUILD
Int32 vpsMdrvSimcopSubmitReq(
    VpsMDrv_IntfHandleObj *hObj,
    VpsMDrv_IntfQueueObj  *qObj);

Int32 vpsMdrvSimcopControl(
    VpsMDrv_IntfHandleObj *hObj,
    UInt32                 cmd,
    Ptr                    cmdArgs,
    Ptr                    cmdStatArgs);
#endif

#ifdef __cplusplus
}
#endif

#endif /*  VPSDRV_M2MISSCORE_H_ */

