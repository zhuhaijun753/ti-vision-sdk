/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*--------------------------------------------------------------------------*/
/* NAME: vcop_copy_new_lk_xy_kernel.k                                       */
/*                                                                          */
/* DESCRIPTION:                                                             */
/*                                                                          */
/* The file provides kernel for copying the xy points from internal scratch */
/* to output buffer                                                         */
/*                                                                          */
/*                                                                          */
/* RECOMMENDATIONS FOR OPTIMAL PERFORMANCE                                  */
/*   1. numKeyPoints is multiple of 8                                       */
/*                                                                          */
/* PERFORMANCE:                                                             */
/*                                                                          */
/*   vcop_copy_new_lk_xy:                                                   */
/*   - ~ (1/8)(numKeyPoints)                                                */
/*                                                                          */
/* @author Venkat R Peddigari (a0393744@ti.com)                             */
/*                                                                          */
/* version 1.0 (November 2013) : Base version.                              */
/*                                                                          */
/*--------------------------------------------------------------------------*/
#if (VCOP_HOST_EMULATION)
#include <vcop.h>
#endif

#define INP_ELEMSZ          sizeof(*pInput_A)
#define INP_VECTORSZ        (VCOP_SIMD_WIDTH*INP_ELEMSZ)
#define OUT_ELEMSZ          sizeof(*pOutput_B)
#define OUT_VECTORSZ        (VCOP_SIMD_WIDTH*OUT_ELEMSZ)

#define OUT_ELEMSZ_VALID_PTS sizeof(*currValidPoints)
#define OUT_ELEMSZ_VALID_ADRS sizeof(*pBaseAddrList)


void vcop_copy_new_lk_xy
(
    __vptr_int16   pInput_A,
    __vptr_int16   pOutput_B,
    __vptr_uint8  currValidPoints,        
		__vptr_uint32 pBaseAddrList ,
		__vptr_uint32 pValidAddrList,
		__vptr_uint32 pOutAddrList     ,
		__vptr_uint32 pValidOutAddrList,
    __vptr_int16   pLocalX,
    __vptr_int16   pLocalY,
    __vptr_int16   pLocalXY,
    unsigned short  numKeyPoints
)
{
    __vector Veven, Vodd;
	__vector Vevenlocalxy, Voddlocalxy;
    __agen AddrIn, AddrOut, AddrXYLocal;              //Address generators for input and output buffers
    __vector Vconst1;
    __agen AddrValidPts, AddrValidAdrs;             
    __vector Vsrc1;
    __vector Vsrc2;

    Vconst1 = 1;
    for (int I1 = 0; I1 < (numKeyPoints+VCOP_SIMD_WIDTH-1)/VCOP_SIMD_WIDTH; I1++)
    {
       AddrIn  = I1*2*INP_VECTORSZ;
       AddrOut = I1*2*OUT_VECTORSZ;
	   AddrXYLocal = I1*OUT_VECTORSZ;
       AddrValidPts  = I1*OUT_ELEMSZ_VALID_PTS*VCOP_SIMD_WIDTH;
       AddrValidAdrs = I1*OUT_ELEMSZ_VALID_ADRS*VCOP_SIMD_WIDTH;
       //Deinterleaving loading of the (X,Y) coordinate pair list
       (Veven, Vodd) =  pInput_A[AddrIn].deinterleave();
       Vsrc1 = pBaseAddrList[AddrValidAdrs];
       Vsrc2 = pOutAddrList[AddrValidAdrs];
       //Deinterleaving loading of the local (X,Y) coordinate pair list
       (Vevenlocalxy, Voddlocalxy) =  pLocalXY[AddrIn].deinterleave();

       pValidAddrList[AddrValidAdrs]    = Vsrc1;
       pValidOutAddrList[AddrValidAdrs] = Vsrc2;
       currValidPoints[AddrValidPts]    = Vconst1;
	   pLocalX[AddrXYLocal] = Vevenlocalxy;
	   pLocalY[AddrXYLocal] = Voddlocalxy;
       //Store the bilinear weights for each key point
       pOutput_B[AddrOut].interleave() = (Veven, Vodd);
   }
}
