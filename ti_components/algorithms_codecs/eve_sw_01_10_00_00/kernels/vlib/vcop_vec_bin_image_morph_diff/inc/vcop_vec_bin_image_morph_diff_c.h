/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME                                                                 */
/*     vcop_vec_bin_image_morph_diff_cn                                    */
/*                                                                          */
/*     USAGE                                                                */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_vec_bin_image_morph_diff_cn                               */
/*     (                                                                    */
/*         unsigned int in[],                                               */
/*         unsigned int out[],                                              */
/*         const char mask[],                                               */
/*         int cols,                                                        */
/*         int pitch,                                                       */
/*         int height                                                       */
/*     )                                                                    */
/*                                                                          */
/*     A         :  Pointer to an input array of shorts.                    */
/*     B         :  Pointer to second input array of shorts.                */
/*     C         :  Pointer to output unsigned int value                    */
/*     array_len :  length of the arrays A and B                            */
/*                                                                          */
/*     Returns :  None or void.                                             */
/*                                                                          */
/*                                                                          */
/*     DESCRIPTION                                                          */
/*             This routine accepts pointers to two input arrays of         */
/*     length array_len and returns a single integer value representing     */
/*     the L1 distance between the two arrays.                              */
/*                                                                          */
/*     ASSUMPTIONS                                                          */
/*     While The C code does not have any assumptions on the length of      */
/*     the arrays, the assembly code assumes that array_len the length      */
/*     of the arrays is a multiple of 8.                                    */
/*                                                                          */
/*==========================================================================*/
/*      Copyright (C) 2010 Texas Instruments Incorporated.                  */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#ifndef _vcop_vec_bin_image_morph_diff_CN
#define _vcop_vec_bin_image_morph_diff_CN  1

void vcop_vec_bin_image_morph_diff_cn
(
    unsigned short        blk_w,        // width of input block, in bits or pixels
    unsigned short        line_ofst,    // offset between input lines, in in bits or pixels
    unsigned short        blk_h,        // height of input block
    unsigned int         *data1_ptr,    // input 1 data pointer (data >= data2)
    unsigned short        data1_bit_shift, // align data 1 and data 2 by shifting data1 to left.
    unsigned int         *data2_ptr,    // input 2 data pointer
    unsigned short        data2_bit_shift, // align data 1 and data 2 by shifting data2 to left.
    unsigned int         *output_ptr    // output data pointer
);

#endif

/* ======================================================================== */
/*  End of file:  vcop_vec_bin_image_morph_diff_c.h                        */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */



