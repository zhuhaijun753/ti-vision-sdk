/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_block_statistics_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating block statistics
 *              function into BAM.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_block_statistics_int.h"
#include "bam_block_statistics.h"
#include "vcop_block_statistics_kernel.h" /* compiler should take care of include path */

/* Function Prototypes */
static BAM_Status Bam_Block_Statistics_initFrame(void *kernelContext);

static BAM_Status Bam_Block_Statistics_initFrame(void *kernelContext)
{
    BAM_Block_Statistics_Context *context = (BAM_Block_Statistics_Context *) kernelContext;
    BAM_Status status = 0;

    /* Return error if assumptions in kernel are not satisfied */
    if(( (context->kernelArgs.blockWidth/context->kernelArgs.statBlockWidth) > 8U) ||
        ( (context->kernelArgs.blockHeight/context->kernelArgs.statBlockHeight) > 8U) ||
        ( (context->kernelArgs.statBlockHeight*context->kernelArgs.statBlockWidth) > 256U)) {
        status = 1;
    }
#if !(VCOP_HOST_EMULATION)
    if(status == 0) {
        vcop_block_statistics_init((uint8_t*)context->pInBlock[IN_IDX],
                               context->kernelArgs.blockStride,
                               context->kernelArgs.blockWidth,
                               context->kernelArgs.blockHeight,
                               context->kernelArgs.statBlockWidth,
                               context->kernelArgs.statBlockHeight,
                               (uint8_t*)context->pInternalBlock[SCRATCH_MINMAX_IDX],
                               (uint16_t*)context->pInternalBlock[SCRATCH_SUM_IDX],
                               (uint32_t*)context->pInternalBlock[SCRATCH_SUMSQ_B_IDX],
                               (uint32_t*)(*((uint32_t (*)[])context->pInternalBlock[SCRATCH_MINMAX_IDX]) + (8U*((context->kernelArgs.blockWidth+7U)/8U)*9U)),
                               (uint16_t*)(*((uint16_t (*)[])context->pInternalBlock[SCRATCH_MINMAX_IDX]) + (8U*((context->kernelArgs.blockWidth+7U)/8U)*18U)),
                               (uint16_t*)(*((uint16_t (*)[])context->pInternalBlock[SCRATCH_MINMAX_IDX]) + (8U*((context->kernelArgs.blockWidth+7U)/8U)*18U) + 1U),
                               (uint8_t*)context->pOutBlock[OUT_MIN_IDX],
                               (uint8_t*)context->pOutBlock[OUT_MAX_IDX],
                               (uint16_t*)context->pOutBlock[OUT_MEAN_IDX],
                               (uint32_t*)context->pOutBlock[OUT_VAR_IDX],
                               (uint16_t*)context->pInternalBlock[PARAMS_IDX]);
    }
#endif
    return status;
}

#if (VCOP_HOST_EMULATION)
static BAM_Status Bam_Block_Statistics_compute(void *kernelContext)
{
    BAM_Block_Statistics_Context *context = (BAM_Block_Statistics_Context *) kernelContext;
    BAM_Status status = 0;

    vcop_block_statistics((uint8_t*)context->pInBlock[IN_IDX],
                               context->kernelArgs.blockStride,
                               context->kernelArgs.blockWidth,
                               context->kernelArgs.blockHeight,
                               context->kernelArgs.statBlockWidth,
                               context->kernelArgs.statBlockHeight,
                               (uint8_t*)context->pInternalBlock[SCRATCH_MINMAX_IDX],
                               (uint16_t*)context->pInternalBlock[SCRATCH_SUM_IDX],
                               (uint32_t*)context->pInternalBlock[SCRATCH_SUMSQ_B_IDX],
                               (uint32_t*)((uint32_t*)context->pInternalBlock[SCRATCH_MINMAX_IDX] + 8U*((context->kernelArgs.blockWidth+7U)/8U)*9U),
                               (uint16_t*)((uint16_t*)context->pInternalBlock[SCRATCH_MINMAX_IDX] + 8U*((context->kernelArgs.blockWidth+7U)/8U)*18U),
                               (uint16_t*)((uint16_t*)context->pInternalBlock[SCRATCH_MINMAX_IDX] + 8U*((context->kernelArgs.blockWidth+7U)/8U)*18U + 1U),
                               (uint8_t*)context->pOutBlock[OUT_MIN_IDX],
                               (uint8_t*)context->pOutBlock[OUT_MAX_IDX],
                               (uint16_t*)context->pOutBlock[OUT_MEAN_IDX],
                               (uint32_t*)context->pOutBlock[OUT_VAR_IDX]);

    return 0;
}
#endif

BAM_KernelExecFuncDef gBAM_TI_blockStatisticsExecFunc =
#if !(VCOP_HOST_EMULATION)
{ NULL, &Bam_Block_Statistics_initFrame, NULL, NULL, NULL, &vcop_block_statistics_vloops };
#else
{ NULL, &Bam_Block_Statistics_initFrame, &Bam_Block_Statistics_compute, NULL, NULL, NULL };
#endif
