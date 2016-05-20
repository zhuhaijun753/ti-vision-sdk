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
 *  \file vpscore_dss.c
 *
 *  \brief DSS core implementation
 *  This file implements the VPS core interface for DSS.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stddef.h>
#include <common/stw_dataTypes.h>
#include <osal/bsp_osal.h>
#include <common/stw_types.h>
#include <common/bsp_types.h>
#include <common/trace.h>
#include <common/stw_config.h>
#include <common/bsp_utils.h>
#include <fvid2/fvid2_dataTypes.h>

#include <dispcore/vpscore_dss.h>
#include <dispcore/src/vpscore_dctrlIntr.h>
#include <dispcore/src/vpscore_dssPriv.h>
#include <vps/vps_cfgDss.h>
#include <vps/vps_cfgMem.h>
#include <common/vpscore.h>
#include <common/vps_common.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                         Function Declarations                              */
/* ========================================================================== */

static Int32 VpsCore_dssValidateDssParams(const VpsCore_DispDssParams *pathCfg,
                                          const VpsCore_DssPathObj    *pathObj);

static Int32 VpsCore_dssVidPathCopyConfig(VpsCore_DssPathObj          *pathObj,
                                          const VpsCore_DispDssParams *pathCfg);

static Int32 VpsCore_dssGfxPathCopyConfig(VpsCore_DssPathObj          *pathObj,
                                          const VpsCore_DispDssParams *pathCfg);

static Int32 VpsCore_isGfxPipeline(const VpsCore_DssPathObj *pathObj);

static Int32 VpsCore_isVidPipeline(const VpsCore_DssPathObj *pathObj);

static Int32 VpsCore_isWbPipeline(const VpsCore_DssPathObj *pathObj);

/**
 *  Below ifdef __cplusplus is added so that C++ build passes without
 *  typecasting. This is because the prototype is build as C type
 *  whereas this file is build as CPP file. Hence we get C++ build error.
 *  Also if tyecasting is used, then we get MisraC error Rule 11.1.
 */
#ifdef __cplusplus
extern "C" {
#endif
static void vpsCoreDssDispcCb(Ptr arg0);
#ifdef __cplusplus
}
#endif
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/** \brief Dss Objects */
static VpsCore_DssObj      gVcoreDssObj;

/** \brief Dss Path Objects */
static VpsCore_DssPathObj  gVcoreDssPathObjMemPool[
    VPS_CFG_MEM_DSS_MAX_FWD_PIPE_OBJS];
/** \brief Pool parameters for Dss Path Object pool memory */
static BspUtils_PoolParams VcoreDssPathObjPoolParams;
/**
 *  \brief The flag variable represents whether a given context object is
 *  allocated or not
 */
static UInt32 VcoreDssPathObjMemFlag[VPS_CFG_MEM_DSS_MAX_FWD_PIPE_OBJS];

/** \brief DSS core function pointer. */
static const VpsCore_Ops   gDssCoreOps =
{
    &VpsCore_dssGetProperty,         /* Get property */
    &VpsCore_dssOpen,                /* Open function */
    &VpsCore_dssClose,               /* Close function */
    &VpsCore_dssPathSetConfig,       /* Set config */
    &VpsCore_dssPathGetConfig,       /* Get config */
    &VpsCore_dssControl,             /* Control */
    &VpsCore_dssStart,               /* Start */
    &VpsCore_dssStop,                /* Stop */
    &VpsCore_dssIsr,                 /* Process */
    &VpsCore_dssProgBuffer,          /* Prog Buffer*/
    NULL,                            /* putFrames */
    NULL,                            /* getFrames */
    &VpsCore_dssGetErrorStat         /* getErrorStat */
};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
#ifdef VPSCORE_DSS_USE_TIMER_ISR
/* This is called when timer expires */
static void vpsCoreDssTimerIsr(UInt32 arg0)
{
    VpsCore_Handle pathHandle;

    GT_assert(VpsDssCoreTrace, (NULL != arg0));
    pathHandle = (VpsCore_Handle) arg0;

    VpsCore_dssIsr(pathHandle, (UInt32) 0);

    return;
}

#endif

static void vpsCoreDssDispcCb(Ptr arg0)
{
    VpsCore_Handle pathHandle;

    GT_assert(VpsDssCoreTrace, (NULL != arg0));
    pathHandle = (VpsCore_Handle) arg0;
    VpsCore_dssIsr(pathHandle, (UInt32) 0);

    return;
}

VpsCore_Inst VpsCore_dssInit(const VpsCore_DssInitParams *initParams)
{
    VpsCore_DssObj *pNewObj = &gVcoreDssObj;
    UInt32          i;

    /* init path object pool */
    BspUtils_initPool(&VcoreDssPathObjPoolParams,
                      (Void *) gVcoreDssPathObjMemPool,
                      VPS_CFG_MEM_DSS_MAX_FWD_PIPE_OBJS,
                      sizeof (VpsCore_DssPathObj),
                      VcoreDssPathObjMemFlag,
                      VpsDssCoreTrace);

    pNewObj->dispcIrqNumber = initParams->dispcIrqNumber;
    pNewObj->vidHandle[0]   = initParams->vidHandle[0];
    pNewObj->vidHandle[1]   = initParams->vidHandle[1];
    pNewObj->vidHandle[2]   = initParams->vidHandle[2];
    /* Gfx pipeline handle*/
    pNewObj->vidHandle[3] = initParams->vidHandle[3];

    pNewObj->ovlHandle[0] = initParams->ovlHandle[0];
    pNewObj->ovlHandle[1] = initParams->ovlHandle[1];
    pNewObj->ovlHandle[2] = initParams->ovlHandle[2];
    pNewObj->ovlHandle[3] = initParams->ovlHandle[3];

    pNewObj->dcNodeNum[0] = VPSCORE_DCTRL_NODE_VID1;
    pNewObj->dcNodeNum[1] = VPSCORE_DCTRL_NODE_VID2;
    pNewObj->dcNodeNum[2] = VPSCORE_DCTRL_NODE_VID3;
    pNewObj->dcNodeNum[3] = VPSCORE_DCTRL_NODE_GFX;

    for (i = 0; i < 4U; i++)
    {
        pNewObj->pathObjPool[i] = 0;
    }
    return (VpsCore_Inst) pNewObj;
}

