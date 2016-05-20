/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/* -------------------------------------------------------------------- */
/* NAME : evelib_fir_filter_2d.c                                        */
/*                                                                      */
/* DESCRIPTION:                                                         */
/*                                                                      */
/* This file contains an FIR filter implementaion                       */
/*                                                                      */
/* Author: Manu Mathew <mathew.manu@ti.com>                             */
/* -------------------------------------------------------------------- */
#include <stdint.h>
#include <vcop/vcop.h>
#include "common/eve_algo_dma_auto_incr.h"
#include "evelib_fir_filter_2d.h"
#include "vcop_filter_kernel.h"


/**
*  @brief      Apply 2D FIR filter on a given grayscale image
*
*  @param[in]  src             source image pointer
*  @param[in]  srcImageWidth   source image width in pixels
*  @param[in]  srcImageHeight  source image height in pixels
*  @param[in]  srcBufferPitch  source image picth in bytes
*  @param[in]  srcBufferHeight source image picth in bytes
*  @params[i]  srcBytesPP      source bytes per pixel (Must be 1 for grayscale. Only 1 is supported.)
*  @param[out] dst             destimation image pointer
*  @param[in]  dstImageWidth   destination image width in pixels
*  @param[in]  dstImageHeight  destination image height in pixels
*  @param[in]  dstBufferPitch  destination image picth in bytes
*  @param[in]  dstBufferHeight destination image picth in bytes
*  @params[in] dstBytesPP      dest bytes per pixel (Must be 1 for grayscale. Only 1 is supported.)
*  @params[in] coeff           filter coefficitents array pointer
*  @params[in] coeffH          horizontal filter taps (=M in an MxN filter)
*  @params[in] coeffV          horizontal filter taps (=N in an MxN filter)
*  @params[in] dnsmplVert      vertical downsample factor
*  @params[in] dnsmplHorz      horizontal downsample factor (only 1 is supported currently)
*  @params[in] rndShift        Shift factor for the given set of coefficients.
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
    )
{
    uint8_t *srcBlk;
    uint8_t *dstBlk;
    char *coeffBlk;

    uint32_t srcBlkPadX = 2;
    uint32_t srcBlkPadY = 2;

    uint32_t srcImageWidthBytes = srcImageWidth * srcBytesPP; //convert to bytes
    uint32_t dstImageWidthBytes = dstImageWidth * dstBytesPP; //convert to bytes

    uint32_t srcBlkWidth = 0;
    uint32_t srcBlkHeight= 0;

    uint32_t srcProcWidth = 0;
    uint32_t srcProcHeight= 0;

    uint32_t perfVal = EVELIB_getBestBlockDimensions(srcImageWidthBytes, srcImageHeight, srcBufferPitch, srcBufferHeight,
        &srcProcWidth, &srcProcHeight, &srcBlkWidth, &srcBlkHeight);

    uint32_t srcBlkPitch = (srcBlkWidth+srcBlkPadX);
    uint32_t srcBlkHeightTot = (srcBlkHeight+srcBlkPadY);

    uint32_t dstBlkWidth  = (srcBlkWidth);
    uint32_t dstBlkHeight = (srcBlkHeight);
    uint32_t dstBlkPitch  = (dstBlkWidth);

    EVELIB_KernelFuncType execFunc[] = {(EVELIB_KernelFuncType)vcop_filter_uchar_char_uchar_vloops};
    EVELIB_KernelContextType context[] = {(EVELIB_KernelContextType)__pblock_vcop_filter_uchar_char_uchar};
    unsigned int numKernels = 1;

    VCOP_BUF_SWITCH_SET (WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST, IBUFHA_SYST, IBUFLA_SYST);

    srcBlk = (unsigned char *)vcop_malloc(VCOP_IBUFLA, srcBlkPitch * srcBlkHeightTot);
    dstBlk = (unsigned char *)vcop_malloc(VCOP_IBUFHA, dstBlkPitch * dstBlkHeight);
    coeffBlk = (char *)vcop_malloc(VCOP_WMEM, coeffH * coeffW);

    memcpy(coeffBlk, coeff, coeffH * coeffW);

    vcop_filter_uchar_char_uchar_init(srcBlk, coeffBlk, dstBlk, srcBlkPitch, coeffW, coeffH, srcBlkWidth,
        srcBlkHeight, dnsmplVert, dnsmplHorz, rndShift, __pblock_vcop_filter_uchar_char_uchar);

    EVELIB_algoDMAAutoIncrInit(
        src,
        srcProcWidth,
        srcProcHeight,
        srcBufferPitch,
        dst,
        dstImageWidthBytes,
        dstImageHeight,
        dstBufferPitch,
        srcBlk,
        srcBlkWidth,
        srcBlkHeight,
        srcBlkPitch,
        dstBlk,
        dstBlkWidth,
        dstBlkHeight,
        dstBlkPitch,
        srcBlkPadX,
        srcBlkPadY);

    EVELIB_algoDMAAutoIncrProcess(
        src,
        srcProcWidth,
        srcProcHeight,
        srcBufferPitch,
        dst,
        dstImageWidthBytes,
        dstImageHeight,
        dstBufferPitch,
        srcBlk,
        srcBlkWidth,
        srcBlkHeight,
        srcBlkPitch,
        dstBlk,
        dstBlkWidth,
        dstBlkHeight,
        dstBlkPitch,
        srcBlkPadX,
        srcBlkPadY,
        execFunc,
        context,
        numKernels,
        0);

    EVELIB_algoDMAAutoIncrDeInit( );


    vcop_free(srcBlk);
    vcop_free(dstBlk);
    vcop_free(coeffBlk);
}

