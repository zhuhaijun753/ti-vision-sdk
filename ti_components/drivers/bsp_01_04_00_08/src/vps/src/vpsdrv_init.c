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
 *  \file vpsdrv_init.c
 *
 *  \brief File containing the VPS driver init and deinit functions.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <xdc/std.h>
#include <common/bsp_types.h>
#include <common/trace.h>
#include <common/bsp_config.h>
#include <soc_defines.h>
#include <platforms/bsp_platform.h>
#include <fvid2/fvid2_dataTypes.h>
#include <vps/vps.h>
#include <vps/vps_control.h>
#include <vps/vps_dataTypes.h>
#include <common/vps_common.h>
#include <common/vpscore.h>
#include <vpsdrv_control.h>

#ifdef VPS_CAPT_BUILD
#ifdef VPS_VIP_BUILD
#include <vps/vps_capture.h>
#include <captcore/vpscore_vip.h>
#endif /* VPS_VIP_BUILD */
#include <captdrv/vpsdrv_capture.h>
#include <vps/vps_capture.h>
#endif /* VPS_CAPT_BUILD */

#ifdef VPS_VPE_BUILD
#include <vps/vps_m2m.h>
#include <vpecore/vpscore_m2m.h>
#include <vpecore/vpscore_vpe.h>
#include <vpecore/vpscore_vpeWb.h>
#include <vpedrv/vps_mlm.h>
#include <vpedrv/vpsdrv_m2mVpe.h>
#endif /* VPS_VPE_BUILD */

#ifdef VPS_DISP_BUILD
#include <vps/vps_display.h>
#ifdef VPS_DSS_BUILD
#include <dispcore/vpscore_dss.h>
#include <dispcore/vpscore_dctrl.h>
#include <dispcore/vpscore_dssWb.h>
#endif /* VPS_DSS_BUILD */
#include <dispdrv/vpsdrv_display.h>
#include <dispdrv/vpsdrv_dctrl.h>
#endif /* VPS_DISP_BUILD */

#ifdef VPS_ISS_BUILD
#include <common/iem_evtmgr.h>
#include <captdrv/vpsdrv_capture.h>
#include <isscore/vpscore_capture.h>
#endif /* VPS_ISS_BUILD */

#ifdef VPS_SIMCOP_BUILD
#include <isscore/vpscore_simcop.h>
#endif /* VPS_SIMCOP_BUILD */

#ifdef VPS_M2M_BUILD
#include <vps/vps_m2mIntf.h>
#include <m2mdrv/vpsdrv_m2mintf.h>
#ifdef VPS_ISS_BUILD
#include <vps/iss/vps_m2mIss.h>
#include <isscore/vpscore_m2m.h>
#endif /* VPS_ISS_BUILD */
#ifdef VPS_SIMCOP_BUILD
#include <isscore/vpscore_simcop.h>
#endif /* VPS_SIMCOP_BUILD */
#endif /* VPS_M2M_BUILD */

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief Platform specific data containing base address information of
 *  various modules.
 */
typedef struct
{
#ifdef VPS_CAPT_BUILD
    VpsDrv_CaptInitParams     captDrvInitPrms[VPS_CFG_CAPT_NUM_INST_OBJS];
    /**< Capture driver init parameters. */
#endif

#ifdef VPS_DISP_BUILD
    VpsDrv_DispInitParams     dispDrvInitPrms[VPS_DISP_INST_MAX];
    /**< Display driver init parameters. */
#endif

#ifdef VPS_ISS_BUILD
    VpsDrv_CaptInitParams     issCaptDrvInitPrms[VPS_ISS_CAPT_INST_MAX_ID];
#endif /* VPS_ISS_BUILD */

#ifdef VPS_M2M_BUILD
    VpsMdrv_M2mIntfInitParams m2mIntfDrvInitPrms[VPS_M2M_INTF_INST_MAX];
#endif

    UInt32                    reserved;
    /**< Needed in case both VIP and DSS are not defined!! */
} VpsDrv_PlatformData;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

#if (defined (TDA2XX_FAMILY_BUILD))
void vpsInitTda2xxPlatData(void);
#elif (defined (TDA3XX_FAMILY_BUILD))
void vpsInitTda3xxPlatData(void);
#elif (defined (TI814X_FAMILY_BUILD))
void vpsInitTi814xPlatData(void);
#elif (defined (OMAP5X_FAMILY_BUILD))
void vpsInitOmap5PlatData(void);
#endif

const VpsDrv_PlatformData *VpsDrv_getPlatformData(void);

