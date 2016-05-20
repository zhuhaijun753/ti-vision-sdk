/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*--------------------------------------------------------------------------*/
/* NAME: vcop_weight_address_bilinear_interpolation_kernel.k                */
/*                                                                          */
/* DESCRIPTION:                                                             */
/*                                                                          */
/* The file provides kernel for computing bilinear weights and updated base */
/* address corresponding to the start of 7x7 neighborhood for each key point*/
/* that is required during bilinear interpolation of a given image          */
/* The base address and weights change due to iterative update of the X and */
/* Y coordinates such as in LK tracker                                      */
/*                                                                          */
/* Weight and address updation kernel needed for bilinear interpolation     */
/* accepts the new updated (X,Y) coordinate pair list for each key point and*/
/* outputs four 8-bit weights for each key point that would be applied over */
/* 2x2 neighborhood pixels during bilinear interpolation. The dimension of  */
/* weight output is (numKeyPoints x 4). Also, this kernel outputs updated   */
/* base address corresponding to the start of new location of 7x7           */
/* neighborhood block used during bilinear interpolation                    */
/*                                                                          */
/* ASSUMPTIONS:                                                             */
/*   1. X, Y coordinates are of 16 bit and are in interleaved fashion       */
/*   2. pOutWts_C allocation should be at least the following:              */
/*      -> (outputStride x 4) wherein outputStride >= numKeyPoints          */
/*   3. 7x7 neighborhood is considered while updating base address          */
/*   4. Updated base address gets stored to parameter block of bilinear     */
/*      interpolation kernel using foreach, namely vcop_foreach_multiblock  */
/*      _bilinear_interp_7x7_u8                                             */
/*   5. X, Y coordinates denote the relative locations w.r.t input block    */
/*      within the internal memory from where the 7x7 neighborhood is being */
/*      considered for bilinear interpolation                               */
/*                                                                          */
/* RECOMMENDATIONS FOR OPTIMAL PERFORMANCE                                  */
/*   1. numKeyPoints is multiple of 8                                       */
/*                                                                          */
/* PERFORMANCE:                                                             */
/*                                                                          */
/*   vcop_weight_address_bilinear_interpolation:                            */
/*   - ~ (numKeyPoints) i.e., 1 scatter store cycle for each key point      */
/*                                                                          */
/* @author Venkat R Peddigari (a0393744@ti.com)                             */
/*                                                                          */
/* version 1.0 (November 2013) : Base version.                              */
/*                                                                          */
/*--------------------------------------------------------------------------*/
#if (VCOP_HOST_EMULATION)
#include <vcop.h>
#endif

#define INP_ELEMSZ          sizeof(*pXList_A)
#define INP_VECTORSZ        (VCOP_SIMD_WIDTH*INP_ELEMSZ)
#define OUT_ELEMSZ          sizeof(*pOutWts_C)
#define OUT_VECTORSZ        (VCOP_SIMD_WIDTH*OUT_ELEMSZ)
#define PWID                (7)  //7x7 Pixel Window assumed

#define OUT_ADDRESS_SIZE        (VCOP_SIMD_WIDTH*4)

