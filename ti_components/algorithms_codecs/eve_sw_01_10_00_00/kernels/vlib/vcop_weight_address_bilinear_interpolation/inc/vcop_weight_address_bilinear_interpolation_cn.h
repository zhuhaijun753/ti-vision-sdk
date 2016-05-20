/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*                                                                          */
/*     @file : vcop_weight_address_bilinear_interpolation_cn.h              */
/*                                                                          */
/*     @brief : This file contains declarations for the C reference         */
/*     function for computing weights and base address of each block        */
/*     corresponding to different feature/key point. These weights and      */
/*     updated base address will be used during bilinear interpolation of   */
/*     frame for which the base address and weights change due to iterative */
/*     update of the X and Y coordinates such as in LK tracker              */
/*                                                                          */
/*     vcop_weight_address_bilinear_interpolation_cn                        */
/*         This is the c-reference for the vcop_weight_address_bilinear     */
/*         _interpolation_cn kernel. This routine accepts an X coordinate,  */
/*         Y coordinate lists of length 'numKeyPoints' along with base      */
/*         address of each block and computes weights and updated base      */
/*         address that will be used for bilinear interpolation of image    */
/*                                                                          */
/*     USAGE:                                                               */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_weight_address_bilinear_interpolation_cn                   */
/*     (                                                                    */
/*       unsigned short    *pXYList,                                        */
/*       unsigned int      *pBaseAddrList,                                  */
/*       unsigned char     *pOutWts,                                        */
/*       unsigned int      *pOutBaseAddress,                                */
/*       unsigned short     numKeyPoints,                                   */
/*       unsigned short     qFormatMaxFactor,                               */
/*       unsigned short     qShift,                                         */
/*       unsigned short     blkStride,                                      */
/*       unsigned short     outputStride                                    */
/*     )                                                                    */
/*                                                                          */
/*     pXYList          : Pointer to (X,Y) Coordinate list of key points    */
/*     pBaseAddrList    : Pointer to base address list of key points        */
/*     pOutWts          : Pointer to output weights for each key point      */
/*                        Buffer Size = 4 * outputStride                    */
/*                        w0, w1, w2, w3 are four outputs for key point     */
/*     pOutBaseAddress  : Pointer to updated base address output for each   */
/*                        key point                                         */
/*     numKeyPoints     : Number of key points                              */
/*     qFormatMaxFactor : Maximum scale factor for given Q format           */
/*                        Q4 format => 4 bits for fraction,                 */
/*                        qFormatMaxFactor = (2)^4 - 1 = 15                 */
/*     qShift           : Number of fractional bits in X,Y coordinates      */
/*     blkStride        : Stride of the block input                         */
/*     outputStride     : Stride of the output buffer, should be greater    */
/*                        than or equal to 'numKeyPoints'                   */
/*                                                                          */
/*     Returns :  None or void.                                             */
/*                                                                          */
/*     @author Venkat R Peddigari (a0393744@ti.com)                         */
/*                                                                          */
/*     @version 1.0 (November 2013) : Base version.                         */
/*                                                                          */
/*==========================================================================*/

#ifndef _VCOP_WEIGHT_ADDRESS_BILINEAR_INTERPOLATION_CN
#define _VCOP_WEIGHT_ADDRESS_BILINEAR_INTERPOLATION_CN  1
/*!

  @fn     vcop_weight_address_bilinear_interpolation_cn

  @brief  This function is a C reference that is used for computing weights
          and base address of each block corresponding to different feature/key
          point. These weights and updated base address will be used during
          bilinear interpolation of frame for which the base address and weights
          change due to iterative update of the X and Y coordinates such as in
          LK tracker
  @param  pXYList          : Pointer to (X,Y) Coordinate list of key points
  @param  pBaseAddrList    : Pointer to base address list of key points
  @param  pOutWts          : Pointer to output weights for each key point
  @param  pOutBaseAddress  : Pointer to updated base address output for each key point
  @param  numKeyPoints     : Number of key points
  @param  qFormatMaxFactor : Maximum scale factor for given Q format
                             Q4 format => 4 bits for fraction,
                             qFormatMaxFactor = (2)^4 - 1 = 15
  @param  qShift           : Number of fractional bits in X,Y coordinates
  @param  blkStride        : Stride of the input block
  @param  outputStride     : Stride of the output buffer

*/
void vcop_weight_address_bilinear_interpolation_cn
(
    unsigned short    *pXList,             /* Pointer to (X) Coordinate list of key points            */
    unsigned short    *pYList,             /* Pointer to (Y) Coordinate list of key points            */
    unsigned int      *pBaseAddrList,      /* Pointer to base address list of key points                */
    unsigned int      *pOutAddrList,       /* Pointer to Out address list of key points                */
    unsigned short    *pOutWts,            /* Pointer to output weights for each key point              */
    unsigned int      *pOutBaseAddress,    /* Pointer to updated base address output for each key point */
    unsigned short    *pParamBlkOffsetVec,
    unsigned short     numKeyPoints,       /* Number of key points                                      */
    unsigned short     qFormatMaxFactor,   /* Maximum scale factor for given Q format                   */
    unsigned short     truncateBits,
    unsigned short     qShift,             /* Number of fractional bits in X,Y coordinates              */
    unsigned short     blkStride,          /* Stride of the input block                                 */
    unsigned short     outputStride        /* Stride of the output buffer                               */
);

#endif /* _VCOP_WEIGHT_ADDRESS_BILINEAR_INTERPOLATION_CN */
