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
/*          unsigned char  *smple_flag,                                     */
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
/*     *smple_flag :  Pointer to sampling flags of type 'type_coef'.        */
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

#include <math.h>
#include <stdio.h>

#include "../inc/vcop_FilterPoly_c.h"

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
)                                                                                        
{
    int x;
    int f_coef;
    long result;
    int i, j, m, n, k;
    int rnd_shift_2;
    int rnd_add;
    int sat_low_cmp, sat_low_val, sat_high_cmp, sat_high_val;
    int loop_end;

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
    /* Select a loop limit value based on whether U is indeed greater    */
    /* than D. So, if U < D, we set the loop end value to 1, else (U/D+1)*/
    /*-------------------------------------------------------------------*/

    loop_end = (U >= D) ? ((U/D) + 1) : 1;

    /*-------------------------------------------------------------------*/
    /* Actual filter processing. Vertical downsampling can be applied    */
    /* to the outermost loop increment. Horizontal downsampling is       */
    /* applied to the output.                                            */
    /*-------------------------------------------------------------------*/

    for ( i = 0; i < (int) w_compute; i++) // lpend1
    {
        k = 0;
        for (j = 0; j < (int) h_compute; j++) //lpend2
        {
            result = 0;

            /*-----------------------------------------------------------*/
            /* Looping over the coefficients incorporating both the up   */
            /* and downsampling values.                                  */
            /*-----------------------------------------------------------*/
            
            for ( m = 0; m < (int) loop_end; m++) 

            { 
                result = 0;
                
                for ( n = 0; n < (int) ntaps; n++ ) 
                {
                    f_coef = f[(n * U) + ( m * D) ];
                    x = in[i  + ((j + n)  * w_input) ];
                    result += (x * f_coef);
                }            
            
                /*-------------------------------------------------------*/
                /* Round and shift the output here.                      */
                /*-------------------------------------------------------*/

                result =  (int) floor( ( (float) result + rnd_add )/ (unsigned) rnd_shift_2);
              
                /*-------------------------------------------------------*/
                /* Saturate to 16 bit unsigned values if needed here     */
                /*-------------------------------------------------------*/

                result = (result < 0) ? 0 : ((result > 255) ? 255 : result);

                if (smple_flag[(j * loop_end) + m])
                {
                    out[(k * w_out) + i] = (unsigned short) result;
                    k++;
                }
            }
        }
    }

    return;
}

