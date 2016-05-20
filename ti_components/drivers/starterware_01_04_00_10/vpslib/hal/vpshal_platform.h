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
 *  \file vpshal_platform.h
 *
 *  \brief VPS HAL platform dependent header file
 *
 */

#ifndef VPSHAL_PLATFORM_H_
#define VPSHAL_PLATFORM_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <common/bsp_types.h>
#include <hal/vpshal.h>
#if defined (VPS_VIP_BUILD) || defined (VPS_VPE_BUILD)
#include <hal/vpshal_vpdma.h>
#include <hal/vpshal_csc.h>
#include <hal/vpshal_sc.h>
#endif
#ifdef VPS_VIP_BUILD
#include <hal/vpshal_vipTop.h>
#include <hal/vpshal_vipPort.h>
#endif
#ifdef VPS_VPE_BUILD
#include <hal/vpshal_vpeTop.h>
#include <hal/vpshal_dei.h>
#include <hal/vpshal_chrus.h>
#endif
#ifdef VPS_DSS_BUILD
#include <hal/vpshal_dssDispcOvly.h>
#include <hal/vpshal_dssDispcVid.h>
#if defined (TDA2XX_FAMILY_BUILD) || defined (OMAP5X_FAMILY_BUILD)
#include <hal/vpshal_dssHdmi.h>
#endif
#if defined (TDA3XX_FAMILY_BUILD)
#include <hal/vpshal_dssSdVenc.h>
#endif
#endif

#ifdef VPS_ISS_ISP_DEF
#include <common/iem_evtmgr.h>
#endif

#ifdef VPS_ISS_BUILD
#include <hal/vpshal_iss.h>
#include <hal/vpshal_issh3a.h>
#include <hal/vpshal_issipipeif.h>
#include <hal/vpshal_issipipe.h>
#include <hal/vpshal_issisif.h>
#include <hal/vpshal_issnsf3.h>
#include <hal/vpshal_issglbce.h>
#include <hal/vpshal_issrsz.h>
#endif
#ifdef VPS_ISS_BUILD
#include <hal/vpshal_iss.h>
#include <hal/vpshal_isscal.h>
#include <hal/vpshal_isslvdsrx.h>
#endif
#ifdef VPS_SIMCOP_BUILD
#include <hal/vpshal_iss.h>
#include <hal/vpshal_isssimcop.h>
#include <hal/vpshal_issldc.h>
#include <hal/vpshal_issvtnf.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief Platform specific data containing base address information of
 *  various HAL modules.
 */
typedef struct
{
#if defined (VPS_VIP_BUILD) || defined (VPS_VPE_BUILD)
    UInt32                     numVpdma;
    /**< Number of VPDMA modules present for a platform. */
    VpsHal_VpdmaInstParams     vpdmaInstPrms[VPSHAL_VPDMA_MAX_INST];
    /**< Corresponding VPDMA instance params. */

    UInt32                     numCsc;
    /**< Number of CSC modules present for a platform. */
    VpsHal_CscInstParams       cscInstPrms[VPSHAL_CSC_MAX_INST];
    /**< Corresponding CSC instance params. */

    UInt32                     numSc;
    /**< Number of SC modules present for a platform. */
    VpsHal_ScInstParams        scInstPrms[VPSHAL_SC_MAX_INST];
    /**< Corresponding SC instance params. */
#endif

#ifdef VPS_VIP_BUILD
    UInt32                     numVipTop;
    /**< Number of VIP Top modules present for a platform. */
    VpsHal_VipTopInstParams    vipTopInstPrms[VPSHAL_VIP_TOP_MAX_INST];
    /**< Corresponding VIP Top instance params. */

    UInt32                     numVipPort;
    /**< Number of VIP Port modules present for a platform. */
    VpsHal_VipPortInstParams   vipPortInstPrms[VPSHAL_VIP_PORT_MAX_INST];
    /**< Corresponding VIP Port instance params. */
#endif

#ifdef VPS_VPE_BUILD
    UInt32                     numVpeTop;
    /**< Number of VPE Top modules present for a platform. */
    VpsHal_VpeTopInstParams    vpeTopInstPrms[VPSHAL_VPE_TOP_MAX_INST];
    /**< Corresponding VPE Top instance params. */

    UInt32                     numChrus;
    /**< Number of CHRUS modules present for a platform. */
    VpsHal_ChrusInstParams     chrusInstPrms[VPSHAL_CHRUS_MAX_INST];
    /**< Corresponding CHRUS instance params. */

    UInt32                     numDei;
    /**< Number of DEI modules present for a platform. */
    VpsHal_DeiInstParams       deiInstPrms[VPSHAL_DEI_MAX_INST];
    /**< Corresponding DEI instance params. */
#endif

#ifdef VPS_DSS_BUILD
    UInt32                     numVidPipe;
    /**< Number of Video+Graphics Pipelines present for a platform. */
    VpsHal_DispcVidInstParams  vidPipeInstPrms[VPSHAL_DSS_DISPC_VID_MAX_INST];
    /**< Corresponding Video/Gfx Pipeline instance params. */

    UInt32                     numWbPipe;
    /**< Number of Write Back Pipelines present for a platform. */
    VpsHal_DispcVidInstParams  wbPipeInstPrms[VPSHAL_DSS_DISPC_WB_MAX_INST];
    /**< Corresponding Writeback Pipeline instance params. */

    UInt32                     numOvlyMgr;
    /**< Number of Overlay Managers present for a platform. */
    VpsHal_DispcOvlyInstParams ovlyMgrInstPrms[VPSHAL_DSS_DISPC_OVLY_MAX_INST];
    /**< Corresponding Overlay Managers instance params. */
#endif /*VPS_DSS_BUILD*/
#if !(defined (VPS_VIP_BUILD)) && !(defined (VPS_VPE_BUILD)) && \
    !(defined (VPS_DSS_BUILD))
    UInt32                     dummy;
#endif
} VpsHal_PlatformData;

