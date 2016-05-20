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
 *  \file stw_platformTda2xx.h
 *
 *  \brief Interface file to the TDA2XX platform specific functions.
 *
 */

#ifndef STW_PLATFORM_TDA2XX_H_
#define STW_PLATFORM_TDA2XX_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <soc.h>
#include <hw/hw_types.h>
#include <hw/hw_ctrl_core.h>
#include <hw_ctrl_wkup.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* Get the CPU revision */
platformCpuRev_t PLATFORMTda2xxGetCpuRev(void);

uint32_t PLATFORMTda2xxGetFtRev(void);

int32_t PLATFORMTda2xxSetPinmuxRegs(uint32_t baseAddrOffset, uint32_t ioPinCfg);
int32_t PLATFORMTda2xxUnLockRegion(platformMmrRegion_t region);
int32_t PLATFORMTda2xxLockRegion(platformMmrRegion_t region);
int32_t PLATFORMTda2xxInit(const platformInitParams_t *initParams);
int32_t PLATFORMTda2xxDeInit(void);
int32_t PLATFORMTda2xxSetPinMux(const platformInitParams_t *initParams);
int32_t PLATFORMTda2xxSetIrqXBar(const platformInitParams_t *initParams);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef STW_PLATFORM_TDA2XX_H_ */

/* @} */
