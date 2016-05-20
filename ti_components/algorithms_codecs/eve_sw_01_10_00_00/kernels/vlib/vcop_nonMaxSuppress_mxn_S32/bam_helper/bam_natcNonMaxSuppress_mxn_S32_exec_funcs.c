/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_natcNonMaxSuppress_mxn_S32_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating the natural C version of nonMaxSuppress_mxn_S32 into a BAM graph
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "../inc/vcop_nonMaxSuppress_mxn_32s_c.h"
#include "bam_nonMaxSuppress_mxn_S32_int.h"
#include "bam_nonMaxSuppress_mxn_S32.h"
#include "vcop_nonMaxSuppress_mxn_32s_kernel.h"

/* Function Prototypes */
static BAM_Status BAM_natcNonMaxSuppress_mxn_S32_computeFrame(void *kernelContext);

static BAM_Status BAM_natcNonMaxSuppress_mxn_S32_computeFrame(void *kernelContext)
{
    BAM_NonMaxSuppress_mxn_S32_Context *context = (BAM_NonMaxSuppress_mxn_S32_Context *) kernelContext;
    BAM_Status status = 0;

    vcop_nonMaxSuppress_mxn_32s_cn
    (
            (int32_t*)context->pInBlock[BAM_NONMAXSUPPRESS_MxN_S32_INPUT_PORT],
            (uint8_t*)context->pOutBlock[BAM_NONMAXSUPPRESS_MxN_S32_OUTPUT_PORT],
            context->kernelArgs.height,
            context->kernelArgs.width,
            context->kernelArgs.inStride,
            context->kernelArgs.outStride,
            context->kernelArgs.winW,
            context->kernelArgs.winH,
            context->kernelArgs.threshold
    );

    return status;
}

BAM_KernelExecFuncDef gBAM_TI_natcNonMaxSuppress_mxn_S32_ExecFunc =
{ NULL, NULL, &BAM_natcNonMaxSuppress_mxn_S32_computeFrame, NULL, NULL, NULL };

