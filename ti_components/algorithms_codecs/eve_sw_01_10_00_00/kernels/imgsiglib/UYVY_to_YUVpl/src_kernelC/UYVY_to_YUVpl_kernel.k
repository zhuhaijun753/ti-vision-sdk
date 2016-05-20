/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/*----------------------------------------------------------------------------*/
/* NAME: eve_UYVY_to_YUVpl                                                    */
/*                                                                            */
/* DESCRIPTION:                                                               */
/*                                                                            */
/* The function "eve_UYVY_to_YUVpl" takes an interleaved array of luma and    */
/* chroma pixels YUV 4:2:2 and deinterleaves them into three separate memory  */
/* regions.                                                                   */
/*                                                                            */
/* The function has the following prototype:                                  */
/*                                                                            */
/* void eve_UYVY_to_YUVpl                                                     */
/* (                                                                          */
/*   __vptr_uint16 in1_ptr,           // interleaved YUV image data           */
/*          int width,                // image width                          */
/*          int line_pitch,           // pitch of each line                   */
/*          int height,               // image height                         */
/*   __vptr_uint8 optr_Y,             // output data pointer, Y               */
/*   __vptr_uint8 optr_Cr,            // output data pointer, Cr              */
/*   __vptr_uint8 optr_Cb             // output data pointer, Cb              */
/* )                                                                          */
/*                                                                            */
/*                                                                            */
/* The input data is stored in the following format:                          */
/*                                                                            */
/*                Byte 0   Byte 1  Byte 2  Byte 3                             */
/*                  Cb0      Y0      Cr0     Y1                               */
/*                                                                            */ 
/* The image data is loaded as 16-bit halfwords where each half word contains */
/* a Y component and either a Cr or Cb component. Planarization is done       */
/* by using store-byte to ignore the upper byte of the half word and store    */
/* only Cb and Cr, and store-byte with trunction by 8-bits to shift the luma  */ 
/* from the upper byte to the lower byte before the store.                    */
/*                                                                            */
/* ASSUMPTIONS:                                                               */
/*                                                                            */
/* This function expects the image width to be a multiple of 16.              */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/* Texas Instruments Incorporated 2010-2012.                                  */
/*============================================================================*/


#define ELEMSZ              sizeof(*in1_ptr)
#define OUT_ELEMSZ          sizeof(*optr_Y)
#define VECTORSZ            (2 * VCOP_SIMD_WIDTH*ELEMSZ)
#define OUT_Y_VECTORSZ      (2 * VCOP_SIMD_WIDTH*OUT_ELEMSZ)
#define OUT_CrCb_VECTORSZ   (VCOP_SIMD_WIDTH*OUT_ELEMSZ)
#define VCOP_2SIMD_WIDTH    (2 * VCOP_SIMD_WIDTH)

void eve_UYVY_to_YUVpl
(
   __vptr_uint16 in1_ptr,           // interleaved YUV image data
          int    width,             // image width
          int    line_pitch,        // pitch of each line
          int    height,            // image height
   __vptr_uint8 optr_Y,             // output data pointer, Y
   __vptr_uint8 optr_Cr,            // output data pointer, Cr
   __vptr_uint8 optr_Cb             // output data pointer, Cb    

)
{
   __vector Vin1,  Vin2;         

   for (int I1 = 0; I1 < height; I1++)
   {
       for (int I2 = 0; I2 < width/VCOP_2SIMD_WIDTH; I2++)
       {
           __agen Addr, AddrOut_Y, AddrOut_CrCb;
      
           /* --------------------------------------------------------------- */
           /* Input Increments                                                */
           /* --------------------------------------------------------------- */
           Addr         = I1*line_pitch*ELEMSZ    + I2*VECTORSZ; 

           /* --------------------------------------------------------------- */
           /* Output Increments                                               */
           /* Cr & Cb are half the width of the Y data                        */
           /* --------------------------------------------------------------- */
           AddrOut_Y    = I1*width*OUT_ELEMSZ     + I2*OUT_Y_VECTORSZ;
           AddrOut_CrCb = I1*(width/2)*OUT_ELEMSZ + I2*OUT_CrCb_VECTORSZ;

           /* --------------------------------------------------------------- */
           /* Load the interleaved image data in half-word chunks. For        */
           /* example:                                                        */
           /*            Vin1 = {Y0 Cb0, Y2 Cb1, Y4 Cb2, . . . Y14 Cb7}       */
           /*            Vin2 = {Y1 Cr0, Y3 Cr1, Y5 Cr2, . . . Y15 Cr7}       */
           /* --------------------------------------------------------------- */                        
           (Vin1,Vin2) = in1_ptr[Addr].deinterleave();

           /* --------------------------------------------------------------- */
           /* Luma data is in upper byte of half word Vin1 and Vin2           */
           /* Perform a truncation by 8-bits to extract and store             */
           /* the luma value to memory.                                       */
           /* --------------------------------------------------------------- */
           optr_Y[AddrOut_Y].interleave() = (Vin1, Vin2).truncate(8);

           /* --------------------------------------------------------------- */
           /* Cb and Cr pixels are in the lower bytes of the odd and even     */
           /* registers from the deinterleaving load. Since the luma pixel is */
           /* in the upper byte of the half word, we use a "store byte" so    */
           /* that only the Cr/Cb data is stored in these memory locations.   */
           /* --------------------------------------------------------------- */ 
           optr_Cb[AddrOut_CrCb] = Vin1;
           optr_Cr[AddrOut_CrCb] = Vin2;
       }
   }
}

/*----------------------------------------------------------------------------*/
/* End of file: UYVY_to_YUVpl_kernel.k                                        */
/*----------------------------------------------------------------------------*/
/* Texas Instruments Incorporated 2010-2012.                                  */
/*============================================================================*/

