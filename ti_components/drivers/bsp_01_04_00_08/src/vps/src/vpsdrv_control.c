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
 *  \file vpsdrv_control.c
 *
 *  \brief File containing the VPS control driver APIs commmon to all drivers.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <xdc/std.h>
#include <common/bsp_types.h>
#include <common/trace.h>
#include <common/bsp_config.h>
#include <common/bsp_utils.h>
#include <fvid2/fvid2.h>
#include <fvid2_drvMgr.h>
#include <vps/vps.h>
#include <vps/vps_control.h>
#include <vpsdrv_control.h>
#ifdef VPS_VPE_BUILD
#include <vpecore/vpscore_m2m.h>
#include <vpedrv/vpsdrv_m2mVpe.h>
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/*
 * struct VpsDrv_CtrlCommonObj
 * \brief Capture driver global/common driver object.
 */
typedef struct
{
    BspOsal_SemHandle lockSem;
    /**< Lock semaphore. */
    Fvid2_DrvOps      fvidDrvOps;
    /**< FVID2 driver ops. */
    Bool              isRegistered;
    /**< FVID2 registeration complete flag. */
} VpsDrv_CtrlCommonObj;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  Below ifdef __cplusplus is added so that C++ build passes without
 *  typecasting. This is because the prototype is build as C type
 *  whereas this file is build as CPP file. Hence we get C++ build error.
 *  Also if tyecasting is used, then we get MisraC error Rule 11.1.
 */
#ifdef __cplusplus
extern "C" {
#endif

/*
 * VPS control API's
 */
static Fdrv_Handle VpsDrv_ctrlCreate(UInt32                   drvId,
                                     UInt32                   instId,
                                     Ptr                      createArgs,
                                     Ptr                      createStatusArgs,
                                     const Fvid2_DrvCbParams *fdmCbPrms);
static Int32 VpsDrv_ctrlDelete(Fdrv_Handle handle, Ptr reserved);
static Int32 VpsDrv_ctrlControl(Fdrv_Handle handle,
                                UInt32      cmd,
                                Ptr         cmdArgs,
                                Ptr         cmdStatusArgs);
#ifdef __cplusplus
}
#endif
/*
 * IOCTLs
 */
#ifdef VPS_VPE_BUILD
static Int32 vpsDrvCtrlSetVpeLazyLoadIoctl(
    VpsDrv_CtrlCommonObj          *pObj,
    const Vps_ScLazyLoadingParams *lazyPrms);
#endif

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static VpsDrv_CtrlCommonObj gVpsCtrlCommonObj;

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  \brief VPS control driver init function.
 */
Int32 VpsDrv_ctrlInit(void)
{
    Int32 retVal = FVID2_SOK;
    VpsDrv_CtrlCommonObj *pObj;
    Int32 initValue;

    pObj = &gVpsCtrlCommonObj;
    BspUtils_memset(pObj, 0, sizeof (gVpsCtrlCommonObj));

    /* Initialize Driver operations */
    Fvid2DrvOps_init(&pObj->fvidDrvOps);

    pObj->fvidDrvOps.drvId                 = FVID2_VPS_CTRL_DRV;
    pObj->fvidDrvOps.createFxn             = &VpsDrv_ctrlCreate;
    pObj->fvidDrvOps.deleteFxn             = &VpsDrv_ctrlDelete;
    pObj->fvidDrvOps.controlFxn            = &VpsDrv_ctrlControl;

    retVal = Fvid2_registerDriver(&pObj->fvidDrvOps);
    if (FVID2_SOK != retVal)
    {
        GT_0trace(VpsDrvCtrlTrace, GT_ERR,
                  "Registering to FVID2 driver manager failed\n");
    }

    if (FVID2_SOK == retVal)
    {
        pObj->isRegistered = (Bool)TRUE;

        /* Allocate lock semaphore */
        initValue = 1;
        pObj->lockSem = BspOsal_semCreate(initValue, FALSE);
        if (NULL == pObj->lockSem)
        {
            GT_0trace(VpsDrvCaptTrace, GT_ERR,
                      "Instance semaphore create failed!!\n");
            retVal = FVID2_EALLOC;
        }
    }

    if (FVID2_SOK != retVal)
    {
        VpsDrv_ctrlDeInit();
    }

    return (retVal);
}

