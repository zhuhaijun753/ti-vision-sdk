/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME                                                                 */
/*         vcop_median3x3, kernel filter computing median over a block of   */
/*     size w_blk X h_blk in internal EVE memory, the output of this        */
/*     compute is of size (w_blk - 2) X (h_blk - 2) and also goes to        */
/*     internal memory.                                                     */
/*                                                                          */
/*     USAGE                                                                */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_median3x3_char                                             */
/*     (                                                                    */
/*         __vptr_int8   *in,                                               */
/*         __vptr_int8   *out,                                              */
/*         __vptr_int8   *scratch1,                                         */
/*         __vptr_int8   *scratch2,                                         */
/*         int           w_blk,                                             */
/*         int           h_blk                                              */
/*     )                                                                    */
/*                                                                          */
/*     *in              :  Pointer to an input array of char.               */
/*     *out             :  Pointer to output array of char.                 */
/*     *scratch1        :  Pointer to intermediate array.                   */
/*     *scratch2        :  Pointer to intermediate array.                   */
/*     w_blk            :  The block width over which median is computed.   */
/*     h_blk            :  The compute height for median filter.            */
/*                                                                          */
/*     Returns :  None or void.                                             */
/*                                                                          */
/*                                                                          */
/*     DESCRIPTION                                                          */
/*             This routine accepts pointers to a input region "in", and    */
/*     computes the median over 3x3 pixels of a block of size w_blk X h_blk */
/*     in internal memory.                                                  */
/*                                                                          */
/*     ASSUMPTIONS                                                          */
/*                                                                          */
/*     1) Intermediate scratch buffers are also used which have sizes of    */
/*     (3 * w_blk * h_blk ).                                                */
/*                                                                          */
/*     2) w_blk should be a multiple of 16 as deinterleaved loads are used. */
/*                                                                          */
/*     3) Output block "out" has a size of (w_blk - 2) X (h_blk - 2)        */
/*                                                                          */
/*    PERFORMANCE/CODESIZE                                                  */
/*    cycles = 18/16 cyc/pix                                                */
/*    codesize = 204 bytes                                                  */
/*                                                                          */
/*==========================================================================*/
/*      Copyright (C) 2009-2012 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#if VCOP_HOST_EMULATION
#include <vcop.h>
#endif

#define ELEMSZ_IN        sizeof(*in)
#define VECTORSZ_IN      (VCOP_SIMD_WIDTH * ELEMSZ_IN)

#define ELEMSZ_OUT       sizeof(*out)
#define VECTORSZ_OUT     (VCOP_SIMD_WIDTH * ELEMSZ_OUT)

#define VCOP_2SIMD_WIDTH (VCOP_SIMD_WIDTH * 2)


/*-------------------------------------------------------------------------*/
/* Median with char type input.                                            */
/*-------------------------------------------------------------------------*/
void vcop_median3x3_char
(
    __vptr_int8     in,
    __vptr_int8     out,
    __vptr_int8     scratch1,
    __vptr_int8     scratch2,
    unsigned short  w_blk,
    unsigned short  h_blk
)
{
    /*-----------------------------------------------------------------------*/
    /* This is the first loop where sets of three consecutive rows are       */
    /* re ordered as min, med and max rows. Thus, the output of this loop    */
    /* has a height of 3x that of the input array.                           */
    /*-----------------------------------------------------------------------*/
    for (int I1 = 0; I1 < (w_blk)/VCOP_2SIMD_WIDTH; I1++)
    {
        __vector c2l_0, c2m_0, c2h_0;
        __vector c2l_1, c2m_1, c2h_1;

        /*-------------------------------------------------------------------*/
        /* Initialize the columns to get started.                            */
        /*-------------------------------------------------------------------*/
        c2l_0 = 0;
        c2m_0 = 0;
        c2h_0 = 0;
        c2l_1 = 0;
        c2m_1 = 0;
        c2h_1 = 0;

        for (int I2 = 0; I2 <  h_blk - 2; I2++)
        {
            __agen dataAddr0;
            __agen dataAddr1;

            dataAddr0 =  (I2 * w_blk * ELEMSZ_IN ) + (I1 * 2 * VECTORSZ_IN );
            dataAddr1 =  (I2 * 3 * w_blk * ELEMSZ_IN ) + (I1 * 2 * VECTORSZ_IN );

            /*-----------------------------------------------------------*/
            /* Read in the latest column.                                */
            /*-----------------------------------------------------------*/
            (c2l_0, c2l_1) = (in + (0 * w_blk * ELEMSZ_IN))[dataAddr0].deinterleave();
            (c2m_0, c2m_1) = (in + (1 * w_blk * ELEMSZ_IN))[dataAddr0].deinterleave();
            (c2h_0, c2h_1) = (in + (2 * w_blk * ELEMSZ_IN))[dataAddr0].deinterleave();

            /*-----------------------------------------------------------*/
            /* Sort the latest column into low, middle and high values.  */
            /* if ( c2l > c2h ) {  tmp = c2l;  c2l = c2h;  c2h = tmp; }  */
            /* if ( c2l > c2m ) {  tmp = c2l;  c2l = c2m;  c2m = tmp; }  */
            /* if ( c2m > c2h ) {  tmp = c2m;  c2m = c2h;  c2h = tmp; }  */
            /*-----------------------------------------------------------*/
            (c2l_0, c2h_0).minmax();
            (c2l_0, c2m_0).minmax();
            (c2m_0, c2h_0).minmax();

            (c2l_1, c2h_1).minmax();
            (c2l_1, c2m_1).minmax();
            (c2m_1, c2h_1).minmax();

            /*-----------------------------------------------------------*/
            /* Write the values out.                                     */
            /*-----------------------------------------------------------*/
            (scratch1 + (0 * w_blk * ELEMSZ_IN))[dataAddr1].interleave() = (c2l_0, c2l_1);
            (scratch1 + (1 * w_blk * ELEMSZ_IN))[dataAddr1].interleave() = (c2m_0, c2m_1);
            (scratch1 + (2 * w_blk * ELEMSZ_IN))[dataAddr1].interleave() = (c2h_0, c2h_1);
        }
    }


    /*-----------------------------------------------------------------------*/
    /* This is the second loop where the max_of_min, min_of_max and          */
    /* med_of_med values are evaluated in the horizontal direction taking    */
    /* three consecutive values at a time and moving the pointer by one each */
    /* time in the horizontal direction.                                     */
    /*-----------------------------------------------------------------------*/

    /*----------------------------------------------------------------------*/
    /* This loops over the height of the image block.                       */
    /*----------------------------------------------------------------------*/
    for (int I1 = 0; I1 < h_blk - 2; I1++)
    {
        /*----------------------------------------------------------------------*/
        /* This loops over the width of the image block, considering three      */
        /* pixels at a time.                                                    */
        /*----------------------------------------------------------------------*/
        for (int I2 = 0; I2 < w_blk/VCOP_2SIMD_WIDTH; I2++)
        {
            __vector min_of_max0, max_of_min0;
            __vector med_in0, min_in0, max_in0;
            __vector med_max0, med_max_nxt0;

            __vector min_of_max1, max_of_min1;
            __vector med_in1, min_in1, max_in1;
            __vector med_max1, med_max_nxt1;

            __agen dataAddr1;

            dataAddr1  = (I2 * 2 * VECTORSZ_IN) + ( (I1 * 3) * w_blk * ELEMSZ_IN);

            med_max0     = -128;
            med_max_nxt0 = -128;
            min_of_max0  =  127;
            max_of_min0  = -128;

            med_max1     = -128;
            med_max_nxt1 = -128;
            min_of_max1  =  127;
            max_of_min1  = -128;

           /*-----------------------------------------------------------------*/
           /* This loops considers three pixels horizontally at a time and    */
           /* obtains the min_of_max, med_of_med and max_of_min values.       */
           /*-----------------------------------------------------------------*/
            for (int I3 = 0; I3 < 3; I3++)
            {
                __agen dataAddr0;

                dataAddr0  = (I3 * ELEMSZ_IN) + (I2 * 2 * VECTORSZ_IN) + ((I1 * 3) * w_blk * ELEMSZ_IN);

                /*----------------------------------------------------------*/
                /* Read in the latest column and copy previous values as    */
                /* current values.                                          */
                /*----------------------------------------------------------*/
                (min_in0, min_in1) = (scratch1 + (0 * w_blk * ELEMSZ_IN))[dataAddr0].deinterleave();
                (med_in0, med_in1) = (scratch1 + (1 * w_blk * ELEMSZ_IN))[dataAddr0].deinterleave();
                (max_in0, max_in1) = (scratch1 + (2 * w_blk * ELEMSZ_IN))[dataAddr0].deinterleave();

                /*-----------------------------------------------------------*/
                /* Obtain the min_of_max, max_of_min and median of median    */
                /* values, using insertion sort method.                      */
                /*-----------------------------------------------------------*/
                max_of_min0 = max(max_of_min0, min_in0);
                min_of_max0 = min(min_of_max0, max_in0);

                max_of_min1 = max(max_of_min1, min_in1);
                min_of_max1 = min(min_of_max1, max_in1);

                (med_in0, med_max0).minmax();
                (med_in0, med_max_nxt0).minmax();

                (med_in1, med_max1).minmax();
                (med_in1, med_max_nxt1).minmax();
           }

           /*---------------------------------------------------------------*/
           /* Write the values out.                                         */
           /*---------------------------------------------------------------*/
           (scratch2 + (0 * w_blk * ELEMSZ_IN))[dataAddr1].interleave() = (max_of_min0,  max_of_min1);
           (scratch2 + (1 * w_blk * ELEMSZ_IN))[dataAddr1].interleave() = (med_max_nxt0, med_max_nxt1);
           (scratch2 + (2 * w_blk * ELEMSZ_IN))[dataAddr1].interleave() = (min_of_max0,  min_of_max1);
        }
    }

    /*-----------------------------------------------------------------------*/
    /* This is the third loop where the true median is computed from the     */
    /* three results of the previous loop -max_of_min, med_of_med and        */
    /* min_of_max values, taken in the vertical order.                       */
    /*-----------------------------------------------------------------------*/
    for ( int I1 = 0; I1 < h_blk - 2; I1++)
    {
        for (int I2 = 0; I2 < w_blk/VCOP_2SIMD_WIDTH; I2++)
        {
            __vector min_out0, med_out0, max_out0;
            __vector min_out1, med_out1, max_out1;

            __agen dataAddr0;
            __agen dataAddr1;

            dataAddr0 = I2 * VCOP_2SIMD_WIDTH * ELEMSZ_IN  + I1 * 3 * w_blk * ELEMSZ_IN;
            dataAddr1 = I2 * VCOP_2SIMD_WIDTH * ELEMSZ_OUT + I1 * (w_blk - 2) * ELEMSZ_OUT;

            /*----------------------------------------------------------*/
            /* Read in the latest column.                               */
            /*----------------------------------------------------------*/
            (min_out0, min_out1) = (scratch2 + (0 * w_blk * ELEMSZ_IN))[dataAddr0].deinterleave();
            (med_out0, med_out1) = (scratch2 + (1 * w_blk * ELEMSZ_IN))[dataAddr0].deinterleave();
            (max_out0, max_out1) = (scratch2 + (2 * w_blk * ELEMSZ_IN))[dataAddr0].deinterleave();

            /*-----------------------------------------------------------*/
            /* Sort the latest column into low, middle and high values.  */
            /*-----------------------------------------------------------*/
            (min_out0, max_out0).minmax();
            (min_out0, med_out0).minmax();
            (med_out0, max_out0).minmax();

            (min_out1, max_out1).minmax();
            (min_out1, med_out1).minmax();
            (med_out1, max_out1).minmax();

            /*-----------------------------------------------------------*/
            /* Write the values out.                                     */
            /*-----------------------------------------------------------*/
            out[dataAddr1].interleave() =  (med_out0, med_out1);
        }
    }
}


