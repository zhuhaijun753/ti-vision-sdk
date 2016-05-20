/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_multiblock_bilinear_interp_7x7_u8_helper_funcs.c
 *
 *  @brief      This file defines interfaces for multi block bilinear
 *              interpolation kernel for neighboorhood of 7x7 8-bit pixel data into BAM.
 */

#include <stdio.h>
#include <stdlib.h>

#include "evealgframework.h"
#include "bam_multiblock_bilinear_interp_7x7_u8_int.h"
#include "vcop_multiblock_bilinear_interp_7x7_u8_kernel.h" /* compiler should take care of include path */

/* Function Prototypes */
static BAM_Status BAM_Multiblock_Bilinear_Interp_7x7_U8_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks);

static BAM_Status BAM_Multiblock_Bilinear_Interp_7x7_U8_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks)
{
    const BAM_Multiblock_Bilinear_Interp_7x7_U8_Args *args = (const BAM_Multiblock_Bilinear_Interp_7x7_U8_Args *) kernelArgs;
    internalBlock[PARAMS_IDX].size = 2U*vcop_multiblock_bilinear_interp_7x7_u8_param_count();
    /*Ideal Output Block Memory Requirement:*/
    outBlock[OUT_IDX].size = args->numKeyPoints * (args->outputStride)*(args->blkHeight);
    outBlock[OUT_IDX].attrs.memAttrs= BAM_MEMATTRS_SCRATCH;
    outBlock[OUT_IDX].space = BAM_MEMSPACE_IBUFLA;    

    return BAM_S_SUCCESS;
}

BAM_KernelInfo gBAM_TI_multiblockBilinearInterp7x7U8Kernel =
{
    0,                                      /* kernelId */
    sizeof(BAM_Multiblock_Bilinear_Interp_7x7_U8_Context),
    sizeof(BAM_Multiblock_Bilinear_Interp_7x7_U8_Args),
    BAM_EVE,                                /* coreType */
    BAM_NODE_COMPUTE,                       /* nodeType */
    NUM_IN_BLOCKS,                          /* 1 */
    NUM_OUT_BLOCKS,                         /* 4 */
    NUM_INTERNAL_BLOCKS                     /* 3 */
};

BAM_KernelHelperFuncDef gBAM_TI_multiblockBilinearInterp7x7U8HelperFunc =
{ &BAM_Multiblock_Bilinear_Interp_7x7_U8_getMemRecFunc, NULL};

