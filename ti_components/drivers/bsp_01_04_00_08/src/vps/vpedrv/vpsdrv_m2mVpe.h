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
 *  \file vpsdrv_m2mVpe.h
 *
 *  \brief This file implements the memory to memory driver for the
 *  VPE with outputs through DEI Write back paths.
 *
 */

#ifndef VPSDRV_M2MVPE_H_
#define VPSDRV_M2MVPE_H_

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

/** \brief Core index for VPE core. */
#define VPSMDRV_VPE_VPE_CORE_IDX        (0U)
/** \brief Core index for VPE writeback core. */
#define VPSMDRV_VPE_VWB_CORE_IDX        (1U)
/* Note: If a new core is to be added into this that has a scaler in it, refer
 * to vps_m2mVpe.h:
 * VPS_M2M_VPE_SCALER_ID_SC0.
 * The new scalerId corresponding to this core needs to be added at the end
 * and the new core with that scaler ID must be added at the end here. This
 * same ordering is assumed within the code.
 */
/** \brief Maximum number of core required by driver. */
#define VPSMDRV_VPE_MAX_CORE            (2U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  struct VpsMdrv_VpeInitParams
 *  \brief Instance specific parameters used at init call.
 */
typedef struct
{
    UInt32              drvInstId;
    /**< Driver instance ID. */
    UInt32              coreInstId[VPSMDRV_VPE_MAX_CORE];
    /**< VPE, VWB core instance number/ID. */
    const Vcore_M2mOps *coreOps[VPSMDRV_VPE_MAX_CORE];
    /**< VPE, VWB core function pointers. */
} VpsMdrv_VpeInitParams;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  VpsMdrv_vpeInit
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
Int32 VpsMdrv_vpeInit(UInt32                       numInst,
                      const VpsMdrv_VpeInitParams *initPrms);

/**
 *  VpsMdrv_vpeDeInit
 *  \brief VPE driver exit function.
 *  Deallocates memory allocated by init function.
 *
 *  \return             Returns BSP_SOK on success else returns error value.
 */
Int32 VpsMdrv_vpeDeInit(void);

/**
 *  VpsMdrv_vpeSetLazyLoadParams
 *  \brief VPE driver set lazy load parameter for a given instance and scaler.
 *
 *  \param lazyPrms     Pointer to lazy loading parameter. This can't be NULL.
 *
 *  \return             Returns BSP_SOK on success else returns error value.
 */
Int32 VpsMdrv_vpeSetLazyLoadParams(const Vps_ScLazyLoadingParams *lazyPrms);

#ifdef __cplusplus
}
#endif

#endif /*  VPSDRV_M2MVPE_H_ */