#ifdef VPS_ISS_BUILD
typedef struct vpshalissIspPlatformData
{
    isshalCalInstParams_t     *calInstPrms;
    /**< Cal init parameters */
    uint32_t                   numCalInst;
    /**< Nuumber of CAL instances */
    isshalIpipieifInstParams_t ipipeifInstPrms;
    /**< IPIPE Init Params */
    uint32_t                   numIpipeifInst;
    /**< Number of IPIPE instances */
    /**< M2M Core Instance ID */
    isshalipipeInstParams_t    ipipeInstPrms;
    /**< IPIPE Init Params */
    uint32_t                   numIpipeInst;
    /**< Number of IPIPE instances */
    isshalisifInstParams_t     isifInstPrms;
    /**< ISIF Init Params */
    uint32_t                   numIsifInst;
    /**< Number of ISIF instances */
    isshalnsf3InstParams_t     nsf3InstPrms[ISSHAL_NSF3_MAX_INST];
    /**< IPIPE Init Params */
    uint32_t                   numNsf3Inst;
    /**< Number of NSF3 Instance */
    isshalrszInstParams_t      rszInstPrms;
    /**< Resizer instance parameters */
    uint32_t                   numRszInst;
    /**< Number of Resize instance */
    isshalh3aInstParams_t      h3aInstPrms;
    /**< Resizer instance parameters */
    uint32_t                   numH3aInst;
    /**< Number of Resize instance */
    isshalglbceInstParams_t    glbceInstPrms;
    /**< Resizer instance parameters */
    uint32_t                   numGlbceInst;
    /**< Number of Resize instance */
    isshalIssCtrlInitParams_t *issCtrlInitPrms;
    /*< ISS Control Init Params */
} vpshalissIspPlatformData_t;
#endif

#ifdef VPS_ISS_BUILD
typedef struct vpshalissCalPlatformData
{
    uint32_t                   numCalInst;
    /**< Nuumber of CAL instances */
    isshalCalInstParams_t     *calInstPrms;
    /**< Cal init parameters */
    isshalIssCtrlInitParams_t *issCtrlInitPrms;
    /*< ISS Control Init Params */
    uint32_t                   numLvdsInst;
    /**< Number of LVDS Instances */
    isshallvdsrxInstParams_t  *lvdsInstPrms;
    /**< LVDS Instance Params */
} vpshalissCalPlatformData_t;
#endif /* VPS_ISS_BUILD */

#ifdef VPS_SIMCOP_BUILD
typedef struct vpshalissSimcopPlatformData
{
    uint32_t                 numSimcop;
    /**< Number of SIMCOP instances */
    isshalsimcopInstParams_t simcopInitPrms[ISSHAL_SIMCOP_MAX_INST];
    /**< SIMCOP Init params array with numSimcop valid entries*/
    isshalldcInstParams_t    ldcInitPrms[ISSHAL_SIMCOP_MAX_INST];
    /**< LDC Init params array with numSimcop valid entries */
    isshalvtnfInstParams_t   vtnfInitPrms[ISSHAL_SIMCOP_MAX_INST];
    /**< VTNF Init params array with numSimcop valid entries */
} vpshalissSimcopPlatformData_t;
#endif

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief Returns HAL platform data.
 */
VpsHal_PlatformData *VpsHal_getPlatformData(void);

#ifdef VPS_ISS_ISP_DEF
const issemInitParams_t *VpsHal_getCommonPlatformData(void);
#endif

#ifdef VPS_ISS_BUILD
vpshalissIspPlatformData_t *VpsHal_getIspPlatformData(void);
#endif

#ifdef VPS_SIMCOP_BUILD
vpshalissSimcopPlatformData_t *VpsHal_getSimcopPlatformData(void);
#endif

#ifdef VPS_ISS_BUILD
vpshalissCalPlatformData_t *VpsHal_getCalPlatformData(void);
#endif

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef VPSHAL_PLATFORM_H_ */
