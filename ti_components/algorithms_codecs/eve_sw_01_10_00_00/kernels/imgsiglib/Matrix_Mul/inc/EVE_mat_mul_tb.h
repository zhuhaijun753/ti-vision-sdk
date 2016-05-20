/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
void vcop_mat_mul_cn
(
    unsigned char  *in1,         // Pointer to first input array.      
    unsigned char  *in2,         // Pointer to second input array.
    signed short   *out,         // Pointer to output array.       
    int            in1_w,        // Width of the first input array in pixels.             
    int            in1_h,        // Height of the first input array in pixels.            
    int            in2_w,        // Width of the second input array in pixels.           
    int            type_output,  // output type
    int            rnd_shift     // Rounding and shifting amount.                                                            
);