#ifdef VPS_CAPT_BUILD
static Int32 Vps_captInit(void);
static Int32 Vps_captDeInit(void);
#endif
#ifdef VPS_VPE_BUILD
static Int32 Vps_vpeInit(void);
static Int32 Vps_vpeDeInit(void);
#endif
#ifdef VPS_DISP_BUILD
static Int32 Vps_dispInit(void);
static Int32 Vps_dispDeInit(void);
#endif
#ifdef VPS_M2M_BUILD
static Int32 Vps_m2mInit(void);
static Int32 Vps_m2mDeInit(void);
#endif

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

#ifdef TDA2XX_FAMILY_BUILD
static VpsDrv_PlatformData gVpsDrvPlatDataTda2xx;
#endif

#ifdef TDA3XX_FAMILY_BUILD
static VpsDrv_PlatformData gVpsDrvPlatDataTda3xx;
#endif

#ifdef OMAP5X_FAMILY_BUILD
static VpsDrv_PlatformData gVpsDrvPlatDataOmap5x;
#endif

#ifdef TI814X_FAMILY_BUILD
static VpsDrv_PlatformData gVpsDrvPlatDataTI814x;
#endif

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  \brief VPS init function.
 */
Int32 Vps_init(const Vps_InitParams *initPrms)
{
    Int32             retVal = BSP_SOK;
    Vps_InitParams    localInitPrms;
    VpsLib_InitParams vpsLibInitPrms;

#if (defined (TDA2XX_FAMILY_BUILD))
    vpsInitTda2xxPlatData();
#elif (defined (TDA3XX_FAMILY_BUILD))
    vpsInitTda3xxPlatData();
#elif (defined (TI814X_FAMILY_BUILD))
    vpsInitTi814xPlatData();
#elif (defined (OMAP5X_FAMILY_BUILD))
    vpsInitOmap5PlatData();
#else
    GT_0trace(VpsDrvTrace, GT_ERR, "VPS: Unsupported SOC!!\n");
#endif

    if (NULL == initPrms)
    {
        initPrms = &localInitPrms;
        VpsInitParams_init(&localInitPrms);
    }

    vpsLibInitPrms.isAddrTransReq  = initPrms->isAddrTransReq;
    vpsLibInitPrms.virtBaseAddr    = initPrms->virtBaseAddr;
    vpsLibInitPrms.physBaseAddr    = initPrms->physBaseAddr;
    vpsLibInitPrms.isCacheOpsReq   = initPrms->isCacheOpsReq;
    vpsLibInitPrms.isCacheFlushReq = initPrms->isCacheFlushReq;
    retVal = VpsLib_init(&vpsLibInitPrms);
    if (BSP_SOK == retVal)
    {
        retVal += VpsDrv_ctrlInit();
#ifdef VPS_CAPT_BUILD
        retVal += Vps_captInit();
#endif
#ifdef VPS_VPE_BUILD
        retVal += Vps_vpeInit();
#endif
#ifdef VPS_DISP_BUILD
        retVal += Vps_dispInit();
#endif
#ifdef VPS_M2M_BUILD
        retVal += Vps_m2mInit();
#endif
    }

    return (retVal);
}

/**
 *  \brief VPS deinit function.
 */
Int32 Vps_deInit(Ptr args)
{
    Int32 retVal = BSP_SOK;

#ifdef VPS_M2M_BUILD
    retVal += Vps_m2mDeInit();
#endif

#ifdef VPS_DISP_BUILD
    retVal += Vps_dispDeInit();
#endif
#ifdef VPS_VPE_BUILD
    retVal += Vps_vpeDeInit();
#endif
#ifdef VPS_CAPT_BUILD
    retVal += Vps_captDeInit();
#endif

    retVal += VpsDrv_ctrlDeInit();
    retVal += VpsLib_deInit(NULL);

    return (retVal);
}

const VpsDrv_PlatformData *VpsDrv_getPlatformData(void)
{
    VpsDrv_PlatformData *platData = NULL;
#if (defined (TDA2XX_FAMILY_BUILD))
    platData = &gVpsDrvPlatDataTda2xx;
#elif (defined (TDA3XX_FAMILY_BUILD))
    platData = &gVpsDrvPlatDataTda3xx;
#elif (defined (TI814X_FAMILY_BUILD))
    platData = &gVpsDrvPlatDataTI814x;
#elif (defined (OMAP5X_FAMILY_BUILD))
    platData = &gVpsDrvPlatDataOmap5x;
#else
    GT_0trace(VpsDrvTrace, GT_ERR, "VPS: Unsupported SOC!!\n");
#endif
    return (platData);
}

