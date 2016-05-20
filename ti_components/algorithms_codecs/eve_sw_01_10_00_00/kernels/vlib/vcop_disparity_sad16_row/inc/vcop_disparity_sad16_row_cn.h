/*==========================================================================*/
/*      Copyright (C) 2009-2014 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *******************************************************************************
 *  @func          vcop_disparity_sad16_row_cn
 *  @brief         The function vcop_disparity_sad16_row_cn takes two input image rows,          
 * left and right and compute the disparity and kinimum SAD cost for every pixel 
 * Use this function for the very first row of the image                        
 * Subsequent row should use vcop_disparity_sad16_row_iterative_cn() in the same file .
 *
 *
 *  @param [in]    left : Pointer to row from left image 
 *  @param [in]    right : Pointer to row from right image
 *  @param [in]    leftStride : Stride of the left row, need to be greater or equal to width + winWidth-1
 *  @param [in]    rightStride : Stride of the right row, need to be greater or equal to width + numDisparities - 1 + winWidth-1 
 *  @param [in]    winWidth : width of the support window used for SAD calculation
 *  @param [in]    winHeight : height of the support window used for SAD calculation
 *  @param [in]    disparityOutput: pointer to disparity found for every pixels. Size is (numDisparities/disparityStep) bytes
 *  @param [in]    minCostOutput: pointer to minimum cost corresponding to the disparity found for every pixel. Size is 4*(numDisparities/disparityStep) bytes 
 *  @param [in]    allCostOutput: size must be equal 4*(numDisparities/disparityStep )*width bytes
 *  @param [in]    width: number of pixels in the row for which disparities are produced 
 *  @param [in]    numDisparities: Number of disparities. Note that actual number of disparities produced is numDisparities/disparityStep
 *  @param [in]    disparityStep: Disparity step, for faster computation
 *  @return        None
 *******************************************************************************
 */


#ifndef _VCOP_DISPARITY_SAD_16_CN_H_
#define _VCOP_DISPARITY_SAD_16_CN_H_

#include <stdint.h>

void vcop_disparity_sad16_row_ref_cn
(
        uint16_t *left,
        uint16_t *right,
        uint16_t leftStride,
        uint16_t rightStride,
        uint8_t winWidth,
        uint8_t winHeight,
        uint8_t *disparityOutput,
        uint32_t *minCostOutput,
        uint32_t *allCostOutput,
        uint16_t width,
        uint8_t numDisparities,
        uint8_t disparityStep
);

void vcop_disparity_sad16_first_row_cn
(
        uint16_t *left,
        uint16_t *right,
        uint16_t leftStride,
        uint16_t rightStride,
        uint8_t winWidth,
        uint8_t winHeight,
        uint8_t *disparityOutput,
        uint32_t *minCostOutput,
        uint32_t *allCostOutput,
        uint16_t width,
        uint16_t allCostOutputStride,
        uint8_t numDisparities,
        uint8_t disparityStep
);

void vcop_disparity_sad16_nth_row_cn
(
        uint16_t *left,
        uint16_t *right,
        uint16_t leftStride,
        uint16_t rightStride,
        uint8_t winWidth,
        uint8_t winHeight,
        uint8_t *disparityOutput,
        uint32_t *minCostOutput,
        uint32_t *prevAllCostOutput,
        uint32_t *allCostOutput,
        uint16_t width,
        uint16_t allCostOutputStride,
        uint8_t numDisparities,
        uint8_t disparityStep
);

#endif
