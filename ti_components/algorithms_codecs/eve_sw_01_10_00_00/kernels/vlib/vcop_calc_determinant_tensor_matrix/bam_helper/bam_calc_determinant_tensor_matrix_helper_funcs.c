/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_calc_determinant_tensor_matrix_helper_funcs.c
 *
 *  @brief      This file defines interfaces for integrating kernel that computes
 *              determinant of the tensor matrix into BAM.
 */

#include <stdio.h>
#include <stdlib.h>

#include "evealgframework.h"
#include "bam_calc_determinant_tensor_matrix_int.h"
#include "vcop_calc_determinant_tensor_matrix_kernel.h" /* compiler should take care of include path */

/* Function Prototypes */
static BAM_Status BAM_Calc_Determinant_Tensor_Matrix_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks);

static BAM_Status BAM_Calc_Determinant_Tensor_Matrix_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks)
{
    const BAM_Calc_Determinant_Tensor_Matrix_Args *args = (const BAM_Calc_Determinant_Tensor_Matrix_Args *) kernelArgs;
    internalBlock[PARAMS_IDX].size = 2U*vcop_calc_determinant_tensor_matrix_param_count();

    /*Ideal Output Block Memory Requirement*/
    outBlock[OUT_IDX1].size = (args->n * 2);
    outBlock[OUT_IDX1].attrs.memAttrs= BAM_MEMATTRS_SCRATCH;
    outBlock[OUT_IDX1].space = BAM_MEMSPACE_IBUFHA;
    outBlock[OUT_IDX2].size = (args->n * 4);
    outBlock[OUT_IDX2].attrs.memAttrs= BAM_MEMATTRS_SCRATCH;
    outBlock[OUT_IDX2].space = BAM_MEMSPACE_IBUFHA;


    return BAM_S_SUCCESS;
}

BAM_KernelInfo gBAM_TI_calcDeterminantTensorMatrixKernel =
{
    0,                                      /* kernelId */
    sizeof(BAM_Calc_Determinant_Tensor_Matrix_Context),
    sizeof(BAM_Calc_Determinant_Tensor_Matrix_Args),
    BAM_EVE,                                /* coreType */
    BAM_NODE_COMPUTE,                       /* nodeType */
    NUM_IN_BLOCKS,                          /* 1 */
    NUM_OUT_BLOCKS,                         /* 4 */
    NUM_INTERNAL_BLOCKS                     /* 3 */
};

BAM_KernelHelperFuncDef gBAM_TI_calcDeterminantTensorMatrixHelperFunc =
{ &BAM_Calc_Determinant_Tensor_Matrix_getMemRecFunc, NULL};

