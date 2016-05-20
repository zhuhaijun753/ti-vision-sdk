/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_feature_matching_int.h
 *
 *  @brief      This header defines internal structures for Hamming distance
 *              based corrrespondence matching computation into BAM.
 */

#ifndef BAM_FEATURE_MATCHING_INT_H_
#define BAM_FEATURE_MATCHING_INT_H_

#include <stdint.h>
#include <vcop.h>

#include "evealgframework.h"
#include "bam_feature_matching.h"

typedef void (*FUNC_PTR)(uint16_t* pblock);

#define NUM_IN_BLOCKS (BAM_FEATURE_MATCHING_NUM_INPUT_BLOCKS)
#define NUM_OUT_BLOCKS (BAM_FEATURE_MATCHING_NUM_OUTPUT_BLOCKS)

#define STR1_IDX (BAM_FEATURE_MATCHING_STRING_1_PORT)    /* 0 */
#define STR2_IDX (BAM_FEATURE_MATCHING_STRING_2_PORT)    /* 1 */

#define OUT_IDX (BAM_FEATURE_MATCHING_OUTPUT_PORT)       /* 0 */

/* Internal Buffer Maximum Sizes */
#define FEATURE_MATCHING_MAX_PARAMS_SIZE                      (380U)
#define FEATURE_MATCHING_MAX_SCRATCH_SCATTER_OFST_SIZE        (16U)

typedef enum
{
  PARAMS_IDX   =    0,
  SCRATCH_HAM_IDX,
  SCRATCH_DESCRIPTOR_MASK,
  SCRATCH_SCATTER_OFST,
  SCRATCH_HAM_DIST_IDX,
  SCRATCH_MINDIST0_IDX,
  SCRATCH_MINDIST1_IDX,
  NUM_INTERNAL_BLOCKS
} eBAM_FEATURE_MATCHING_TEMP_PORTS;

typedef struct
{
    /* Must always follow this order: pInternalBlock[], pInBlock[], pOutputBlock[], args */
    void *pInternalBlock[NUM_INTERNAL_BLOCKS];
    void *pInBlock[NUM_IN_BLOCKS];
    void *pOutBlock[NUM_OUT_BLOCKS];
    BAM_featureMatching_Args kernelArgs;
    BAM_featureMatching_CtlArgs kernelCtrlArgs;
    FUNC_PTR vcop_featureMatching_vloops;
    FUNC_PTR vcop_featureMatch_pblk_update_vloops;
    FUNC_PTR vcop_featureMatch_pblk_reset_vloops;
    uint16_t *pblock_vcop_featureMatch_initialize;
    uint16_t *pblock_vcop_featureMatching;
    uint16_t *pblock_vcop_findTwoBestMatches;
    uint16_t *pblock_vcop_featureMatch_pblk_update;
    uint16_t *pblock_vcop_pickConfidentMatches;
    uint16_t *pblock_vcop_featureMatch_pblk_reset;
    uint16_t *pblock_vcop_twoBestMatches_update_n;
    uint16_t *pblock_vcop_twoBestMatches_restore_n;
    uint32_t    iter;
    uint16_t  loopCount2;
    uint16_t  innerLoopCount;
    uint16_t  startIdx;
} BAM_featureMatching_Context;

#endif /* BAM_FEATURE_MATCHING_INT_H_ */
