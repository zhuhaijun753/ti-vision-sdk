/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_histogram_helper_funcs.c
 *
 *  @brief      This file defines interfaces for integrating contrast stretching
                    kernels into BAM.
 */

#include <stdio.h>
#include <stdlib.h>

#include "evealgframework.h"
#include "bam_histogram_int.h"
#include "vcop_contrast_stretching_kernel.h" /* compiler should take care of include path */

/* Function Prototypes */
static BAM_Status BAM_Histogram_getMemRecFunc(
                            const void *kernelArgs,
                            BAM_MemRec internalBlock[],
                            BAM_MemRec outBlock[],
                            uint8_t *numInternalBlocks,
                            uint8_t *numOutBlocks);

static BAM_Status BAM_Histogram_getMemRecFunc(
                            const void *kernelArgs,
                            BAM_MemRec internalBlock[],
                            BAM_MemRec outBlock[],
                            uint8_t *numInternalBlocks,
                            uint8_t *numOutBlocks)

{
#if !VCOP_HOST_EMULATION
    internalBlock[HISTOGRAM_INTERNAL_PARAMS_IDX].size =
                      sizeof(uint16_t) * vcop_histogram_8c_word_param_count();
#else
    internalBlock[HISTOGRAM_INTERNAL_PARAMS_IDX].size = 4U;
#endif

    internalBlock[HISTOGRAM_INTERNAL_HISTOGRAM8COPY_IDX].size =
                  HISTOGRAM_NUM_BINS * sizeof(uint32_t) * HISTOGRAM_NUM_COPIES;
    internalBlock[HISTOGRAM_INTERNAL_HISTOGRAM8COPY_IDX].space =
                  BAM_MEMSPACE_WBUF;
    internalBlock[HISTOGRAM_INTERNAL_HISTOGRAM8COPY_IDX].attrs.memAttrs =
                  BAM_MEMATTRS_CONST;
    internalBlock[HISTOGRAM_INTERNAL_HISTOGRAM8COPY_IDX].alignment = 32U;

    /* output of this currently a dummy output as BAM doesnt allow to have output buf to be
    constant, hence using internal buffer for that  */
    outBlock[BAM_HISTOGRAM_OUTPUT_DUMMY_PORT].size = 4U;
    return BAM_S_SUCCESS;
}


BAM_KernelInfo gBAM_TI_histogramKernel =
{
    0,                                      /* kernelId */
    sizeof(BAM_Histogram_Context),
    sizeof(BAM_Histogram_Args),
    BAM_EVE,                                /* coreType */
    BAM_NODE_COMPUTE,                       /* nodeType */
    NUM_IN_BLOCKS,                          /* 2 */
    NUM_OUT_BLOCKS,                         /* 2 */
    NUM_INTERNAL_BLOCKS                     /* 1 */
};

BAM_KernelHelperFuncDef gBAM_TI_histogramHelperFunc =
{ &BAM_Histogram_getMemRecFunc, NULL};

