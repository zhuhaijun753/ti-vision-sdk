/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_calc_determinant_tensor_matrix_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating for kernel that computes
 *              determinant of the tensor matrix into BAM.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_calc_determinant_tensor_matrix_int.h"
#include "bam_calc_determinant_tensor_matrix.h"
#include "vcop_calc_determinant_tensor_matrix_kernel.h" /* compiler should take care of include path */
#include "vcop_calc_determinant_tensor_matrix_cn.h"

/* Function Prototypes */
static BAM_Status Bam_Calc_Determinant_Tensor_Matrix_initFrame(void *kernelContext);

static BAM_Status Bam_Calc_Determinant_Tensor_Matrix_initFrame(void *kernelContext)
{
    BAM_Calc_Determinant_Tensor_Matrix_Context *context = (BAM_Calc_Determinant_Tensor_Matrix_Context *) kernelContext;
    BAM_Status status = 0;
    uint32_t nValue = (uint32_t)context->kernelArgs.n;
    /* Return error if assumptions in kernel are not satisfied*/ 
    if(((context->kernelArgs.n) < 1)) {
        status = 1;
    }

    if(status == 0) {
        uint8_t * inAddr1;
        uint8_t * inAddr2;
        uint8_t * inAddr3;
        uint8_t * inAddr4;
        uint8_t * inAddr5;

        /* CHECK_MISRA("-17.1,-17.4")  -> Disable rule 17.1 and 17.4  */
        /* Pointer is used in arithmetic or array index expression */
        /* Deviation allowed since, the same addrees (32 bit element ) */
        /* needs to be accesed as two 16 bit elements seperatly  */
        inAddr1 = (uint8_t *)context->pInBlock[IN_IDX2] + (nValue*(uint32_t)4);
        inAddr2 = (uint8_t *)context->pInBlock[IN_IDX3] + (nValue*(uint32_t)4*(uint32_t)2);
        inAddr3 = (uint8_t *)context->pInBlock[IN_IDX1] + (uint32_t)2;
        inAddr4 = (uint8_t *)context->pInBlock[IN_IDX2] + (uint32_t)2 + (nValue*(uint32_t)4);
        inAddr5 = (uint8_t *)context->pInBlock[IN_IDX3] + (uint32_t)2 + (nValue*(uint32_t)4*(uint32_t)2);
        vcop_calc_determinant_tensor_matrix_init(
                               (uint16_t *)((context->pInBlock[IN_IDX1])),
                               (uint16_t *)(void*)(inAddr1),
                               (uint16_t *)(void*)(inAddr2),
                               (int16_t *) (void*)(inAddr3),
                               (int16_t *) (void*)(inAddr4),
                               (int16_t *) (void*)(inAddr5),
                               (uint16_t *)context->pOutBlock[OUT_IDX1],
                               (int32_t *)context->pOutBlock[OUT_IDX2],
                               context->kernelArgs.n,
                               (uint16_t*)context->pInternalBlock[PARAMS_IDX]);
        /* RESET_MISRA("17.1,17.4")  -> Reset rule 17.1 and 17.4*/
    }

    return status;
}

#ifdef NATC
static BAM_Status Bam_Calc_Determinant_Tensor_Matrix_computeFrame(void *kernelContext);

static BAM_Status Bam_Calc_Determinant_Tensor_Matrix_computeFrame(void *kernelContext)
{
    BAM_Calc_Determinant_Tensor_Matrix_Context *context = (BAM_Calc_Determinant_Tensor_Matrix_Context *) kernelContext;
    BAM_Status status = 0;

    vcop_calc_determinant_tensor_matrix_cn(
                           (int *)(((uint32_t)context->pInBlock[IN_IDX1])),
                           (int *)(((uint32_t)context->pInBlock[IN_IDX2]) + context->kernelArgs.n*4),
                           (int *)(((uint32_t)context->pInBlock[IN_IDX3]) + context->kernelArgs.n*4*2),
                           (uint16_t *)context->pOutBlock[OUT_IDX1],
                           (int *)context->pOutBlock[OUT_IDX2],
                           context->kernelArgs.n);

    return status;
}
#endif

BAM_KernelExecFuncDef gBAM_TI_calcDeterminantTensorMatrixExecFunc =
#ifdef NATC
    { NULL, &Bam_Calc_Determinant_Tensor_Matrix_initFrame, &Bam_Calc_Determinant_Tensor_Matrix_computeFrame, NULL, NULL, NULL };
#else
    { NULL, &Bam_Calc_Determinant_Tensor_Matrix_initFrame, NULL, NULL, NULL, &vcop_calc_determinant_tensor_matrix_vloops };
#endif
