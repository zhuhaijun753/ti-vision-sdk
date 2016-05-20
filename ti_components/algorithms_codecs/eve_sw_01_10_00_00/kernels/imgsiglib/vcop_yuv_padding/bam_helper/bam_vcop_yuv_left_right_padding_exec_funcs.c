/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_vcop_yuv_left_right_padding_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating YUV padding
 *              function into BAM.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_vcop_yuv_left_right_padding_int.h"
#include "bam_vcop_yuv_left_right_padding.h"
#include "vcop_yuv_left_right_padding_kernel.h" /* compiler should take care of include path */

/* Function Prototypes */
static BAM_Status Bam_yuvLeftRightPadding_initFrame(void *kernelContext);

static BAM_Status Bam_yuvLeftRightPadding_initFrame(void *kernelContext)
{
    BAM_yuvLeftRightPadding_Context *context = (BAM_yuvLeftRightPadding_Context *) kernelContext;
    BAM_Status status = 0;
#if (!VCOP_HOST_EMULATION)
    status = (BAM_Status)vcop_yuv_left_right_padding_u8_init((uint8_t*)context->pInBlock[IN_LEFT_IDX],
                               (uint8_t*)context->pInBlock[IN_RIGHT_IDX],
                               (uint8_t*)context->pOutBlock[OUT_LEFT_IDX],
                               (uint8_t*)context->pOutBlock[OUT_RIGHT_IDX],
                               context->kernelArgs.width,
                               context->kernelArgs.height,
                               context->kernelArgs.out_stride,
                               (uint16_t*)context->pInternalBlock[PARAMS_IDX1]);
    status = (BAM_Status)vcop_yuv_left_right_padding_u16_init((uint16_t*)context->pInBlock[IN_CHROMA_LEFT_IDX],
                               (uint16_t*)context->pInBlock[IN_CHROMA_RIGHT_IDX],
                               (uint16_t*)context->pOutBlock[OUT_CHROMA_LEFT_IDX],
                               (uint16_t*)context->pOutBlock[OUT_CHROMA_RIGHT_IDX],
                               context->kernelArgs.width/2U,
                               context->kernelArgs.height/2U,
                               context->kernelArgs.out_stride/2U,
                               (uint16_t*)context->pInternalBlock[PARAMS_IDX2]);
#endif
    return status;
}

static BAM_Status Bam_yuvLeftRightPadding_compute(void *kernelContext);

static BAM_Status Bam_yuvLeftRightPadding_compute(void *kernelContext)
{
    BAM_yuvLeftRightPadding_Context *context = (BAM_yuvLeftRightPadding_Context *) kernelContext;

#if (VCOP_HOST_EMULATION)
    vcop_yuv_left_right_padding_u8((uint8_t*)context->pInBlock[IN_LEFT_IDX],
                               (uint8_t*)context->pInBlock[IN_RIGHT_IDX],
                               (uint8_t*)context->pOutBlock[OUT_LEFT_IDX],
                               (uint8_t*)context->pOutBlock[OUT_RIGHT_IDX],
                               context->kernelArgs.width,
                               context->kernelArgs.height,
                               context->kernelArgs.out_stride);

    vcop_yuv_left_right_padding_u16((uint16_t*)context->pInBlock[IN_CHROMA_LEFT_IDX],
                               (uint16_t*)context->pInBlock[IN_CHROMA_RIGHT_IDX],
                               (uint16_t*)context->pOutBlock[OUT_CHROMA_LEFT_IDX],
                               (uint16_t*)context->pOutBlock[OUT_CHROMA_RIGHT_IDX],
                               context->kernelArgs.width/2,
                               context->kernelArgs.height/2,
                               context->kernelArgs.out_stride/2);
#else
    vcop_yuv_left_right_padding_u8_vloops((uint16_t*)context->pInternalBlock[PARAMS_IDX1]);
    vcop_yuv_left_right_padding_u16_vloops((uint16_t*)context->pInternalBlock[PARAMS_IDX2]);
#endif
    return 0;
}

BAM_KernelExecFuncDef gBAM_TI_yuvLeftRightPaddingExecFunc =
    { NULL, &Bam_yuvLeftRightPadding_initFrame, &Bam_yuvLeftRightPadding_compute, NULL, NULL, NULL };

