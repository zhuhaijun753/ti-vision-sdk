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
#include <common/stw_config.h>
#include <common/vps_common.h>

#include <captcore/vpscore_vip.h>
#include <common/bsp_utils.h>
#include <vps_vipDrv.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

static VpsDrv_CaptInstObj     gCaptDrvObj[VPS_CAPT_VIP_INST_MAX];
static UInt32 gDrvInit = 0;
#ifdef TDA2XX_FAMILY_BUILD
static VpsDrv_VipPlatformData gVpsDrvVipPlatDataTda2xx =
{
    /* Capture driver */
    {
        /*  captDrvInitPrms:drvInstId,
         *  captDrvInitPrms:coreInstObj,    captDrvInitPrms:coreOps */
#if defined (VPS_VIP1_BUILD)
        {
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
            NULL, NULL
        },
        {
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTB),
            NULL, NULL
        },
        {
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA),
            NULL, NULL
        },
        {
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTB),
            NULL, NULL
        },
#endif  /* #if defined (VPS_VIP1_BUILD) */
#ifndef TDA2EX_BUILD
#if defined (VPS_VIP2_BUILD)
        {
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP2, VPS_VIP_S0, VPS_VIP_PORTA),
            NULL, NULL
        },
        {
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP2, VPS_VIP_S0, VPS_VIP_PORTB),
            NULL, NULL
        },
        {
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP2, VPS_VIP_S1, VPS_VIP_PORTA),
            NULL, NULL
        },
        {
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP2, VPS_VIP_S1, VPS_VIP_PORTB),
            NULL, NULL
        },
#endif  /* #if defined (VPS_VIP2_BUILD) */
#if defined (VPS_VIP3_BUILD)
        {
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP3, VPS_VIP_S0, VPS_VIP_PORTA),
            NULL, NULL
        },
        {
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP3, VPS_VIP_S0, VPS_VIP_PORTB),
            NULL, NULL
        },
        {
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP3, VPS_VIP_S1, VPS_VIP_PORTA),
            NULL, NULL
        },
        {
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP3, VPS_VIP_S1, VPS_VIP_PORTB),
            NULL, NULL
        }
#endif  /* #if defined (VPS_VIP3_BUILD) */
#endif  /* #ifndef TDA2EX_BUILD */
    },
};
#endif

#ifdef TI814X_FAMILY_BUILD
static VpsDrv_VipPlatformData gVpsDrvVipPlatDataTI814x =
{
    /* Capture driver */
    {
        /*  captDrvInitPrms:drvInstId,
         *  captDrvInitPrms:coreInstObj,    captDrvInitPrms:coreOps */
#if defined (VPS_VIP1_BUILD)
        {
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
            NULL, NULL
        },
        {
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTB),
            NULL, NULL
        },
        {
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA),
            NULL, NULL
        },
        {
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTB),
            NULL, NULL
        }
#endif  /* #if defined (VPS_VIP1_BUILD) */
    },
};
#endif

#ifdef TDA3XX_FAMILY_BUILD
static VpsDrv_VipPlatformData gVpsDrvVipPlatDataTda3xx =
{
    /* Capture driver */
    {
        /*  captDrvInitPrms:drvInstId,
         *  captDrvInitPrms:coreInstObj,    captDrvInitPrms:coreOps */
#if defined (VPS_VIP1_BUILD)
        {
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA),
            NULL, NULL
        },
        {
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTB),
            NULL, NULL
        },
        {
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA),
            NULL, NULL
        },
        {
            VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTB),
            NULL, NULL
        }
#endif  /* #if defined (VPS_VIP1_BUILD) */
    },
};
#endif

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/**
 *  VpsDrv_captInit
 *  \brief VPS VIP capture driver init function.
 *
 *  \param numInst            Number of instances to initialize.
 *  \param initPrms           Pointer to #VpsDrv_CaptInitParams.
 *
 *  \return                   success    0
 *                            failure    error value
 *
 */
