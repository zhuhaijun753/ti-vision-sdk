/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*                                                                          */
/*  @file : vcop_median3x3_cn.h                                             */
/*                                                                          */
/*  @brief : This file contains declarations for the C reference            */
/*  function for 3x3 median filtering kernel.                               */
/*                                                                          */
/*  vcop_median3x3_char_cn                                                  */
/*     This routine accepts pointers to a input region "in" of type         */
/*     unsigned char, and computes the median over 3x3 pixels of the        */
/*     image.                                                               */
/*                                                                          */
/*  ASSUMPTIONS                                                             */
/*     While The C code does not have any assumptions on the size of        */
/*     the arrays, the kernel-C code assumes zero padding of last 2 rows    */
/*     and 2 columns of the input image. Intermediate scratch buffers are   */
/*     also used which have sizes of (3 * (width + 2) * height ).           */
/*                                                                          */
/*  USAGE:                                                                  */
/*     void vcop_median3x3_uchar_cn                                         */
/*     (                                                                    */
/*          signed char   *in,                                              */
/*          signed char   *out,                                             */
/*          signed char   *scratch1,                                        */
/*          signed char   *scratch2,                                        */
/*          int           w_input,                                          */
/*          int           w_out,                                            */
/*          int           w_compute,                                        */
/*          int           h_compute                                         */
/*     )                                                                    */
/*                                                                          */
/*     *in        :  Pointer to an input array of uchar.                    */
/*     *out       :  Pointer to output array of uchar.                      */
/*     *scratch1  :  Pointer to intermediate array.                         */
/*     *scratch2  :  Pointer to intermediate array.                         */
/*     w_input    :  Width of the input image in pixels.                    */
/*     w_out      :  Width of the output image in pixels.                   */
/*     w_compute  :  The compute width over which median values are found.  */
/*     h_compute  :  The compute height for median filter.                  */
/*                                                                          */
/*     Returns :  None or void.                                             */
/*                                                                          */
/*                                                                          */
/*  vcop_median3x3_char_cn                                                  */
/*     This routine accepts pointers to a input region "in" of type         */
/*     signed char, and computes the median over 3x3 pixels of the          */
/*     image.                                                               */
/*                                                                          */
/*  ASSUMPTIONS                                                             */
/*     While The C code does not have any assumptions on the size of        */
/*     the arrays, the kernel-C code assumes zero padding of last 2 rows    */
/*     and 2 columns of the input image. Intermediate scratch buffers are   */
/*     also used which have sizes of (3 * (width + 2) * height ).           */
/*                                                                          */
/*  USAGE:                                                                  */
/*     void vcop_median3x3_char_cn                                          */
/*     (                                                                    */
/*          signed char   *in,                                              */
/*          signed char   *out,                                             */
/*          signed char   *scratch1,                                        */
/*          signed char   *scratch2,                                        */
/*          int           w_input,                                          */
/*          int           w_out,                                            */
/*          int           w_compute,                                        */
/*          int           h_compute                                         */
/*     )                                                                    */
/*                                                                          */
/*     *in        :  Pointer to an input array of char.                     */
/*     *out       :  Pointer to output array of char.                       */
/*     *scratch1  :  Pointer to intermediate array.                         */
/*     *scratch2  :  Pointer to intermediate array.                         */
/*     w_input    :  Width of the input image in pixels.                    */
/*     w_out      :  Width of the output image in pixels.                   */
/*     w_compute  :  The compute width over which median values are found.  */
/*     h_compute  :  The compute height for median filter.                  */
/*                                                                          */
/*     Returns :  None or void.                                             */
/*                                                                          */
/*                                                                          */
/*  @version 0.1 (July 2014) : Base version.                                */
/*                                                                          */
/*==========================================================================*/

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
);

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
);
