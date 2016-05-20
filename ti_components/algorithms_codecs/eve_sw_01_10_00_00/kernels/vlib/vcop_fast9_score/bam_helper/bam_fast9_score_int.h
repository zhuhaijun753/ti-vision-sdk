/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_fast9_score_int.h
 *
 *  @brief      This header defines internal structures for fast9 score
 *              into BAM.
 */

#ifndef BAM_FAST9_SCORE_INT_H
#define BAM_FAST9_SCORE_INT_H

#include <stdint.h>
#include <vcop.h>

#include "evealgframework.h"
#include "bam_fast9_score.h"

#define NUM_IN_BLOCKS 1    /* 8x8 patch around XY */
#define NUM_OUT_BLOCKS 1   /* Fast9 Score is output */

#define NUM_FEATURES 32

/* Using max number of sad and threshold method */
/* Threshold method needs only 8 internal blocks */
/* So, for threshold, the BSCORE and DSCORE will have dummy allocation */

#define NUM_INTERNAL_BLOCKS 8


#define NUM_IND_SAD   17     /* 17 indeces to be looked up by LUT for SAD based score */
#define NUM_IND_THR   25     /* 25 indeces to be looked up by LUT for threshold based score */
#define NUM_BANKS     8     /* 8 memory banks to do 8-way look-up */

typedef struct
{
    uint8_t offset_out[NUM_FEATURES*4*17];
    uint8_t Dscore[NUM_FEATURES*16];
}SCORE_INTERNAL_MEMORY_IBUFHA;

#define IN_IDX   (BAM_FAST9_SCORE_INPUT_PORT_IN)

#define OUT_SCORE_IDX (BAM_FAST9_SCORE_OUTPUT_PORT_SCORE)

#define PARAMS_IDX                  0       /* 0 */
#define PTEMP_BUF_IDX               1       /* 1 */
#define PTEMP_IDX                   2       /* 2 */
#define SCORE_INTERNAL_IBUFHA_IDX   3       /* 3 */
#define BSCORE_IDX                  4       /* 4 */
#define SCORE_B_IDX                 5       /* 5 */
#define SCORE_D_IDX                 6       /* 6 */
#define LUT_IDX                     7       /* 7 */


extern const uint8_t LUT_EXT_IDX_SAD[NUM_IND_SAD*NUM_BANKS];
extern const uint8_t LUT_EXT_IDX_THR[NUM_IND_THR*NUM_BANKS];

typedef struct bam_fast9_score_context
{
    /* Must always follow this order: pInternalBlock[], pInBlock[], pOutputBlock[], args */
    void *pInternalBlock[NUM_INTERNAL_BLOCKS];
    void *pInBlock[NUM_IN_BLOCKS];
    void *pOutBlock[NUM_OUT_BLOCKS];
    BAM_Fast9_Score_Args kernelArgs;
    void *pOutBlockBase_OUT_SCORE_IDX;
} BAM_Fast9_Score_Context;

#endif