Int32 VpsCore_dssDeInit(VpsCore_Inst pDssHandle)
{
    return BSP_SOK;
}

/**
 *  VpsCore_dssGetCoreOps
 *  \brief Returns the pointer to core function pointer table.
 *
 *  \return             Returns the pointer to core function pointer table.
 */
const VpsCore_Ops *VpsCore_dssGetCoreOps(void)
{
    return (&gDssCoreOps);
}

Int32 VpsCore_dssGetProperty(VpsCore_Inst      instObj,
                             VpsCore_Property *property)
{
    Int32 retVal = BSP_EFAIL;

    if (NULL != property)
    {
        property->name = VPSCORE_DISP_DSS;
        retVal         = BSP_SOK;
    }

    return (retVal);
}

Int32 VpsCore_dssPathGetConfig(VpsCore_Handle pathHandle,
                               void          *params)
{
    Int32 retVal = BSP_SOK;
    VpsCore_DssPathObj    *pathObj = (VpsCore_DssPathObj *) pathHandle;
    VpsCore_DispDssParams *pathCfg = (VpsCore_DispDssParams *) params;

    /* Check for NULL pointer */
    GT_assert(VpsDssCoreTrace, (NULL != pathHandle));
    GT_assert(VpsDssCoreTrace, (NULL != params));

    if ((Int32) TRUE == VpsCore_isVidPipeline(pathObj))
    {
        BspUtils_memcpy(
            &pathCfg->inFmt,
            &pathObj->vidPipeCfg.inFmt,
            sizeof (Fvid2_Format));

        pathCfg->tarWidth  = pathObj->vidPipeCfg.outWidth;
        pathCfg->tarHeight = pathObj->vidPipeCfg.outHeight;
        pathCfg->posX      = pathObj->vidPipeCfg.posX;
        pathCfg->posY      = pathObj->vidPipeCfg.posY;
        pathCfg->memType   = pathObj->memType;

        if (NULL != pathCfg->vidCfg)
        {
            pathCfg->vidCfg->pipeCfg.repliEnable =
                pathObj->vidPipeCfg.repliEnable;
            pathCfg->vidCfg->pipeCfg.scEnable =
                pathObj->vidPipeCfg.scEnable;
            pathCfg->vidCfg->pipeCfg.cscFullRngEnable =
                pathObj->vidPipeCfg.cscFullRngEnable;
            pathCfg->vidCfg->pipeCfg.chromaSampling =
                pathObj->vidPipeCfg.chromaSampling;

            if (NULL != pathCfg->vidCfg->advDmaCfg)
            {
                BspUtils_memcpy(
                    pathCfg->vidCfg->advDmaCfg,
                    &pathObj->halAdvDmaCfg,
                    sizeof (VpsHal_DssDispcAdvDmaConfig));
            }

            if (NULL != pathCfg->vidCfg->vc1Cfg)
            {
                BspUtils_memcpy(
                    pathCfg->vidCfg->vc1Cfg,
                    &pathObj->vc1Cfg,
                    sizeof (Vps_DssDispcVidVC1Config));
            }
        }
    }
    else if ((Int32) TRUE == VpsCore_isGfxPipeline(pathObj))
    {
        BspUtils_memcpy(
            &pathCfg->inFmt,
            &pathObj->gfxPipeCfg.inFmt,
            sizeof (Fvid2_Format));

        pathCfg->posX    = pathObj->gfxPipeCfg.posX;
        pathCfg->posY    = pathObj->gfxPipeCfg.posY;
        pathCfg->memType = pathObj->memType;

        if (NULL != pathCfg->gfxCfg)
        {
            pathCfg->gfxCfg->pipeCfg.repliEnable =
                (UInt32) pathObj->gfxPipeCfg.repliEnable;
            pathCfg->gfxCfg->pipeCfg.antiFlickerEnable =
                (UInt32) pathObj->gfxPipeCfg.antiFlickerEnable;

            if (NULL != pathCfg->gfxCfg->advDmaCfg)
            {
                BspUtils_memcpy(
                    pathCfg->gfxCfg->advDmaCfg,
                    &pathObj->halAdvDmaCfg,
                    sizeof (VpsHal_DssDispcAdvDmaConfig));
            }
        }
    }
    else
    {
        GT_0trace(
            VpsDssCoreTrace, GT_ERR,
            "Invalid path handle \n");
    }

    return (retVal);
}

Int32 VpsCore_dssControl(VpsCore_Handle handle,
                         UInt32         cmd,
                         void          *appArgs,
                         void          *drvArgs)
{
    Int32 retVal = BSP_SOK;
    VpsCore_DssPathObj *pathObj;

    GT_assert(VpsDssCoreTrace, (NULL != handle));
    GT_assert(VpsDssCoreTrace, (NULL != appArgs));

    pathObj = (VpsCore_DssPathObj *) handle;

    switch (cmd)
    {
        case VCORE_DSS_SET_CSC_COEFF:
            retVal =
                VpsHal_dssSetCscCoeff(pathObj->pipeHandle,
                                      (Vps_DssCscCoeff *) appArgs);
            break;
        default:
            GT_0trace(VpsDssCoreTrace, GT_ERR, "Invalid cmd \n");
            break;
    }
    return retVal;
}

Int32 VpsCore_dssGetErrorStat(VpsCore_Handle pathHandle,
                              void          *params)
{
    Int32 retVal = BSP_SOK;
    VpsCore_DssPathObj *pathObj;
    VpsCore_DssVidErrorStatus *retParams;

    GT_assert(VpsDssCoreTrace, (NULL != params));
    GT_assert(VpsDssCoreTrace, (NULL != pathHandle));

    retParams = (VpsCore_DssVidErrorStatus *) params;

    pathObj = (VpsCore_DssPathObj *) pathHandle;

    retVal = Vpscore_dctrlGetDssVidErrorCount(pathObj->dcHandle, retParams);

    return retVal;
}