#ifdef VPS_CAPT_BUILD
static Int32 Vps_captInit(void)
{
    Int32  retVal  = BSP_SOK;
    UInt32 instCnt = 0, numInst = 0;

#ifdef VPS_VIP_BUILD
    UInt32 numVipPort;
#endif
#ifdef VPS_DSS_BUILD
    UInt32 numWbPipe;
#endif

    UInt32 captInstCnt = 0U;
    const VpsLib_PlatformData *libPlatData;
    const VpsDrv_PlatformData *drvPlatData;
#ifdef VPS_ISS_BUILD
    VpsDrv_CaptInitParams      captDrvInitPrms[VPS_CFG_CAPT_NUM_INST_OBJS +
                                               VPS_ISS_CAPT_INST_MAX_ID];
#else
    VpsDrv_CaptInitParams      captDrvInitPrms[VPS_CFG_CAPT_NUM_INST_OBJS];
#endif /* VPS_ISS_BUILD */

    /* Get Platform data */
    libPlatData = VpsLib_getPlatformData();

#ifdef VPS_VIP_BUILD
    numVipPort = libPlatData->hal->numVipPort;
    numInst   += numVipPort;
    GT_assert(VpsDrvTrace,
              (numVipPort <= VPS_CFG_CAPT_NUM_INST_OBJS));
#endif

#ifdef VPS_DSS_BUILD
    numWbPipe = libPlatData->hal->numWbPipe;
    numInst  += numWbPipe;
    GT_assert(VpsDrvTrace,
              (numWbPipe <= VPS_DISP_INST_MAX));
#endif

#ifdef VPS_ISS_BUILD
    numInst += VPS_ISS_CAPT_INST_MAX_ID;
    GT_assert(VpsDrvTrace,
              (numInst <= (VPS_CFG_CAPT_NUM_INST_OBJS + VPS_ISS_CAPT_INST_MAX_ID)));
#endif

    GT_assert(VpsDrvTrace, (NULL != libPlatData));

    drvPlatData = VpsDrv_getPlatformData();
    GT_assert(VpsDrvTrace, (NULL != drvPlatData));

#ifdef VPS_VIP_BUILD
    for (instCnt = 0U; instCnt < numVipPort; instCnt++)
    {
        captDrvInitPrms[captInstCnt].drvInstId =
            drvPlatData->captDrvInitPrms[instCnt].drvInstId;
        captDrvInitPrms[captInstCnt].coreInstObj =
            VpsLib_getVipCoreInstObj(
                Vps_captGetVipId(captDrvInitPrms[instCnt].drvInstId));

        GT_assert(VpsDrvTrace,
                  (NULL != captDrvInitPrms[captInstCnt].coreInstObj));

        captDrvInitPrms[captInstCnt].coreOps = VpsCore_vipGetCoreOps();
        captInstCnt++;
    }
#endif

#ifdef VPS_DSS_BUILD
    for (instCnt = 0U; instCnt < numWbPipe; instCnt++)
    {
        captDrvInitPrms[captInstCnt].drvInstId =
            VPS_CAPT_INST_DSS_WB_BASE + instCnt;
        captDrvInitPrms[captInstCnt].coreInstObj =
            VpsLib_getDssWbCoreInstObj();
        GT_assert(VpsDrvTrace,
                  (NULL != captDrvInitPrms[captInstCnt].coreInstObj));

        captDrvInitPrms[captInstCnt].coreOps = VpsCore_dssWbGetCoreOps();
        captInstCnt++;
    }
#endif

#if defined (VPS_ISS_BUILD)
    {
        UInt32 coreInst = 0;
        for (instCnt = 0U; instCnt < VPS_ISS_CAPT_INST_MAX_ID; instCnt++)
        {
            captDrvInitPrms[captInstCnt].drvInstId = VPS_CAPT_INST_ISS_BASE +
                                                     drvPlatData->
                                                     issCaptDrvInitPrms[instCnt
                                                     ].drvInstId;
            /* Get core instance objects for a given instance */
            captDrvInitPrms[captInstCnt].coreInstObj =
                VpsCore_issCaptGetCoreInstObj((vpsissCaptInstId_t) coreInst);

            GT_assert(VpsDrvTrace,
                      (NULL != captDrvInitPrms[captInstCnt].coreInstObj));

            captDrvInitPrms[captInstCnt].coreOps = VpsCore_issCaptGetCoreOps();
            captInstCnt++;
            coreInst++;
        }
    }
#endif

    /* Call Capture init only if required */
    if (captInstCnt > 0U)
    {
        retVal =
            VpsDrv_captInit(captInstCnt, &captDrvInitPrms[0U]);
    }

    return (retVal);
}

static Int32 Vps_captDeInit(void)
{
    Int32 retVal = BSP_SOK;

    retVal = VpsDrv_captDeInit();

    return (retVal);
}

#endif /* VPS_ISS_BUILD */

