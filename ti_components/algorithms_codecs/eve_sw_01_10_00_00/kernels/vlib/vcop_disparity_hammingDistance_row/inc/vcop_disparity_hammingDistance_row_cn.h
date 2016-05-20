/*==========================================================================*/
/*      Copyright (C) 2009-2014 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *******************************************************************************
 *  @func          vcop_disparity_hammingDistance_row_cn
 *  @brief         The function vcop_disparity_hammingDistance_row_cn takes two input image rows,
 * left and right and compute the disparity and kinimum SAD cost for every pixel 
 * Use this function for the very first row of the image                        
 * Subsequent row should use vcop_disparity_hammingDistance_row_iterative_cn() in the same file .
 *
 *
 *  @param [in]    left : Pointer to row from left image 
 *  @param [in]    right : Pointer to row from right image
 *  @param [in]    leftStride : Stride of the left row, need to be greater or equal to width + winWidth-1
 *  @param [in]    rightStride : Stride of the right row, need to be greater or equal to width + numDisparities - 1 + winWidth-1 
 *  @param [in]    winWidth : width of the support window used for SAD calculation
 *  @param [in]    winHeight : height of the support window used for SAD calculation
 *  @param [in]    disparityOutput: pointer to disparity found for every pixels. Size is (numDisparities/disparityStep) bytes
 *  @param [in]    minCostOutput: pointer to minimum cost corresponding to the disparity found for every pixel. Size is 2*(numDisparities/disparityStep) bytes 
 *  @param [in]    allCostOutput: size must be equal 2*(numDisparities/disparityStep )*width bytes
 *  @param [in]    width: Must be multiple of 32, number of pixels in the row for which disparities are produced 
 *  @param [in]    numDisparities: Number of disparities. Note that actual number of disparities produced is numDisparities/disparityStep
 *  @param [in]    disparityStep: Disparity step, for faster computation
 *  @return        None
 *******************************************************************************
 */

#ifndef _VCOP_DISPARITY_HAMMING_CN_H_
#define _VCOP_DISPARITY_HAMMING_CN_H_

#include <stdint.h>

/* CHECK_MISRA("-20.1")  -> Disable rule 20.1  */
/* Usage of a reserved name for naming a macro*/
/* Deviation allowed as name is not used for any language entiry */

#define _TRUE_DISPARITY_VALUES
#define _PICK_HIGH_DISPARITY_WHEN_TIE

/* When _TRUE_DISPARITY_VALUES is defined, in case step is >= 1, the disparities values produced are true disparity values
 * whereas when it is undefined, the disparity values are equal to the index in the cost array. 
 * The later more may be enabled on EVE side for faster computation. 
 */
/* CHECK_MISRA("-19.7")  -> Disable rule 19.7 */
/* Function-like macro definition */
/* Deviation is allowed because this is a simple operation best implemented through a macro */
#ifdef _TRUE_DISPARITY_VALUES
#define INDEX_2_DISP(a, step) (a)
#define DISP_2_INDEX(a, step) ((a)/(step))
#else
#define INDEX_2_DISP(a, step) ((a)/(step))
#define DISP_2_INDEX(a, step) (a)
#endif

#ifdef _PICK_HIGH_DISPARITY_WHEN_TIE
#define IS_SMALLER(a,b) ((a)<=(b))
#else
#define IS_SMALLER(a,b) ((a)<(b))
#endif
/* RESET_MISRA("19.7")  -> Reset rule 19.7*/

void vcop_disparity_hammingDistance64_row_ref_cn
(
        uint8_t *left,
        uint8_t *right,
        uint16_t leftStride,
        uint16_t rightStride,
        uint8_t winWidth,
        uint8_t winHeight,
        uint8_t *disparityOutput,
        uint16_t *minCostOutput,
        uint16_t *allCostOutput,
        uint16_t width,
        uint8_t numDisparities,
        uint8_t disparityStep
);