VpsCore_Handle VpsCore_dssOpen(VpsCore_Inst            pDssHandle,
                               const VpsCore_OpenPrms *openPrms,
                               const void             *coreOpenPrms,
                               void                   *coreReturnPrms)
{
    const VpsCore_DssOpenParams *corePrms =
        (const VpsCore_DssOpenParams *) coreOpenPrms;
    VpsCore_DssOpenRetParams    *retPrms =
        (VpsCore_DssOpenRetParams *) coreReturnPrms;
    VpsCore_DssPathObj          *pathObj     = NULL;
    VpsCore_DssObj              *pDssInstObj = (VpsCore_DssObj *) pDssHandle;
    Int32 retVal    = BSP_SOK;
    UInt32 index    = 0;
    UInt32 handleId = 0;
    Vpscore_dctrlPathInfo        pathInfo;
    Vpscore_dctrlClientInfo      clientInfo;

    GT_assert(VpsDssCoreTrace, (coreOpenPrms != NULL));
    GT_assert(VpsDssCoreTrace, (openPrms != NULL));
    GT_assert(VpsDssCoreTrace, (coreReturnPrms != NULL));

    if (corePrms->src > VPS_DSS_DISPC_PIPE_GFX1)
    {
        retVal = BSP_EINVALID_PARAMS;
    }
    else
    {
        index = corePrms->src;
    }

    /* TODO: make this part as re-interant, protect global variables*/
    if (retVal == BSP_SOK)
    {
        if (NULL == pDssInstObj->pathObjPool[index])
        {
            pDssInstObj->pathObjPool[index] = (VpsCore_Handle) BspUtils_alloc(
                &VcoreDssPathObjPoolParams,
                sizeof (VpsCore_DssPathObj),
                VpsDssCoreTrace);

            if (pDssInstObj->pathObjPool[index] == NULL)
            {
                GT_0trace(
                    VpsDssCoreTrace, GT_ERR,
                    "Failed to allocate memory for pathobj\n");
                retVal = BSP_EALLOC;
            }
            else
            {
                pathObj =
                    (VpsCore_DssPathObj *) pDssInstObj->pathObjPool[index];
                BspUtils_memset(pathObj, (UInt8) 0U, sizeof (VpsCore_DssPathObj));
            }
        }
        else
        {
            GT_0trace(
                VpsDssCoreTrace, GT_ERR,
                "Core for this instance is already opened\n");
            retVal = BSP_EFAIL;
        }
    }

    if (retVal == BSP_SOK)
    {
        pathObj->drvData    = openPrms->drvData;
        pathObj->handleId   = index;
        pathObj->parent     = (VpsCore_DssObj *) pDssInstObj;
        pathObj->reqFrmCb   = openPrms->reqFrmCb;
        pathObj->frmDoneCb  = openPrms->frmDoneCb;
        pathObj->pipeHandle = pDssInstObj->vidHandle[index];
        pathObj->dcNode     = pDssInstObj->dcNodeNum[index];
        pathObj->isStarted  = FALSE;
    }

    if (retVal == BSP_SOK)
    {
        clientInfo.cbFxn  = &vpsCoreDssDispcCb;
        clientInfo.arg    = pathObj;
        pathObj->dcHandle = Vpscore_dctrlRegisterClient(
            pathObj->dcNode,
            &clientInfo,
            NULL);
        if (pathObj->dcHandle == NULL)
        {
            GT_1trace(
                VpsDssCoreTrace, GT_ERR,
                "Display Controller registration failed for dss core instance %d \n",
                index);
            retVal = BSP_EALLOC;
        }
        else
        {
            retVal = Vpscore_dctrlGetPathInfo(pathObj->dcHandle, &pathInfo);
            if (retVal != BSP_SOK)
            {
                GT_1trace(
                    VpsDssCoreTrace, GT_ERR,
                    "Getting path info from DC failed for dss core instance %d \n",
                    index);
            }
            else
            {
                /* Copy the details into pathobj */
                pathObj->dispHeight     = pathInfo.height;
                pathObj->dispWidth      = pathInfo.width;
                pathObj->dispStandard   = pathInfo.standard;
                pathObj->dispScanFormat = pathInfo.scanFormat;
                pathObj->shiftVidPosX   = pathInfo.shiftVidPosX;
            }

            /* This is to clear the underflow count */
            retVal = Vpscore_dctrlClrErrorCount(pathObj->dcHandle);
        }
    }
    if ((retPrms != NULL) && (retVal == BSP_SOK))
    {
        retPrms->standard   = pathInfo.standard;
        retPrms->dispWidth  = pathInfo.width;
        retPrms->dispHeight = pathInfo.height;
        retPrms->vencId     = pathInfo.vencId;
    }

#ifdef VPSCORE_DSS_USE_TIMER_ISR
    if (retVal == BSP_SOK)
    {
        /* Create periodic timer */
        pDssInstObj->procClkHandle = BspOsal_clockCreate(
            &vpsCoreDssTimerIsr,
            16U,
            FALSE,
            pathObj);
        if (NULL == pDssInstObj->procClkHandle)
        {
            GT_0trace(VpsDssCoreTrace, GT_ERR,
                      "Periodic timer create failed!!\n");
            retVal = BSP_EALLOC;
        }
    }
#endif
    if (retVal != BSP_SOK)
    {
        /* Free previously allocated memory*/
        if (pathObj != NULL)
        {
            if (pathObj->dcHandle != NULL)
            {
                Vpscore_dctrlUnRegisterClient(pathObj->dcHandle);
            }
            handleId = pathObj->handleId;
            /* Free the handle object */
            retVal = BspUtils_free(&VcoreDssPathObjPoolParams,
                                   (const Void *) pathObj,
                                   VpsDssCoreTrace);
            pDssInstObj->pathObjPool[handleId] = NULL;
        }
        pathObj = NULL;
    }
    return pathObj;
}

