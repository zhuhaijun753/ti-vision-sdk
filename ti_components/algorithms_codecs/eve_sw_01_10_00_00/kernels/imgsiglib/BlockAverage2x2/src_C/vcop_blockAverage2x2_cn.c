/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME                                                                 */
/*         vcop_blockAverage2x2, average2x2 filter for the imgsig library.         */
/*                                                                          */
/*                                                                          */
/*     USAGE                                                                */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_average2x2_cn                                              */
/*     (                                                                    */
/*          signed char   *in,                                              */
/*          signed char   *out,                                        */
/*          int            in_w,                                         */
/*          int            out_w,                                          */
/*          int            compute_w,                                            */
/*          int            compute_h                                            */
/*     )                                                                    */
/*                                                                          */
/*                                                                          */
/*     *in        :  Pointer to an input array of "type_input".             */
/*     *out       :  Pointer to output array of "type_output".              */
/*     in_w    :  Width of the input image in pixels.                    */
/*    out_w     :  Width of the compute block in pixels.                  */
/*     compute_w      :  The block width for computing the average should be multiple of 2 or else results will be wrong             */
/*     compute_h      :  The compute height for computing average. should be multiple of 2 or else results will be wrong             */
/*                                                                          */
/*     Returns :  None or void.                                             */
/*                                                                          */
/*                                                                          */
/*     DESCRIPTION                                                          */
/*             This routine accepts pointers to a input region "in", and    */
/*     computes the average over a blocks of 2x2 pixels in the image.                   */
/*                                                                          */
/*                                                                          */
/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#include "../inc/vcop_blockAverage2x2_cn.h"

void vcop_blockAverage2x2_uchar_cn
(
    unsigned char  *in,
    unsigned char  *out,
    int            in_w,
    int            out_w,
    int            compute_w,
    int            compute_h
)
{

    int i, j;
    unsigned int temp;

    for ( i  = 0; i < compute_h/2; i++)
    {
        for ( j = 0; j < compute_w/2; j++ )
        {
            temp= in[(2*i * in_w) + 2*j] + in[(2*i * in_w) + 2*j + 1];
            temp += in[((2*i+1) * in_w) + 2*j] + in[((2*i+1) * in_w) + 2*j + 1];
            out[(i * out_w) + j] = (temp+2)>>2;
        }
    }

   return;
}

void vcop_blockAverage2x2_char_cn
(
    char  *in,
    char  *out,
    int            in_w,
    int            out_w,
    int            compute_w,
    int            compute_h
)
{

    int i, j;
    unsigned int temp;

    for ( i  = 0; i < compute_h/2; i++)
    {
        for ( j = 0; j < compute_w/2; j++ )
        {
            temp= in[(2*i * in_w) + 2*j] + in[(2*i * in_w) + 2*j + 1];
            temp += in[((2*i+1) * in_w) + 2*j] + in[((2*i+1) * in_w) + 2*j + 1];
            out[(i * out_w) + j] = (temp+2)>>2;
        }
    }

   return;
}

void vcop_blockAverage2x2_ushort_cn
(
    unsigned short  *in,
    unsigned short  *out,
    int            in_w,
    int            out_w,
    int            compute_w,
    int            compute_h
)
{

    int i, j;
    unsigned int temp;

    for ( i  = 0; i < compute_h/2; i++)
    {
        for ( j = 0; j < compute_w/2; j++ )
        {
            temp= in[(2*i * in_w) + 2*j] + in[(2*i * in_w) + 2*j + 1];
            temp += in[((2*i+1) * in_w) + 2*j] + in[((2*i+1) * in_w) + 2*j + 1];
            out[(i * out_w) + j] = (temp+2)>>2;
        }
    }

   return;
}


void vcop_blockAverage2x2_short_cn
(
    short  *in,
    short  *out,
    int            in_w,
    int            out_w,
    int            compute_w,
    int            compute_h
)
{

    int i, j;
    unsigned int temp;

    for ( i  = 0; i < compute_h/2; i++)
    {
        for ( j = 0; j < compute_w/2; j++ )
        {
            temp= in[(2*i * in_w) + 2*j] + in[(2*i * in_w) + 2*j + 1];
            temp += in[((2*i+1) * in_w) + 2*j] + in[((2*i+1) * in_w) + 2*j + 1];
            out[(i * out_w) + j] = (temp+2)>>2;
        }
    }

   return;
}
