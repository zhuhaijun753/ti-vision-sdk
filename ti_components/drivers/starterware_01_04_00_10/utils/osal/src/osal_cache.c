/* =================================================================
 *   Copyright (C) 2015 Texas Instruments Incorporated
 *
 *   All rights reserved. Property of Texas Instruments Incorporated.
 *   Restricted rights to use, duplicate or disclose this code are
 *   granted through contract.
 *
 *   The program may not be used without the written permission
 *   of Texas Instruments Incorporated or against the terms and
 *    conditionsstipulated in the agreement under which this program
 *     has been supplied.
 * =================================================================*/

/**
 *  \file osal_cache.c
 *
 *  \brief OSAL Cache API
 *  This file implements the OSAL cache functionality.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <common/stw_dataTypes.h>
#include <osal/bsp_osal.h>

#if defined (BUILD_A15)
#include "cache_a15.h"
#endif
#if defined (BUILD_M4)
#include "soc.h"
#include "unicache.h"
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Check macros values. */
#if defined (BUILD_A15)
#if ((BSP_OSAL_CT_L1P != CACHE_A15_TYPE_L1I) ||                             \
     (BSP_OSAL_CT_L1D != CACHE_A15_TYPE_L1D) ||                             \
     (BSP_OSAL_CT_L1 != CACHE_A15_TYPE_L1) ||                               \
     (BSP_OSAL_CT_L2P != CACHE_A15_TYPE_L2I) ||                             \
     (BSP_OSAL_CT_L2D != CACHE_A15_TYPE_L2D) ||                             \
     (BSP_OSAL_CT_L2 != CACHE_A15_TYPE_L2) ||                               \
     (BSP_OSAL_CT_ALLP != CACHE_A15_TYPE_ALLI) ||                           \
     (BSP_OSAL_CT_ALLD != CACHE_A15_TYPE_ALLD) ||                           \
     (BSP_OSAL_CT_ALL != CACHE_A15_TYPE_ALL))
    #error "OSAL and A15 Cache type enums are not same!!"
#endif
#endif

#if defined (BUILD_M4)
#if (BSP_OSAL_WAIT_FOREVER != UNICACHE_WAIT_INFINITE)
    #error "OSAL and UNICACHE wait forever macros are not same!!"
#endif
#if (BSP_OSAL_NO_WAIT != UNICACHE_WAIT_NOWAIT)
    #error "OSAL and UNICACHE no-wait macros are not same!!"
#endif
#endif

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void BspOsal_cacheDisable(UInt32 type)
{
#if defined (BUILD_A15)
    CACHEA15Disable(type);
#endif

#if defined (BUILD_M4)
    UNICACHEDisable(SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE);
#endif

    return;
}

void BspOsal_cacheEnable(UInt32 type)
{
#if defined (BUILD_A15)
    CACHEA15Enable(type);
#endif

#if defined (BUILD_M4)
    UNICACHEEnable(SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE);
#endif

    return;
}

void BspOsal_cacheInv(void *blockPtr,
                      UInt32 byteCnt,
                      UInt32 type,
                      UInt32 timeOut)
{
#if defined (BUILD_A15)
    CACHEA15Invalidate(type, (uint32_t) blockPtr, byteCnt);
#endif

#if defined (BUILD_M4)
    UNICACHEInvalidate(
        SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE,
        (uint32_t) blockPtr,
        byteCnt,
        timeOut);
#endif

    return;
}

void BspOsal_cacheWb(void *blockPtr,
                     UInt32 byteCnt,
                     UInt32 type,
                     UInt32 timeOut)
{
#if defined (BUILD_A15)
    CACHEA15WriteBack((uint32_t) blockPtr, byteCnt);
#endif

#if defined (BUILD_M4)
    UNICACHEWriteBack(
        SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE,
        (uint32_t) blockPtr,
        byteCnt,
        timeOut);
#endif

    return;
}

void BspOsal_cacheWbAll(void)
{
#if defined (BUILD_A15)
    CACHEA15WriteBackAll();
#endif

#if defined (BUILD_M4)
    UNICACHEWriteBackAll(
        SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE,
        UNICACHE_WAIT_INFINITE);
#endif

    return;
}

void BspOsal_cacheWbInv(void *blockPtr,
                        UInt32 byteCnt,
                        UInt32 type,
                        UInt32 timeOut)
{
#if defined (BUILD_A15)
    CACHEA15WriteBackAndInvalidate((uint32_t) blockPtr, byteCnt);
#endif

#if defined (BUILD_M4)
    UNICACHEWriteBackAndInvalidate(
        SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE,
        (uint32_t) blockPtr,
        byteCnt,
        timeOut);
#endif

    return;
}

void BspOsal_cacheWbInvAll(void)
{
#if defined (BUILD_A15)
    CACHEA15WriteBackAndInvalidateAll();
#endif

#if defined (BUILD_M4)
    UNICACHEWriteBackAndInvalidateAll(
        SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE,
        UNICACHE_WAIT_INFINITE);
#endif

    return;
}
