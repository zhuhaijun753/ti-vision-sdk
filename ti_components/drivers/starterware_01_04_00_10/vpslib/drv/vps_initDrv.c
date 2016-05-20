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
 *  \file vps_initDrv.c
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

#ifdef VPS_VIP_BUILD
#include <vps_vipDrv.h>
#endif

#ifdef VPS_DSS_BUILD
#include <vps_dssDrv.h>
#include <vps_dctrlDrv.h>
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
#ifdef VPS_DSS_BUILD
extern UInt32 gDssDrvInit;
#endif

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

#ifdef VPS_VIP_BUILD
extern const VpsDrv_VipPlatformData *VpsDrv_getVipPlatformData(void);
#endif

#ifdef VPS_DSS_BUILD
extern const VpsDrv_DssPlatformData *VpsDrv_getDssPlatformData(void);
#endif

#ifdef VPS_VIP_BUILD
extern Int32 VpsDrv_captInit(UInt32                       numInst,
                             const VpsDrv_CaptInitParams *initPrms);
extern Int32 VpsDrv_captDeInit(void);
#endif

#ifdef VPS_DSS_BUILD
extern Int32 VpsDrv_dssInit(UInt32                       numInst,
                            const VpsDrv_DispInitParams *initPrms);
extern Int32 VpsDrv_dssDeInit(void);
#endif

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 *  Vps_init
 *  \brief Initializes all HAL/CORE/DRIVER SW modules for VPS starterware
 *
 *  \param none
 *
 *  \return                   success    0
 *                            failure    error value
 *
 */
Int32 Vps_init(Ptr args)
{
#ifdef VPS_VIP_BUILD
    VpsDrv_CaptInitParams         captDrvInitPrms[VPS_CAPT_VIP_INST_MAX];
    const VpsDrv_VipPlatformData *drvVipPlatData;
#endif

#ifdef VPS_DSS_BUILD
    VpsDrv_DispInitParams         dssDrvInitPrms[VPS_DISP_INST_MAX];
    VpsDrv_DctrlInitParams        dctrlDrvInitPrms;
    const VpsDrv_DssPlatformData *drvDssPlatData;
#endif

#if defined (VPS_VIP_BUILD) || defined (VPS_DSS_BUILD)
    UInt32 instCnt;
#endif

    Int32 retVal;

#if defined (VPS_VIP_BUILD) || defined (VPS_DSS_BUILD)
    const VpsLib_PlatformData    *libPlatData;
#endif

    retVal = VpsLib_init(NULL);

#ifdef VPS_DSS_BUILD
    gDssDrvInit = 1U;
    dctrlDrvInitPrms.coreInstObj = VpsLib_getDctrlCoreInstObj();
    dctrlDrvInitPrms.coreOps     = VpsCore_dctrlGetCoreOps();
    VpsDrv_dctrlInit(&dctrlDrvInitPrms);
#endif

    if (BSP_SOK == retVal)
    {
#if defined (VPS_VIP_BUILD) || defined (VPS_DSS_BUILD)
        /* Get Platform data */
        libPlatData = VpsLib_getPlatformData();
#endif

#ifdef VPS_VIP_BUILD

        drvVipPlatData = VpsDrv_getVipPlatformData();

        for (instCnt = 0U; instCnt < libPlatData->hal->numVipPort; instCnt++)
        {
            captDrvInitPrms[instCnt].drvInstId =
                drvVipPlatData->captDrvInitPrms[instCnt].drvInstId;
            captDrvInitPrms[instCnt].coreInstObj =
                VpsLib_getVipCoreInstObj(
                    Vps_captGetVipId(captDrvInitPrms[instCnt].drvInstId));

            captDrvInitPrms[instCnt].coreOps = VpsCore_vipGetCoreOps();
        }

        retVal =
            VpsDrv_captInit(libPlatData->hal->numVipPort, &captDrvInitPrms[0U]);

#endif

#ifdef VPS_DSS_BUILD

        drvDssPlatData = VpsDrv_getDssPlatformData();
        for (instCnt = 0U; instCnt < libPlatData->hal->numVidPipe; instCnt++)
        {
            dssDrvInitPrms[instCnt].drvInstId =
                drvDssPlatData->DispDrvInitPrms[instCnt].drvInstId;
            dssDrvInitPrms[instCnt].coreInstObj = VpsLib_getDssCoreInstObj();
            dssDrvInitPrms[instCnt].coreOps     = VpsCore_dssGetCoreOps();
        }

        /* Call display init only if required */
        if (libPlatData->hal->numVidPipe > 0U)
        {
            retVal = VpsDrv_dssInit(libPlatData->hal->numVidPipe,
                                    &dssDrvInitPrms[0U]);
        }
#endif
    }

    return retVal;
}

/**
 *  Vps_deInit
 *  \brief Initializes all HAL/CORE/DRIVER SW modules for VPS starterware
 *
 *  \param none
 *
 *  \return                   success    0
 *                            failure    error value
 *
 */

Int32 Vps_deInit(Ptr args)
{
    Int32 retVal = BSP_SOK;

#ifdef VPS_VIP_BUILD
    retVal = VpsDrv_captDeInit();
#endif

#ifdef VPS_DSS_BUILD
    retVal     += VpsDrv_dssDeInit();
    retVal     += VpsDrv_dctrlDeInit();
    gDssDrvInit = 0;
#endif
    retVal += VpsLib_deInit(NULL);

    return retVal;
}

