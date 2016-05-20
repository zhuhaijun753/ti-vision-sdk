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
 *  \file vpscore_dssWb.c
 *
 *  \brief DSS WB core implementation
 *  This file implements the VPS core interface for DSS WB.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stddef.h>
#include <stdint.h>
#include <common/stw_dataTypes.h>
#include <common/stw_types.h>
#include <common/bsp_types.h>
#include <common/trace.h>
#include <common/stw_config.h>
#include <common/bsp_utils.h>
#include <fvid2/fvid2_dataTypes.h>

#include <dispcore/vpscore_dssWb.h>
#include <dispcore/src/vpscore_dctrlIntr.h>
#include <dispcore/src/vpscore_dssWbPriv.h>
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

static Int32 VpsCore_dssValidateDssWbParams(
    const VpsCore_DispDssWbParams *pathCfg,
    const VpsCore_DssWbPathObj    *
    pathObj);

static Int32 VpsCore_dssWbPathCopyConfig(VpsCore_DssWbPathObj          *pathObj,
                                         const VpsCore_DispDssWbParams *pathCfg);

static Int32 VpsCore_isWbPipeline(const VpsCore_DssWbPathObj *pathObj);

/**
 *  Below ifdef __cplusplus is added so that C++ build passes without
 *  typecasting. This is because the prototype is build as C type
 *  whereas this file is build as CPP file. Hence we get C++ build error.
 *  Also if tyecasting is used, then we get MisraC error Rule 11.1.
 */
#ifdef __cplusplus
extern "C" {
#endif
static void vpsCoreDssWbDispcCb(Ptr arg0);
#ifdef __cplusplus
}
#endif
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static VpsCore_DssWbObj     gVcoreDssWbObj;

/** \brief Dss Path Objects */
static VpsCore_DssWbPathObj gVcoreDssWbPathObjMemPool[
    VPS_CFG_MEM_DSS_MAX_WB_PIPE_OBJS];
/** \brief Pool parameters for Dss Path Object pool memory */
static BspUtils_PoolParams  VcoreDssWbPathObjPoolParams;
/**
 *  \brief The flag variable represents whether a given context object is
 *  allocated or not
 */
static UInt32 VcoreDssWbPathObjMemFlag[VPS_CFG_MEM_DSS_MAX_WB_PIPE_OBJS];

/** \brief DSS core function pointer. */
static const VpsCore_Ops    gDssWbCoreOps =
{
    &VpsCore_dssWbGetProperty,   /* Get property */
    &VpsCore_dssWbOpen,          /* Open function */
    &VpsCore_dssWbClose,         /* Close function */
    &VpsCore_dssWbPathSetConfig, /* Set config */
    &VpsCore_dssWbPathGetConfig, /* Get config */
    &VpsCore_dssWbControl,       /* Control */
    &VpsCore_dssWbStart,         /* Start */
    &VpsCore_dssWbStop,          /* Stop */
    &VpsCore_dssWbIsr,           /* Process */
    NULL,                        /* Prog Buffer*/
    NULL,                        /* putFrames */
    NULL,                        /* getFrames */
    &VpsCore_dssWbGetErrorStat,  /* Get error stats */
};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

static void vpsCoreDssWbDispcCb(Ptr arg0)
{
    VpsCore_Handle pathHandle;

    GT_assert(VpsDssCoreTrace, (NULL != arg0));
    pathHandle = (VpsCore_Handle) arg0;
    VpsCore_dssWbIsr(pathHandle, (UInt32) 0);

    return;
}

VpsCore_Inst VpsCore_dssWbInit(const VpsCore_DssWbInitParams *initParams)
{
    VpsCore_DssWbObj *pNewObj = &gVcoreDssWbObj;
    UInt32 i;

    /* init path object pool */
    BspUtils_initPool(&VcoreDssWbPathObjPoolParams,
                      (Void *) gVcoreDssWbPathObjMemPool,
                      VPS_CFG_MEM_DSS_MAX_WB_PIPE_OBJS,
                      sizeof (VpsCore_DssWbPathObj),
                      VcoreDssWbPathObjMemFlag,
                      VpsDssCoreTrace);

    pNewObj->dispcIrqNumber = initParams->dispcIrqNumber;
    /* WB pipeline handle*/
    pNewObj->wbHandle[0] = initParams->wbHandle[0];

    pNewObj->dcNodeNum[0] = VPSCORE_DCTRL_NODE_WB;

    for (i = 0; i < VPSHAL_DSS_DISPC_WB_MAX_INST; i++)
    {
        pNewObj->pathObjPool[i] = 0;
    }
    return (VpsCore_Inst) pNewObj;
}

