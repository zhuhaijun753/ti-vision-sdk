/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*                                                                          */
/*     @file : vcop_multiblock_bilinear_interp_7x7_u8_cn.h                  */
/*                                                                          */
/*     @brief : This file contains declarations for the C reference         */
/*     function for computing bilinear interpolation of image pixels for    */
/*     multiple blocks centered around each feature/key point               */
/*                                                                          */
/*     vcop_multiblock_bilinear_interp_7x7_u8_cn                            */
/*         This is the c-reference for the vcop_multiblock_bilinear_interp  */
/*         _u8_cn kernel. This routine accepts multiple blocks of 8-bit     */
/*         image pixels centered around 'numKeyPoints' and the precomputed  */
/*         bilinear weights for each key point to compute the bilinear      */
/*         interpolation of image pixels wherein each output block is of    */
/*         dimension (blkWidth) x (blkHeight). pIn denotes the first pixel  */
/*         location in the first block from where bilinear interpolation is */
/*         computed for output block size and "blkOffset" denotes the offset*/
/*         to the first pixel of the next block for which bilinear          */
/*         interpolation is computed                                        */
/*                                                                          */
/*     USAGE:                                                               */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_multiblock_bilinear_interp_7x7_u8_cn                       */
/*     (                                                                    */
/*        unsigned char     *pIn,                                           */
/*        unsigned char     *pInpWts,                                       */
/*        unsigned char     *pOutBilinearInterpImg,                         */
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
/*     pInput         : Pointer to input image data                         */
/*     pInpWts        : Pointer to bilinear weights for each key point      */
/*     pOutBilinearInterpImg : Pointer to bilinear interpolated image pixel */
/*     input1Stride   : Stride of the input buffer, pIn                     */
/*     input2Stride   : Stride of the input buffer, pInpWts                 */
/*     outputStride   : Stride of the output buffer, pOutBilinearInterpImg  */
/*     blkWidth       : Width of the input block around each key point      */
/*     blkHeight      : Height of the input block around each key point     */
/*     blkOffset      : Offset to the start of next block from current block*/
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

void vcop_multiblock_bilinear_interp_7x7_u8_cn
(
    unsigned char     *pIn,
    unsigned short     *pInpWts,
    unsigned char     *pOutBilinearInterpImg,
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
    unsigned char pix00, pix01, pix10, pix11;
    unsigned short w0, w1, w2, w3;
    unsigned char *row1, *row2;

    for(i = 0; i < numKeyPoints; i++)
    {
        w0 = pInpWts[i];                     //axay
        w1 = pInpWts[input2Stride + i];      //bxay
        w2 = pInpWts[2 * input2Stride + i];  //axby
        w3 = pInpWts[3 * input2Stride + i];  //bxby

        for(j = 0; j < blkHeight; j++)
        {
            row1 = pIn + j*input1Stride + i*blkOffset;
            row2 = row1 + input1Stride;
            for(k = 0; k < blkWidth; k++)
            {
                pix00 = row1[k];   //bb
                pix01 = row1[k+1]; //ab
                pix10 = row2[k];   //ba
                pix11 = row2[k+1]; //aa

                pOutBilinearInterpImg[i*outputStride*(blkHeight)+j*outputStride+k] =
                        (((int) w3 * pix00) + ((int)w2 * pix01) + ((int) w1 * pix10) + ((int)w0 * pix11)) >> shiftValue;
            }
        }
    }
}
