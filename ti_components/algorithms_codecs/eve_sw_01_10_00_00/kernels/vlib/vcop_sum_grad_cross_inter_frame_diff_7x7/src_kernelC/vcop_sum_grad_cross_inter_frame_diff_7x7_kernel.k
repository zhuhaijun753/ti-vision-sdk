/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/*----------------------------------------------------------------------------*/
/* NAME: vcop_sum_grad_cross_inter_frame_diff_7x7_kernel                     */
/*                                                                            */
/* DESCRIPTION:                                                               */
/*                                                                            */
/*     This kernel implements sum of Ix*It ans Iy*It                          */
/*     computation on EVE                                                     */
/* AUTHOR:                                                                    */
/*             Kumar Desappan(kumar.desappan@ti.com)                         */
/*                                                                            */
/* VERSION:                                                                   */
/*            1.0 (Nov 2013) : Base version.                                  */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/* Texas Instruments Incorporated 2010-2013.                                  */
/*============================================================================*/
#if (VCOP_HOST_EMULATION)
#include <vcop.h>
#endif

#define TRANSPOSE_STRIDE (36)
#define BLK_WIDTH        (7)
#define BLK_HEIGHT       (7)
#define IN_GRAD_SZ       (2)
#define IN_IMG_SZ        (1)
#define OUT_ELEM_SZ      (4)


void vcop_sum_grad_cross_inter_frame_diff_7x7
  (
  __vptr_int16           gradX_a,         
  __vptr_int16           gradY_b,         
  __vptr_uint8          im1_a,         
  __vptr_uint8        im2_b,         
    unsigned short       gradStride,            
    unsigned short       imStride,            
    unsigned short       n,              
  __vptr_int32           IxIt_a,         
  __vptr_int32           IyIt_b,         
  __vptr_int32           scartch_a,         
  __vptr_int32           scartch_b         
  )
{
  __vector VgradX, VgradY, VimC, VimP, VDiff;
  __vector VsumIxIt, VsumIyIt;
  __vector VIxIt, VIyIt;
  __agen inAddr1;
  __agen inAddr2;
  __agen outAddr;

  for (int I0 = 0; I0 < (n + VCOP_SIMD_WIDTH-1)/VCOP_SIMD_WIDTH; I0++)
  {
    for (int I1 = 0; I1 < VCOP_SIMD_WIDTH; I1++)
    {
      outAddr  = I0*TRANSPOSE_STRIDE*VCOP_SIMD_WIDTH + I1*OUT_ELEM_SZ;
      VsumIxIt = 0;
      VsumIyIt = 0;
      for (int I2 = 0; I2 < BLK_HEIGHT; I2++)
      {
        inAddr1  = I0*VCOP_SIMD_WIDTH*BLK_HEIGHT*gradStride*IN_GRAD_SZ + I1*gradStride*BLK_HEIGHT*IN_GRAD_SZ + I2*gradStride*IN_GRAD_SZ;
        inAddr2  = I0*VCOP_SIMD_WIDTH*BLK_HEIGHT*imStride*IN_IMG_SZ + I1*imStride*BLK_HEIGHT*IN_IMG_SZ + I2*imStride*IN_IMG_SZ;
        VgradX = gradX_a[inAddr1];
        VgradY = gradY_b[inAddr1];
        VimC   = im1_a[inAddr2]; 
        VimP   = im2_b[inAddr2]; 

        VDiff = VimC - VimP;

        VsumIxIt += VgradX*VDiff;
        VsumIyIt += VgradY*VDiff;

      }
      scartch_a[outAddr].offset_np1()     = VsumIxIt;
      scartch_b[outAddr].offset_np1()     = VsumIyIt;
    }
  }

  for (int I0 = 0; I0 < (n + VCOP_SIMD_WIDTH-1)/VCOP_SIMD_WIDTH; I0++)
  {
      outAddr  = I0*OUT_ELEM_SZ*VCOP_SIMD_WIDTH;
      VsumIxIt = 0;
      VsumIyIt = 0;
      for (int I2 = 0; I2 < BLK_WIDTH; I2++)
      {
        inAddr1  = I0*TRANSPOSE_STRIDE*VCOP_SIMD_WIDTH + I2*TRANSPOSE_STRIDE;
        VIxIt = scartch_a[inAddr1];
        VIyIt = scartch_b[inAddr1];
        VsumIxIt += VIxIt;
        VsumIyIt += VIyIt;
     }
      IxIt_a[outAddr] = VsumIxIt;
      IyIt_b[outAddr] = VsumIyIt;
  }
}


/*----------------------------------------------------------------------------*/
/* End of file:vcop_sum_grad_cross_inter_frame_diff_7x7_kernel.k              */
/*----------------------------------------------------------------------------*/
/* Texas Instruments Incorporated 2010-2013.                                  */
/*============================================================================*/
