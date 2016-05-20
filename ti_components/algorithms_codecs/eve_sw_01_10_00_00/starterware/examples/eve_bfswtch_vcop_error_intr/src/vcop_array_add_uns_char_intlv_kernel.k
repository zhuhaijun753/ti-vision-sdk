/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*----------------------------------------------------------------------------*/
/* NAME: eve_array_add_uns_char_intlv                                         */
/*                                                                            */
/* DESCRIPTION:                                                               */
/*                                                                            */
/* The function "eve_array_add_uns_char_intlv" takes two input arrays         */
/* in1_ptr and in2_ptr, and adds the values in them writing it out to         */
/* the output array "optr". The input and output arrays are 2D arrays         */
/* of the form [width * height].                                              */
/*                                                                            */
/* The function has the following prototype:                                  */
/*                                                                            */
/* void eve_array_add_uns_char_intlv                                          */
/* (                                                                          */
/*    __vptr_uint8  in1_ptr,         // input 1 data pointer                  */
/*    __vptr_uint8  in2_ptr,         // input 2 data pointer                  */
/*    __vptr_uint8  optr,            // output data pointer                   */
/*   unsigned short width,           // width of each line                    */
/*   unsigned short height           // height of each line                   */
/* )                                                                          */
/*                                                                            */
/* ASSUMPTIONS:                                                               */
/*                                                                            */
/* This function does not expect any alignment restrictions on "in1_ptr"      */
/* "in2_ptr" and "optr". It expects the width to be a multiple of 16, and     */
/* can be as small as 16.                                                     */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/* Texas Instruments Incorporated 2010-2012.                                  */
/*============================================================================*/

#define ELEMSZ              sizeof(*in1_ptr)
#define VECTORSZ            (2 * VCOP_SIMD_WIDTH*ELEMSZ)
#define VCOP_2SIMD_WIDTH    (2 * VCOP_SIMD_WIDTH)

void eve_array_add_uns_char_intlv
(
   __vptr_uint8  in1_ptr,         // input 1 data pointer
   __vptr_uint8  in2_ptr,         // input 2 data pointer
   __vptr_uint8  optr,            // output data pointer
  unsigned short width,           // width of each line
  unsigned short height           // height of each line
)
{
   __vector Vin1,  Vin2;          // input from array input1
   __vector Vin3,  Vin4;          // input from array input2
   __vector Vout1, Vout2;         // outputs


   for (int I1 = 0; I1 < height; I1++)
   {
       for (int I2 = 0; I2 < width/VCOP_2SIMD_WIDTH; I2++)
       {
           __agen Addr;
      
           Addr = I1*width*ELEMSZ + I2*VECTORSZ; 

           (Vin1,Vin2)     = in1_ptr[Addr].deinterleave();
           (Vin3,Vin4)     = in2_ptr[Addr].deinterleave();
           Vout1           = Vin1 + Vin3;
           Vout2           = Vin2 + Vin4;
           optr[Addr].interleave() = (Vout1, Vout2);
       }
   }
}

/*----------------------------------------------------------------------------*/
/* End of file: vcop_array_add_uns_char_intlv_kernel.k                        */
/*----------------------------------------------------------------------------*/
/* Texas Instruments Incorporated 2010-2012.                                  */
/*============================================================================*/

