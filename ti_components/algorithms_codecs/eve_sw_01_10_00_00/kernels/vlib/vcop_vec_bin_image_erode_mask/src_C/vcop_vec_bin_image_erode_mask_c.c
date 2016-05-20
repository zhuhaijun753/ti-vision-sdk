/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME                                                                 */
/*     vcop_vec_bin_image_erode_mask_cn                                     */
/*                                                                          */
/*     USAGE                                                                */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_vec_bin_image_erode_mask_cn                                */
/*     (                                                                    */
/*         unsigned int in[],                                               */
/*         unsigned int out[],                                              */
/*         const char   complementMask[],                                   */
/*         unsigned short cols,                                               */
/*         unsigned short pitch,                                              */
/*         unsigned short height                                              */
/*     )                                                                    */
/*                                                                          */
/*                                                                          */
/*     in        :  32-bit packed input binary image                        */
/*     out       :  32-bit packed output binary image                       */
/*     complementMask      :  compliment or not (~) of 3*3 erosion kernel   */
/*     cols      :  Number of columns in the binary image                   */
/*     pitch     :  Pitch of the binary image                               */
/*     height    :  Number of rows in the binary image                      */
/*                                                                          */
/*     Returns :  None or void.                                             */
/*                                                                          */
/*                                                                          */
/*     DESCRIPTION                                                          */
/*             This routine accepts 8-bit packed input binary image and     */
/*     performs erosion using a general 3x3 kernel and writes as a 8-bit   */
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

#include "vcop_vec_bin_image_erode_mask_c.h"
#define ALIGN_8(a) ((a + 8-1) & ~(8-1))

void vcop_vec_bin_image_erode_mask_cn
(
    unsigned int in[],
    unsigned int out[],
    const char complementMask[],
    unsigned short cols,
    unsigned short pitch,
    unsigned short height
)
{
    int      i4,i3;
    unsigned char  p0, p1, p2, p3, p4, p5, p6, p7, p8, r;
    unsigned char  in00, in01, in10, in11, in20, in21;
    unsigned char *in8  = (unsigned char *)in;
    unsigned char *out8 = (unsigned char *)out;

    char mask00 = (((complementMask[0] > 0) << 31) >> 31);
    char mask01 = (((complementMask[1] > 0) << 31) >> 31);
    char mask02 = (((complementMask[2] > 0) << 31) >> 31);
    char mask10 = (((complementMask[3] > 0) << 31) >> 31);
    char mask11 = (((complementMask[4] > 0) << 31) >> 31);
    char mask12 = (((complementMask[5] > 0) << 31) >> 31);
    char mask20 = (((complementMask[6] > 0) << 31) >> 31);
    char mask21 = (((complementMask[7] > 0) << 31) >> 31);
    char mask22 = (((complementMask[8] > 0) << 31) >> 31);


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

            p0 = in00 ;
            p1 = (in00>>1  | in01 <<7);
            p2 = (in00>>2  | in01 <<6);
            p3 = in10 ;
            p4 = (in10>>1  | in11 <<7);
            p5 = (in10>>2  | in11 <<6);
            p6 = in20 ;
            p7 = (in20>>1  | in21 <<7);
            p8 = (in20>>2  | in21 <<6);

            p0 |= mask00;
            p1 |= mask01;
            p2 |= mask02;
            p3 |= mask10;
            p4 |= mask11;
            p5 |= mask12;
            p6 |= mask20;
            p7 |= mask21;
            p8 |= mask22;

            r  = ~0;
            r  = (p0 & p1 & p2 & p3 & p4 & p5 & p6 & p7 & p8);

             out8[i4 + i3*pitch/8] = r;
        }
    }
}

/* ======================================================================== */
/*  End of file:  vcop_vec_bin_image_erode_mask_c.c                         */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */


