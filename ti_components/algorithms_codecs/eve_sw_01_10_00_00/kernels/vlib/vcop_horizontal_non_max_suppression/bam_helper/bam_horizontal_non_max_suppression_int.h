/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_horizontal_non_max_suppression_int.h
 *
 *  @brief      This header defines internal structures for horizontal non max suppression
 *              into BAM.
 */

#ifndef BAM_HORIZONTAL_NON_MAX_SUPPRESSION_INT_H
#define BAM_HORIZONTAL_NON_MAX_SUPPRESSION_INT_H

#include <stdint.h>
#include <vcop.h>

#include "evealgframework.h"
#include "bam_horizontal_non_max_suppression.h"

#define NUM_IN_BLOCKS (2)    /* packed (XY), Fast9 Score */
#define NUM_OUT_BLOCKS (2)   /* packed (XY,ID) and Fast9 Score are outputs */
#define NUM_INTERNAL_BLOCKS (2)   /* ID as scratch buffer */

#define IN_XY_IDX (BAM_HORIZONTAL_NON_MAX_SUPPRESSION_INPUT_PORT_XY)
#define IN_SCORE_IDX (BAM_HORIZONTAL_NON_MAX_SUPPRESSION_INPUT_PORT_SCORE)

#define OUT_XY_IDX (BAM_HORIZONTAL_NON_MAX_SUPPRESSION_OUTPUT_PORT_XY)
#define OUT_SCORE_IDX (BAM_HORIZONTAL_NON_MAX_SUPPRESSION_OUTPUT_PORT_SCORE)

#define PARAMS_IDX (0)      /* 0 */
#define ID_IDX     (1)       /* 1 */

extern const uint8_t ID_EXT_IDX[8];

typedef struct bam_horizontal_non_max_suppression_context
{
    /* Must always follow this order: pInternalBlock[], pInBlock[], pOutputBlock[], args */
    void *pInternalBlock[NUM_INTERNAL_BLOCKS];
    void *pInBlock[NUM_IN_BLOCKS];
    void *pOutBlock[NUM_OUT_BLOCKS];
    BAM_Horizontal_Non_Max_Suppression_Args kernelArgs;
} BAM_Horizontal_Non_Max_Suppression_Context;

#endif
