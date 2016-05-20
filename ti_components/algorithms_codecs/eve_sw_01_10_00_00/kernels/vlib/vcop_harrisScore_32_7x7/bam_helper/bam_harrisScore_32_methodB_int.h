/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_harrisScore_32_methodB_int.h
 *
 *  @brief      This header defines internal structures  for integrating harris score
 */
#ifndef BAM_HARRISSCORE_32_METHODB_INT_H_

#define BAM_HARRISSCORE_32_METHODB_INT_H_

#include <stdint.h>
#include <vcop.h>

#include "evealgframework.h"
#include "bam_harrisScore_32_7x7.h"


typedef enum
{
  BAM_HARRISSCORE_32_METHOD_B_INTERNAL_PARAM_IDX   =   0,
  BAM_HARRISSCORE_32_METHOD_B_INTERNAL_SCRATCHXX_IDX,
  BAM_HARRISSCORE_32_METHOD_B_INTERNAL_SCRATCHYY_IDX,
  BAM_HARRISSCORE_32_METHOD_B_INTERNAL_TOTAL_BLOCKS
} BAM_HARRISSCORE_32_METHOD_B_INTERNAL_BLOCKS;


#define NUM_IN_BLOCKS       (BAM_HARRISSCORE_32_INPUT_BLOCKS)
#define NUM_OUT_BLOCKS      (BAM_HARRISSCORE_32_OUTPUT_BLOCKS)
#define NUM_INTERNAL_BLOCKS (BAM_HARRISSCORE_32_METHOD_B_INTERNAL_TOTAL_BLOCKS)

typedef struct
{
    /* Must always follow this order: pInternalBlock[], pInBlock[], pOutputBlock[], args */
    void *pInternalBlock[NUM_INTERNAL_BLOCKS];
    void *pInBlock[NUM_IN_BLOCKS];
    void *pOutBlock[NUM_OUT_BLOCKS];
    BAM_HarrisScore_32_7x7_Args kernelArgs;
} BAM_HarrisScore_32_methodB_Context;

#endif /* BAM_HARRISSCORE_32_METHODB_INT_H_*/

