/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_block_statistics_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating block statistics
 *              into BAM
 */

#include <stdio.h>
#include <stdlib.h>

#include "evealgframework.h"
#include "bam_block_statistics_int.h"
#include "vcop_block_statistics_kernel.h" /* compiler should take care of include path */

/* Function Prototypes */
static BAM_Status BAM_Block_Statistics_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks);

static BAM_Status BAM_Block_Statistics_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks)
{
    const BAM_Block_Statistics_Args *args = (const BAM_Block_Statistics_Args *) kernelArgs;

#if !(VCOP_HOST_EMULATION)
    internalBlock[PARAMS_IDX].size = 2U*vcop_block_statistics_param_count();
#else
    internalBlock[PARAMS_IDX].size = 4U;
#endif
    internalBlock[SCRATCH_MINMAX_IDX].size = (8U*((args->blockWidth+7U)/8U)*36U) + (8U*36U); /* Includes additional space for scratchSumSq_C */
    internalBlock[SCRATCH_SUM_IDX].size = 8U*((args->blockWidth+7U)/8U)*36U;
    internalBlock[SCRATCH_SUMSQ_B_IDX].size = 8U*((args->blockWidth+7U)/8U)*36U;

    outBlock[OUT_MIN_IDX].size = 8U*36U;
    outBlock[OUT_MAX_IDX].size = 8U*36U; /* Can we use the free space in memory allocated for min? */
    outBlock[OUT_MEAN_IDX].size = 8U*36U; /* Can we use the free space in memory allocated for min? */
    outBlock[OUT_VAR_IDX].size = 4U*(((args->blockWidth/args->statBlockWidth) * (args->blockHeight/args->statBlockHeight)) + 7U);

    return BAM_S_SUCCESS;
}

BAM_KernelInfo gBAM_TI_blockStatisticsKernel =
{
    0,                                      /* kernelId */
    sizeof(BAM_Block_Statistics_Context),
    sizeof(BAM_Block_Statistics_Args),
    BAM_EVE,                                /* coreType */
    BAM_NODE_COMPUTE,                       /* nodeType */
    NUM_IN_BLOCKS,                          /* 1 */
    NUM_OUT_BLOCKS,                         /* 4 */
    NUM_INTERNAL_BLOCKS                     /* 3 */
};

BAM_KernelHelperFuncDef gBAM_TI_blockStatisticsHelperFunc =
{ &BAM_Block_Statistics_getMemRecFunc, NULL};

