/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_multiblock_bilinear_interp_intlv_7x7_s16_helper_funcs.c
 *
 *  @brief      This file defines interfaces for integrating multi block bilinear
 *              interpolation kernel for neighboorhood of 7x7 signed 16-bit gradient
 *              pixel data which includes gradient along X and Y directions in
 *              interleaved format into BAM.
 */

#include <stdio.h>
#include <stdlib.h>

#include "evealgframework.h"
#include "bam_multiblock_bilinear_interp_intlv_7x7_s16_int.h"
#include "vcop_multiblock_bilinear_interp_intlv_7x7_s16_kernel.h" /* compiler should take care of include path */

/* Function Prototypes */
static BAM_Status BAM_Multiblock_Bilinear_Interp_Intlv_7x7_S16_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks);

static BAM_Status BAM_Multiblock_Bilinear_Interp_Intlv_7x7_S16_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks)
{
    const BAM_Multiblock_Bilinear_Interp_Intlv_7x7_S16_Args *args = (const BAM_Multiblock_Bilinear_Interp_Intlv_7x7_S16_Args *) kernelArgs;
    internalBlock[PARAMS_IDX].size = 2U*vcop_multiblock_bilinear_interp_intlv_7x7_s16_param_count();
    /*Ideal Output Block Memory Requirement:*/
    outBlock[OUT_IDX1].size = args->numKeyPoints * 2 * (args->blkWidth)*(args->blkHeight);
    outBlock[OUT_IDX1].attrs.memAttrs= BAM_MEMATTRS_SCRATCH;
    outBlock[OUT_IDX1].space = BAM_MEMSPACE_IBUFLA;    
    outBlock[OUT_IDX2].size = args->numKeyPoints * 2 * (args->blkWidth)*(args->blkHeight);
    outBlock[OUT_IDX2].attrs.memAttrs= BAM_MEMATTRS_SCRATCH;
    outBlock[OUT_IDX2].space = BAM_MEMSPACE_IBUFLA;    


    return BAM_S_SUCCESS;
}

BAM_KernelInfo gBAM_TI_multiblockBilinearInterpIntlv7x7S16Kernel =
{
    0,                                      /* kernelId */
    sizeof(BAM_Multiblock_Bilinear_Interp_Intlv_7x7_S16_Context),
    sizeof(BAM_Multiblock_Bilinear_Interp_Intlv_7x7_S16_Args),
    BAM_EVE,                                /* coreType */
    BAM_NODE_COMPUTE,                       /* nodeType */
    NUM_IN_BLOCKS,                          /* 1 */
    NUM_OUT_BLOCKS,                         /* 4 */
    NUM_INTERNAL_BLOCKS                     /* 3 */
};

BAM_KernelHelperFuncDef gBAM_TI_multiblockBilinearInterpIntlv7x7S16HelperFunc =
{ &BAM_Multiblock_Bilinear_Interp_Intlv_7x7_S16_getMemRecFunc, NULL};

