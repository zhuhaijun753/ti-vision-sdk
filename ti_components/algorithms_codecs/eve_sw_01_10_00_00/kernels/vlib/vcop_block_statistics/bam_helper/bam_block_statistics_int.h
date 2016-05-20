/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_block_statistics_int.h
 *
 *  @brief      This header defines internal structures for block statistics
 *              into BAM.
 */

#ifndef BAM_BLOCK_STATISTICS_INT_H_
#define BAM_BLOCK_STATISTICS_INT_H_

#include <stdint.h>
#include <vcop.h>

#include "evealgframework.h"
#include "bam_block_statistics.h"

#define NUM_IN_BLOCKS  (1U)
#define NUM_OUT_BLOCKS (4U)
#define NUM_INTERNAL_BLOCKS (4U)

#define IN_IDX       (BAM_BLOCK_STATISTICS_INPUT_PORT)   /* 0 */

#define OUT_MIN_IDX  (BAM_BLOCK_STATISTICS_OUTPUT_PORT_MIN)   /* 0 */
#define OUT_MAX_IDX  (BAM_BLOCK_STATISTICS_OUTPUT_PORT_MAX)   /* 1 */
#define OUT_MEAN_IDX (BAM_BLOCK_STATISTICS_OUTPUT_PORT_MEAN) /* 2 */
#define OUT_VAR_IDX  (BAM_BLOCK_STATISTICS_OUTPUT_PORT_VAR)   /* 3 */

#define PARAMS_IDX   (BAM_BLOCK_STATISTICS_TEMP_PARAM)                /* 0 */
#define SCRATCH_MINMAX_IDX (BAM_BLOCK_STATISTICS_TEMP_MIN_MAX)      /* 1 */
#define SCRATCH_SUM_IDX (BAM_BLOCK_STATISTICS_TEMP_SUM)             /* 2 */
#define SCRATCH_SUMSQ_B_IDX (BAM_BLOCK_STATISTICS_TEMP_SUM_SQ_B)    /* 3 */


typedef struct bam_block_statistics_context
{
    /* Must always follow this order: pInternalBlock[], pInBlock[], pOutputBlock[], args */
    void *pInternalBlock[NUM_INTERNAL_BLOCKS];
    void *pInBlock[NUM_IN_BLOCKS];
    void *pOutBlock[NUM_OUT_BLOCKS];
    BAM_Block_Statistics_Args kernelArgs;
} BAM_Block_Statistics_Context;

#endif /* BAM_BLOCK_STATISTICS_INT_H_ */

