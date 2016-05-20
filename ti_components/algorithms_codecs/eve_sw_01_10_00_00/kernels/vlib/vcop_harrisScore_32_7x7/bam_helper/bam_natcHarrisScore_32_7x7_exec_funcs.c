/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_natcHarrisScore_32_7x7_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating the natural C version of harrisScore_32_7x7 into a BAM graph
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "../inc/vcop_harrisScore_32_7x7_cn.h"
#include "bam_harrisScore_32_7x7_int.h"
#include "bam_harrisScore_32_7x7.h"
#include "vcop_harrisScore_32_7x7_kernel.h"

/* Function Prototypes */
static BAM_Status BAM_natcHarrisScore_32_7x7_computeFrame(void *kernelContext);

static BAM_Status BAM_natcHarrisScore_32_7x7_computeFrame(void *kernelContext)
{
    BAM_HarrisScore_32_7x7_Context *context = (BAM_HarrisScore_32_7x7_Context *) kernelContext;
    BAM_Status status = 0;

    vcop_harrisScore_32_7x7_cn
    (
            (int16_t*)context->pInBlock[BAM_HARRISSCORE_32_INPUT_GRADX_PORT],
            (int16_t*)context->pInBlock[BAM_HARRISSCORE_32_INPUT_GRADY_PORT],
            context->kernelArgs.width,                                          /* width */
            context->kernelArgs.height,                                         /* height */
            context->kernelArgs.inStride,                                       /* srcPitch */
            context->kernelArgs.outStride,  /* dstPitch */
            context->kernelArgs.windowSize,
            (int32_t*)context->pOutBlock[BAM_HARRISSCORE_32_OUTPUT_SCORE_PORT], /* outm */
            context->kernelArgs.scaling    /* k */
    );

    return status;
}

BAM_KernelExecFuncDef gBAM_TI_natcHarrisScore_32_7x7_ExecFunc =
{ NULL, NULL, &BAM_natcHarrisScore_32_7x7_computeFrame, NULL, NULL, NULL };

