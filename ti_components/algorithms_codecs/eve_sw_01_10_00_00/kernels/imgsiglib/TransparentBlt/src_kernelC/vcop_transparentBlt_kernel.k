
/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME                                                                 */
/*         vcop_transparentBlt, transparentBlt for the VICP lib.            */
/*                                                                          */
/*                                                                          */
/*     USAGE                                                                */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_transparentBlt_ushort_ushort                               */
/*     (                                                                    */
/*         unsigned short  *inrgb555_ptr,                                   */
/*         unsigned short  *back_rgb555_ptr,                                */
/*         unsigned short   transparentClr,                                 */
/*         unsigned short   in_rgb555_w,                                    */
/*         unsigned short   in_rgb555_h,                                    */
/*         unsigned short   back_rgb555_w,                                  */ 
/*         unsigned short   back_rgb555_h.                                  */
/*         unsigned short   out_w,                                          */
/*         unsigned short   out_h,                                          */
/*         unsigned short  *outptr                                          */
/*     );                                                                   */
/*                                                                          */
/*                                                                          */
/*      *inrgb555_ptr   :  Pointer to an rgb555 source array.               */
/*      *back_rgb555_ptr:  Pointer to an rgb555 background array.           */
/*      transparentBlt  :  Pointer to alpha array.                          */
/*      in_rgb555_w     :  Width of the input1 image in pixels.             */
/*      in_rgb555_h     :  Height of input1 array in pixels.                */
/*      back_rgb555_w   :  Width of the input1 image in pixels.             */
/*      back_rgb555_h   :  Height of input1 array in pixels.                */
/*      out_w           :  Width of the input1 image in pixels.             */
/*      out_h           :  Height of input1 array in pixels.                */
/*      *outptr         :  Pointer to output array.                         */
/*                                                                          */
/*     Returns :  None or void.                                             */
/*                                                                          */
/*                                                                          */
/*     DESCRIPTION                                                          */
/*      This routine accepts pointers to a input region and background      */
/*     and does a transparentBlt function to produce output pointed to by   */
/*     outptr, using "transparentClr" as the color that is made transparent.*/
/*                                                                          */
/*     PERFORMANCE                                                          */
/*     1/8 cyc/pix                                                          */
/*                                                                          */
/*==========================================================================*/
/*      Copyright (C) 2009-2012 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#define VCOP_2SIMD_WIDTH        (2 * VCOP_SIMD_WIDTH) 

#define ELEMSZ_IN1               sizeof( *inrgb555_ptr )
#define VECTORSZ_IN1             (VCOP_2SIMD_WIDTH * ELEMSZ_IN1)

#define ELEMSZ_IN2               sizeof( *backrgb555_ptr )
#define VECTORSZ_IN2             (VCOP_2SIMD_WIDTH * ELEMSZ_IN2)

#define ELEMSZ_OUT              sizeof( *outptr )
#define VECTORSZ_OUT            (VCOP_2SIMD_WIDTH * ELEMSZ_OUT)

/* * * * * * * * * * * * * * * * * * * * */


void vcop_transparentBlt_ushort_ushort
( 
    __vptr_uint16    inrgb555_ptr, 
    __vptr_uint16    backrgb555_ptr, 
    unsigned short   transparentClr, 
    unsigned short   in1_w, 
    unsigned short   in1_h,                
    unsigned short   in2_w, 
    unsigned short   in2_h,
    unsigned short   comp_w,
    unsigned short   comp_h,
    unsigned short   out_w,
    unsigned short   out_h,
    __vptr_uint16    outptr 
)
{
    __vector Vin0,  Vin1;          // foreground input
    __vector Vbk0,  Vbk1;          // background input
    __vector Vcomp0, Vcomp1;
    __vector VtranspClr;

    VtranspClr = transparentClr;
    
    for (int I1 = 0; I1 < comp_h; I1++) 
    {
        for (int I2 = 0; I2 < comp_w/VCOP_2SIMD_WIDTH; I2++) 
        {
            __agen Addr_in1, Addr_in2, Addr_alpha, Addr_out;
            
            Addr_in1   =  I1 * in1_w * ELEMSZ_IN1 + I2 * VECTORSZ_IN1; 
            Addr_in2   =  I1 * in2_w * ELEMSZ_IN2 + I2 * VECTORSZ_IN2; 
            Addr_out   =  I1 * out_w * ELEMSZ_OUT + I2 * VECTORSZ_OUT; 
            
            (Vin0, Vin1)       =  inrgb555_ptr[Addr_in1].deinterleave();  
            (Vbk0, Vbk1)       =  backrgb555_ptr[Addr_in2].deinterleave();  
  
            /*-----------------------------------------------------------*/
            /* Compare the foreground color to the transparent color     */
            /* value transparentClr.                                     */
            /*-----------------------------------------------------------*/
           
            Vcomp0 = (Vin0 == VtranspClr);
            Vcomp1 = (Vin1 == VtranspClr);

            /*-----------------------------------------------------------*/
            /* Choose from either background or foreground (image to be  */
            /* overlayed).                                               */
            /*-----------------------------------------------------------*/

            Vin0  = select(Vcomp0, Vbk0, Vin0); 
            Vin1  = select(Vcomp1, Vbk1, Vin1);

            outptr[Addr_out].interleave() = (Vin0, Vin1);  
        }
    }
}


/* * * * * * * * * * * * * * * * * * * * */
