/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_median3x3_helper_funcs.c
 *
 *  @brief      This file defines interfaces for integrating 3x3 median filter
 *              into BAM.
 */

#include <stdio.h>
#include <stdlib.h>

#include "evealgframework.h"
#include "bam_median3x3_int.h"
#include "vcop_median3x3_kernel.h" /* compiler should take care of include path */

/* Function prototype */
static BAM_Status BAM_Median3x3_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks);

static BAM_Status BAM_Median3x3_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks)
{
    const BAM_Median3x3_Args *args = (const BAM_Median3x3_Args *) kernelArgs;

#if !VCOP_HOST_EMULATION
    internalBlock[PARAMS_IDX].size = 2*MAX(vcop_median3x3_char_param_count(),
                                           vcop_median3x3_uchar_param_count());
#else
    internalBlock[PARAMS_IDX].size = 4;
#endif

    internalBlock[SCRATCH_VERT_IDX].size = 3*args->blockHeight*args->blockWidth;
    internalBlock[SCRATCH_VERT_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    internalBlock[SCRATCH_VERT_IDX].space = BAM_MEMSPACE_IBUFHA;

    internalBlock[SCRATCH_HORZ_IDX].size = 3*args->blockHeight*args->blockWidth;
    internalBlock[SCRATCH_HORZ_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    internalBlock[SCRATCH_HORZ_IDX].space = BAM_MEMSPACE_WBUF;

    outBlock[OUT_IDX].size = args->blockWidth*args->blockHeight;
    outBlock[OUT_IDX].space = BAM_MEMSPACE_IBUFHA;

    return BAM_S_SUCCESS;
}


BAM_KernelInfo gBAM_TI_median3x3Kernel =
{
    0,                                      /* kernelId */
    sizeof(BAM_Median3x3_Context),
    sizeof(BAM_Median3x3_Args),
    BAM_EVE,                                /* coreType */
    BAM_NODE_COMPUTE,                       /* nodeType */
    NUM_IN_BLOCKS,                          /* 1 */
    NUM_OUT_BLOCKS,                         /* 1 */
    NUM_INTERNAL_BLOCKS                     /* 3 */
};

BAM_KernelHelperFuncDef gBAM_TI_median3x3HelperFunc =
{ &BAM_Median3x3_getMemRecFunc, NULL};

