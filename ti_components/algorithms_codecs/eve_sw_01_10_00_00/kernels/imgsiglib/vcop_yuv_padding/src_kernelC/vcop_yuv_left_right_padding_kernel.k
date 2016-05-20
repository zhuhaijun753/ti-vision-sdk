/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*                                                                          */
/*    @file : vcop_yuv_left_right_padding_kernel.k                          */
/*                                                                          */
/*    @brief : Kernel for left and right padding                            */
/*                                                                          */
/*    @version : 1.0 (Mar 2014) : Base version.                             */
/*                                                                          */
/*==========================================================================*/
#if (VCOP_HOST_EMULATION)
#include <vcop.h>
#endif

void vcop_yuv_left_right_padding_u8
(
    __vptr_uint8   in_left_A,
    __vptr_uint8   in_right_B,
    __vptr_uint8   out_left_A,
    __vptr_uint8   out_right_B,
    unsigned short width,
    unsigned short height,
    unsigned short out_stride
)
{
  __vector vin_left;
  __vector vin_right;
  __agen Addr_in, Addr_out;
  for(int I1 = 0; I1 < height; I1++)
  {
    Addr_in = I1;
    vin_left  = in_left_A[Addr_in].onept();
    vin_right = in_right_B[Addr_in].onept();
    for(int I2 = 0; I2 < (width + VCOP_SIMD_WIDTH - 1)/VCOP_SIMD_WIDTH; I2++)
    {
      Addr_out = I1*out_stride + I2*VCOP_SIMD_WIDTH;
      out_left_A[Addr_out]  = vin_left;
      out_right_B[Addr_out] = vin_right;
    }
  }

}


void vcop_yuv_left_right_padding_u16
(
    __vptr_uint16   in_left_A,
    __vptr_uint16   in_right_B,
    __vptr_uint16   out_left_A,
    __vptr_uint16   out_right_B,
    unsigned short width,
    unsigned short height,
    unsigned short out_stride
)
{
  __vector vin_left;
  __vector vin_right;
  __agen Addr_in, Addr_out;
  for(int I1 = 0; I1 < height; I1++)
  {
    Addr_in = I1*2;
    vin_left  = in_left_A[Addr_in].onept();
    vin_right = in_right_B[Addr_in].onept();
    for(int I2 = 0; I2 < (width + VCOP_SIMD_WIDTH - 1)/VCOP_SIMD_WIDTH; I2++)
    {
      Addr_out = I1*out_stride*2 + I2*VCOP_SIMD_WIDTH*2;
      out_left_A[Addr_out]  = vin_left;
      out_right_B[Addr_out] = vin_right;
    }
  }

}
