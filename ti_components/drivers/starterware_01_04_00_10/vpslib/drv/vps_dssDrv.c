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
 *  \file vpsdrv_captureApi.c
 *
 *  \brief File containing the VPS capture driver APIs.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <stddef.h>
#include <common/stw_dataTypes.h>
#include <common/stw_types.h>
#include <common/vps_common.h>
#include <common/stw_config.h>
#include <common/bsp_utils.h>
#include <vps_dssDrv.h>
#include <vps_dctrlDrv.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                         Function Declarations                              */
/* ========================================================================== */

static inline Bool Vps_dssIsVidInst(UInt32 instId);
static inline Bool Vps_dssIsGfxInst(UInt32 instId);
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static VpsDrv_DispInstObj     gDispDrvObj[VPS_DISP_INST_MAX];
UInt32 gDssDrvInit = 0;
#ifdef TDA2XX_FAMILY_BUILD
static VpsDrv_DssPlatformData gVpsDssDrvPlatDataTda2xx =
{
    /* Display driver */
    {
        /*  dispDrvInitPrms:drvInstId,
         *  dispDrvInitPrms:coreInstObj,    dispDrvInitPrms:coreOps */
        {
            VPSDRV_DISP_INST_DSS_VID1,
            NULL, NULL
        },
        {
            VPSDRV_DISP_INST_DSS_VID2,
            NULL, NULL
        },
        {
            VPSDRV_DISP_INST_DSS_VID3,
            NULL, NULL
        },
        {
            VPSDRV_DISP_INST_DSS_GFX1,
            NULL, NULL
        }
    },
};
#endif
#ifdef TDA3XX_FAMILY_BUILD
static VpsDrv_DssPlatformData gVpsDssDrvPlatDataTda3xx =
{
    /* Display driver */
    {
        /*  dispDrvInitPrms:drvInstId,
         *  dispDrvInitPrms:coreInstObj,    dispDrvInitPrms:coreOps */
        {
            VPSDRV_DISP_INST_DSS_VID1,
            NULL, NULL
        },
        {
            VPSDRV_DISP_INST_DSS_VID2,
            NULL, NULL
        },
        {
            VPSDRV_DISP_INST_DSS_GFX1,
            NULL, NULL
        },
        {
            0U,
            NULL, NULL
        }
    },
};
#endif

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/**
 *  VpsDrv_dssInit
 *  \brief VPS DSS driver init function.
 *
 *  \param numInst            Number of instances to initialize.
 *  \param initPrms           Pointer to #VpsDrv_DispInitParams.
 *
 *  \return                   success    0
 *                            failure    error value
 *
 */
Int32 VpsDrv_dssInit(UInt32 numInst, const VpsDrv_DispInitParams *initPrms);

/**
 *  VpsDrv_dssDeInit
 *  \brief VPS DSS driver de-initialization function.
 *
 *  \return                   success    0
 *                            failure    error value
 *
 */
Int32 VpsDrv_dssDeInit(void);

const VpsDrv_DssPlatformData *VpsDrv_getDssPlatformData(void);

/**
 *  VpsDrv_dssGetInst
 *  \brief Get Handle to the Dss Driver instance as per specified ID
 *
 *  \param instId             Instance ID
 *
 *  \return                   success    BSP_SOK
 *                            failure    error value
 *
 */
static VpsDrv_DispInstObj *VpsDrv_dssGetInst(UInt32 instId);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
/**
 *  VpsDrv_dispInit
 *  \brief VPS DSS capture driver init function.
 *
 *  \param numInst            Number of instances to initialize.
 *  \param initPrms           Pointer to #VpsDrv_DispInitParams.
 *
 *  \return                   success    0
 *                            failure    error value
 *
 */
Int32 VpsDrv_dssInit(UInt32 numInst, const VpsDrv_DispInitParams *initPrms)
{
    UInt32 i;

    for (i = 0; i < numInst; i++)
    {
        gDispDrvObj[i].drvInstId   = initPrms[i].drvInstId;
        gDispDrvObj[i].coreInstObj = initPrms[i].coreInstObj;
        gDispDrvObj[i].coreOps     = initPrms[i].coreOps;
    }

    return BSP_SOK;
}