/*-------------------------------------------------------------------------*/
/* Median with unsigned char type input.                                   */
/*-------------------------------------------------------------------------*/\
void vcop_median3x3_uchar
(
    __vptr_uint8    in,
    __vptr_uint8    out,
    __vptr_uint8    scratch1,
    __vptr_uint8    scratch2,
    unsigned short  w_blk,
    unsigned short  h_blk
)
{

    /*-----------------------------------------------------------------------*/
    /* This is the first loop where sets of three consecutive rows are       */
    /* re ordered as min, med and max rows. Thus, the output of this loop    */
    /* has a height of 3x that of the input array.                           */
    /*-----------------------------------------------------------------------*/
    for (int I1 = 0; I1 < w_blk/VCOP_2SIMD_WIDTH; I1++)
    {
        __vector c2l_0, c2m_0, c2h_0;
        __vector c2l_1, c2m_1, c2h_1;

        /*-------------------------------------------------------------------*/
        /* Initialize the columns to get started.                            */
        /*-------------------------------------------------------------------*/
        c2l_0 = 0;
        c2m_0 = 0;
        c2h_0 = 0;
        c2l_1 = 0;
        c2m_1 = 0;
        c2h_1 = 0;

        for (int I2 = 0; I2 <  h_blk - 2; I2++)
        {
               __agen dataAddr0;
               __agen dataAddr1;

                dataAddr0 =  (I2 * w_blk * ELEMSZ_IN ) + (I1 * 2 * VECTORSZ_IN );
                dataAddr1 =  (I2 * 3 * w_blk * ELEMSZ_IN ) + (I1 * 2 * VECTORSZ_IN );

                /*-----------------------------------------------------------*/
                /* Read in the latest column.                                */
                /*-----------------------------------------------------------*/
                (c2l_0, c2l_1) = (in + (0 * w_blk * ELEMSZ_IN))[dataAddr0].deinterleave();
                (c2m_0, c2m_1) = (in + (1 * w_blk * ELEMSZ_IN))[dataAddr0].deinterleave();
                (c2h_0, c2h_1) = (in + (2 * w_blk * ELEMSZ_IN))[dataAddr0].deinterleave();

                /*-----------------------------------------------------------*/
                /* Sort the latest column into low, middle and high values.  */
                /* if ( c2l > c2h ) {  tmp = c2l;  c2l = c2h;  c2h = tmp; }  */
                /* if ( c2l > c2m ) {  tmp = c2l;  c2l = c2m;  c2m = tmp; }  */
                /* if ( c2m > c2h ) {  tmp = c2m;  c2m = c2h;  c2h = tmp; }  */
                /*-----------------------------------------------------------*/
                (c2l_0, c2h_0).minmax();
                (c2l_0, c2m_0).minmax();
                (c2m_0, c2h_0).minmax();

                (c2l_1, c2h_1).minmax();
                (c2l_1, c2m_1).minmax();
                (c2m_1, c2h_1).minmax();

                /*-----------------------------------------------------------*/
                /* Write the values out.                                     */
                /*-----------------------------------------------------------*/
                (scratch1 + (0 * w_blk * ELEMSZ_IN))[dataAddr1].interleave() = (c2l_0, c2l_1);
                (scratch1 + (1 * w_blk * ELEMSZ_IN))[dataAddr1].interleave() = (c2m_0, c2m_1);
                (scratch1 + (2 * w_blk * ELEMSZ_IN))[dataAddr1].interleave() = (c2h_0, c2h_1);
        }
    }


    /*-----------------------------------------------------------------------*/
    /* This is the second loop where the max_of_min, min_of_max and          */
    /* med_of_med values are evaluated in the horizontal direction taking    */
    /* three consecutive values at a time and moving the pointer by one each */
    /* time in the horizontal direction.                                     */
    /*-----------------------------------------------------------------------*/

    /*----------------------------------------------------------------------*/
    /* This loops over the height of the image block.                       */
    /*----------------------------------------------------------------------*/
    for ( int I1 = 0; I1 < h_blk - 2; I1++)
    {
        /*----------------------------------------------------------------------*/
        /* This loops over the width of the image block, considering three      */
        /* pixels at a time.                                                    */
        /*----------------------------------------------------------------------*/
        for (int I2 = 0; I2 < w_blk/VCOP_2SIMD_WIDTH; I2++ )
        {
            __vector min_of_max0, max_of_min0;
            __vector med_in0, min_in0, max_in0;
            __vector med_max0, med_max_nxt0;

            __vector min_of_max1, max_of_min1;
            __vector med_in1, min_in1, max_in1;
            __vector med_max1, med_max_nxt1;

            __agen dataAddr1;

            dataAddr1  = (I2 * 2 * VECTORSZ_IN) + ( (I1 * 3) * w_blk * ELEMSZ_IN);

            med_max0     = 0x0;
            med_max_nxt0 = 0x0;
            min_of_max0  = 255;
            max_of_min0  = 0x0;

            med_max1     = 0x0;
            med_max_nxt1 = 0x0;
            min_of_max1  = 255;
            max_of_min1  = 0x0;

            /*-----------------------------------------------------------------*/
            /* This loops considers three pixels horizontally at a time and    */
            /* obtains the min_of_max, med_of_med and max_of_min values.       */
            /*-----------------------------------------------------------------*/
            for ( int I3 = 0; I3 < 3; I3++ )
            {
                __agen dataAddr0;

                dataAddr0  = (I3 * ELEMSZ_IN) + (I2 * 2 * VECTORSZ_IN) + ((I1 * 3) *  w_blk  * ELEMSZ_IN);

                /*----------------------------------------------------------*/
                /* Read in the latest column and copy previous values as    */
                /* current values.                                          */
                /*----------------------------------------------------------*/
                (min_in0, min_in1) = (scratch1 + (0 * w_blk * ELEMSZ_IN))[dataAddr0].deinterleave();
                (med_in0, med_in1) = (scratch1 + (1 * w_blk * ELEMSZ_IN))[dataAddr0].deinterleave();
                (max_in0, max_in1) = (scratch1 + (2 * w_blk * ELEMSZ_IN))[dataAddr0].deinterleave();

                /*-----------------------------------------------------------*/
                /* Obtain the min_of_max, max_of_min and median of median    */
                /* values, using insertion sort method.                      */
                /*-----------------------------------------------------------*/
                max_of_min0 = max(max_of_min0, min_in0);
                min_of_max0 = min(min_of_max0, max_in0);

                max_of_min1 = max(max_of_min1, min_in1);
                min_of_max1 = min(min_of_max1, max_in1);

                (med_in0, med_max0).minmax();
                (med_in0, med_max_nxt0).minmax();

                (med_in1, med_max1).minmax();
                (med_in1, med_max_nxt1).minmax();
            }

            /*-----------------------------------------------------------*/
            /* Write the values out.                                     */
            /*-----------------------------------------------------------*/
            (scratch2 + ((0  * w_blk) * ELEMSZ_IN))[dataAddr1].interleave() = (max_of_min0,  max_of_min1);
            (scratch2 + ((1  * w_blk) * ELEMSZ_IN))[dataAddr1].interleave() = (med_max_nxt0, med_max_nxt1);
            (scratch2 + ((2  * w_blk) * ELEMSZ_IN))[dataAddr1].interleave() = (min_of_max0,  min_of_max1);
        }
    }

    /*-----------------------------------------------------------------------*/
    /* This is the third loop where the true median is computed from the     */
    /* three results of the previous loop -max_of_min, med_of_med and        */
    /* min_of_max values, taken in the vertical order.                       */
    /*-----------------------------------------------------------------------*/

    for ( int I1 = 0; I1 < h_blk - 2; I1++)
    {
        for (int I2 = 0; I2 < w_blk/VCOP_2SIMD_WIDTH; I2++)
        {
            __vector min_out0, med_out0, max_out0;
            __vector min_out1, med_out1, max_out1;

            __agen dataAddr0;
            __agen dataAddr1;

            dataAddr0 = I2 * VCOP_2SIMD_WIDTH * ELEMSZ_IN  + I1 * 3 * w_blk * ELEMSZ_IN;
            dataAddr1 = I2 * VCOP_2SIMD_WIDTH * ELEMSZ_OUT + I1 * (w_blk - 2) * ELEMSZ_OUT;

            /*----------------------------------------------------------*/
            /* Read in the latest column.                               */
            /*----------------------------------------------------------*/
            (min_out0, min_out1) = (scratch2 + (0  * w_blk * ELEMSZ_IN))[dataAddr0].deinterleave();
            (med_out0, med_out1) = (scratch2 + (1  * w_blk * ELEMSZ_IN))[dataAddr0].deinterleave();
            (max_out0, max_out1) = (scratch2 + (2  * w_blk * ELEMSZ_IN))[dataAddr0].deinterleave();

            /*-----------------------------------------------------------*/
            /* Sort the latest column into low, middle and high values.  */
            /*-----------------------------------------------------------*/
            (min_out0, max_out0).minmax();
            (min_out0, med_out0).minmax();
            (med_out0, max_out0).minmax();

            (min_out1, max_out1).minmax();
            (min_out1, med_out1).minmax();
            (med_out1, max_out1).minmax();

            /*-----------------------------------------------------------*/
            /* Write the values out.                                     */
            /*-----------------------------------------------------------*/
            out[dataAddr1].interleave() =  (med_out0, med_out1);
        }
    }
}

