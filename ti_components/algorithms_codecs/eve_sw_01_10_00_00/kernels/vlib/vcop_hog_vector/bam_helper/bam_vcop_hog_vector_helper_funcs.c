/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_vcop_hog_vector_helper_funcs.c
 *
 *  @brief      This file defines interfaces for integrating hog vector compute kernel
 *              into BAM
 */

#include <stdio.h>
#include <stdlib.h>

#include "evealgframework.h"
#include "bam_vcop_hog_vector_int.h"
#include "vcop_hog_vector_kernel.h" /* compiler should take care of include path */

/* Function Prototypes */
static BAM_Status BAM_sliding_2x2_sum_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks);

static BAM_Status BAM_sliding_2x2_sum_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks)
{
    const BAM_sliding_2x2_sum_Args *args = (const BAM_sliding_2x2_sum_Args *) kernelArgs;
    BAM_Status status = 0;
    if(args->sun2x2outFormat >= EVE_VLIB_SLIDING_2x2_SUM_MAX)
    {
      status =  BAM_E_FAIL;
    }
    else
    {

#if !(VCOP_HOST_EMULATION)
      internalBlock[PARAMS_IDX].size = 2U*vcop_ti_pd_2x2_sum_param_count();
#else
      internalBlock[PARAMS_IDX].size = 4;
#endif
      if(args->sun2x2outFormat == EVE_VLIB_SLIDING_2x2_SUM_DEINTERLEAVED)
      {
        outBlock[OUT_IDX1].size = (args->blockWidth/2)*args->blockHeight*2;
        outBlock[OUT_IDX2].size = (args->blockWidth/2)*args->blockHeight*2;
      }
      /* CHECK_MISRA("-14.1")  -> Disable rule 14.1  */
      /* UNREACH.GEN or INVARIANT_CONDITION.UNREACH */
      /* Currently sun2x2outFormat will not be grater than EVE_VLIB_SLIDING_2x2_SUM_PLANAR, hence code is unreachable but  */
      /* as the implementation of the function changes, it will not be unreachable.   */
      else if(args->sun2x2outFormat == EVE_VLIB_SLIDING_2x2_SUM_PLANAR)
      {
        outBlock[OUT_IDX1].size = (args->blockWidth)*args->blockHeight*2;
        outBlock[OUT_IDX2].size = 4;
      }
      else
      {
        status = BAM_E_FAIL;
      }
      /* RESET_MISRA("14.1")  -> Reset rule 14.1      */
    }

    return status;
}

BAM_KernelInfo gBAM_TI_sliding2x2SumKernel =
{
    0,                                      /* kernelId */
    sizeof(BAM_sliding_2x2_sum_Context),
    sizeof(BAM_sliding_2x2_sum_Args),
    BAM_EVE,                                /* coreType */
    BAM_NODE_COMPUTE,                       /* nodeType */
    NUM_IN_BLOCKS,                          /* 1 */
    NUM_OUT_BLOCKS,                         /* 4 */
    NUM_INTERNAL_BLOCKS                     /* 3 */
};

BAM_KernelHelperFuncDef gBAM_TI_sliding2x2SumHelperFunc =
{ &BAM_sliding_2x2_sum_getMemRecFunc, NULL};

