/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_nonMaxSuppress_mxn_S32_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating nonMaxSuppress_mxn_S32 into a BAM graph
 */

#include <stdio.h>
#include <stdlib.h>

#include "evealgframework.h"
#include "bam_nonMaxSuppress_mxn_S32_int.h"
#include "vcop_nonMaxSuppress_mxn_32s_kernel.h"
#include <assert.h>

/* Function Prototypes */
static BAM_Status BAM_nonMaxSuppress_mxn_S32_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks);

static BAM_Status BAM_nonMaxSuppress_mxn_S32_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks)
{
    const BAM_NonMaxSuppress_mxn_S32_Args *args = (const BAM_NonMaxSuppress_mxn_S32_Args *) kernelArgs;

    if ( args->outputFormat == BAM_NONMAXSUPPRESS_MxN_S32_OUTPUT_FORMAT_BYTEMAP )
    {

        /* Verify that args->outStride is multiple of 8 for the kernel-C implementation vcop_nonMaxSuppression_mxn_32s() to work correctly */
        assert((args->outStride & 0x7u) == 0);
    }

#if !(VCOP_HOST_EMULATION)
    if ( args->outputFormat == BAM_NONMAXSUPPRESS_MxN_S32_OUTPUT_FORMAT_BYTEMAP )
    {
      internalBlock[PARAMS_IDX].size = sizeof(uint16_t) * vcop_nonMaxSuppress_mxn_32s_param_count();
    }
    else
    {
      internalBlock[PARAMS_IDX].size = sizeof(uint16_t) * vcop_nonMaxSuppress_mxn_32s_bitPack_param_count();
    }

#else
    internalBlock[PARAMS_IDX].size = 4;
#endif

    internalBlock[SCRATCH1_IDX].size = (uint32_t)sizeof(int32_t)*(((uint32_t)args->height - (args->winH - 1u))*ALIGN_2SIMD(args->width));
    internalBlock[SCRATCH1_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;

    internalBlock[SCRATCH2_IDX].size = (uint32_t)sizeof(int32_t)*(2u*(((uint32_t)args->height - (args->winH - 2u))/2u) * ALIGN_SIMD(args->width) );
    internalBlock[SCRATCH2_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;

    outBlock[OUT_IDX].size = sizeof(uint8_t)*(args->outStride*(args->height-(args->winH-1)));

    return BAM_S_SUCCESS;
}

BAM_KernelInfo gBAM_TI_nonMaxSuppress_mxn_S32_Kernel =
{
        0,                                      /* kernelId */
        sizeof(BAM_NonMaxSuppress_mxn_S32_Context),
        sizeof(BAM_NonMaxSuppress_mxn_S32_Args),
        BAM_EVE,                                /* coreType */
        BAM_NODE_COMPUTE,                       /* nodeType */
        NUM_IN_BLOCKS,                          /* 1 */
        NUM_OUT_BLOCKS,                         /* 1 */
        NUM_INTERNAL_BLOCKS                     /* 3 */
};

BAM_KernelInfo gBAM_TI_nonMaxSuppress_mxn_S32_binPack_Kernel =
{
        0,                                      /* kernelId */
        sizeof(BAM_NonMaxSuppress_mxn_S32_Context),
        sizeof(BAM_NonMaxSuppress_mxn_S32_Args),
        BAM_EVE,                                /* coreType */
        BAM_NODE_COMPUTE,                       /* nodeType */
        NUM_IN_BLOCKS,                          /* 1 */
        NUM_OUT_BLOCKS,                         /* 1 */
        NUM_INTERNAL_BLOCKS                     /* 3 */
};


BAM_KernelHelperFuncDef gBAM_TI_nonMaxSuppress_mxn_S32_HelperFunc =
{ &BAM_nonMaxSuppress_mxn_S32_getMemRecFunc, NULL};