Int32 VpsDrv_captInit(UInt32 numInst, const VpsDrv_CaptInitParams *initPrms);

/**
 *  VpsDrv_captDeInit
 *  \brief VPS VIP capture driver de-initialization function.
 *
 *  \return                   success    0
 *                            failure    error value
 *
 */
Int32 VpsDrv_captDeInit(void);

const VpsDrv_VipPlatformData *VpsDrv_getVipPlatformData(void);

/**
 *  vpsDrvCaptVemIsr
 *  \brief Call the ISR function for specified capture handle
 *
 *  \param event        Unused
 *  \param numEvents    Unused
 *  \param arg          Capture Handle instance
 *
 *  \return             none
 *
 */
static Void vpsDrvCaptVemIsr(const UInt32 *event, UInt32 numEvents, Ptr arg);

Void vpsDrvCaptVemSubFrmIsr(const UInt32 *event, UInt32 numEvents, Ptr arg);

/**
 *  VpsDrv_captGetInst
 *  \brief Get Handle to the capture Driver instance as per specified ID
 *
 *  \param instId             Capture Instance ID
 *
 *  \return                   success    BSP_SOK
 *                            failure    error value
 *
 */
static VpsDrv_CaptInstObj *VpsDrv_captGetInst(UInt32 instId);

/**
 *  Below ifdef __cplusplus is added so that C++ build passes without
 *  typecasting. This is because the prototype is build as C type
 *  whereas this file is build as CPP file. Hence we get C++ build error.
 *  Also if tyecasting is used, then we get MisraC error Rule 11.1.
 */
#ifdef __cplusplus
extern "C" {
#endif
/**
 *  vpsDrvCaptVemOverflowIsr
 *  \brief This is the callback when overflow occurs on VIP
 *
 *  \return             success    BSP_SOK
 *                      failure    error value
 *
 */
static Void vpsDrvCaptVemOverflowIsr(const UInt32 *event,
                                     UInt32        numEvents,
                                     Ptr           arg);
#ifdef __cplusplus
}
#endif

/**
 *  VpsDrv_enableOverflowIntr
 *  \brief Function to enable the overflow interrupt.
 *
 *
 *  \param handle           [IN] Display driver instance handle returned by
 *                          create function.
 *  \param overflowParams    [IN] Parameters containing the return argument and
 *                                          the callback function when interrupt
 *                                          occurs.
 *
 *  \return                 Returns BSP_SOK on success else returns
 *                          appropriate error code.
 */

Int32 VpsDrv_enableOverflowIntr(VpsDrv_CaptInstObj       *pObj,
                                const Vps_OverflowParams *overflowParams);

/**
 *  vpsDrvCaptDisableOfIntr
 *  \brief Function to disable overflow interrupt..
 *
 *
 *  \param handle           [IN] Display driver instance handle returned by
 *                          create function.
 *
 *  \return                 Returns BSP_SOK on success else returns
 *                          appropriate error code.
 */

Int32 VpsDrv_captDisableOfIntr(VpsDrv_CaptInstObj *instObj);

/**
 *  VpsDrv_captCheckOverflow
 *  \brief Function to disable check if overflow occured on a VIP instance.
 *
 *
 *  \param handle           [IN] Display driver instance handle returned by
 *                          create function.
 *  \param overflowCheckParams [OUT] Vps_OverflowCheckParams* object
 *                              to recive the status of the overflow.
 *
 *  \return                 Returns BSP_SOK on success else returns
 *                          appropriate error code.
 */

Int32 VpsDrv_captCheckOverflow(VpsDrv_CaptInstObj      *instObj,
                               Vps_OverflowCheckParams *overflowCheckParams);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
/**
 *  VpsDrv_captInit
 *  \brief VPS VIP capture driver init function.
 *
 *  \param numInst            Number of instances to initialize.
 *  \param initPrms           Pointer to #VpsDrv_CaptInitParams.
 *
 *  \return                   success    0
 *                            failure    error value
 *
 */
