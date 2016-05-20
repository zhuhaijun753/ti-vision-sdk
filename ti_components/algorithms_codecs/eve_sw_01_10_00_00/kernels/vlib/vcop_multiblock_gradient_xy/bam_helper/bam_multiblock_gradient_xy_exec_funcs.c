/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_multiblock_gradient_xy_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating for multi block gradient
 *              XY compute kernel function into BAM.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_multiblock_gradient_xy_int.h"
#include "bam_multiblock_gradient_xy.h"
#include "vcop_multiblock_gradient_xy_kernel.h" /* compiler should take care of include path */
#include "vcop_multiblock_gradient_xy_cn.h"

/* Function Prototypes */
static BAM_Status Bam_Multiblock_Gradient_XY_initFrame(void *kernelContext);

static BAM_Status Bam_Multiblock_Gradient_XY_initFrame(void *kernelContext)
{
    BAM_Multiblock_Gradient_XY_Context *context = (BAM_Multiblock_Gradient_XY_Context *) kernelContext;
    BAM_Status status = 0;

    /* Return error if assumptions in kernel are not satisfied*/
    if((context->kernelArgs.inputStride < (context->kernelArgs.numBlocks*context->kernelArgs.blkOffset)) ||
        ((context->kernelArgs.blkWidth) < 1) || ((context->kernelArgs.blkHeight) < 1) ||
        ((context->kernelArgs.numBlocks) < 1)) {
        status = 1;
    }

    if(status == 0) {
        vcop_multiblock_gradient_xy_init((uint8_t*)context->pInBlock[IN_IDX],
                               (int16_t*)context->pOutBlock[OUT_IDX],
                               context->kernelArgs.inputStride,
                               context->kernelArgs.blkWidth,
                               context->kernelArgs.blkHeight,
                               context->kernelArgs.blkOffset,
                               context->kernelArgs.numBlocks,
                               (uint16_t*)context->pInternalBlock[PARAMS_IDX]);
    }

    return status;
}

#ifdef NATC
static BAM_Status Bam_Multiblock_Gradient_XY_computeFrame(void *kernelContext);

static BAM_Status Bam_Multiblock_Gradient_XY_computeFrame(void *kernelContext)
{
    BAM_Multiblock_Gradient_XY_Context *context = (BAM_Multiblock_Gradient_XY_Context *) kernelContext;
    BAM_Status status = 0;

    vcop_multiblock_gradient_xy_cn((uint8_t*)context->pInBlock[IN_IDX],
                           (int16_t*)context->pOutBlock[OUT_IDX],
                           context->kernelArgs.inputStride,
                           context->kernelArgs.blkWidth,
                           context->kernelArgs.blkHeight,
                           context->kernelArgs.blkOffset,
                           context->kernelArgs.numBlocks);

    return status;

}
#endif

BAM_KernelExecFuncDef gBAM_TI_multiblockGradientXYExecFunc =
#ifdef NATC
    { NULL, &Bam_Multiblock_Gradient_XY_initFrame, &Bam_Multiblock_Gradient_XY_computeFrame, NULL, NULL, NULL };
#else
    { NULL, &Bam_Multiblock_Gradient_XY_initFrame, NULL, NULL, NULL, &vcop_multiblock_gradient_xy_vloops };
#endif
