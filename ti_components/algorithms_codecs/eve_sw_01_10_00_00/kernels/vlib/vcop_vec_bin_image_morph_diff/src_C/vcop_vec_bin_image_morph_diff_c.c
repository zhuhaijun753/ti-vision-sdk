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
/*         unsigned short         blk_w,                                    */
/*         unsigned short         line_ofst,                                */
/*         unsigned short         blk_h,                                    */
/*         unsigned int          *data1_ptr,                                 */
/*         unsigned short         data1_bit_shift,                          */
/*         unsigned int          *data2_ptr                                  */
/*         unsigned short         data2_bit_shift,                          */
/*         unsigned int          *output_ptr                                 */
/*     )                                                                    */
/*                                                                          */
/*     blk_w           :  Number of columns (in bits) in the binary image   */
/*     line_ofst       :  Pitch of the binary image in bits                 */
/*     blk_h           :  Number of rows in the binary image                */
/*     data1_ptr       :  8-bit packed input binary image                   */
/*     data1_bit_shift :  number of bit Shift to be performed on data 1     */
/*     data2_ptr       :  8-bit packed input binary image                   */
/*     data2_bit_shift :  number of bit Shift to be performed on data 2     */
/*     out             :  8-bit packed output binary image                  */
/*                                                                          */
/*     Returns :  None or void.                                             */
/*                                                                          */
/*                                                                          */
/*     DESCRIPTION                                                          */
/*             This routine accepts two 8-bit packed input binary image,    */
/*     bit aligns them by performing bit shift, and then performs a bit     */
/*     subtraction or XOR to generate a 8-bit packed output binary image.   */
/*                                                                          */
/*     ASSUMPTIONS                                                          */
/*     The pitch in the input binary image should be a                      */
/*     multiple of 8.                                                       */
/*                                                                          */
/*==========================================================================*/
/*      Copyright (C) 2010 Texas Instruments Incorporated.                  */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#include <stdio.h>
#include <stdlib.h>

#include "vcop_vec_bin_image_morph_diff_c.h"
#define ALIGN_8(a) ((a + 8-1) & ~(8-1))


void vcop_vec_bin_image_morph_diff_cn
(
    unsigned short        blk_w,
    unsigned short        line_ofst,
    unsigned short        blk_h,
    unsigned int         *data1_ptr,
    unsigned short        data1_bit_shift,
    unsigned int         *data2_ptr,
    unsigned short        data2_bit_shift,
    unsigned int         *output_ptr
)
{
    unsigned int  i1, i2, data1_bit_align_opp, data2_bit_align_opp;
    unsigned char data1, data1_1, data2, data2_1;
    unsigned char *data1_8ptr  = (unsigned char *)data1_ptr;
    unsigned char *data2_8ptr  = (unsigned char *)data2_ptr;
    unsigned char *output_8ptr = (unsigned char *)output_ptr;

    data1_bit_align_opp = 8 - data1_bit_shift;
    data2_bit_align_opp = 8 - data2_bit_shift;

    for (i1 = 0; i1 < blk_h; i1++)
    {
        for (i2 = 0; i2 < ALIGN_8(blk_w)/8; i2++)
        {
            data1   = data1_8ptr[i2 + i1*line_ofst/8];
            data1_1 = data1_8ptr[i2 + i1*line_ofst/8 + 1];
            data2   = data2_8ptr[i2 + i1*line_ofst/8];
            data2_1 = data2_8ptr[i2 + i1*line_ofst/8 + 1];

            data1   = data1   >> data1_bit_shift;
            data1_1 = ((unsigned int)data1_1) << data1_bit_align_opp;
            data1   = data1 | data1_1;

            data2   = data2   >> data2_bit_shift;
            data2_1 = ((unsigned int)data2_1) << data2_bit_align_opp;
            data2   = data2 | data2_1;

            output_8ptr[i2 + i1*line_ofst/8] = data1 ^ data2;
        }
    }
}

/* ======================================================================== */
/*  End of file:  vcop_vec_bin_image_morph_diff_c.c                        */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */


