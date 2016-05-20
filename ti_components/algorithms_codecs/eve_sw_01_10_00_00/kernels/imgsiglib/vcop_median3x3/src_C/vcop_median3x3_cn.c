/*==========================================================================*/
/*      Copyright (C) 2009-2012 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "vcop_median3x3_cn.h"

#define MAX(a, b) (a > b ? a : b)
#define MIN(a, b) (a < b ? a : b)

void vcop_median3x3_uchar_cn
(
    unsigned char *in,
    unsigned char *out,
    unsigned char *scratch1,
    unsigned char *scratch2,
    int w_input,
    int w_out,
    int w_compute,
    int h_compute
)
{
    int i, j, m, n, k;
    int c2l, c2m, c2h;
    int in0, in1;
    int tmp;
    int min_of_max, max_of_min;
    int min_in, max_in, med_in, med_max, med_max_nxt;
    int min, med, max;

    int scratch_w = w_compute + 0;

    /*-----------------------------------------------------------------------*/
    /* Initialize the output to zeros at the beginning.                      */
    /*-----------------------------------------------------------------------*/

    for ( i = 0; i < (int) h_compute * 3; i++) // lpend3
    {
        for (j = 0; j < scratch_w; j++ ) //lpend4
        {
            scratch1[( i * scratch_w) + j ] = 0;
        }
    }


    for ( i = 0; i < w_compute; i++ )
        for ( j = 0; j < h_compute; j++ )
            out[j * w_compute + i ] = 0;

    /*-----------------------------------------------------------------------*/
    /* This is the first loop where sets of three consecutive rows are       */
    /* re ordered as min, med and max rows. Thus, the output of this loop    */
    /* has a height of 3x that of the input array.                           */
    /*-----------------------------------------------------------------------*/

    for ( j = 0; j < (int) w_compute; j++) // lpend3
    {
        /*-------------------------------------------------------------------*/
        /* Initialize the columns to get started.                            */
        /*-------------------------------------------------------------------*/

        c2l = c2m = c2h = 0;
        in0 = in1 = 0;

        m = 0;
        for (i = 0; i < (int) h_compute; i++ ) //lpend4
        {
            /*-----------------------------------------------------------*/
            /* Read in the latest column.                                */
            /*-----------------------------------------------------------*/

            c2l = in0;
            c2m = in1;
            c2h = in[( ( i + 0 ) * (w_input + 0) ) + j ];
#ifdef __PRINT__
            printf("column values read in are:\n %x, %x, %x\n", c2l, c2m, c2h);
#endif

            /*-----------------------------------------------------------*/
            /* Sort the latest column into low, middle and high values.  */
            /*-----------------------------------------------------------*/

            in0 = c2m;
            in1 = c2h;

            if ( c2l > c2h ) {  tmp = c2l;  c2l = c2h;  c2h = tmp;  }
            if ( c2l > c2m ) {  tmp = c2l;  c2l = c2m;  c2m = tmp;  }
            if ( c2m > c2h ) {  tmp = c2m;  c2m = c2h;  c2h = tmp;  }

            /*-----------------------------------------------------------*/
            /* Write the values out.                                     */
            /*-----------------------------------------------------------*/

            m = (i * 3);

            scratch1[(  (m + 0)  * scratch_w) + j] = c2l;
            scratch1[(  (m + 1)  * scratch_w) + j] = c2m;
            scratch1[(  (m + 2)  * scratch_w) + j] = c2h;

        }
    }

    /*-----------------------------------------------------------------------*/
    /* This is the second loop where the max_of_min, min_of_max and          */
    /* med_of_med values are evaluated in the horizontal direction taking    */
    /* three consecutive values at a time and moving the pointer by one each */
    /* time in the horizontal direction.                                     */
    /*-----------------------------------------------------------------------*/

    for ( i = 0; i < (int) (h_compute * 3); i+=3) // lpend3
    {
        for (j = 0; j < (int) scratch_w; j++ ) //lpend4
        {
            med_max      =   0;
            med_max_nxt  =   0;
            min_of_max   = 255;
            max_of_min   =   0;

            for ( k = 0; k < 3; k++)
            {
                /*----------------------------------------------------------*/
                /* Read in the latest column and copy previous values as    */
                /* current values.                                          */
                /*----------------------------------------------------------*/

                min_in =   scratch1[( ( i + 6 + 0 ) * scratch_w) + j + k];
                med_in =   scratch1[( ( i + 6 + 1 ) * scratch_w) + j + k];
                max_in =   scratch1[( ( i + 6 + 2 ) * scratch_w) + j + k];

                /*-----------------------------------------------------------*/
                /* Obtain the min_of_max, max_of_min and median of median    */
                /* values, taking three at a time.                           */
                /*-----------------------------------------------------------*/

                max_of_min = MAX(max_of_min, min_in);
                min_of_max = MIN(min_of_max, max_in);


                if (med_in > med_max) { tmp = med_max; med_max = med_in; med_in = tmp; }
                if (med_in > med_max_nxt) { tmp = med_max_nxt; med_max_nxt = med_in; med_in = tmp; }

            }

            /*-----------------------------------------------------------*/
            /* Write the values out.                                     */
            /*-----------------------------------------------------------*/

            scratch2[( (i + 0)  * scratch_w) + j] = max_of_min;
            scratch2[( (i + 1)  * scratch_w) + j] = med_max_nxt;
            scratch2[( (i + 2)  * scratch_w) + j] = min_of_max;
        }
    }

    /*-----------------------------------------------------------------------*/
    /* This is the third loop where the true median is computed from the     */
    /* previous result by taking the max_of_min, med_of_med and min_of_max   */
    /* values in the vertical order. The resultant array has the same height */
    /* as that of the input.                                                 */
    /*-----------------------------------------------------------------------*/

    n = 0;
    for ( i = 0; i < (int) h_compute * 3; i+=3) // lpend1
    {
        for (j = 0; j < (int) w_compute; j++) //lpend2
        {
                /*----------------------------------------------------------*/
                /* Read in the latest column.                               */
                /*----------------------------------------------------------*/

                min =   scratch2[( ( i + 0 ) * scratch_w) + j];
                med =   scratch2[( ( i + 1 ) * scratch_w) + j];
                max =   scratch2[( ( i + 2 ) * scratch_w) + j];

                /*-----------------------------------------------------------*/
                /* Sort the latest column into low, middle and high values.  */
                /*-----------------------------------------------------------*/

                if ( min > max ) {  tmp = min;  min = max;  max = tmp;  }
                if ( min > med ) {  tmp = min;  min = med;  med = tmp;  }
                if ( med > max ) {  tmp = med;  med = max;  max = tmp;  }

                /*-----------------------------------------------------------*/
                /* Write the values out.                                     */
                /*-----------------------------------------------------------*/

                n = (int) (i/3);
                out[( n * w_compute) + j] = med;
        }
    }

   return;
}