/**
 *  VpsDrv_dispDeInit
 *  \brief VPS DSS capture driver de-initialization function.
 *
 *  \return                   success    0
 *                            failure    error value
 *
 */
Int32 VpsDrv_dssDeInit(void)
{
    UInt32 i;
    for (i = 0; i < VPS_DISP_INST_MAX; i++)
    {
        gDispDrvObj[i].drvInstId   = NULL;
        gDispDrvObj[i].coreInstObj = NULL;
        gDispDrvObj[i].coreOps     = NULL;
    }
    return BSP_SOK;
}

/**
 *  VpsDrv_dssGetInst
 *  \brief Get Handle to the capture Driver instance as per specified ID
 *
 *  \param instId             Capture Instance ID
 *
 *  \return                   success    BSP_SOK
 *                            failure    error value
 *
 */
static VpsDrv_DispInstObj *VpsDrv_dssGetInst(UInt32 instId)
{
    VpsDrv_DispInstObj *pObj = NULL;
    if (gDssDrvInit)
    {
        if (NULL != gDispDrvObj[instId].coreInstObj)
        {
            pObj = &gDispDrvObj[instId];
        }
    }
    return pObj;
}

/**
 *  VpsDrv_dssOpen
 *  \brief Open a capture driver instance as per specified parameters
 *
 *  \param dssInstId         DSS Instance ID #dssInstId
 *  \param OpenParams Capture Driver parameters #VpsCore_OpenPrms
 *  \param dssOpenParams     VIP specific parameters #VpsCore_DssOpenParams
 *
 *  \return                  Capture handle #VpsDrv_CaptInstObj on success
 *                           NULL pointer on failure
 *
 */
VpsDrv_DispInstObj *VpsDrv_dssOpen(
    UInt32                 dssInstId,
    VpsCore_OpenPrms      *OpenParams,
    VpsCore_DssOpenParams *dssOpenParams)
{
    VpsDrv_DispInstObj      *pObj = NULL;
    Int32 retVal = BSP_SOK;
    VpsCore_DssOpenRetParams dssRetParams;
    BspUtils_memset((void *) (&dssRetParams), 0,
                    sizeof (VpsCore_DssOpenRetParams));

    pObj = (VpsDrv_DispInstObj *) VpsDrv_dssGetInst(dssInstId);
    if (pObj != NULL)
    {
        OpenParams->drvData = pObj;

        /* Open the core instance */
        switch (pObj->drvInstId)
        {
            case VPSDRV_DISP_INST_DSS_VID1:
                dssOpenParams->src = VPS_DSS_DISPC_PIPE_VID1;
                break;

            case VPSDRV_DISP_INST_DSS_VID2:
                dssOpenParams->src = VPS_DSS_DISPC_PIPE_VID2;
                break;
#ifdef TDA2XX_FAMILY_BUILD
            case VPSDRV_DISP_INST_DSS_VID3:
                dssOpenParams->src = VPS_DSS_DISPC_PIPE_VID3;
                break;
#endif
            case VPSDRV_DISP_INST_DSS_GFX1:
                dssOpenParams->src = VPS_DSS_DISPC_PIPE_GFX1;
                break;

            default:
                retVal = BSP_EINVALID_PARAMS;
                break;
        }

        pObj->coreHandle = NULL;
        pObj->coreHandle = pObj->coreOps->open(
            pObj->coreInstObj,
            (const VpsCore_OpenPrms *) OpenParams,
            dssOpenParams,
            &dssRetParams);
        if (NULL == pObj->coreHandle)
        {
            retVal = BSP_EFAIL;
        }

        if (BSP_SOK == retVal)
        {
            pObj->standard   = dssRetParams.standard;
            pObj->dispWidth  = dssRetParams.dispWidth;
            pObj->dispHeight = dssRetParams.dispHeight;
            pObj->vencId     = dssRetParams.vencId;
        }
        else
        {
            pObj = NULL;
        }
    }
    return pObj;
}

