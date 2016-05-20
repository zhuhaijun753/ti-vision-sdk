/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_gauss5x5Pyramid_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating block average 2x2 into BAM, used for image pyamid applet.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_gauss5x5Pyramid_8_int.h"
#include "bam_gauss5x5Pyramid_8.h"
#include "vcop_gauss5x5PyramidKernel_8_kernel.h"

/* Function Prototypes */
static BAM_Status BAM_gauss5x5Pyramid_initFrame(void *kernelContext);
static BAM_Status BAM_gauss5x5Pyramid_compute(void *kernelContext);


static BAM_Status BAM_gauss5x5Pyramid_initFrame(void *kernelContext)
{
    BAM_Gauss5x5Pyramid_Context *context = (BAM_Gauss5x5Pyramid_Context *) kernelContext;
    BAM_Status status = 0;

#if !(VCOP_HOST_EMULATION)
        vcop_gauss5x5PyramidKernel_8_horiz_init(
                (uint8_t*)context->pInBlock[BAM_GAUSS5x5PYRAMID_INPUT_PORT],
                (uint8_t*)context->pInternalBlock[PARAMS_TEMP_IDX],
                context->kernelArgs.width, /* width */
                context->kernelArgs.height+4u,
                context->kernelArgs.in_stride, /* inPitch */
                context->kernelArgs.width/2u, /* outPitch */
                (uint16_t *)context->pInternalBlock[PARAMS_H_IDX]);

        vcop_gauss5x5PyramidKernel_8_vert_init(
                (uint8_t*)context->pInternalBlock[PARAMS_TEMP_IDX],
                (uint8_t*)context->pOutBlock[BAM_GAUSS5x5PYRAMID_OUTPUT_PORT],
                context->kernelArgs.width/2u, /* width */
                context->kernelArgs.height,
                context->kernelArgs.width/2u,
                context->kernelArgs.out_stride,
                (uint16_t *)context->pInternalBlock[PARAMS_V_IDX]);
#endif
    return status;
}

#if (VCOP_HOST_EMULATION)
static BAM_Status BAM_gauss5x5Pyramid_compute(void *kernelContext)
{
    BAM_Gauss5x5Pyramid_Context *context = (BAM_Gauss5x5Pyramid_Context *) kernelContext;
    uint32_t BAM_Status = 0;

    vcop_gauss5x5PyramidKernel_8_horiz(
            (uint8_t*)context->pInBlock[BAM_GAUSS5x5PYRAMID_INPUT_PORT],
            (uint8_t*)context->pInternalBlock[PARAMS_TEMP_IDX],
            context->kernelArgs.width, /* width */
            context->kernelArgs.height+4,
            context->kernelArgs.in_stride, /* inPitch */
            context->kernelArgs.width/2 /* outPitch */
    );

    vcop_gauss5x5PyramidKernel_8_vert(
            (uint8_t*)context->pInternalBlock[PARAMS_TEMP_IDX],
            (uint8_t*)context->pOutBlock[BAM_GAUSS5x5PYRAMID_OUTPUT_PORT],
            context->kernelArgs.width/2, /* width */
            context->kernelArgs.height,
            context->kernelArgs.width/2,
            context->kernelArgs.out_stride
    );

    return 0;
}

#else

static BAM_Status BAM_gauss5x5Pyramid_compute(void *kernelContext)
{
    BAM_Gauss5x5Pyramid_Context *context = (BAM_Gauss5x5Pyramid_Context *) kernelContext;

    vcop_gauss5x5PyramidKernel_8_horiz_vloops((uint16_t *)context->pInternalBlock[PARAMS_H_IDX]);
    vcop_gauss5x5PyramidKernel_8_vert_vloops((uint16_t *)context->pInternalBlock[PARAMS_V_IDX]);

    return 0;
}

#endif


BAM_KernelExecFuncDef gBAM_TI_gauss5x5PyramidExecFunc =
{ NULL, &BAM_gauss5x5Pyramid_initFrame, &BAM_gauss5x5Pyramid_compute, NULL, NULL, NULL};


