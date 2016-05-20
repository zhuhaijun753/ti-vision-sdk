/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_vcop_yuv420_fir2d_separable.c
 *
 *  @brief      This file defines interfaces for integrating YUV420 separable filter
 *              into BAM
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_yuv420_fir2d_separable_int.h"
#include "bam_yuv420_fir2d_separable.h"
#include "vcop_yuv420_fir2d_separable_kernel.h"

/* Function Prototypes */
static BAM_Status BAM_Yuv420_fir2dseparable_Y_initFrame(void *kernelContext);

static BAM_Status BAM_Yuv420_fir2dseparable_Y_initFrame(void *kernelContext)
{
    BAM_Yuv420_fir2dseparable_Context *context = (BAM_Yuv420_fir2dseparable_Context *) kernelContext;
    BAM_Status status = 0;

    memcpy(context->pInternalBlock[YUV420_FIR2D_SEPARABLE_INTERNAL_COEF_HORZ_IDX],
           (*context->kernelArgs.coefPtr),
           context->kernelArgs.coefWidth);

    memcpy(context->pInternalBlock[YUV420_FIR2D_SEPARABLE_INTERNAL_COEF_VERT_IDX],
           &(*context->kernelArgs.coefPtr)[context->kernelArgs.coefWidth],
           context->kernelArgs.coefHeight);

#if (!VCOP_HOST_EMULATION)
    vcop_yuv420_fir2d_separable_y_init((uint8_t *)context->pInBlock[YUV420_FIR2D_SEPARABLE_IN_IDX],
                    (int16_t *)context->pInternalBlock[YUV420_FIR2D_SEPARABLE_INTERNAL_INTERM_IDX],
                    (char *)context->pInternalBlock[YUV420_FIR2D_SEPARABLE_INTERNAL_COEF_HORZ_IDX],
                    (char *)context->pInternalBlock[YUV420_FIR2D_SEPARABLE_INTERNAL_COEF_VERT_IDX],
                    context->kernelArgs.blockWidth,
                    context->kernelArgs.pitch,
                    context->kernelArgs.blockHeight,
                    /* For separable filter coefWidth and coefHeight should be same */
                    context->kernelArgs.coefWidth,
                    (uint8_t *)context->pOutBlock[YUV420_FIR2D_SEPARABLE_OUT_IDX],
                    context->kernelArgs.rndBits,
                    context->pInternalBlock[YUV420_FIR2D_SEPARABLE_INTERNAL_PARAMS_IDX]);
#endif

    return status;
}

#if (VCOP_HOST_EMULATION)
static BAM_Status BAM_Yuv420_fir2dseparable_Y_compute(void *kernelContext);

static BAM_Status BAM_Yuv420_fir2dseparable_Y_compute(void *kernelContext)
{
    BAM_Yuv420_fir2dseparable_Context *context = (BAM_Yuv420_fir2dseparable_Context *) kernelContext;
    BAM_Status status = 0;

    vcop_yuv420_fir2d_separable_y((uint8_t *)context->pInBlock[YUV420_FIR2D_SEPARABLE_IN_IDX],
                    (int16_t *)context->pInternalBlock[YUV420_FIR2D_SEPARABLE_INTERNAL_INTERM_IDX],
                    (char *)context->pInternalBlock[YUV420_FIR2D_SEPARABLE_INTERNAL_COEF_HORZ_IDX],
                    (char *)context->pInternalBlock[YUV420_FIR2D_SEPARABLE_INTERNAL_COEF_VERT_IDX],
                    context->kernelArgs.blockWidth,
                    context->kernelArgs.pitch,
                    context->kernelArgs.blockHeight,
                    /* For separable filter coefWidth and coefHeight should be same */
                    context->kernelArgs.coefWidth,
                    (uint8_t *)context->pOutBlock[YUV420_FIR2D_SEPARABLE_OUT_IDX],
                    context->kernelArgs.rndBits);

    return status;
}
#endif

static BAM_Status BAM_Yuv420_fir2dseparable_UV_initFrame(void *kernelContext);

