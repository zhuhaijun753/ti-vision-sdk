/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME                                                                 */
/*     vcop_block_statistics_cn                                             */
/*                                                                          */
/*     DESCRIPTION                                                          */
/*         This is the c-reference for the vcop_block_statistics            */
/*     kernel. This routine accepts an 8-bit input image and outputs mean,  */
/*     variance, minimum and maximum for blocks of dimension                */
/*     statBlockWidth x statBlockHeight.                                    */
/*                                                                          */
/*     USAGE                                                                */
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
/*         unsigned char     *pMaximum,                                     */
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
/*==========================================================================*/

#include <stdio.h>
#include <string.h>
#include "vcop_block_statistics_cn.h"

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
    unsigned short    *pMean,          // Q16
    unsigned int      *pVariance       // Q32
)
{
    unsigned short sum;
    unsigned int sqSum;
    unsigned char min, max;
    unsigned int uiRow, uiCol, uiNumPix;
    unsigned int i, j;
    const unsigned char *pPixel;
    unsigned char *pMinimumVal = pMinimum, *pMaximumVal = pMaximum;
    unsigned short *pMeanVal = pMean;
    unsigned int *pVarianceVal = pVariance;

    for (uiRow =0; uiRow < imageHeight; uiRow = uiRow+statBlockHeight) {
        for (uiCol = 0; uiCol< imageWidth; uiCol = uiCol+statBlockWidth) {
            sum = 0;
            sqSum = 0;
            min = 255;
            max = 0;

            for (i = 0; i < statBlockWidth; i++) {
                for (j = 0; j < statBlockHeight; j++) {
                    pPixel = (unsigned char*) &pInput[(uiRow+j)*imageStride + (uiCol+i)];

                    sum += *pPixel;

                    sqSum += ((*pPixel) * (*pPixel));

                    if(min > *pPixel)
                        min = *pPixel;

                    if(max < *pPixel)
                        max = *pPixel;
                }
            }
            uiNumPix = (statBlockWidth * statBlockHeight);

            if (pMeanVal != NULL) {
                *(pMeanVal++) = sum;
                //printf("Mean at     (%d, %d) = %d\n", uiRow/statBlockHeight, uiCol/statBlockWidth, *(pMeanVal-1));
            }

            if (pVarianceVal != NULL) {
                *(pVarianceVal++) = (unsigned int)(uiNumPix*sqSum - (int)(sum*sum));
                //printf("Variance at (%d, %d) = %d\n", uiRow/statBlockHeight, uiCol/statBlockWidth, *(pVarianceVal-1));
            }

            if (pMinimumVal != NULL) {
                *(pMinimumVal++) = min;
            }

            if (pMaximumVal != NULL) {
                *(pMaximumVal++) = max;
            }
        }
    }
}
