/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_sobel_xy_helper_funcs.c
 *
 *  @brief      This file defines interfaces for integrating Sobel XY
 *              kernel into BAM.
 */

#include <stdio.h>
#include <stdlib.h>

#include "evealgframework.h"
#include "bam_sobel_xy_int.h"
#include "vcop_sobel_xy_kernel.h" /* compiler should take care of include path */

static BAM_Status BAM_SobelXy_getMemRecFunc( const void *kernelArgs,
                            BAM_MemRec internalBlock[],
                            BAM_MemRec outBlock[],
                            uint8_t *numInternalBlocks,
                            uint8_t *numOutBlocks);

static BAM_Status BAM_SobelXy_getMemRecFunc( const void *kernelArgs,
                            BAM_MemRec internalBlock[],
                            BAM_MemRec outBlock[],
                            uint8_t *numInternalBlocks,
                            uint8_t *numOutBlocks)

{
    const BAM_SobelXy_Args *args = (const BAM_SobelXy_Args *) kernelArgs;

    uint16_t blockHeight;
    uint16_t computeWidth;
    uint16_t computeHeight;

    computeWidth  = (uint16_t)ALIGN_2SIMD(((uint32_t)args->maxBlockWidth));
    computeHeight = args->maxBlockHeight;

    blockHeight = computeHeight + 2U;

#if !VCOP_HOST_EMULATION
    internalBlock[SOBEL_XY_INTERNAL_PARAMS_IDX].size = sizeof(uint16_t) * vcop_sobelXY_3x3_separable_uchar_param_count();
#else
    internalBlock[SOBEL_XY_INTERNAL_PARAMS_IDX].size = 4U;
#endif

    internalBlock[SOBEL_XY_INTERNAL_SCRATCH_X_IDX].size = blockHeight * computeWidth * sizeof(uint16_t) ;
    internalBlock[SOBEL_XY_INTERNAL_SCRATCH_X_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    internalBlock[SOBEL_XY_INTERNAL_SCRATCH_X_IDX].space = BAM_MEMSPACE_WBUF;

    internalBlock[SOBEL_XY_INTERNAL_SCRATCH_Y_IDX].size = blockHeight * computeWidth * sizeof(uint16_t) ;
    internalBlock[SOBEL_XY_INTERNAL_SCRATCH_Y_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    internalBlock[SOBEL_XY_INTERNAL_SCRATCH_Y_IDX].space = BAM_MEMSPACE_IBUFHA;

    outBlock[BAM_SOBEL_XY_OUTPUT_X_PORT].size = computeWidth * computeHeight;
    outBlock[BAM_SOBEL_XY_OUTPUT_X_PORT].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    outBlock[BAM_SOBEL_XY_OUTPUT_X_PORT].space = BAM_MEMSPACE_IBUFLA;

    outBlock[BAM_SOBEL_XY_OUTPUT_Y_PORT].size = computeWidth * computeHeight;
    outBlock[BAM_SOBEL_XY_OUTPUT_Y_PORT].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    outBlock[BAM_SOBEL_XY_OUTPUT_Y_PORT].space = BAM_MEMSPACE_IBUFLA;

    return BAM_S_SUCCESS;
}


/* For Compute Hough Space index BAM node */
BAM_KernelInfo gBAM_TI_sobelXyKernel =
{
    0,                                      /* kernelId */
    sizeof(BAM_SobelXy_Context),
    sizeof(BAM_SobelXy_Args),
    BAM_EVE,                                /* coreType */
    BAM_NODE_COMPUTE,                       /* nodeType */
    BAM_SOBEL_XY_NUM_INPUT_BLOCKS,
    BAM_SOBEL_XY_NUM_OUTPUT_BLOCKS,
    SOBEL_XY_INTERNAL_NUM_BLOCK
};

BAM_KernelHelperFuncDef gBAM_TI_sobelXyHelperFunc =
{ &BAM_SobelXy_getMemRecFunc,
  NULL};

