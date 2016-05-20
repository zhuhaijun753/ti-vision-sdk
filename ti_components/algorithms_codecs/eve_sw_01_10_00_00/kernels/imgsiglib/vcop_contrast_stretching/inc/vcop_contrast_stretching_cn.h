/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*                                                                          */
/*  @file : vcop_contrast_stretching_cn.h                                              */
/*                                                                          */
/*  @brief : This file contains declarations for the C reference            */
/*  functions for a contrast stretching.                   */
/*                                                                          */
/*  @version 0.1 (May 2014) : Base version.                                 */
/*                                                                          */
/*==========================================================================*/

#ifndef VCOP_CONTRAST_STRETCHING_CN_
#define VCOP_CONTRAST_STRETCHING_CN_

#define MAX_PIXEL_VAL (255)

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
                            uint32_t * histogram8Copy);



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
                            uint32_t  scaleFactorQ16);

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
);

#endif /* VCOP_CONTRAST_STRETCHING_CN_ */

