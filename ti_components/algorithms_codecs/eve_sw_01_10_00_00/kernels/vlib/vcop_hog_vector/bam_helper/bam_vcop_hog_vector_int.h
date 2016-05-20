/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_vcop_hog_vector_int.h
 *
 *  @brief      This header defines internal structures for integrating hog vector compute kernel
 *              into BAM.
 */
#ifndef BAM_HOG_VECTOR_INT
#define BAM_HOG_VECTOR_INT

#include <stdint.h>
#include <vcop.h>

#include "evealgframework.h"
#include "bam_vcop_hog_vector.h"

#define NUM_IN_BLOCKS       ( 1 )
#define NUM_OUT_BLOCKS      ( 2 )
#define NUM_INTERNAL_BLOCKS ( 1 )

#define IN_IDX   (BAM_SLIDING_2x2_SUM_INPUT_PORT    )

#define OUT_IDX1 (BAM_SLIDING_2x2_SUM_OUTPUT_PORT1  )
#define OUT_IDX2 (BAM_SLIDING_2x2_SUM_OUTPUT_PORT2  )
#define PARAMS_IDX (0)

typedef struct 
{
    /* Must always follow this order: pInternalBlock[], pInBlock[], pOutputBlock[], args */
    void *pInternalBlock[NUM_INTERNAL_BLOCKS];
    void *pInBlock[NUM_IN_BLOCKS];
    void *pOutBlock[NUM_OUT_BLOCKS];
    BAM_sliding_2x2_sum_Args kernelArgs;
    BAM_KernelCustom kernelCustom;
} BAM_sliding_2x2_sum_Context;

#endif

