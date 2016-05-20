/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME                                                                 */
/*         vcop_HorzUpsample, horizontal upsampling of 2D input image       */
/*     data for the VICP library.                                           */
/*                                                                          */
/*                                                                          */
/*     USAGE                                                                */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*                                                                          */
/*     void vcop_HorzUpsample_ushort_short_ushort                           */
/*      (                                                                   */
/*          unsigned short *in,                                             */
/*          short          *f,                                              */
/*          unsigned short *out,                                            */
/*          int            w_input,                                         */
/*          int            ntaps,                                           */
/*          int            w_compute,                                       */
/*          int            h_compute,                                       */
/*          int            w_out,                                           */
/*          int            U,                                               */
/*          int            type_output,                                     */
/*          int            rnd_shift                                        */
/*          );                                                              */
/*                                                                          */
/*                                                                          */
/*     *in         :  Pointer to an input array of "type_input".            */
/*     *f          :  Pointer to coefficient array of type 'type_coef'.     */
/*     *out        :  Pointer to output array of "type_output".             */
/*     w_input     :  Width of the input image in pixels.                   */
/*     ntaps       :  No of coefficients per stage of polyphase.            */
/*     w_compute   :  Compute width in pixels.                              */
/*     h_compute   :  Compute height in pixels.                             */
/*     w_out       :  Width of the output image in pixels.                  */
/*     U           :  Upsampling value.                                     */
/*     type_output :  0 - BYTE,  1 - SHORT                                  */
/*     rnd_shift   :  Rounding and shifting amount.                         */
/*                                                                          */
/*     Returns :  None or void.                                             */
/*                                                                          */
/*     DESCRIPTION                                                          */
/*             This routine accepts pointers to a input region "in", and    */
/*     resamples that block based on up and down-sampling values, using the */
/*     polyphase filtering approach.                                        */
/*                                                                          */
/*     The coefficients used are provided in the coefficient array and are  */
/*     computed externally in the GenFilterCoeffs() function. A "NUM_TAPS"  */
/*     value is also returned to the calling function by GenFilterCoeffs()  */
/*     and is used in this function as the "ntaps" value.                   */
/*                                                                          */
/*     PERFORMANCE:                                                         */
/*     ntaps/U cyc/pix                                                      */
/*                                                                          */
/*==========================================================================*/


#define VCOP_2SIMD_WIDTH (2 * VCOP_SIMD_WIDTH)

#define ELEMSZ_IN        sizeof(*in)
#define VECTORSZ_IN      (VCOP_SIMD_WIDTH * ELEMSZ_IN)

#define ELEMSZ_COEF      sizeof(*f_coef)
#define VECTORSZ_COEF    (VCOP_SIMD_WIDTH * ELEMSZ_COEF)

#define ELEMSZ_OUT       sizeof(*out)
#define VECTORSZ_OUT     (VCOP_SIMD_WIDTH * ELEMSZ_OUT)

#define SAT_LO_CHAR           (0)
#define SAT_HI_CHAR           (255)
#define SAT_LO_SHORT          (0)
#define SAT_HI_SHORT          (65535)


void vcop_HorzUpsample_ushort_short_ushort
(
    __vptr_uint16  in,           // Pointer to an input array of "type_input".      
    __vptr_int16   f_coef,       // Pointer to cofficient array of type 'type_coef'.
    __vptr_uint16  out,          // Pointer to output array of "type_output".       
    int            w_input,      // Width of the input image in pixels.             
    int            ntaps,        // No of coefficients per stage of polyphase.            
    int            w_compute,    // Compute width in pixels.                        
    int            h_compute,    // Compute height in pixels.                       
    int            w_out,        // Width of the output image in pixels.             
    int            U,            // Upsampling value.  
    int            type_output,  // 0 - BYTE,  1 - SHORT                            
    int            rnd_shift     // Rounding and shifting amount.                                                             
)                                                                                        
{

    __vector Vcoef, Vin, Vout;

    /*-------------------------------------------------------------------*/
    /* Actual filter processing. Vertical downsampling can be applied    */
    /* to the outermost loop increment. Horizontal downsampling is       */
    /* applied to the output.                                            */
    /*-------------------------------------------------------------------*/

    for (int I1 = 0; I1 < h_compute; I1++) // lpend1
    {
        for (int I2 = 0; I2 < w_compute; I2++) //lpend2
        {
            __agen OutAddr;

            /*-----------------------------------------------------------*/
            /* For all pixels in the X-direction, we loop over           */
            /* write out only the relevant output pixels in the          */
            /* vertical direction.                                       */
            /*-----------------------------------------------------------*/

             OutAddr = I1 * w_out * ELEMSZ_OUT +
                       I2 * U * ELEMSZ_OUT; 
                       
             /*----------------------------------------------------------*/
             /* We loop over 'ntaps' coefficients.                       */
             /*----------------------------------------------------------*/

            Vout = 0;
            
            for (int I3 = 0; I3 < ntaps; I3++ ) 
            {
                 __agen CoefAddr, InAddr;


                 CoefAddr =  I3 * U * ELEMSZ_COEF;

                 /*------------------------------------------------------*/
                 /* We loop over all input pixels in the course of       */
                 /* filtering operation.                                 */
                 /*------------------------------------------------------*/

                 InAddr   =  I3 * ELEMSZ_IN + 
                             I1 * w_input * ELEMSZ_IN +
                             I2 * ELEMSZ_IN;
                 
                 Vcoef    =  f_coef[CoefAddr].npt();
                 Vin      =  in[InAddr].onept();

                 Vout    +=  (Vin * Vcoef);
            }

            /*-----------------------------------------------------------*/
            /* Round and shift the output here.                          */
            /* Saturate to 16 bit unsigned values if needed here         */
            /*-----------------------------------------------------------*/

            out[OutAddr].npt() = Vout.round(rnd_shift).saturate(SAT_LO_CHAR, SAT_HI_CHAR);
        }
    }
}

