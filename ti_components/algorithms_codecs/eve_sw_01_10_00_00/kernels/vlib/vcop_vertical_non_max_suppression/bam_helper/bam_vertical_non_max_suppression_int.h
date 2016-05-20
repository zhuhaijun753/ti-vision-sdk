/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_vertical_non_max_suppression_int.h
 *
 *  @brief      This header defines internal structures for vertical non max suppression
 *              into BAM.
 */

#ifndef BAM_VERTICAL_NON_MAX_SUPPRESSION_INT_H
#define BAM_VERTICAL_NON_MAX_SUPPRESSION_INT_H

#include <stdint.h>
#include <vcop.h>

#include "evealgframework.h"
#include "bam_vertical_non_max_suppression.h"

#define NUM_IN_BLOCKS 2    /* packed (XY), Fast9 Score are inputs */
#define NUM_OUT_BLOCKS 2   /* packed (XY) and packed (Fast9 Score, ID) are outputs */
#define NUM_INTERNAL_BLOCKS 4   /* 4 internal scratch buffers required */

#define IN_XY_IDX (BAM_VERTICAL_NON_MAX_SUPPRESSION_INPUT_PORT_XY)   /* 0 */
#define IN_SCORE_IDX (BAM_VERTICAL_NON_MAX_SUPPRESSION_INPUT_PORT_SCORE)   /* 1 */

#define OUT_XY_IDX (BAM_VERTICAL_NON_MAX_SUPPRESSION_OUTPUT_PORT_XY)     /* 0 */
#define OUT_SCORE_IDX (BAM_VERTICAL_NON_MAX_SUPPRESSION_OUTPUT_PORT_SCORE)   /* 1 */

#define PARAMS_IDX      0        /* 0 */
#define NMS_ID_IDX      1        /* 1 */
#define NMS_Y_SCORE_IDX 2        /* 2 */
#define ID_IDX          3        /* 3 */

extern const uint8_t IN_ID_IDX[8];

typedef struct bam_vertical_non_max_suppression_context
{
    /* Must always follow this order: pInternalBlock[], pInBlock[], pOutputBlock[], args */
    void *pInternalBlock[NUM_INTERNAL_BLOCKS];
    void *pInBlock[NUM_IN_BLOCKS];
    void *pOutBlock[NUM_OUT_BLOCKS];
    BAM_Vertical_Non_Max_Suppression_Args kernelArgs;
    void *pInBlockBase_INDEX_LIST;
} BAM_Vertical_Non_Max_Suppression_Context;

#endif   /* BAM_VERTICAL_NON_MAX_SUPPRESSION_INT_H */
