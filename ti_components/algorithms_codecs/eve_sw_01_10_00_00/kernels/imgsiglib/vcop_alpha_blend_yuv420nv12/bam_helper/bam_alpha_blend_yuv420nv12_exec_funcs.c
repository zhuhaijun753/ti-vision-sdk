/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_alpha_blend_yuv420nv12_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating YUV420 NV12
 *              Alpha Blending function into BAM.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_alpha_blend_yuv420nv12_int.h"
#include "bam_alpha_blend_yuv420nv12.h"
#include "vcop_alpha_blend_yuv420nv12_kernel.h" /* compiler should take care of include path */
#if (NATC)
#include "vcop_alpha_blend_yuv420nv12_cn.h"
#endif

/* Function Prototypes */
static BAM_Status Bam_Alpha_Blend_YUV420nv12_initFrame(void *kernelContext);

static BAM_Status Bam_Alpha_Blend_YUV420nv12_initFrame(void *kernelContext)
{
    BAM_Alpha_Blend_YUV420nv12_Context *context = (BAM_Alpha_Blend_YUV420nv12_Context *) kernelContext;
    BAM_Status status = 0;
#if (!VCOP_HOST_EMULATION && !NATC)
    vcop_alpha_blend_yuv420nv12_init((uint8_t*)context->pInBlock[ALPHA_BLEND_YUV420_IN_IMG1_IDX],
                               (uint8_t*)context->pInBlock[ALPHA_BLEND_YUV420_IN_IMG2_IDX],
                               (uint8_t*)context->pInBlock[ALPHA_BLEND_YUV420_IN_ALPHA_IDX],
                               (uint8_t*)context->pOutBlock[ALPHA_BLEND_YUV420_OUT_IDX],
                               context->kernelArgs.width,
                               context->kernelArgs.height,
                               context->kernelArgs.in_img1_stride,
                               context->kernelArgs.in_img2_stride,
                               context->kernelArgs.out_stride,
                               (uint16_t*)context->pInternalBlock[PARAMS_IDX]);
#endif
    return status;
}

#if (VCOP_HOST_EMULATION || NATC)
static BAM_Status Bam_Alpha_Blend_YUV420nv12_compute(void *kernelContext);

static BAM_Status Bam_Alpha_Blend_YUV420nv12_compute(void *kernelContext)
{
    BAM_Alpha_Blend_YUV420nv12_Context *context = (BAM_Alpha_Blend_YUV420nv12_Context *) kernelContext;

#if (NATC)
    vcop_alpha_blend_yuv420nv12_cn((uint8_t*)context->pInBlock[ALPHA_BLEND_YUV420_IN_IMG1_IDX],
                                   (uint8_t*)context->pInBlock[ALPHA_BLEND_YUV420_IN_IMG2_IDX],
                                   (uint8_t*)context->pInBlock[ALPHA_BLEND_YUV420_IN_ALPHA_IDX],
                                   (uint8_t*)context->pOutBlock[ALPHA_BLEND_YUV420_OUT_IDX],
                                    context->kernelArgs.width,
                                    context->kernelArgs.height,
                                    context->kernelArgs.in_img1_stride,
                                    context->kernelArgs.in_img2_stride,
                                    context->kernelArgs.out_stride);

#else /*if (VCOP_HOST_EMULATION) */
    vcop_alpha_blend_yuv420nv12((uint8_t*)context->pInBlock[ALPHA_BLEND_YUV420_IN_IMG1_IDX],
                               (uint8_t*)context->pInBlock[ALPHA_BLEND_YUV420_IN_IMG2_IDX],
                               (uint8_t*)context->pInBlock[ALPHA_BLEND_YUV420_IN_ALPHA_IDX],
                               (uint8_t*)context->pOutBlock[ALPHA_BLEND_YUV420_OUT_IDX],
                               context->kernelArgs.width,
                               context->kernelArgs.height,
                               context->kernelArgs.in_img1_stride,
                               context->kernelArgs.in_img2_stride,
                               context->kernelArgs.out_stride);
#endif
    return 0;
}
#else
static BAM_Status Bam_Alpha_Blend_YUV420nv12_compute(void *kernelContext);

static BAM_Status Bam_Alpha_Blend_YUV420nv12_compute(void *kernelContext)
{
    BAM_Alpha_Blend_YUV420nv12_Context *context = (BAM_Alpha_Blend_YUV420nv12_Context *) kernelContext;

    vcop_alpha_blend_yuv420nv12_vloops((uint16_t*)context->pInternalBlock[PARAMS_IDX]);

    return 0;
}
#endif



BAM_KernelExecFuncDef gBAM_TI_alphaBlendYUV420nv12ExecFunc =
#if (VCOP_HOST_EMULATION || NATC)
    { NULL, &Bam_Alpha_Blend_YUV420nv12_initFrame, &Bam_Alpha_Blend_YUV420nv12_compute, NULL, NULL, NULL };
#else
    { NULL, &Bam_Alpha_Blend_YUV420nv12_initFrame, &Bam_Alpha_Blend_YUV420nv12_compute, NULL, NULL, &vcop_alpha_blend_yuv420nv12_vloops };
#endif