/**
 *  VpsDrv_dssClose
 *  \brief Close the specified capture handle
 *
 *  \param pObj         Dss Handle to close
 *
 *  \return             success    BSP_SOK
 *                      failure    error value
 *
 */
Int32 VpsDrv_dssClose(VpsDrv_DispInstObj *pObj)
{
    Int32 retVal = BSP_SOK;
    if (NULL != pObj->coreHandle)
    {
        /* Close core */
        retVal = pObj->coreOps->close(pObj->coreHandle);
        if (BSP_SOK != retVal)
        {
            retVal = BSP_EFAIL;
        }
        pObj->coreHandle = NULL;
    }
    return retVal;
}

/**
 *  VpsDrv_dssStart
 *  \brief Start capture on the specified capture handle
 *
 *  \param pObj         Capture Handle #VpsDrv_DispInstObj
 *
 *  \return             success    BSP_SOK
 *                      failure    error value
 *
 */
Int32 VpsDrv_dssStart(VpsDrv_DispInstObj *pObj)
{
    Int32 retVal = BSP_SOK;

    retVal = pObj->coreOps->start(pObj->coreHandle);
    if (FVID2_SOK != retVal)
    {
        retVal = BSP_EFAIL;
    }
    return retVal;
}

/**
 *  VpsDrv_dispStop
 *  \brief Stop capture on the specified capture handle
 *
 *  \param pObj         Capture Handle #VpsDrv_DispInstObj
 *
 *  \return             success    BSP_SOK
 *                      failure    error value
 *
 */
Int32 VpsDrv_dssStop(VpsDrv_DispInstObj *pObj)
{
    return pObj->coreOps->stop(pObj->coreHandle);
}

static inline Bool Vps_dssIsVidInst(UInt32 instId)
{
    Bool isVidInst = FALSE;
#if defined (TDA2XX_FAMILY_BUILD)
    if ((VPSDRV_DISP_INST_DSS_VID1 == instId) ||
        (VPSDRV_DISP_INST_DSS_VID2 == instId) ||
        (VPSDRV_DISP_INST_DSS_VID3 == instId))
#elif defined (TDA3XX_FAMILY_BUILD)
    if ((VPSDRV_DISP_INST_DSS_VID1 == instId) ||
        (VPSDRV_DISP_INST_DSS_VID2 == instId))

#endif
    {
        isVidInst = TRUE;
    }

    return (isVidInst);
}

static inline Bool Vps_dssIsGfxInst(UInt32 instId)
{
    Bool isGfxInst = FALSE;

    if (VPSDRV_DISP_INST_DSS_GFX1 == instId)
    {
        isGfxInst = TRUE;
    }

    return (isGfxInst);
}

/**
 *  VpsDrv_dispSetParams
 *  \brief Set capture params for specified handle
 *
 *  \param instObj           Capture Handle #VpsDrv_DispInstObj
 *  \param DssParams         Path configuration #VpsDrv_DispDssParams
 *
 *  \return             success    BSP_SOK
 *                      failure    error value
 *
 */