Int32 VpsDrv_captInit(UInt32 numInst, const VpsDrv_CaptInitParams *initPrms)
{
    UInt32 i, strm;

    for (i = 0; i < numInst; i++)
    {
        gCaptDrvObj[i].drvInstId   = initPrms[i].drvInstId;
        gCaptDrvObj[i].coreInstObj = initPrms[i].coreInstObj;
        gCaptDrvObj[i].coreOps     = initPrms[i].coreOps;
        gCaptDrvObj[i].coreHandle  = NULL;
        gCaptDrvObj[i].vemHandle   = NULL;
        for (strm = 0; strm < VPSCORE_VIP_STREAM_ID_MAX; strm++)
        {
            gCaptDrvObj[i].subFrameCb[strm]      = NULL;
            gCaptDrvObj[i].vemSubFrmHandle[strm] = NULL;
            gCaptDrvObj[i].strmObj[strm].pObj    = &gCaptDrvObj[i];
            gCaptDrvObj[i].strmObj[strm].strmId  = strm;
        }
    }

    gDrvInit = 1U;
    return BSP_SOK;
}

/**
 *  VpsDrv_captDeInit
 *  \brief VPS VIP capture driver de-initialization function.
 *
 *  \return                   success    0
 *                            failure    error value
 *
 */
Int32 VpsDrv_captDeInit(void)
{
    UInt32 i, strm;
    for (i = 0; i < VPS_CAPT_VIP_INST_MAX; i++)
    {
        gCaptDrvObj[i].drvInstId   = NULL;
        gCaptDrvObj[i].coreInstObj = NULL;
        gCaptDrvObj[i].coreOps     = NULL;
        gCaptDrvObj[i].coreHandle  = NULL;
        for (strm = 0; strm < VPSCORE_VIP_STREAM_ID_MAX; strm++)
        {
            gCaptDrvObj[i].subFrameCb[strm]      = NULL;
            gCaptDrvObj[i].vemSubFrmHandle[strm] = NULL;
            gCaptDrvObj[i].strmObj[strm].pObj    = NULL;
            gCaptDrvObj[i].strmObj[strm].strmId  = strm;
        }
    }
    gDrvInit = 0;
    return BSP_SOK;
}

/**
 *  VpsDrv_captGetInst
 *  \brief Get Handle to the capture Driver instance as per specified ID
 *
 *  \param instId             Capture Instance ID
 *
 *  \return                   success    BSP_SOK
 *                            failure    error value
 *
 */
static VpsDrv_CaptInstObj *VpsDrv_captGetInst(UInt32 instId)
{
    VpsDrv_CaptInstObj *pObj = NULL;
    if (gDrvInit)
    {
        if (NULL != gCaptDrvObj[instId].coreInstObj)
        {
            pObj = &gCaptDrvObj[instId];
        }
    }
    return pObj;
}

/**
 *  VpsDrv_captOpen
 *  \brief Open a capture driver instance as per specified parameters
 *
 *  \param vipInstId         VIP Instance ID #Vps_VipInst
 *  \param captureOpenParams Capture Driver parameters #VpsCore_OpenPrms
 *  \param vipOpenParams     VIP specific parameters #VpsCore_VipOpenParams
 *
 *  \return                  Capture handle #VpsDrv_CaptInstObj on success
 *                           NULL pointer on failure
 *
 */
