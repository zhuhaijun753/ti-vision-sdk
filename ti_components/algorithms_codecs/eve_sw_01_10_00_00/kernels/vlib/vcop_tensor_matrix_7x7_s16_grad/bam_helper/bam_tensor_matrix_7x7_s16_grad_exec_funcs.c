/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_tensor_matrix_7x7_s16_grad_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating for kernel that computes
 *              tensor matrix using the 7x7 patch window of signed gradient input into BAM.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_tensor_matrix_7x7_s16_grad_int.h"
#include "bam_tensor_matrix_7x7_s16_grad.h"
#include "vcop_tensor_matrix_7x7_s16_grad_kernel.h" /* compiler should take care of include path */


/* Function Prototypes */
static BAM_Status Bam_Tensor_Matrix_7x7_S16_Grad_initFrame(void *kernelContext);

static BAM_Status Bam_Tensor_Matrix_7x7_S16_Grad_initFrame(void *kernelContext)
{
    BAM_Tensor_Matrix_7x7_S16_Grad_Context *context = (BAM_Tensor_Matrix_7x7_S16_Grad_Context *) kernelContext;
    BAM_Status status = 0;

    /* Return error if assumptions in kernel are not satisfied*/
    if(((context->kernelArgs.n) < 1) || ((context->kernelArgs.stride) < 1)) {
        status = 1;
    }

    if(status == 0) {
      /* CHECK_MISRA("-17.1,-17.4")  -> Disable rule 17.1 and 17.4  */
      /* Pointer is used in arithmetic or array index expression */
      /* Deviation allowed since, this same address needs to be accessed with an offset  */
      vcop_tensor_matrix_7x7_s16_grad_init((int16_t *)context->pInBlock[IN_IDX1],
                               (int16_t *)context->pInBlock[IN_IDX2],
                               context->kernelArgs.stride,
                               context->kernelArgs.n,
                               (int32_t *)context->pOutBlock[OUT_IDX1],
                               (int32_t *)context->pOutBlock[OUT_IDX1] + context->kernelArgs.n,
                               (int32_t *)context->pOutBlock[OUT_IDX1] + (context->kernelArgs.n*2),
                               (int32_t *)context->pInternalBlock[SCRATCH_IDX1],
                               (int32_t *)context->pInternalBlock[SCRATCH_IDX2],
                               (int32_t *)context->pInternalBlock[SCRATCH_IDX3],
                               (uint16_t*)context->pInternalBlock[PARAMS_IDX]);
      /* RESET_MISRA("17.1,17.4")  -> Reset rule 17.1 and 17.4*/
    }

    return status;
}

#ifdef NATC
static BAM_Status Bam_Tensor_Matrix_7x7_S16_Grad_computeFrame(void *kernelContext);

static BAM_Status Bam_Tensor_Matrix_7x7_S16_Grad_computeFrame(void *kernelContext)
{
    BAM_Tensor_Matrix_7x7_S16_Grad_Context *context = (BAM_Tensor_Matrix_7x7_S16_Grad_Context *) kernelContext;
    BAM_Status status = 0;

    vcop_tensor_matrix_7x7_s16_grad_cn((int16_t *)context->pInBlock[IN_IDX1],
                           (int16_t *)context->pInBlock[IN_IDX2],
                           context->kernelArgs.stride,
                           context->kernelArgs.n,
                           (int *)context->pOutBlock[OUT_IDX1],
                           (int *)context->pOutBlock[OUT_IDX1] + context->kernelArgs.n,
                           (int *)context->pOutBlock[OUT_IDX1] + context->kernelArgs.n*2);

    return status;
}
#endif

BAM_KernelExecFuncDef gBAM_TI_tensorMatrix7x7S16GradExecFunc =
#ifdef NATC
    { NULL, &Bam_Tensor_Matrix_7x7_S16_Grad_initFrame, &Bam_Tensor_Matrix_7x7_S16_Grad_computeFrame, NULL, NULL, NULL };
#else
    { NULL, &Bam_Tensor_Matrix_7x7_S16_Grad_initFrame, NULL, NULL, NULL, &vcop_tensor_matrix_7x7_s16_grad_vloops };
#endif