Int32 VpsDrv_dssSetParams(VpsDrv_DispInstObj         *instObj,
                          const VpsDrv_DispDssParams *dssPrms)
{
    Int32 retVal = BSP_SOK;
    VpsCore_DispDssParams    dssCorePrms;
    Vps_DssDispcVidConfig    vidCoreCfg;
    Vps_DssDispcGfxConfig    gfxCoreCfg;
    Vps_DssDispcAdvDmaConfig advCoreDmaCfg;
    Vps_DssDispcVidVC1Config vc1CoreCfg;

    dssCorePrms.memType   = dssPrms->memType;
    dssCorePrms.posX      = dssPrms->posX;
    dssCorePrms.posY      = dssPrms->posY;
    dssCorePrms.tarHeight = dssPrms->tarHeight;
    dssCorePrms.tarWidth  = dssPrms->tarWidth;

    BspUtils_memcpy(
        &dssCorePrms.inFmt,
        &dssPrms->inFmt,
        sizeof (Fvid2_Format));

    if (Vps_dssIsVidInst(instObj->drvInstId) == TRUE)
    {
        if (dssPrms->vidCfg != NULL)
        {
            dssCorePrms.vidCfg = &vidCoreCfg;
            BspUtils_memcpy(
                &dssCorePrms.vidCfg->pipeCfg,
                &dssPrms->vidCfg->pipeCfg,
                sizeof (Vps_DssDispcVidPipeConfig));

            if (dssPrms->vidCfg->advDmaCfg != NULL)
            {
                dssCorePrms.vidCfg->advDmaCfg = &advCoreDmaCfg;
                BspUtils_memcpy(
                    dssCorePrms.vidCfg->advDmaCfg,
                    dssPrms->vidCfg->advDmaCfg,
                    sizeof (Vps_DssDispcAdvDmaConfig));
            }
            else
            {
                dssCorePrms.vidCfg->advDmaCfg = NULL;
            }

            if (dssPrms->vidCfg->vc1Cfg != NULL)
            {
                dssCorePrms.vidCfg->vc1Cfg = &vc1CoreCfg;
                BspUtils_memcpy(
                    dssCorePrms.vidCfg->vc1Cfg,
                    dssPrms->vidCfg->vc1Cfg,
                    sizeof (Vps_DssDispcVidVC1Config));
            }
            else
            {
                dssCorePrms.vidCfg->vc1Cfg = NULL;
            }
        }
        else
        {
            dssCorePrms.vidCfg = NULL;
        }
    }
    else if (Vps_dssIsGfxInst(instObj->drvInstId) == TRUE)
    {
        if (dssPrms->gfxCfg != NULL)
        {
            dssCorePrms.gfxCfg = &gfxCoreCfg;
            BspUtils_memcpy(
                &dssCorePrms.gfxCfg->pipeCfg,
                &dssPrms->gfxCfg->pipeCfg,
                sizeof (Vps_DssDispcGfxPipeConfig));

            if (dssPrms->gfxCfg->advDmaCfg != NULL)
            {
                dssCorePrms.gfxCfg->advDmaCfg = &advCoreDmaCfg;
                BspUtils_memcpy(
                    dssCorePrms.gfxCfg->advDmaCfg,
                    dssPrms->gfxCfg->advDmaCfg,
                    sizeof (Vps_DssDispcAdvDmaConfig));
            }
            else
            {
                dssCorePrms.gfxCfg->advDmaCfg = NULL;
            }
        }
        else
        {
            dssCorePrms.gfxCfg = NULL;
        }
    }
    else
    {
        GT_assert(VpsDctrlCoreTrace, FALSE);
    }

    if (BSP_SOK == retVal)
    {
        /* Configure the core */
        retVal = instObj->coreOps->setParams(instObj->coreHandle,
                                             &dssCorePrms,
                                             NULL);
        if (BSP_SOK != retVal)
        {
            retVal = BSP_EFAIL;
        }
    }
    return (retVal);
}

/**
 *  VpsDrv_dispGetParams
 *  \brief Get capture params for specified handle. If not configured, this will
 *  return a default configuration
 *
 *  \param pObj         Capture Handle #VpsDrv_DispInstObj
 *  \param vipParams    Pointer to #VpsCore_DispDssParams where configuration
 *                                     will be copied
 *
 *  \return             success    BSP_SOK
 *                      failure    error value
 *
 */
Int32 VpsDrv_dssGetParams(VpsDrv_DispInstObj    *pObj,
                          VpsCore_DispDssParams *dssParams)
{
    return pObj->coreOps->getParams(pObj->coreHandle,
                                    &dssParams);
}

const VpsDrv_DssPlatformData *VpsDrv_getDssPlatformData(void)
{
#if defined (TDA2XX_FAMILY_BUILD)
    return &gVpsDssDrvPlatDataTda2xx;
#elif defined (TDA3XX_FAMILY_BUILD)
    return &gVpsDssDrvPlatDataTda3xx;
#else
    return NULL;
#endif
}

