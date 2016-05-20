/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_yuv_420nv12_to_422uyvy_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating YUV420 NV12
 *              to YUV422 UYVY format conversion into BAM
 */

#include <stdio.h>
#include <stdlib.h>

#include "evealgframework.h"
#include "bam_yuv_420nv12_to_422uyvy_int.h"
#include "vcop_yuv_420nv12_to_422uyvy_kernel.h" /* compiler should take care of include path */

/* Function Prototypes */
static BAM_Status BAM_Yuv_420nv12_to_422uyvy_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks);

static BAM_Status BAM_Yuv_420nv12_to_422uyvy_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks)
{
#if (VCOP_HOST_EMULATION)
    const BAM_Yuv_420nv12_to_422uyvy_Args *args = (const BAM_Yuv_420nv12_to_422uyvy_Args *)kernelArgs;
#else
    /* Typecasting by (const BAM_Yuv_420nv12_to_422uyvy_Args *) will lead to MISRA C 11.5. */
    const BAM_Yuv_420nv12_to_422uyvy_Args *args = kernelArgs;
#endif


#if (!VCOP_HOST_EMULATION)
    internalBlock[PARAMS_IDX].size = 2U*vcop_yuv_420nv12_to_422uyvy_param_count();
#else
    internalBlock[PARAMS_IDX].size = 4U;
#endif

    outBlock[YUV_420NV12_TO_422UYVY_OUT_IDX].size = args->out_stride*args->height;

    return BAM_S_SUCCESS;
}

BAM_KernelInfo gBAM_TI_yuv420nv12_to_422uyvyKernel =
{
    0,                                      /* kernelId */
    sizeof(BAM_Yuv_420nv12_to_422uyvy_Context),
    sizeof(BAM_Yuv_420nv12_to_422uyvy_Args),
    BAM_EVE,                                /* coreType */
    BAM_NODE_COMPUTE,                       /* nodeType */
    YUV_420NV12_TO_422UYVY_NUM_IN_BLOCKS,                          /* 1 */
    YUV_420NV12_TO_422UYVY_NUM_OUT_BLOCKS,                         /* 1 */
    YUV_420NV12_TO_422UYVY_NUM_INTERNAL_BLOCKS                     /* 1 */
};

BAM_KernelHelperFuncDef gBAM_TI_yuv420nv12_to_422uyvyHelperFunc =
{ &BAM_Yuv_420nv12_to_422uyvy_getMemRecFunc, NULL};