VpsDrv_CaptInstObj *VpsDrv_captOpen(
    UInt32                       vipInstId,
    const VpsCore_OpenPrms      *captureOpenParams,
    const VpsCore_VipOpenParams *vipOpenParams)
{
    VpsDrv_CaptInstObj      *pObj = NULL;
    Int32 retVal = BSP_SOK;
    UInt32 instId;
    VpsCore_VipOpenRetParams vipRetPrms;
    UInt32 vpsDrvCaptVemIsrFxnPtrTmp;
    BspUtils_memset((void *) (&vipRetPrms), 0, sizeof (VpsCore_VipOpenRetParams));

    switch (vipOpenParams->src)
    {
        case S0_PORTA_08:
        case S0_PORTA_16:
        case S0_PORTA_24:
            instId = VPS_CAPT_VIP_MAKE_INST_ID(vipInstId, VPS_VIP_S0,
                                               VPS_VIP_PORTA);
            break;
        case S0_PORTB_08:
            instId = VPS_CAPT_VIP_MAKE_INST_ID(vipInstId, VPS_VIP_S0,
                                               VPS_VIP_PORTB);
            break;
        case S1_PORTA_08:
        case S1_PORTA_16:
        case S1_PORTA_24:
            instId = VPS_CAPT_VIP_MAKE_INST_ID(vipInstId, VPS_VIP_S1,
                                               VPS_VIP_PORTA);
            break;
        case S1_PORTB_08:
            instId = VPS_CAPT_VIP_MAKE_INST_ID(vipInstId, VPS_VIP_S1,
                                               VPS_VIP_PORTB);
            break;
        default:
            retVal = BSP_EFAIL;
            break;
    }

    if (BSP_SOK == retVal)
    {
        pObj = (VpsDrv_CaptInstObj *) VpsDrv_captGetInst(instId);
        if (pObj != NULL)
        {
            pObj->coreHandle = NULL;
            pObj->coreHandle = (VpsCore_Handle *) pObj->coreOps->open(
                pObj->coreInstObj,
                captureOpenParams,
                vipOpenParams,
                &vipRetPrms
                );
            if (NULL == pObj->coreHandle)
            {
                retVal = BSP_EFAIL;
            }
        }
        else
        {
            retVal = BSP_EFAIL;
        }
    }

    if ((VPSCORE_VIP_INTRTYPE_VEM == vipRetPrms.intrType[0U]) &&
        (BSP_SOK == retVal))
    {
        vpsDrvCaptVemIsrFxnPtrTmp = (UInt32) (&vpsDrvCaptVemIsr);
        /* Only single channel supported */
        pObj->vemHandle = NULL;
        pObj->vemHandle = Vem_register(
            vipRetPrms.vemInstId[0U],
            vipRetPrms.vemEventGroup[0U],
            &vipRetPrms.vemEvent[0U],
            (UInt32) 1,
            VEM_PRIORITY1,
            (Vem_ClientCbFxn) vpsDrvCaptVemIsrFxnPtrTmp,
            pObj);
        if (NULL == pObj->vemHandle)
        {
            pObj->coreOps->close(pObj->coreHandle);
            retVal = BSP_EFAIL;
        }
    }
    else
    {
        Bsp_printf("Unsupported ISR mode\n");
        retVal = BSP_EFAIL;
    }

    if (BSP_SOK != retVal)
    {
        pObj = NULL;
    }

    return pObj;
}

/**
 *  VpsDrv_captClose
 *  \brief Close the specified capture handle
 *
 *  \param pObj         Capture Handle to close
 *
 *  \return             success    BSP_SOK
 *                      failure    error value
 *
 */
Int32 VpsDrv_captClose(VpsDrv_CaptInstObj *pObj)
{
    UInt32 strm;
    Int32  retVal = BSP_SOK;

    for (strm = 0U; strm < VPSCORE_VIP_STREAM_ID_MAX; strm++)
    {
        if (NULL != pObj->subFrameCb[strm])
        {
            Vem_unRegister(pObj->vemSubFrmHandle[strm]);
            pObj->vemSubFrmHandle[strm] = NULL;
        }
    }
    if (NULL != pObj->vemHandle)
    {
        Vem_unRegister(pObj->vemHandle);
        pObj->vemHandle = NULL;
    }
    retVal = pObj->coreOps->close(pObj->coreHandle);
    if (BSP_SOK != retVal)
    {
        Bsp_printf("Closing of VIP Core resulted in error.\n");
    }
    pObj->coreHandle = NULL;

    return retVal;
}

