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

#include <common/bsp_utils.h>
#include <vps_dctrlDrv.h>

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

static VpsDrv_DctrlInstObj gDctrlDrvObj;
static UInt32 gDrvInit = 0;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static VpsDrv_DctrlInstObj *VpsDrv_DctrlGetInst(void);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  VpsDrv_dctrlInit
 *  \brief VPS DSS capture driver init function.
 *
 *  \param numInst            Number of instances to initialize.
 *  \param initPrms           Pointer to #VpsDrv_DispInitParams.
 *
 *  \return                   success    0
 *                            failure    error value
 *
 */
Int32 VpsDrv_dctrlInit(const VpsDrv_DctrlInitParams *initPrms)
{
    gDctrlDrvObj.drvInstId   = 0;
    gDctrlDrvObj.coreInstObj = initPrms->coreInstObj;
    gDctrlDrvObj.coreOps     = initPrms->coreOps;

    gDrvInit = 1U;
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
Int32 VpsDrv_dctrlDeInit(void)
{
    gDctrlDrvObj.drvInstId   = NULL;
    gDctrlDrvObj.coreInstObj = NULL;
    gDctrlDrvObj.coreOps     = NULL;
    gDrvInit = 0;

    return BSP_SOK;
}

/**
 *  VpsDrv_DctrlGetInst
 *  \brief Get Handle to the Driver control instance as per specified ID
 *
 *  \param instId             Driver control Instance ID
 *
 *  \return                   success    BSP_SOK
 *                            failure    error value
 *
 */

static VpsDrv_DctrlInstObj *VpsDrv_DctrlGetInst(void)
{
    VpsDrv_DctrlInstObj *pObj = NULL;
    if (gDrvInit)
    {
        if (NULL != gDctrlDrvObj.coreInstObj)
        {
            pObj = &gDctrlDrvObj;
        }
    }
    return pObj;
}

/**
 *  VpsDrv_DctrlOpen
 *  \brief Open a capture driver instance as per specified parameters
 *
 *  \param captureOpenParams Capture Driver parameters #VpsCore_OpenPrms
 *  \param vipOpenParams     VIP specific parameters #VpsCore_VipOpenParams
 *
 *  \return                  Capture handle #VpsDrv_CaptInstObj on success
 *                           NULL pointer on failure
 *
 */
VpsDrv_DctrlInstObj *VpsDrv_dctrlOpen(void)
{
    VpsDrv_DctrlInstObj *pObj = NULL;
    VpsCore_OpenPrms     openParams;

    pObj = (VpsDrv_DctrlInstObj *) VpsDrv_DctrlGetInst();
    if (pObj != NULL)
    {
        pObj->coreHandle = NULL;

        /* Init parameters */
        openParams.drvData   = pObj;
        openParams.reqFrmCb  = NULL;
        openParams.frmDoneCb = NULL;

        pObj->coreHandle = (VpsCore_Handle *) pObj->coreOps->open(
            pObj->coreInstObj,
            &openParams,
            NULL,
            NULL
            );
    }
    return pObj;
}

/**
 *  VpsDrv_DctrlClose
 *  \brief Close the specified capture handle
 *
 *  \param pObj         Capture Handle to close
 *
 *  \return             success    BSP_SOK
 *                      failure    error value
 *
 */
Int32 VpsDrv_dctrlClose(VpsDrv_DctrlInstObj *pObj)
{
    Int32 retVal = BSP_SOK;

    retVal = pObj->coreOps->close(pObj->coreInstObj);
    if (BSP_SOK != retVal)
    {
        Bsp_printf("Closing of Dctrl Core resulted in error.\n");
    }
    pObj->coreHandle = NULL;

    return retVal;
}

/**
 *  vpsDrv_DctrlSetConfig
 *  \brief Gets the current display status information.
 *
 *  NOTE: This can't be be called from ISR context.
 *
 *  Returns BSP_SOK on success else returns appropriate error code.
 */
Int32 vpsDrv_DctrlSetConfig(VpsDrv_DctrlInstObj *pObj,
                            Vps_DctrlConfig     *dctrlCfg)

{
    Int32 retVal = BSP_SOK;

    if (NULL == pObj)
    {
        Bsp_printf("Invalid argument!!\n");
        retVal = BSP_EBADARGS;
    }
    else
    {
    #if 0
        for (i = 0; i < dctrlCfg->vencInfo.numVencs; i++)
        {
            if (FVID2_STD_CUSTOM !=
                dctrlCfg->vencInfo.modeInfo[i].mInfo.standard)
            {
                /* Get the timing from FVID2 layer */
                mInfo.standard = dctrlCfg->vencInfo.modeInfo[i].mInfo.standard;
                /* Support for standard formats to be added later*/
            }
        }
    #endif
        retVal = pObj->coreOps->control(
            pObj,
            IOCTL_VPSCORE_DCTRL_SET_CONFIG,
            dctrlCfg,
            (Ptr) pObj->coreInstObj);

        if (BSP_SOK != retVal)
        {
            Bsp_printf("Core control: Set Config failed!!\n");
        }
    }
    return (retVal);
}

/**
 *  vpsDrv_DctrlCleatConfig
 *  \brief Gets the current display status information.
 *
 *  NOTE: This can't be be called from ISR context.
 *
 *  Returns BSP_SOK on success else returns appropriate error code.
 */
Int32 vpsDrv_DctrlClearConfig(VpsDrv_DctrlInstObj *pObj,
                              Vps_DctrlConfig     *dctrlCfg)

{
    Int32 retVal = BSP_SOK;

    /* Check for NULL pointers */
    /* GT_assert(VpsDrvDctrlTrace, (NULL != dctrlCfg)); */

    retVal = pObj->coreOps->control(
        pObj,
        IOCTL_VPSCORE_DCTRL_CLEAR_CONFIG,
        dctrlCfg,
        (Ptr) pObj->coreInstObj);
    if (BSP_SOK != retVal)
    {
        Bsp_printf("Core control: clear config failed!!\n");
    }

    return (retVal);
}

/**
 *  vpsDrv_DctrlSetVencOutput
 *  \brief Gets the current display status information.
 *
 *  NOTE: This can't be be called from ISR context.
 *
 *  Returns FVID2_SOK on success else returns appropriate error code.
 */
Int32 vpsDrv_DctrlSetVencOutput(VpsDrv_DctrlInstObj *pObj,
                                Vps_DctrlOutputInfo *dctrl_info)

{
    Int32 retVal = BSP_SOK;

    retVal = pObj->coreOps->control(
        pObj,
        IOCTL_VPSCORE_DCTRL_SET_VENC_OUTPUT,
        dctrl_info,
        (Ptr) pObj->coreInstObj);
    if (BSP_SOK != retVal)
    {
        Bsp_printf("Core control: Set venc output failed!!\n");
    }

    return (retVal);
}

/**
 *  vpsDrv_DctrlGetVencOutput
 *  \brief Gets the current display status information.
 *
 *  NOTE: This can't be be called from ISR context.
 *
 *  Returns FVID2_SOK on success else returns appropriate error code.
 */
Int32 vpsDrv_DctrlGetVencOutput(VpsDrv_DctrlInstObj *pObj,
                                Vps_DctrlOutputInfo *dctrl_info)

{
    Int32 retVal = BSP_SOK;

    retVal = pObj->coreOps->control(
        pObj,
        IOCTL_VPSCORE_DCTRL_GET_VENC_OUTPUT,
        dctrl_info,
        (Ptr) pObj->coreInstObj);
    if (FVID2_SOK != retVal)
    {
        Bsp_printf("Core control: Get venc output failed!!\n");
    }

    return (retVal);
}

/**
 *  vpsDrvDctrlSetVencDivisorIoctl
 *  \brief Sets the Venc divisor values to get desired pixel clock.
 *
 *  NOTE: This can't be be called from ISR context.
 *
 *  Returns BSP_SOK on success else returns appropriate error code.
 */
Int32 vpsDrv_DctrlSetVencDivisor(
    VpsDrv_DctrlInstObj *pObj,
    Vps_DctrlVencDivisorInfo *
    vencDivisor)

{
    Int32 retVal = BSP_SOK;

    /* Check for NULL pointers */
    /* GT_assert(VpsDrvDctrlTrace, (NULL != vencDivisor)); */

    retVal = pObj->coreOps->control(
        pObj,
        IOCTL_VPSCORE_DCTRL_SET_VENC_PCLK_DIVISORS,
        vencDivisor,
        (Ptr) pObj->coreInstObj);
    if (FVID2_SOK != retVal)
    {
        Bsp_printf("Core control: Set panelconfig failed!!\n");
    }

    return (retVal);
}

/**
 *  vpsDrv_DctrlSetOvlyParms
 *  \brief Gets the current display status information.
 *
 *  NOTE: This can't be be called from ISR context.
 *
 *  Returns BSP_SOK on success else returns appropriate error code.
 */
Int32 vpsDrv_DctrlSetOvlyParams(
    VpsDrv_DctrlInstObj *pObj,
    Vps_DssDispcOvlyPanelConfig *
    panelconfig)

{
    Int32 retVal = BSP_SOK;

    retVal = pObj->coreOps->control(
        pObj,
        IOCTL_VPSCORE_DCTRL_SET_OVLY_PARAMS,
        panelconfig,
        (Ptr) pObj->coreInstObj);
    if (BSP_SOK != retVal)
    {
        Bsp_printf("Core control: Set panelconfig failed!!\n");
    }

    return (retVal);
}

/**
 *  vpsDrvDctrlSetPipelineParmsIoctl
 *  \brief Gets the current display status information.
 *
 *  NOTE: This can't be be called from ISR context.
 *
 *  Returns BSP_SOK on success else returns appropriate error code.
 */
Int32 vpsDrv_DctrlSetPipelineParams(
    VpsDrv_DctrlInstObj        *pObj,
    Vps_DssDispcOvlyPipeConfig *ovlpipeconfig)

{
    Int32 retVal = BSP_SOK;

    /* Check for NULL pointers */
    /* GT_assert(VpsDrvDctrlTrace, (NULL != ovlpipeconfig)); */

    retVal = pObj->coreOps->control(
        pObj,
        IOCTL_VPSCORE_DCTRL_SET_PIPELINE_PARAMS,
        ovlpipeconfig,
        (Ptr) pObj->coreInstObj);

    if (BSP_SOK != retVal)
    {
        Bsp_printf("Core control: Set pipelineconfig failed!!\n");
    }

    return (retVal);
}

