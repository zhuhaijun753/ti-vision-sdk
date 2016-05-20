/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*----------------------------------------------------------------------------*/
/* NAME: eve_array_add_uns_char_                                              */
/*                                                                            */
/* DESCRIPTION:                                                               */
/*                                                                            */
/* The function "eve_array_add_uns_char_     " takes two input arrays         */
/* in1_ptr and in2_ptr, and adds the values in them writing it out to         */
/* the output array "optr". The input and output arrays are 2D arrays         */
/* of the form [width * height].                                              */
/*                                                                            */
/* The function has the following prototype:                                  */
/*                                                                            */
/* void eve_array_add_uns_char_                                               */
/* (                                                                          */
/*    __vptr_uint8  in1_ptr,         // input 1 data pointer                  */
/*    __vptr_uint8  in2_ptr,         // input 2 data pointer                  */
/*    __vptr_uint8  optr,            // output data pointer                   */
/*           Uint16 width,           // width of each line                    */
/*           Uint16 height           // height of each line                   */
/* )                                                                          */
/*                                                                            */
/* ASSUMPTIONS:                                                               */
/*                                                                            */
/* This function does not expect any alignment restrictions on "in1_ptr"      */
/* "in2_ptr" and "optr". It expects the width to be a multiple of 8, and      */
/* can be as small as 8.                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/* Texas Instruments Incorporated 2010-2012.                                  */
/*============================================================================*/

#define ELEMSZ          sizeof(*in1_ptr)
#define VECTORSZ        (VCOP_SIMD_WIDTH*ELEMSZ)

void eve_array_add_uns_char
(
   __vptr_uint8    in1_ptr,         // input 1 data pointer
   __vptr_uint8    in2_ptr,         // input 2 data pointer
   __vptr_uint8    optr,            // output data pointer
   unsigned short  width,           // width of each line
   unsigned short  height           // height of each line
)
{
   __vector Vin1;                 // input1
   __vector Vin2;                 // input2
   __vector Vout;                 // output
   __vector Vdum;                 // dum

   for (int I0 = 0; I0 < 1; I0++)
   {
       for (int I1 = 0; I1 < height; I1++)
       {
           for (int I2 = 0; I2 < width/VCOP_SIMD_WIDTH; I2++)
           {
               __agen Addr;
      
               Addr = I1*width*ELEMSZ + I2*VECTORSZ; 

               Vin1     = in1_ptr[Addr];
               Vin2     = in2_ptr[Addr];
               Vout     = Vin1 + Vin2;
               optr[Addr] = Vout;
           }
       }
   }
}

/*----------------------------------------------------------------------------*/
/* End of file: vcop_array_add_uns_char_kernel.k                              */
/*----------------------------------------------------------------------------*/
/* Texas Instruments Incorporated 2010-2012.                                  */
/*============================================================================*/

