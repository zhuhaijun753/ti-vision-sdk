
/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME                                                                 */
/*         vcop_dct8x8col, 8x8 columnwise DCT for the VICP library using    */
/*     Chen's DCT decomposition technique.                                  */
/*                                                                          */
/*                                                                          */
/*     USAGE                                                                */
/*     void vcop_dct8x8col                                                  */
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
/*==========================================================================*/
/*      Copyright (C) 2009-2012 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/



#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "../inc/eve_dct8x8col_tb.h"

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

void vcop_dct8x8col_cn
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
    int   w_coeff, h_coeff;
    int   rnd_add;
    int   rnd_shift_2;
    int   sat_low_cmp, sat_low_val, sat_high_cmp, sat_high_val;
    int   x_0a7, x_1a6, x_2a5, x_3a4, x_0s7, x_1s6,  x_2s5, x_3s4;
    int   x_0a7_a_3a4, x_1a6_a_2a5, x_0a7_s_3a4, x_1a6_s_2a5, x_1s6_a_2s5, x_1s6_s_2s5;
	int   c4_X_x_1s6_a_2s5, c4_X_x_1s6_s_2s5;
	int   x_0s7_a_c4_X_x_1s6_a_2s5,	x_0s7_s_c4_X_x_1s6_a_2s5;
	int   x_3s4_a_c4_X_x_1s6_s_2s5,	x_3s4_s_c4_X_x_1s6_s_2s5;
    int   x_0a7a3a4a1a6a2a5, x_0a7a3a4s1s6s2s5;
    int   c4, c2, c6, c1, c3, c5, c7; 
    int  res_a, res_b, res_c, res_d, res_e, res_f, res_g, res_h;


    w_coeff = h_coeff = 8;
    
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
    /*-------------------------------------------------------------------*/

    c4 = 23173;
    c2 = 30271;
    c6 = 12537;
    c1 = 32138;
    c3 = 27243;
    c5 = 18208;
    c7 =  6389;

    /*-------------------------------------------------------------------*/
    /* DCT column wise filtering. This is the part where the transform T */
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

                x_0a7 = x[0] + x[7];
                x_1a6 = x[1] + x[6];
                x_2a5 = x[2] + x[5];
                x_3a4 = x[3] + x[4];
               
                x_0s7 = x[0] - x[7];
                x_1s6 = x[1] - x[6];
                x_2s5 = x[2] - x[5];
                x_3s4 = x[3] - x[4];

                /*-------------------------------------------------------*/
				/* Second stage of butterfly -                           */
				/*-------------------------------------------------------*/

                x_0a7_a_3a4 = x_0a7 + x_3a4;
                x_1a6_a_2a5 = x_1a6 + x_2a5;
                x_0a7_s_3a4 = x_0a7 - x_3a4;
                x_1a6_s_2a5 = x_1a6 - x_2a5;

				/*-------------------------------------------------------*/
				/* Additional compute for Chen's.                        */
				/*-------------------------------------------------------*/

				x_1s6_a_2s5 = x_1s6 + x_2s5;
				x_1s6_s_2s5 = x_1s6 - x_2s5;

				c4_X_x_1s6_a_2s5 = (c4 * x_1s6_a_2s5) >> 15;
				c4_X_x_1s6_s_2s5 = (c4 * x_1s6_s_2s5) >> 15;

				x_0s7_a_c4_X_x_1s6_a_2s5 = x_0s7 + c4_X_x_1s6_a_2s5;
				x_0s7_s_c4_X_x_1s6_a_2s5 = x_0s7 - c4_X_x_1s6_a_2s5;
				
				x_3s4_a_c4_X_x_1s6_s_2s5 = x_3s4 + c4_X_x_1s6_s_2s5;
				x_3s4_s_c4_X_x_1s6_s_2s5 = x_3s4 - c4_X_x_1s6_s_2s5;
				
                /*-------------------------------------------------------*/
				/* Third stage of butterfly -                            */
				/*-------------------------------------------------------*/

                x_0a7a3a4a1a6a2a5 = x_0a7_a_3a4 + x_1a6_a_2a5;
                x_0a7a3a4s1s6s2s5 = x_0a7_a_3a4 - x_1a6_a_2a5;

                /*-------------------------------------------------------*/
                /* Transform coefficients multiplied with the input data */
                /* reordered and manipulated using butterfly.            */
				/*                                                       */
				/* Note: T16 "MPY" reads two 32-bit src registers and    */
				/* writes to a 32-bit dest register. Hence, the src      */
				/* registers have to be shifted right accordingly to     */
				/* ensure valid bits are used in the multiply.           */
                /*-------------------------------------------------------*/

                res_a = c4 * x_0a7a3a4a1a6a2a5;
                res_b = c4 * x_0a7a3a4s1s6s2s5;

                res_c = (c2 * x_0a7_s_3a4) + ( c6 * x_1a6_s_2a5);
                res_d = (c6 * x_0a7_s_3a4) - ( c2 * x_1a6_s_2a5);

				res_e = c1 * (x_0s7_a_c4_X_x_1s6_a_2s5 ) + c7 * ( x_3s4_a_c4_X_x_1s6_s_2s5);
                res_f = c3 * (x_0s7_s_c4_X_x_1s6_a_2s5 ) - c5 * ( x_3s4_s_c4_X_x_1s6_s_2s5);
                res_g = c5 * (x_0s7_s_c4_X_x_1s6_a_2s5 ) + c3 * ( x_3s4_s_c4_X_x_1s6_s_2s5);
                res_h = c7 * (x_0s7_a_c4_X_x_1s6_a_2s5 ) - c1 * ( x_3s4_a_c4_X_x_1s6_s_2s5);


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


