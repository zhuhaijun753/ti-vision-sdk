/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) < (b) ? (b) : (a))
#define NUM_BANKS (8)
#define NUM_COPIES (8)
#include "vcop_contrast_stretching_cn.h"

/**
 *******************************************************************************
 *  @func          vcop_histogram_8c_word_cn
 *  @brief         This is function is reference C Implementation of histogram for 8 bit
 *                    gray scale image. This function gives a 32 bit histogram for 8 bit
 *                    input image data.
 *  @param [in]   inputImage : Pointer to input image
 *  @param [in]   width   : Width of input Image
 *  @param [in]   height   : Height of input Image
 *  @param [in]   inPitch   : Pitch of input Image
 *  @param [out] histogram8Copy   : Pointer to the output 8 copy histogram
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t vcop_histogram_8c_word_cn(uint8_t * inputData,
                            uint16_t  width,
                            uint16_t  height,
                            uint16_t  inPitch,
                            uint32_t * histogram8Copy)
{
  uint32_t i,j,k;
  uint8_t  binNum;
  uint32_t histCount;

  for (i = 0; i < height; i++)
  {
    for (j=0; j < width/NUM_COPIES; j++)
    {
      for ( k = 0 ; k < NUM_COPIES ; k++)
      {
        binNum = inputData[(i * inPitch) + (NUM_COPIES * j + k)];
        histCount = histogram8Copy[binNum * NUM_BANKS + k];
        histCount++;
        histogram8Copy[binNum * NUM_BANKS + k] = histCount;
      }

    }
  }

  return 0;
}


/**
 *******************************************************************************
 *  @func          vcop_contrast_stretching_cn
 *  @brief         This is function is reference C Implementation of contrast stretching kernel.
 *  @param [in]   inputImage : Pointer to input image
 *  @param [out] outputImage : Pointer to output image
 *  @param [in]   width   : Width of input Image
 *  @param [in]   height   : Height of input Image
 *  @param [in]   inPitch   : Pitch of input Image
 *  @param [in]   outPitch   : Pitch of output Image
 *  @param [in]  minVal   : Minimum value of the histogram for stretching
 *  @param [in]  scaleFactorQ16   : Scaling factor in Q16 format. Scale factor is
 *                                             calculated using following formula.
 *                               1 / ( maxVal - minVal) in Q16 format;
 *
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
int32_t vcop_contrast_stretching_cn(uint8_t * inputImage,
                            uint8_t * outputImage,
                            uint16_t  width,
                            uint16_t  height,
                            uint16_t  inPitch,
                            uint16_t  outPitch,
                            uint32_t  minVal,
                            uint32_t  scaleFactorQ16)

{
  int32_t status = 0;
  uint32_t i, j;
  uint8_t pixVal;
  int32_t pixDiff;
  uint32_t remappedValQ16;
  uint32_t outPixelVal;

  for(i = 0; i < height; i++)
  {
    for(j = 0; j < width; j++)
    {
      pixVal = inputImage[j + ( i * inPitch )];
      pixDiff = (pixVal - minVal);
      pixDiff = ( pixDiff < 0 ) ? 0:  pixDiff;

      remappedValQ16 =  pixDiff * scaleFactorQ16 * MAX_PIXEL_VAL;
      outPixelVal = ( remappedValQ16 + (1 << 15) ) >> 16;

      outPixelVal = ( outPixelVal > MAX_PIXEL_VAL ) ? MAX_PIXEL_VAL : outPixelVal;

      outputImage[j + (i * outPitch)] = outPixelVal;
    }
  }

  return (status);
}

/**
 *******************************************************************************
 *  @func          vcop_histogram_8c_word_sum_cn
 *  @brief         This is function is reference C Implementation of summing 8 histogram
 *                    generated using 8 channel histrogram to generate a single histogram
 *  @param [in] histogram8Copy   : Pointer to the output 8 copy histogram
 *  @param [out] histogram   : Pointer to single copy of histogram
 *  @return        status of the function execution 0: SUCCESS, <0 Error
 *  @remarks
 *              -# None
 *******************************************************************************
 */
void vcop_histogram_8c_word_sum_cn
(
    uint32_t  *histogram8Copy,
    uint32_t  *histogram
)
{
  uint32_t i;
  uint32_t j;

  /* Sum all 8 copy histogram to get final histrogram */
  for ( i = 0 ; i < 256 ; i++ )
  {
    histogram[i] = 0;
    for (j = 0 ; j < 8 ; j++)
    {
      histogram[i] += histogram8Copy[j + (i*8)];
    }
  }

}

