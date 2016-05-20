/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/** @file   evelib_fir_filter_2d_scatter_gather.h
 *
 *  @brief  2D FIR filtering with scatter gather EDMA
 *
 */

/**
*  @brief      Apply 2D FIR filter on a given grayscale image
*
*  @param[in]  src             source image pointer
*  @param[in]  srcImageWidth   source image width in pixels
*  @param[in]  srcImageHeight  source image height in pixels
*  @param[in]  srcImagePitch   source image picth in bytes
*  @param[out] dst             destimation image pointer
*  @param[in]  dstImageWidth   destination image width in pixels
*  @param[in]  dstImageHeight  destination image height in pixels
*  @param[in]  dstImagePitch   destination image picth in bytes
*  @param[in]  coeff           filter coefficitents array pointer
*  @param[in]  coeffH          horizontal filter taps (=M in an MxN filter)
*  @param[in]  coeffW          horizontal filter taps (=N in an MxN filter)
*  @param[in]  dnsmplVert      vertical downsample factor
*  @param[in]  dnsmplHorz      horizontal downsample factor (only 1 is supported currently)
*  @param[in]  rndShift        Shift factor for the given set of coefficients.
*
*  @remarks    Grayscale filtering function - 2D FIR filter. This uses scatter gather EDMA internally. This is meant as a test for scatter gather EDMA APIs.
*  @remarks    The performance of this algorithm is best when either the srcImageWidth*srcBytesPP or srcImagePitch is a multiple of 64 or 32.
*
*  @sa         EVELIB_algoDMAScatterGatherInit(), EVELIB_algoDMAScatterGatherProcess(), EVELIB_algoDMAScatterGatherDeInit()
*/
void EVELIB_firFilter2D_scatterGather(
    unsigned char       *src,
    unsigned int        srcImageWidth,
    unsigned int        srcImageHeight,
    int                 srcImagePitch,
    unsigned char       *dst,
    unsigned int        dstImageWidth,
    unsigned int        dstImageHeight,
    int                 dstImagePitch,
    char                coeff[],
    unsigned int        coeffH,
    unsigned int        coeffW,
    unsigned int        dnsmplVert,
    unsigned int        dnsmplHorz,
    int                 rndShift
    );

