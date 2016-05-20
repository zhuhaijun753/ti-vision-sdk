/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME                                                                 */
/*         vcop_BayerCFA_HorzUpsample, horizontal upsampling of Bayer CFA   */
/*     data for the VICP library.                                           */
/*                                                                          */
/*                                                                          */
/*     USAGE                                                                */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*                                                                          */
/*     void vcop_BayerCFA_HorzUpsample_ushort_short_ushort                  */
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
/*     and is used by BayerCFA_HorzUpsample_ushort_short_ushort()           */
/*     function as the "ntaps" value.                                       */
/*                                                                          */
/*     PERFORMANCE:                                                         */
/*     ntaps/U cyc/pix                                                      */
/*==========================================================================*/


#ifndef __VCOP_BAYER_CFA_INTERPOLATE_KERNEL_H__
#define __VCOP_BAYER_CFA_INTERPOLATE_KERNEL_H__    1

void vcop_BayerCFA_HorzUpsample_ushort_short_ushort
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
);

#endif

/*-----------------------------------------------------------------*/
/* End of file: vcop_BayerCFA_interpolate_kernel.h                 */
/*=================================================================*/
/* Texas Instruments Incorporated 2009-2012.                       */
/*-----------------------------------------------------------------*/

