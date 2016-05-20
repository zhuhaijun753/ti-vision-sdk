/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_histogram_int.h
 *
 *  @brief      This header defines internal structures for  contrast stretching kernel .
 */

 #ifndef BAM_HISTOGRAM_INT_H_
#define BAM_HISTOGRAM_INT_H_

#include <stdint.h>
#include <vcop.h>

#include "evealgframework.h"
#include "bam_histogram.h"

typedef enum
{
  HISTOGRAM_INTERNAL_PARAMS_IDX   =    0,
  HISTOGRAM_INTERNAL_HISTOGRAM8COPY_IDX,
  HISTOGRAM_INTERNAL_NUM_BLOCK
} eBAM_HISTOGRAM_INTERNAL_BLOCKS;


#define NUM_IN_BLOCKS (BAM_HISTOGRAM_NUM_INPUT_BLOCKS)
#define NUM_OUT_BLOCKS (BAM_HISTOGRAM_NUM_OUTPUT_BLOCKS)
#define NUM_INTERNAL_BLOCKS (HISTOGRAM_INTERNAL_NUM_BLOCK)

typedef struct
{
    /* Must always follow this order: pInternalBlock[], pInBlock[], pOutputBlock[], args */
    void *pInternalBlock[NUM_INTERNAL_BLOCKS];
    void *pInBlock[NUM_IN_BLOCKS];
    void *pOutBlock[NUM_OUT_BLOCKS];
    BAM_Histogram_Args kernelArgs;
    uint16_t           totalBlockCnt;
    uint16_t           blockCnt;
} BAM_Histogram_Context;

#endif /* BAM_HISTOGRAM_INT_H_ */

