/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_alpha_blend_yuv422i_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating YUV422 Interleaved
 *              Alpha Blending into BAM
 */

#include <stdio.h>
#include <stdlib.h>

#include "evealgframework.h"
#include "bam_alpha_blend_yuv422i_int.h"
#include "vcop_alpha_blend_yuv422i_kernel.h" /* compiler should take care of include path */

/* Function Prototypes */
static BAM_Status BAM_Alpha_Blend_YUV422i_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks);

static BAM_Status BAM_Alpha_Blend_YUV422i_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks)
{
#if (VCOP_HOST_EMULATION)
    const BAM_Alpha_Blend_YUV422i_Args *args = (const BAM_Alpha_Blend_YUV422i_Args *)kernelArgs;
#else
    /* Typecasting by (const BAM_Alpha_Blend_YUV422i_Args *) will lead to MISRA C 11.5. */
    const BAM_Alpha_Blend_YUV422i_Args *args = kernelArgs;
#endif

#if (!VCOP_HOST_EMULATION)
    internalBlock[PARAMS_IDX].size = 2U*vcop_alpha_blend_yuv422i_param_count();
#else
    internalBlock[PARAMS_IDX].size = 4U;
#endif

    outBlock[ALPHA_BLEND_YUV422I_OUT_IDX].size = args->out_stride*args->height;

    return BAM_S_SUCCESS;
}

BAM_KernelInfo gBAM_TI_alphaBlendYUV422iKernel =
{
    0,                                      /* kernelId */
    sizeof(BAM_Alpha_Blend_YUV422i_Context),
    sizeof(BAM_Alpha_Blend_YUV422i_Args),
    BAM_EVE,                                /* coreType */
    BAM_NODE_COMPUTE,                       /* nodeType */
    ALPHA_BLEND_YUV422I_NUM_IN_BLOCKS,                          /* 3 */
    ALPHA_BLEND_YUV422I_NUM_OUT_BLOCKS,                         /* 1 */
    ALPHA_BLEND_YUV422I_NUM_INTERNAL_BLOCKS                     /* 1 */
};

BAM_KernelHelperFuncDef gBAM_TI_alphaBlendYUV422iHelperFunc =
{ &BAM_Alpha_Blend_YUV422i_getMemRecFunc, NULL};