Int32 VpsCore_dssClose(VpsCore_Handle pathHandle)
{
    VpsCore_DssPathObj *pathObj;
    VpsCore_DssObj     *pDssInstObj;
    UInt32 handleId = 0;

    GT_assert(VpsDssCoreTrace, (NULL != pathHandle));
    pathObj     = (VpsCore_DssPathObj *) pathHandle;
    pDssInstObj = pathObj->parent;
    GT_assert(VpsDssCoreTrace, (NULL != pDssInstObj));

#ifdef VPSCORE_DSS_USE_TIMER_ISR
    /* Delete the timer */
    if (NULL != pDssInstObj->procClkHandle)
    {
        BspOsal_clockStop(pDssInstObj->procClkHandle);
        BspOsal_clockDelete(&pDssInstObj->procClkHandle);
        pDssInstObj->procClkHandle = NULL;
    }
#endif

    Vpscore_dctrlUnRegisterClient(pathObj->dcHandle);

    handleId = pathObj->handleId;
    /* Free the handle object */
    BspUtils_free(&VcoreDssPathObjPoolParams,
                  (const Void *) pathObj,
                  VpsDssCoreTrace);

    pDssInstObj->pathObjPool[handleId] = NULL;

    return BSP_SOK;
}

Int32 VpsCore_dssPathSetConfig(VpsCore_Handle pathHandle,
                               const void    *params,
                               void          *retPrms)
{
    VpsCore_DssPathObj          *pathObj = (VpsCore_DssPathObj *) pathHandle;
    Int32 retVal = BSP_SOK;
    const VpsCore_DispDssParams *pathCfg =
        (const VpsCore_DispDssParams *) params;

    /* Check for NULL pointer */
    GT_assert(VpsDssCoreTrace, (NULL != pathHandle));
    GT_assert(VpsDssCoreTrace, (NULL != params));

    /* Validate the DssParams */
    retVal = VpsCore_dssValidateDssParams(pathCfg, pathObj);
    if (BSP_SOK == retVal)
    {
        /* Copy the Video/Gfx parameters into the path handle. */
        if ((Int32) TRUE == VpsCore_isVidPipeline(pathObj))
        {
            retVal = VpsCore_dssVidPathCopyConfig(pathObj, pathCfg);
        }
        else if ((Int32) TRUE == VpsCore_isGfxPipeline(pathObj))
        {
            retVal = VpsCore_dssGfxPathCopyConfig(pathObj, pathCfg);
        }
        else
        {
            retVal = BSP_EBADARGS;
        }
    }

    /*pathObj->pipeHandle should be opened in core open only*/
    if (BSP_SOK == retVal)
    {
        if ((Int32) TRUE == VpsCore_isVidPipeline(pathObj))
        {
            retVal = VpsHal_dssConfVidPipe(pathObj->pipeHandle,
                                           &pathObj->vidPipeCfg,
                                           &pathObj->vc1Cfg);
        }
        else if ((Int32) TRUE == VpsCore_isGfxPipeline(pathObj))
        {
            retVal = VpsHal_dssConfGfxPipe(pathObj->pipeHandle,
                                           &pathObj->gfxPipeCfg);
        }
        else if ((Int32) TRUE == VpsCore_isWbPipeline(pathObj))
        {
            /* This else is just to avoid warning */
        }
        else
        {
            retVal = BSP_EBADARGS;
        }
    }
    if (BSP_SOK == retVal)
    {
        retVal = VpsHal_dssConfAdvDma(pathObj->pipeHandle,
                                      &pathObj->halAdvDmaCfg);
    }

    return retVal;
}

Int32 VpsCore_dssStart(VpsCore_Handle pathHandle)
{
    VpsCore_DssPathObj *pathObj;
    VpsCore_DssObj     *pDssInstObj;
    Int32 retVal = BSP_SOK;
    VpsCore_Frame     **programedFrame;

    /* Check for NULL pointer */
    GT_assert(VpsDssCoreTrace, (NULL != pathHandle));
    pathObj     = (VpsCore_DssPathObj *) pathHandle;
    pDssInstObj = pathObj->parent;
    GT_assert(VpsDssCoreTrace, (NULL != pDssInstObj));

    /* Reset all the frame pointers to NULL*/
    pathObj->curFrame  = NULL;
    pathObj->progFrame = NULL;

    programedFrame = &(pathObj->progFrame);

    /* stream ID and Channel Id is Zero Here*/
    *programedFrame = pathObj->reqFrmCb(pathObj->drvData, 0, 0);

    /* Driver should always give the buffers when requested */
    GT_assert(VpsDssCoreTrace, (*programedFrame != NULL));

    /*TODO - Error handling when frame is null*/
    retVal += VpsHal_dssVidPipeSetBufAddr(
        pathObj->pipeHandle,
        0,
        (UInt32) (*programedFrame)->addr[0][0],
        (UInt32) (*programedFrame)->addr[0][1]);

    if (pathObj->inScanFormat == FVID2_SF_INTERLACED)
    {
        retVal += VpsHal_dssVidPipeSetBufAddr(
            pathObj->pipeHandle,
            (UInt32) 1U,
            (UInt32) (*programedFrame)->addr[1][0],
            (UInt32) (*programedFrame)->addr[1][1]);
    }
    else
    {
        /* In case of switching from interlaced to progressive, sometimes buffer
         * is fetched from BA1 insted of BA0. So program BA1 with same value for
         * progressive display. */
        retVal += VpsHal_dssVidPipeSetBufAddr(
            pathObj->pipeHandle,
            1U,
            (UInt32) (*programedFrame)->addr[0][0],
            (UInt32) (*programedFrame)->addr[0][1]);
    }

    if (retVal == BSP_SOK)
    {
        retVal = VpsHal_dssVidPipeEnable(pathObj->pipeHandle, (UInt32) TRUE);
    }

    if (retVal == BSP_SOK)
    {
        retVal = Vpscore_dctrlStartClient(pathObj->dcHandle);
    }

    if (retVal == BSP_SOK)
    {
        pathObj->isStarted = TRUE;
    }
    else
    {
        /* TODO - Check if you need this */
        Vpscore_dctrlStopClient(pathObj->dcHandle);
        VpsHal_dssVidPipeEnable(pathObj->pipeHandle, (UInt32) FALSE);
    }

#ifdef VPSCORE_DSS_USE_TIMER_ISR
    BspOsal_clockStart(pDssInstObj->procClkHandle);
#endif

    return retVal;
}

