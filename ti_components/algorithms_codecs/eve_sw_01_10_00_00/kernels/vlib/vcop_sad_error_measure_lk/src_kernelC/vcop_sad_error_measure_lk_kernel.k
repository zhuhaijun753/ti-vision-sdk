/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*--------------------------------------------------------------------------*/
/* NAME: vcop_sad_error_measure_lk_kernel.k                                 */
/*                                                                          */
/* DESCRIPTION:                                                             */
/*                   This file contains the VCOP implementation of the      */
/*     function for computing SAD (Sum of Absolute Differences) based error */
/*     measure for each key point. It will also incorporate boundary check  */
/*     compute and initializes error to 0xFFFF for out of bound key points  */
/*     The following figure illustrates the input data arrangement of the   */
/*     bilinear interpolated patch windows for both previous and current    */
/*     frames across each key point.                                        */
/*                                                                          */
/*                           (inputStride) bytes                            */
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
/*   1. X,Y coordinates are of 16 bit (Q12.4) and are in interleaved fashion*/
/*                                                                          */
/* RECOMMENDATIONS FOR OPTIMAL PERFORMANCE                                  */
/*   1. numKeyPoints is multiple of 8                                       */
/*                                                                          */
/* PERFORMANCE:                                                             */
/*                                                                          */
/*   vcop_sad_error_measure_lk:                                             */
/*   - ~ 1/16 * 64 (instead of 49)  = 4 cycle per point + 25/8 overhead     */
/*                                  = 7.x cycles per point                  */
/*                                                                          */
/* version 1.0 (January 2014) : Base version.                               */
/*                                                                          */
/*--------------------------------------------------------------------------*/
#if (VCOP_HOST_EMULATION)
#include <vcop.h>
#endif

#define INP_ELEMSZ          sizeof(*pPrevBiLinImg_A)
#define INP_VECTORSZ        (VCOP_SIMD_WIDTH*INP_ELEMSZ)
#define OUT_ELEMSZ          sizeof(*pOutErrorMeasure_C)
#define OUT_VECTORSZ        (VCOP_SIMD_WIDTH*OUT_ELEMSZ)
#define TRANSPOSE_STRIDE    (36)
#define VCOP_LK_PATCH_WIDTH (7)

