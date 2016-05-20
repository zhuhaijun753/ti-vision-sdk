/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_remap_bilinear_interpolate8b_helper_funcs.c
 *
 *  @brief      This file defines interfaces for integrating Remap Bilinear
 *              interpolate 8 bit kernel into BAM.
 */

#include <stdio.h>
#include <stdlib.h>

#include "evealgframework.h"
#include "bam_remap_bilinear_interpolate8b_int.h"
#include "vcop_bilinearInterpolate8b.h"

/* Function Prototypes */
static BAM_Status BAM_RemapBilinearInterpolate8b_getMemRecFunc(
                          const void *kernelArgs,
                          BAM_MemRec internalBlock[],
                          BAM_MemRec outBlock[],
                          uint8_t *numInternalBlocks,
                          uint8_t *numOutBlocks);


static BAM_Status BAM_RemapBilinearInterpolate8b_getMemRecFunc(
                          const void *kernelArgs,
                          BAM_MemRec internalBlock[],
                          BAM_MemRec outBlock[],
                          uint8_t *numInternalBlocks,
                          uint8_t *numOutBlocks)
{
#if (VCOP_HOST_EMULATION)
    const BAM_RemapBilinearInterpolate8b_Args *args = (const BAM_RemapBilinearInterpolate8b_Args *)kernelArgs;
#else
    /* Typecasting by (const BAM_RemapBilinearInterpolate8b_Args *) will lead to MISRA C 11.5. */
    const BAM_RemapBilinearInterpolate8b_Args *args = kernelArgs;
#endif

#if (!VCOP_HOST_EMULATION)
    internalBlock[REMAP_BILINEAR_INTERPOLATE8B_INTERTNAL_PARAMS_IDX].size = 2U * vcop_bilinearInterpolate8b_highSpeed_param_count();
#else
    /* This field could be any non-zero number for host emulation */
    internalBlock[REMAP_BILINEAR_INTERPOLATE8B_INTERTNAL_PARAMS_IDX].size = 4U;
#endif

    internalBlock[REMAP_BILINEAR_INTERPOLATE8B_INTERTNAL_SCRATCH_IDX].size = 4U;
    internalBlock[REMAP_BILINEAR_INTERPOLATE8B_INTERTNAL_SCRATCH_IDX].attrs.memAttrs    = BAM_MEMATTRS_SCRATCH;
    internalBlock[REMAP_BILINEAR_INTERPOLATE8B_INTERTNAL_SCRATCH_IDX].space             = BAM_MEMSPACE_WBUF;

    internalBlock[REMAP_BILINEAR_INTERPOLATE8B_INTERTNAL_SCRATCH_HBUF_IDX].size = 4U*ALIGN_2SIMD(args->outBlockWidth * args->outBlockHeight);
    internalBlock[REMAP_BILINEAR_INTERPOLATE8B_INTERTNAL_SCRATCH_HBUF_IDX].attrs.memAttrs    = BAM_MEMATTRS_SCRATCH;
    internalBlock[REMAP_BILINEAR_INTERPOLATE8B_INTERTNAL_SCRATCH_HBUF_IDX].space             = BAM_MEMSPACE_IBUFHA;

    internalBlock[REMAP_BILINEAR_INTERPOLATE8B_INTERTNAL_INDATA_LUT].size = 2U*ALIGN_2SIMD(args->ctrlArgs.maxInBlockSize);
    internalBlock[REMAP_BILINEAR_INTERPOLATE8B_INTERTNAL_INDATA_LUT].attrs.memAttrs    = BAM_MEMATTRS_SCRATCH;
    internalBlock[REMAP_BILINEAR_INTERPOLATE8B_INTERTNAL_INDATA_LUT].space             = BAM_MEMSPACE_WBUF;


    outBlock[REMAP_BILINEAR_INTERPOLATE8B_OUT_DATA_IDX].size = args->outBlockWidth * (args->outBlockHeight+1U);

    return BAM_S_SUCCESS;
}


BAM_KernelInfo gBAM_TI_remapBilinearInterpolate8bKernel =
{
    0,                                      /* kernelId */
    sizeof(BAM_RemapBilinearInterpolate8b_Context),
    sizeof(BAM_RemapBilinearInterpolate8b_Args),
    BAM_EVE,                                /* coreType */
    BAM_NODE_COMPUTE,                       /* nodeType */
    NUM_IN_BLOCKS,                          /* 1 */
    NUM_OUT_BLOCKS,                         /* 1 */
    NUM_INTERNAL_BLOCKS                     /* 4 */
};

BAM_KernelHelperFuncDef gBAM_TI_remapBilinearInterpolate8bHelperFunc =
{ &BAM_RemapBilinearInterpolate8b_getMemRecFunc, NULL};

