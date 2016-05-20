/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*--------------------------------------------------------------------------*/
/* NAME: vcop_multiblock_bilinear_interp_7x7_u8_kernel.k                    */
/*                                                                          */
/* DESCRIPTION:                                                             */
/*                                                                          */
/* The file provides kernel for computing bilinear interpolated image pixels*/
/* of multiple input blocks corresponding to diferent feature or key point  */
/*                                                                          */
/* Multi Block Bilinear Interpolation Kernel accepts an 8-bit input image   */
/* with stride equal to "input1Stride", pre-computed bilinear weights for   */
/* each key point or input block and outputs 8-bit bilinear interpolated    */
/* pixels for each output block corresponding to each key point of dimension*/
/* of dimension,(blkWidth) x (blkHeight). blkOffset denotes the inter block */
/* offset which implies distance between first pixel of Blk(n) and Blk(n-1) */
/* 7x7 neighboorhood window is being used here, due to SIMD alignment 8x7 is*/
/* recommended as blkWidth x blkHeight                                      */
/*                                                                          */
/*  pIn_A - Input Image Data:                                               */
/*                             input1Stride                                 */
/*          <------------------------------------------------------->       */
/*           __________________________________________________________     */
/*          |      |      |      |                    | Blk(           |    */
/*          |Blk(0)|Blk(1)|Blk(2)| ...................|numKeyPoints -1)|    */
/*          |______|______|______|____________________|________________|    */
/*          <------>                                                        */
/*          blkOffset                                                       */
/*                                                                          */
/*pOutBilinearInterpImg_C - 8-bit bilinear interpolated image pixels output */
/*                                                                          */
/*                            (blkWidth) bytes                              */
/*                      <----------------------->                           */
/*                       _______________________                            */
/*                      |                       |                           */
/*      (blkHeight)     |        Blk(0)         |                           */
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
/*      -> numKeyPoints * (outputStride)*(blkHeight)                        */
/*   3. input2Stride >= numKeyPoints                                        */
/*   4. input1Stride >= numKeyPoints * blkOffset                            */
/* RECOMMENDATIONS FOR OPTIMAL PERFORMANCE                                  */
/*   1. (blkWidth) is multiple of 8                                         */
/*                                                                          */
/* PERFORMANCE:                                                             */
/*                                                                          */
/*   vcop_multiblock_bilinear_interp_7x7_u8:                                */
/*   - ~ (4/8)*(blkWidth)* numKeyPoints * (blkHeight)                       */
/*                                                                          */
/* @author Venkat R Peddigari (a0393744@ti.com)                             */
/*                                                                          */
/* version 1.0 (November 2013) : Base version.                              */
/*                                                                          */
/*--------------------------------------------------------------------------*/
#if (VCOP_HOST_EMULATION)
#include <vcop.h>
#endif

#define WGT_ELEMSZ      (sizeof(*pInpWts_B))
#define ELEMSZ          sizeof(*pIn_A)
#define VECTORSZ        (VCOP_SIMD_WIDTH*ELEMSZ)

void vcop_multiblock_bilinear_interp_7x7_u8
(
    __vptr_uint8    pIn_A,
    __vptr_uint16   pInpWts_B,
    __vptr_uint8    pOutBilinearInterpImg_C,
    unsigned short  input1Stride,
    unsigned short  input2Stride,
    unsigned short  outputStride,
    unsigned short  blkWidth,
    unsigned short  blkHeight,
    unsigned short  blkOffset,
    unsigned short  shiftValue,
    unsigned short  numKeyPoints 
)
{
    __vector Vwt0, Vwt1, Vwt2, Vwt3;          //Bilinear weights needed for bilinear interpolation
    __vector Vpix00, Vpix01, Vpix10, Vpix11;  //2x2 neigbhorhood pixels required for bilinear interpolation
    __vector Vout;                            //Output vectors to hold intermediate outputs
    __agen AddrWt,AddrPix, AddrOut;           //Address generators for inputs and output

    for (int I1 = 0; I1 < numKeyPoints; I1++)
    {
        AddrWt = I1*WGT_ELEMSZ;

        //Load the precomputed bilinear weights for the given input block
        //corresponding to given key point
        Vwt0 = pInpWts_B[AddrWt].onept();
        Vwt1 = (pInpWts_B + 1*input2Stride*WGT_ELEMSZ)[AddrWt].onept();
        Vwt2 = (pInpWts_B + 2*input2Stride*WGT_ELEMSZ)[AddrWt].onept();
        Vwt3 = (pInpWts_B + 3*input2Stride*WGT_ELEMSZ)[AddrWt].onept();

        for (int I2 = 0; I2 < blkHeight; I2++)
        {
           for (int I3 = 0; I3 < (blkWidth+VCOP_SIMD_WIDTH-1)/VCOP_SIMD_WIDTH; I3++)
           {
               AddrPix = I1*blkOffset*ELEMSZ + I2*input1Stride*ELEMSZ + I3*VECTORSZ;
               AddrOut = I1*outputStride*blkHeight*ELEMSZ + I2*outputStride*ELEMSZ + I3*VECTORSZ;

               //Load the 2x2 neighborhood pixels for computing bilinear interpolated output
               Vpix00 = (pIn_A)                          [AddrPix].npt();
               Vpix01 = (pIn_A + ELEMSZ)                 [AddrPix].npt();
               Vpix10 = (pIn_A + input1Stride*ELEMSZ)    [AddrPix].npt();
               Vpix11 = (pIn_A + (input1Stride+1)*ELEMSZ)[AddrPix].npt();

               //Compute partial products of first column pixels with corresponding weights
               Vout  = Vwt3 * Vpix00;
               Vout += Vwt1 * Vpix10;

               //Compute partial products of second column pixels with corresponding weights
               Vout += Vwt2 * Vpix01;
               Vout += Vwt0 * Vpix11;

               pOutBilinearInterpImg_C[AddrOut].npt()   = Vout.truncate(shiftValue);
          }
       }
   }
}
