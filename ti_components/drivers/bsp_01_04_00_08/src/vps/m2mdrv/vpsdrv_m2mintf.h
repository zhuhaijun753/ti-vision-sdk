/******************************************************************************
 *                                                                            *
 * Copyright (c) 2014 Texas Instruments Incorporated - http://www.ti.com/     *
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
 *  \file vps_m2mIntf.h
 *
 *  \brief This file implements the memory to memory driver.
 *
 */

#ifndef VPS_DRV_M2M_INTF_H_
#define VPS_DRV_M2M_INTF_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Maxium number of cores supported */
#define VPSMDRV_INTF_MAX_CORE           (2U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  struct VpsMdrv_M2mInitParams
 *  \brief Instance specific parameters used at init call.
 */
typedef struct
{
    UInt32             drvInstId;
    /**< Driver instance ID. */
    UInt32             isMultiChSupported;
    /**< Flag to indicate if this instance supports multiple channels or not */
    UInt32             numCores;
    /**< Number of valid entries in coreInstId and coreOps */
    VpsCore_Inst       coreInstId[VPSMDRV_INTF_MAX_CORE];
    /**< Core instance number/ID. */
    const VpsCore_Ops *coreOps[VPSMDRV_INTF_MAX_CORE];
    /**< VPE, VWB core function pointers. */
} VpsMdrv_M2mIntfInitParams;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  VpsMdrv_intfInit
 *  \brief VPE M2M driver init function.
 *  Initializes driver objects, allocates memory etc.
 *  This function should be called before calling any of FVID2 APIs for this
 *  driver.
 *
 *  \param numInst      Number of instance objects to be initialized.
 *  \param initPrms     Pointer to the init parameter containing
 *                      instance specific information. If the number of
 *                      instance is greater than 1, then this pointer
 *                      should point to an array of init parameter
 *                      structure of size numInst.
 *
 *  \return             Returns BSP_SOK on success else returns error value.
 */
Int32 VpsMdrv_intfInit(UInt32                           numInst,
                       const VpsMdrv_M2mIntfInitParams *initPrms);

/**
 *  VpsMdrv_deInit
 *  \brief VPE driver exit function.
 *  Deallocates memory allocated by init function.
 *
 *  \return             Returns BSP_SOK on success else returns error value.
 */
Int32 VpsMdrv_intfDeInit(void);

#ifdef __cplusplus
}
#endif

#endif /* VPS_DRV_M2M_INTF_H_ */
