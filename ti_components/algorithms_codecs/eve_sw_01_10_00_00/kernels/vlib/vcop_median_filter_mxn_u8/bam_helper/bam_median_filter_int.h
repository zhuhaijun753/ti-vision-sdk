/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_MEDIAN_FILTER_int.h
 *
 *  @brief      This header defines internal structures for median filter
 *              into BAM.
 */

#ifndef BAM_MEDIAN_FILTER_INT_H_
#define BAM_MEDIAN_FILTER_INT_H_

#include <stdint.h>
#include <vcop.h>

#include "evealgframework.h"
#include "bam_median_filter.h"

#define NUM_IN_BLOCKS  (1U)
#define NUM_OUT_BLOCKS (1U)
#define NUM_INTERNAL_BLOCKS (6U)

#define IN_IDX  (BAM_MEDIAN_FILTER_INPUT_PORT)     /* 0 */

#define OUT_IDX (BAM_MEDIAN_FILTER_OUTPUT_PORT)   /* 0 */

#define PARAMS_IDX (BAM_MEDIAN_FILTER_TEMP_PARAM)                /* 0 */
#define HISTO_IDX (BAM_MEDIAN_FILTER_HISTOGRAM)                  /* 1 */
#define SCRATCH_WEIGHT_IDX (BAM_MEDIAN_FILTER_TEMP_WGT)          /* 2 */
#define SCRATCH_HISTO_IDX (BAM_MEDIAN_FILTER_TEMP_HISTO)         /* 3 */
#define BLK_HIST_IDX (BAM_MEDIAN_FILTER_TEMP_BLK_HIST)           /* 4 */
#define COARSE_HIST_IDX (BAM_MEDIAN_FILTER_COARSE_HIST)          /* 5 */

typedef struct bam_median_filter_context
{
    /* Must always follow this order: pInternalBlock[], pInBlock[], pOutputBlock[], args */
    void *pInternalBlock[NUM_INTERNAL_BLOCKS];
    void *pInBlock[NUM_IN_BLOCKS];
    void *pOutBlock[NUM_OUT_BLOCKS];
    BAM_Median_Filter_Args kernelArgs;
} BAM_Median_Filter_Context;

#endif /* BAM_MEDIAN_FILTER_INT_H_ */

