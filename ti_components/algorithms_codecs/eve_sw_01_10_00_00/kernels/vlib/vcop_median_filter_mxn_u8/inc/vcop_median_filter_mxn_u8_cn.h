/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*                                                                          */
/*     @file : vcop_block_statistics_cn.h                                   */
/*                                                                          */
/*     @brief : This file contains declarations for the C reference         */
/*     function for median filtering for an 8 bit image.                    */
/*                                                                          */
/*     vcop_median_filter_mxn_u8_cn                                         */
/*         This is the c-reference for the vcop_median_filter_mxn_u8        */
/*         kernel. This routine accepts an 8-bit input image and outputs    */
/*         median filtered image.                                           */
/*                                                                          */
/*     USAGE:                                                               */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_median_filter_mxn_u8_cn                                    */
/*     (                                                                    */
/*         unsigned char  *pInput,                                          */
/*         unsigned char  *pMedian,                                         */
/*         unsigned short  blkStride,                                       */
/*         unsigned short  blkWidth,                                        */
/*         unsigned short  blkHeight,                                       */
/*         unsigned char   kernelWidth,                                     */
/*         unsigned char   kernelHeight,                                    */
/*         unsigned short  stepSizeHorz,                                    */
/*         unsigned short  stepSizeVert                                     */
/*     )                                                                    */
/*                                                                          */
/*     pInput          : Input image data                                   */
/*     pMedian         : Median filter output                               */
/*     blkStride       : Stride in the input buffer                         */
/*     blkWidth        : Width in the input buffer                          */
/*     blkHeight       : Height in the input buffer                         */
/*     kernelWidth     : Filtering kernel width                             */
/*     kernelHeight    : Filtering kernel height                            */
/*     stepSizeHorz    : Step in horizontal direction by which the kernel   */
/*                       slides.                                            */
/*     stepSizeVert    : Step in vertical direction by which the kernel     */
/*                       slides.                                            */
/*                                                                          */
/*     Returns :  None or void.                                             */
/*                                                                          */
/*     @version 0.1 (Sept 2013) : Base version.                             */
/*                                                                          */
/*==========================================================================*/

#ifndef _VCOP_MEDIAN_FILTER_CN
#define _VCOP_MEDIAN_FILTER_CN  1

void vcop_median_filter_mxn_u8_cn
(
    unsigned char  *pInput,
    unsigned char  *pMedian,
    unsigned short  blkStride,
    unsigned short  blkWidth,
    unsigned short  blkHeight,
    unsigned char   kernelWidth,
    unsigned char   kernelHeight,
    unsigned short  stepSizeHorz,
    unsigned short  stepSizeVert
);

#endif /* _VCOP_MEDIAN_FILTER_CN */
