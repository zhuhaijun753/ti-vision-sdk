/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_feature_matching_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating Hamming distance
 *              based corrrespondence matching computation into BAM
 */

#include <stdio.h>
#include <stdlib.h>

#include "evealgframework.h"
#include "bam_feature_matching_int.h"
#include "vcop_feature_matching_kernel.h" /* compiler should take care of include path */

/* Function Prototypes */
static BAM_Status BAM_featureMatching_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks);

static BAM_Status BAM_featureMatching_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks)
{
  const BAM_featureMatching_Args *args = (const BAM_featureMatching_Args *)kernelArgs;

#if !VCOP_HOST_EMULATION
  internalBlock[PARAMS_IDX].size = 2U*(vcop_featureMatch_initialize_param_count() +
                                      vcop_findTwoBestMatches_param_count() +
                                      vcop_pickConfidentMatches_param_count() +
                                      (2U*vcop_twoBestMatches_update_n_param_count()));

  if(args->descriptorSize == 32U) {
    internalBlock[PARAMS_IDX].size += (2U*(vcop_featureMatching_32_param_count() +
                                         vcop_featureMatch_32_pblk_update_param_count() +
                                         vcop_featureMatch_32_pblk_reset_param_count()));
  }
  else if(args->descriptorSize < 32U) {
    internalBlock[PARAMS_IDX].size += (2U*(vcop_featureMatching_lt_32_param_count() +
                                         vcop_featureMatch_lt_32_pblk_update_param_count() +
                                         vcop_featureMatch_lt_32_pblk_reset_param_count()));
  }
  else {
    internalBlock[PARAMS_IDX].size += (2U*(vcop_featureMatching_gt_32_param_count() +
                                         vcop_featureMatch_gt_32_pblk_update_param_count() +
                                         vcop_featureMatch_gt_32_pblk_reset_param_count()));
  }
#else
  internalBlock[PARAMS_IDX].size = 4U;
#endif

  internalBlock[SCRATCH_HAM_IDX].size  = ((args->descriptorSize <= 32U) ? 36U : 68U)*8U*((args->numDescriptors2 + 1U)/2U);
  internalBlock[SCRATCH_HAM_IDX].space = BAM_MEMSPACE_WBUF;

  internalBlock[SCRATCH_DESCRIPTOR_MASK].size = (args->descriptorSize != 32U) ? 32U*((args->descriptorSize + 31U)/32U) : 4U;
  internalBlock[SCRATCH_DESCRIPTOR_MASK].space = BAM_MEMSPACE_WBUF;

  internalBlock[SCRATCH_SCATTER_OFST].size = (args->descriptorSize > 32U) ? 8U*sizeof(uint16_t) : 4U;
  internalBlock[SCRATCH_SCATTER_OFST].space = BAM_MEMSPACE_WBUF;

  internalBlock[SCRATCH_HAM_DIST_IDX].size = 2U*((args->numDescriptors2 + 1U)/2U)*16U* sizeof(uint32_t);
  internalBlock[SCRATCH_HAM_DIST_IDX].space = BAM_MEMSPACE_IBUFLA;

  internalBlock[SCRATCH_MINDIST0_IDX].size = 16U*((args->numDescriptors1 + 15U)/16U)* sizeof(uint32_t);
  internalBlock[SCRATCH_MINDIST0_IDX].space = BAM_MEMSPACE_WBUF;

  internalBlock[SCRATCH_MINDIST1_IDX].size = 16U*((args->numDescriptors1 + 15U)/16U)* sizeof(uint32_t);
  internalBlock[SCRATCH_MINDIST1_IDX].space = BAM_MEMSPACE_WBUF;

  outBlock[OUT_IDX].size = sizeof(uint16_t)*8U*((args->numDescriptors1 + 7U)/8U);
  outBlock[OUT_IDX].space = BAM_MEMSPACE_IBUFHA;

  return BAM_S_SUCCESS;
}

BAM_KernelInfo gBAM_TI_featureMatchingKernel =
{
  0,                                      /* kernelId */
  sizeof(BAM_featureMatching_Context),
  sizeof(BAM_featureMatching_Args),
  BAM_EVE,                                /* coreType */
  BAM_NODE_COMPUTE,                       /* nodeType */
  NUM_IN_BLOCKS,                          /* 1 */
  NUM_OUT_BLOCKS,                         /* 1 */
  NUM_INTERNAL_BLOCKS                     /* 3 */
};

BAM_KernelHelperFuncDef gBAM_TI_featureMatchingHelperFunc =
  {&BAM_featureMatching_getMemRecFunc, NULL};

