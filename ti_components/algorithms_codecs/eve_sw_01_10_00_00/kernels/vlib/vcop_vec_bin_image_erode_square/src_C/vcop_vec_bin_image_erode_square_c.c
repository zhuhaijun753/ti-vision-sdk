/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME                                                                 */
/*     vcop_vec_bin_image_erode_square_cn                                   */
/*                                                                          */
/*     USAGE                                                                */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_vec_bin_image_erode_square_cn                              */
/*     (                                                                    */
/*         unsigned int in[],                                               */
/*         unsigned int out[],                                              */
/*         unsigned short cols,                                              */
/*         unsigned short pitch,                                             */
/*         unsigned short height                                             */
/*     )                                                                    */
/*                                                                          */
/*                                                                          */
/*     in        :  32-bit packed input binary image                        */
/*     out       :  32-bit packed output binary image                       */
/*     cols      :  Number of columns (bits) in the binary image            */
/*     pitch     :  Pitch of the binary image in terms of bits              */
/*     height    :  Number of rows in the binary image                      */
/*                                                                          */
/*     Returns :  None or void.                                             */
/*                                                                          */
/*                                                                          */
/*     DESCRIPTION                                                          */
/*             This routine accepts 8-bit packed input binary image and     */
/*     performs erosion using a 3x3 square kernel and writes as a 8-bit     */
/*     packed output binary image. Each binary image byte will have         */
/*     left most pixel 0 at LSB and right most pixel 7 at MSB of the byte.  */
/*     Therefore the first 4 bytes of the image in memory will be:          */
/*     P7 P6 ... P0 P15 P14 ... P8 P23 P22 ... P16 P31 P30 ... P24          */
/*     where Pi is the pixel at location i of binary image.                 */
/*     On loading these 4 bytes onto register, the register will have:      */
/*     P31 P30 ... P24 P23 ... P16 P15 ... P8 P7 ... P0                     */
/*                                                                          */
/*     ASSUMPTIONS                                                          */
/*     The number of pitch in the input binary image should be a            */
/*     multiple of 8.                                                       */
/*                                                                          */
/*==========================================================================*/
/*      Copyright (C) 2010 Texas Instruments Incorporated.                  */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#include <stdio.h>
#include <stdlib.h>

#include "vcop_vec_bin_image_erode_square_c.h"
#define ALIGN_8(a) ((a + 8-1) & ~(8-1))

void vcop_vec_bin_image_erode_square_cn
(
    unsigned int in[],
    unsigned int out[],
    unsigned short cols,
    unsigned short pitch,
    unsigned short height
)
{
    int i4,i3;
    unsigned char r,in00, in01, in10, in11, in20, in21;
    unsigned char *in8  = (unsigned char *)in;
    unsigned char *out8 = (unsigned char *)out;

    for(i3 = 0; i3 < height; i3 ++ )
    {
        for (i4 = 0; i4 < ALIGN_8(cols)/8; i4 ++)
        {
             in00 = in8[i4 + i3*pitch/8];
             in01 = in8[i4 + i3*pitch/8 + 1];
             in10 = in8[i4 + i3*pitch/8 + pitch/8];
             in11 = in8[i4 + i3*pitch/8 + pitch/8 + 1];
             in20 = in8[i4 + i3*pitch/8 + pitch/4];
             in21 = in8[i4 + i3*pitch/8 + pitch/4 + 1];

            r = ~0;
            r &= in00;
            r &= (in00>>1  | in01 <<7);
            r &= (in00>>2  | in01 <<6);
            r &= in10;
            r &= (in10>>1  | in11 <<7);
            r &= (in10>>2  | in11 <<6);
            r &= in20;
            r &= (in20>>1  | in21 <<7);
            r &= (in20>>2  | in21 <<6);

             out8[i4 + i3*pitch/8] = r;
        }
    }
}

/* ======================================================================== */
/*  End of file:  vcop_vec_bin_image_erode_square_c.c                       */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2012 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */


