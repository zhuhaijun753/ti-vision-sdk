/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_weight_computation_helper_funcs.c
 *
 *  @brief      This file defines interfaces for integrating weight computation
 *              function into BAM
 */

#include <stdio.h>
#include <stdlib.h>

#include "evealgframework.h"
#include "bam_weight_computation_int.h"
#include "vcop_weight_computation_kernel.h" /* compiler should take care of include path */

/* Function Prototypes */
static BAM_Status BAM_Weight_Computation_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks);

static BAM_Status BAM_Weight_Computation_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks)
{
    const BAM_Weight_Computation_Args *args = (const BAM_Weight_Computation_Args *) kernelArgs;

    internalBlock[PARAMS_IDX].size = 2U*vcop_weight_computation_param_count();

    /*Ideal Output Block Memory Requirement, Factor of 4 is used since we have 4 bilinear weights per key point*/
    outBlock[OUT_IDX].size = args->outputStride * 4 * sizeof(int16_t);
    outBlock[OUT_IDX].attrs.memAttrs= BAM_MEMATTRS_SCRATCH;
    outBlock[OUT_IDX].space = BAM_MEMSPACE_IBUFHA;

    return BAM_S_SUCCESS;
}

BAM_KernelInfo gBAM_TI_weightComputationKernel =
{
    0,                                      /* kernelId */
    sizeof(BAM_Weight_Computation_Context),
    sizeof(BAM_Weight_Computation_Args),
    BAM_EVE,                                /* coreType */
    BAM_NODE_COMPUTE,                       /* nodeType */
    NUM_IN_BLOCKS,                          /* 1 */
    NUM_OUT_BLOCKS,                         /* 4 */
    NUM_INTERNAL_BLOCKS                     /* 3 */
};

BAM_KernelHelperFuncDef gBAM_TI_weightComputationHelperFunc =
{ &BAM_Weight_Computation_getMemRecFunc, NULL};

