/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_harrisScore_32_methodB_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating harrisScore_32_7x7 into a BAM graph
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_harrisScore_32_methodB_int.h"
#include "bam_harrisScore_32_7x7.h"
#include "vcop_harrisScore_32_7x7_kernel.h"

/* Function Prototypes */
static BAM_Status BAM_harrisScore_32_methodB_initFrame(void *kernelContext);

static BAM_Status BAM_harrisScore_32_methodB_initFrame(void *kernelContext)
{
    BAM_HarrisScore_32_methodB_Context *context = (BAM_HarrisScore_32_methodB_Context *) kernelContext;
    BAM_Status status = 0;

#if !(VCOP_HOST_EMULATION)
    vcop_harrisScore_32_methodB_init(
            (int16_t*)context->pInBlock[BAM_HARRISSCORE_32_INPUT_GRADX_PORT], /* gradX */
            (int16_t*)context->pInBlock[BAM_HARRISSCORE_32_INPUT_GRADY_PORT], /* gradY */
            (uint32_t*)context->pInternalBlock[BAM_HARRISSCORE_32_METHOD_B_INTERNAL_SCRATCHXX_IDX],/* XX */
            (uint32_t*)context->pInternalBlock[BAM_HARRISSCORE_32_METHOD_B_INTERNAL_SCRATCHYY_IDX],/* YY */
            context->kernelArgs.width,                                          /* width */
            context->kernelArgs.height,                                         /* height */
            context->kernelArgs.inStride,                                       /* srcPitch */
            context->kernelArgs.outStride,  /* dstPitch */
            context->kernelArgs.windowSize, /* window Size */
            (uint32_t *) context->pOutBlock[BAM_HARRISSCORE_32_OUTPUT_SCORE_PORT],
            (uint16_t*) context->pInternalBlock[BAM_HARRISSCORE_32_METHOD_B_INTERNAL_PARAM_IDX]);
#endif
    return status;
}

#if (VCOP_HOST_EMULATION)
static BAM_Status BAM_harrisScore_32_methodB_compute(void *kernelContext)
{
    BAM_HarrisScore_32_methodB_Context *context = (BAM_HarrisScore_32_methodB_Context *) kernelContext;
    BAM_Status status = 0;

    vcop_harrisScore_32_methodB (
            (int16_t*)context->pInBlock[BAM_HARRISSCORE_32_INPUT_GRADX_PORT], /* gradX */
            (int16_t*)context->pInBlock[BAM_HARRISSCORE_32_INPUT_GRADY_PORT], /* gradY */
            (uint32_t*)context->pInternalBlock[BAM_HARRISSCORE_32_METHOD_B_INTERNAL_SCRATCHXX_IDX],/* XX */
            (uint32_t*)context->pInternalBlock[BAM_HARRISSCORE_32_METHOD_B_INTERNAL_SCRATCHYY_IDX],/* YY */
            context->kernelArgs.width,                                          /* width */
            context->kernelArgs.height,                                         /* height */
            context->kernelArgs.inStride,                                       /* srcPitch */
            context->kernelArgs.outStride,  /* dstPitch */
            context->kernelArgs.windowSize, /* window Size */
            (uint32_t *) context->pOutBlock[BAM_HARRISSCORE_32_OUTPUT_SCORE_PORT]);

    return status;

}
#endif

BAM_KernelExecFuncDef gBAM_TI_harrisScore_32_methodB_ExecFunc =
{
#if VCOP_HOST_EMULATION
  NULL,
  &BAM_harrisScore_32_methodB_initFrame,
  &BAM_harrisScore_32_methodB_compute,
  NULL,
  NULL,
  NULL
#else
  NULL,
  &BAM_harrisScore_32_methodB_initFrame,
  NULL,
  NULL,
  NULL,
  &vcop_harrisScore_32_methodB_vloops
#endif
  };

