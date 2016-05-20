/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_median_filter_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating median filter
 *              into BAM
 */

#include <stdio.h>
#include <stdlib.h>

#include "evealgframework.h"
#include "bam_median_filter_int.h"
#include "vcop_median_filter_mxn_u8.h"


/* Function Prototypes */
static BAM_Status BAM_Median_Filter_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks);


static BAM_Status BAM_Median_Filter_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks)
{

    internalBlock[PARAMS_IDX].size = 2U*vcop_large_kernel_median_wrapper_param_count();
    internalBlock[HISTO_IDX].size = 4096U;
    internalBlock[SCRATCH_HISTO_IDX].size = 8U*36U*8U;
    internalBlock[BLK_HIST_IDX].size = 36U*16U;
    internalBlock[COARSE_HIST_IDX].size = 2U*16U;

    internalBlock[SCRATCH_WEIGHT_IDX].size = 16U;
    internalBlock[SCRATCH_WEIGHT_IDX].space = BAM_MEMSPACE_WBUF;

    outBlock[OUT_IDX].size = 1U;

    return BAM_S_SUCCESS;
}


BAM_KernelInfo gBAM_TI_medianFilterKernel =
{
    0,                                      /* kernelId */
    sizeof(BAM_Median_Filter_Context),
    sizeof(BAM_Median_Filter_Args),
    BAM_EVE,                                /* coreType */
    BAM_NODE_COMPUTE,                       /* nodeType */
    NUM_IN_BLOCKS,                          /* 1 */
    NUM_OUT_BLOCKS,                         /* 1 */
    NUM_INTERNAL_BLOCKS                     /* 6 */
};

BAM_KernelHelperFuncDef gBAM_TI_medianFilterHelperFunc =
{ &BAM_Median_Filter_getMemRecFunc, NULL};

