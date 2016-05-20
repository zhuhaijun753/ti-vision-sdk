/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*                                                                          */
/*     @file : vcop_weight_computation_cn.h                                 */
/*                                                                          */
/*     @brief : This file contains declarations for the C reference         */
/*     function for computing weights corresponding to different feature/key*/
/*     point. These weights will be used during bilinear interpolation      */
/*                                                                          */
/*     vcop_weight_computation_cn                                           */
/*         This is the c-reference for the vcop_weight_computation_cn       */
/*         kernel. This routine accepts an X coordinate and Y coordinate    */
/*         lists of length 'numKeyPoints' and computes weights used for     */
/*         bilinear interpolation of image or gradient pixels               */
/*                                                                          */
/*     USAGE:                                                               */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_weight_computation_cn                                      */
/*     (                                                                    */
/*        uint16_t    *pXYList,                                       */
/*        uint8_t     *pOutWts,                                       */
/*        uint16_t     numKeyPoints,                                  */
/*        uint16_t     qFormatMaxFactor                               */
/*        uint16_t     outputStride                                   */
/*     )                                                                    */
/*                                                                          */
/*     pXYList          : Pointer to (X,Y) Coordinate list of key points    */
/*     pOutWts          : Pointer to output weights for each key point      */
/*                        Buffer Size = 4 * outputStride                    */
/*                        w0, w1, w2, w3 are four outputs for key point     */
/*     numKeyPoints     : Number of key points                              */
/*     qFormatMaxFactor : Maximum scale factor for given Q format           */
/*                        Q4 format => 4 bits for fraction,                 */
/*                        qFormatMaxFactor = (2)^4 - 1 = 15                 */
/*     outputStride     : Stride in the output buffer, should be greater    */
/*                        than or equal to 'numKeyPoints'                   */
/*                                                                          */
/*     Returns :  None or void.                                             */
/*                                                                          */
/*     @author Venkat R Peddigari (a0393744@ti.com)                         */
/*                                                                          */
/*     @version 1.0 (November 2013) : Base version.                         */
/*                                                                          */
/*==========================================================================*/

#ifndef VCOP_WEIGHT_COMPUTATION_CN
#define VCOP_WEIGHT_COMPUTATION_CN  1
/*!

  @fn     vcop_weight_computation_cn

  @brief  This function is a C reference that is used to compute weights for
          each key point that need to be used during bilinear interpolation of
          image or gradient pixels
  @param  pXYList          : Pointer to (X,Y) Coordinate list of key points
  @param  pOutWts          : Pointer to output weights for each key point
  @param  numKeyPoints     : Number of key points
  @param  qFormatMaxFactor : Maximum scale factor for given Q format
                             Q4 format => 4 bits for fraction,
                             qFormatMaxFactor = (2)^4 - 1 = 15
  @param  outputStride     : Stride in the output buffer

*/
void vcop_weight_computation_cn
(
    uint16_t    *pXYList,            /* Pointer to (X,Y) Coordinate list of key points   */
    uint16_t    *pOutWts,            /* Pointer to output weights for each key point     */
    uint16_t     numKeyPoints,       /* Number of key points                             */
    uint16_t     qFormatMaxFactor,   /* Maximum scale factor for given Q format          */
    uint16_t     truncateBits,
    uint16_t     outputStride        /* Stride in the output buffer                      */
);

#endif /* VCOP_WEIGHT_COMPUTATION_CN */
