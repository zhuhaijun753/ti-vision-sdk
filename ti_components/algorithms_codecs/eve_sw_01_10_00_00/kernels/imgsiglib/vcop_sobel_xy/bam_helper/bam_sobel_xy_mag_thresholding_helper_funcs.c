/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_sobel_xy_mag_thresholding_helper_funcs.c
 *
 *  @brief      This file defines interfaces for integrating Sobel XY magnitude thresholding
 *              kernel into BAM.
 */

#include <stdio.h>
#include <stdlib.h>

#include "evealgframework.h"
#include "bam_sobel_xy_mag_thresholding_int.h"
#include "vcop_sobel_xy_kernel.h" /* compiler should take care of include path */

static BAM_Status BAM_SobelXyMagThresholding_getMemRecFunc( const void *kernelArgs,
                            BAM_MemRec internalBlock[],
                            BAM_MemRec outBlock[],
                            uint8_t *numInternalBlocks,
                            uint8_t *numOutBlocks);

static BAM_Status BAM_SobelXyMagThresholdingBinPack_getMemRecFunc( const void *kernelArgs,
                            BAM_MemRec internalBlock[],
                            BAM_MemRec outBlock[],
                            uint8_t *numInternalBlocks,
                            uint8_t *numOutBlocks);

static BAM_Status BAM_SobelXyMagThresholding_getMemRecFunc( const void *kernelArgs,
                            BAM_MemRec internalBlock[],
                            BAM_MemRec outBlock[],
                            uint8_t *numInternalBlocks,
                            uint8_t *numOutBlocks)

{
    const BAM_SobelXyMagThresholding_Args *args = (const BAM_SobelXyMagThresholding_Args *) kernelArgs;

#if !VCOP_HOST_EMULATION
    internalBlock[SOBEL_XY_MAG_THRESHOLDING_INTERNAL_PARAMS_IDX].size = sizeof(uint16_t) * vcop_sobelXy_3x3_L1_thresholding_param_count();
#else
    internalBlock[SOBEL_XY_MAG_THRESHOLDING_INTERNAL_PARAMS_IDX].size = 4U;
#endif

    outBlock[BAM_SOBEL_XY_MAG_THRESHOLDING_OUTPUT_IMAGE_PORT].size = args->maxBlockWidth * args->maxBlockHeight;
    outBlock[BAM_SOBEL_XY_MAG_THRESHOLDING_OUTPUT_IMAGE_PORT].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    outBlock[BAM_SOBEL_XY_MAG_THRESHOLDING_OUTPUT_IMAGE_PORT].space = BAM_MEMSPACE_IBUFHA;

    return BAM_S_SUCCESS;
}


/* For Compute Hough Space index BAM node */
BAM_KernelInfo BAM_SobelXyMagThresholdingKernel =
{
    0,                                      /* kernelId */
    sizeof(BAM_SobelXyMagThresholding_Context),
    sizeof(BAM_SobelXyMagThresholding_Args),
    BAM_EVE,                                /* coreType */
    BAM_NODE_COMPUTE,                       /* nodeType */
    BAM_SOBEL_XY_MAG_THRESHOLDING_NUM_INPUT_BLOCKS,
    BAM_SOBEL_XY_MAG_THRESHOLDING_NUM_OUTPUT_BLOCKS,
    SOBEL_XY_MAG_THRESHOLDING_INTERNAL_NUM_BLOCK
};

BAM_KernelHelperFuncDef gBAM_TI_sobelXyMagThresholdingHelperFunc =
{ &BAM_SobelXyMagThresholding_getMemRecFunc,
  NULL};

static BAM_Status BAM_SobelXyMagThresholdingBinPack_getMemRecFunc( const void *kernelArgs,
                            BAM_MemRec internalBlock[],
                            BAM_MemRec outBlock[],
                            uint8_t *numInternalBlocks,
                            uint8_t *numOutBlocks)

{
    const BAM_SobelXyMagThresholding_Args *args = (const BAM_SobelXyMagThresholding_Args *) kernelArgs;

#if !VCOP_HOST_EMULATION
    internalBlock[SOBEL_XY_MAG_THRESHOLDING_INTERNAL_PARAMS_IDX].size = sizeof(uint16_t) * vcop_sobelXy_3x3_L1_thresholding_binPack_param_count();
#else
    internalBlock[SOBEL_XY_MAG_THRESHOLDING_INTERNAL_PARAMS_IDX].size = 4U;
#endif

    outBlock[BAM_SOBEL_XY_MAG_THRESHOLDING_OUTPUT_IMAGE_PORT].size = (args->maxBlockWidth * args->maxBlockHeight) / 8U;
    outBlock[BAM_SOBEL_XY_MAG_THRESHOLDING_OUTPUT_IMAGE_PORT].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    outBlock[BAM_SOBEL_XY_MAG_THRESHOLDING_OUTPUT_IMAGE_PORT].space = BAM_MEMSPACE_IBUFHA;

    return BAM_S_SUCCESS;
}


/* For Compute Hough Space index BAM node */
BAM_KernelInfo BAM_SobelXyMagThresholdingBinPackKernel =
{
    0,                                      /* kernelId */
    sizeof(BAM_SobelXyMagThresholding_Context),
    sizeof(BAM_SobelXyMagThresholding_Args),
    BAM_EVE,                                /* coreType */
    BAM_NODE_COMPUTE,                       /* nodeType */
    BAM_SOBEL_XY_MAG_THRESHOLDING_NUM_INPUT_BLOCKS,
    BAM_SOBEL_XY_MAG_THRESHOLDING_NUM_OUTPUT_BLOCKS,
    SOBEL_XY_MAG_THRESHOLDING_INTERNAL_NUM_BLOCK
};

BAM_KernelHelperFuncDef gBAM_TI_sobelXyMagThresholdingBinPackHelperFunc =
{ &BAM_SobelXyMagThresholdingBinPack_getMemRecFunc,
  NULL};

