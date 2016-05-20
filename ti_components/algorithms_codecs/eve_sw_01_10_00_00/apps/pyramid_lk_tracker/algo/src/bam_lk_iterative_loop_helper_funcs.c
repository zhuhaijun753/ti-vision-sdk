/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_lk_iterative_loop_helper_funcs.c
 *
 *  @brief      This file defines interfaces for integrating kernel that computes
 *              relative location within the fetched input block along with updated
 *              source pointers using the new X, Y coordinates into BAM. It also
 *              incorporates the iterative LK loop to compute the flow vectors
 */

#include <stdio.h>
#include <stdlib.h>

#include "evealgframework.h"
#include "bam_lk_iterative_loop_int.h"

/* Function Prototypes */
static BAM_Status BAM_LK_Iterative_Loop_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks);

static BAM_Status BAM_LK_Iterative_Loop_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks)
{
#if (!VCOP_HOST_EMULATION)
   const BAM_LK_Iterative_Loop_Args *args =  kernelArgs;
#else
   const BAM_LK_Iterative_Loop_Args *args = (const BAM_LK_Iterative_Loop_Args *) kernelArgs;
#endif

    internalBlock[PARAMS_IDX].size = 2;

    internalBlock[SCRATCH_IDX1].size              = SCRATCH_IDX1_SIZE;
    internalBlock[SCRATCH_IDX1].attrs.memAttrs    = BAM_MEMATTRS_PERSIST;
    internalBlock[SCRATCH_IDX1].space             = BAM_MEMSPACE_WBUF;

    /*Ideal Output Block Memory Requirement*/
    outBlock[OUT_IDX1].size  = (args->numKeyPointsPerCall * 4);
    outBlock[OUT_IDX1].attrs.memAttrs= BAM_MEMATTRS_SCRATCH;
    outBlock[OUT_IDX1].space = BAM_MEMSPACE_IBUFHA;

    outBlock[OUT_IDX2].size  = (args->numKeyPointsPerCall * 2);
    outBlock[OUT_IDX2].attrs.memAttrs= BAM_MEMATTRS_SCRATCH;
    outBlock[OUT_IDX2].space = BAM_MEMSPACE_IBUFLA;

    return BAM_S_SUCCESS;
}

BAM_KernelInfo gBAM_TI_lkIterativeLoopKernel =
{
    0,                                      /* kernelId */
    sizeof(BAM_LK_Iterative_Loop_Context),
    sizeof(BAM_LK_Iterative_Loop_Args),
    BAM_EVE,                                /* coreType */
    BAM_NODE_COMPUTE,                       /* nodeType */
    NUM_IN_BLOCKS,                          /* 1 */
    NUM_OUT_BLOCKS,                         /* 4 */
    NUM_INTERNAL_BLOCKS                     /* 3 */
};

BAM_KernelHelperFuncDef gBAM_TI_lkIterativeLoopHelperFunc =
{ &BAM_LK_Iterative_Loop_getMemRecFunc, NULL};
