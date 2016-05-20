/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*                                                                          */
/*     @file : vcop_multiblock_bilinear_interp_intlv_7x7_s16_cn.h           */
/*                                                                          */
/*     @brief : This file contains declarations for the C reference         */
/*     function for computing bilinear interpolation of gradient pixels     */
/*     which includes gradient along X and Y stored in interleaved format   */
/*     for multiple blocks centered around each feature/key point           */
/*                                                                          */
/*     vcop_multiblock_bilinear_interp_intlv_7x7_s16_cn                     */
/*         This is the c-reference for the vcop_multiblock_bilinear_interp  */
/*         _intlv_7x7_s16_cn kernel. This routine accepts multiple blocks   */
/*         of 16 bit gradient pixels centered around 'numKeyPoints' and     */
/*         the precomputed bilinear weights for each key point to compute   */
/*         the bilinear interpolation of gradient pixels wherein each       */
/*         output block is of dimension (blkWidth) x (blkHeight)            */
/*                                                                          */
/*     USAGE:                                                               */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_multiblock_bilinear_interp_intlv_7x7_s16_cn                */
/*     (                                                                    */
/*        short             *pIntlvGradXY,                                  */
/*        unsigned short    *pInpWts,                                       */
/*        short             *pGradXBilinearInterpImg,                       */
/*        short             *pGradYBilinearInterpImg,                       */
/*        unsigned short     input1Stride,                                  */
/*        unsigned short     input2Stride,                                  */
/*        unsigned short     outputStride,                                  */
/*        unsigned short     blkWidth,                                      */
/*        unsigned short     blkHeight,                                     */
/*        unsigned short     blkOffset,                                     */
/*        unsigned short     shiftValue,                                    */
/*        unsigned short     numKeyPoints                                   */
/*     )                                                                    */
/*                                                                          */
/*     pIntlvGradXY   : Pointer to interleaved gradient pixel data          */
/*     pInpWts        : Pointer to bilinear weights for each key point      */
/*     pGradXBilinearInterpImg : Pointer to bilinear interpolated GradX     */
/*     pGradYBilinearInterpImg : Pointer to bilinear interpolated GradY     */
/*     input1Stride   : Stride of the input buffer, pIntlvGradXY            */
/*     input2Stride   : Stride of the input buffer, pInpWts                 */
/*     outputStride   : Stride of the output buffers, GradX & GradY         */
/*     blkWidth       : Width of the output block around each key point     */
/*                      in pixels for which bilinear interpolation is       */
/*                      computed                                            */
/*     blkHeight      : Height of the output block around each key point    */
/*                      in pixels for which bilinear interpolation is       */
/*                      computed                                            */
/*     blkOffset      : Offset to the start of next block from current block*/
/*                      in pixels                                           */
/*     numKeyPoints   : Number of key points                                */
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

void vcop_multiblock_bilinear_interp_intlv_7x7_s16_cn
(
    short             *pIntlvGradXY,
    unsigned short    *pInpWts,
    short             *pGradXBilinearInterpImg,
    short             *pGradYBilinearInterpImg,
    unsigned short     input1Stride,
    unsigned short     input2Stride,
    unsigned short     outputStride,
    unsigned short     blkWidth,
    unsigned short     blkHeight,
    unsigned short     blkOffset,
    unsigned short     shiftValue,
    unsigned short     numKeyPoints
)
{
    int i,j,k;
    short pix00GradX, pix01GradX, pix10GradX, pix11GradX;
    short pix00GradY, pix01GradY, pix10GradY, pix11GradY;
    unsigned short w0, w1, w2, w3;
    short *row1, *row2;

    for(i = 0; i < numKeyPoints; i++)
    {
        w0 = pInpWts[i];                     //axay
        w1 = pInpWts[input2Stride + i];      //bxay
        w2 = pInpWts[2 * input2Stride + i];  //axby
        w3 = pInpWts[3 * input2Stride + i];  //bxby

        for(j = 0; j < blkHeight; j++)
        {
            row1 = pIntlvGradXY + j*input1Stride + i*blkOffset;
            row2 = row1 + input1Stride;
            for(k = 0; k < blkWidth; k++)
            {
                pix00GradX = row1[2*k];   //bb
                pix01GradX = row1[2*k+2]; //ab
                pix10GradX = row2[2*k];   //ba
                pix11GradX = row2[2*k+2]; //aa

                pix00GradY = row1[2*k+1]; //bb
                pix01GradY = row1[2*k+3]; //ab
                pix10GradY = row2[2*k+1]; //ba
                pix11GradY = row2[2*k+3]; //aa

                pGradXBilinearInterpImg[i*outputStride*blkHeight+j*outputStride+k] =
                        (((int) w3 * pix00GradX) + ((int)w2 * pix01GradX) + ((int) w1 * pix10GradX) + ((int)w0 * pix11GradX)) >> shiftValue;

                pGradYBilinearInterpImg[i*outputStride*blkHeight+j*outputStride+k] =
                        (((int) w3 * pix00GradY) + ((int)w2 * pix01GradY) + ((int) w1 * pix10GradY) + ((int)w0 * pix11GradY)) >> shiftValue;
            }
        }
    }
}
