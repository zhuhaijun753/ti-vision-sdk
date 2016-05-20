/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_intensity_scaling_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating intensity
 *              scaling function into BAM.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_intensity_scaling_int.h"
#include "vcop_intensity_scaling.h"
#include "vcop_intensity_scaling_kernel.h" /* compiler should take care of include path */

/* Function Prototypes */
static BAM_Status Bam_Intensity_scaling_initFrame(void *kernelContext);

static BAM_Status Bam_Intensity_scaling_initFrame(void *kernelContext)
{
    BAM_Intensity_scaling_Context *context = (BAM_Intensity_scaling_Context *) kernelContext;

#if (!VCOP_HOST_EMULATION)
    vcop_intensity_scaling_init((uint8_t*)context->pInBlock[IN_IMG_IDX],
                               (uint8_t*)context->pInternalBlock[LUT_IDX],
                               (uint8_t*)context->pOutBlock[OUT_IMG_IDX],
                               context->kernelArgs.blockWidth,
                               context->kernelArgs.blockHeight,
                               context->kernelArgs.blockStride,
                               (uint16_t*)context->pInternalBlock[PARAMS_IDX]);
#endif

    /* Prepare LUT for intensity scaling */
    prepare_lut(context->kernelArgs.loPixelVal, context->kernelArgs.hiPixelVal,
        context->kernelArgs.numLevels, NUM_SCALING_TBLS,
        (uint8_t*)context->pInternalBlock[LUT_IDX]);

    return 0;
}

#if VCOP_HOST_EMULATION
static BAM_Status Bam_Intensity_scaling_computeFrame(void *kernelContext)
{
    BAM_Intensity_scaling_Context *context = (BAM_Intensity_scaling_Context *) kernelContext;

    vcop_intensity_scaling((uint8_t*)context->pInBlock[IN_IMG_IDX],
                           (uint8_t*)context->pInternalBlock[LUT_IDX],
                           (uint8_t*)context->pOutBlock[OUT_IMG_IDX],
                           context->kernelArgs.blockWidth,
                           context->kernelArgs.blockHeight,
                           context->kernelArgs.blockStride);
    return 0;

}
#endif


BAM_KernelExecFuncDef gBAM_TI_intensityScalingExecFunc =
#if VCOP_HOST_EMULATION
    { NULL, &Bam_Intensity_scaling_initFrame, Bam_Intensity_scaling_computeFrame, NULL, NULL, NULL };
#else
    { NULL, &Bam_Intensity_scaling_initFrame, NULL, NULL, NULL, &vcop_intensity_scaling_vloops };
#endif