Int32 VpsCore_dssStop(VpsCore_Handle pathHandle)
{
    VpsCore_DssPathObj *pathObj;
    VpsCore_DssObj     *pDssInstObj;
    Int32 retVal = BSP_SOK;

    /* Check for NULL pointer */
    GT_assert(VpsDssCoreTrace, (NULL != pathHandle));
    pathObj     = (VpsCore_DssPathObj *) pathHandle;
    pDssInstObj = pathObj->parent;
    GT_assert(VpsDssCoreTrace, (NULL != pDssInstObj));

    retVal = VpsHal_dssVidPipeEnable(pathObj->pipeHandle, (UInt32) FALSE);
    if (retVal == BSP_SOK)
    {
#ifdef VPSCORE_DSS_USE_TIMER_ISR
        BspOsal_clockStop(pDssInstObj->procClkHandle);
#endif
        pathObj->isStarted = FALSE;

        /* Reset all the frame pointers to NULL*/
        pathObj->curFrame  = NULL;
        pathObj->progFrame = NULL;

        retVal = Vpscore_dctrlStopClient(pathObj->dcHandle);
    }
    return retVal;
}

/* Sequence that is followed in the ISR.
 * 1. Give back the current frame to driver if its not NULL.
 * 2. Move programmed Frame to current frame.
 * 3. Get next Frame from the driver, program this into programmed frame.
 * 4. Update the registers with address of program frame.
 * 5. Set Go bit of the corresponding Overlay Manager.
 */
Int32 VpsCore_dssIsr(VpsCore_Handle pathHandle, UInt32 chId)
{
    VpsCore_DssPathObj *pathObj = (VpsCore_DssPathObj *) pathHandle;
    Int32  retVal = BSP_SOK;
    UInt32 cookie;

    if (pathObj->isStarted == TRUE)
    {
        cookie = BspOsal_disableInterrupt();

        if (pathObj->curFrame != NULL)
        {
            pathObj->frmDoneCb(pathObj->drvData, pathObj->curFrame);
        }
        pathObj->curFrame = pathObj->progFrame;

        pathObj->progFrame = pathObj->reqFrmCb(pathObj->drvData, 0, 0);
        /* Driver should always give the buffers when requested */
        /* Driver should give both the fields in single call for Interlaced
         * display */
        GT_assert(VpsDssCoreTrace, (pathObj->progFrame != NULL));

        /*TODO - Error handling when frame is null*/
        retVal += VpsHal_dssVidPipeSetBufAddr(
            pathObj->pipeHandle,
            0,
            (UInt32) pathObj->progFrame->addr[0][0],
            (UInt32) pathObj->progFrame->addr[0][1]);

        if (pathObj->inScanFormat == FVID2_SF_INTERLACED)
        {
            retVal += VpsHal_dssVidPipeSetBufAddr(
                pathObj->pipeHandle,
                (UInt32) 1U,
                (UInt32) pathObj->progFrame->addr[1][0],
                (UInt32) pathObj->progFrame->addr[1][1]);
        }
        else
        {
            /* In case of switching from interlaced to progressive, sometimes
             * buffer is fetched from BA1 insted of BA0. So program BA1 with
             * same value for progressive display. */
            retVal += VpsHal_dssVidPipeSetBufAddr(
                pathObj->pipeHandle,
                1U,
                (UInt32) pathObj->progFrame->addr[0][0],
                (UInt32) pathObj->progFrame->addr[0][1]);
        }

        if (retVal == BSP_SOK)
        {
            retVal = Vpscore_dctrlReadyToSetGoBit(pathObj->dcHandle);
        }

        BspOsal_restoreInterrupt(cookie);
    }

    return retVal;
}

