/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_yuv_422uyvy_to_420nv12_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating YUV422 UYVY
 *              to YUV420 NV12 format conversion function into BAM.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_yuv_422uyvy_to_420nv12_int.h"
#include "bam_yuv_422uyvy_to_420nv12.h"
#include "vcop_yuv_422uyvy_to_420nv12_kernel.h" /* compiler should take care of include path */
#if (NATC)
#include "vcop_yuv_422uyvy_to_420nv12_cn.h"
#endif

/* Function Prototypes */
static BAM_Status Bam_Yuv_422uyvy_to_420nv12_initFrame(void *kernelContext);

static BAM_Status Bam_Yuv_422uyvy_to_420nv12_initFrame(void *kernelContext)
{
    BAM_Yuv_422uyvy_to_420nv12_Context *context = (BAM_Yuv_422uyvy_to_420nv12_Context *) kernelContext;
    BAM_Status status = 0;
#if (!VCOP_HOST_EMULATION && !NATC)
    vcop_yuv_422uyvy_to_420nv12_init((uint8_t*)context->pInBlock[YUV_422UYVY_TO_420NV12_IN_IMG_IDX],
                               (uint8_t*)context->pOutBlock[YUV_422UYVY_TO_420NV12_OUT_IDX],
                               context->kernelArgs.width,
                               context->kernelArgs.height,
                               context->kernelArgs.in_stride,
                               context->kernelArgs.out_stride,
                               (uint16_t*)context->pInternalBlock[PARAMS_IDX]);
#endif
    return status;
}

#if (VCOP_HOST_EMULATION || NATC)
static BAM_Status Bam_Yuv_422uyvy_to_420nv12_compute(void *kernelContext);

static BAM_Status Bam_Yuv_422uyvy_to_420nv12_compute(void *kernelContext)
{
    BAM_Yuv_422uyvy_to_420nv12_Context *context = (BAM_Yuv_422uyvy_to_420nv12_Context *) kernelContext;

#if (NATC)
    vcop_yuv_422uyvy_to_420nv12_cn((uint8_t*)context->pInBlock[YUV_422UYVY_TO_420NV12_IN_IMG_IDX],
                               (uint8_t*)context->pOutBlock[YUV_422UYVY_TO_420NV12_OUT_IDX],
                               context->kernelArgs.width,
                               context->kernelArgs.height,
                               context->kernelArgs.in_stride,
                               context->kernelArgs.out_stride);

#else /*if (VCOP_HOST_EMULATION) */
    vcop_yuv_422uyvy_to_420nv12((uint8_t*)context->pInBlock[YUV_422UYVY_TO_420NV12_IN_IMG_IDX],
                               (uint8_t*)context->pOutBlock[YUV_422UYVY_TO_420NV12_OUT_IDX],
                               context->kernelArgs.width,
                               context->kernelArgs.height,
                               context->kernelArgs.in_stride,
                               context->kernelArgs.out_stride);
#endif
    return 0;
}
#else
static BAM_Status Bam_Yuv_422uyvy_to_420nv12_compute(void *kernelContext);

static BAM_Status Bam_Yuv_422uyvy_to_420nv12_compute(void *kernelContext)
{
    BAM_Yuv_422uyvy_to_420nv12_Context *context = (BAM_Yuv_422uyvy_to_420nv12_Context *) kernelContext;
    vcop_yuv_422uyvy_to_420nv12_vloops((uint16_t*)context->pInternalBlock[PARAMS_IDX]);
    return 0;
}

#endif
BAM_KernelExecFuncDef gBAM_TI_yuv422uyvy_to_420nv12ExecFunc =
#if (VCOP_HOST_EMULATION || NATC)
    { NULL, &Bam_Yuv_422uyvy_to_420nv12_initFrame, &Bam_Yuv_422uyvy_to_420nv12_compute, NULL, NULL, NULL };
#else
    { NULL, &Bam_Yuv_422uyvy_to_420nv12_initFrame, &Bam_Yuv_422uyvy_to_420nv12_compute, NULL, NULL, &vcop_yuv_422uyvy_to_420nv12_vloops };
#endif

