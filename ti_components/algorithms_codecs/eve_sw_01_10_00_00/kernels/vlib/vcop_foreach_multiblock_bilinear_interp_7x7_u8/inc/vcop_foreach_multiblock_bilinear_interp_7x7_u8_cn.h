/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*                                                                          */
/*     @file : vcop_foreach_multiblock_bilinear_interp_7x7_u8_cn.h          */
/*                                                                          */
/*     @brief : This file contains declarations for the C reference         */
/*     function for computing bilinear interpolation of image pixels for    */
/*     multiple blocks centered around each feature/key point               */
/*                                                                          */
/*     vcop_foreach_multiblock_bilinear_interp_7x7_u8_cn                    */
/*         This is the c-reference for the vcop_foreach_multiblock_bilinear */
/*         _interp_7x7_u8_cn kernel. This routine accepts multiple blocks   */
/*         of 8-bit image pixels centered around 'numKeyPoints', precomputed*/
/*         bilinear weights for each key point and the updated base address */
/*         corresponding to the start pixel of the output block for which   */
/*         bilinear interpolation has to be performed. It should be noted   */
/*         that the output block lies within the input block wherein the    */
/*         output block is of dimension outBlkWidth x outBlkHeight.         */
/*         Each input block has a stride of input1Stride.                   */
/*                                                                          */
/*     USAGE:                                                               */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_foreach_multiblock_bilinear_interp_7x7_u8_cn               */
/*     (                                                                    */
/*        unsigned char     *pIn[],                                         */
/*        unsigned char     *pInpWts,                                       */
/*        unsigned char     *pOutBilinearInterpImg,                         */
/*        unsigned short     input1Stride,                                  */
/*        unsigned short     input2Stride,                                  */
/*        unsigned short     outputStride,                                  */
/*        unsigned short     outBlkWidth,                                   */
/*        unsigned short     outBlkHeight,                                  */
/*        unsigned short     shiftValue,                                    */
/*        unsigned short     numKeyPoints                                   */
/*     )                                                                    */
/*                                                                          */
/*     pIn            : List of Pointers to input image data,               */
/*                      output from "vcop_weight_address_bilinear_          */
/*                      interpolation_cn"                                   */
/*     pInpWts        : Pointer to bilinear weights for each key point,     */
/*                      output from "vcop_weight_address_bilinear_          */
/*                      interpolation_cn"                                   */
/*     pOutBilinearInterpImg : Pointer to bilinear interpolated image pixel */
/*     input1Stride   : Stride of the input buffer, pIn                     */
/*     input2Stride   : Stride of the input buffer, pInpWts                 */
/*     outputStride   : Stride of the output buffer, pOutBilinearInterpImg  */
/*     outBlkWidth    : Width of the output block around each key point     */
/*     outBlkHeight   : Height of the output block around each key point    */
/*     numKeyPoints   : Number of key points                                */
/*                                                                          */
/*     Returns :  None or void.                                             */
/*                                                                          */
/*     @author Venkat R Peddigari (a0393744@ti.com)                         */
/*                                                                          */
/*     @version 1.0 (November 2013) : Base version.                         */
/*                                                                          */
/*==========================================================================*/

#ifndef _VCOP_FOREACH_MULTIBLOCK_BILINEAR_INTERP_7x7_U8_CN
#define _VCOP_FOREACH_MULTIBLOCK_BILINEAR_INTERP_7x7_U8_CN  1
/*!

  @fn     vcop_foreach_multiblock_bilinear_interp_7x7_u8_cn

  @brief  This function is a C reference that is used for computing bilinear
          interpolation of image pixels for multiple blocks centered around
          each feature/key point. It should be noted that each key point need
          not be in the center of the input block of dimensions

  @param  pIn[]                 : List of Pointers to input image data,          
                                  output from "vcop_weight_address_bilinear_     
                                  interpolation_cn"                              
  @param  pInpWts               : Pointer to bilinear weights for each key point,
                                  output from "vcop_weight_address_bilinear_     
                                  interpolation_cn"                              
  @param  pOutBilinearInterpImg : Pointer to bilinear interpolated image pixel
  @param  input1Stride          : Stride of the input buffer, pIn                   
  @param  input2Stride          : Stride of the input buffer, pInpWts               
  @param  outputStride          : Stride of the output buffer, pOutBilinearInterpImg
  @param  outBlkWidth           : Width of the output block around each key point   
  @param  outBlkHeight          : Height of the output block around each key point  
  @param  numKeyPoints          : Number of key points                              

*/
void vcop_foreach_multiblock_bilinear_interp_7x7_u8_cn
(
    unsigned char     *pIn[],                   /* List of Pointers to input image data,               */
                                                /* output from "vcop_weight_address_bilinear_          */
                                                /* interpolation_cn"                                   */
    unsigned short    *pInpWts,                 /* Pointer to bilinear weights for each key point,     */
                                                /* output from "vcop_weight_address_bilinear_          */
                                                /* interpolation_cn"                                   */
    unsigned char     *pOutBilinearInterpImg,   /* Pointer to bilinear interpolated image pixel        */
    unsigned short     input1Stride,            /* Stride of the input buffer, pIn                     */
    unsigned short     input2Stride,            /* Stride of the input buffer, pInpWts                 */
    unsigned short     outputStride,            /* Stride of the output buffer, pOutBilinearInterpImg  */
    unsigned short     outBlkWidth,             /* Width of the output block around each key point     */
    unsigned short     outBlkHeight,            /* Height of the output block around each key point    */
    unsigned short     shiftValue,              /* Shift Value for trucncation                         */
    unsigned short     numKeyPoints             /* Number of key points                                */
);

#endif /* _VCOP_FOREACH_MULTIBLOCK_BILINEAR_INTERP_7x7_U8_CN */
