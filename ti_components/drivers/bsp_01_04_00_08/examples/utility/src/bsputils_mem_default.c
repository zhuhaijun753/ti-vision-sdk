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

#include <xdc/std.h>
#include <common/bsp_types.h>
#include <vps/vps.h>
#include <platforms/bsp_platform.h>
#include <bsputils_mem.h>

/** \brief Maximum frame buffer memory pool size */
#if defined (TDA2XX_FAMILY_BUILD)
#define BSPUTILS_MEM_FRAME_HEAP_SIZE    (246U * MB)
#endif

#if defined (TDA3XX_FAMILY_BUILD)
    #ifdef PLATFORM_ZEBU
#define BSPUTILS_MEM_FRAME_HEAP_SIZE    (64U * MB)
    #else
#define BSPUTILS_MEM_FRAME_HEAP_SIZE    (240U * MB)
    #endif
#define BSPUTILS_MEM_FRAME_HEAP_SIZE_12x12  (48U * MB)
#endif

#if defined (OMAP5430_BUILD)
#define BSPUTILS_MEM_FRAME_HEAP_SIZE    (246U * MB)
#endif

#if defined (TI814X_BUILD) || defined (TI8149_BUILD)
#define BSPUTILS_MEM_FRAME_HEAP_SIZE    (123U * MB)
#endif

#if defined (TI811X_BUILD)
#define BSPUTILS_MEM_FRAME_HEAP_SIZE    (57U * MB)
#endif

#ifdef CUSTOM_MEM_FRAME_HEAP_SIZE
#undef BSPUTILS_MEM_FRAME_HEAP_SIZE
#define BSPUTILS_MEM_FRAME_HEAP_SIZE    (CUSTOM_MEM_FRAME_HEAP_SIZE * MB)
#endif

/* Memory pool */
/* Align descriptor memory with that of VPDMA requirement. */
/* Place the frame heap in frame buffer section. */
#ifdef __cplusplus
#pragma DATA_ALIGN(VPS_BUFFER_ALIGNMENT_RECOMMENDED)
#pragma DATA_SECTION(".bss:frameBuffer");
#else
#pragma DATA_ALIGN(gBspUtils_heapMemFrame, VPS_BUFFER_ALIGNMENT_RECOMMENDED)
#pragma DATA_SECTION(gBspUtils_heapMemFrame,".bss:frameBuffer");
#endif  /* #ifdef __cplusplus */
UInt32 gBspUtils_heapMemFrame[(UInt32) BSPUTILS_MEM_FRAME_HEAP_SIZE /
                              (UInt32) sizeof (UInt32)];

Int32 BspUtils_memInit(void)
{
    UInt32 memSize;

    memSize = sizeof (gBspUtils_heapMemFrame);
    /* In case of TDA3xx 12x12 package, only 64MB DDR is present */
#if defined (TDA3XX_FAMILY_BUILD)
    if (Bsp_platformGetPackageType() == BSP_PLATFORM_PACKAGE_TYPE_12x12)
    {
        /* Out of 64MB, 16MB is used for code/data/descriptor */
        memSize = BSPUTILS_MEM_FRAME_HEAP_SIZE_12x12;
    }
#endif

    BspUtils_memInit_internal(gBspUtils_heapMemFrame, memSize);
    return 0;
}