/**
 *  VpsDrv_captStart
 *  \brief Start capture on the specified capture handle
 *
 *  \param pObj         Capture Handle #VpsDrv_CaptInstObj
 *
 *  \return             success    BSP_SOK
 *                      failure    error value
 *
 */
Int32 VpsDrv_captStart(VpsDrv_CaptInstObj *pObj)
{
    pObj->overflowCount = 0;
    return pObj->coreOps->start(pObj->coreHandle);
}

/**
 *  VpsDrv_captStop
 *  \brief Stop capture on the specified capture handle
 *
 *  \param pObj         Capture Handle #VpsDrv_CaptInstObj
 *
 *  \return             success    BSP_SOK
 *                      failure    error value
 *
 */
Int32 VpsDrv_captStop(VpsDrv_CaptInstObj *pObj)
{
    return pObj->coreOps->stop(pObj->coreHandle);
}

/**
 *  \brief VPS VIP capture driver control function.
 */
Int32 VpsDrv_captControl(VpsDrv_CaptInstObj *pObj,
                         UInt32              cmd,
                         Ptr                 cmdArgs,
                         Ptr                 cmdStatusArgs)
{
    Int32 retVal = BSP_SOK;
    VpsDrv_CaptInstObj *instObj;

    instObj = (VpsDrv_CaptInstObj *) pObj;
    switch (cmd)
    {
        case IOCTL_VPS_CAPT_SET_VIP_PARAMS:

            retVal = VpsDrv_captSetParams(
                instObj,
                (VpsDrv_VipParams *) cmdArgs);

            break;

        case IOCTL_VPS_CAPT_GET_VIP_PARAMS:

            retVal = VpsDrv_captGetParams(
                instObj,
                (VpsCore_VipParams *) cmdArgs);

            break;

        case IOCTL_VPS_CAPT_REGISTER_OVF_INTR:

            retVal = VpsDrv_enableOverflowIntr(
                instObj,
                (Vps_OverflowParams *) cmdArgs);

            break;

        case IOCTL_VPS_CAPT_CHECK_OVERFLOW:
        {
            retVal = VpsDrv_captCheckOverflow(
                instObj,
                (Vps_OverflowCheckParams *)
                cmdStatusArgs);

            break;
        }

        case IOCTL_VPS_CAPT_RESET_VIP_PORT:
        {
            instObj->coreOps->control(
                instObj->coreHandle,
                VPSCORE_VIP_IOCTL_RESET_VIP_PORT,
                NULL, NULL);

            break;
        }

        case IOCTL_VPS_CAPT_UNREGISTER_OVF_INTR:
        {
            retVal = VpsDrv_captDisableOfIntr(instObj);
            break;
        }

        default:
            retVal = (Int32) FAIL;
            break;
    }

    return (retVal);
}

Int32 VpsDrv_captCheckOverflow(VpsDrv_CaptInstObj      *instObj,
                               Vps_OverflowCheckParams *overflowCheckParams)
{
    UInt32 regIntrStatus = FALSE;
    Int32  retVal;

    /*Get the status of the overflow interrupt registers*/
    retVal = instObj->coreOps->control(
        instObj->coreHandle,
        VPSCORE_VIP_IOCTL_GET_OVERFLOW_REG_STATUS,
        NULL,
        &regIntrStatus);
    if ((instObj->overflowCount > 0) ||
        (0U != regIntrStatus))
    {
        overflowCheckParams->isOverflowOccured = (UInt32) TRUE;
    }
    else
    {
        overflowCheckParams->isOverflowOccured = (UInt32) FALSE;
    }
    return retVal;
}

Int32 VpsDrv_captDisableOfIntr(VpsDrv_CaptInstObj *instObj)
{
    Int32 retVal = BSP_SOK;

    retVal = Vem_unRegister(instObj->vemHandle);

    return retVal;
}

