/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME                                                                 */
/*         vcop_filter, Resampling in the vertical direction using          */
/*     polyphase filter for the VICP library.                               */
/*                                                                          */
/*     USAGE                                                                */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*                                                                          */
/*     void vcop_FilterPoly                                                 */
/*      (                                                                   */
/*          __vptr_uint16  in,                                              */ 
/*          __vptr_int16   f,                                               */ 
/*          __vptr_uint8   smpl_flag,                                       */ 
/*          __vptr_uint16  inter_out,                                       */ 
/*          __vptr_uint8   out,                                             */ 
/*          int            w_input,                                         */ 
/*          int            ntaps,                                           */  
/*          int            w_compute,                                       */ 
/*          int            h_compute,                                       */ 
/*          int            w_out,                                           */ 
/*          int            D,                                               */ 
/*          int            U,                                               */ 
/*          int            loop_end,                                        */ 
/*          int            type_output,                                     */ 
/*          int            rnd_shift                                        */ 
/*          );                                                              */
/*                                                                          */
/*                                                                          */
/*     in          :  Pointer to an input array of "type_input".            */
/*     f           :  Pointer to coefficient array of type 'type_coef'.     */
/*     smpl_flag   :  Pointer to sampling flags array of uchar type.        */
/*     inter_out   :  Pointer to output array of "type_output".             */
/*     out         :  Pointer to output array of "type_outputfinal".        */
/*     w_input     :  Width of the input image in pixels.                   */
/*     ntaps       :  No of coefficients per stage of polyphase.            */
/*     w_compute   :  Compute width in pixels.                              */
/*     h_compute   :  Compute height in pixels.                             */
/*     w_out       :  Width of the output image in pixels.                  */
/*     D           :  Downsampling value.                                   */
/*     U           :  Upsampling value.                                     */
/*     loop_end    :  Loop end value.                                       */
/*     type_output :  0 - BYTE,  1 - SHORT                                  */
/*     rnd_shift   :  Rounding and shifting amount.                         */
/*                                                                          */
/*                                                                          */
/*     Returns :  None or void.                                             */
/*                                                                          */
/*                                                                          */
/*     DESCRIPTION                                                          */
/*             This routine accepts pointers to a input region "in", and    */
/*     resamples that block based on up and down-sampling values, using the */
/*     polyphase filtering approach.                                        */
/*                                                                          */
/*     The coefficients used are provided in the coefficient array and are  */
/*     computed externally in the GenFilterCoeffs() function. A "NUM_TAPS"  */
/*     value is also returned to the calling function by GenFilterCoeffs()  */
/*     and is used in this file, by the  vcop_FilterPoly_general_cn()       */
/*     function as the "ntaps" value.                                       */
/*                                                                          */
/*                                                                          */
/*     PERFORMANCE                                                          */
/*     ((U/D + 1) * ntaps)/8 + (1/8) cyc/pix                                */
/*                                                                          */
/*==========================================================================*/
/*      Copyright (C) 2009-2012 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#define VCOP_2SIMD_WIDTH (2 * VCOP_SIMD_WIDTH)

#define ELEMSZ_IN        sizeof(*in)
#define VECTORSZ_IN      (VCOP_SIMD_WIDTH * ELEMSZ_IN)

#define ELEMSZ_COEF      sizeof(*f_coef)
#define VECTORSZ_COEF    (VCOP_SIMD_WIDTH * ELEMSZ_COEF)

#define ELEMSZ_FLG       sizeof(*smpl_flag)

#define ELEMSZ_OUT       sizeof(*inter_out)
#define VECTORSZ_OUT     (VCOP_SIMD_WIDTH * ELEMSZ_OUT)

#define ELEMSZ_OUTFINAL   sizeof(*out)
#define VECTORSZ_OUTFINAL (VCOP_SIMD_WIDTH * ELEMSZ_OUTFINAL)

#define SAT_LO_CHAR           (0)
#define SAT_HI_CHAR           (255)
#define SAT_LO_SHORT          (0)
#define SAT_HI_SHORT          (65535)


void vcop_FilterPoly_ushort_short_ushort
(
    __vptr_uint16  in,           // Pointer to an input array of "type_input".      
    __vptr_int16   f_coef,       // Pointer to cofficient array of type 'type_coef'.
    __vptr_uint8   smpl_flag,    // Pointer to sampling flag array of type char.       
    __vptr_uint16  inter_out,    // Pointer to output array of "type_output".       
    __vptr_uint8   out,          // Pointer to reordered output array of "type_outputfinal".       
    int            w_input,      // Width of the input image in pixels.             
    int            ntaps,        // No of coefficients per stage of polyphase.            
    int            w_compute,    // Compute width in pixels.                        
    int            h_compute,    // Compute height in pixels.                       
    int            w_out,        // Width of the output image in pixels.             
    int            h_out,        // Height of the output image in pixels.             
    int            D,            // Downsampling value.                    
    int            U,            // Upsampling value.
    int            loop_end,     // Loop limit giving number of phases for polyphase
    int            rnd_shift     // Rounding and shifting amount.                                                             
)                                                                                        
{

    __vector Vcoef, Vin, Vflg, Vout;

    /*-------------------------------------------------------------------*/
    /* Actual filter processing. Vertical downsampling can be applied    */
    /* to the outermost loop increment. Horizontal downsampling is       */
    /* applied to the output.                                            */
    /* performance: ((U/D + 1) * ntaps)/8 cyc/pix                        */
    /*-------------------------------------------------------------------*/
   
    _COLLATE(inter_out);
    for (int I1 = 0; I1 < w_compute/VCOP_SIMD_WIDTH; I1++) 
    {
        for (int I2 = 0; I2 < h_compute; I2++)
        {
            /*-----------------------------------------------------------*/
            /* Looping over the coefficients incorporating both the up   */
            /* and downsampling values.                                  */
            /* loop_end can be thought of as the total number of phases. */
            /* loop_end = U/D + 1                                        */
            /*-----------------------------------------------------------*/
     
            for (int I3 = 0; I3 < loop_end; I3++) 
            { 
                __agen FlagAddr;

                /*-------------------------------------------------------*/
                /* For all pixels in the X-direction, we loop over       */
                /* write inter_out only the relevant output pixels in the*/
                /* vertical direction.                                   */
                /*-------------------------------------------------------*/

                FlagAddr = I3 * ELEMSZ_FLG + I2 * loop_end * ELEMSZ_FLG;
  
                Vflg = smpl_flag[FlagAddr].onept();
               
                Vout = 0;

                for (int I4 = 0; I4 < ntaps; I4++ ) 
                {
                     __agen CoefAddr, InAddr;

                     /*--------------------------------------------------*/
                     /* We loop over the coefficients repeatedly where   */
                     /* loop_end gives the number of phases.             */
                     /*--------------------------------------------------*/

                     CoefAddr =  I4 * U * ELEMSZ_COEF + I3 * D * ELEMSZ_COEF;

                     /*--------------------------------------------------*/
                     /* We loop over all input pixels in the course of   */
                     /* filtering operation.                             */
                     /*--------------------------------------------------*/

                     InAddr   =  I4 * w_input * ELEMSZ_IN + 
                                 I2 * w_input * ELEMSZ_IN +
                                 I1 * VCOP_SIMD_WIDTH * ELEMSZ_IN;
                     
                     Vcoef    =  f_coef[CoefAddr].onept();
                     Vin      =  in[InAddr].npt();

                     Vout    +=  (Vin * Vcoef);
  
                }
            
                /*-------------------------------------------------------*/
                /* Round and shift the output here.                      */
                /* Saturate to 16 bit unsigned values if needed here     */
                /*-------------------------------------------------------*/

                inter_out[collate(Vflg)] = Vout.round(rnd_shift).saturate(SAT_LO_CHAR, SAT_HI_CHAR);
            }
        }
    }

    /*-------------------------------------------------------------------*/
    /* Loop to reorder the collated pixels.                              */
    /* performance: (1/8) cyc/pix                                        */ 
    /*-------------------------------------------------------------------*/

    for ( int I1 = 0; I1 < h_out; I1++)
    {
        for (int I2 = 0; I2 < w_compute/VCOP_SIMD_WIDTH; I2++)
        {
            __agen inAddr, outAddr;

            inAddr  =  I2 * h_out * VCOP_SIMD_WIDTH * ELEMSZ_OUT + I1 * VCOP_SIMD_WIDTH * ELEMSZ_OUT;
            outAddr =  I2 * VCOP_SIMD_WIDTH * ELEMSZ_OUTFINAL + I1 * w_compute * ELEMSZ_OUTFINAL;

            Vin = inter_out[inAddr].npt();

            out[outAddr].npt() = Vin;
        }
    }
}

