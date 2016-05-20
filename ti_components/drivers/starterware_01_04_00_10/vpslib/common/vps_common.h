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
 *  \file vps_common.h
 *
 *  \brief BSP header file containing commonly used functions.
 *
 */

#ifndef VPS_COMMON_H_
#define VPS_COMMON_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <common/vps_evtMgr.h>
#include <common/vps_resrcMgr.h>
#include <common/vpscore.h>
#include <hal/vpshal.h>
#include <hal/vpshal_platform.h>
#if defined TDA3XX_FAMILY_BUILD
#if defined VPS_ISS_ISP_DEF
#include <common/iem_evtmgr.h>
#endif
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
 *  \brief VPS Lib initialization parameters.
 */
typedef struct
{
    UInt32 isAddrTransReq;
    /**< Set this flag to TRUE if the driver has to perform address translation
     *   of the descriptor memory before submitting the descriptor to the
     *   hardware. This is used when the physical memory of the descriptor
     *   is mapped to a different virtual memory.
     *
     *   When address translation is enabled, the dirver performs the following
     *   operations to convert the virtual address to physical address and
     *   vice versa.
     *
     *   physAddr = (virtAddr - virtBaseAddr) + physBaseAddr;
     *   virtAddr = (physAddr - physBaseAddr) + virtBaseAddr;
     *
     *   Important: The descriptor memory should in a physically continuous
     *   memory.
     *
     *   Note: The buffer address will not be translated using the above
     *   translation and hence the application should provide the physical
     *   address to be programmed to the hardware.
     *
     *   Note: VPSHAL_VPDMA_ENABLE_ADDR_TRANS macro should be defined in
     *   vpshal_vpdma.c file to enable address translation at compile time.
     *   By default this is defined. But alternatively application could disable
     *   this conversion at compile time by removing this macro definition
     *   to improve performance. */
    UInt32 virtBaseAddr;
    /**< Virtual memory base address. */
    UInt32 physBaseAddr;
    /**< Physical memory base address. */
    UInt32 isCacheOpsReq;
    /**< This will enable cache flush and invalidate operations on the
     *   descriptor memory in case the descriptor memory is cache region.
     *
     *   Note: This is not supported in the current implementation and is meant
     *   for future use. */
    UInt32 isCacheFlushReq;
    /**< This will enable cache flush operations on the
     *   descriptor memory in case the descriptor memory is cache region.
     *   In case of write-through cache mode, this flag could be set to FALSE
     *   to save cycles as flush operation is not required in write-through
     *   mode.
     *   This parameter is valid/used only if isCacheOpsReq is TRUE.
     *
     *   Note: This is not supported in the current implementation and is meant
     *   for future use. */
} VpsLib_InitParams;

/**
 *  \brief Platform specific data containing base address information of
 *  various modules.
 */
typedef struct
{
    const VpsHal_PlatformData *hal;
    /**< HAL related platform data. */

    const Ptr                 *ispHal;
    /**< ISP Hal Information */
    const Ptr                 *simcopHal;
    /**< Simcop Hal Information */

    const Ptr                 *issCommonPrms;
    /**< Common Parameters */

    /*
     * Misc platform data.
     */
    UInt32                     numEvtMgr;
    /**< Number of event manager present for a platform. */
    Vem_InstParams             evtMgrInstPrms[VEM_MAX_INST];
    /**< Corresponding VEM instance params. */

    UInt32                     numResrcMgr;
    /**< Number of resource manager present for a platform. */
    Vrm_InstParams             resrcMgrInstPrms[VRM_MAX_INST];
    /**< Corresponding VRM instance params. */

    const Ptr                 *calHal;
    /**< CAL Hal information */
} VpsLib_PlatformData;

/**
 *  struct VpsCore_SubFrameParams
 *  \brief Configuration for sub-frame level processing at create time used
 */