/**
 *  \brief VPS control driver deinit function.
 */
Int32 VpsDrv_ctrlDeInit(void)
{
    Int32 retVal = FVID2_SOK;
    VpsDrv_CtrlCommonObj *pObj;

    pObj = &gVpsCtrlCommonObj;
    if (TRUE == pObj->isRegistered)
    {
        /* Unregister from driver manager */
        retVal = Fvid2_unRegisterDriver(&pObj->fvidDrvOps);
        if (FVID2_SOK != retVal)
        {
            GT_0trace(VpsDrvCtrlTrace, GT_ERR,
                      "Unregistering from FVID2 driver manager failed\n");
        }
        pObj->isRegistered = (Bool)FALSE;
    }

    if (NULL != pObj->lockSem)
    {
        BspOsal_semDelete(&pObj->lockSem);
        pObj->lockSem = NULL;
    }

    return (retVal);
}

/**
 *  \brief VPS control driver create function.
 */
static Fdrv_Handle VpsDrv_ctrlCreate(UInt32                   drvId,
                                     UInt32                   instId,
                                     Ptr                      createArgs,
                                     Ptr                      createStatusArgs,
                                     const Fvid2_DrvCbParams *fdmCbPrms)
{
    Fdrv_Handle drvHandle = NULL;

    /* Check for NULL pointers and invalid arguments */
    if ((FVID2_VPS_CTRL_DRV != drvId) || (VPS_CTRL_INST_0 != instId))
    {
        GT_0trace(VpsDrvCtrlTrace, GT_ERR, "Invalid arguments\n");
    }
    else
    {
        drvHandle = (Fdrv_Handle) & gVpsCtrlCommonObj;
    }

    return (drvHandle);
}

/**
 *  \brief VPS control driver delete function.
 */
static Int32 VpsDrv_ctrlDelete(Fdrv_Handle handle, Ptr reserved)
{
    Int32 retVal = FVID2_EBADARGS;

    /* Global handle - do nothing */
    if (((Fdrv_Handle) & gVpsCtrlCommonObj) == handle)
    {
        retVal = FVID2_SOK;
    }

    return (retVal);
}

/**
 *  \brief VPS control driver control function.
 */
static Int32 VpsDrv_ctrlControl(Fdrv_Handle handle,
                                UInt32      cmd,
                                Ptr         cmdArgs,
                                Ptr         cmdStatusArgs)
{
    Int32 retVal = FVID2_EBADARGS;

    if (handle == (Fdrv_Handle) & gVpsCtrlCommonObj)
    {
        retVal = FVID2_SOK;
        switch (cmd)
        {
#ifdef VPS_VPE_BUILD
            case IOCTL_VPS_CTRL_SET_VPE_LAZY_LOADING:
                if (NULL != cmdArgs)
                {
                    retVal = vpsDrvCtrlSetVpeLazyLoadIoctl(
                        (VpsDrv_CtrlCommonObj *) handle,
                        (Vps_ScLazyLoadingParams *) cmdArgs);
                }
                else
                {
                    GT_0trace(VpsDrvCtrlTrace, GT_ERR, "NULL argument\n");
                    retVal = FVID2_EBADARGS;
                }
                break;
#endif

            default:
                GT_0trace(
                    VpsDrvCtrlTrace, GT_ERR,
                    "UNSUPPORTED_CMD: IOCTL not supported!!\n");
                retVal = FVID2_EUNSUPPORTED_CMD;
                break;
        }
    }

    return (retVal);
}

#ifdef VPS_VPE_BUILD
static Int32 vpsDrvCtrlSetVpeLazyLoadIoctl(
    VpsDrv_CtrlCommonObj          *pObj,
    const Vps_ScLazyLoadingParams *lazyPrms)
{
    Int32 retVal = FVID2_SOK;

    retVal = VpsMdrv_vpeSetLazyLoadParams(lazyPrms);

    return (retVal);
}

#endif