void vcop_disparity_hammingDistance64_row_right_left_ref_cn
(
        uint8_t *left,
        uint8_t *right,
        uint16_t leftStride, /* in bytes */
        uint16_t rightStride, /* in bytes */
        uint8_t winWidth,
        uint8_t winHeight,
        uint8_t *disparityOutput,
        uint16_t *minCostOutput,
        uint16_t *allCostOutput,
        uint16_t width, /* Number of 64-bits codeword */
        uint8_t numDisparities,
        uint8_t disparityStep
);

void vcop_disparity_hammingDistance64_first_row_cn
(
        uint8_t *left,
        uint8_t *right,
        uint16_t leftStride,
        uint16_t rightStride,
        uint8_t winWidth,
        uint8_t winHeight,
        uint8_t *disparityOutput,
        uint16_t *minCostOutput,
        uint16_t *allCostOutput,
        uint16_t width,
        uint16_t allCostOutputStride,
        uint8_t numDisparities,
        uint8_t disparityStep
);

void vcop_disparity_hammingDistance64_nth_row_cn
(
        uint8_t *left,
        uint8_t *right,
        uint16_t leftStride,
        uint16_t rightStride,
        uint8_t winWidth,
        uint8_t winHeight,
        uint8_t *disparityOutput,
        uint16_t *minCostOutput,
        uint16_t *prevAllCostOutput,
        uint16_t *allCostOutput,
        uint16_t width,
        uint16_t allCostOutputStride,
        uint8_t numDisparities,
        uint8_t disparityStep
);

void vcop_disparity_hammingDistance32_row_ref_cn
(
        uint8_t *left,
        uint8_t *right,
        uint16_t leftStride,
        uint16_t rightStride,
        uint8_t winWidth,
        uint8_t winHeight,
        uint8_t *disparityOutput,
        uint16_t *minCostOutput,
        uint16_t *allCostOutput,
        uint16_t width,
        uint8_t numDisparities,
        uint8_t disparityStep
);

void vcop_disparity_hammingDistance32_RL_row_ref_cn
(
        uint8_t *left,
        uint8_t *right,
        uint16_t leftStride,
        uint16_t rightStride,
        uint8_t winWidth,
        uint8_t winHeight,
        uint8_t *disparityOutput,
        uint16_t *minCostOutput,
        uint16_t *allCostOutput,
        uint16_t width,
        uint8_t numDisparities,
        uint8_t disparityStep
);
#if 0
static void wrapepr_vcop_disparity_hammingDistance32_row_ref_cn
(
        uint8_t *left,
        uint8_t *right,
        uint16_t leftStride,
        uint16_t rightStride,
        uint8_t winWidth,
        uint8_t winHeight,
        uint8_t *disparityOutput,
        uint16_t *minCostOutput,
        uint16_t *allCostOutput,
        uint16_t width,
        uint8_t numDisparities,
        uint8_t disparityStep,
        uint8_t rlFlag
) {
    if (rlFlag== 1) {
        vcop_disparity_hammingDistance32_RL_row_ref_cn(
                left,
                right,
                leftStride,
                rightStride,
                winWidth,
                winHeight,
                disparityOutput,
                minCostOutput,
                allCostOutput,
                width,
                numDisparities,
                disparityStep
        );
    }
    else {
        vcop_disparity_hammingDistance32_row_ref_cn(
                left,
                right,
                leftStride,
                rightStride,
                winWidth,
                winHeight,
                disparityOutput,
                minCostOutput,
                allCostOutput,
                width,
                numDisparities,
                disparityStep
        );
    }
}
#endif
void vcop_disparity_genPrevAndNextMinCost_cn(
        const uint8_t *disparityOutput,
        const uint16_t *allCostOutput,
        uint16_t *prevMinCostOutput,
        uint16_t *nextMinCostOutput,
        uint16_t width,
        uint8_t numDisparities,
        uint8_t disparityStep
);

