/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_tensor_matrix_7x7_s16_grad_helper_funcs.c
 *
 *  @brief      This file defines interfaces for integrating kernel that computes
 *              tensor matrix using the 7x7 patch window of signed gradient input into BAM.
 */

#include <stdio.h>
#include <stdlib.h>

#include "evealgframework.h"
#include "bam_tensor_matrix_7x7_s16_grad_int.h"
#include "vcop_tensor_matrix_7x7_s16_grad_kernel.h" /* compiler should take care of include path */

/* Function Prototypes */
static BAM_Status BAM_Tensor_Matrix_7x7_S16_Grad_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks);

static BAM_Status BAM_Tensor_Matrix_7x7_S16_Grad_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks)
{
    const BAM_Tensor_Matrix_7x7_S16_Grad_Args *args = (const BAM_Tensor_Matrix_7x7_S16_Grad_Args *) kernelArgs;
    internalBlock[PARAMS_IDX].size = 2U*vcop_tensor_matrix_7x7_s16_grad_param_count();
    internalBlock[SCRATCH_IDX1].size = ((uint16_t)SCRATCH_SIZE)*4U;
    internalBlock[SCRATCH_IDX2].size = ((uint16_t)SCRATCH_SIZE)*4U;
    internalBlock[SCRATCH_IDX3].size = ((uint16_t)SCRATCH_SIZE)*4U;
    /*Ideal Output Block Memory Requirement*/
    outBlock[OUT_IDX1].size = (args->n * 4 * 3);
    outBlock[OUT_IDX1].attrs.memAttrs= BAM_MEMATTRS_SCRATCH;
    outBlock[OUT_IDX1].space = BAM_MEMSPACE_IBUFHA;    

    return BAM_S_SUCCESS;
}

BAM_KernelInfo gBAM_TI_tensorMatrix7x7S16GradKernel =
{
    0,                                      /* kernelId */
    sizeof(BAM_Tensor_Matrix_7x7_S16_Grad_Context),
    sizeof(BAM_Tensor_Matrix_7x7_S16_Grad_Args),
    BAM_EVE,                                /* coreType */
    BAM_NODE_COMPUTE,                       /* nodeType */
    NUM_IN_BLOCKS,                          /* 1 */
    NUM_OUT_BLOCKS,                         /* 4 */
    NUM_INTERNAL_BLOCKS                     /* 3 */
};

BAM_KernelHelperFuncDef gBAM_TI_tensorMatrix7x7S16GradHelperFunc =
{ &BAM_Tensor_Matrix_7x7_S16_Grad_getMemRecFunc, NULL};

