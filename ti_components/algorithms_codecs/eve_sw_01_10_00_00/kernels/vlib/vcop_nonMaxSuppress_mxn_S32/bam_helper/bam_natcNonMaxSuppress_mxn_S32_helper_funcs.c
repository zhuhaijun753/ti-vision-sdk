/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_natcNonMaxSuppress_mxn_S32_helper_funcs.c
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
static BAM_Status BAM_natcNonMaxSuppress_mxn_S32_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks);

static BAM_Status BAM_natcNonMaxSuppress_mxn_S32_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks)
{

#if !(VCOP_HOST_EMULATION)
    const BAM_NonMaxSuppress_mxn_S32_Args *args = kernelArgs;
    internalBlock[PARAMS_IDX].size = 2u*vcop_nonMaxSuppress_mxn_32s_param_count();
#else
    const BAM_NonMaxSuppress_mxn_S32_Args *args = (const BAM_NonMaxSuppress_mxn_S32_Args *)kernelArgs;
    internalBlock[PARAMS_IDX].size = 4u;
#endif

    /* Verify that args->outStride is multiple of 8 for the kernel-C implementation vcop_nonMaxSuppression_mxn_32s() to work correctly */
    assert(((uint32_t)args->outStride & 0x7U) == 0);

    internalBlock[SCRATCH1_IDX].size = sizeof(uint32_t)*(((uint32_t)args->height-(args->winH-1u))*ALIGN_2SIMD(args->width));
    internalBlock[SCRATCH1_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;

    internalBlock[SCRATCH2_IDX].size = sizeof(uint32_t)*(2u*(((uint32_t)args->height-(args->winH-2u))/2u)*ALIGN_SIMD(args->width-(args->winW-1u)));
    internalBlock[SCRATCH2_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;

    outBlock[OUT_IDX].size = sizeof(uint8_t)*(args->outStride*(args->height-(args->winH-1u)));

    return BAM_S_SUCCESS;
}

BAM_KernelInfo gBAM_TI_natcNonMaxSuppress_mxn_S32_Kernel =
{
        0,                                      /* kernelId */
        sizeof(BAM_NonMaxSuppress_mxn_S32_Context),
        sizeof(BAM_NonMaxSuppress_mxn_S32_Args),
        BAM_EVE_ARP32,                                /* coreType */
        BAM_NODE_COMPUTE,                       /* nodeType */
        NUM_IN_BLOCKS,                          /* 1 */
        NUM_OUT_BLOCKS,                         /* 1 */
        NUM_INTERNAL_BLOCKS                     /* 3 */
};

BAM_KernelHelperFuncDef gBAM_TI_natcNonMaxSuppress_mxn_S32_HelperFunc =
{ &BAM_natcNonMaxSuppress_mxn_S32_getMemRecFunc, NULL};

