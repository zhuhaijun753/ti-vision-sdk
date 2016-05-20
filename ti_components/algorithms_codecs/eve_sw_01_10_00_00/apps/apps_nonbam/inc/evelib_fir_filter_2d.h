/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/** @file   evelib_fir_filter_2d.h
 *
 *  @brief  2D FIR filtering Applet
 *
 *  @date   March 2013
 *
 */

/**
*  @brief      Apply 2D FIR filter on a given grayscale image
*
*  @param[in]  src             source image pointer
*  @param[in]  srcImageWidth   source image width in pixels
*  @param[in]  srcImageHeight  source image height in pixels
*  @param[in]  srcBufferPitch  source image picth in bytes
*  @param[in]  srcBufferHeight source image picth in bytes
*  @param[in]  srcBytesPP      source bytes per pixel (Must be 1 for grayscale. Only 1 is supported.)
*  @param[out] dst             destimation image pointer
*  @param[in]  dstImageWidth   destination image width in pixels
*  @param[in]  dstImageHeight  destination image height in pixels
*  @param[in]  dstBufferPitch  destination image picth in bytes
*  @param[in]  dstBufferHeight destination image picth in bytes
*  @param[in]  dstBytesPP      dest bytes per pixel (Must be 1 for grayscale. Only 1 is supported.)
*  @param[in]  coeff           filter coefficitents array pointer
*  @param[in]  coeffH          vertical filter taps (=M in an MxN filter)
*  @param[in]  coeffW          horizontal filter taps (=N in an MxN filter)
*  @param[in]  dnsmplVert      vertical downsample factor
*  @param[in]  dnsmplHorz      horizontal downsample factor (only 1 is supported currently)
*  @param[in]  rndShift        Shift factor for the given set of coefficients.
*
*  @remarks    Grayscale filtering function - 2D FIR filter.
*  @remarks    The performance of this algorithm is best when either the srcImageWidth*srcBytesPP or srcImagePitch is a multiple of 64 or 32.
*
*  @sa         EVELIB_algoDMAAutoIncrInit(), EVELIB_algoDMAAutoIncrProcess(), EVELIB_algoDMAAutoIncrDeInit()
*/
void EVELIB_firFilter2D(
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
    unsigned int        dstBytesPP,
    char                coeff[],
    unsigned int        coeffH,
    unsigned int        coeffW,
    unsigned int        dnsmplVert,
    unsigned int        dnsmplHorz,
    int                 rndShift
    );

