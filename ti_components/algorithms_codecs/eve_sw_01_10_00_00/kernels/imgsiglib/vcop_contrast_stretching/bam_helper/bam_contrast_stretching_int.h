/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_contrast_stretching_int.h
 *
 *  @brief      This header defines internal structures for  contrast stretching kernel .
 */

 #ifndef BAM_CONTRAST_STRETCHING_INT_H_
#define BAM_CONTRAST_STRETCHING_INT_H_

#include <stdint.h>
#include <vcop.h>

#include "evealgframework.h"
#include "bam_contrast_stretching.h"

typedef enum
{
  CONTRAST_STRETCHING_INTERNAL_PARAMS_IDX   =    0,
  CONTRAST_STRETCHING_INTERNAL_NUM_BLOCK
} eBAM_CONTRAST_STRETCHING_INTERNAL_BLOCKS;


#define NUM_IN_BLOCKS (BAM_CONTRAST_STRETCHING_NUM_INPUT_BLOCKS)
#define NUM_OUT_BLOCKS (BAM_CONTRAST_STRETCHING_NUM_OUTPUT_BLOCKS)
#define NUM_INTERNAL_BLOCKS (CONTRAST_STRETCHING_INTERNAL_NUM_BLOCK)

typedef struct
{
    /* Must always follow this order: pInternalBlock[], pInBlock[], pOutputBlock[], args */
    void *pInternalBlock[NUM_INTERNAL_BLOCKS];
    void *pInBlock[NUM_IN_BLOCKS];
    void *pOutBlock[NUM_OUT_BLOCKS];
    BAM_ContrastStretching_Args kernelArgs;
} BAM_ContrastStretching_Context;

#endif /* BAM_CONTRAST_STRETCHING_INT_H_ */

