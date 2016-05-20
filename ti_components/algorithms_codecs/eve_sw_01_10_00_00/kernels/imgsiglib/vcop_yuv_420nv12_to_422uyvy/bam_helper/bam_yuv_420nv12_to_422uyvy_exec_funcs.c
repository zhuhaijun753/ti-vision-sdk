/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_yuv_420nv12_to_422uyvy_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating YUV420 NV12
 *              to YUV422 UYVY format conversion function into BAM.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_yuv_420nv12_to_422uyvy_int.h"
#include "bam_yuv_420nv12_to_422uyvy.h"
#include "vcop_yuv_420nv12_to_422uyvy_kernel.h" /* compiler should take care of include path */
#if (NATC)
#include "vcop_yuv_420nv12_to_422uyvy_cn.h"
#endif

/* Function Prototypes */
static BAM_Status Bam_Yuv_420nv12_to_422uyvy_initFrame(void *kernelContext);

static BAM_Status Bam_Yuv_420nv12_to_422uyvy_initFrame(void *kernelContext)
{
    BAM_Yuv_420nv12_to_422uyvy_Context *context = (BAM_Yuv_420nv12_to_422uyvy_Context *) kernelContext;
    BAM_Status status = 0;
#if (!VCOP_HOST_EMULATION && !NATC)
    vcop_yuv_420nv12_to_422uyvy_init((uint8_t*)context->pInBlock[YUV_420NV12_TO_422UYVY_IN_IMG_IDX],
                               (uint8_t*)context->pOutBlock[YUV_420NV12_TO_422UYVY_OUT_IDX],
                               context->kernelArgs.width,
                               context->kernelArgs.height,
                               context->kernelArgs.in_stride,
                               context->kernelArgs.out_stride,
                               (uint16_t*)context->pInternalBlock[PARAMS_IDX]);
#endif
    return status;
}

#if (VCOP_HOST_EMULATION || NATC)
static BAM_Status Bam_Yuv_420nv12_to_422uyvy_compute(void *kernelContext);

static BAM_Status Bam_Yuv_420nv12_to_422uyvy_compute(void *kernelContext)
{
    BAM_Yuv_420nv12_to_422uyvy_Context *context = (BAM_Yuv_420nv12_to_422uyvy_Context *) kernelContext;

#if (NATC)
    vcop_yuv_420nv12_to_422uyvy_cn((uint8_t*)context->pInBlock[YUV_420NV12_TO_422UYVY_IN_IMG_IDX],
                               (uint8_t*)context->pOutBlock[YUV_420NV12_TO_422UYVY_OUT_IDX],
                               context->kernelArgs.width,
                               context->kernelArgs.height,
                               context->kernelArgs.in_stride,
                               context->kernelArgs.out_stride);

#else /*if (VCOP_HOST_EMULATION) */
    vcop_yuv_420nv12_to_422uyvy((uint8_t*)context->pInBlock[YUV_420NV12_TO_422UYVY_IN_IMG_IDX],
                               (uint8_t*)context->pOutBlock[YUV_420NV12_TO_422UYVY_OUT_IDX],
                               context->kernelArgs.width,
                               context->kernelArgs.height,
                               context->kernelArgs.in_stride,
                               context->kernelArgs.out_stride);
#endif
    return 0;
}
#else
static BAM_Status Bam_Yuv_420nv12_to_422uyvy_compute(void *kernelContext);

static BAM_Status Bam_Yuv_420nv12_to_422uyvy_compute(void *kernelContext)
{
    BAM_Yuv_420nv12_to_422uyvy_Context *context = (BAM_Yuv_420nv12_to_422uyvy_Context *) kernelContext;
    vcop_yuv_420nv12_to_422uyvy_vloops((uint16_t*)context->pInternalBlock[0]);
    return 0;
}
#endif


BAM_KernelExecFuncDef gBAM_TI_yuv420nv12_to_422uyvyExecFunc =
#if (VCOP_HOST_EMULATION || NATC)
    { NULL, &Bam_Yuv_420nv12_to_422uyvy_initFrame, &Bam_Yuv_420nv12_to_422uyvy_compute, NULL, NULL, NULL };
#else
    { NULL, &Bam_Yuv_420nv12_to_422uyvy_initFrame, &Bam_Yuv_420nv12_to_422uyvy_compute, NULL, NULL, &vcop_yuv_420nv12_to_422uyvy_vloops };
#endif

