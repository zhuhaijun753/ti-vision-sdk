/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_natcBlockAverage2x2_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating the natural C version of blockAverage2x2 into a BAM graph
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "../inc/vcop_blockAverage2x2_cn.h"
#include "bam_blockAverage2x2_int.h"
#include "bam_blockAverage2x2.h"
#include "vcop_blockAverage2x2_kernel.h"

/* Function Prototypes */
static BAM_Status BAM_natcBlockAverage2x2_computeFrame(void *kernelContext);

static BAM_Status BAM_natcBlockAverage2x2_computeFrame(void *kernelContext)
{
    BAM_BlockAverage2x2_Context *context = (BAM_BlockAverage2x2_Context *) kernelContext;
    BAM_Status status = 0;

    vcop_blockAverage2x2_uchar_cn((uint8_t*)context->pInBlock[BAM_BLOCKAVERAGE2x2_INPUT_PORT],
            (uint8_t*)context->pOutBlock[BAM_BLOCKAVERAGE2x2_OUTPUT_PORT],
            context->kernelArgs.in_stride,
            context->kernelArgs.out_stride,
            context->kernelArgs.width,
            context->kernelArgs.height);

    return status;
}

BAM_KernelExecFuncDef gBAM_TI_natcBlockAverage2x2ExecFunc =
{ NULL, NULL, &BAM_natcBlockAverage2x2_computeFrame, NULL, NULL, NULL };