Int32 VpsDrv_enableOverflowIntr(VpsDrv_CaptInstObj       *pObj,
                                const Vps_OverflowParams *overflowParams)
{
    Int32 retVal = BSP_SOK;
    VpsCore_VipOpenRetParams vipRetPrms;

    /*Get the parametrs from the core*/
    vipRetPrms.intrType[0U] = VPSCORE_VIP_INTRTYPE_VEM;
    pObj->coreOps->control(
        pObj->coreHandle,
        VPSCORE_VIP_IOCTL_GET_VEM_PARAMS,
        pObj->coreInstObj,
        &vipRetPrms);

    /*Set the callback function*/
    pObj->overflowCbFxn = overflowParams->overflowCbFxn;
    /*Set the return paramets*/
    pObj->appOverFlowCbPrms = overflowParams->retParams;
    /*While initializing, overflow is not occures*/
    pObj->overflowCount = 0;

    /*Register the interrupt*/
    pObj->overflowVemHandle = Vem_register(
        vipRetPrms.vemInstId[0U],
        vipRetPrms.vemEventGroup[0U],
        &vipRetPrms.vemEvent[0U],
        (UInt32) 1,
        VEM_PRIORITY1,
        vpsDrvCaptVemOverflowIsr,
        pObj);
    if (NULL == pObj->overflowVemHandle)
    {
        retVal = BSP_EFAIL;
    }
    return retVal;
}

/**
 *  VpsDrv_captSetParams
 *  \brief Set capture params for specified handle
 *
 *  \param pObj           Capture Handle #VpsDrv_CaptInstObj
 *  \param captVipParams  Path configuration #VpsCore_VipParams
 *  \param setCfgRetPrms  Non-null pointer to #VpsCore_VipSetCfgRetPrms where
 *                        interrupt related information for sub-frame callbacks
 *                        will be returned.
 *
 *  \return             success    BSP_SOK
 *                      failure    error value
 *
 */
Int32 VpsDrv_captSetParams(VpsDrv_CaptInstObj     *pObj,
                           const VpsDrv_VipParams *captVipParams)
{
    UInt32 strm, event;
    VpsCore_VipSetCfgRetPrms setCfgRetPrms;
    UInt32 vpsDrvCaptVemSubFrmIsrFxnPtrTmp;
    Int32  retVal = BSP_SOK;

    for (strm = 0U; strm < captVipParams->pathCfg->numStreams; strm++)
    {
        if (captVipParams->pathCfg->subFrmPrms[strm].subFrameEnable)
        {
            pObj->subFrameCb[strm] = captVipParams->subFrameCb[strm];
        }
    }

    retVal = pObj->coreOps->setParams(pObj->coreHandle,
                                      captVipParams->pathCfg,
                                      &setCfgRetPrms);

    for (strm = 0U; strm < captVipParams->pathCfg->numStreams; strm++)
    {
        if (retVal == BSP_SOK)
        {
            if ((NULL != pObj->subFrameCb[strm]) &&
                ((captVipParams->pathCfg->subFrmPrms[strm].subFrameEnable) != 0))
            {
                vpsDrvCaptVemSubFrmIsrFxnPtrTmp = (UInt32) &
                                                  vpsDrvCaptVemSubFrmIsr;
                event = setCfgRetPrms.subFrmVemEvent[strm][0U];
                pObj->vemSubFrmHandle[strm] = Vem_register(
                    setCfgRetPrms.subFrmVemInstId,
                    setCfgRetPrms.subFrmVemEventGroup,
                    &event,
                    (UInt32) 1,
                    VEM_PRIORITY0,
                    (Vem_ClientCbFxn) vpsDrvCaptVemSubFrmIsrFxnPtrTmp,
                    &pObj->strmObj[strm]); /* TODO: The last argument will */
                                           /* change */
            }
        }
    }

    return retVal; /* TODO: Error checks */
}

/**
 *  VpsDrv_captGetParams
 *  \brief Get capture params for specified handle. If not configured, this will
 *  return a default configuration
 *
 *  \param pObj         Capture Handle #VpsDrv_CaptInstObj
 *  \param vipParams    Pointer to #VpsCore_VipParams where configuration will
 *                      be copied
 *
 *  \return             success    BSP_SOK
 *                      failure    error value
 *
 */
