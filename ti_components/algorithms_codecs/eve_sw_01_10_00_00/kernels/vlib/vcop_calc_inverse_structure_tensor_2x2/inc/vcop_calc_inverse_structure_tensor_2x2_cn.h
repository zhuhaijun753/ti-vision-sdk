/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*                                                                          */
/*     @file : vcop_calc_inverse_structure_tensor_2x2_cn.h                  */
/*                                                                          */
/*     @brief : This file contains declarations of the C reference          */
/*     function for computing inverse of the 2x2 structure tensor which     */
/*     is being computed over a given neighborhood window (say 7x7) of the  */
/*     gradient image (bilinear interpolated gradient image is used in case */
/*     of LK tracker). It is also referred as second moment matrix.         */
/*                                                                          */
/*     USAGE:                                                               */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     vcop_calc_inverse_structure_tensor_2x2_cn                            */
/*     (                                                                    */
/*        int              *pTensorArrInp,                                  */
/*        uint16_t   *pD_nrsb,                                              */
/*        uint32_t     *pD_norm,                                        */
/*        int16_t            *pInverseArrOut,                               */
/*        uint16_t    inputStride,                                          */
/*        uint16_t    outputStride,                                         */
/*        uint16_t    numKeyPoints                                          */
/*     )                                                                    */
/*                                                                          */
/*     Returns :  None or void.                                             */
/*                                                                          */
/*     @author Venkat R Peddigari (a0393744@ti.com)                         */
/*                                                                          */
/*     @version 1.0 (November 2013) : Base version.                         */
/*                                                                          */
/*==========================================================================*/

#ifndef VCOP_CALC_INVERSE_STRUCTURE_TENSOR_2X2_CN
#define VCOP_CALC_INVERSE_STRUCTURE_TENSOR_2X2_CN  1
/*!

  @fn     vcop_calc_inverse_structure_tensor_2x2_cn

  @brief  This is c-reference for the vcop_calc_inverse_structure_tensor
          _2x2_cn kernel. This routine accepts the determinant represented
          using normalized notation along with 32 bit gradient sums over
          the neighborhood windows namely sumIX2, sumIY2 & sumIXIY wherein
          wherein IX, IY denotes the gradient along X and Y directions for
          'numKeyPoints' and computes sumIX2/D, sumIY2/D and sumIXIY/D for
          each key point using exponential and fractional notation.
          Output storage per key point is as follows:(D imply determinant)
          frac(sumIX2/D)  exp(sumIX2/D)  frac(sumIY2/D)   exp(sumIY2/D)
          frac(sumIXIY/D) exp(sumIXIY/D)
  @param  pSumIx2         : Pointer to sum of squared gradients over
                            neighboorhood window along X direction around
                            each key point
  @param  pSumIy2         : Pointer to sum of squared gradients over
                            neighboorhood window along Y direction around
                            each key point
  @param  pSumIxIy        : Pointer to sum of dot product of gradients along X
                            and Y directions over neighboorhood window around
                            each key point
  @param  pD_nrsb         : Pointer to number of non redundant sign bits
                            within determinant of structure tensor for each
                            key point
  @param  pD_norm         : Pointer to norm of the determinant of structure
                            tensor for each key point
  @param  pSumIx2ByD      : Pointer to fractional and exponential parts of the
                            structure tensor inverse element, SumIx2/D where
                            D is the determinant of the structure tensor
  @param  pSumIy2ByD      : Pointer to fractional and exponential parts of the
                            structure tensor inverse element, SumIy2/D where
                            D is the determinant of the structure tensor
  @param  pSumIxIyByD     : Pointer to fractional and exponential parts of the
                            structure tensor inverse element, SumIxIy/D where
                            D is the determinant of the structure tensor
  @param  numKeyPoints    : Number of key points

*/
void vcop_calc_inverse_structure_tensor_2x2_cn
(
	int32_t          *pTensorArrInp,
    uint16_t   *pD_nrsb,
    uint32_t     *pD_norm,
    int16_t            *pInverseArrOut,
    uint16_t    inputStride,
    uint16_t    outputStride,
    uint16_t    numFracBits,
    uint16_t    numKeyPoints
);

/*!

  @fn     find_leading_bit_for_integer_data

  @brief  This function is a C reference function for computing the leading bit of a given
          integer number
  @param  x         : Input integer for which leading bit needs to be found

*/
uint16_t find_leading_bit_for_integer_data
(
    int32_t x
);

/*!

  @fn     divide_int

  @brief  This function is a C reference function for performing the integer division
          for the given number of integer division bits
  @param  a_norm    : Dividend input
  @param  b_norm    : Divisor input
  @param  n         : Number of integer division bits

*/
int16_t divide_int
(
    int32_t a_norm,
    uint32_t b_norm,
    uint8_t n
);

#endif /* VCOP_CALC_INVERSE_STRUCTURE_TENSOR_2X2_CN */