void vcop_disparity_hammingDistance32_row_right_left_ref_cn
(
        uint8_t *left,
        uint8_t *right,
        uint16_t leftStride, /* in bytes */
        uint16_t rightStride, /* in bytes */
        uint8_t winWidth,
        uint8_t winHeight,
        uint8_t *disparityOutput,
        uint16_t *minCostOutput,
        uint16_t *allCostOutput,
        uint16_t width, /* Number of 64-bits codeword */
        uint8_t numDisparities,
        uint8_t disparityStep
);

void vcop_disparity_hammingDistance_row_right_left_cn
(
        const uint16_t *allCostOutput,
        uint8_t *rlDisparityOutput,
        uint16_t *rlMinCostOutput,
        uint8_t *prevRlDisparityOutput,
        uint16_t *prevRlMinCostOutput,
        uint16_t *rlAllCostOutput,
        uint8_t *rlDisparityScratch, /* not used, only to match kernel-C prototype */
        uint16_t *rlMinCostScratch, /* not used, only to match kernel-C prototype */
        uint16_t allCostStride,
        uint16_t rlAllCostStride,
        uint16_t width, 
        uint8_t numDisparities,
        uint8_t disparityStep
);


void vcop_disparity_hammingDistance32_first_row_cn
(
        uint8_t *left,
        uint8_t *right,
        uint16_t leftStride,
        uint16_t rightStride,
        uint8_t winWidth,
        uint8_t winHeight,
        uint8_t *disparityOutput,
        uint16_t *minCostOutput,
        uint16_t *allCostOutput,
        uint16_t width,
        uint16_t allCostOutputStride,
        uint8_t numDisparities,
        uint8_t disparityStep
);

void vcop_disparity_hammingDistance32_RL_first_row_cn
(
        uint8_t *left,
        uint8_t *right,
        uint16_t leftStride,
        uint16_t rightStride,
        uint8_t winWidth,
        uint8_t winHeight,
        uint8_t *disparityOutput,
        uint16_t *minCostOutput,
        uint16_t *allCostOutput,
        uint16_t width,
        uint16_t allCostOutputStride,
        uint8_t numDisparities,
        uint8_t disparityStep
);

static void wrapper_vcop_disparity_hammingDistance32_RL_first_row_cn
(
        uint8_t *left,
        uint8_t *right,
        uint16_t leftStride,
        uint16_t rightStride,
        uint8_t winWidth,
        uint8_t winHeight,
        uint8_t *disparityOutput,
        uint16_t *minCostOutput,
        uint16_t *allCostOutput,
        uint16_t width,
        uint16_t allCostOutputStride,
        uint8_t numDisparities,
        uint8_t disparityStep,
        uint8_t rlFlag
) {
    if (rlFlag== 1) {
        vcop_disparity_hammingDistance32_RL_first_row_cn
        (
                left,
                right,
                leftStride,
                rightStride,
                winWidth,
                winHeight,
                disparityOutput,
                minCostOutput,
                allCostOutput,
                width,
                allCostOutputStride,
                numDisparities,
                disparityStep
        );
    }
    else {
        vcop_disparity_hammingDistance32_first_row_cn
        (
                left,
                right,
                leftStride,
                rightStride,
                winWidth,
                winHeight,
                disparityOutput,
                minCostOutput,
                allCostOutput,
                width,
                allCostOutputStride,
                numDisparities,
                disparityStep
        );
    }
}

void vcop_disparity_hammingDistance32_nth_row_cn
(
        uint8_t *left,
        uint8_t *right,
        uint16_t leftStride,
        uint16_t rightStride,
        uint8_t winWidth,
        uint8_t winHeight,
        uint8_t *disparityOutput,
        uint16_t *minCostOutput,
        uint16_t *prevAllCostOutput,
        uint16_t *allCostOutput,
        uint16_t width,
        uint16_t allCostOutputStride,
        uint8_t numDisparities,
        uint8_t disparityStep
);

