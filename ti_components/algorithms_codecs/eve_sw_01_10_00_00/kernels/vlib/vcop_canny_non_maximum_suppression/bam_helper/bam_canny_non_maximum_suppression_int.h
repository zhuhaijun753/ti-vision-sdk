/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_canny_non_maximum_suppression_int.h
 *
 *  @brief      This header defines internal structures for Canny Nms
 *               kernel.
 */

#ifndef BAM_CANNY_NON_MAXIMUM_SUPPRESSION_INT_H_
#define BAM_CANNY_NON_MAXIMUM_SUPPRESSION_INT_H_

#include <stdint.h>
#include <vcop.h>

#include "evealgframework.h"
#include "bam_canny_non_maximum_suppression.h"

typedef enum
{
  CANNY_NON_MAXIMUM_SUPPRESSION_INTERNAL_PARAMS_IDX = 0,
  CANNY_NON_MAXIMUM_SUPPRESSION_INTERNAL_INDEX_IDX,
  CANNY_NON_MAXIMUM_SUPPRESSION_INTERNAL_MAXCASE1_IDX,
  CANNY_NON_MAXIMUM_SUPPRESSION_INTERNAL_MAXCASE2_IDX,
  CANNY_NON_MAXIMUM_SUPPRESSION_INTERNAL_MAXCASE3_IDX,
  CANNY_NON_MAXIMUM_SUPPRESSION_INTERNAL_MAXCASE4_IDX,
  CANNY_NON_MAXIMUM_SUPPRESSION_INTERNAL_NUM_BLOCKS
} eBAM_CANNY_NON_MAXIMUM_SUPPRESSION_INTERNAL_BLOCKS;

typedef struct
{
    /* Must always follow this order: pInternalBlock[], pInBlock[], pOutputBlock[], args */
    void *pInternalBlock[CANNY_NON_MAXIMUM_SUPPRESSION_INTERNAL_NUM_BLOCKS];
    void *pInBlock[BAM_CANNY_NON_MAXIMUM_SUPPRESSION_NUM_INPUT_BLOCKS];
    void *pOutBlock[BAM_CANNY_NON_MAXIMUM_SUPPRESSION_NUM_OUTPUT_BLOCKS];
    BAM_CannyNonMaximumSuppression_Args     kernelInitArgs;
    BAM_CannyNonMaximumSuppression_CtrlArgs kernelCtrlArgs;
    uint16_t                                 *pBlockIndexBinning;
    uint16_t                                 *pBlockMaxCases;
    uint16_t                                 *pBlockDoubleThresholding;
} BAM_CannyNonMaximumSuppression_Context;

#endif /* BAM_CANNY_NON_MAXIMUM_SUPPRESSION_INT_H_*/

