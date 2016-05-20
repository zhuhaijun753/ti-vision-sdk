/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_multiblock_gradient_xy_helper_funcs.c
 *
 *  @brief      This file defines interfaces for integrating multi block gradient
 *              XY compute function into BAM
 */

#include <stdio.h>
#include <stdlib.h>

#include "evealgframework.h"
#include "bam_multiblock_gradient_xy_int.h"
#include "vcop_multiblock_gradient_xy_kernel.h" /* compiler should take care of include path */

/* Function Prototypes */
static BAM_Status BAM_Multiblock_Gradient_XY_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks);

static BAM_Status BAM_Multiblock_Gradient_XY_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks)
{
    const BAM_Multiblock_Gradient_XY_Args *args = (const BAM_Multiblock_Gradient_XY_Args *) kernelArgs;
    internalBlock[PARAMS_IDX].size = 2U*vcop_multiblock_gradient_xy_param_count();
    /*Ideal Output Block Memory Requirement:
    args.numBlocks * 4 * (args.blkWidth)*(args.blkHeight) + args.numBlocks * 4 * (8 - ((args.blkWidth)%8))
    Worst Case Memory Requirement: Since VCOP processes with SIMD WIDTH of 8, the worst case padding required is 7
    additional pixels to process one extra valid pixel
    args.numBlocks * 4 * (args.blkWidth)*(args.blkHeight) + args.numBlocks * 4 * 7
    Factor of '4' is used to accommodate 2 bytes of GRADX and 2 bytes of GRADY which are stored in interleaved format
    for every output pixel*/
    outBlock[OUT_IDX].size = (args->numBlocks * 4 * (args->blkWidth)*(args->blkHeight)) + (args->numBlocks * 4 * 7);
    outBlock[OUT_IDX].attrs.memAttrs= BAM_MEMATTRS_SCRATCH;
    outBlock[OUT_IDX].space = BAM_MEMSPACE_IBUFLA;    

    return BAM_S_SUCCESS;
}

BAM_KernelInfo gBAM_TI_multiblockGradientXYKernel =
{
    0,                                      /* kernelId */
    sizeof(BAM_Multiblock_Gradient_XY_Context),
    sizeof(BAM_Multiblock_Gradient_XY_Args),
    BAM_EVE,                                /* coreType */
    BAM_NODE_COMPUTE,                       /* nodeType */
    NUM_IN_BLOCKS,                          /* 1 */
    NUM_OUT_BLOCKS,                         /* 4 */
    NUM_INTERNAL_BLOCKS                     /* 3 */
};

BAM_KernelHelperFuncDef gBAM_TI_multiblockGradientXYHelperFunc =
{ &BAM_Multiblock_Gradient_XY_getMemRecFunc, NULL};

