/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME                                                                 */
/*         vcop_mat_mul, mat_mul for the VICP library.                      */
/*                                                                          */
/*                                                                          */
/*     USAGE                                                                */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*                                                                          */
/*     void vcop_mat_mul                                                    */
/*     (                                                                    */
/*         unsigned char  *in,                                              */
/*         unsigned char  *f,                                               */
/*         unsigned char  *out,                                             */
/*         int            w_input,                                          */
/*         int            h_input,                                          */
/*         int            w_coeff,                                          */
/*         int            h_coeff,                                          */
/*         int            w_out,                                            */
/*         int            h_out,                                            */
/*         int            w_compute,                                        */
/*         int            h_compute,                                        */
/*         int            dnsmpl_vert,                                      */
/*         int            dnsmpl_horz,                                      */
/*         int            type_input,                                       */
/*         int            type_coeff,                                       */
/*         int            type_output,                                      */
/*         int            rnd_shift                                         */        
/*      );                                                                  */
/*                                                                          */
/*                                                                          */
/*     *in         :  Pointer to an input array of "type_input".            */
/*     *f          :  Pointer to cofficient array of type 'type_coef'.      */
/*     *out        :  Pointer to output array of "type_output".             */
/*     w_input     :  Width of the input image in pixels.                   */
/*     h_input     :  Height of the input block in pixels.                  */
/*     w_coeff     :  Width of the coefficients in pixels.                  */
/*     h_coeff     :  Height of the coefficients in pixels.                 */
/*     w_out       :  Width of the output in pixels.                        */
/*     h_out       :  Height of the output in pixels.                       */
/*     w_compute   :  Compute width in pixels.                              */
/*     h_compute   :  Compute height in pixels.                             */
/*     dnsmpl_vert :  Vertical downsampling value.                          */
/*     dnsmpl_horz :  Horizontal downsampling value.                        */
/*     type_input  :  0 - UBYTE, 1 - BYTE, 2 - USHORT, 3 - SHORT            */
/*     type_coeff  :  0 - UBYTE, 1 - BYTE, 2 - USHORT, 3 - SHORT            */
/*     type_output :  0 - BYTE,  1 - SHORT                                  */
/*     rnd_shift   :  Rounding and shifting amount.                         */
/*                                                                          */
/*                                                                          */
/*     Returns :  None or void.                                             */
/*                                                                          */
/*                                                                          */
/*     DESCRIPTION                                                          */
/*             This routine accepts pointers to a input region "in", and    */
/*     computes the mat_mul result over a block of the image.               */
/*                                                                          */
/*                                                                          */
/*==========================================================================*/
/*      Copyright (C) 2009-2012 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#include <math.h>

#include "../inc/EVE_mat_mul_tb.h"

#define SAT_EN   1

typedef signed   char   Int8;
typedef unsigned char   Uint8;
typedef unsigned short  Uint16;
typedef signed   short  Int16;

void get_saturation_params
(
    int rnd_shift, 
    int type_output, 
    int *rnd_add, 
    int *rnd_shift_2,
    int *sat_low_cmp,
    int *sat_low_val, 
    int *sat_high_cmp,
    int *sat_high_val
)
{

    /*-------------------------------------------------------------------*/
    /* Round and shift setup.                                            */
    /*-------------------------------------------------------------------*/

      if ( ( rnd_shift <= 0 ))
           *rnd_add = 0;
      else
           *rnd_add = (int) pow(2,(rnd_shift-1));

      *rnd_shift_2 =  (int) pow(2,rnd_shift) ;

    /*------------------------------------------------------------------*/
    /* Saturation limits setup.                                         */
    /*------------------------------------------------------------------*/

    if ( type_output == 0)
    {

        *sat_low_cmp  = (int) -pow(2,7);
        *sat_low_val  = (int) -pow(2,7);
        *sat_high_cmp = (int) (pow(2,7) - 1);
        *sat_high_val = (int) (pow(2,7) - 1);

    }
    else
    {
        *sat_low_cmp  = (int) -pow(2,15);
        *sat_low_val  = (int) -pow(2,15);
        *sat_high_cmp = (int) (pow(2,15) - 1);
        *sat_high_val = (int) (pow(2,15) - 1);
    }

    return;
}


void vcop_mat_mul_cn
(
    unsigned char  *in1,         // Pointer to first input array.      
    unsigned char  *in2,         // Pointer to second input array.
    signed short   *out,         // Pointer to output array.       
    int            in1_w,        // Width of the first input array in pixels.             
    int            in1_h,        // Height of the first input array in pixels.            
    int            in2_w,        // Width of the second input array in pixels.   
    int            type_output,  // Type of output result.
    int            rnd_shift     // Rounding and shifting amount.                                                            
)
{
    int sum;
    int i, j, k;
    int rnd_shift_2;
    int rnd_add;
    int sat_low_cmp, sat_low_val, sat_high_cmp, sat_high_val;

    /*-------------------------------------------------------------------*/
    /* Compute the saturation parameters.                                */
    /*-------------------------------------------------------------------*/
 
    get_saturation_params
    (
        rnd_shift, 
        type_output, 
        &rnd_add, 
        &rnd_shift_2,
        &sat_low_cmp,
        &sat_low_val, 
        &sat_high_cmp,
        &sat_high_val
    ); 


    /*-------------------------------------------------------------------*/
    /* Actual mat_mul processing. Vertical downsampling can be applied   */
    /* to the outermost loop increment. Horizontal downsampling is       */
    /* applied to the output.                                            */
    /*-------------------------------------------------------------------*/

    for ( j = 0; j < in1_h; j++)
    {
        

        for ( k = 0; k < in2_w; k++)
        {
            sum = 0;
            for ( i = 0; i < in1_w; i++)
            {
                sum += (in1[ (j * in2_w) + i] * in2[ ( i * in2_w) + k]);

            }

            /*---------------------------------------------------------*/
            /* Rounding and saturation part.                           */
            /*---------------------------------------------------------*/

            sum =  (int) floor( ( (float) sum + rnd_add )/ (unsigned) rnd_shift_2);
            
            if ( sum < sat_low_cmp)
                sum = sat_low_val;
            
            if ( sum > sat_high_cmp)
                sum = sat_high_val;
            
            out[ (j * in2_w) + k] = sum;
        }
    }

    return;
}


