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
/*     void vcop_FilterPoly                                                 */
/*      (                                                                   */
/*          __vptr_uint16  in,                                              */ 
/*          __vptr_int16   f,                                               */ 
/*          __vptr_uint8   smpl_flag,                                       */ 
/*          __vptr_uint16  out,                                             */ 
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
/*     out         :  Pointer to output array of "type_output".             */
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
/*==========================================================================*/
/*      Copyright (C) 2009-2012 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/


#ifndef __VCOP_FILTER_POLY_H__
#define __VCOP_FILTER_POLY_H__

void vcop_FilterPoly_smallU_uchar_char_short
(
    __vptr_uint8   in,           // Pointer to an input array of "type_input".      
    __vptr_int8    coef,         // Pointer to cofficient array of type 'type_coef'.
    __vptr_int16   res,          // Pointer to output array of "type_output". 
    int            w_input,      // Width of the input image in pixels.             
    int            w_coeff,      // Width of the coefficients in pixels.   
    int            coef_loop_cnt,// how many such coefficient sets
    int            w_compute,    // Compute width in pixels.                        
    int            h_compute,    // Compute height in pixels.                       
    int            D,            // Downsampling value.                    
    int            U,            // Upsampling value.     
    int            OUT_OFSET_VAL,// sometimes we write fewer than 8 outputs and have
                                 // to move output pointer back
    int            rnd_shift     // Rounding and shifting amount.                                                             
);

void vcop_FilterPoly_largeU_uchar_char_short
(
    __vptr_uint8   in,           // Pointer to an input array of "type_input".      
    __vptr_int8    coef,         // Pointer to cofficient array of type 'type_coef'.
    __vptr_int16   res,          // Pointer to output array of "type_output". 
    int            w_input,      // Width of the input image in pixels.             
    int            w_coeff,      // Width of the coefficients in pixels.   
    int            coef_loop_cnt,// how many such coefficient sets
    int            w_compute,    // Compute width in pixels.                        
    int            h_compute,    // Compute height in pixels.                       
    int            D,            // Downsampling value.                    
    int            U,            // Upsampling value.     
    int            OUT_OFSET_VAL,// sometimes we write fewer than 8 outputs and have
                                 // to move output pointer back
    int            rnd_shift     // Rounding and shifting amount.                                                             
);

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
); 

#endif
