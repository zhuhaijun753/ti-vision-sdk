/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_multipoint_harrisScore_u16_int.h
 *
 *  @brief      This header defines internal structures for multi-point
 *              16-bit Harris score function.
 */

#ifndef BAM_MULTIPOINT_HARRISSCORE_INT_H_
#define BAM_MULTIPOINT_HARRISSCORE_INT_H_

#include <stdint.h>
#include <vcop.h>

#include "evealgframework.h"
#include "bam_multipoint_harrisScore_u16.h"

#define NUM_IN_BLOCKS  (BAM_MULTIPOINT_HARRIS_SCORE_NUM_INPUT_BLOCKS)
#define NUM_OUT_BLOCKS (BAM_MULTIPOINT_HARRIS_SCORE_NUM_OUTPUT_BLOCKS)


#define IN_IMG_IDX         (BAM_MULTIPOINT_HARRIS_SCORE_INPUT_PORT_IMG)
#define IN_ARGS_IDX        (BAM_MULTIPOINT_HARRIS_SCORE_INPUT_PORT_INARGS)

#define OUT_IDX            (BAM_MULTIPOINT_HARRIS_SCORE_OUTPUT_PORT)

#define PARAMS_IDX         0
#define SEQ_ARRAY_IDX      1
#define SCRATCH_A          2
#define SCRATCH_B          3
#define SCRATCH_C          4

#define NUM_INTERNAL_BLOCKS 5


typedef struct bam_multipoint_harris_score_context
{
    /* Must always follow this order: pInternalBlock[], pInBlock[], pOutputBlock[], args */
    void *pInternalBlock[NUM_INTERNAL_BLOCKS];
    void *pInBlock[NUM_IN_BLOCKS];
    void *pOutBlock[NUM_OUT_BLOCKS];
    BAM_Multipoint_Harris_Score_Args kernelArgs;
    void *pOutBlockBase_OUT_IDX;
} BAM_Multipoint_Harris_Score_Context;

#endif /* BAM_MULTIPOINT_HARRISSCORE_INT_H_ */
