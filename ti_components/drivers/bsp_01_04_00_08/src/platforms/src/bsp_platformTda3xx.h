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
 *  \addtogroup BSP_DRV_PLATFORM_TDA3XX_API TDA3XX Platform Specific API
 *  @{
 */

/**
 *  \file bsp_platformTda3xx.h
 *
 *  \brief Interface file to the TDA3XX platform specific functions.
 *
 */

#ifndef BSP_PLATFORM_TDA3XX_H_
#define BSP_PLATFORM_TDA3XX_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

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
Int32 Bsp_platformTda3xxInit(const Bsp_PlatformInitParams *initParams);

/* De-Init platform related sub-systems */
Int32 Bsp_platformTda3xxDeInit(void);

/* Get the CPU revision */
Bsp_PlatformCpuRev Bsp_platformTda3xxGetCpuRev(void);
Bsp_PlatformPackageType Bsp_platformTda3xxGetPackageType(void);

Int32 Bsp_platformTda3xxSetVencClkSrc(const Bsp_PlatformVencSrc *vencPrms);

Int32 Bsp_platformTda3xxSetPllFreq(const Bsp_PlatformSetPllFreq *pllFreq);

Int32 Bsp_platformTda3xxSetDispcFuncClkSrc(UInt32 fClkSrc);

Int32 Bsp_platformTda3xxSimVideoInputSelect(UInt32 vipInstId,
                                            UInt32 fileId,
                                            UInt32 pixelClk);

/*
 * To set the polarity of the LCD with the polarity value.
 * Refer #Fvid2_Polarity for valid values of polarity and
 */
Int32 Bsp_platformTda3xxSetLCDinputPolarity(UInt32 vencId, UInt32 polarity);
Int32 Bsp_platformTda3xxSetLcdSyncPolarity(UInt32 vencId,
                                           UInt32 ctrlEnable,
                                           UInt32 edgePolarity);
Int32 Bsp_platformTda3xxSetVipClkInversion(UInt32 instId, UInt32 invEnable);

Int32 Bsp_platformTda3xxSetPinmuxRegs(UInt32 mode_index,
                                      UInt32 offset,
                                      UInt32 pupd_info);
Int32 Bsp_platformTda3xxLockRegion(Bsp_PlatformMmrRegion region);
Int32 Bsp_platformTda3xxUnLockRegion(Bsp_PlatformMmrRegion region);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef BSP_PLATFORM_TDA3XX_H_ */

/* @} */
