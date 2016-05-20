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
/*        uint8_t     *pIn,                                           */
/*        uint8_t     *pInpWts,                                       */
/*        uint8_t     *pOutBilinearInterpImg,                         */
/*        uint16_t     input1Stride,                                  */
/*        uint16_t     input2Stride,                                  */
/*        uint16_t     outputStride,                                  */
/*        uint16_t     blkWidth,                                      */
/*        uint16_t     blkHeight,                                     */
/*        uint16_t     blkOffset,                                     */
/*        uint16_t     numKeyPoints                                   */
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

#ifndef VCOP_MULTIBLOCK_BILINEAR_INTERP_7x7_U8_CN
#define VCOP_MULTIBLOCK_BILINEAR_INTERP_7x7_U8_CN  1
/*!

  @fn     vcop_multiblock_bilinear_interp_7x7_u8_cn

  @brief  This function is a C reference that is used for computing bilinear
          interpolation of image pixels for multiple blocks centered around
          each feature/key point

  @param  pInput                : Pointer to input image data
  @param  pInpWts               : Pointer to bilinear weights for each key point
  @param  pOutBilinearInterpImg : Pointer to bilinear interpolated image pixel
  @param  input1Stride          : Stride of the input buffer, pIn
  @param  input2Stride          : Stride of the input buffer, pInpWts
  @param  outputStride          : Stride of the output buffer, pOutBilinearInterpImg
  @param  blkWidth              : Width of the input block around each key point
  @param  blkHeight             : Height of the input block around each key point
  @param  blkOffset             : Offset to the start of next block from current block
  @param  shiftValue            : Number of bits for trucnation
  @param  numKeyPoints          : Number of key points

*/
void vcop_multiblock_bilinear_interp_7x7_u8_cn
(
    uint8_t     *pIn,                     /* Pointer to input image data                         */
    uint16_t    *pInpWts,                 /* Pointer to bilinear weights for each key point      */
    uint8_t     *pOutBilinearInterpImg,   /* Pointer to bilinear interpolated image pixel        */
    uint16_t     input1Stride,            /* Stride of the input buffer, pIn                     */
    uint16_t     input2Stride,            /* Stride of the input buffer, pInpWts                 */
    uint16_t     outputStride,            /* Stride of the output buffer, pOutBilinearInterpImg  */
    uint16_t     blkWidth,                /* Width of the input block around each key point      */
    uint16_t     blkHeight,               /* Height of the input block around each key point     */
    uint16_t     blkOffset,               /* Offset to the start of next block from current block*/
    uint16_t     shiftValue,              /* Number of bits for trucnation                       */
    uint16_t     numKeyPoints             /* Number of key points                                */
);

#endif /* VCOP_MULTIBLOCK_BILINEAR_INTERP_7x7_U8_CN */