#ifdef VPS_M2M_BUILD
static Int32 Vps_m2mInit(void)
{
    Int32  retVal  = BSP_SOK;
    UInt32 instCnt = 0U;
    VpsMdrv_M2mIntfInitParams m2mDrvInitPrms[VPS_M2M_INTF_INST_MAX];

#ifdef VPS_ISS_BUILD
    m2mDrvInitPrms[instCnt].drvInstId          = VPS_M2M_ISS_INST_CAL_ISP;
    m2mDrvInitPrms[instCnt].isMultiChSupported = FALSE;
    m2mDrvInitPrms[instCnt].numCores           = 1U;
    m2mDrvInitPrms[instCnt].coreInstId[0U]     =
        VpsCore_issM2mGetCoreInstObj(VPSCORE_ISS_M2M_ISP_INST_0);
    m2mDrvInitPrms[instCnt].coreOps[0U] = VpsCore_issM2mGetCoreOps();
    instCnt++;
#endif

#ifdef VPS_SIMCOP_BUILD
    m2mDrvInitPrms[instCnt].drvInstId          = VPS_M2M_ISS_INST_SIMCOP;
    m2mDrvInitPrms[instCnt].isMultiChSupported = FALSE;
    m2mDrvInitPrms[instCnt].numCores           = 1U;
    m2mDrvInitPrms[instCnt].coreInstId[0U]     =
        (VpsCore_Inst *) VPSCORE_ISS_SIMCOP_INST_0;
    m2mDrvInitPrms[instCnt].coreOps[0U] = VpsCore_simcopGetCoreOps();

    instCnt++;
#endif

    if (0 < instCnt)
    {
        retVal = VpsMdrv_intfInit(instCnt, &m2mDrvInitPrms[0U]);
    }
    else
    {
        retVal = BSP_EFAIL;
    }

    return (retVal);
}

static Int32 Vps_m2mDeInit(void)
{
    Int32 retVal = BSP_SOK;

    retVal = VpsMdrv_intfDeInit();

    return (retVal);
}

#endif /* VPS_M2M_BUILD */

#ifdef VPS_VPE_BUILD
static Int32 Vps_vpeInit(void)
{
    Int32                 retVal = BSP_SOK;
    VpsHal_Handle         vpdmaHandle;
    Mlm_InitParams        mlmInitPrms;
    VpsMdrv_VpeInitParams vpeDrvInitPrms;
    UInt32                numInst;

    /* MLM Init */
    if (BSP_SOK == retVal)
    {
        vpdmaHandle = VpsLib_getVpdmaHalHandle(VPSHAL_VPE1_VPDMA);
        if (NULL == vpdmaHandle)
        {
            vpdmaHandle = VpsLib_getVpdmaHalHandle(VPSHAL_VPDMA_GENERIC);
            GT_assert(VpsDrvTrace, (NULL != vpdmaHandle));
            mlmInitPrms.vpdmaHandle = vpdmaHandle;
            mlmInitPrms.vemInstId   = VEM_INST_ID_GENERIC;
            mlmInitPrms.vrmInstId   = VRM_INST_ID_GENERIC;
        }
        else
        {
            mlmInitPrms.vpdmaHandle = vpdmaHandle;
            mlmInitPrms.vemInstId   = VEM_INST_ID_VPE1;
            mlmInitPrms.vrmInstId   = VRM_INST_ID_VPE1;
        }
        retVal = Mlm_init(&mlmInitPrms);
        if (retVal != BSP_SOK)
        {
            GT_0trace(VpsDrvTrace, GT_ERR, "VPS: MLM init failed\n");
        }
    }

    /* M2M VPE driver Init */
    if (BSP_SOK == retVal)
    {
        vpeDrvInitPrms.drvInstId = VPS_M2M_INST_VPE1;
        vpeDrvInitPrms.coreInstId[VPSMDRV_VPE_VPE_CORE_IDX] =
            VCORE_VPE_INST_PRI;
        vpeDrvInitPrms.coreInstId[VPSMDRV_VPE_VWB_CORE_IDX] =
            VCORE_VWB_INST_WB0;
        vpeDrvInitPrms.coreOps[VPSMDRV_VPE_VPE_CORE_IDX] =
            Vcore_vpeGetCoreOps();
        vpeDrvInitPrms.coreOps[VPSMDRV_VPE_VWB_CORE_IDX] =
            Vcore_vwbGetCoreOps();
        numInst = 1U;
        retVal  = VpsMdrv_vpeInit(numInst, &vpeDrvInitPrms);
        if (retVal != BSP_SOK)
        {
            GT_0trace(VpsDrvTrace, GT_ERR, "VPS: M2M VPE init failed\n");
        }
    }

    return (retVal);
}

static Int32 Vps_vpeDeInit(void)
{
    Int32 retVal = BSP_SOK;

    retVal += VpsMdrv_vpeDeInit();
    retVal += Mlm_deInit();

    return (retVal);
}

#endif

