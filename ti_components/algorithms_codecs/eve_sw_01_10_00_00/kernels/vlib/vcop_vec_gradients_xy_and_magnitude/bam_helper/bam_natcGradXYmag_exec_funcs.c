/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_natcGradXYmag_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating the natural C version of gradXYmag into a BAM graph
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "../inc/vcop_vec_gradients_xy_and_magnitude_c.h"
#include "bam_gradXYmag_int.h"
#include "bam_gradXYmag.h"
#include "vcop_vec_gradients_xy_and_magnitude_kernel.h"

/* Function Prototypes */
static BAM_Status BAM_natcGradXYmag_computeFrame(void *kernelContext);

static BAM_Status BAM_natcGradXYmag_computeFrame(void *kernelContext)
{
    BAM_GradXYmag_Context *context = (BAM_GradXYmag_Context *) kernelContext;
    BAM_Status status = 0;

    /* By the way the function is initialized, it will take a block of kernelArgs.width x kernelArgs.height pixels
     *  and calculate the gradient of of every pixel in the center region of dimension (kernelArgs.width-2)x(kernelArgs.height-2).
     *  The output is however written in a region of dimensions kernelArgs.width x (kernelArgs.height-2), so the last 2 pixels of each output row
     *  must be ignored.
     */
    vcop_vec_gradients_xy_and_magnitude_cn2(
            (uint8_t*)context->pInBlock[BAM_GRADXYMAG_INPUT_PORT],
            (int16_t*)context->pOutBlock[BAM_GRADXYMAG_X_OUTPUT_PORT],
            (int16_t*)context->pOutBlock[BAM_GRADXYMAG_Y_OUTPUT_PORT],
            (int16_t*)context->pOutBlock[BAM_GRADXYMAG_MAG_OUTPUT_PORT],
            context->kernelArgs.width,
            context->kernelArgs.height,
            context->kernelArgs.pitch,
            context->kernelArgs.width
    );

    return status;
}

BAM_KernelExecFuncDef gBAM_TI_natcGradXYmagExecFunc =
{ NULL, NULL, &BAM_natcGradXYmag_computeFrame, NULL, NULL, NULL };

