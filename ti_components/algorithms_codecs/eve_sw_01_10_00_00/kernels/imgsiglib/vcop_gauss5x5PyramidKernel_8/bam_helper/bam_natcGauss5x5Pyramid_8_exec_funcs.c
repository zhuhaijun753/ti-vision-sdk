/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_natcGauss5x5Pyramid_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating the natural C version of gauss5x5Pyramid into a BAM graph
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "../inc/vcop_gauss5x5PyramidKernel_8_cn.h"
#include "bam_gauss5x5Pyramid_8_int.h"
#include "bam_gauss5x5Pyramid_8.h"
#include "vcop_gauss5x5PyramidKernel_8_kernel.h"

/* Function Prototypes */
static BAM_Status BAM_natcGauss5x5Pyramid_computeFrame(void *kernelContext);

static BAM_Status BAM_natcGauss5x5Pyramid_computeFrame(void *kernelContext)
{
    BAM_Gauss5x5Pyramid_Context *context = (BAM_Gauss5x5Pyramid_Context *) kernelContext;
    BAM_Status status = 0;

    vcop_gauss5x5PyramidKernel_8_horiz_c(
            (uint8_t*)context->pInBlock[BAM_GAUSS5x5PYRAMID_INPUT_PORT],
            (uint8_t*)context->pInternalBlock[PARAMS_TEMP_IDX],
            context->kernelArgs.width,
            context->kernelArgs.height+4u,
            context->kernelArgs.in_stride,
            context->kernelArgs.width
            );

    vcop_gauss5x5PyramidKernel_8_vert_c(
            (uint8_t*)context->pInternalBlock[PARAMS_TEMP_IDX],
            (uint8_t*)context->pOutBlock[BAM_GAUSS5x5PYRAMID_OUTPUT_PORT],
            context->kernelArgs.width,
            context->kernelArgs.height,
            context->kernelArgs.width,
            context->kernelArgs.out_stride
            );

    return status;
}

BAM_KernelExecFuncDef gBAM_TI_natcGauss5x5PyramidExecFunc =
{ NULL, NULL, &BAM_natcGauss5x5Pyramid_computeFrame, NULL, NULL, NULL };