#ifdef VPS_DISP_BUILD
static Int32 Vps_dispInit(void)
{
    Int32  retVal = BSP_SOK;
    UInt32 instCnt;
    const VpsLib_PlatformData *libPlatData;
    const VpsDrv_PlatformData *drvPlatData;
    VpsDrv_DispInitParams      dispDrvInitPrms[VPS_DISP_INST_MAX];
    VpsDrv_DctrlInitParams     dctrlDrvInitPrms;

    /* Get Platform data */
    libPlatData = VpsLib_getPlatformData();
    GT_assert(VpsDrvTrace, (NULL != libPlatData));
    drvPlatData = VpsDrv_getPlatformData();
    GT_assert(VpsDrvTrace, (NULL != drvPlatData));

    dctrlDrvInitPrms.coreInstObj = VpsLib_getDctrlCoreInstObj();
    dctrlDrvInitPrms.coreOps     = VpsCore_dctrlGetCoreOps();

    VpsDrv_dctrlInit(&dctrlDrvInitPrms);

#ifdef VPS_DSS_BUILD
    GT_assert(VpsDrvTrace,
              ((libPlatData->hal->numVidPipe) <= VPS_DISP_INST_MAX));
    for (instCnt = 0U; instCnt < libPlatData->hal->numVidPipe; instCnt++)
    {
        dispDrvInitPrms[instCnt].drvInstId =
            drvPlatData->dispDrvInitPrms[instCnt].drvInstId;
        dispDrvInitPrms[instCnt].coreInstObj = VpsLib_getDssCoreInstObj();
        GT_assert(VpsDrvTrace, (NULL != dispDrvInitPrms[instCnt].coreInstObj));
        dispDrvInitPrms[instCnt].coreOps = VpsCore_dssGetCoreOps();
    }
#endif

    /* Call display init only if required */
    if (libPlatData->hal->numVidPipe > 0U)
    {
        retVal = VpsDrv_dispInit(libPlatData->hal->numVidPipe,
                                 &dispDrvInitPrms[0U]);
    }

    return (retVal);
}

static Int32 Vps_dispDeInit(void)
{
    Int32 retVal = BSP_SOK;
    const VpsLib_PlatformData *platData;

    /* Get Platform data */
    platData = VpsLib_getPlatformData();
    GT_assert(VpsDrvTrace, (NULL != platData));

    /* Call display deinit only if required */
    if (platData->hal->numVidPipe > 0U)
    {
        retVal += VpsDrv_dispDeInit();
    }

    VpsDrv_dctrlDeInit();

    return (retVal);
}

#endif

/* ========================================================================== */
/*                              Local Functions                               */
/* ========================================================================== */

#if (defined (TDA2XX_FAMILY_BUILD))
void vpsInitTda2xxPlatData(void)
{
#if (defined (VPS_VIP_BUILD) || defined (VPS_DSS_BUILD))
    UInt32 idx = 0;
#ifdef VPS_CAPT_BUILD
#ifdef VPS_VIP_BUILD
#if defined (VPS_VIP1_BUILD)
    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].drvInstId =
        VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA);
    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].coreOps     = NULL;
    idx++;

    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].drvInstId =
        VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTB);
    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].coreOps     = NULL;
    idx++;

    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].drvInstId =
        VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA);
    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].coreOps     = NULL;
    idx++;

    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].drvInstId =
        VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTB);
    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].coreOps     = NULL;
    idx++;

    GT_assert(VpsDrvTrace, (VPS_CFG_CAPT_NUM_INST_OBJS > idx));
#endif  /* #if defined (VPS_VIP1_BUILD) */
#ifndef TDA2EX_BUILD
#if defined (VPS_VIP2_BUILD)
    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].drvInstId =
        VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP2, VPS_VIP_S0, VPS_VIP_PORTA);
    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].coreOps     = NULL;
    idx++;

    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].drvInstId =
        VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP2, VPS_VIP_S0, VPS_VIP_PORTB);
    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].coreOps     = NULL;
    idx++;

    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].drvInstId =
        VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP2, VPS_VIP_S1, VPS_VIP_PORTA);
    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].coreOps     = NULL;
    idx++;

    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].drvInstId =
        VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP2, VPS_VIP_S1, VPS_VIP_PORTB);
    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].coreOps     = NULL;
    idx++;
#endif  /* #if defined (VPS_VIP2_BUILD) */
#if defined (VPS_VIP3_BUILD)
    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].drvInstId =
        VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP3, VPS_VIP_S0, VPS_VIP_PORTA);
    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].coreOps     = NULL;
    idx++;

    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].drvInstId =
        VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP3, VPS_VIP_S0, VPS_VIP_PORTB);
    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].coreOps     = NULL;
    idx++;

    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].drvInstId =
        VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP3, VPS_VIP_S1, VPS_VIP_PORTA);
    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].coreOps     = NULL;
    idx++;

    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].drvInstId =
        VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP3, VPS_VIP_S1, VPS_VIP_PORTB);
    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].coreOps     = NULL;
    idx++;
    GT_assert(VpsDrvTrace, (VPS_CFG_CAPT_NUM_INST_OBJS > idx));
