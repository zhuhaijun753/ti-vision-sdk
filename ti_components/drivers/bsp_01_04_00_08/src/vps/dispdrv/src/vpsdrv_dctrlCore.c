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
 *  \file vpsdrv_dctrlCore.c
 *
 *  \brief File containing the VPS display controller driver functions related
 *  to core interactions.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <xdc/std.h>
#include <dispdrv/src/vpsdrv_dctrlPriv.h>

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

static Int32 vpsDrvDispOpenDctrlCore(VpsDrv_DctrlInstObj *instObj);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  \brief Open and configure the core connected to the driver instance.
 */
Int32 vpsDrvDctrlOpenCore(VpsDrv_DctrlInstObj *instObj)
{
    Int32 retVal = FVID2_SOK;

    GT_assert(VpsDrvDctrlTrace, (NULL != instObj));
    GT_assert(VpsDrvDctrlTrace, (NULL != instObj->coreOps));
    GT_assert(VpsDrvDctrlTrace, (NULL != instObj->coreOps->getProperty));

    instObj->coreHandle = NULL;

    /* Get core property */
    retVal = instObj->coreOps->getProperty(
        instObj->coreInstObj,
        &instObj->coreProperty);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(VpsDrvDctrlTrace, GT_ERR, "Get core property failed!!\n");
    }

    if (FVID2_SOK == retVal)
    {
        /* Call the respective core open function */
        switch (instObj->coreProperty.name)
        {
            case VPSCORE_DISP_DCTRL:
                retVal = vpsDrvDispOpenDctrlCore(instObj);
                break;

            default:
                GT_0trace(VpsDrvDctrlTrace, GT_ERR, "Unknown core!!\n");
                retVal = FVID2_EFAIL;
                break;
        }
    }

    return (retVal);
}

Int32 vpsDrvDctrlCloseCore(VpsDrv_DctrlInstObj *instObj)
{
    Int32 retVal = FVID2_SOK;

    GT_assert(VpsDrvDctrlTrace, (NULL != instObj));
    GT_assert(VpsDrvDctrlTrace, (NULL != instObj->coreOps));
    GT_assert(VpsDrvDctrlTrace, (NULL != instObj->coreOps->close));

    /* Close core */
    retVal = instObj->coreOps->close(instObj->coreInstObj);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(VpsDrvDctrlTrace, GT_ERR, "Core close failed!!\n");
    }

    return (retVal);
}

static Int32 vpsDrvDispOpenDctrlCore(VpsDrv_DctrlInstObj *instObj)
{
    Int32 retVal = FVID2_SOK;
    VpsCore_OpenPrms openPrms;

    GT_assert(VpsDrvDctrlTrace, (NULL != instObj));
    GT_assert(VpsDrvDctrlTrace, (NULL != instObj->coreOps));
    GT_assert(VpsDrvDctrlTrace, (NULL != instObj->coreOps->open));

    /* Init parameters */
    instObj->coreHandle = NULL;
    openPrms.drvData    = instObj;
    openPrms.reqFrmCb   = NULL;
    openPrms.frmDoneCb  = NULL;

    instObj->coreHandle = instObj->coreOps->open(
        instObj->coreInstObj,
        &openPrms,
        NULL,
        NULL);
    #if 0
    if (NULL == instObj->coreHandle)
    {
        GT_0trace(VpsDrvDctrlTrace, GT_ERR, "Dss core open failed!!\n");
        retVal = FVID2_EFAIL;
    }

    /* Close core if error occurs */
    if ((FVID2_SOK != retVal) && (NULL != instObj->coreHandle))
    {
        vpsDrvDctrlCloseCore(instObj);
    }
    #endif

    return (retVal);
}