void vcop_disparity_hammingDistance32_RL_nth_row_cn
(
        uint8_t *left,
        uint8_t *right,
        uint16_t leftStride,
        uint16_t rightStride,
        uint8_t winWidth,
        uint8_t winHeight,
        uint8_t *disparityOutput,
        uint16_t *minCostOutput,
        uint16_t *prevAllCostOutput,
        uint16_t *allCostOutput,
        uint16_t width,
        uint16_t allCostOutputStride,
        uint8_t numDisparities,
        uint8_t disparityStep
);
#if 0
static void wrapper_vcop_disparity_hammingDistance32_nth_row_cn
(
        uint8_t *left,
        uint8_t *right,
        uint16_t leftStride,
        uint16_t rightStride,
        uint8_t winWidth,
        uint8_t winHeight,
        uint8_t *disparityOutput,
        uint16_t *minCostOutput,
        uint16_t *prevAllCostOutput,
        uint16_t *allCostOutput,
        uint16_t width,
        uint16_t allCostOutputStride,
        uint8_t numDisparities,
        uint8_t disparityStep,
        uint8_t rlFlag
){
    if (rlFlag==1) {
        vcop_disparity_hammingDistance32_RL_nth_row_cn
        (
                left,
                right,
                leftStride,
                rightStride,
                winWidth,
                winHeight,
                disparityOutput,
                minCostOutput,
                prevAllCostOutput,
                allCostOutput,
                width,
                allCostOutputStride,
                numDisparities,
                disparityStep
        );
    }
    else {
        vcop_disparity_hammingDistance32_nth_row_cn
        (
                left,
                right,
                leftStride,
                rightStride,
                winWidth,
                winHeight,
                disparityOutput,
                minCostOutput,
                prevAllCostOutput,
                allCostOutput,
                width,
                allCostOutputStride,
                numDisparities,
                disparityStep
        );
    }
}
#endif
void vcop_disparity_hammingDistance32_row_ref_circ_cn
(
        uint8_t *left,
        uint8_t *right,
        uint16_t leftStride,
        uint16_t rightStride,
        uint8_t winWidth,
        uint8_t winHeight,
        uint8_t *disparityOutput,
        uint16_t *minCostOutput,
        uint16_t *allCostOutput,
        uint16_t width,
        uint8_t numDisparities,
        uint8_t disparityStep,
        uint8_t rowIndex,
        uint8_t circBufferLen
);

void vcop_disparity_hammingDistance32_row_RL_ref_circ_cn
(
        uint8_t *left,
        uint8_t *right,
        uint16_t leftStride,
        uint16_t rightStride,
        uint8_t winWidth,
        uint8_t winHeight,
        uint8_t *disparityOutput,
        uint16_t *minCostOutput,
        uint16_t *allCostOutput,
        uint16_t width,
        uint8_t numDisparities,
        uint8_t disparityStep,
        uint8_t rowIndex,
        uint8_t circBufferLen
);
#if 0
static void wrapper_vcop_disparity_hammingDistance32_row_ref_circ_cn
(
        uint8_t *left,
        uint8_t *right,
        uint16_t leftStride,
        uint16_t rightStride,
        uint8_t winWidth,
        uint8_t winHeight,
        uint8_t *disparityOutput,
        uint16_t *minCostOutput,
        uint16_t *allCostOutput,
        uint16_t width,
        uint8_t numDisparities,
        uint8_t disparityStep,
        uint8_t rowIndex,
        uint8_t circBufferLen,
        uint8_t rlFlag
) {
    if (rlFlag== 1) {
        vcop_disparity_hammingDistance32_row_RL_ref_circ_cn
        (
                left,
                right,
                leftStride,
                rightStride,
                winWidth,
                winHeight,
                disparityOutput,
                minCostOutput,
                allCostOutput,
                width,
                numDisparities,
                disparityStep,
                rowIndex,
                circBufferLen
        );
    }
    else {
        vcop_disparity_hammingDistance32_row_ref_circ_cn
        (
                left,
                right,
                leftStride,
                rightStride,
                winWidth,
                winHeight,
                disparityOutput,
                minCostOutput,
                allCostOutput,
                width,
                numDisparities,
                disparityStep,
                rowIndex,
                circBufferLen
        );
    }
}
#endif
void vcop_disparity_hammingDistance32_first_row_circ_cn
(
        uint8_t *left,
        uint8_t *right,
        uint16_t leftStride,
        uint16_t rightStride,
        uint8_t winWidth,
        uint8_t winHeight,
        uint8_t *disparityOutput,
        uint16_t *minCostOutput,
        uint16_t *allCostOutput,
        uint16_t width,
        uint16_t allCostOutputStride,
        uint8_t numDisparities,
        uint8_t disparityStep,
        uint16_t rowIndex,
        uint8_t circBufferLen
);

