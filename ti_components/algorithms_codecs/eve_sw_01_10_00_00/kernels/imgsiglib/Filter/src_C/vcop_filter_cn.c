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
/*     void vcop_filter                                                     */
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
/*     computes the FIR filter result over a block of the image.            */
/*                                                                          */
/*                                                                          */
/*==========================================================================*/
/*      Copyright (C) 2009-2012 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#include <math.h>

#include "../inc/vcop_filter_cn.h"

#define SAT_EN   1

typedef signed   char   Int8;
typedef unsigned char   Uint8;
typedef unsigned short  Uint16;
typedef signed   short  Int16;

static void get_saturation_params
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
           *rnd_add = (int) pow((float)2,(rnd_shift-1));

      *rnd_shift_2 =  (int) pow((float)2,rnd_shift) ;

    /*------------------------------------------------------------------*/
    /* Saturation limits setup.                                         */
    /*------------------------------------------------------------------*/

    if ( type_output == 0)
    {

        *sat_low_cmp  = (int) -pow((float)2,7);
        *sat_low_val  = (int) -pow((float)2,7);
        *sat_high_cmp = (int) (pow((float)2,7) - 1);
        *sat_high_val = (int) (pow((float)2,7) - 1);

    }
    else if ( type_output == 1)
    {
        *sat_low_cmp  = (int) -pow((float)2,15);
        *sat_low_val  = (int) -pow((float)2,15);
        *sat_high_cmp = (int) (pow((float)2,15) - 1);
        *sat_high_val = (int) (pow((float)2,15) - 1);
    }
    else if ( type_output == 2)
	{
        *sat_low_cmp  = (int) 0;
        *sat_low_val  = (int) 0;
        *sat_high_cmp = (int) (pow((float)2,8) - 1);
        *sat_high_val = (int) (pow((float)2,8) - 1);
	}

    return;
}


void filter_cn
(
    unsigned short *in,          // Pointer to an input array of "type_input".
    unsigned short *f,           // Pointer to cofficient array of type 'type_coef'.
    unsigned short *out,         // Pointer to output array of "type_output".
    int            w_input,      // Width of the input image in pixels.
    int            w_coeff,      // Width of the coefficients in pixels.
    int            h_coeff,      // Height of the coefficients in pixels.
    int            w_compute,    // Compute width in pixels.
    int            h_compute,    // Compute height in pixels.
    int            w_out,        // Width of the output image in pixels.
    int            dnsmpl_vert,  // Vertical downsampling value.
    int            dnsmpl_horz,  // Horizontal downsampling value.
    int            type_output,  // 0 - CHAR,  1 - SHORT, 2 - UCHAR
    int            rnd_shift     // Rounding and shifting amount.
)
{
    int x;
    int f_coef;
    long result;
    int i, j, m, n, k, l;
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
    /* Actual filter processing. Vertical downsampling can be applied    */
    /* to the outermost loop increment. Horizontal downsampling is       */
    /* applied to the output.                                            */
    /*-------------------------------------------------------------------*/

    l = 0;
    for ( i = 0; i < (int) h_compute; i++) // lpend1
    {
        k = 0;
        for (j = 0; j < (int) w_compute; j++) //lpend2
        {
            result = 0;


            /*-----------------------------------------------------------*/
            /* Core filter loop.                                         */
            /*-----------------------------------------------------------*/

            for ( m = 0; m < (int) h_coeff; m++) // height == lpend3
            {
                for ( n = 0; n < (int) w_coeff; n++ ) // width == lpend4
                {
                    f_coef = f[m * w_coeff + n ];

                    x = in[((i + m) * w_input) + (j + n) ];
                    result += (x * f_coef);
                }
            }

            /*-----------------------------------------------------------*/
            /* Here we write out the output after applying any           */
            /* horizontal downsampling. Any rounding and saturation      */
            /* steps are also carried out before saving the output.      */
            /*-----------------------------------------------------------*/

            if ( !( j % dnsmpl_horz ) && !( i % dnsmpl_vert ) )
            {


                result =  (int) floor( ( (float) result + rnd_add )/ (unsigned) rnd_shift_2);

                  if ( result < sat_low_cmp)
                     result = sat_low_val;

                  if ( result > sat_high_cmp)
                       result = sat_high_val;

                out[(l * w_out) + k ] = result;
                k++;

            }
        }
        if (!( i % dnsmpl_vert )) l++;
    }

    return;
}



void filter_uchar_cn
(
    unsigned char *in,          // Pointer to an input array of "type_input".
    char          *f,           // Pointer to cofficient array of type 'type_coef'.
    unsigned char *out,         // Pointer to output array of "type_output".
    int            w_input,      // Width of the input image in pixels.
    int            w_coeff,      // Width of the coefficients in pixels.
    int            h_coeff,      // Height of the coefficients in pixels.
    int            w_compute,    // Compute width in pixels.
    int            h_compute,    // Compute height in pixels.
    int            w_out,        // Width of the output image in pixels.
    int            dnsmpl_vert,  // Vertical downsampling value.
    int            dnsmpl_horz,  // Horizontal downsampling value.
    int            type_output,  // 0 - CHAR,  1 - SHORT, 2 - UCHAR
    int            rnd_shift     // Rounding and shifting amount.
)
{
    int x;
    int f_coef;
    long result;
    int i, j, m, n, k, l;
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
    /* Actual filter processing. Vertical downsampling can be applied    */
    /* to the outermost loop increment. Horizontal downsampling is       */
    /* applied to the output.                                            */
    /*-------------------------------------------------------------------*/

    l = 0;
    for ( i = 0; i < (int) h_compute; i++) // lpend1
    {
        k = 0;
        for (j = 0; j < (int) w_compute; j++) //lpend2
        {
            result = 0;


            /*-----------------------------------------------------------*/
            /* Core filter loop.                                         */
            /*-----------------------------------------------------------*/

            for ( m = 0; m < (int) h_coeff; m++) // height == lpend3
            {
                for ( n = 0; n < (int) w_coeff; n++ ) // width == lpend4
                {
                    f_coef = f[m * w_coeff + n ];

                    x = in[((i + m) * w_input) + (j + n) ];
                    result += (x * f_coef);
                }
            }

            /*-----------------------------------------------------------*/
            /* Here we write out the output after applying any           */
            /* horizontal downsampling. Any rounding and saturation      */
            /* steps are also carried out before saving the output.      */
            /*-----------------------------------------------------------*/

            if ( !( j % dnsmpl_horz ) && !( i % dnsmpl_vert ) )
            {


                result =  (int) floor( ( (float) result + rnd_add )/ (unsigned) rnd_shift_2);

                  if ( result < sat_low_cmp)
                     result = sat_low_val;

                  if ( result > sat_high_cmp)
                       result = sat_high_val;

                out[(l * w_out) + k ] = result;
                k++;

            }
        }
        if (!( i % dnsmpl_vert )) l++;
    }

    return;
}

