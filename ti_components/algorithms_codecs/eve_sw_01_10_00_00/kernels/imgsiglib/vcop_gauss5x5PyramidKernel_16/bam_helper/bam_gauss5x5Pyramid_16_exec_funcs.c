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

#include "bam_gauss5x5Pyramid_16_int.h"
#include "bam_gauss5x5Pyramid_16.h"
#include "vcop_gauss5x5PyramidKernel_16_kernel.h"

/* Function Prototypes */
static BAM_Status BAM_gauss5x5Pyramid16_initFrame(void *kernelContext);
static BAM_Status BAM_gauss5x5Pyramid16_compute(void *kernelContext);

static BAM_Status BAM_gauss5x5Pyramid16_initFrame(void *kernelContext)
{
    BAM_Gauss5x5Pyramid16_Context *context = (BAM_Gauss5x5Pyramid16_Context *) kernelContext;
    BAM_Status status = 0;

#if !(VCOP_HOST_EMULATION)
    vcop_gauss5x5PyramidKernel_16_horiz_init(
            (uint16_t*)context->pInBlock[BAM_GAUSS5x5PYRAMID_INPUT_PORT],
            (uint16_t*)context->pInternalBlock[PARAMS_TEMP_IDX],
            context->kernelArgs.width, /* width */
            context->kernelArgs.height+4u,
            context->kernelArgs.in_stride, /* inPitch */
            context->kernelArgs.width/2u, /* outPitch */
            (uint16_t *)context->pInternalBlock[PARAMS_H_IDX]);

    vcop_gauss5x5PyramidKernel_16_vert_init(
            (uint16_t*)context->pInternalBlock[PARAMS_TEMP_IDX],
            (uint16_t*)context->pOutBlock[BAM_GAUSS5x5PYRAMID_OUTPUT_PORT],
            context->kernelArgs.width/2u, /* width */
            context->kernelArgs.height,
            context->kernelArgs.width/2u,
            context->kernelArgs.out_stride,
            (uint16_t *)context->pInternalBlock[PARAMS_V_IDX]);

#endif
    return status;
}

#if (VCOP_HOST_EMULATION)
static BAM_Status BAM_gauss5x5Pyramid16_compute(void *kernelContext)
{
    BAM_Gauss5x5Pyramid16_Context *context = (BAM_Gauss5x5Pyramid16_Context *) kernelContext;
    BAM_Status status = 0;

    vcop_gauss5x5PyramidKernel_16_horiz(
            (uint16_t*)context->pInBlock[BAM_GAUSS5x5PYRAMID_INPUT_PORT],
            (uint16_t*)context->pInternalBlock[PARAMS_TEMP_IDX],
            context->kernelArgs.width, /* width */
            context->kernelArgs.height+4u,
            context->kernelArgs.in_stride, /* inPitch */
            context->kernelArgs.width/2u /* outPitch */
    );

    vcop_gauss5x5PyramidKernel_16_vert(
            (uint16_t*)context->pInternalBlock[PARAMS_TEMP_IDX],
            (uint16_t*)context->pOutBlock[BAM_GAUSS5x5PYRAMID_OUTPUT_PORT],
            context->kernelArgs.width/2u, /* width */
            context->kernelArgs.height,
            context->kernelArgs.width/2u,
            context->kernelArgs.out_stride
    );

    return 0;
}

#else

static BAM_Status BAM_gauss5x5Pyramid16_compute(void *kernelContext)
{
    BAM_Gauss5x5Pyramid16_Context *context = (BAM_Gauss5x5Pyramid16_Context *) kernelContext;

    vcop_gauss5x5PyramidKernel_16_horiz_vloops((uint16_t *)context->pInternalBlock[PARAMS_H_IDX]);
    vcop_gauss5x5PyramidKernel_16_vert_vloops((uint16_t *)context->pInternalBlock[PARAMS_V_IDX]);

    return 0;
}

#endif


BAM_KernelExecFuncDef gBAM_TI_gauss5x5Pyramid16ExecFunc =
{ NULL, &BAM_gauss5x5Pyramid16_initFrame, &BAM_gauss5x5Pyramid16_compute, NULL, NULL, NULL};


