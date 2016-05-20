/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*                                                                          */
/*     @file : vcop_block_statistics_cn.h                                   */
/*                                                                          */
/*     @brief : This file contains declarations for the C reference         */
/*     function for block statistics for an 8 bit image.                    */
/*                                                                          */
/*     vcop_block_statistics_cn                                             */
/*         This is the c-reference for the vcop_block_statistics            */
/*         kernel. This routine accepts an 8-bit input image and outputs    */
/*         mean, variance, minimum and maximum for blocks of dimension      */
/*         statBlockWidth x statBlockHeight.                                */
/*                                                                          */
/*     USAGE:                                                               */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_block_statistics_cn                                        */
/*     (                                                                    */
/*         unsigned char     *pInput,                                       */
/*         unsigned short     imageStride,                                  */
/*         unsigned short     imageWidth,                                   */
/*         unsigned short     imageHeight,                                  */
/*         unsigned short     statBlockWidth,                               */
/*         unsigned short     statBlockHeight,                              */
/*         unsigned char     *pMinimum,                                     */
/*         unsigned char     *pMaximum,                                      */
/*         unsigned short    *pMean,                                        */
/*         unsigned short    *pVariance                                     */
/*     )                                                                    */
/*                                                                          */
/*     pInput          : Input image data                                   */
/*     imageStride     : Stride in the input buffer                         */
/*     imageWidth      : Width in the input buffer                          */
/*     imageHeight     : Height in the input buffer                         */
/*     statBlockWidth  : Width of the block over which stats are computed   */
/*     statBlockHeight : Height of the block over which stats are computed  */
/*     pMinimum        : Array of Block minimas                             */
/*     pMaximum        : Array of Block maximas                             */
/*     pMean           : Array of Block means (Q16)                         */
/*     pVariance       : Array of Block variances (Q32)                     */
/*                                                                          */
/*     Returns :  None or void.                                             */
/*                                                                          */
/*     @version 0.1 (Sept 2013) : Base version.                             */
/*                                                                          */
/*==========================================================================*/

#ifndef _VCOP_BLOCK_STATISTICS_CN
#define _VCOP_BLOCK_STATISTICS_CN  1

void vcop_block_statistics_cn
(
    unsigned char     *pInput,
    unsigned short     imageStride,
    unsigned short     imageWidth,
    unsigned short     imageHeight,
    unsigned short     statBlockWidth,
    unsigned short     statBlockHeight,
    unsigned char     *pMinimum,
    unsigned char     *pMaximum,
    unsigned short    *pMean,
    unsigned int      *pVariance
);

#endif /* _VCOP_BLOCK_STATISTICS_CN */