#endif /* #if defined (VPS_VIP3_BUILD) */
#endif /* TDA2EX_BUILD */
#endif /* VPS_VIP_BUILD */

#ifdef VPS_DSS_BUILD

    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].drvInstId =
        VPS_CAPT_INST_DSS_WB1;
    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataTda2xx.captDrvInitPrms[idx].coreOps     = NULL;
    GT_assert(VpsDrvTrace, (VPS_CFG_CAPT_NUM_INST_OBJS > idx));

#endif /* VPS_DSS_BUILD */
#endif /* VPS_CAPT_BUILD */

    /* Display driver */
#ifdef VPS_DSS_BUILD
    idx = 0;
    gVpsDrvPlatDataTda2xx.dispDrvInitPrms[idx].drvInstId =
        VPS_DISP_INST_DSS_VID1;
    gVpsDrvPlatDataTda2xx.dispDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataTda2xx.dispDrvInitPrms[idx].coreOps     = NULL;
    idx++;

    gVpsDrvPlatDataTda2xx.dispDrvInitPrms[idx].drvInstId =
        VPS_DISP_INST_DSS_VID2;
    gVpsDrvPlatDataTda2xx.dispDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataTda2xx.dispDrvInitPrms[idx].coreOps     = NULL;
    idx++;

    gVpsDrvPlatDataTda2xx.dispDrvInitPrms[idx].drvInstId =
        VPS_DISP_INST_DSS_VID3;
    gVpsDrvPlatDataTda2xx.dispDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataTda2xx.dispDrvInitPrms[idx].coreOps     = NULL;
    idx++;

    gVpsDrvPlatDataTda2xx.dispDrvInitPrms[idx].drvInstId =
        VPS_DISP_INST_DSS_GFX1;
    gVpsDrvPlatDataTda2xx.dispDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataTda2xx.dispDrvInitPrms[idx].coreOps     = NULL;
    GT_assert(VpsDrvTrace, (VPS_DISP_INST_MAX > idx));
#endif /* VPS_DSS_BUILD */
#endif /* defined(VPS_VIP_BUILD) ||... */
}

#endif

#if (defined (TDA3XX_FAMILY_BUILD))
void vpsInitTda3xxPlatData(void)
{
#if (defined (VPS_VIP_BUILD) || defined (VPS_DSS_BUILD) || \
    defined (VPS_ISS_BUILD))
    UInt32 idx = 0;
#ifdef VPS_CAPT_BUILD
#ifdef VPS_VIP_BUILD
#if defined (VPS_VIP1_BUILD)
    gVpsDrvPlatDataTda3xx.captDrvInitPrms[idx].drvInstId =
        VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA);
    gVpsDrvPlatDataTda3xx.captDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataTda3xx.captDrvInitPrms[idx].coreOps     = NULL;
    idx++;

    gVpsDrvPlatDataTda3xx.captDrvInitPrms[idx].drvInstId =
        VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTB);
    gVpsDrvPlatDataTda3xx.captDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataTda3xx.captDrvInitPrms[idx].coreOps     = NULL;
    idx++;

    gVpsDrvPlatDataTda3xx.captDrvInitPrms[idx].drvInstId =
        VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA);
    gVpsDrvPlatDataTda3xx.captDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataTda3xx.captDrvInitPrms[idx].coreOps     = NULL;
    idx++;

    gVpsDrvPlatDataTda3xx.captDrvInitPrms[idx].drvInstId =
        VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTB);
    gVpsDrvPlatDataTda3xx.captDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataTda3xx.captDrvInitPrms[idx].coreOps     = NULL;
    idx++;
    GT_assert(VpsDrvTrace, (VPS_CFG_CAPT_NUM_INST_OBJS > idx));
#endif /* #if defined (VPS_VIP1_BUILD) */
#endif /* VPS_VIP_BUILD */

#ifdef VPS_DSS_BUILD
    gVpsDrvPlatDataTda3xx.captDrvInitPrms[idx].drvInstId =
        VPS_CAPT_INST_DSS_WB1;
    gVpsDrvPlatDataTda3xx.captDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataTda3xx.captDrvInitPrms[idx].coreOps     = NULL;
    GT_assert(VpsDrvTrace, (VPS_CFG_CAPT_NUM_INST_OBJS > idx));
#endif /* VPS_DSS_BUILD */
#endif /* VPS_CAPT_BUILD */

    /* Display driver */
