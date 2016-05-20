/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*--------------------------------------------------------------------------*/
/* NAME: vcop_foreach_multiblock_bilinear_interp_7x7_u8_kernel.k            */
/*                                                                          */
/* DESCRIPTION:                                                             */
/*                                                                          */
/* The file provides kernel for computing bilinear interpolated image pixels*/
/* of multiple input blocks corresponding to diferent feature or key point  */
/*                                                                          */
/* Multi Block Bilinear Interpolation Kernel using repeat loop accepts a    */
/* list of pointers denoting the start pixel of the 7x7 neighborhood window */
/* within each input block corresponding to each key point, each input block*/ 
/* consists of 8-bit input pixels with stride equal to "input1Stride". It   */
/* also takes pre-computed bilinear weights for each key point or input     */
/* block and outputs 8-bit bilinear interpolated pixels for each output     */
/* block corresponding to each key point of dimension,(outBlkWidth) x       */
/* (outBlkHeight).                                                          */
/* 7x7 neighboorhood window is being used here, due to SIMD alignment 8x7 is*/
/* recommended as outBlkWidth x outBlkHeight                                */
/*                                                                          */
/*  *pIn_A[] - List of pointers to processing block within each input block */
/*                             input1Stride                                 */
/*          <------------------------------------------------------->       */
/*           __________________________________________________________     */
/*          |                                                          |    */
/*          |          outBlkWidth                                     |    */
/*          | pIn_A[n]_____________                                    |    */
/*          |        |             |       Blk(n)                      |    */
/*          |        |             |                                   |    */
/*          |        |             | outBlkHeight                      |    */
/*          |        |_____________|                                   |    */
/*          |                                                          |    */
/*          |                                                          |    */
/*          |                                                          |    */
/*          |                                                          |    */
/*          |__________________________________________________________|    */
/*                                                                          */
/*pOutBilinearInterpImg_C - 8-bit bilinear interpolated image pixels output */
/*                                                                          */
/*                            (outBlkWidth) bytes                           */
/*                      <----------------------->                           */
/*                       _______________________                            */
/*                      |                       |                           */
/*      (outBlkHeight)  |        Blk(0)         |                           */
/*                      |_______________________|                           */
/*                      |                       |                           */
/*                      |        Blk(1)         |                           */
/*                      |_______________________|                           */
/*                                  :                                       */
/*                                  :                                       */
/*                                  :                                       */
/*                       _______________________                            */
/*                      |                       |                           */
/*                      |  Blk(numKeyPoints-1)  |                           */
/*                      |_______________________|                           */
/*                                                                          */
/* ASSUMPTIONS:                                                             */
/*   1. Input image is of 8-bit                                             */
/*   2. pOutBilinearInterpImg_C allocation should be at least the following:*/
/*      -> numKeyPoints * (outputStride)*(outBlkHeight)                     */
/*   3. input2Stride >= numKeyPoints                                        */
/*                                                                          */
/* RECOMMENDATIONS FOR OPTIMAL PERFORMANCE                                  */
/*   1. (outBlkWidth) is multiple of 8                                      */
/*                                                                          */
/* PERFORMANCE:                                                             */
/*                                                                          */
/*   vcop_foreach_multiblock_bilinear_interp_7x7_u8:                        */
/*   - ~ (4/8)*(outBlkWidth)* numKeyPoints * (outBlkHeight)                 */
/*    + Overhead of repeat loop for each key point                          */
/*                                                                          */
/* @author Venkat R Peddigari (a0393744@ti.com)                             */
/*                                                                          */
/* version 1.0 (November 2013) : Base version.                              */
/*                                                                          */
/*--------------------------------------------------------------------------*/
#if (VCOP_HOST_EMULATION)
#include <vcop.h>
#endif

#define WGT_ELEMSZ          (2)
#define ELEMSZ              (1)
#define VECTORSZ        (VCOP_SIMD_WIDTH*ELEMSZ)
#define MAX_KEY_POINTS  (16)

void vcop_foreach_multiblock_bilinear_interp_7x7_u8
(
    __vptr_uint8_arr    pIn_A,                
    __vptr_uint16_arr   pInpWts_B,              
    __vptr_uint8_arr    pOutBilinearInterpImg_C,
    unsigned short      input1Stride,         
    unsigned short      input2Stride,         
    unsigned short      outputStride,         
    unsigned short      outBlkWidth,          
    unsigned short      outBlkHeight,         
    unsigned short      shiftValue,
    unsigned short      numKeyPoints
)
{
    __vector Vwt0, Vwt1, Vwt2, Vwt3;          //Bilinear weights needed for bilinear interpolation
    __vector Vpix00, Vpix01, Vpix10, Vpix11;  //2x2 neigbhorhood pixels required for bilinear interpolation
    __vector Vout;                            //Output vectors to hold intermediate outputs
    __agen AddrWt,AddrPix, AddrOut;           //Address generators for inputs and output

#define ROW1 pIn_A[I0]

    foreach(I0, numKeyPoints, MAX_KEY_POINTS)
    {
        AddrWt = 0;

        //Load the precomputed bilinear weights for the given input block
        //corresponding to given key point
        Vwt0 = pInpWts_B[I0][AddrWt].onept();
        Vwt1 = (pInpWts_B[I0] + 1*input2Stride*WGT_ELEMSZ)[AddrWt].onept();
        Vwt2 = (pInpWts_B[I0] + 2*input2Stride*WGT_ELEMSZ)[AddrWt].onept();
        Vwt3 = (pInpWts_B[I0] + 3*input2Stride*WGT_ELEMSZ)[AddrWt].onept();

        for (int I2 = 0; I2 < outBlkHeight; I2++)
        {
           for (int I3 = 0; I3 < (outBlkWidth+VCOP_SIMD_WIDTH-1)/VCOP_SIMD_WIDTH; I3++)
           {
               AddrPix = I2*input1Stride*ELEMSZ + I3*VECTORSZ;
               AddrOut = I2*outputStride*ELEMSZ + I3*VECTORSZ;

               //Load the 2x2 neighborhood pixels for computing bilinear interpolated output
               Vpix00 = (ROW1)                          [AddrPix].npt();
               Vpix01 = (ROW1 + ELEMSZ)                 [AddrPix].npt();
               Vpix10 = (ROW1 + input1Stride*ELEMSZ)    [AddrPix].npt();
               Vpix11 = (ROW1 + (input1Stride+1)*ELEMSZ)[AddrPix].npt();

               //Compute partial products of first column pixels with corresponding weights
               Vout  = Vwt3 * Vpix00;
               Vout += Vwt1 * Vpix10;

               //Compute partial products of second column pixels with corresponding weights
               Vout += Vwt2 * Vpix01;
               Vout += Vwt0 * Vpix11;

               pOutBilinearInterpImg_C[I0][AddrOut].npt()   = Vout.truncate(shiftValue);
          }
       }
   }
}
