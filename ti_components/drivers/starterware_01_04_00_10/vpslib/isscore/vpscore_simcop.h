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
 *  \file vpshal_iss.h
 *
 *  \brief Common Header file for all ISS HALs. The ISS block is sub-divded into
 *  3 distinct functional blocks, namely, CAL - Capture, ISP - Image Processing,
 *  SIMCOP - Simple Image Co-Processor.
 *  This file defines common data-structures, enums, control functions, etc for
 *  all ISS HALs
 *
 */

#ifndef VPSCORE_SIMCOP_H_
#define VPSCORE_SIMCOP_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <common/vps_common.h>
#include <common/vpscore.h>
#include <common/iem_evtmgr.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */
/**
 *  \brief Instance identifier
 */
typedef enum vcoreSimcopInst
{
    VPSCORE_ISS_SIMCOP_INST_0           = 0,
    VPSCORE_ISS_SIMCOP_INST_MAX         = 1,
    VPSCORE_ISS_SIMCOP_INST_FORCE_INT   = 0x7FFFFFFF
                                        /**< This will ensure enum is not
                                         * *packed, will always be contained in
                                         *int */
} vcoreSimcopInst_t;

/**
 *  \brief Initialization parameters.
 */
typedef struct vcoreSimcopInitParams
{
    Ptr                         halPlatformData;
    /**< HAL information */
    uint32_t                    instId;
    /**< SIMCOP CORE Instance ID # */
    issemInstId_t               irqNum;
    /**< IRQ Number for the fraem completion callback */
    issemEventGroup_t           eventGroup;
    /**< Event type */
    uint32_t                    eventNum;
    /**< Event Number */
    uint32_t                    isSimcopDmaCfgValid;
    /**< If FALSE, driver will compute simcopDmaCfg
     *   If TRUE, driver will use contents of simcopDmaCfg */
    vpsisssimcopDmaCtrlParams_t simcopDmaCfg;
    /**< Instance specific DMA control params, if not supplied, defaults
     *      would be applied. */
    Ptr                         arg;
    /**< UnUsed reserved for future */
}vcoreSimcopInitParams_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/**
 *  VpsCore_simcopGetCoreOps
 *  \brief Returns the core ops supported
 *
 *  \param none      None
 *
 *  \return          Returns pointer to a #VpsCore_Ops instance
 *
 */
const VpsCore_Ops *VpsCore_simcopGetCoreOps(void);

/**
 *  VpsCore_simcopInit
 *  \brief SIMCOP core init function.
 *  Initializes core objects for all instances of SIMCOP.
 *  This function should be called before calling any of SIMCOP core API's.
 *  TBD: Fix Prototype
 *
 *  \param numInst      [IN] Number of SIMCOP instances to initialize
 *  \param initPrms     [IN] Array of type #vcoreSimcopInitParams_t and size
 *                      numInst containing init parameters with instance
 *                      numInst containing init parameters
 *
 *  \return             Returns BSP_SOK on success else returns error value.
 *
 */
int32_t VpsCore_simcopInit(uint32_t                       numInst,
                           const vcoreSimcopInitParams_t *initPrms,
                           Ptr                            arg);

/**
 *  VpsCore_simcopDeInit
 *  \brief This function closes all HAL handles & power down SIMCOP
 *
 *  \param numInst      [IN] Number of SIMCOP instances to initialize
 *
 *  \return             Returns BSP_SOK on success else returns error value.
 *
 */
int32_t VpsCore_simcopDeInit(uint32_t numInst);

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef VPSCORE_SIMCOP_H_ */