Int32 VpsCore_dssProgBuffer(VpsCore_Handle pathHandle,
                            VpsCore_Frame *frm,
                            UInt32         bypassLowLatencyCheck)
{
    VpsCore_DssPathObj *pathObj = (VpsCore_DssPathObj *) pathHandle;
    Int32  retVal = BSP_SOK;
    Int32  isSafe = (Int32) FALSE;
    UInt32 curLineNum;
    UInt32 cookie;

    GT_assert(VpsDssCoreTrace, (NULL != pathHandle));
    GT_assert(VpsDssCoreTrace, (frm != NULL));

    cookie = BspOsal_disableInterrupt();

    if (pathObj->isStarted == FALSE)
    {
        retVal = BSP_EFAIL;
    }

    if (retVal == BSP_SOK)
    {
        retVal = Vpscore_dctrlGetCurLineNumber(pathObj->dcHandle,
                                               &curLineNum);

        if ((retVal == BSP_SOK) && (curLineNum < pathObj->dispHeight))
        {
            if ((pathObj->dispHeight - curLineNum) >= 5U)
            {
                isSafe = (Int32) TRUE;
            }
            else
            {
                isSafe = (Int32) FALSE;
            }
        }
        else
        {
            isSafe = (Int32) FALSE;
        }

        /* Current Line number will be 0 in VFP, VSW and VBP(blanking),so the
         * decision cant be solely based on current line number. Its safe to
         * push the buffer from start of frame upto start of VFP - 5 lines,
         * so we basically need to know if we are currently in VFP(unsafe) or
         * VSW/VBP(safe to push)*/
        if (curLineNum == 0)
        {
            isSafe = (Int32) Vpscore_dctrlIsSafeToPush(pathObj->dcHandle);
        }

        if (pathObj->dispHeight <= 5U)
        {
            isSafe = (Int32) FALSE;
        }

        /* If user wants to bypass the check, override all logic and do
         * as requested!! */
        if (TRUE == bypassLowLatencyCheck)
        {
            isSafe = (Int32) TRUE;
            retVal = BSP_SOK;
        }
    }

    if ((retVal == BSP_SOK) && (isSafe == (Int32) TRUE))
    {
        pathObj->progFrame = frm;

        retVal += VpsHal_dssVidPipeSetBufAddr(
            pathObj->pipeHandle,
            0,
            (UInt32) pathObj->progFrame->addr[0][0],
            (UInt32) pathObj->progFrame->addr[0][1]);

        if (pathObj->inScanFormat == FVID2_SF_INTERLACED)
        {
            retVal += VpsHal_dssVidPipeSetBufAddr(
                pathObj->pipeHandle,
                (UInt32) 1U,
                (UInt32) pathObj->progFrame->addr[1][0],
                (UInt32) pathObj->progFrame->addr[1][1]);
        }
        else
        {
            /* In case of switching from interlaced to progressive, sometimes
             * buffer is fetched from BA1 insted of BA0. So program BA1 with
             * same value for progressive display. */
            retVal += VpsHal_dssVidPipeSetBufAddr(
                pathObj->pipeHandle,
                1U,
                (UInt32) pathObj->progFrame->addr[0][0],
                (UInt32) pathObj->progFrame->addr[0][1]);
        }
    }

    if ((retVal == BSP_SOK) && (isSafe == (Int32) TRUE))
    {
        /* TODO - here go bit needs to be set immediately, define onemore API */
        retVal = Vpscore_dctrlReadyToSetGoBit(pathObj->dcHandle);
    }

    BspOsal_restoreInterrupt(cookie);

    return isSafe;
}

static Int32 VpsCore_dssVidPathCopyConfig(VpsCore_DssPathObj          *pathObj,
                                          const VpsCore_DispDssParams *pathCfg)
{
    Int32  retVal = BSP_SOK;
    UInt32 tempWidth, tempPitch;

    VpsHal_dssAdvDmaConfigInit(&pathObj->halAdvDmaCfg);

    pathObj->vidPipeCfg.outHeight = pathCfg->tarHeight;
    pathObj->vidPipeCfg.outWidth  = pathCfg->tarWidth;
    pathObj->vidPipeCfg.posX      = pathCfg->posX + pathObj->shiftVidPosX;
    pathObj->vidPipeCfg.posY      = pathCfg->posY;
    pathObj->inScanFormat         = pathCfg->inFmt.scanFormat;
    pathObj->memType = pathCfg->memType;

    /* Only Field merge of plane 1 is considered here, as DSS doesn't support
     *  different options for different planes */
    pathObj->isFieldMergeBuff = pathCfg->inFmt.fieldMerged[0];

    BspUtils_memcpy(
        &pathObj->vidPipeCfg.inFmt,
        &pathCfg->inFmt,
        sizeof (Fvid2_Format));

    /* In case of Interlaced output, in Height and out Height should be devided
     * by 2 to make it field height */
    if (pathObj->inScanFormat == FVID2_SF_INTERLACED)
    {
        pathObj->vidPipeCfg.inFmt.height /= 2U;
        pathObj->vidPipeCfg.outHeight    /= 2U;
    }

    tempWidth = pathObj->vidPipeCfg.inFmt.width;
    tempPitch = pathObj->vidPipeCfg.inFmt.pitch[0];

    if (retVal == BSP_SOK)
    {
        VpsHal_dssVidPipeCfgInit(&pathObj->vidPipeCfg);

        if ((Int32) TRUE == Fvid2_isDataFmtYuv422I(pathCfg->inFmt.dataFormat))
        {
            if (tempPitch < (tempWidth * 2U))
            {
                GT_0trace(VpsDssCoreTrace, GT_ERR, "Pitch less than Width \n");
                retVal = BSP_EBADARGS;
            }
            else
            {
                pathObj->halAdvDmaCfg.rowInc =
                    (tempPitch - (tempWidth * 2U)) + 1U;
            }
        }
        else if ((Int32) TRUE ==
                 Fvid2_isDataFmtSemiPlanar(pathCfg->inFmt.dataFormat))
        {
            if (tempPitch < tempWidth)
            {
                GT_0trace(VpsDssCoreTrace, GT_ERR, "Pitch less than Width \n");
                retVal = BSP_EBADARGS;
            }
            else
            {
                pathObj->halAdvDmaCfg.rowInc = (tempPitch - tempWidth) + 1U;
            }
        }
        else if ((Int32) TRUE ==
                 Fvid2_isDataFmtRgb16bit(pathCfg->inFmt.dataFormat))
        {
            if (tempPitch < (tempWidth * 2U))
            {
                GT_0trace(VpsDssCoreTrace, GT_ERR, "Pitch less than Width \n");
                retVal = BSP_EBADARGS;
            }
            else
            {
                pathObj->halAdvDmaCfg.rowInc =
                    (tempPitch - (tempWidth * 2U)) + 1U;
            }
        }
        else if ((Int32) TRUE ==
                 Fvid2_isDataFmtRgb24bit(pathCfg->inFmt.dataFormat))
        {
            if (tempPitch < (tempWidth * 3U))
            {
                GT_0trace(VpsDssCoreTrace, GT_ERR, "Pitch less than Width \n");
                retVal = BSP_EBADARGS;
            }
            else
            {
                pathObj->halAdvDmaCfg.rowInc =
                    (tempPitch - (tempWidth * 3U)) + 1U;
            }
        }
        else if ((Int32) TRUE ==
                 Fvid2_isDataFmtRgb32bit(pathCfg->inFmt.dataFormat))
        {
            if (tempPitch < (tempWidth * 4U))
            {
                GT_0trace(VpsDssCoreTrace, GT_ERR, "Pitch less than Width \n");
                retVal = BSP_EBADARGS;
            }
            else
            {
                pathObj->halAdvDmaCfg.rowInc =
                    (tempPitch - (tempWidth * 4U)) + 1U;
            }
        }
        else
        {
            GT_0trace(VpsDssCoreTrace, GT_ERR, "Un supported data format \n");
            retVal = BSP_EINVALID_PARAMS;
        }

        /* For interlaced buffers we need to skip one line */
        if ((pathObj->inScanFormat == FVID2_SF_INTERLACED) &&
            (pathObj->isFieldMergeBuff == TRUE))
        {
            pathObj->halAdvDmaCfg.rowInc += pathObj->vidPipeCfg.inFmt.pitch[0];
        }

        if (pathCfg->vidCfg != NULL)
        {
            pathObj->vidPipeCfg.chromaSampling =
                pathCfg->vidCfg->pipeCfg.chromaSampling;
            pathObj->vidPipeCfg.cscFullRngEnable =
                pathCfg->vidCfg->pipeCfg.cscFullRngEnable;
            pathObj->vidPipeCfg.repliEnable =
                pathCfg->vidCfg->pipeCfg.repliEnable;
            pathObj->vidPipeCfg.scEnable =
                pathCfg->vidCfg->pipeCfg.scEnable;

            if (pathCfg->vidCfg->advDmaCfg != NULL)
            {
                pathObj->halAdvDmaCfg.burstSize =
                    pathCfg->vidCfg->advDmaCfg->burstSize;
                pathObj->halAdvDmaCfg.burstType =
                    pathCfg->vidCfg->advDmaCfg->burstType;
                pathObj->halAdvDmaCfg.bufPreloadType =
                    pathCfg->vidCfg->advDmaCfg->bufPreloadType;
                pathObj->halAdvDmaCfg.bufHighThreshold =
                    pathCfg->vidCfg->advDmaCfg->bufHighThreshold;
                pathObj->halAdvDmaCfg.bufLowThreshold =
                    pathCfg->vidCfg->advDmaCfg->bufLowThreshold;
                pathObj->halAdvDmaCfg.selfRefreshEnable =
                    pathCfg->vidCfg->advDmaCfg->selfRefreshEnable;
                pathObj->halAdvDmaCfg.arbitration =
                    pathCfg->vidCfg->advDmaCfg->arbitration;
                pathObj->halAdvDmaCfg.pixelInc =
                    pathCfg->vidCfg->advDmaCfg->pixelInc;
            }
            if (pathCfg->vidCfg->vc1Cfg != NULL)
            {
                BspUtils_memcpy(
                    &pathObj->vc1Cfg,
                    pathCfg->vidCfg->vc1Cfg,
                    sizeof (Vps_DssDispcVidVC1Config));
            }
        }
    }
    return retVal;
}

