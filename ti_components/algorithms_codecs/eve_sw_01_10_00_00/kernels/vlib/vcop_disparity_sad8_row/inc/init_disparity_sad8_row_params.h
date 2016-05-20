/*==========================================================================*/
/*      Copyright (C) 2009-2014 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *******************************************************************************
 *  @func          init_disparity_sad8_row_params
 *  @brief         This function initializes and checks the validity of some of the parameters passed to vcop_disparity_sad8_row()
 *
 *  @param [out]   pOffset : Pointer to offset array that will be used by p-scatter and is filled by init_disparity_sad8_row_params()
 *  @param [in]    sizeOffsetArray : sizeOffsetArray should be set to 32 bytes, this parameter is checked by init_disparity_sad8_row_params() prior to filling pOffset 
 *  @param [out]   collateMask : Pointer to single byte that will be filled by  init_disparity_sad8_row_params
 *  @param [out]   scratchBufferSize : size of scratch buffers scratch0 and scratch1 that will be passed to vcop_disparity_sad8_row() will be returned into *scratchBufferSize
 *  @param [out]   scratchBufferStride :  stride of scratch buffers scratch0 and scratch1 that will be passed to vcop_disparity_sad8_row() will be returned into *scratchBufferStride
 *  @param [out]   allCostOutputStride: value allCostOutputStride that will be passed to vcop_disparity_sad8_row() will be returned into *allCostOutputStride 
 *  @param [out]   allCostOutputBufferSize: size of allCostOutputBuffer that will be passed to vcop_disparity_sad8_row() will be returned into *allCostOutputBufferSize 
 *  @param [in]    width: Number of pixels in the row for which disparities are calculated
 *  @param [in]    numDisparities: number of disparities
 *  @param [in]    disparityStep: disparity step
 *  @return        None
 *******************************************************************************
 */
#ifndef _INIT_DISPARITY_SAD_8_H_
#define _INIT_DISPARITY_SAD_8_H_

#include <stdint.h>

#define SIZE_COST 2 /* disparity cost is 2 bytes */

int32_t init_disparity_sad8_row_params
(
        uint16_t *pOffset,  /* Pointer to offset array that will be used by p-scatter and is filled by init_disparity_sad8_row_params() */
        uint8_t sizeOffsetArray, /* sizeOffsetArray should be set to 32 bytes, this parameter is checked by init_disparity_sad8_row_params() prior to filling pOffset */
        uint8_t *collateMask, /* Pointer to single byte that will be filled by  init_disparity_sad8_row_params */
        uint16_t *scratchBufferSize, /* size of scratch buffers scratch0 and scratch1 that will be passed to vcop_disparity_sad8_row() will be returned into *scratchBufferSize */
        uint16_t *scratchBufferStride, /* stride of scratch buffers scratch0 and scratch1 that will be passed to vcop_disparity_sad8_row() will be returned into *scratchBufferStride */
        uint16_t *allCostOutputStride, /* value allCostOutputStride that will be passed to vcop_disparity_sad8_row() will be returned into *allCostOutputStride */
        uint16_t *allCostOutputBufferSize, /* size of allCostOutputBuffer that will be passed to vcop_disparity_sad8_row() will be returned into *allCostOutputBufferSize */
        uint16_t width, /* Number of pixels in the row for which disparities are calculated */
        uint8_t numDisparities, /* number of disparities */
        uint8_t disparityStep /* disparity step */
);

#endif