Int32 VpsDrv_captGetParams(VpsDrv_CaptInstObj *pObj,
                           VpsCore_VipParams  *vipParams)
{
    return pObj->coreOps->getParams(pObj->coreHandle, vipParams);
}

/**
 *  vpsDrvCaptVemIsr
 *  \brief Call the ISR function for specified capture handle
 *
 *  \param event        Unused
 *  \param numEvents    Unused
 *  \param arg          Capture Handle instance
 *
 *  \return             none
 *
 */
static Void vpsDrvCaptVemIsr(const UInt32 *event, UInt32 numEvents, Ptr arg)
{
    VpsDrv_CaptInstObj *pObj = (VpsDrv_CaptInstObj *) arg;
    pObj->coreOps->proc(pObj->coreHandle, 0U); /*Single Channel */
    return;
}

static Void vpsDrvCaptVemOverflowIsr(const UInt32 *event, UInt32 numEvents,
                                     Ptr arg)
{
    UInt32 overflowCbFxnTmp;
    VpsDrv_CaptInstObj *instObj = (VpsDrv_CaptInstObj *) arg;

    overflowCbFxnTmp = (UInt32) instObj->overflowCbFxn;
    VpsDrv_VipOverflowFxn appCallbackFxn =
        (VpsDrv_VipOverflowFxn) overflowCbFxnTmp;

    instObj->overflowCount += 1;
    appCallbackFxn(instObj->appOverFlowCbPrms);
    return;
}

/**
 *  vpsDrvCaptVemSubFrmIsr
 *  \brief Call the Sub Frame ISR function for specified capture handle
 *
 *  \param event        Unused
 *  \param numEvents    Unused
 *  \param arg          Capture Stream object
 *
 *  \return             none
 *
 */
Void vpsDrvCaptVemSubFrmIsr(const UInt32 *event, UInt32 numEvents, Ptr arg)
{
    VpsDrv_CaptStrmObj *strmObj = (VpsDrv_CaptStrmObj *) arg;
    VpsDrv_CaptInstObj *pObj;
    VpsCore_Frame       curFrmptr;

    /* TOOD: NULL checks pending */
    pObj = strmObj->pObj;

    /* Call IOCTL to get the current frame that is being captured,
     * Pass the same to App. */

    pObj->coreOps->control(
        pObj->coreHandle,
        VPSCORE_VIP_IOCTL_GET_CURCAPTFRM_INFO,
        NULL,
        &curFrmptr);

    if (NULL != pObj->subFrameCb[strmObj->strmId])
    {
        /* Issue the user callback */
        pObj->subFrameCb[strmObj->strmId](pObj, &curFrmptr);
    }

    return;
}

/**
 *  VpsDrv_resetPort
 *  \brief Reset specified PORT. For TI814X_FAMILY_BUILD, you MUST call this
 *  function for all active PORTs. This is not required for VAYU.
 *
 *  \param pObj         Capture Handle #VpsDrv_CaptInstObj
 *
 *  \return             success    BSP_SOK
 *                      failure    error value
 *
 */
Int32 VpsDrv_resetPort(VpsDrv_CaptInstObj *pObj)
{
    pObj->overflowCount = 0;
    return pObj->coreOps->control(pObj->coreHandle,
                                  VPSCORE_VIP_IOCTL_RESET_PORT,
                                  NULL, NULL);
}

const VpsDrv_VipPlatformData *VpsDrv_getVipPlatformData(void)
{
#ifdef TDA2XX_FAMILY_BUILD
    return &gVpsDrvVipPlatDataTda2xx;
#elif defined TDA3XX_FAMILY_BUILD
    return &gVpsDrvVipPlatDataTda3xx;
#elif defined TI814X_FAMILY_BUILD
    return &gVpsDrvVipPlatDataTI814x;
#endif
}

