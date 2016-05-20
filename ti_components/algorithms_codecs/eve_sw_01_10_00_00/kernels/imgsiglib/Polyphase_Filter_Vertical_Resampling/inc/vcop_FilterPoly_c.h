/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME                                                                 */
/*         vcop_filter, FIR filter for the VICP library.                    */
/*                                                                          */
/*                                                                          */
/*     USAGE                                                                */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*                                                                          */
/*     void vcop_FilterPoly_general_cn                                      */
/*      (                                                                   */
/*          unsigned short *in,                                             */ 
/*          short          *f,                                              */ 
/*          unsigned short *res,                                            */ 
/*          unsigned short *out,                                            */ 
/*          int            w_input,                                         */ 
/*          int            ntaps,                                           */   
/*          int            w_compute,                                       */ 
/*          int            h_compute,                                       */ 
/*          int            w_out,                                           */ 
/*          int            D,                                               */ 
/*          int            U,                                               */ 
/*          int            type_output,                                     */ 
/*          int            rnd_shift                                        */ 
/*          );                                                              */
/*                                                                          */
/*                                                                          */
/*     *in         :  Pointer to an input array of "type_input".            */
/*     *f          :  Pointer to coefficient array of type 'type_coef'.     */
/*     *res        :  Pointer to intermediate array of type 'type_output'.  */
/*     *out        :  Pointer to output array of "type_output".             */
/*     w_input     :  Width of the input image in pixels.                   */
/*     ntaps       :  No of coefficients per stage of polyphase.            */
/*     w_compute   :  Compute width in pixels.                              */
/*     h_compute   :  Compute height in pixels.                             */
/*     w_out       :  Width of the output image in pixels.                  */
/*     D           :  Downsampling value.                                   */
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
/*     and is used in this file, by the  vcop_FilterPoly_general_cn()       */
/*     function as the "ntaps" value.                                       */
/*                                                                          */
/*                                                                          */
/*==========================================================================*/
/*      Copyright (C) 2009-2012 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#ifndef __VCOP_FILTER_POLY_H__
#define __VCOP_FILTER_POLY_H__

void vcop_FilterPoly_general_cn
(
    unsigned short *in,          // Pointer to an input array of "type_input".      
    short          *f,           // Pointer to cofficient array of type 'type_coef'.
    unsigned char  *smple_flag,  // Sampling pattern to write the outputs
    unsigned short *out,         // Pointer to output array of "type_output".       
    int            w_input,      // Width of the input image in pixels.             
    int            ntaps,        // No of coefficients per stage of polyphase.            
    int            w_compute,    // Compute width in pixels.                        
    int            h_compute,    // Compute height in pixels.                       
    int            w_out,        // Width of the output image in pixels.             
    int            D,            // Downsampling value.                    
    int            U,            // Upsampling value.                  
    int            type_output,  // 0 - BYTE,  1 - SHORT                            
    int            rnd_shift     // Rounding and shifting amount.                                                             
);

#endif
