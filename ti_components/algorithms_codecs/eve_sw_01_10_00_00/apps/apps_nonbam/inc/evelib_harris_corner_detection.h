/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/** @file   evelib_harris_corner_detection.h
 *
 *  @brief  Harris Corner Detection Applet
 *
 *  @date   April 2013
 *
 */

/**
*  @brief      Compute corners for a given grayscale image using 
*              Shi & Tomasi corner detector which is based on Harris
*              Corner Detection algorithm
*
*  @param[in]  src                        source image pointer
*  @param[in]  srcImageWidth              source image width in pixels
*  @param[in]  srcImageHeight             source image height in pixels
*  @param[in]  srcBufferPitch             source buffer pitch in bytes
*  @param[in]  srcBufferHeight            source buffer height in bytes
*  @param[in]  srcBytesPP                 source bytes per pixel (Must be 1 for grayscale. Only 1 is supported.)
*  @param[out] dst                        destimation image pointer
*  @param[in]  dstImageWidth              destination image width in pixels
*  @param[in]  dstImageHeight             destination image height in pixels
*  @param[in]  dstBufferPitch             destination buffer pitch in bytes
*  @param[in]  dstBufferHeight            destination buffer height in bytes
*  @param[in]  srcBlkWidth                block width of the source
*  @param[in]  srcBlkHeight               block height of the source
*  @param[in]  dstBytesPP                 dest bytes per pixel (Must be 1 for grayscale. Only 1 is supported.)
*  @param[in]  harrisScoreScalingFactor   scaling factor used by harris score kernel
*  @param[in]  nmsThresh                  threshold parameter for non maximum suppression kernel
*
*  @remarks    Harris corner detector function.
*  @remarks    Currently, the algorithm works fine when srcImageWidth*srcBytesPP or srcImagePitch is a multiple of 16.
*
*  @sa         EVELIB_algoDMAAutoIncrInit(), EVELIB_algoDMAAutoIncrProcess(), EVELIB_algoDMAAutoIncrDeInit()
*/
void EVELIB_harrisCornerDetection(
    unsigned char       *src,
    unsigned int        srcImageWidth,
    unsigned int        srcImageHeight,
    int                 srcBufferPitch,
    int                 srcBufferHeight,
    unsigned int        srcBytesPP,
    unsigned char       *dst,
    unsigned int        dstImageWidth,
    unsigned int        dstImageHeight,
    int                 dstBufferPitch,
    int                 dstBufferHeight,
    unsigned int        srcBlkWidth,
    unsigned int        srcBlkHeight,
    unsigned int        dstBytesPP,
    short               harrisScoreScalingFactor,
    short               nmsThresh
    );

