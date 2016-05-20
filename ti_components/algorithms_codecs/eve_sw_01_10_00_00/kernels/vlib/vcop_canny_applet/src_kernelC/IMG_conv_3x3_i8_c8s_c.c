/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  IMGLIB-2  DSP Image/Video Processing Library                            */
/*                                                                          */
/*      Release:        Revision 2.0.1                                      */
/*      Snapshot date:  6-May-2008                                          */
/*                                                                          */
/*  This library contains proprietary intellectual property of Texas        */
/*  Instruments, Inc.  The library and its source code are protected by     */
/*  various copyrights, and portions may also be protected by patents or    */
/*  other legal protections.                                                */
/*                                                                          */
/*  This software is licensed for use with Texas Instruments TMS320         */
/*  family DSPs.  This license was provided to you prior to installing      */
/*  the software.  You may review this license by consulting the file       */
/*  TI_license.PDF which accompanies the files in this library.             */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2008 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  NAME                                                                    */
/*      IMG_conv_3x3_i8_c8s    -- 3x3 convolution                           */
/*   USAGE                                                                  */
/*      This routine has the following C prototype:                         */
/*                                                                          */
/*      void IMG_conv_3x3_i8_c8s(const unsigned char *restrict inptr,       */
/*                                 unsigned char *restrict outptr,          */
/*                                          int            x_dim,           */
/*                           const          char *restrict mask,            */
/*                                          int            shift)           */
/*                                                                          */
/*     The convolution routine accepts three rows of 'x_dim' input points   */
/*     and performs some operation on each.  A total of 'x_dim' outputs     */
/*     are written to the output array. The 'mask' array has the 3 by 3     */
/*     array of coefficients.                                               */
/*                                                                          */
/*                                                                          */
/*  DESCRIPTION                                                             */
/*                                                                          */
/*     The convolution kernel accepts three rows of 'x_dim' input points    */
/*     and produces one output row of 'x_dim' points using the input mask   */
/*     of 3 by 3. The user defined shift value is used to shift the convo-  */
/*     lution value, down to the byte range. The convolution sum is also    */
/*     range limited to 0..255. The shift amount is non-zero for low pass   */
/*     filters, and zero for high pass and sharpening filters.              */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2008 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

//#include "host_build.h"

//#pragma CODE_SECTION(IMG_conv_3x3_i8_c8s_cn, ".text:ansi");

//#include "IMG_conv_3x3_i8_c8s_c.h"

/* ======================================================================== */
/*  IMG_conv_3x3_i8_c8s_cn   -- Natural C version of conv_3x3_i8_c8s().     */
/* ======================================================================== */

void IMG_conv_3x3_i8_c8s(const unsigned char *restrict inptr,
                                  unsigned char *restrict outptr,
                                  int                     x_dim,
                                  const char    *restrict mask,
                                  int                     shift)
{
     const unsigned char     *IN1,*IN2,*IN3;
     unsigned char           *OUT;

     short    pix10,  pix20,  pix30;
     short    mask10, mask20, mask30;

     int      sum,    sum00,  sum11;
     int      i;
     int      sum22,  j;

     /*-------------------------------------------------------------------*/
     /* Set imgcols to the width of the image and set three pointers for  */
     /* reading data from the three input rows. Alos set the output poin- */
     /* ter.                                                              */
     /*-------------------------------------------------------------------*/

     IN1      =   inptr;
     IN2      =   IN1 + x_dim;
     IN3      =   IN2 + x_dim;
     OUT      =   outptr;

     /*-------------------------------------------------------------------*/
     /* The j: loop iterates to produce one output pixel per iteration.   */
     /* The mask values and the input values are read using the i loop.   */
     /* The convolution sum is then computed. The convolution sum is      */
     /* then shifted and range limited to 0..255                          */
     /*-------------------------------------------------------------------*/

     for (j = 0; j < x_dim ; j++)
     {
         /*---------------------------------------------------------------*/
         /* Initialize convolution sum to zero, for every iteration of    */
         /* outer loop. The inner loop computes convolution sum.          */
         /*---------------------------------------------------------------*/

         sum = 0;

         for (i = 0; i < 3; i++)
         {
             pix10  =   IN1[i];
             pix20  =   IN2[i];
             pix30  =   IN3[i];

             mask10 =   mask[i];
             mask20 =   mask[i + 3];
             mask30 =   mask[i + 6];

             sum00  =   pix10 * mask10;
             sum11  =   pix20 * mask20;
             sum22  =   pix30 * mask30;

             sum   +=   sum00 + sum11+ sum22;
         }

         /*---------------------------------------------------------------*/
         /*  Increment input pointers and shift sum and range limit to    */
         /*  0..255.                                                      */
         /*---------------------------------------------------------------*/

         IN1++;
         IN2++;
         IN3++;

         sum = (sum >> shift);

         if ( sum <  0  )       sum = 0;
         if ( sum > 255 )       sum = 255;

         /*--------------------------------------------------------------*/
         /* Store output sum into the output pointer OUT                 */
         /*--------------------------------------------------------------*/

         *OUT++   =       sum;
     }
}

/* ======================================================================== */
/*  End of file:  IMG_conv_3x3_i8_c8s_c.c                                   */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2001, 2008 Texas Instruments, Incorporated.       */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
