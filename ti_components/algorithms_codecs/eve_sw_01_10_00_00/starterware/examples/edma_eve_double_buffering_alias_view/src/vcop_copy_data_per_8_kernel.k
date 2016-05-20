/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME                                                                 */
/*     vcop_copy_data_per_8                                                 */
/*                                                                          */
/*    void vcop_copy_data_per_8 (                                           */
/*         __vptr_uint8 in1_ptr,           // input image data              */
/*         __vptr_uint8 optr_Y,            // output image data             */
/*         unsigned short width,           // image width                   */
/*         unsigned short height           // image height                  */
/*                               )                                          */
/*                                                                          */
/*     DESCRIPTION                                                          */
/*            This routine accepts a pointer to a greyscale image and       */
/*     copies its data to the ouput array declared as optr_Y.               */
/*                                                                          */
/*==========================================================================*/

#define ELEMSZ          sizeof(*in1_ptr)
#define VECTORSZ        (VCOP_SIMD_WIDTH*ELEMSZ)

void vcop_copy_data_per_8
(
   __vptr_uint8     in1_ptr,           
   __vptr_uint8     optr_Y,            
   unsigned short   width,           
   unsigned short   height           
)
{
    __vector Vin1;         

    for (int I4 = 0; I4 < ((width*height)/VCOP_SIMD_WIDTH); I4++)
    {
        __agen Addr;
      
        /* --------------------------------------------------------------- */
        /* Input and Output Address Increments                             */
        /* --------------------------------------------------------------- */
           
        Addr  = I4 * VECTORSZ; 
        Vin1 = in1_ptr[Addr];
        optr_Y[Addr] = Vin1;
    }

}

/*============================================================================*/
/* Texas Instruments Incorporated 2010-2012.                                  */
/*============================================================================*/