void vcop_sad_error_measure_lk
(
   __vptr_uint8      pPrevBiLinImg_A,
   __vptr_uint8      pCurrBiLinImg_B,
   __vptr_uint16     pNewXYList_X,
   __vptr_uint16     pOutErrorMeasure_C,
   unsigned short    inputStride,
   unsigned short    frmWidth,
   unsigned short    frmHeight,
   unsigned short    blkWidth,
   unsigned short    blkHeight,
   unsigned short    numKeyPoints,
   unsigned short    shiftValue,
   __vptr_uint16     scratch_a

)
{
  __agen   inAddr1;       //Address generator for the previous frame pixel
  __agen   inAddr2;       //Address generator for the current frame pixel
  __agen   outAddr;       //Address generator for the SAD based error measure output

  for (int I0 = 0; I0 < (numKeyPoints + VCOP_SIMD_WIDTH-1)/VCOP_SIMD_WIDTH; I0++)
  {
    for (int I1 = 0; I1 < VCOP_SIMD_WIDTH/2; I1++)
    {
      __vector VimC, VimP, VimC1, VimP1;    //Vector registers to hold the current and previous frame interpolated pixels
      __vector VsumAbsDiff, VsumAbsDiff1;   //Vector register for accumulating absolute difference of current and previous frame pixels

      outAddr = I0*OUT_ELEMSZ*VCOP_SIMD_WIDTH + (2*I1)*OUT_ELEMSZ;

      VsumAbsDiff  = 0;
      VsumAbsDiff1 = 0;
      for (int I2 = 0; I2 < blkHeight; I2++)
      {
        inAddr1 = I0*VCOP_SIMD_WIDTH*blkHeight*inputStride*INP_ELEMSZ + (2*I1)*inputStride*blkHeight*INP_ELEMSZ + I2*inputStride*INP_ELEMSZ;
        inAddr2 = I0*VCOP_SIMD_WIDTH*blkHeight*inputStride*INP_ELEMSZ + (2*I1)*inputStride*blkHeight*INP_ELEMSZ + I2*inputStride*INP_ELEMSZ;

        VimP  = pPrevBiLinImg_A[inAddr1];
        VimC  = pCurrBiLinImg_B[inAddr2];

        VimP1 = (pPrevBiLinImg_A + inputStride*blkHeight*INP_ELEMSZ)[inAddr1];
        VimC1 = (pCurrBiLinImg_B + inputStride*blkHeight*INP_ELEMSZ)[inAddr2];

        VsumAbsDiff  += abs(VimC - VimP);
        VsumAbsDiff1 += abs(VimC1 - VimP1);
      }
      //Storing the intermediate sum of absolute differences to scratch in transpose mode to enable SIMD for next loop
      scratch_a[outAddr].offset_np1()                   = VsumAbsDiff;
      (scratch_a + OUT_ELEMSZ)[outAddr].offset_np1()    = VsumAbsDiff1;
    }
  }

  //Accumulate the intermediate SAD's within the vector for each key point
  for (int I0 = 0; I0 < (numKeyPoints + 2*VCOP_SIMD_WIDTH-1)/(2*VCOP_SIMD_WIDTH); I0++)
  {
      __vector Vodd, Veven;
      __vector VsumAbsDiff, VsumAbsDiff1;   //Vector register for accumulating absolute difference of current and previous frame pixels

      outAddr  = I0*OUT_ELEMSZ*2*VCOP_SIMD_WIDTH;
      VsumAbsDiff  = 0;
      VsumAbsDiff1 = 0;
      for (int I2 = 0; I2 < blkHeight; I2++)
      {
        inAddr1  = I0*TRANSPOSE_STRIDE*VCOP_SIMD_WIDTH + I2*TRANSPOSE_STRIDE;
        (Vodd, Veven) = scratch_a[inAddr1].deinterleave();
        VsumAbsDiff  += Vodd;
        VsumAbsDiff1 += Veven;
      }
      pOutErrorMeasure_C[outAddr].interleave() = (VsumAbsDiff, VsumAbsDiff1);
  }

  //Check the boundary conditions and set the flag if it is out of bounds
  //Use select instruction to either store the computed SAD or the default 0xFFFF
  for (int I0 = 0; I0 < (numKeyPoints + VCOP_SIMD_WIDTH-1)/VCOP_SIMD_WIDTH; I0++)
  {
      __vector Vlimit1, Vlimit2, Vlimit3; //Upper and lower limits for checking the out of bound conditions along X and Y directions
      __vector Vflag, Vflag1, Vflag2;     //Flags for indicating if the out of bound is true or false for each key point
      __vector Vshift;                    //Number of fractional bits in X,Y coordinates to be truncated
      __vector Vmaxerror;                 //Vector registers for constants used in out of bound condition checks
      __vector Verror;                    //Vector register for the SAD based error measure output
      __vector Vxint, Vyint;              //Vector registers to hold the integer pixel locations of key points being tracked

      Vlimit1 = (VCOP_LK_PATCH_WIDTH/2+1);
      Vlimit2 = (frmWidth - VCOP_LK_PATCH_WIDTH/2-2);
      Vlimit3 = (frmHeight - VCOP_LK_PATCH_WIDTH/2-2);
      Vshift  = -shiftValue;
      Vmaxerror = 0xFFFF;

      outAddr  = I0*OUT_ELEMSZ*VCOP_SIMD_WIDTH;
      inAddr1  = I0*OUT_ELEMSZ*VCOP_SIMD_WIDTH;
      inAddr2  = I0*OUT_ELEMSZ*VCOP_SIMD_WIDTH*2;

      Verror = pOutErrorMeasure_C[inAddr1];
      (Vxint, Vyint) = pNewXYList_X[inAddr2].deinterleave();

      //Compute the integer locations by truncating fractional bits
      Vxint = Vxint << Vshift;
      Vyint = Vyint << Vshift;

      //Check the boundary conditions along X direction
      Vflag1  = Vxint <  Vlimit1;
      Vflag2  = Vxint >= Vlimit2;

      Vflag   = Vflag1 | Vflag2;

      //Compute the boundary conditions along Y direction
      Vflag1  = Vyint <  Vlimit1;
      Vflag2  = Vyint >= Vlimit3;

      Vflag |= Vflag1 | Vflag2;

      //Select MAX ERROR if Out of Bound flag is set
      Verror = select(Vflag, Vmaxerror, Verror);

      pOutErrorMeasure_C[outAddr] = Verror;
  }
}
