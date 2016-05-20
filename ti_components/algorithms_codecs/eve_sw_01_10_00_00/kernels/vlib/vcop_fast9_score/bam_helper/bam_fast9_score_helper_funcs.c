/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_fast9_score_helper_funcs.c
 *
 *  @brief      This file defines interfaces for integrating fast9 score
 *              into BAM
 */

#include <stdio.h>
#include <stdlib.h>

#include "evealgframework.h"
#include "bam_fast9_score_int.h"
#include "vcop_fast9_score_kernel.h" /* compiler should take care of include path */

const uint8_t LUT_EXT_IDX_SAD[NUM_IND_SAD*NUM_BANKS] =
{
     3,  3,  3,  3,  3,  3,  3,  3,
     4,  4,  4,  4,  4,  4,  4,  4,
    13, 13, 13, 13, 13, 13, 13, 13,
    22, 22, 22, 22, 22, 22, 22, 22,
    30, 30, 30, 30, 30, 30, 30, 30,
    38, 38, 38, 38, 38, 38, 38, 38,
    45, 45, 45, 45, 45, 45, 45, 45,
    52, 52, 52, 52, 52, 52, 52, 52,
    51, 51, 51, 51, 51, 51, 51, 51,
    50, 50, 50, 50, 50, 50, 50, 50,
    41, 41, 41, 41, 41, 41, 41, 41,
    32, 32, 32, 32, 32, 32, 32, 32,
    24, 24, 24, 24, 24, 24, 24, 24,
    16, 16, 16, 16, 16, 16, 16, 16,
     9,  9,  9,  9,  9,  9,  9,  9,
     2,  2,  2,  2,  2,  2,  2,  2,
    27, 27, 27, 27, 27, 27, 27, 27
};

const uint8_t LUT_EXT_IDX_THR[NUM_IND_THR*NUM_BANKS] =
{
     3,  3,  3,  3,  3,  3,  3,  3,
     4,  4,  4,  4,  4,  4,  4,  4,
    13, 13, 13, 13, 13, 13, 13, 13,
    22, 22, 22, 22, 22, 22, 22, 22,
    30, 30, 30, 30, 30, 30, 30, 30,
    38, 38, 38, 38, 38, 38, 38, 38,
    45, 45, 45, 45, 45, 45, 45, 45,
    52, 52, 52, 52, 52, 52, 52, 52,
    51, 51, 51, 51, 51, 51, 51, 51,
    50, 50, 50, 50, 50, 50, 50, 50,
    41, 41, 41, 41, 41, 41, 41, 41,
    32, 32, 32, 32, 32, 32, 32, 32,
    24, 24, 24, 24, 24, 24, 24, 24,
    16, 16, 16, 16, 16, 16, 16, 16,
     9,  9,  9,  9,  9,  9,  9,  9,
     2,  2,  2,  2,  2,  2,  2,  2,
     3,  3,  3,  3,  3,  3,  3,  3,
     4,  4,  4,  4,  4,  4,  4,  4,
    13, 13, 13, 13, 13, 13, 13, 13,
    22, 22, 22, 22, 22, 22, 22, 22,
    30, 30, 30, 30, 30, 30, 30, 30,
    38, 38, 38, 38, 38, 38, 38, 38,
    45, 45, 45, 45, 45, 45, 45, 45,
    52, 52, 52, 52, 52, 52, 52, 52,
    27, 27, 27, 27, 27, 27, 27, 27
};
/* Function Prototypes */
static BAM_Status BAM_Fast9_Score_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks);

static BAM_Status BAM_Fast9_Score_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks)
{
    const BAM_Fast9_Score_Args *args = (const BAM_Fast9_Score_Args *) kernelArgs;

#if (!VCOP_HOST_EMULATION)
if (args->score_method)
{
    internalBlock[PARAMS_IDX].size = 2U*vcop_fast9_score_kernel_param_count();
}
else
{
    internalBlock[PARAMS_IDX].size = 2U*vcop_fast9_thresh_score_param_count();
}
#else
    internalBlock[PARAMS_IDX].size = 16U;
#endif

    internalBlock[PTEMP_BUF_IDX].size = args->num_features * 8U * 9U;
    internalBlock[PTEMP_BUF_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    internalBlock[PTEMP_BUF_IDX].space = BAM_MEMSPACE_IBUFHA;

    internalBlock[PTEMP_IDX].size = args->num_features * 8U * 8U;
    internalBlock[PTEMP_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    internalBlock[PTEMP_IDX].space = BAM_MEMSPACE_IBUFLA;

    /* Make sure the LUT is placed in WBUF since we DMA this
       If not in WBUF, then make 2 copies, in A and B buffers so that it works in
       Aliased view */

if (args->score_method)
    {
        internalBlock[LUT_IDX].size = sizeof(LUT_EXT_IDX_SAD); /* fixed for LUT index */
        internalBlock[LUT_IDX].attrs.memAttrs = BAM_MEMATTRS_CONST;
        internalBlock[LUT_IDX].space = BAM_MEMSPACE_WBUF;

        /* Dummy allocation */
        internalBlock[BSCORE_IDX].size = 4U;
        internalBlock[BSCORE_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
        internalBlock[BSCORE_IDX].space = BAM_MEMSPACE_IBUFLA;
    }
else
    {
        internalBlock[LUT_IDX].size = sizeof(LUT_EXT_IDX_THR); /* fixed for LUT index */
        internalBlock[LUT_IDX].attrs.memAttrs = BAM_MEMATTRS_CONST;
        internalBlock[LUT_IDX].space = BAM_MEMSPACE_WBUF;

        internalBlock[BSCORE_IDX].size = args->num_features * 16U;
        internalBlock[BSCORE_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
        internalBlock[BSCORE_IDX].space = BAM_MEMSPACE_IBUFLA;
    }

    internalBlock[SCORE_INTERNAL_IBUFHA_IDX].size = sizeof(SCORE_INTERNAL_MEMORY_IBUFHA);
    internalBlock[SCORE_INTERNAL_IBUFHA_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    internalBlock[SCORE_INTERNAL_IBUFHA_IDX].space = BAM_MEMSPACE_IBUFHA;
    
    internalBlock[SCORE_B_IDX].size = args->num_features * sizeof(uint16_t);
    internalBlock[SCORE_B_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    internalBlock[SCORE_B_IDX].space = BAM_MEMSPACE_IBUFLA;

    internalBlock[SCORE_D_IDX].size = args->num_features * sizeof(uint16_t);
    internalBlock[SCORE_D_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    internalBlock[SCORE_D_IDX].space = BAM_MEMSPACE_IBUFHA;

    outBlock[OUT_SCORE_IDX].size = args->total_features * sizeof(uint16_t);
    outBlock[OUT_SCORE_IDX].space = BAM_MEMSPACE_WBUF;

    return BAM_S_SUCCESS;
}

BAM_KernelInfo gBAM_TI_fast9scoreKernel =
{
    0,                                      /* kernelId */
    sizeof(BAM_Fast9_Score_Context),
    sizeof(BAM_Fast9_Score_Args),
    BAM_EVE,                                /* coreType */
    BAM_NODE_COMPUTE,                       /* nodeType */
    NUM_IN_BLOCKS,                          /* 1 */
    NUM_OUT_BLOCKS,                         /* 1 */
    NUM_INTERNAL_BLOCKS                     /* 7(SAD method) or 9(thresh method) */
};

BAM_KernelHelperFuncDef gBAM_TI_fast9scoreHelperFunc =
{ &BAM_Fast9_Score_getMemRecFunc, NULL};

