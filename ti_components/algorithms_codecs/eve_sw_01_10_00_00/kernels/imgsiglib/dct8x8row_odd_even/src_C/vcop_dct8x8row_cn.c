

/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME                                                                 */
/*         vcop_dct8x8row, 8x8 rowwise DCT for the VICP library.            */
/*                                                                          */
/*                                                                          */
/*     USAGE                                                                */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_dct8x8row                                                  */
/*      (                                                                   */
/*         signed char  *in,                                                */
/*         signed char  *f,                                                 */
/*         signed short *out,                                               */
/*         int          w_input,                                            */
/*         int          h_input,                                            */
/*         int          w_out,                                              */
/*         int          h_out,                                              */
/*         int          calc_HBLKS,                                         */
/*         int          calc_VBLKS,                                         */
/*         int          type_input,                                         */
/*         int          type_coeff,                                         */
/*         int          type_output,                                        */
/*         int          rnd_shift                                           */
/*     )                                                                    */
/*                                                                          */
/*                                                                          */
/*      *in        :  Pointer to an input array of "type_input".            */
/*      *f         :  This pointer is ignored, in this implementation       */
/*                    the DCT coeffs are implicitly defined within kernel   */
/*      *out       :  Pointer to output array of "type_output".             */
/*      w_input    :  Width of the input image in pixels.                   */
/*      h_input    :  Height of the input image in pixels.                  */
/*      w_out      :  Width of the output in pixels.                        */
/*      h_out      :  Height of the output coefficents in pixels.           */
/*      calc_HBLKS :  The number of 8x8 blocks of input in horz direction.  */
/*      calc_VBLKS :  The number of 8x8 blocks of input in vert direction.  */
/*      type_input :  0 - UBYTE, 1 - BYTE, 2 - USHORT, 3 - SHORT            */
/*      type_coeff :  This is also ignored, coefficients are always 32-bit  */
/*                 :  int and implicitly defined.                           */
/*      type_output:  0 - BYTE,  1 - SHORT                                  */
/*      Rnd_shift  :  Noneround and shift amount may be specified.          */
/*                                                                          */
/*  ASSUMPTIONS                                                             */
/*  - While The C code does not have any assumptions on the size of         */
/*  the arrays, the assembly code assumes that the DCT is computed on       */
/*  8x8 block of input at a time.                                           */
/*  - The DCT coefficients are implicitly defined. There is no need to      */
/*  pass them from the calling function to the callee.                      */
/*  - Input data is in Q12 format, DCT coefficients are in Q15 format.      */
/*                                                                          */
/*     DESCRIPTION                                                          */
/*             This routine accepts pointers to a input region "in", where  */
/*     the region is assumed to be in 8x8 blocks with a total of            */
/*     (calc_HBLKS * calc_VBLKS) and 1-D DCT is carried out on each of the  */
/*     8x8 blocks and output is written out to "out".                       */
/*                                                                          */
/*                                                                          */
/*==========================================================================*/
/*      Copyright (C) 2009-2012 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "../inc/eve_dct8x8row_tb.h"


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

void vcop_dct8x8row_cn
(
    short  *in, 
    short  *f, 
    short *out,
    int   w_input, 
    int   h_input, 
    int   w_out,
    int   h_out,
    int   calc_HBLKS,
    int   calc_VBLKS,
    int   type_input, // 0 - UBYTE, 1 - BYTE, 2 - USHORT, 3 - SHORT
    int   type_coeff, // 0 - UBYTE, 1 - BYTE, 2 - USHORT, 3 - SHORT
    int   type_output,// 0 - BYTE,  1 - SHORT
    int   rnd_shift 
)
{
    int   x[8] = {0};
    int   i, j;
    int   blk_w, blk_h;
    int   h_coeff, w_coeff;
    int   rnd_add;
    int   rnd_shift_2;
    int   sat_low_cmp, sat_low_val, sat_high_cmp, sat_high_val;
    int   x0_1, x2_1, x4_1, x6_1, x1_1, x3_1,  x5_1, x7_1;
    int   x0_2, x2_2, x4_2, x6_2, x1_2, x3_2,  x5_2, x7_2;
    int   x0_3, x2_3, x4_3, x6_3, x1_3, x3_3,  x5_3, x7_3;
    int   c00, c22, c23, c33, c44, c45, c46, c47, c55, c56, c57; 
    int  res_a, res_b, res_c, res_d, res_e, res_f, res_g, res_h;


    h_coeff = w_coeff = 8;

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
    /* Read the coefficients separately to reduce memory accesses.       */
    /* Coefficients are in Q-15 format.                                  */
    /*-------------------------------------------------------------------*/

    c00 = 23173;
    c22 = 30271;
    c23 = 12537;
    c44 = 32138;
    c45 = 27243;
    c46 = 18208;
    c47 =  6389;
    c33 = -c22;
    c55 = -c47;
    c56 = -c44;
    c57 = -c46;

    /*-------------------------------------------------------------------*/
    /* DCT rowumn wise filtering. This is the part where the transform T */
    /* (8x8) is applied to image block A as T*A.                         */
    /*-------------------------------------------------------------------*/

    for ( blk_h = 0; blk_h < calc_VBLKS; blk_h++)
    {
        for ( blk_w = 0; blk_w < calc_HBLKS; blk_w++)
        {              
            for ( j = 0; j < (int) w_coeff; j++) 
            { 
                for ( i = 0; i < (int) h_coeff; i++) 
                {
                    x[i] = in[ ( (i + (blk_h * w_coeff) )* w_input) + j + (blk_w * h_coeff)];
                }

                /*-------------------------------------------------------*/
                /* First stage of butterfly -                            */
                /*-------------------------------------------------------*/

                x0_1 = x[0] + x[7];
                x2_1 = x[1] + x[6];
                x4_1 = x[2] + x[5];
                x6_1 = x[3] + x[4];
               
                x1_1 = x[0] - x[7];
                x3_1 = x[1] - x[6];
                x5_1 = x[2] - x[5];
                x7_1 = x[3] - x[4];
             
                /*-------------------------------------------------------*/
                /* Second stage of butterfly -                           */
                /*-------------------------------------------------------*/

                x0_2 = x0_1 + x6_1;
                x2_2 = x2_1 + x4_1;
                x4_2 = x0_1 - x6_1;
                x6_2 = x2_1 - x4_1;

                x1_2 = x1_1;
                x3_2 = x3_1;
                x5_2 = x5_1;
                x7_2 = x7_1;

                /*-------------------------------------------------------*/
                /* Third stage of butterfly -                            */
                /*-------------------------------------------------------*/

                x0_3 = x0_2 + x2_2;
                x2_3 = x0_2 - x2_2;
                x4_3 = x4_2;  
                x6_3 = x6_2;  
                            
                x1_3  = x1_2; 
                x3_3  = x3_2; 
                x5_3  = x5_2; 
                x7_3  = x7_2;

                /*-------------------------------------------------------*/
                /* Transform coefficients multiplied with the input data */
                /* reordered and manipulated using butterfly.            */
                /*                                                       */
                /* Note: T16 "MPY" reads two 32-bit src registers and    */
                /* writes to a 32-bit dest register. Hence, the src      */
                /* registers have to be shifted right accordingly to     */
                /* ensure valid bits are used in the multiply.           */
                /*-------------------------------------------------------*/

                res_a = c00 * x0_3;
                res_b = c00 * x2_3;
                res_c = (c22 * x4_3) + ( c23 * x6_3);
                res_d = (c23 * x4_3) + ( c33 * x6_3);
                res_e = (c44 * x1_3) + ( c45 * x3_3) + ( c46 * x5_3) + (c47 * x7_3);
                res_f = (c45 * x1_3) + ( c55 * x3_3) + ( c56 * x5_3) + (c57 * x7_3);
                res_g = (c46 * x1_3) + ( c56 * x3_3) + ( c47 * x5_3) + (c45 * x7_3);
                res_h = (c47 * x1_3) + ( c57 * x3_3) + ( c45 * x5_3) + (c56 * x7_3);

                /*-------------------------------------------------------*/
                /* Output data is reordered to write to the correct      */ 
                /* location.                                             */
                /*-------------------------------------------------------*/        
    

                res_a =  (int) floor( ( (float) res_a + rnd_add )/ (unsigned) rnd_shift_2);
                res_b =  (int) floor( ( (float) res_b + rnd_add )/ (unsigned) rnd_shift_2);
                res_c =  (int) floor( ( (float) res_c + rnd_add )/ (unsigned) rnd_shift_2);
                res_d =  (int) floor( ( (float) res_d + rnd_add )/ (unsigned) rnd_shift_2);
                res_e =  (int) floor( ( (float) res_e + rnd_add )/ (unsigned) rnd_shift_2);
                res_f =  (int) floor( ( (float) res_f + rnd_add )/ (unsigned) rnd_shift_2);
                res_g =  (int) floor( ( (float) res_g + rnd_add )/ (unsigned) rnd_shift_2);
                res_h =  (int) floor( ( (float) res_h + rnd_add )/ (unsigned) rnd_shift_2);


                  if ( res_a < sat_low_cmp)
                       res_a = sat_low_val;

                  if ( res_b < sat_low_cmp)
                       res_b = sat_low_val;
                  
                  if ( res_c < sat_low_cmp)
                       res_c = sat_low_val;

                  if ( res_d < sat_low_cmp)
                       res_d = sat_low_val;

                  if ( res_e < sat_low_cmp)
                       res_e = sat_low_val;

                  if ( res_f < sat_low_cmp)
                       res_f = sat_low_val;

                  if ( res_g < sat_low_cmp)
                       res_g = sat_low_val;

                  if ( res_h < sat_low_cmp)
                       res_h = sat_low_val;

                  if ( res_a > sat_high_cmp)
                       res_a = sat_high_val;
                            
                  if ( res_b > sat_high_cmp)
                       res_b = sat_high_val;
                            
                  if ( res_c > sat_high_cmp)
                       res_c = sat_high_val;
                            
                  if ( res_d > sat_high_cmp)
                       res_d = sat_high_val;
                            
                  if ( res_e > sat_high_cmp)
                       res_e = sat_high_val;
                            
                  if ( res_f > sat_high_cmp)
                       res_f = sat_high_val;
                            
                  if ( res_g > sat_high_cmp)
                       res_g = sat_high_val;
                            
                  if ( res_h > sat_high_cmp)
                       res_h = sat_high_val;


                out[ (( j + (blk_w * 8) + (blk_h * calc_HBLKS * 8 )) *  18 ) + 0]  = (short) res_a;
                out[ (( j + (blk_w * 8) + (blk_h * calc_HBLKS * 8 )) *  18 ) + 1]  = (short) res_e;
                out[ (( j + (blk_w * 8) + (blk_h * calc_HBLKS * 8 )) *  18 ) + 2]  = (short) res_c;
                out[ (( j + (blk_w * 8) + (blk_h * calc_HBLKS * 8 )) *  18 ) + 3]  = (short) res_f;
                out[ (( j + (blk_w * 8) + (blk_h * calc_HBLKS * 8 )) *  18 ) + 4]  = (short) res_b;
                out[ (( j + (blk_w * 8) + (blk_h * calc_HBLKS * 8 )) *  18 ) + 5]  = (short) res_g;
                out[ (( j + (blk_w * 8) + (blk_h * calc_HBLKS * 8 )) *  18 ) + 6]  = (short) res_d;
                out[ (( j + (blk_w * 8) + (blk_h * calc_HBLKS * 8 )) *  18 ) + 7]  = (short) res_h;

            }
        }
    }
    
    return;
}


