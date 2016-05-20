/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_harrisScore_32_7x7_int.h
 *
 *  @brief      This header defines internal structures  for integrating harris score
 */
#ifndef BAM_HARRISSCORE_U32_7x7_INT_H

#define BAM_HARRISSCORE_U32_7x7_INT_H

#include <stdint.h>
#include <vcop.h>

#include "evealgframework.h"
#include "bam_harrisScore_32_7x7.h"

#define NUM_IN_BLOCKS 2
#define NUM_OUT_BLOCKS 1
#define NUM_INTERNAL_BLOCKS 7

#define OUT_IDX (BAM_HARRISSCORE_32_OUTPUT_SCORE_PORT)            /* 0 */

#define PARAMS_IDX_1 0
#define PARAMS_IDX_2 1
#define XX_IDX       2
#define YY_IDX       3
#define XY_IDX       4
#define DETL_IDX     5
#define DETH_IDX     6


typedef struct
{
    /* Must always follow this order: pInternalBlock[], pInBlock[], pOutputBlock[], args */
    void *pInternalBlock[NUM_INTERNAL_BLOCKS];
    void *pInBlock[NUM_IN_BLOCKS];
    void *pOutBlock[NUM_OUT_BLOCKS];
    BAM_HarrisScore_32_7x7_Args kernelArgs;
} BAM_HarrisScore_32_7x7_Context;

#endif