static Int32 VpsCore_dssGfxPathCopyConfig(VpsCore_DssPathObj          *pathObj,
                                          const VpsCore_DispDssParams *pathCfg)
{
    Int32  retVal = BSP_SOK;
    UInt32 tempWidth, tempPitch;

    /* Only Field merge of plane 1 is considered here, as DSS doesn't support
     *  different options for different planes */
    pathObj->isFieldMergeBuff = pathCfg->inFmt.fieldMerged[0];

    /* Copy input format first, this cannot be done after data format
     * conversion */
    BspUtils_memcpy(
        &pathObj->gfxPipeCfg.inFmt,
        &pathCfg->inFmt,
        sizeof (Fvid2_Format));

    pathObj->inScanFormat         = pathCfg->inFmt.scanFormat;

    /* In case of Interlaced output, in Height and out Height should be devided
     * by 2 to make it field height */
    if (pathObj->inScanFormat == FVID2_SF_INTERLACED)
    {
        pathObj->gfxPipeCfg.inFmt.height /= 2U;
    }

    tempWidth = pathObj->gfxPipeCfg.inFmt.width;
    tempPitch = pathObj->gfxPipeCfg.inFmt.pitch[0];

    if (retVal == BSP_SOK)
    {
        VpsHal_dssAdvDmaConfigInit(&pathObj->halAdvDmaCfg);

        pathObj->gfxPipeCfg.posX = pathCfg->posX + pathObj->shiftVidPosX;
        pathObj->gfxPipeCfg.posY = pathCfg->posY;
        pathObj->memType         = pathCfg->memType;

        VpsHal_dssGfxPipeCfgInit(&pathObj->gfxPipeCfg);

        /* Gfx only supports RGB formats */
        if ((Int32) TRUE == Fvid2_isDataFmtRgb16bit(pathCfg->inFmt.dataFormat))
        {
            if (tempPitch < (tempWidth * 2U))
            {
                GT_0trace(VpsDssCoreTrace, GT_ERR, "Pitch less than Width \n");
                retVal = BSP_EBADARGS;
            }
            else
            {
                pathObj->halAdvDmaCfg.rowInc =
                    (tempPitch - (tempWidth * 2U)) + 1U;
            }
        }
        else if ((Int32) TRUE ==
                 Fvid2_isDataFmtRgb24bit(pathCfg->inFmt.dataFormat))
        {
            if (tempPitch < (tempWidth * 3U))
            {
                GT_0trace(VpsDssCoreTrace, GT_ERR, "Pitch less than Width \n");
                retVal = BSP_EBADARGS;
            }
            else
            {
                pathObj->halAdvDmaCfg.rowInc =
                    (tempPitch - (tempWidth * 3U)) + 1U;
            }
        }
        else if ((Int32) TRUE ==
                 Fvid2_isDataFmtRgb32bit(pathCfg->inFmt.dataFormat))
        {
            if (tempPitch < (tempWidth * 4U))
            {
                GT_0trace(VpsDssCoreTrace, GT_ERR, "Pitch less than Width \n");
                retVal = BSP_EBADARGS;
            }
            else
            {
                pathObj->halAdvDmaCfg.rowInc =
                    (tempPitch - (tempWidth * 4U)) + 1U;
            }
        }
        else
        {
            GT_0trace(VpsDssCoreTrace, GT_ERR, "Un supported data format \n");
            retVal = BSP_EINVALID_PARAMS;
        }

        /* For interlaced buffers we need to skip one line */
        if ((pathObj->inScanFormat == FVID2_SF_INTERLACED) &&
            (pathObj->isFieldMergeBuff == TRUE))
        {
            pathObj->halAdvDmaCfg.rowInc += pathObj->gfxPipeCfg.inFmt.pitch[0];
        }

        if (pathCfg->gfxCfg != NULL)
        {
            pathObj->gfxPipeCfg.antiFlickerEnable =
                pathCfg->gfxCfg->pipeCfg.antiFlickerEnable;
            pathObj->gfxPipeCfg.repliEnable =
                pathCfg->gfxCfg->pipeCfg.repliEnable;

            if (pathCfg->gfxCfg->advDmaCfg != NULL)
            {
                pathObj->halAdvDmaCfg.burstSize =
                    pathCfg->gfxCfg->advDmaCfg->burstSize;
                pathObj->halAdvDmaCfg.burstType =
                    pathCfg->gfxCfg->advDmaCfg->burstType;
                pathObj->halAdvDmaCfg.bufPreloadType =
                    pathCfg->gfxCfg->advDmaCfg->bufPreloadType;
                pathObj->halAdvDmaCfg.bufHighThreshold =
                    pathCfg->gfxCfg->advDmaCfg->bufHighThreshold;
                pathObj->halAdvDmaCfg.bufLowThreshold =
                    pathCfg->gfxCfg->advDmaCfg->bufLowThreshold;
                pathObj->halAdvDmaCfg.selfRefreshEnable =
                    pathCfg->gfxCfg->advDmaCfg->selfRefreshEnable;
                pathObj->halAdvDmaCfg.arbitration =
                    pathCfg->gfxCfg->advDmaCfg->arbitration;
                pathObj->halAdvDmaCfg.pixelInc =
                    pathCfg->gfxCfg->advDmaCfg->pixelInc;
            }
        }
    }

    return retVal;
}