void vcop_disparity_hammingDistance32_RL_first_row_circ_cn
(
        uint8_t *left,
        uint8_t *right,
        uint16_t leftStride,
        uint16_t rightStride,
        uint8_t winWidth,
        uint8_t winHeight,
        uint8_t *disparityOutput,
        uint16_t *minCostOutput,
        uint16_t *allCostOutput,
        uint16_t width,
        uint16_t allCostOutputStride,
        uint8_t numDisparities,
        uint8_t disparityStep,
        uint16_t rowIndex,
        uint8_t circBufferLen
);

void wrapper_vcop_disparity_hammingDistance32_first_row_circ_cn
(
        uint8_t *left,
        uint8_t *right,
        uint16_t leftStride,
        uint16_t rightStride,
        uint8_t winWidth,
        uint8_t winHeight,
        uint8_t *disparityOutput,
        uint16_t *minCostOutput,
        uint16_t *allCostOutput,
        uint16_t width,
        uint16_t allCostOutputStride,
        uint8_t numDisparities,
        uint8_t disparityStep,
        uint16_t rowIndex,
        uint8_t circBufferLen,
        uint8_t rlFlag
);

void vcop_disparity_hammingDistance32_nth_row_circ_cn
(
        uint8_t *left,
        uint8_t *right,
        uint16_t leftStride,
        uint16_t rightStride,
        uint8_t winWidth,
        uint8_t winHeight,
        uint8_t *disparityOutput,
        uint16_t *minCostOutput,
        uint16_t *prevAllCostOutput,
        uint16_t *allCostOutput,
        uint16_t width,
        uint16_t allCostOutputStride,
        uint8_t numDisparities,
        uint8_t disparityStep,
        uint16_t rowIndex,
        uint8_t circBufferLen
);

void vcop_disparity_hammingDistance32_RL_nth_row_circ_cn
(
        uint8_t *left,
        uint8_t *right,
        uint16_t leftStride,
        uint16_t rightStride,
        uint8_t winWidth,
        uint8_t winHeight,
        uint8_t *disparityOutput,
        uint16_t *minCostOutput,
        uint16_t *prevAllCostOutput,
        uint16_t *allCostOutput,
        uint16_t width,
        uint16_t allCostOutputStride,
        uint8_t numDisparities,
        uint8_t disparityStep,
        uint16_t rowIndex,
        uint8_t circBufferLen
);

void wrapper_vcop_disparity_hammingDistance32_nth_row_circ_cn
(
        uint8_t *left,
        uint8_t *right,
        uint16_t leftStride,
        uint16_t rightStride,
        uint8_t winWidth,
        uint8_t winHeight,
        uint8_t *disparityOutput,
        uint16_t *minCostOutput,
        uint16_t *prevAllCostOutput,
        uint16_t *allCostOutput,
        uint16_t width,
        uint16_t allCostOutputStride,
        uint8_t numDisparities,
        uint8_t disparityStep,
        uint16_t rowIndex,
        uint8_t circBufferLen,
        uint8_t rlFlag
);

/*RESET_MISRA("20.1")  -> Reset rule 20.1 for GOTO */


#endif
