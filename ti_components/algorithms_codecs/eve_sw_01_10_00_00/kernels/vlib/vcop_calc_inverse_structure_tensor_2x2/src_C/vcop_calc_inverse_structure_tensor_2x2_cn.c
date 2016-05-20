/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*                                                                          */
/*     @file : vcop_calc_inverse_structure_tensor_2x2_cn.h                  */
/*                                                                          */
/*     @brief : This file contains declarations for the C reference         */
/*     function for computing inverse of the 2x2 structure tensor which     */
/*     is being computed over a given neighborhood window (say 7x7) of the  */
/*     gradient image (bilinear interpolated gradient image is used in case */
/*     of LK tracker). It is also referred as second moment matrix.         */
/*                                                                          */
/*     vcop_calc_inverse_structure_tensor_2x2_cn                            */
/*         This is c-reference for the vcop_calc_inverse_structure_tensor   */
/*         _2x2_cn kernel. This routine accepts the determinant represented */
/*         using normalized notation along with 32 bit gradient sums over   */
/*         the neighborhood windows namely sumIX2, sumIY2 & sumIXIY wherein */
/*         wherein IX, IY denotes the gradient along X and Y directions for */
/*         'numKeyPoints' and computes sumIX2/D, sumIY2/D and sumIXIY/D for */
/*         each key point using exponential and fractional notation.        */
/*         Output storage per key point is as follows:(D imply determinant) */
/*         frac(sumIX2/D)  exp(sumIX2/D)  frac(sumIY2/D)   exp(sumIY2/D)    */
/*         frac(sumIXIY/D) exp(sumIXIY/D)                                   */
/*                                                                          */
/*     USAGE:                                                               */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_calc_inverse_structure_tensor_2x2_cn                       */
/*     (                                                                    */
/*        int              *pSumIx2,                                        */
/*        int              *pSumIy2,                                        */
/*        int              *pSumIxIy,                                       */
/*        unsigned short   *pD_nrsb,                                        */
/*        int              *pD_norm,                                        */
/*        short            *pSumIx2ByD,                                     */
/*        short            *pSumIy2ByD,                                     */
/*        short            *pSumIxIyByD,                                    */
/*        unsigned short    numKeyPoints                                    */
/*     )                                                                    */
/*                                                                          */
/*     pSumIx2          : Pointer to sum of squared gradients over          */
/*                        neighboorhood window along X direction around     */
/*                        each key point                                    */
/*     pSumIy2          : Pointer to sum of squared gradients over          */
/*                        neighboorhood window along Y direction around     */
/*                        each key point                                    */
/*     pSumIxIy         : Pointer to sum of dot product of gradients along X*/
/*                        and Y directions over neighboorhood window around */
/*                        each key point                                    */
/*     pD_nrsb          : Pointer to number of non redundant sign bits      */
/*                        within determinant of structure tensor for each   */
/*                        key point                                         */
/*     pD_norm          : Pointer to norm of the determinant of structure   */
/*                        tensor for each key point                         */
/*     pSumIx2ByD       : Pointer to fractional and exponential parts of the*/
/*                        structure tensor inverse element, SumIx2/D where  */
/*                        D is the determinant of the structure tensor      */
/*     pSumIy2ByD       : Pointer to fractional and exponential parts of the*/
/*                        structure tensor inverse element, SumIy2/D where  */
/*                        D is the determinant of the structure tensor      */
/*     pSumIxIyByD      : Pointer to fractional and exponential parts of the*/
/*                        structure tensor inverse element, SumIxIy/D where */
/*                        D is the determinant of the structure tensor      */
/*     numKeyPoints     : Number of key points                              */
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

#define M2_DIVIDE_BITS 9

unsigned short find_leading_bit_for_integer_data(int x)
{
    unsigned char n = 0;
    if(x < 0)
    {
        while(x<0)
        {
            x = x << 1;
            n++;
        }
    }
    else
    {
        while(x>=0 && n <32)
        {
            x = x << 1;
            n++;
        }
    }
    return n-1;
}

short divide_int(int a_norm, unsigned int b_norm, unsigned char n)
{
    unsigned char i, sign;
    short quotient = 0;
    unsigned int dividend;
    unsigned int divider = b_norm;

    if(a_norm < 0)
    {
        dividend = -a_norm;
        sign = 1;
    }
    else
    {
        dividend = a_norm;
        sign = 0;
    }

    for(i=0; i<n; i++)
    {
        if(dividend > divider)
        {
            quotient = (quotient<<1) | 1;
            dividend = (dividend-divider)<<1;
        }
        else
        {
            quotient = quotient << 1;
            dividend = dividend << 1;
        }
    }

    if(sign)
    {
        quotient = -quotient;
    }
    return quotient;
}

void vcop_calc_inverse_structure_tensor_2x2_cn
(
    int              *pTensorArrInp,
    unsigned short   *pD_nrsb,
    unsigned int     *pD_norm,
    short            *pInverseArrOut,
    unsigned short    inputStride,
    unsigned short    outputStride,
    unsigned short    numFracBits,
    unsigned short    numKeyPoints
)
{
    unsigned short i, j;
    unsigned short tensorArr_nrsb;
    unsigned int tensorArr_norm;
    short tensorArr_frac;

    for(i = 0; i < 3; i++)
    {
        for(j = 0; j < numKeyPoints; j++)
        {
            pD_norm[j] = pD_norm[j] & ~((1 << M2_DIVIDE_BITS) -1); // discard M2_DIVIDE_BITS LSBs (VLIB compatibility)

            tensorArr_nrsb = find_leading_bit_for_integer_data(pTensorArrInp[i*inputStride+j]);
            tensorArr_norm = pTensorArrInp[i*inputStride+j] << tensorArr_nrsb;//QS0.31

            tensorArr_frac  = divide_int(tensorArr_norm, pD_norm[j], M2_DIVIDE_BITS);

            pInverseArrOut[i*outputStride+2*j] = tensorArr_frac;
            pInverseArrOut[i*outputStride+2*j+1]  = (tensorArr_nrsb  + (32-pD_nrsb[j]) + (M2_DIVIDE_BITS-1) - numFracBits)*-1;

        }
    }
}
