/* ======================================================================
 *   Copyright (C) 2013 Texas Instruments Incorporated
 *
 *   All rights reserved. Property of Texas Instruments Incorporated.
 *   Restricted rights to use, duplicate or disclose this code are
 *   granted through contract.
 *
 *   The program may not be used without the written permission
 *   of Texas Instruments Incorporated or against the terms and conditions
 *   stipulated in the agreement under which this program has been
 *   supplied.
 * ==================================================================== */
/**
 *  \defgroup BSP_DRV_VIP_STARTERWARE_API VIP Starterware Driver API
 *
 *  @{
 */

/**
 *  \file vpsdrv_captureApi.c
 *
 *  \brief File containing the VPS capture driver APIs.
 *
 */
#ifndef VPS_DCTRLDRV_H_
#define VPS_DCTRLDRV_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <dispcore/vpscore_dctrl.h>
#include <vps/vps_displayCtrlDataTypes.h>

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C"
{
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Forward declaration for instance object. */
typedef struct VpsDrv_DctrlInstObj_t VpsDrv_DctrlInstObj;

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  struct VpsDrv_DctrlInitParams
 *  \brief Instance specific parameters used at init call.
 */
typedef struct
{
    const VpsCore_Ops *coreOps;
    /**< Core function pointers. */
    VpsCore_Inst       coreInstObj;
    /**< Core instance object used in core open. */
} VpsDrv_DctrlInitParams;

/**
 *  struct VpsDrv_CaptInstObj
 *  \brief Instance specific parameters used at init call.
 */
struct VpsDrv_DctrlInstObj_t
{
    UInt32             drvInstId;
    /**< Instance ID. */
    VpsCore_Inst       coreInstObj;
    /**< Core instance object used in core open. */
    const VpsCore_Ops *coreOps;
    /**< Core function pointers. */
    VpsCore_Handle     coreHandle;
    /**< Core handle. */
};

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* ========================================================================== */
/*                          Function Declarations                             */
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

Int32 VpsDrv_dctrlInit(const VpsDrv_DctrlInitParams *initPrms);

/**
 *  VpsDrv_dctrlDeInit
 *  \brief VPS DSS capture driver de-initialization function.
 *
 *  \return                   success    0
 *                            failure    error value
 *
 */
Int32 VpsDrv_dctrlDeInit(void);

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
VpsDrv_DctrlInstObj *VpsDrv_dctrlOpen(void);

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
Int32 VpsDrv_dctrlClose(VpsDrv_DctrlInstObj *pObj);

/**
 *  vpsDrv_DctrlSetConfig
 *  \brief Gets the current display status information.
 *
 *  NOTE: This can't be be called from ISR context.
 *
 *  Returns BSP_SOK on success else returns appropriate error code.
 */
Int32 vpsDrv_DctrlSetConfig(VpsDrv_DctrlInstObj *pObj,
                            Vps_DctrlConfig     *dctrlCfg);

/**
 *  vpsDrv_DctrlCleatConfig
 *  \brief Gets the current display status information.
 *
 *  NOTE: This can't be be called from ISR context.
 *
 *  Returns BSP_SOK on success else returns appropriate error code.
 */
Int32 vpsDrv_DctrlClearConfig(VpsDrv_DctrlInstObj *pObj,
                              Vps_DctrlConfig     *dctrlCfg);

/**
 *  vpsDrv_DctrlSetVencOutput
 *  \brief Gets the current display status information.
 *
 *  NOTE: This can't be be called from ISR context.
 *
 *  Returns FVID2_SOK on success else returns appropriate error code.
 */
Int32 vpsDrv_DctrlSetVencOutput(VpsDrv_DctrlInstObj *pObj,
                                Vps_DctrlOutputInfo *dctrl_info);

/**
 *  vpsDrv_DctrlGetVencOutput
 *  \brief Gets the current display status information.
 *
 *  NOTE: This can't be be called from ISR context.
 *
 *  Returns FVID2_SOK on success else returns appropriate error code.
 */
Int32 vpsDrv_DctrlGetVencOutput(VpsDrv_DctrlInstObj *pObj,
                                Vps_DctrlOutputInfo *dctrl_info);

/**
 *  vpsDrv_DctrlSetVencDivisor
 *  \brief Sets the Venc divisor values to get desired pixel clock.
 *
 *  NOTE: This can't be be called from ISR context.
 *
 *  Returns BSP_SOK on success else returns appropriate error code.
 */
Int32 vpsDrv_DctrlSetVencDivisor(VpsDrv_DctrlInstObj      *pObj,
                                 Vps_DctrlVencDivisorInfo *vencDivisor);

/**
 *  vpsDrv_DctrlSetOvlyParms
 *  \brief Gets the current display status information.
 *
 *  NOTE: This can't be be called from ISR context.
 *
 *  Returns BSP_SOK on success else returns appropriate error code.
 */
Int32 vpsDrv_DctrlSetOvlyParams(VpsDrv_DctrlInstObj         *pObj,
                                Vps_DssDispcOvlyPanelConfig *panelconfig);

/**
 *  vpsDrv_DctrlSetPipelineParms
 *  \brief Gets the current display status information.
 *
 *  NOTE: This can't be be called from ISR context.
 *
 *  Returns BSP_SOK on success else returns appropriate error code.
 */
Int32 vpsDrv_DctrlSetPipelineParams(VpsDrv_DctrlInstObj        *pObj,
                                    Vps_DssDispcOvlyPipeConfig *ovlpipeconfig);

#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif

#endif /* VPS_DCTRLDRV_H_ */
