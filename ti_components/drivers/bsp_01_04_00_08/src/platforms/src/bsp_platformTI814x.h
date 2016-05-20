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
 *  \ingroup BSP_DRV_PLATFORM_API Platform Specific API
 *  \addtogroup BSP_DRV_PLATFORM_TI814X_API TI814x Platform Specific API
 *  @{
 */

/**
 *  \file bsp_platformTI814x.h
 *
 *  \brief Interface file to the TI814x platform specific functions.
 *
 */

#ifndef BSP_PLATFORM_TI814X_H_
#define BSP_PLATFORM_TI814X_H_

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

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* Init the underlying platform */
Int32 Bsp_platformTI814xInit(const Bsp_PlatformInitParams *initParams);

/* De-Init platform related sub-systems */
Int32 Bsp_platformTI814xDeInit(void);

/* Get the CPU revision */
Bsp_PlatformCpuRev Bsp_platformTI814xGetCpuRev(void);
Bsp_PlatformPackageType Bsp_platformTI814xGetPackageType(void);

Int32 Bsp_platformTI814xSimVideoInputSelect(UInt32 vipInstId,
                                            UInt32 fileId,
                                            UInt32 pixelClk);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef BSP_PLATFORM_TI814X_H_ */

/* @} */
