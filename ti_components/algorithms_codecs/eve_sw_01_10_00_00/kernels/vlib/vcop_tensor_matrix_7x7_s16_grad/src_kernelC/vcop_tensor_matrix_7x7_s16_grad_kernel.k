/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/*----------------------------------------------------------------------------*/
/* NAME: vcop_tensor_matrix_7x7_s16_grad_kernel                               */
/*                                                                            */
/* DESCRIPTION:                                                               */
/*                                                                            */
/*     This kernel implements vcop functions required for tensor              */
/*     matrix computation                                                     */
/* AUTHOR:                                                                    */
/*             Kumar Desappan(kumar.desappanp@ti.com)                         */
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
#define IN_ELEM_SZ       (2)
#define OUT_ELEM_SZ      (4)


void vcop_tensor_matrix_7x7_s16_grad
  (
  __vptr_int16           gradX_a,         
  __vptr_int16           gradY_b,         
  unsigned short         stride,            
  unsigned short         n,              
  __vptr_int32           Ix2_a,         
  __vptr_int32           Iy2_b,         
  __vptr_int32           Ixy_c,
  __vptr_int32           scartch_a,         
  __vptr_int32           scartch_b,         
  __vptr_int32           scartch_c
  )
{
  __vector VgradX1, VgradY1, VgradX2, VgradY2;
  __vector VsumIx21, VsumIy21, VsumIxy1, VsumIx22, VsumIy22, VsumIxy2;
  __agen inAddr;
  __agen outAddr;

  for (int I0 = 0; I0 < n/VCOP_SIMD_WIDTH; I0++)
  {
    for (int I1 = 0; I1 < VCOP_SIMD_WIDTH/2; I1++)
    {
      outAddr  = I0*TRANSPOSE_STRIDE*VCOP_SIMD_WIDTH + I1*2*OUT_ELEM_SZ;
      VsumIx21 = 0;
      VsumIy21 = 0;
      VsumIxy1 = 0;
      VsumIx22 = 0;
      VsumIy22 = 0;
      VsumIxy2 = 0;
      for (int I2 = 0; I2 < BLK_HEIGHT; I2++)
      {
        inAddr  = I0*VCOP_SIMD_WIDTH*BLK_HEIGHT*stride*IN_ELEM_SZ + I1*2*stride*BLK_HEIGHT*IN_ELEM_SZ + I2*stride*IN_ELEM_SZ;
        VgradX1 = gradX_a[inAddr];
        VgradY1 = gradY_b[inAddr];
        VgradX2 = (gradX_a+stride*BLK_HEIGHT*IN_ELEM_SZ)[inAddr];
        VgradY2 = (gradY_b+stride*BLK_HEIGHT*IN_ELEM_SZ)[inAddr];

        VsumIx21 += VgradX1*VgradX1;
        VsumIx22 += VgradX2*VgradX2;

        VsumIy21 += VgradY1*VgradY1;
        VsumIy22 += VgradY2*VgradY2;

        VsumIxy1 += VgradX1*VgradY1;
        VsumIxy2 += VgradX2*VgradY2;

      }
      scartch_a[outAddr].offset_np1()               = VsumIx21;
      (scartch_a+OUT_ELEM_SZ)[outAddr].offset_np1() = VsumIx22;
      scartch_b[outAddr].offset_np1()               = VsumIy21;
      (scartch_b+OUT_ELEM_SZ)[outAddr].offset_np1() = VsumIy22;
      scartch_c[outAddr].offset_np1()               = VsumIxy1;
      (scartch_c+OUT_ELEM_SZ)[outAddr].offset_np1() = VsumIxy2;
    }
  }

#define VsumIx2 VsumIx21
#define VsumIy2 VsumIy21
#define VsumIxy VsumIxy1

#define VIx2 VgradX1
#define VIy2 VgradX2
#define VIxy VgradY1

  for (int I0 = 0; I0 < n/VCOP_SIMD_WIDTH; I0++)
  {
      outAddr  = I0*OUT_ELEM_SZ*VCOP_SIMD_WIDTH;
      VsumIx2 = 0;
      VsumIy2 = 0;
      VsumIxy = 0;
      for (int I2 = 0; I2 < BLK_WIDTH; I2++)
      {
        inAddr  = I0*TRANSPOSE_STRIDE*VCOP_SIMD_WIDTH + I2*TRANSPOSE_STRIDE;
        VIx2 = scartch_a[inAddr];
        VIy2 = scartch_b[inAddr];
        VIxy = scartch_c[inAddr];
        VsumIx2 += VIx2;
        VsumIy2 += VIy2;
        VsumIxy += VIxy;
      }
      Ix2_a[outAddr] = VsumIx2;
      Iy2_b[outAddr] = VsumIy2;
      Ixy_c[outAddr] = VsumIxy;
  }
}


/*----------------------------------------------------------------------------*/
/* End of file: vcop_tensor_matrix_7x7_s16_grad_kernel.k                      */
/*----------------------------------------------------------------------------*/
/* Texas Instruments Incorporated 2010-2013.                                  */
/*============================================================================*/