typedef struct
{
    UInt32 subFrameEnable;
    /**< TRUE : SubFrame level capture/processing is enabled.
     *   FALSE: SubFrame level capture/processing is disabled.
     *   Must be FALSE for multi-channel capture mode. */
    UInt32 numLinesPerSubFrame;
    /**< Number of lines per subframes.
     *
     *   MUST be multiple of the output size.
     *   Not valid, ignored for ancillary data capture.
     *
     *   In case of capture,
     *   SubFrame callback gets called after every numLinesPerSubFrame
     *   for every output stream, except ancillary data stream.
     *
     *   Ignored when subFrameEnable = FALSE */
    UInt32 interruptMode;
    /**< Client Interrupt mode as per #Vps_VpdmaClientIntrMode
     *   Ignored when subFrameEnable = FALSE */
} VpsCore_SubFrameParams;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief VPS Lib init function.
 *
 *  Initializes the VPS library.
 *  This function should be called before calling any of driver API's and
 *  should be called only once.
 *
 *  \param initPrms     [IN] VPS Initialization parameters.
 *                           If NULL is passed, the default parameters will be
 *                           assumed - address translation disabled.
 *
 *  \return BSP_SOK on success else appropiate FVID2 error code on failure.
 */
Int32 VpsLib_init(const VpsLib_InitParams *initPrms);

/**
 *  \brief VPS Lib deinit function.
 *
 *  Uninitializes the VPS library and should be called during
 *  system shutdown. Should not be called if Vps_init() is not called.
 *
 *  \param args         [IN] Not used currently. Set to NULL.
 *
 *  \return BSP_SOK on success, else appropriate FVID2 error code on failure.
 */
Int32 VpsLib_deInit(Ptr args);

/**
 *  \brief Returns VPS Lib platform data.
 */
const VpsLib_PlatformData *VpsLib_getPlatformData(void);

#ifdef VPS_VIP_BUILD
/**
 *  \brief Returns VPS Lib VIP core instance object pointer.
 *
 *  \param vipInstId    [IN]  VIP Instance number
 */
VpsCore_Inst VpsLib_getVipCoreInstObj(UInt32 vipInstId);
#endif

#ifdef VPS_DSS_BUILD
/**
 *  \brief Returns VPS Lib DSS core instance object pointer.
 */
VpsCore_Inst VpsLib_getDssCoreInstObj(void);

/**
 *  \brief Returns VPS Lib DSS WB core instance object pointer.
 */
VpsCore_Inst VpsLib_getDssWbCoreInstObj(void);

/**
 *  \brief Returns VPS Lib Dctrl core instance object pointer.
 */
VpsCore_Inst VpsLib_getDctrlCoreInstObj(void);

/**
 *  \brief Returns VPS Lib DSS overlay Hal handle.
 *
 *  \param vpdmaInstId  [IN]  DSS overlay instance number
 */
VpsHal_Handle VpsLib_getDssOvlyHalHandle(UInt32 ovlyInstId);
#endif

#if defined (VPS_VIP_BUILD) || defined (VPS_VPE_BUILD)
/**
 *  \brief Returns VPS Lib VPDMA Hal handle.
 *
 *  \param vpdmaInstId  [IN]  VPDMA instance number
 */
VpsHal_Handle VpsLib_getVpdmaHalHandle(UInt32 vpdmaInstId);
#endif

/**
 *  \brief VpsLib_InitParams structure init function.
 *
 *  \param initPrms     [IN] Pointer to #VpsLib_InitParams structure.
 *
 */
static inline void VpsLibInitParams_init(VpsLib_InitParams *initPrms);

Bool VpsLib_platformIsTda2xxFamilyBuild(void);
Bool VpsLib_platformIsOmap5FamilyBuild(void);
Bool VpsLib_platformIsTI814xFamilyBuild(void);
Bool VpsLib_platformIsTda3xxFamilyBuild(void);

int32_t VpsLib_issCommonInit(const VpsLib_PlatformData *platData);

int32_t VpsLib_issCommonDeInit(Ptr arg);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

static inline void VpsLibInitParams_init(VpsLib_InitParams *initPrms)
{
    if (NULL != initPrms)
    {
        initPrms->isAddrTransReq  = (UInt32) FALSE;
        initPrms->virtBaseAddr    = 0U;
        initPrms->physBaseAddr    = 0U;
        initPrms->isCacheOpsReq   = (UInt32) FALSE;
        initPrms->isCacheFlushReq = (UInt32) FALSE;
    }

    return;
}

#ifdef __cplusplus
}
#endif

#endif /* #ifndef VPS_COMMON_H_ */
