/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
* @file bam_nxn_block_sum_helper_funcs.h
*
* @brief
*
*
* @version 0.0 (Jan 2014) : Base version.
*/

#ifndef BAM_NXN_BLOCK_SUM_HELPER_FUNCS_H_
#define BAM_NXN_BLOCK_SUM_HELPER_FUNCS_H_

#include "evealgframework.h"
#include "bam_nxn_block_sum.h"
#include <vcop.h>
#include <stdint.h>

/*
1 Internal Block for param register
2. temp Ptr1
3. temp Ptr2
*/
#define NXN_BLOCK_SUM_NUM_INTERNAL_BLOCKS 3u

/* Two Input Blocks
1. Input Ptr1 block
2. Input Ptr2 block */
#define NXN_BLOCK_SUM_NUM_IN_BLOCKS 2u

/* Two Output Blocks
1. outBlock 1
2. outBlock 2 */
#define NXN_BLOCK_SUM_NUM_OUT_BLOCKS 2u


/* Index for Internal Blocks */
#define NXN_BLOCK_SUM_INTERNAL_PARAMS_IDX     (0u)
#define NXN_BLOCK_SUM_INTERNAL_TEMP_PTR1_IDX  (1u)
#define NXN_BLOCK_SUM_INTERNAL_TEMP_PTR2_IDX  (2u)



/* Index for Input Blocks */
#define NXN_BLOCK_SUM_IN_PTR1_IDX    (0u)
#define NXN_BLOCK_SUM_IN_PTR2_IDX    (1u)

/* Index for output Block */
#define NXN_BLOCK_SUM_OUT_PTR1_IDX     (0u)
#define NXN_BLOCK_SUM_OUT_PTR2_IDX     (1u)

typedef struct bam_nxn_block_sum_context
{
    void *pInternalBlock[NXN_BLOCK_SUM_NUM_INTERNAL_BLOCKS];
    void *pInBlock[NXN_BLOCK_SUM_NUM_IN_BLOCKS];
    void *pOutBlock[NXN_BLOCK_SUM_NUM_OUT_BLOCKS];
    BAM_nxn_block_sum_Args  kernelArgs;
    BAM_KernelCustom kernelCustom;
} BAM_nxn_block_sum_Context;

#endif /* BAM_NXN_BLOCK_SUM_HELPER_FUNCS_H_*/