static BAM_Status BAM_Yuv420_fir2dseparable_UV_initFrame(void *kernelContext)
{
    BAM_Yuv420_fir2dseparable_Context *context = (BAM_Yuv420_fir2dseparable_Context *) kernelContext;
    BAM_Status status = 0;

    memcpy(context->pInternalBlock[YUV420_FIR2D_SEPARABLE_INTERNAL_COEF_HORZ_IDX],
           (*context->kernelArgs.coefPtr),
           context->kernelArgs.coefWidth);

    memcpy(context->pInternalBlock[YUV420_FIR2D_SEPARABLE_INTERNAL_COEF_VERT_IDX],
           &(*context->kernelArgs.coefPtr)[context->kernelArgs.coefWidth],
           context->kernelArgs.coefHeight);

#if (!VCOP_HOST_EMULATION)
    vcop_yuv420_fir2d_separable_uv_init((uint8_t *)context->pInBlock[YUV420_FIR2D_SEPARABLE_IN_IDX],
                    (int16_t *)context->pInternalBlock[YUV420_FIR2D_SEPARABLE_INTERNAL_INTERM_IDX],
                    (char *)context->pInternalBlock[YUV420_FIR2D_SEPARABLE_INTERNAL_COEF_HORZ_IDX],
                    (char *)context->pInternalBlock[YUV420_FIR2D_SEPARABLE_INTERNAL_COEF_VERT_IDX],
                    context->kernelArgs.blockWidth,
                    context->kernelArgs.pitch,
                    context->kernelArgs.blockHeight,
                    /* For separable filter coefWidth and coefHeight should be same */
                    context->kernelArgs.coefWidth,
                    (uint8_t *)context->pOutBlock[YUV420_FIR2D_SEPARABLE_OUT_IDX],
                    context->kernelArgs.rndBits,
                    context->pInternalBlock[YUV420_FIR2D_SEPARABLE_INTERNAL_PARAMS_IDX]);
#endif

    return status;
}

#if (VCOP_HOST_EMULATION)
static BAM_Status BAM_Yuv420_fir2dseparable_UV_compute(void *kernelContext);

static BAM_Status BAM_Yuv420_fir2dseparable_UV_compute(void *kernelContext)
{
    BAM_Yuv420_fir2dseparable_Context *context = (BAM_Yuv420_fir2dseparable_Context *) kernelContext;
    BAM_Status status = 0;

    vcop_yuv420_fir2d_separable_uv((uint8_t *)context->pInBlock[YUV420_FIR2D_SEPARABLE_IN_IDX],
                    (int16_t *)context->pInternalBlock[YUV420_FIR2D_SEPARABLE_INTERNAL_INTERM_IDX],
                    (char *)context->pInternalBlock[YUV420_FIR2D_SEPARABLE_INTERNAL_COEF_HORZ_IDX],
                    (char *)context->pInternalBlock[YUV420_FIR2D_SEPARABLE_INTERNAL_COEF_VERT_IDX],
                    context->kernelArgs.blockWidth,
                    context->kernelArgs.pitch,
                    context->kernelArgs.blockHeight,
                    /* For separable filter coefWidth and coefHeight should be same */
                    context->kernelArgs.coefWidth,
                    (uint8_t *)context->pOutBlock[YUV420_FIR2D_SEPARABLE_OUT_IDX],
                    context->kernelArgs.rndBits);

    return status;
}
#endif

BAM_KernelExecFuncDef gBAM_TI_yuv420Fir2dSeparableYExecFunc =
#if (!VCOP_HOST_EMULATION)
    { NULL,
      &BAM_Yuv420_fir2dseparable_Y_initFrame,
      NULL,
      NULL,
      NULL,
      &vcop_yuv420_fir2d_separable_y_vloops };
#else
    { NULL,
      &BAM_Yuv420_fir2dseparable_Y_initFrame,
      &BAM_Yuv420_fir2dseparable_Y_compute,
      NULL,
      NULL,
      NULL };
#endif


BAM_KernelExecFuncDef gBAM_TI_yuv420Fir2dSeparableUvExecFunc =
#if (!VCOP_HOST_EMULATION)
    { NULL,
      &BAM_Yuv420_fir2dseparable_UV_initFrame,
      NULL,
      NULL,
      NULL,
      &vcop_yuv420_fir2d_separable_uv_vloops };
#else
    { NULL,
      &BAM_Yuv420_fir2dseparable_UV_initFrame,
      &BAM_Yuv420_fir2dseparable_UV_compute,
      NULL,
      NULL,
      NULL };
#endif