#ifdef VPS_DSS_BUILD
    idx = 0;
    gVpsDrvPlatDataTda3xx.dispDrvInitPrms[idx].drvInstId =
        VPS_DISP_INST_DSS_VID1;
    gVpsDrvPlatDataTda3xx.dispDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataTda3xx.dispDrvInitPrms[idx].coreOps     = NULL;
    idx++;
    gVpsDrvPlatDataTda3xx.dispDrvInitPrms[idx].drvInstId =
        VPS_DISP_INST_DSS_VID2;
    gVpsDrvPlatDataTda3xx.dispDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataTda3xx.dispDrvInitPrms[idx].coreOps     = NULL;
    idx++;

    gVpsDrvPlatDataTda3xx.dispDrvInitPrms[idx].drvInstId =
        VPS_DISP_INST_DSS_GFX1;
    gVpsDrvPlatDataTda3xx.dispDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataTda3xx.dispDrvInitPrms[idx].coreOps     = NULL;
    GT_assert(VpsDrvTrace, (VPS_DISP_INST_MAX > idx));
#endif /* VPS_DSS_BUILD */

#ifdef VPS_ISS_BUILD

    /* Generic capture driver should be included in the build, else we cannot
     *  support ISS based capture */
#ifndef VPS_CAPT_BUILD
    #error "ReBuild after including build option -DVPS_CAPT_BUILD"
#endif /* VPS_CAPT_BUILD */

    idx = 0;
    gVpsDrvPlatDataTda3xx.issCaptDrvInitPrms[idx].drvInstId =
        VPS_ISS_CAPT_CAL_A_ID;
    gVpsDrvPlatDataTda3xx.issCaptDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataTda3xx.issCaptDrvInitPrms[idx].coreOps     = NULL;
    idx++;
    gVpsDrvPlatDataTda3xx.issCaptDrvInitPrms[idx].drvInstId =
        VPS_ISS_CAPT_CAL_A_CPI;
    gVpsDrvPlatDataTda3xx.issCaptDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataTda3xx.issCaptDrvInitPrms[idx].coreOps     = NULL;
    idx++;
    gVpsDrvPlatDataTda3xx.issCaptDrvInitPrms[idx].drvInstId =
        VPS_ISS_CAPT_CAL_A_OTF0_ID;
    gVpsDrvPlatDataTda3xx.issCaptDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataTda3xx.issCaptDrvInitPrms[idx].coreOps     = NULL;
    GT_assert(VpsDrvTrace, (VPS_ISS_CAPT_INST_MAX_ID > idx));

#endif /* VPS_ISS_BUILD */
#endif /* (defined(VPS_VIP_BUILD) ||... */

#ifdef VPS_M2M_BUILD

    BspUtils_memset(&gVpsDrvPlatDataTda3xx.m2mIntfDrvInitPrms, 0U,
                    sizeof (gVpsDrvPlatDataTda3xx.m2mIntfDrvInitPrms));
    idx = 0U;

#ifdef VPS_ISS_BUILD
    gVpsDrvPlatDataTda3xx.m2mIntfDrvInitPrms[idx].drvInstId =
        VPS_M2M_ISS_INST_CAL_ISP;
    gVpsDrvPlatDataTda3xx.m2mIntfDrvInitPrms[idx].isMultiChSupported = FALSE;
    gVpsDrvPlatDataTda3xx.m2mIntfDrvInitPrms[idx].numCores           = 1U;
    gVpsDrvPlatDataTda3xx.m2mIntfDrvInitPrms[idx].coreInstId[0U]     =
        VpsCore_issM2mGetCoreInstObj(VPSCORE_ISS_M2M_ISP_INST_0);
    idx++;
#endif /* VPS_ISS_BUILD */

#ifdef VPS_SIMCOP_BUILD
    gVpsDrvPlatDataTda3xx.m2mIntfDrvInitPrms[idx].drvInstId =
        VPS_M2M_ISS_INST_SIMCOP;
    gVpsDrvPlatDataTda3xx.m2mIntfDrvInitPrms[idx].isMultiChSupported = FALSE;
    gVpsDrvPlatDataTda3xx.m2mIntfDrvInitPrms[idx].numCores           = 1U;
    gVpsDrvPlatDataTda3xx.m2mIntfDrvInitPrms[idx].coreInstId[0U]     =
        (VpsCore_Inst *) VPSCORE_ISS_SIMCOP_INST_0;
    idx++;
#endif /* VPS_SIMCOP_BUILD */

#endif /* VPS_M2M_BUILD */
}

#endif /* end of TDA3XX_FAMILY_BUILD */

