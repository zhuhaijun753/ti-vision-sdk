/* ======================================================================
 *   Copyright (C) 2014 Texas Instruments Incorporated
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
 *  \file stw_platformTda3xx.h
 *
 *  \brief Interface file to the TDA3XX platform specific functions.
 *
 */

#ifndef STW_PLATFORM_TDA3XX_H_
#define STW_PLATFORM_TDA3XX_H_

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

/* Get the CPU revision */
platformCpuRev_t PLATFORMTda3xxGetCpuRev(void);
int32_t PLATFORMTda3xxSetPinmuxRegs(uint32_t baseAddrOffset, uint32_t ioPinCfg);
int32_t PLATFORMTda3xxUnLockRegion(platformMmrRegion_t region);
int32_t PLATFORMTda3xxLockRegion(platformMmrRegion_t region);
int32_t PLATFORMTda3xxInit(const platformInitParams_t *initParams);
int32_t PLATFORMTda3xxDeInit(void);
int32_t PLATFORMTda3xxSetPinMux(const platformInitParams_t *initParams);
int32_t PLATFORMTda3xxSetIrqXBar(const platformInitParams_t *initParams);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef STW_PLATFORM_TDA3XX_H_ */

/* @} */
