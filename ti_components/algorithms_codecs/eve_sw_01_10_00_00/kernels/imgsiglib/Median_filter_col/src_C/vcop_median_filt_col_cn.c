/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME                                                                 */
/*         vcop_median_filt_col, median filter for the VICP library.        */
/*                                                                          */
/*                                                                          */
/*     USAGE                                                                */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_median_filt_col_cn                                         */ 
/*     (                                                                    */
/*         Int16 *input_ptr,	                                            */
/*         Int16 *output_ptr,	                                            */
/*         Int16 input_width,	                                            */
/*         Int16 input_height,                                              */
/*         Int16 output_width,                                              */
/*         Int16 output_height,                                             */
/*         Int16 compute_width,                                             */
/*         Int16 compute_height,                                            */
/*         Int16 median_size,	                                            */
/*         Int16 input_type,	                                            */
/*         Int16 output_type	                                            */
/*     );                                                                   */
/*                                                                          */
/*     *input_ptr	 :  Pointer to an input array of "type_input"           */
/*     *output_ptr	 :  Pointer to output array of "type_output"            */
/*     input_width	 :  Input width size                                    */
/*     input_height  :  Input height size                                   */
/*     output_width  :  Output width size                                   */
/*     output_height :  Output height size                                  */
/*     compute_width :  The compute width over which median is computed     */
/*     compute_height:  The compute height for median filter                */
/*     median_size	 :  Indicates 3-tap or 5-tap filter                     */
/*     input_type	 :  0 - UBYTE, 1 - BYTE, 2 - USHORT, 3 - SHORT          */
/*     output_type	 :  0 - BYTE,  1 - SHORT                                */
/*                                                                          */
/*     Returns       :  None or void.                                       */
/*                                                                          */
/*     DESCRIPTION                                                          */
/*             This routine accepts pointers to a input region "in", and    */
/*     computes the median on a 3-tap or 5-tap col block of the image.      */
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

typedef unsigned char  Uint8;
typedef unsigned short Uint16;
typedef unsigned int   Uint32;

typedef char    Int8;
typedef short   Int16;
typedef int     Int32;

#include "EVE_median_filt_col_tb.h"

#define MAX(a, b) (a > b ? a : b)
#define MIN(a, b) (a < b ? a : b)

void vcop_median_filt_col_cn
(
    Int16 *input_ptr,		/* starting address of input */                           
    Int16 *output_ptr,		/* starting address of output */
    Int16 input_width,	    /* height of input array */
    Int16 input_height,     /* width of input array */
    Int16 output_width,    	/* height of output array */
    Int16 output_height,    /* width of output array */
    Int16 compute_width,   	/* height of compute block */
    Int16 compute_height,   /* width of compute block */
    Int16 median_size,		/* 3 or 5-tap median filter */
    Int16 input_type,		/* 0 - UBYTE, 1 - BYTE, 2 - USHORT, 3 - SHORT  */
    Int16 output_type		/* 0 - BYTE,  1 - SHORT */
)
{
   int i, j, k;
   int t_min, t_mid, t_max;
   int prev_min, prev_max, prev_mid;
   int prev_minus0, prev_minus1, prev_minus2, prev_minus3, prev_minus4;
   int tmp;
   int t_minus0, t_minus1, t_minus2, t_minus3, t_minus4;

   /*--------------------------------------------------------------------*/
   /* This is the code for computing col-wise median taking three pixels */
   /* at a time.                                                         */
   /*--------------------------------------------------------------------*/

   if (median_size == 3)
   {
       for ( i = 0; i < compute_width; i++)
       {

           prev_min = 0;
           prev_mid = 0;
           prev_max = 0;

           for ( j = 0; j < compute_height; j++)
           {
               for ( k = 0; k < median_size; k++)
               {
                   prev_max = input_ptr[( (j + k) * input_width) + i];

                   /*--------------------------------------------------------*/
                   /* First level of sorting.                                */
                   /*--------------------------------------------------------*/
                   
                   t_mid = MIN(prev_mid, prev_max);
                   t_max = MAX(prev_mid, prev_max);
                   
                   t_min = MIN(prev_min, t_mid);
                   t_mid = MAX(prev_min, t_mid);
                   
                   /*--------------------------------------------------------*/
                   /* Second level of sorting.                               */
                   /*--------------------------------------------------------*/
                   
                   t_mid      = MIN(t_max, t_mid);
                   
                   prev_min = prev_mid;
                   prev_mid = prev_max;
               }

               output_ptr[(j * output_width) + i] = t_mid;

           }
       }
   }

   /*--------------------------------------------------------------------*/
   /* This is the code for computing col-wise median taking five pixels  */
   /* at a time.                                                         */
   /*--------------------------------------------------------------------*/

   if (median_size == 5)
   {
       for ( i = 0; i < compute_width; i++)
       {

           prev_minus4 = 0;
           prev_minus3 = 0;
           prev_minus2 = 0;
           prev_minus1 = 0;

           for ( j = 0; j < compute_height; j++)
           {
               for ( k = 0; k < median_size; k++)
               {
                   
                   prev_minus0 = input_ptr[( (j + k) * input_width) + i];
             
                   /*--------------------------------------------------------*/
                   /* First level of sorting.                                */
                   /*--------------------------------------------------------*/

                   t_minus1 = MIN(prev_minus0, prev_minus1);
                   t_minus0 = MAX(prev_minus0, prev_minus1);
                  
                   t_minus2 = MIN(t_minus1, prev_minus2);
                   t_minus1 = MAX(t_minus1, prev_minus2);
                  
                   t_minus3 = MIN(t_minus2, prev_minus3);
                   t_minus2 = MAX(t_minus2, prev_minus3);
                  
                   t_minus4 = MIN(t_minus3, prev_minus4);
                   t_minus3 = MAX(t_minus3, prev_minus4);
                  
                   /*--------------------------------------------------------*/
                   /* Second level of sorting.                               */
                   /*--------------------------------------------------------*/
                  
                   tmp      = MIN(t_minus0, t_minus1);
                   t_minus0 = MAX(t_minus0, t_minus1);
                  
                   t_minus1 = tmp;
                  
                   tmp      = MIN(t_minus1, t_minus2);
                   t_minus1 = MAX(t_minus1, t_minus2);
                   
                   t_minus2 = tmp;
                  
                   tmp      = MIN(t_minus2, t_minus3);
                   t_minus2 = MAX(t_minus2, t_minus3);
                  
                   t_minus3 = tmp;
                  
                   /*--------------------------------------------------------*/
                   /* Third level of sorting.                                */
                   /*--------------------------------------------------------*/
                  
                   tmp      = MIN(t_minus0, t_minus1);
                   t_minus0 = MAX(t_minus0, t_minus1);
                  
                   t_minus1 = tmp;
                  
                   tmp      = MIN(t_minus1, t_minus2);
                   t_minus1 = MAX(t_minus1, t_minus2);
                  
                   t_minus2 = tmp;
            
                  
                   prev_minus4 = prev_minus3;
                   prev_minus3 = prev_minus2;
                   prev_minus2 = prev_minus1;
                   prev_minus1 = prev_minus0;

               }

                  
#ifdef __PRINT__

                   printf("IN: %d, %d, %d, %d\n", prev_minus4, prev_minus3, prev_minus2, prev_minus1);
#endif
       
#ifdef __PRINT__
               printf("    %d, %d, %d, %d, %d", t_minus4, t_minus3, t_minus2, t_minus1, t_minus0);
               printf(": %d\n\n", t_minus2);
#endif
               output_ptr[(j * output_width) + i] = t_minus2;
           }
       }
   }

   return;
}