static Int32 VpsCore_isGfxPipeline(const VpsCore_DssPathObj *pathObj)
{
    Int32 retVal = (Int32) FALSE;

    if (pathObj->handleId == VPS_DSS_DISPC_PIPE_GFX1)
    {
        retVal = (Int32) TRUE;
    }
    else
    {
        retVal = (Int32) FALSE;
    }

    return retVal;
}

static Int32 VpsCore_isVidPipeline(const VpsCore_DssPathObj *pathObj)
{
    Int32 retVal = (Int32) FALSE;

    if ((pathObj->handleId == VPS_DSS_DISPC_PIPE_VID1) ||
        (pathObj->handleId == VPS_DSS_DISPC_PIPE_VID2) ||
        (pathObj->handleId == VPS_DSS_DISPC_PIPE_VID3))
    {
        retVal = (Int32) TRUE;
    }
    else
    {
        retVal = (Int32) FALSE;
    }

    return retVal;
}

static Int32 VpsCore_isWbPipeline(const VpsCore_DssPathObj *pathObj)
{
    Int32 retVal = (Int32) FALSE;

    if (pathObj->handleId == VPS_DSS_DISPC_PIPE_WB)
    {
        retVal = (Int32) TRUE;
    }
    else
    {
        retVal = (Int32) FALSE;
    }

    return retVal;
}

static Int32 VpsCore_dssValidateDssParams(const VpsCore_DispDssParams *pathCfg,
                                          const VpsCore_DssPathObj    *pathObj)
{
    Int32 retVal = BSP_SOK;

    /*Input widht, height,posx,posy,dispwidth,dispheight*/
    if (((pathCfg->tarHeight + pathCfg->posY) > pathObj->dispHeight) ||
        ((pathCfg->tarWidth + pathCfg->posX) > pathObj->dispWidth))
    {
        GT_0trace(
            VpsDssCoreTrace, GT_ERR,
            "Input width+posx/height+posy > display width /height \n");
        retVal = BSP_EINVALID_PARAMS;
    }
    /* Interlaced to progressive or vice versa*/
    if (pathCfg->inFmt.scanFormat != pathObj->dispScanFormat)
    {
        GT_0trace(
            VpsDssCoreTrace, GT_ERR,
            "Format(interlaced/progressive) conversion is not supported \n");
        retVal = BSP_EINVALID_PARAMS;
    }
    /* Memory type */
    if (pathCfg->memType == VPS_VPDMA_MT_TILEDMEM)
    {
        GT_0trace(
            VpsDssCoreTrace, GT_ERR,
            "Tiled memory not supported \n");
        retVal = BSP_EINVALID_PARAMS;
    }

    /* Scaling ratio check */
    if (((pathCfg->inFmt.height * 8) <
         (pathCfg->tarHeight)) ||
        ((pathCfg->inFmt.width * 8) < (pathCfg->tarWidth)))
    {
        GT_0trace(
            VpsDssCoreTrace, GT_ERR,
            "Upscaling of greater than 8x is not supported \n");
        retVal = BSP_EINVALID_PARAMS;
    }
    if (((pathCfg->inFmt.height) >
         (pathCfg->tarHeight * 4)) ||
        ((pathCfg->inFmt.width) > (pathCfg->tarWidth * 4)))
    {
        GT_0trace(
            VpsDssCoreTrace, GT_ERR,
            "Downscaling of greater than 4x is not supported \n");
        retVal = BSP_EINVALID_PARAMS;
    }
    if ((pathCfg->inFmt.height != pathCfg->tarHeight) ||
        (pathCfg->inFmt.width != pathCfg->tarWidth))
    {
        if (pathCfg->vidCfg->pipeCfg.scEnable == FALSE)
        {
            GT_0trace(
                VpsDssCoreTrace, GT_ERR,
                "Scaling should be enabled\n");
            retVal = BSP_EINVALID_PARAMS;
        }
    }
    return retVal;
}