void vcop_weight_address_bilinear_interpolation
(
    __vptr_uint16   pXList_A,
    __vptr_uint16   pYList_A,
    __vptr_uint32   pBaseAddrList_B,
    __vptr_uint32   pOutAddrList_B,
    __vptr_uint16   pOutWts_C,
    __vptr_uint32   pOutBaseAddress_C,
    __vptr_uint16   pParamBlkOffsetVec_C,
    unsigned short  numKeyPoints,
    unsigned short  qFormatMaxFactor,
    unsigned short  truncateBits,
    unsigned short  qShift,
    unsigned short  blkStride,
    unsigned short  outputStride
)
{
    __vector Vwt0, Vwt1, Vwt2, Vwt3;     //Bilinear weights that would be applied on 2x2 neighborhood pixels during bilinear interpolation
    __vector Vx, Vy;                     //Denotes the X & Y coordinates in Q format as specified by qFormatMaxFactor
    __vector VxFrac, VyFrac;             //Fractional part of the X & Y coordinates in Q format specified by qFormatMaxFactor
    __vector VQFt_xFrac, VQFt_yFrac;     //Delta between the Max Q format value and the fractional part of the X & Y coordinates respectively
    __vector Vpwid;                      //Denotes the pixel window size
    __vector Vstride;                    //Denotes the stride of the input block
    __vector VbaseAddr;                  //Denotes the base address for each input block corresponding to each key point
    __vector VqFormat;                   //Denotes the maximum value allowed for the given Q format
                                         //Example: Q4 format => (2^4 - 1) = 15 is maximum value
    __vector VqShift;                    //Denotes the number of bits that X & Y coordinates need to be shift to convert them into integer format from Q format
    __vector Vzero, VscatterOffset;
    __agen AddrIn1, AddrOut1;            //Address generators for input, pXYList_A and output, pOutWts_C buffers
    __agen AddrIn2, AddrOut2;            //Address generators for pBaseAddrList_B & pOutBaseAddress_C buffers
    __agen offset;

    offset = 0;
    VscatterOffset = pParamBlkOffsetVec_C[offset].npt();

    for (int I1 = 0; I1 < (numKeyPoints+VCOP_SIMD_WIDTH-1)/VCOP_SIMD_WIDTH; I1++)
    {
       AddrIn1  = I1*INP_VECTORSZ;
       AddrOut1 = I1*OUT_VECTORSZ;
       AddrIn2  = I1*2*OUT_VECTORSZ;
       AddrOut2 = I1*26*OUT_VECTORSZ;
       //Deinterleaving loading of the (X,Y) coordinate pair list
       Vx =  pXList_A[AddrIn1];
       Vy =  pYList_A[AddrIn1];
       VbaseAddr = pBaseAddrList_B[AddrIn2].npt();
       VqFormat = qFormatMaxFactor;
       VqShift  = -qShift;                  //Assumes Q4 format currently
       Vpwid    = PWID/2;
       Vstride  = blkStride;
       Vzero    = 0;

       //Get the fractional part from (X,Y) which is in Q format
       VxFrac = Vx & VqFormat;
       VyFrac = Vy & VqFormat;

       //Compute the difference between the maximum and the fractional parts of X & Y for given Q format
       VQFt_xFrac = VqFormat - VxFrac;
       VQFt_yFrac = VqFormat - VyFrac;

       //Compute the weights for the 2x2 neighboorhood pixels which are used during bilinear interpolation
       Vwt0  = VxFrac * VyFrac;
       Vwt1  = VQFt_xFrac * VyFrac;

       Vwt2  = VxFrac * VQFt_yFrac;
       Vwt3  = VQFt_xFrac * VQFt_yFrac;

#define VxInt Vx //Denotes the integer value of Q format X coordinate
#define VyInt Vy //Denotes the integer value of Q format Y coordinate

       //Find the integer values of X,Y coordinates by discarding the Q-format bits
       VxInt = Vx << VqShift;
       VyInt = Vy << VqShift;

       //Compute the start location of the 7x7 neighborhood window
       VxInt  = VxInt - Vpwid;
       VyInt  = VyInt - Vpwid;

       //Check if VxInt or VyInt is negative and if yes, make them zero
#define Vxneg VxFrac
#define Vyneg VyFrac
       Vxneg  = VxInt < Vzero;
       Vyneg  = VyInt < Vzero;

       VxInt  = select(Vxneg, Vzero, VxInt);
       VyInt  = select(Vyneg, Vzero, VyInt);
        
       /*---------------------------------------------------------------
        If the flow vector points to the regoin outside the valid search 
        region then the flow vector will not be updated by the next 
        iterartion. The address generated by this kerenl will be only
        used by interpolatrion kernel and the output is iignored. 
        So it is ok to point the address to start of the buffer
        -----------------------------------------------------------------*/
#define VXend VQFt_xFrac
#define VYend VQFt_yFrac
       VXend = VxInt + Vpwid;
       VYend = VyInt + Vpwid;
       VXend += Vpwid;
       VYend += Vpwid;
       VXend += Vpwid;
       VYend += Vpwid;

       Vxneg  = VXend >= Vstride;
       Vyneg  = VYend >= Vstride;
       VxInt  = select(Vxneg, Vzero, VxInt);
       VyInt  = select(Vyneg, Vzero, VyInt);
       
       //Computes the offset to the start of 7x7 neighborhood block witin input block for given key point
       VxInt += VyInt*Vstride;

#define VbaseAddr00 Vx
#define VbaseAddr01 Vy
#define VbaseAddr10 VQFt_xFrac
#define VbaseAddr11 VQFt_yFrac
#define Vone VxFrac
       //Compute the updated base address by adding the offset
       Vone        = Vzero > VqShift;
       VbaseAddr00 = VbaseAddr   + VxInt;
       VbaseAddr01 = VbaseAddr00 + Vone;
       VbaseAddr10 = VbaseAddr00 + Vstride;
       VbaseAddr11 = VbaseAddr01 + Vstride;

       //Store the bilinear weights for each key point
       (pOutWts_C                            )[AddrOut1] = Vwt0.truncate(truncateBits);
       (pOutWts_C +   outputStride*OUT_ELEMSZ)[AddrOut1] = Vwt1.truncate(truncateBits);
       (pOutWts_C + 2*outputStride*OUT_ELEMSZ)[AddrOut1] = Vwt2.truncate(truncateBits);
       (pOutWts_C + 3*outputStride*OUT_ELEMSZ)[AddrOut1] = Vwt3.truncate(truncateBits);

       //Store the updated base address
       //TODO: Replace this by parallel scatter store to updated base address to param space with known offset
       //VscatterOffset specifies offsets in terms of bytes from the given address pointer for each element in vector
       (pOutBaseAddress_C)[AddrOut2].s_scatter(VscatterOffset) = VbaseAddr00;
       (pOutBaseAddress_C+4)[AddrOut2].s_scatter(VscatterOffset) = VbaseAddr01;
       (pOutBaseAddress_C+8)[AddrOut2].s_scatter(VscatterOffset) = VbaseAddr10;
       (pOutBaseAddress_C+12)[AddrOut2].s_scatter(VscatterOffset) = VbaseAddr11;
   }

#define outAddress Vx
    for (int I1 = 0; I1 < (numKeyPoints+VCOP_SIMD_WIDTH-1)/VCOP_SIMD_WIDTH; I1++)
    {
       AddrIn2  = I1*OUT_ADDRESS_SIZE;
       AddrOut2 = I1*26*OUT_VECTORSZ;
       outAddress = pOutAddrList_B[AddrIn2].npt();

       (pOutBaseAddress_C+16)[AddrOut2].s_scatter(VscatterOffset) = outAddress;
   }
}