Int32 VpsCore_dssWbDeInit(VpsCore_Inst pDssWbHandle)
{
    return BSP_SOK;
}

/**
 *  VpsCore_dssWbGetCoreOps
 *  \brief Returns the pointer to core function pointer table.
 *
 *  \return             Returns the pointer to core function pointer table.
 */
const VpsCore_Ops *VpsCore_dssWbGetCoreOps(void)
{
    return (&gDssWbCoreOps);
}

Int32 VpsCore_dssWbGetProperty(VpsCore_Inst      instObj,
                               VpsCore_Property *property)
{
    Int32 retVal = BSP_EFAIL;

    if (NULL != property)
    {
        property->name = VPSCORE_DISP_DSSWB;
        retVal         = BSP_SOK;
    }

    return (retVal);
}

Int32 VpsCore_dssWbPathGetConfig(VpsCore_Handle pathHandle,
                                 void          *params)
{
    Int32 retVal = BSP_EFAIL;

    return retVal;
}

Int32 VpsCore_dssWbControl(VpsCore_Handle handle,
                           UInt32         cmd,
                           void          *appArgs,
                           void          *drvArgs)
{
    Int32 retVal = BSP_EFAIL;
    VpsCore_DssWbPathObj *pathObj;

    GT_assert(VpsDssCoreTrace, (NULL != handle));
    GT_assert(VpsDssCoreTrace, (NULL != appArgs));

    pathObj = (VpsCore_DssWbPathObj *) handle;

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

Int32 VpsCore_dssWbGetErrorStat(VpsCore_Handle pathHandle,
                                void          *params)
{
    Int32 retVal = BSP_SOK;
    VpsCore_DssWbPathObj *pathObj;
    VpsCore_DssWbErrorStatus *retParams;

    GT_assert(VpsDssCoreTrace, (NULL != pathHandle));
    GT_assert(VpsDssCoreTrace, (NULL != params));

    pathObj = (VpsCore_DssWbPathObj *) pathHandle;

    retParams = (VpsCore_DssWbErrorStatus *) params;

    retVal = Vpscore_dctrlGetDssWbErrorCount(pathObj->dcHandle, retParams);

    return retVal;
}

VpsCore_Handle VpsCore_dssWbOpen(VpsCore_Inst            pDssWbHandle,
                                 const VpsCore_OpenPrms *openPrms,
                                 const void             *coreOpenPrms,
                                 void                   *coreReturnPrms)
{
    const VpsCore_DssWbOpenParams *corePrms =
        (const VpsCore_DssWbOpenParams *) coreOpenPrms;

    VpsCore_DssWbPathObj          *pathObj       = NULL;
    VpsCore_DssWbObj              *pDssWbInstObj =
        (VpsCore_DssWbObj *) pDssWbHandle;
    Int32 retVal    = BSP_SOK;
    UInt32 index    = 0;
    UInt32 handleId = 0;
    Vpscore_dctrlClientInfo        clientInfo;

    GT_assert(VpsDssCoreTrace, (coreOpenPrms != NULL));
    GT_assert(VpsDssCoreTrace, (openPrms != NULL));

    if (corePrms->src != VPS_DSS_DISPC_PIPE_WB)
    {
        retVal = BSP_EINVALID_PARAMS;
    }
    else
    {
        /* Currently only one WB pipeline present */
        index = 0;
    }

    /* TODO: make this part as re-interant, protect global variables*/
    if (retVal == BSP_SOK)
    {
        if (NULL == pDssWbInstObj->pathObjPool[index])
        {
            pDssWbInstObj->pathObjPool[index] = (VpsCore_Handle) BspUtils_alloc(
                &VcoreDssWbPathObjPoolParams,
                sizeof (VpsCore_DssWbPathObj),
                VpsDssCoreTrace);
            if (pDssWbInstObj->pathObjPool[index] == NULL)
            {
                GT_0trace(
                    VpsDssCoreTrace, GT_ERR,
                    "Failed to allocate memory for pathobj\n");
                retVal = BSP_EALLOC;
            }
            else
            {
                pathObj =
                    (VpsCore_DssWbPathObj *) pDssWbInstObj->pathObjPool[index];
                BspUtils_memset(pathObj, (UInt8) 0U,
                                sizeof (VpsCore_DssWbPathObj));
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
        pathObj->drvData        = openPrms->drvData;
        pathObj->handleId       = (index + VPS_DSS_DISPC_PIPE_WB);
        pathObj->parent         = (VpsCore_DssWbObj *) pDssWbInstObj;
        pathObj->reqFrmCb       = openPrms->reqFrmCb;
        pathObj->frmDoneCb      = openPrms->frmDoneCb;
        pathObj->pipeHandle     = pDssWbInstObj->wbHandle[index];
        pathObj->dcNode         = pDssWbInstObj->dcNodeNum[index];
        pathObj->isStarted      = FALSE;
        pathObj->regionBasedBit = 0;
    }

    if (retVal == BSP_SOK)
    {
        clientInfo.cbFxn  = &vpsCoreDssWbDispcCb;
        clientInfo.arg    = pathObj;
        pathObj->dcHandle = Vpscore_dctrlRegisterClient(
            pathObj->dcNode,
            &clientInfo,
            NULL);
        if (pathObj->dcHandle == NULL)
        {
            GT_1trace(
                VpsDssCoreTrace, GT_ERR,
                "Display Controller registration failed for dss \
                  Wb core instance %d \n",
                index);
            retVal = BSP_EALLOC;
        }
        else
        {
            /* This is to clear the Error(overflow & Incomplete) count */
            Vpscore_dctrlClrErrorCount(pathObj->dcHandle);
        }
    }

    if (retVal != BSP_SOK)
    {
        /* Free previously allocated memory*/
        if (pathObj != NULL)
        {
            if (pathObj->dcHandle != NULL)
            {
                Vpscore_dctrlUnRegisterClient(pathObj->dcHandle);
            }
            handleId = (pathObj->handleId - VPS_DSS_DISPC_PIPE_WB);
            retVal   = BspUtils_free(&VcoreDssWbPathObjPoolParams,
                                     (const Void *) pathObj,
                                     VpsDssCoreTrace);
            pDssWbInstObj->pathObjPool[handleId] = NULL;
        }
        pathObj = NULL;
    }
    return pathObj;
}

Int32 VpsCore_dssWbClose(VpsCore_Handle pathHandle)
{
    VpsCore_DssWbPathObj *pathObj;
    VpsCore_DssWbObj     *pDssWbInstObj;
    UInt32 handleId = 0;

    GT_assert(VpsDssCoreTrace, (NULL != pathHandle));
    pathObj       = (VpsCore_DssWbPathObj *) pathHandle;
    pDssWbInstObj = pathObj->parent;
    GT_assert(VpsDssCoreTrace, (NULL != pDssWbInstObj));

    Vpscore_dctrlUnRegisterClient(pathObj->dcHandle);

    handleId = (pathObj->handleId - VPS_DSS_DISPC_PIPE_WB);
    BspUtils_free(&VcoreDssWbPathObjPoolParams,
                  (const Void *) pathObj,
                  VpsDssCoreTrace);
    pDssWbInstObj->pathObjPool[handleId] = NULL;

    return BSP_SOK;
}

Int32 VpsCore_dssWbPathSetConfig(VpsCore_Handle pathHandle,
                                 const void    *params,
                                 void          *retPrms)
{
    VpsCore_DssWbPathObj          *pathObj =
        (VpsCore_DssWbPathObj *) pathHandle;
    Int32 retVal = BSP_SOK;
    const VpsCore_DispDssWbParams *pathCfg =
        (const VpsCore_DispDssWbParams *) params;

    /* Check for NULL pointer */
    GT_assert(VpsDssCoreTrace, (NULL != pathHandle));
    GT_assert(VpsDssCoreTrace, (NULL != params));

    /* Validate the DssParams */
    retVal = VpsCore_dssValidateDssWbParams(pathCfg, pathObj);
    if (BSP_SOK == retVal)
    {
        /* Copy the Writeback parameters into the path handle. */
        if ((Int32) TRUE == VpsCore_isWbPipeline(pathObj))
        {
            retVal = VpsCore_dssWbPathCopyConfig(pathObj, pathCfg);
        }
        else
        {
            retVal = BSP_EBADARGS;
        }
    }

    /* pathObj->pipeHandle should be opened in core open only */
    if (BSP_SOK == retVal)
    {
        if ((Int32) TRUE == VpsCore_isWbPipeline(pathObj))
        {
            retVal = VpsHal_dssConfWbPipe(pathObj->pipeHandle,
                                          &pathObj->wbPipeCfg);
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

    if (pathObj->wbPipeCfg.wbMode == VPS_DSS_DISPC_WB_CAPT)
    {
        VpsCore_dctrlPipeUpdateOverlayNode(pathObj->dcHandle,
                                           pathObj->wbPipeCfg.inNode);
    }
    else
    {
        /* In m2m Mode WB node acts as Dummy Ovly node */
        VpsCore_dctrlPipeUpdateOverlayNode(pathObj->dcHandle,
                                           VPSCORE_DCTRL_NODE_WB);
    }

    return retVal;
}

Int32 VpsCore_dssWbStart(VpsCore_Handle pathHandle)
{
    VpsCore_DssWbPathObj *pathObj;
    VpsCore_DssWbObj     *pDssInstObj;
    Int32 retVal = BSP_SOK;
    VpsCore_Frame       **programedFrame;

    /* Check for NULL pointer */
    GT_assert(VpsDssCoreTrace, (NULL != pathHandle));
    pathObj     = (VpsCore_DssWbPathObj *) pathHandle;
    pDssInstObj = pathObj->parent;
    GT_assert(VpsDssCoreTrace, (NULL != pDssInstObj));

    /* Reset all the frame pointers to NULL */
    pathObj->curFrame  = NULL;
    pathObj->progFrame = NULL;

    programedFrame = &(pathObj->progFrame);

    /* stream ID and Channel Id is Zero Here */
    *programedFrame = pathObj->reqFrmCb(pathObj->drvData, 0, 0);

    /* Driver should always give the buffers when requested */
    GT_assert(VpsDssCoreTrace, (*programedFrame != NULL));

    /*TODO - Error handling when frame is null*/
    retVal += VpsHal_dssVidPipeSetBufAddr(
        pathObj->pipeHandle,
        0,
        (UInt32) (*programedFrame)->addr[0][0],
        (UInt32) (*programedFrame)->addr[0][1]);

    if (pathObj->outScanFormat == FVID2_SF_INTERLACED)
    {
        retVal += VpsHal_dssVidPipeSetBufAddr(
            pathObj->pipeHandle,
            (UInt32) 1U,
            (UInt32) (*programedFrame)->addr[1][0],
            (UInt32) (*programedFrame)->addr[1][1]);
    }
#ifdef TDA3XX_FAMILY_BUILD
    /* For tda3xx clear region based bit
     * If region based to be enabled its already done in set config
     * When shadow to work copy happens at the end of
     * first frame RB End window This bit should be cleared. */
    VpsHal_dssWbPipeSetRegionBased(pathObj->pipeHandle, 0);
#endif

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

    return retVal;
}

Int32 VpsCore_dssWbStop(VpsCore_Handle pathHandle)
{
    VpsCore_DssWbPathObj *pathObj;
    VpsCore_DssWbObj     *pDssInstObj;
    Int32 retVal = BSP_SOK;

    /* Check for NULL pointer */
    GT_assert(VpsDssCoreTrace, (NULL != pathHandle));
    pathObj     = (VpsCore_DssWbPathObj *) pathHandle;
    pDssInstObj = pathObj->parent;
    GT_assert(VpsDssCoreTrace, (NULL != pDssInstObj));

    retVal = VpsHal_dssVidPipeEnable(pathObj->pipeHandle, (UInt32) FALSE);
    if (retVal == BSP_SOK)
    {
        pathObj->isStarted = FALSE;

        /* Reset all the frame pointers to NULL */
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
Int32 VpsCore_dssWbIsr(VpsCore_Handle pathHandle, UInt32 chId)
{
    VpsCore_DssWbPathObj  *pathObj = (VpsCore_DssWbPathObj *) pathHandle;
    Int32 retVal = BSP_SOK;
    UInt32 cookie;
    VpsCore_DssWbRtParams *rtParams = NULL;

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

        if (pathObj->progFrame->rtParams != NULL)
        {
            rtParams = (VpsCore_DssWbRtParams *) pathObj->progFrame->rtParams;

            pathObj->wbPipeCfg.inHeight      = rtParams->inHeight;
            pathObj->wbPipeCfg.inWidth       = rtParams->inWidth;
            pathObj->wbPipeCfg.outFmt.width  = rtParams->outWidth;
            pathObj->wbPipeCfg.outFmt.height = rtParams->outHeight;
            pathObj->wbPipeCfg.inPosX        = rtParams->inPosX;
            pathObj->wbPipeCfg.inPosY        = rtParams->inPosY;

            retVal += VpsHal_dssConfWbPipe(pathObj->pipeHandle,
                                           &pathObj->wbPipeCfg);
        }
        /*TODO - Error handling when frame is null*/
        retVal += VpsHal_dssVidPipeSetBufAddr(
            pathObj->pipeHandle,
            0,
            (UInt32) pathObj->progFrame->addr[0][0],
            (UInt32) pathObj->progFrame->addr[0][1]);

        if (pathObj->outScanFormat == FVID2_SF_INTERLACED)
        {
            retVal += VpsHal_dssVidPipeSetBufAddr(
                pathObj->pipeHandle,
                (UInt32) 1U,
                (UInt32) pathObj->progFrame->addr[1][0],
                (UInt32) pathObj->progFrame->addr[1][1]);
        }

        /* In case of Tda3xx GOLCD bit will be cleared at WBsync Event and not
         * at Vsync event in capture WB mode. Since the WB is cleared at wbsync
         * the updated configuration for Forward Pipeline (video/gfx) will not
         * be updated in next vsync which comes after current wbsync event.
         * To avoid such scenarios GOLCD will be set in WBSYNC event
         * callback as well. */
        if (retVal == BSP_SOK)
        {
            retVal = Vpscore_dctrlReadyToSetGoBit(pathObj->dcHandle);
        }

#if defined (TDA2XX_FAMILY_BUILD) || defined (OMAP5X_FAMILY_BUILD)
        /* In case of TDA2XX there is WBGO bit which should be set for
         * shadow to work copy for WB registers.*/
        if (retVal == BSP_SOK)
        {
            retVal = VpsHal_dssWbSetGoBit(pathObj->pipeHandle);
        }
#endif

        BspOsal_restoreInterrupt(cookie);
    }

    return retVal;
}

static Int32 VpsCore_dssWbPathCopyConfig(VpsCore_DssWbPathObj          *pathObj,
                                         const VpsCore_DispDssWbParams *pathCfg)
{
    Int32 retVal = BSP_SOK;

    VpsHal_dssWbAdvDmaConfigInit(&pathObj->halAdvDmaCfg);

    VpsHal_dssWbPipeCfgInit(&pathObj->wbPipeCfg);

    pathObj->wbPipeCfg.inHeight     = pathCfg->inHeight;
    pathObj->wbPipeCfg.inWidth      = pathCfg->inWidth;
    pathObj->wbPipeCfg.inPosX       = pathCfg->inPosX;
    pathObj->wbPipeCfg.inPosY       = pathCfg->inPosY;
    pathObj->outScanFormat          = pathCfg->outFmt.scanFormat;
    pathObj->wbPipeCfg.inDataFormat = pathCfg->indataFormat;
    pathObj->wbPipeCfg.inNode       = pathCfg->inNode;
    pathObj->wbPipeCfg.wbMode       = pathCfg->wbMode;

    /* Only Field merge of plane 1 is considered here, as DSS WB doesn't
     * support different options for different planes */
    pathObj->isFieldMergeBuff = pathCfg->outFmt.fieldMerged[0];
    pathObj->currentFieldVal  = FVID2_FID_BOTTOM;

    BspUtils_memcpy(
        &pathObj->wbPipeCfg.outFmt,
        &pathCfg->outFmt,
        sizeof (Fvid2_Format));

    /* In case of Interlaced output, in Height and out Height should be devided
     * by 2 to make it field height */
    if (pathObj->outScanFormat == FVID2_SF_INTERLACED)
    {
        pathObj->wbPipeCfg.inHeight      /= 2U;
        pathObj->wbPipeCfg.outFmt.height /= 2U;
    }

    if (retVal == BSP_SOK)
    {
        if ((Int32) TRUE == Fvid2_isDataFmtYuv422I(pathCfg->outFmt.dataFormat))
        {
            pathObj->halAdvDmaCfg.rowInc =
                (pathObj->wbPipeCfg.outFmt.pitch[0] -
                 (pathObj->wbPipeCfg.outFmt.width * 2)) + 1;
        }
        else if ((Int32) TRUE ==
                 Fvid2_isDataFmtSemiPlanar(pathCfg->outFmt.dataFormat))
        {
            pathObj->halAdvDmaCfg.rowInc =
                (pathObj->wbPipeCfg.outFmt.pitch[0] -
                 (pathObj->wbPipeCfg.outFmt.width)) + 1;
        }
        else if ((Int32) TRUE ==
                 Fvid2_isDataFmtRgb16bit(pathCfg->outFmt.dataFormat))
        {
            pathObj->halAdvDmaCfg.rowInc =
                (pathObj->wbPipeCfg.outFmt.pitch[0] -
                 (pathObj->wbPipeCfg.outFmt.width * 2)) + 1;
        }
        else if ((Int32) TRUE ==
                 Fvid2_isDataFmtRgb24bit(pathCfg->outFmt.dataFormat))
        {
            pathObj->halAdvDmaCfg.rowInc =
                (pathObj->wbPipeCfg.outFmt.pitch[0] -
                 (pathObj->wbPipeCfg.outFmt.width * 3)) + 1;
        }
        else if ((Int32) TRUE ==
                 Fvid2_isDataFmtRgb32bit(pathCfg->outFmt.dataFormat))
        {
            pathObj->halAdvDmaCfg.rowInc =
                (pathObj->wbPipeCfg.outFmt.pitch[0] -
                 (pathObj->wbPipeCfg.outFmt.width * 4)) + 1;
        }
        else
        {
            GT_0trace(
                VpsDssCoreTrace, GT_ERR,
                "Un supported data format \n");
            retVal = BSP_EINVALID_PARAMS;
        }

#ifdef TDA3XX_FAMILY_BUILD
        if (pathObj->halAdvDmaCfg.rowInc != 1)
        {
            GT_0trace(VpsDssCoreTrace, GT_ERR,
                      "Bigger Pitch is not supported for Tda3xx platform \n");
            retVal = BSP_EINVALID_PARAMS;
        }
#endif

        /* For interlaced buffers we need to skip one line */
        if ((pathObj->outScanFormat == FVID2_SF_INTERLACED) &&
            (pathObj->isFieldMergeBuff == TRUE))
        {
            pathObj->halAdvDmaCfg.rowInc += pathObj->wbPipeCfg.outFmt.pitch[0];
        }

        pathObj->wbPipeCfg.cscFullRngEnable =
            pathCfg->wbCfg.pipeCfg.cscFullRngEnable;
        pathObj->wbPipeCfg.scEnable =
            pathCfg->wbCfg.pipeCfg.scEnable;
        pathObj->wbPipeCfg.cropEnable = pathCfg->wbCfg.pipeCfg.cropEnable;

        if (pathCfg->wbCfg.advDmaCfg != NULL)
        {
            pathObj->halAdvDmaCfg.burstSize =
                pathCfg->wbCfg.advDmaCfg->burstSize;
            pathObj->halAdvDmaCfg.burstType =
                pathCfg->wbCfg.advDmaCfg->burstType;
            pathObj->halAdvDmaCfg.bufPreloadType =
                pathCfg->wbCfg.advDmaCfg->bufPreloadType;
            pathObj->halAdvDmaCfg.bufHighThreshold =
                pathCfg->wbCfg.advDmaCfg->bufHighThreshold;
            pathObj->halAdvDmaCfg.bufLowThreshold =
                pathCfg->wbCfg.advDmaCfg->bufLowThreshold;
            pathObj->halAdvDmaCfg.selfRefreshEnable =
                pathCfg->wbCfg.advDmaCfg->selfRefreshEnable;
            pathObj->halAdvDmaCfg.arbitration =
                pathCfg->wbCfg.advDmaCfg->arbitration;
            pathObj->halAdvDmaCfg.pixelInc =
                pathCfg->wbCfg.advDmaCfg->pixelInc;
        }
    }
    return retVal;
}

static Int32 VpsCore_isWbPipeline(const VpsCore_DssWbPathObj *pathObj)
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

static Int32 VpsCore_dssValidateDssWbParams(
    const VpsCore_DispDssWbParams *pathCfg,
    const VpsCore_DssWbPathObj    *
    pathObj)
{
    Int32 retVal = BSP_SOK;

    /* Memory type */
    if (pathCfg->memType == VPS_VPDMA_MT_TILEDMEM)
    {
        GT_0trace(
            VpsDssCoreTrace, GT_ERR,
            "Tiled memory not supported \n");
        retVal = BSP_EINVALID_PARAMS;
    }

    if (pathCfg->wbMode != VPS_DSS_DISPC_WB_CAPT)
    {
        GT_0trace(
            VpsDssCoreTrace, GT_ERR,
            "Only capture Wb supported in current version of driver\n");
        retVal = BSP_EINVALID_PARAMS;
    }

    if (((pathCfg->inHeight * 8) <
         (pathCfg->outFmt.height)) ||
        ((pathCfg->inWidth * 8) < (pathCfg->outFmt.width)))
    {
        GT_0trace(
            VpsDssCoreTrace, GT_ERR,
            "Upscaling of greater than 8x is not supported \n");
        retVal = BSP_EINVALID_PARAMS;
    }

    if ((Int32) TRUE == Fvid2_isDataFmtYuv(pathCfg->outFmt.dataFormat))
    {
        if (((pathCfg->inHeight) >
             (pathCfg->outFmt.height * 2)) ||
            ((pathCfg->inWidth) > (pathCfg->outFmt.width * 2)))
        {
            GT_0trace(
                VpsDssCoreTrace, GT_ERR,
                "Downscaling of greater than 1/2x is not supported \n");
            retVal = BSP_EINVALID_PARAMS;
        }
    }
    else
    {
        if (((pathCfg->inHeight) >
             (pathCfg->outFmt.height * 4)) ||
            ((pathCfg->inWidth) > (pathCfg->outFmt.width * 4)))
        {
            GT_0trace(
                VpsDssCoreTrace, GT_ERR,
                "Downscaling of greater than 1/4x is not supported \n");
            retVal = BSP_EINVALID_PARAMS;
        }
    }

    if ((pathCfg->inHeight != pathCfg->outFmt.height) ||
        (pathCfg->inWidth != pathCfg->outFmt.width))
    {
        if (pathCfg->wbCfg.pipeCfg.scEnable == FALSE)
        {
            GT_0trace(
                VpsDssCoreTrace, GT_ERR,
                "Scaling should be enabled\n");
            retVal = BSP_EINVALID_PARAMS;
        }
    }
    if ((pathCfg->sourceHeight != pathCfg->inHeight) ||
        (pathCfg->sourceWidth != pathCfg->inWidth))
    {
#ifdef TDA2XX_FAMILY_BUILD
        GT_0trace(
            VpsDssCoreTrace, GT_ERR,
            "Crop not supported for tda2xx platform\n");
        retVal = BSP_EINVALID_PARAMS;
#else
        if (pathCfg->wbCfg.pipeCfg.cropEnable == FALSE)
        {
            GT_0trace(
                VpsDssCoreTrace, GT_ERR,
                "Crop (Region based writeback) should be enabled\n");
            retVal = BSP_EINVALID_PARAMS;
        }
#endif
    }
    if (((pathCfg->inHeight + pathCfg->inPosY) > pathCfg->sourceHeight) ||
        ((pathCfg->inWidth + pathCfg->inPosX) > pathCfg->sourceWidth))
    {
        GT_0trace(
            VpsDssCoreTrace, GT_ERR,
            "WB Input width+posx/height+posy > Overlay width /height");
        retVal = BSP_EINVALID_PARAMS;
    }

    return retVal;
}

