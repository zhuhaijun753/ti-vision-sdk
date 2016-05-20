/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_disparityHamDist_int.h
 *
 *  @brief      This header defines internal structures for hamming distance based disparity calculation kernel
 *              into BAM.
 */
#ifndef BAM_DISPARITY_HAMDIST_INT_H_
#define BAM_DISPARITY_HAMDIST_INT_H_

#include <stdint.h>
#include <vcop.h>

#include "evealgframework.h"
#include "bam_disparityHamDist.h"

/* CHECK_MISRA("-19.7")  -> Disable rule 19.7 */
/* Function-like macro definition */
/* Deviation is allowed because this is a simple operation best implemented through a macro */
#define MAX(a,b) (((a)>(b)) ? (a) : (b))
/*RESET_MISRA("19.7")  -> Reset rule 19.7 */

#define NUM_IN_BLOCKS 3
#define NUM_OUT_BLOCKS 5
#define NUM_INTERNAL_BLOCKS 6

#define DISPARITY_HAMDIST_IN_LEFT_IDX      0
#define DISPARITY_HAMDIST_IN_RIGHT_IDX     1
#define DISPARITY_HAMDIST_CARRYOVER_IN_IDX 2

#define DISPARITY_HAMDIST_DISP_OUT_IDX        0 
#define DISPARITY_HAMDIST_MINCOST_OUT_IDX     1
#define DISPARITY_HAMDIST_CARRYOVER_OUT_IDX   2
#define DISPARITY_HAMDIST_PREV_ADJ_COST       3
#define DISPARITY_HAMDIST_NEXT_ADJ_COST       4
/* Don't support for now
#define DISPARITY_HAMDIST_RL_DISP_OUT_IDX     5
#define DISPARITY_HAMDIST_RL_MINCOST_OUT_IDX  6
*/

#define DISPARITY_HAMDIST_PARAMS_IDX                               0
#define DISPARITY_HAMDIST_COLLATE_MASK_OFFSET_IDX                  1
#define DISPARITY_HAMDIST_SCRATCH0_IDX                             2
#define DISPARITY_HAMDIST_SCRATCH1_IDX                             3
#define DISPARITY_HAMDIST_SCRATCH2_IDX                             4
#define DISPARITY_HAMDIST_ALLCOST_IDX                              5

#define DISPARITY_HAMDIST_FIRST_ROW_FIRST_CALL_PARAMS_OFST                0
#define DISPARITY_HAMDIST_FIRST_ROW_PARAMS_OFST                           (PARAM_SIZE_vcop_disparity_hammingDistance32_first_row_firstCall)
#define DISPARITY_HAMDIST_NTH_ROW_FIRST_CALL_PARAMS_OFST                  (PARAM_SIZE_vcop_disparity_hammingDistance32_first_row_firstCall + PARAM_SIZE_vcop_disparity_hammingDistance32_first_row)
#define DISPARITY_HAMDIST_NTH_ROW_PARAMS_OFST                             (PARAM_SIZE_vcop_disparity_hammingDistance32_first_row_firstCall + PARAM_SIZE_vcop_disparity_hammingDistance32_first_row + PARAM_SIZE_vcop_disparity_hammingDistance32_nth_row_firstCall)

#define DISPARITY_HAMDIST_GEN_PREV_NEXT_MINCOST_OFST                      (PARAM_SIZE_vcop_disparity_hammingDistance32_first_row_firstCall + PARAM_SIZE_vcop_disparity_hammingDistance32_first_row + PARAM_SIZE_vcop_disparity_hammingDistance32_nth_row_firstCall + PARAM_SIZE_vcop_disparity_hammingDistance32_nth_row)
#define DISPARITY_HAMDIST_PARAMS_SIZE                                     (2U*(PARAM_SIZE_vcop_disparity_hammingDistance32_first_row_firstCall + PARAM_SIZE_vcop_disparity_hammingDistance32_first_row + PARAM_SIZE_vcop_disparity_hammingDistance32_nth_row_firstCall + PARAM_SIZE_vcop_disparity_hammingDistance32_nth_row + PARAM_SIZE_vcop_disparity_hammingDistance_row_right_left_firstCall + PARAM_SIZE_vcop_disparity_genPrevAndNextMinCost))