void vcop_median3x3_char_cn
(
    signed char *in,
    signed char *out,
    signed char *scratch1,
    signed char *scratch2,
    int w_input,
    int w_out,
    int w_compute,
    int h_compute
)
{
    int i, j, m, n, k;
    int c2l, c2m, c2h;
    int in0, in1;
    int tmp;
    int min_of_max, max_of_min;
    int min_in, max_in, med_in, med_max, med_max_nxt;
    int min, med, max;

    int scratch_w = w_compute + 0;

    /*-----------------------------------------------------------------------*/
    /* Initialize the output to zeros at the beginning.                      */
    /*-----------------------------------------------------------------------*/

    for ( i = 0; i < (int) h_compute * 3; i++) // lpend3
    {
        for (j = 0; j < scratch_w; j++ ) //lpend4
        {
            scratch1[( i * scratch_w) + j ] = 0;
        }
    }


    for ( i = 0; i < w_compute; i++ )
        for ( j = 0; j < h_compute; j++ )
            out[j * w_compute + i ] = 0;

    /*-----------------------------------------------------------------------*/
    /* This is the first loop where sets of three consecutive rows are       */
    /* re ordered as min, med and max rows. Thus, the output of this loop    */
    /* has a height of 3x that of the input array.                           */
    /*-----------------------------------------------------------------------*/

    for ( j = 0; j < (int) w_compute; j++) // lpend3
    {

        /*-------------------------------------------------------------------*/
        /* Initialize the columns to get started.                            */
        /*-------------------------------------------------------------------*/

        c2l = c2m = c2h = 0;
        in0 = in1 = 0;

        m = 0;
        for (i = 0; i < (int) h_compute; i++ ) //lpend4
        {
                /*-----------------------------------------------------------*/
                /* Read in the latest column.                                */
                /*-----------------------------------------------------------*/

                c2l = in0;
                c2m = in1;
                c2h = in[( i * w_input ) + j ];
#ifdef __PRINT__
                printf("column values read in are:\n %x, %x, %x\n", c2l, c2m, c2h);
#endif

                /*-----------------------------------------------------------*/
                /* Sort the latest column into low, middle and high values.  */
                /*-----------------------------------------------------------*/

                in0 = c2m;
                in1 = c2h;

                if ( c2l > c2h ) {  tmp = c2l;  c2l = c2h;  c2h = tmp;  }
                if ( c2l > c2m ) {  tmp = c2l;  c2l = c2m;  c2m = tmp;  }
                if ( c2m > c2h ) {  tmp = c2m;  c2m = c2h;  c2h = tmp;  }

                /*-----------------------------------------------------------*/
                /* Write the values out.                                     */
                /*-----------------------------------------------------------*/

                m = (i * 3);

                scratch1[(  (m + 0)  * scratch_w) + j] = c2l;
                scratch1[(  (m + 1)  * scratch_w) + j] = c2m;
                scratch1[(  (m + 2)  * scratch_w) + j] = c2h;

        }
    }

    /*-----------------------------------------------------------------------*/
    /* This is the second loop where the max_of_min, min_of_max and          */
    /* med_of_med values are evaluated in the horizontal direction taking    */
    /* three consecutive values at a time and moving the pointer by one each */
    /* time in the horizontal direction.                                     */
    /*-----------------------------------------------------------------------*/

    for ( i = 0; i < (int) (h_compute * 3); i+=3) // lpend3
    {
        for (j = 0; j < (int) scratch_w; j++ ) //lpend4
        {
            med_max     = -128;
            med_max_nxt = -128;
            min_of_max  =  127;
            max_of_min  = -128;

            for ( k = 0; k < 3; k++)
            {

                /*----------------------------------------------------------*/
                /* Read in the latest column and copy previous values as    */
                /* current values.                                          */
                /*----------------------------------------------------------*/

                min_in =   scratch1[( ( i + 6 + 0 ) * scratch_w) + j + k];
                med_in =   scratch1[( ( i + 6 + 1 ) * scratch_w) + j + k];
                max_in =   scratch1[( ( i + 6 + 2 ) * scratch_w) + j + k];

                /*-----------------------------------------------------------*/
                /* Obtain the min_of_max, max_of_min and median of median    */
                /* values, taking three at a time.                           */
                /*-----------------------------------------------------------*/

                max_of_min = MAX(max_of_min, min_in);
                min_of_max = MIN(min_of_max, max_in);


                if (med_in > med_max) { tmp = med_max; med_max = med_in; med_in = tmp; }
                if (med_in > med_max_nxt) { tmp = med_max_nxt; med_max_nxt = med_in; med_in = tmp; }

            }

                /*-----------------------------------------------------------*/
                /* Write the values out.                                     */
                /*-----------------------------------------------------------*/

                scratch2[( (i + 0)  * scratch_w) + j] = max_of_min;
                scratch2[( (i + 1)  * scratch_w) + j] = med_max_nxt;
                scratch2[( (i + 2)  * scratch_w) + j] = min_of_max;
        }
    }

    /*-----------------------------------------------------------------------*/
    /* This is the third loop where the true median is computed from the     */
    /* previous result by taking the max_of_min, med_of_med and min_of_max   */
    /* values in the vertical order. The resultant array has the same height */
    /* as that of the input.                                                 */
    /*-----------------------------------------------------------------------*/

    n = 0;
    for ( i = 0; i < (int) h_compute * 3; i+=3) // lpend1
    {
        for (j = 0; j < (int) w_compute; j++) //lpend2
        {
                /*----------------------------------------------------------*/
                /* Read in the latest column.                               */
                /*----------------------------------------------------------*/

                min =   scratch2[( ( i + 0 ) * scratch_w) + j];
                med =   scratch2[( ( i + 1 ) * scratch_w) + j];
                max =   scratch2[( ( i + 2 ) * scratch_w) + j];

                /*-----------------------------------------------------------*/
                /* Sort the latest column into low, middle and high values.  */
                /*-----------------------------------------------------------*/

                if ( min > max ) {  tmp = min;  min = max;  max = tmp;  }
                if ( min > med ) {  tmp = min;  min = med;  med = tmp;  }
                if ( med > max ) {  tmp = med;  med = max;  max = tmp;  }

                /*-----------------------------------------------------------*/
                /* Write the values out.                                     */
                /*-----------------------------------------------------------*/

                n = (int) (i/3);
                out[( n * w_compute) + j] = med;
        }
    }

   return;
}