#if (defined (OMAP5X_FAMILY_BUILD))
void vpsInitOmap5PlatData(void)
{
#ifdef VPS_DSS_BUILD
    UInt32 idx = 0;
    gVpsDrvPlatDataOmap5x.dispDrvInitPrms[idx].drvInstId =
        VPS_DISP_INST_DSS_VID1;
    gVpsDrvPlatDataOmap5x.dispDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataOmap5x.dispDrvInitPrms[idx].coreOps     = NULL;
    idx++;

    gVpsDrvPlatDataOmap5x.dispDrvInitPrms[idx].drvInstId =
        VPS_DISP_INST_DSS_VID2;
    gVpsDrvPlatDataOmap5x.dispDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataOmap5x.dispDrvInitPrms[idx].coreOps     = NULL;
    idx++;

    gVpsDrvPlatDataOmap5x.dispDrvInitPrms[idx].drvInstId =
        VPS_DISP_INST_DSS_VID3;
    gVpsDrvPlatDataOmap5x.dispDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataOmap5x.dispDrvInitPrms[idx].coreOps     = NULL;
    idx++;

    gVpsDrvPlatDataOmap5x.dispDrvInitPrms[idx].drvInstId =
        VPS_DISP_INST_DSS_GFX1;
    gVpsDrvPlatDataOmap5x.dispDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataOmap5x.dispDrvInitPrms[idx].coreOps     = NULL;
    GT_assert(VpsDrvTrace, (VPS_DISP_INST_MAX > idx));
#endif /* VPS_DSS_BUILD */
}

#endif /* OMAP5X_FAMILY_BUILD */

#if (defined (TI814X_FAMILY_BUILD))
void vpsInitTi814xPlatData(void)
{
#if (defined (VPS_VIP_BUILD) || defined (VPS_DSS_BUILD))
    UInt32 idx = 0;
#ifdef VPS_CAPT_BUILD
#ifdef VPS_VIP_BUILD
#if defined (VPS_VIP1_BUILD)
    gVpsDrvPlatDataTI814x.captDrvInitPrms[idx].drvInstId =
        VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTA);
    gVpsDrvPlatDataTI814x.captDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataTI814x.captDrvInitPrms[idx].coreOps     = NULL;
    idx++;

    gVpsDrvPlatDataTI814x.captDrvInitPrms[idx].drvInstId =
        VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S0, VPS_VIP_PORTB);
    gVpsDrvPlatDataTI814x.captDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataTI814x.captDrvInitPrms[idx].coreOps     = NULL;
    idx++;

    gVpsDrvPlatDataTI814x.captDrvInitPrms[idx].drvInstId =
        VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTA);
    gVpsDrvPlatDataTI814x.captDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataTI814x.captDrvInitPrms[idx].coreOps     = NULL;
    idx++;

    gVpsDrvPlatDataTI814x.captDrvInitPrms[idx].drvInstId =
        VPS_CAPT_VIP_MAKE_INST_ID(VPS_VIP1, VPS_VIP_S1, VPS_VIP_PORTB);
    gVpsDrvPlatDataTI814x.captDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataTI814x.captDrvInitPrms[idx].coreOps     = NULL;
    GT_assert(VpsDrvTrace, (VPS_CFG_CAPT_NUM_INST_OBJS > idx));
#endif /* #if defined (VPS_VIP1_BUILD) */
#endif /* VPS_VIP_BUILD */
#endif /* VPS_CAPT_BUILD */

#ifdef VPS_DSS_BUILD
    idx = 0;
    gVpsDrvPlatDataTI814x.dispDrvInitPrms[idx].drvInstId   = VPS_DISP_INST_MAX;
    gVpsDrvPlatDataTI814x.dispDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataTI814x.dispDrvInitPrms[idx].coreOps     = NULL;
    idx++;
    gVpsDrvPlatDataTI814x.dispDrvInitPrms[idx].drvInstId   = VPS_DISP_INST_MAX;
    gVpsDrvPlatDataTI814x.dispDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataTI814x.dispDrvInitPrms[idx].coreOps     = NULL;
    idx++;
    gVpsDrvPlatDataTI814x.dispDrvInitPrms[idx].drvInstId   = VPS_DISP_INST_MAX;
    gVpsDrvPlatDataTI814x.dispDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataTI814x.dispDrvInitPrms[idx].coreOps     = NULL;
    idx++;
    gVpsDrvPlatDataTI814x.dispDrvInitPrms[idx].drvInstId   = VPS_DISP_INST_MAX;
    gVpsDrvPlatDataTI814x.dispDrvInitPrms[idx].coreInstObj = NULL;
    gVpsDrvPlatDataTI814x.dispDrvInitPrms[idx].coreOps     = NULL;
    GT_assert(VpsDrvTrace, (VPS_DISP_INST_MAX > idx));
#endif /* VPS_DSS_BUILD */
#endif /* (defined(VPS_VIP_BUILD) || defined(VPS_DSS_BUILD)) */
}

#endif

