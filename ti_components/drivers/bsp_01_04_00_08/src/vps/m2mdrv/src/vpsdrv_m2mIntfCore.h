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
 *  \file vpsdrv_m2mIntfPriv.h
 *
 *  \brief VPS M2M driver internal header file.
 */

#ifndef VPSDRV_M2MINTFCORE_H_
#define VPSDRV_M2MINTFCORE_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <vps/vps_m2mIntf.h>
#ifdef VPS_ISS_BUILD
#include <vps/iss/vps_m2mIss.h>
#endif
#include "vpsdrv_m2mIsscore.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/** \brief Function pointer for submitting request */
typedef Int32 (*VpsMDrvSubmitReq)(VpsMDrv_IntfHandleObj *hObj,
                                  VpsMDrv_IntfQueueObj  *qObj);

/** \brief Function pointer for processing control commands */
typedef Int32 (*VpsMDrvControl)(VpsMDrv_IntfHandleObj *hObj,
                                UInt32                 cmd,
                                Ptr                    cmdArgs,
                                Ptr                    cmdStatusArgs);

typedef struct
{
    UInt32           drvInstId;
    /**< Driver Instance Id */
    VpsMDrvSubmitReq submitReq;
    /**< Function pointer for submitting the request */
    VpsMDrvControl   control;
    /**< Function pointer for processing control command */
} VpsMDrv_M2mCoreOps;

#ifdef __cplusplus
}
#endif

#endif /*  VPSDRV_M2MINTFCORE_H_ */

