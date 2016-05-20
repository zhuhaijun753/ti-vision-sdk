/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*                                                                          */
/*     @file : vcop_multiblock_gradient_xy_cn.h                             */
/*                                                                          */
/*     @brief : This file contains declarations for the C reference         */
/*     function for computing gradients of multiple blocks corresponding to */
/*     different feature/key point                                          */
/*                                                                          */
/*     vcop_multiblock_gradient_xy_cn                                       */
/*         This is the c-reference for the vcop_multiblock_gradient_xy      */
/*         kernel. This routine accepts an 8-bit input image and outputs    */
/*         16-bit gradients along X and Y directions in interleaved format  */
/*         for 'numblocks' wherein each output block is of dimension,       */
/*         4 * (blkWidth) x (blkHeight) wherein a factor of '4' bytes is    */
/*         to denote 2 bytes each for gradient along X and Y directions     */
/*                                                                          */
/*     USAGE:                                                               */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_multiblock_gradient_xy_cn                                  */
/*     (                                                                    */
/*         unsigned char     *pIn,                                          */
/*         short             *pIntlvGradXY,                                 */
/*         unsigned short     inputStride,                                  */
/*         unsigned short     blkWidth,                                     */
/*         unsigned short     blkHeight,                                    */
/*         unsigned short     blkOffset,                                    */
/*         unsigned short     numBlocks                                     */
/*     )                                                                    */
/*                                                                          */
/*     pInput         : Pointer to input image data                         */
/*     pIntlvGradXY   : Pointer to interleaved gradient output per block    */
/*     inputStride    : Stride in the input buffer                          */
/*     blkWidth       : Width of the block for which gradients is computed  */
/*     blkHeight      : Height of the block for which gradients is computed */
/*     blkOffset      : Offset to the start of next block from current block*/
/*     numBlocks      : Number of blocks for which gradients is computed    */
/*                                                                          */
/*     Returns :  None or void.                                             */
/*                                                                          */
/*     @author Venkat R Peddigari (a0393744@ti.com)                         */
/*                                                                          */
/*     @version 1.0 (November 2013) : Base version.                         */
/*                                                                          */
/*==========================================================================*/

#include <stdio.h>
#include <string.h>

void vcop_multiblock_gradient_xy_cn
(
    unsigned char     *pIn,
    short             *pIntlvGradXY,
    unsigned short     inputStride,
    unsigned short     blkWidth,
    unsigned short     blkHeight,
    unsigned short     blkOffset,
    unsigned short     numBlocks
)
{
    int i,j,k;
    int top, left, right, bottom;
    int gradx, grady;

    for(i = 0; i < blkHeight; i++)
    {
        for(j = 0; j < numBlocks; j++)
        {
            for(k = 0; k < blkWidth; k++)
            {
                top    = pIn[i*inputStride+j*blkOffset+k+1];
                left   = pIn[(i+1)*inputStride+j*blkOffset+k];
                right  = pIn[(i+1)*inputStride+j*blkOffset+k+2];
                bottom = pIn[(i+2)*inputStride+j*blkOffset+k+1];

                gradx = right - left;
                grady = bottom - top;

                pIntlvGradXY[i*blkWidth*2 + j*((blkHeight*blkWidth)+((blkWidth+7)/8)*8-(blkWidth))*2+k*2] = gradx;
                pIntlvGradXY[i*blkWidth*2 + j*((blkHeight*blkWidth)+((blkWidth+7)/8)*8-(blkWidth))*2+k*2+1] = grady;
            }
        }
    }


}