/* Don't support for now
#define DISPARITY_HAMDIST_RL_FIRST_CALL_PARAMS_OFST                       (PARAM_SIZE_vcop_disparity_hammingDistance32_first_row_firstCall + PARAM_SIZE_vcop_disparity_hammingDistance32_first_row + PARAM_SIZE_vcop_disparity_hammingDistance32_nth_row_firstCall + PARAM_SIZE_vcop_disparity_hammingDistance32_nth_row)
#define DISPARITY_HAMDIST_RL_PARAMS_OFST                                  (PARAM_SIZE_vcop_disparity_hammingDistance32_first_row_firstCall + PARAM_SIZE_vcop_disparity_hammingDistance32_first_row + PARAM_SIZE_vcop_disparity_hammingDistance32_nth_row_firstCall + PARAM_SIZE_vcop_disparity_hammingDistance32_nth_row + PARAM_SIZE_vcop_disparity_hammingDistance_row_right_left_firstCall)

#define DISPARITY_HAMDIST_PARAMS_SIZE                                     (2*(PARAM_SIZE_vcop_disparity_hammingDistance32_first_row_firstCall + PARAM_SIZE_vcop_disparity_hammingDistance32_first_row + PARAM_SIZE_vcop_disparity_hammingDistance32_nth_row_firstCall + PARAM_SIZE_vcop_disparity_hammingDistance32_nth_row + PARAM_SIZE_vcop_disparity_hammingDistance_row_right_left_firstCall + PARAM_SIZE_vcop_disparity_hammingDistance_row_right_left))
*/

/* CHECK_MISRA("-20.2")  -> Disable rule 20.2  */
/* Usage of a reserved name for naming a language entity */
/* Deviation allowed as name is not used for any language entiry */
typedef struct _bam_disparityHamDist_context
{
    /* Must always follow this order: pInternalBlock[], pInBlock[], pOutputBlock[], args */
    void *pInternalBlock[NUM_INTERNAL_BLOCKS];
    void *pInBlock[NUM_IN_BLOCKS];
    void *pOutBlock[NUM_OUT_BLOCKS];
    BAM_DisparityHamDist_Args kernelArgs;
    uint16_t scratchBufferStride;
    uint16_t horzBlockIdx;
    uint16_t vertBlockIdx;
    uint16_t updateHorzBlockIdx;
    uint16_t updateVertBlockIdx;
    uint32_t *nth_row_firstCall_leftPrevRowPtr[2][5];
    uint32_t *nth_row_firstCall_leftLastRowPtr[2][5];
    uint32_t *nth_row_firstCall_rightPrevRowPtr[2][5];
    uint32_t *nth_row_firstCall_rightLastRowPtr[2][5];
    uint32_t *nth_row_leftPrevRowPtr[2][4];
    uint32_t *nth_row_leftLastRowPtr[2][4];
    uint32_t *nth_row_rightPrevRowPtr[2][4];
    uint32_t *nth_row_rightLastRowPtr[2][4];
    int16_t prevRowLeftOffset;
    int16_t prevRowLeftInitOffset;
    int16_t prevRowRightOffset;
    int16_t prevRowRightInitOffset;
    int16_t lastRowLeftOffset;
    int16_t lastRowLeftInitOffset;
    int16_t lastRowRightOffset;
    int16_t lastRowRightInitOffset;
    int16_t leftEndMarker;
    int16_t rightEndMarker;
    uint16_t *pFirstRowFirstCallParams[2];
    uint16_t *pFirstRowParams[2];
    uint16_t *pNthRowFirstCallParams[2];
    uint16_t *pNthRowParams[2];
    /*
    uint16_t *pRLFirstCallParams[2];
    uint16_t *pRLParams[2];
    */
    uint16_t *pGenPrevAndNextMinCostParams[2];
    uint8_t pingPongFlag;
} BAM_DisparityHamDist_Context;
/* RESET_MISRA("20.2")  -> Reset rule 20.2*/

#endif /* BAM_DISPARITY_HAMDIST_INT_H_*/
