/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_gradXYmag_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating gradXYmag into a BAM graph
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_gradXYmag_int.h"
#include "bam_gradXYmag.h"
#include "vcop_vec_gradients_xy_and_magnitude_kernel.h"

/* Function Prototypes */
static BAM_Status BAM_gradXYmag_initFrame(void *kernelContext);
static BAM_Status BAM_gradXYmag_Compute(void *kernelContext);


static BAM_Status BAM_gradXYmag_initFrame(void *kernelContext)
{
    BAM_GradXYmag_Context *context = (BAM_GradXYmag_Context *) kernelContext;
    BAM_Status status = 0;

    /* By the way the function is initialized, it will take a block of kernelArgs.width x kernelArgs.height pixels
     *  and calculate the gradient of of every pixel in the center region of dimension (kernelArgs.width-2)x(kernelArgs.height-2).
     *  The output is however written in a region of dimensions kernelArgs.width x (kernelArgs.height-2), so the last 2 pixels of each output row
     *  must be ignored.
     *  The function may also produce more data if kernelArgs.width x (kernelArgs.height-2) is not multiple of 16. That's why the getMemRec function asks
     *  for a total output size that is rounded up to the next multiple of 16. In any case only the first kernelArgs.width x (kernelArgs.height-2) elements
     *  in the output are to be considered. And within this, the two last pixels of each row of kernelArgs.width pixels must be ignored.
     */
#if !(VCOP_HOST_EMULATION)
    if(context->kernelArgs.gradientMethod == EVE_VLIB_GRADIENT_MAGNITUDE_9BITS)
    {
      vcop_vec_gradients_xy_and_magnitude_init(
            (uint8_t*)context->pInBlock[BAM_GRADXYMAG_INPUT_PORT],
            (int16_t*)context->pOutBlock[BAM_GRADXYMAG_X_OUTPUT_PORT],
            (int16_t*)context->pOutBlock[BAM_GRADXYMAG_Y_OUTPUT_PORT],
            (int16_t*)context->pOutBlock[BAM_GRADXYMAG_MAG_OUTPUT_PORT],
            context->kernelArgs.pitch,
            context->kernelArgs.width,
            context->kernelArgs.height,
            (uint16_t*)context->pInternalBlock[PARAMS_IDX]);
      context->kernelCustom = &vcop_vec_gradients_xy_and_magnitude_vloops;
    }
    else {
        if(context->kernelArgs.gradientMethod == EVE_VLIB_GRADIENT_MAGNITUDE_SAT_8BITS)
        {
          vcop_vec_gradients_xy_magnitudeu8_init(
                (uint8_t*)context->pInBlock[BAM_GRADXYMAG_INPUT_PORT],
                (int16_t*)context->pOutBlock[BAM_GRADXYMAG_X_OUTPUT_PORT],
                (int16_t*)context->pOutBlock[BAM_GRADXYMAG_Y_OUTPUT_PORT],
                (uint8_t*)context->pOutBlock[BAM_GRADXYMAG_MAG_OUTPUT_PORT],
                context->kernelArgs.pitch,
                context->kernelArgs.width,
                context->kernelArgs.height,
                (uint16_t*)context->pInternalBlock[PARAMS_IDX]);
          context->kernelCustom = &vcop_vec_gradients_xy_magnitudeu8_vloops;
        }
    }
#endif
    return status;
}

static BAM_Status BAM_gradXYmag_Compute(void *kernelContext)
{
    BAM_GradXYmag_Context *context = (BAM_GradXYmag_Context *) kernelContext;

    /* By the way the function is initialized, it will take a block of kernelArgs.width x kernelArgs.height pixels
     *  and calculate the gradient of of every pixel in the center region of dimension (kernelArgs.width-2)x(kernelArgs.height-2).
     *  The output is however written in a region of dimensions kernelArgs.width x (kernelArgs.height-2), so the last 2 pixels of each output row
     *  must be ignored.
     *  The function may also produce more data if kernelArgs.width x (kernelArgs.height-2) is not multiple of 16. That's why the getMemRec function asks
     *  for a total output size that is rounded up to the next multiple of 16. In any case only the first kernelArgs.width x (kernelArgs.height-2) elements
     *  in the output are to be considered. And within this, the two last pixels of each row of kernelArgs.width pixels must be ignored.
     */
#if (VCOP_HOST_EMULATION)
    if(context->kernelArgs.gradientMethod == EVE_VLIB_GRADIENT_MAGNITUDE_9BITS)
    {
    vcop_vec_gradients_xy_and_magnitude(
            (uint8_t*)context->pInBlock[BAM_GRADXYMAG_INPUT_PORT],
            (int16_t*)context->pOutBlock[BAM_GRADXYMAG_X_OUTPUT_PORT],
            (int16_t*)context->pOutBlock[BAM_GRADXYMAG_Y_OUTPUT_PORT],
            (int16_t*)context->pOutBlock[BAM_GRADXYMAG_MAG_OUTPUT_PORT],
            context->kernelArgs.pitch,
            context->kernelArgs.width,
            context->kernelArgs.height);
    }
    else if(context->kernelArgs.gradientMethod == EVE_VLIB_GRADIENT_MAGNITUDE_SAT_8BITS)
    {
      vcop_vec_gradients_xy_magnitudeu8(
            (uint8_t*)context->pInBlock[BAM_GRADXYMAG_INPUT_PORT],
            (int16_t*)context->pOutBlock[BAM_GRADXYMAG_X_OUTPUT_PORT],
            (int16_t*)context->pOutBlock[BAM_GRADXYMAG_Y_OUTPUT_PORT],
            (uint8_t*)context->pOutBlock[BAM_GRADXYMAG_MAG_OUTPUT_PORT],
            context->kernelArgs.pitch,
            context->kernelArgs.width,
            context->kernelArgs.height);
    }
#else
    context->kernelCustom(context->pInternalBlock[PARAMS_IDX]);
#endif

    return 0;
}

BAM_KernelExecFuncDef gBAM_TI_gradXYmagExecFunc =
{ NULL, &BAM_gradXYmag_initFrame, &BAM_gradXYmag_Compute, NULL, NULL, NULL};
