/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_calc_inverse_structure_tensor_2x2_helper_funcs.c
 *
 *  @brief      This file defines interfaces for integrating kernel that computes
 *              inverse of the 2x2 structure tensor into BAM.
 */

#include <stdio.h>
#include <stdlib.h>

#include "evealgframework.h"
#include "bam_calc_inverse_structure_tensor_2x2_int.h"
#include "vcop_calc_inverse_structure_tensor_2x2_kernel.h" /* compiler should take care of include path */

/* Function Prototypes */
static BAM_Status BAM_Calc_Inverse_Structure_Tensor_2x2_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks);

static BAM_Status BAM_Calc_Inverse_Structure_Tensor_2x2_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks)
{
    const BAM_Calc_Inverse_Structure_Tensor_2x2_Args *args = (const BAM_Calc_Inverse_Structure_Tensor_2x2_Args *) kernelArgs;
    internalBlock[PARAMS_IDX].size = 2U*vcop_calc_inverse_structure_tensor_2x2_param_count();
    internalBlock[SCRATCH_IDX1].size = 4*((args->inputStride * 3));
    internalBlock[SCRATCH_IDX2].size = 4*((args->inputStride * 3));
    /*Ideal Output Block Memory Requirement, One factor of 2 is to include exponential and fractional parts of output       
    Another factor of 2 is taken since the output pixel data type is "short", 3 is taken since we 3 tensor array elements
    which are divided by determinant to obtain inverse*/
    outBlock[OUT_IDX1].size = (args->numKeyPoints * 2) * 2 * 3;
    outBlock[OUT_IDX1].attrs.memAttrs= BAM_MEMATTRS_SCRATCH;
    outBlock[OUT_IDX1].space = BAM_MEMSPACE_IBUFLA;    

    return BAM_S_SUCCESS;
}

BAM_KernelInfo gBAM_TI_calcInverseStructureTensor2x2Kernel =
{
    0,                                      /* kernelId */
    sizeof(BAM_Calc_Inverse_Structure_Tensor_2x2_Context),
    sizeof(BAM_Calc_Inverse_Structure_Tensor_2x2_Args),
    BAM_EVE,                                /* coreType */
    BAM_NODE_COMPUTE,                       /* nodeType */
    NUM_IN_BLOCKS,                          /* 1 */
    NUM_OUT_BLOCKS,                         /* 4 */
    NUM_INTERNAL_BLOCKS                     /* 3 */
};

BAM_KernelHelperFuncDef gBAM_TI_calcInverseStructureTensor2x2HelperFunc =
{ &BAM_Calc_Inverse_Structure_Tensor_2x2_getMemRecFunc, NULL};

