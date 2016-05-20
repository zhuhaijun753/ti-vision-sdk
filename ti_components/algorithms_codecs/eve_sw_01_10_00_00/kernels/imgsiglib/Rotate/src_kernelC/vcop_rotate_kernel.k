/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME                                                                 */
/*         vcop_rotate, rotate function for the VICP library.               */
/*                                                                          */
/*                                                                          */
/*     USAGE                                                                */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_rotate_cn                                                  */
/*     (                                                                    */
/*          uint8 *in,                                                      */
/*          uint8 *inter,                                                   */
/*          uint8 *out,                                                     */
/*          int   IMG_W,                                                    */
/*          int   IMG_H,                                                    */
/*          int   OUT_W,                                                    */
/*          int   OUT_H,                                                    */
/*          int   COMP_W,                                                   */
/*          int   COMP_H,                                                   */
/*          int   in_type,                                                  */
/*          int   inter_type                                                */
/*          int   out_type,                                                 */
/*          int   angle,                                                    */
/*          int   rnd_shift                                                 */
/*      );                                                                  */
/*                                                                          */
/*     *in        :  Pointer to an input array of "in_type".                */
/*     *inter     :  Pointer to intermediate array of "inter_type".         */
/*     *out       :  Pointer to output array of "out_type".                 */
/*     IMG_W      :  Width of input image in pixels.                        */
/*     IMG_H      :  Height of the input image in pixels.                   */
/*     OUT_W      :  Width of the output image in pixels.                   */
/*     OUT_H      :  Height of the input image in pixels.                   */
/*     COMP_W     :  The compute width over which rotate values are found.  */
/*     COMP_H     :  The compute height for rotate function.                */
/*     in_type    :  0 - BYTE,  1 - SHORT                                   */
/*     inter_type :  0 - BYTE,  1 - SHORT                                   */
/*     out_type   :  0 - UBYTE, 1 - BYTE, 2 - USHORT, 3 - SHORT             */
/*     angle      :  Angle of rotation, can be 90, 180 or 270.              */
/*     rnd_shift  :  Amount of rounding and shifting on output data.        */
/*                                                                          */
/*                                                                          */
/*     Returns :  None or void.                                             */
/*                                                                          */
/*     DESCRIPTION                                                          */
/*             This routine accepts pointers to a input region "in", and    */
/*     computes the rotate over M X N pixels of the image. The image is     */
/*     split into blocks of size M X N and rotated.                         */
/*                                                                          */
/*     ASSUMPTIONS                                                          */
/*     M and N are assumed to be multiples of 8.                            */
/*                                                                          */
/*     CYCLES/PERFORMANCE                                                   */
/*     1/4 cycles/pixel for 90 and 270 degree rotations.                    */
/*     1/8 cycles/pixel for 180 degree rotation.                            */
/*                                                                          */
/*==========================================================================*/
/*      Copyright (C) 2009-2012 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#define ELEMSZ_IN      sizeof(*in)
#define VECTORSZ_IN   (VCOP_SIMD_WIDTH * ELEMSZ_IN)

#define ELEMSZ_OUT      sizeof(*out)
#define VECTORSZ_OUT   ((VCOP_SIMD_WIDTH) * ELEMSZ_OUT)

#define TRANSPOSE_SIZE        8
#define TRANSPOSE_SIZE_ADD_1  9

#define WORD_SIZE             4

#define ELEMS_PER_WORD  (WORD_SIZE/ELEMSZ_IN)

#define TRANSPOSED_WIDTH_IN_BYTES       ( TRANSPOSE_SIZE * ELEMS_PER_WORD)
#define TRANSPOSED_WIDTH_IN_BYTES_ADD_1 (TRANSPOSE_SIZE_ADD_1 * ELEMS_PER_WORD)

/*------------------------------------------------------------------------*/
/* This is the part where we do 90 degree rotate. Basically, a 2D array   */
/* with the following orientation                                         */
/*   A = 1 2 3                                                            */
/*       4 5 6                                                            */
/*       7 8 9                                                            */
/*                                                                        */
/*  becomes A = 3 6 9                                                     */
/*              2 5 8                                                     */
/*              1 4 7                                                     */
/*                                                                        */
/* This is the rotate kernel to rotate an given image block by 90 deg.    */
/* The rotation is carried out in two steps, first the block is           */
/* transposed, next, the rows are switched such that the top most row     */
/* occupies the bottom-most row and visa versa. Thus, all the rows are    */
/* switched, folding the block along the middle row.                      */
/* e.g.  INPUT                                                            */
/*                row_a                                                   */
/*                row_b                                                   */
/*                row_c                                                   */
/*                row_d                                                   */
/*                row_e                                                   */
/*                                                                        */
/*      OUTPUT                                                            */
/*                row_e                                                   */
/*                row_d                                                   */
/*                row_c                                                   */
/*                row_b                                                   */
/*                row_a                                                   */
/*------------------------------------------------------------------------*/

void vcop_rotate_90
(
     __vptr_uint8  in,         //  Pointer to an input array of "in_type".
     __vptr_uint8  inter,      //  Pointer to intermediate array of "inter_type".
     __vptr_uint8  out,        //  Pointer to output array of "out_type".
     int img_w,                //  Width of input image in pixels.
     int img_h,                //  Height of the input image in pixels.
     int out_w,                //  Width of the output image in pixels.
     int out_h,                //  Height of the input image in pixels.
     int blk_w,                //  The compute width over which rotate values are found.
     int blk_h,                //  The compute height for rotate function.
     int in_type,              //  0 - BYTE,  1 - SHORT
     int inter_type,           //  0 - BYTE,  1 - SHORT
     int out_type,             //  0 - UBYTE, 1 - BYTE, 2 - USHORT, 3 - SHORT
     int angle,                //  Angle of rotation, can be 90, 180 or 270.
     int round_shift           //  Amount of rounding and shifting on output data.
)
{

    /*---------------------------------------------------------------------*/
    /* This is the tranpose block.                                         */
    /*---------------------------------------------------------------------*/


    for ( int I1 = 0; I1 < blk_h/TRANSPOSED_WIDTH_IN_BYTES; I1++ )
    {
        for ( int I2 = 0; I2 < blk_w/VCOP_SIMD_WIDTH; I2++)
        {
            for ( int I3 = 0; I3 < TRANSPOSED_WIDTH_IN_BYTES; I3++)
            {
                /*---------------------------------------------------------*/
                /* Input data is read 8 elements at a time, going          */
                /* column wise (vertically down) upto 32-bytes, and        */
                /* written out as adjacent columns going horizontally.     */
                /*---------------------------------------------------------*/

                __agen dataAddr;
                __agen outAddr;

                dataAddr = I3 * img_w * ELEMSZ_IN + I2 * VCOP_SIMD_WIDTH * ELEMSZ_IN +  I1 * TRANSPOSED_WIDTH_IN_BYTES * img_w * ELEMSZ_IN;
                outAddr  = I3 * ELEMSZ_OUT + I2 * TRANSPOSE_SIZE_ADD_1 * TRANSPOSED_WIDTH_IN_BYTES * ELEMSZ_OUT + I1 * TRANSPOSE_SIZE_ADD_1 * ELEMS_PER_WORD * blk_h * ELEMSZ_OUT;

                V0  =  in[dataAddr];
                inter[outAddr].offset_np1() = V0;
            }
        }
    }

    /*---------------------------------------------------------------------*/
    /* Here we switch the first row with the last and so on. That is fold  */
    /* the array along the middle row.                                     */
    /*---------------------------------------------------------------------*/


    for ( int I1 = 0; I1 < blk_w/TRANSPOSED_WIDTH_IN_BYTES; I1++)
    {
        for ( int I2 = 0; I2 < blk_h; I2++)
        {
            for ( int I3 = 0; I3 < (TRANSPOSED_WIDTH_IN_BYTES/VCOP_SIMD_WIDTH); I3++)
            {
                __agen dataAddr;
                __agen outAddr;

                /*-------------------------------------------------------*/
                /* The input is read is read moving from column 1 to     */
                /* the width of the array.                               */
                /* The output is written starting from the last column   */
                /* moving down towards the first column.                 */
                /*-------------------------------------------------------*/

                dataAddr = I3 * VCOP_SIMD_WIDTH * ELEMSZ_OUT + I2 * TRANSPOSED_WIDTH_IN_BYTES_ADD_1 * ELEMSZ_OUT  +  I1 * blk_h * TRANSPOSED_WIDTH_IN_BYTES_ADD_1 * ELEMSZ_OUT;
                outAddr  = I3 * VCOP_SIMD_WIDTH * ELEMSZ_OUT + I2 * (-TRANSPOSED_WIDTH_IN_BYTES) * ELEMSZ_OUT + I1 * blk_h * TRANSPOSED_WIDTH_IN_BYTES * ELEMSZ_OUT;

                V0 = inter[dataAddr];

               (out + (blk_h  - 1) * TRANSPOSED_WIDTH_IN_BYTES * ELEMSZ_OUT)[outAddr] = V0;

            }
        }
    }

}

/*------------------------------------------------------------------------*/
/* This is the part where we do 180 degree rotate. Basically, a 2D array  */
/* with the following orientation                                         */
/*   A = 1 2 3                                                            */
/*       4 5 6                                                            */
/*       7 8 9                                                            */
/*                                                                        */
/*  becomes A = 9 8 7                                                     */
/*              6 5 4                                                     */
/*              3 2 1                                                     */
/*                                                                        */
/*------------------------------------------------------------------------*/

void vcop_rotate_180
(
     __vptr_uint8  in,
     __vptr_uint8  inter,
     __vptr_uint8  out,
     int img_w,
     int img_h,
     int out_w,
     int out_h,
     int blk_w,
     int blk_h,
     int in_type,
     int inter_type,
     int out_type,
     int angle,
     int round_shift
)
{

     for (int I1 = 0; I1 < blk_h; I1++)
     {
         for (int I2 = 0; I2 < blk_w/VCOP_SIMD_WIDTH; I2++)
         {
             __agen dataAddr;
             __agen outAddr;

             dataAddr = I2 * VCOP_SIMD_WIDTH * ELEMSZ_IN + I1 * img_w * ELEMSZ_IN;
             outAddr  = I2 * (-VCOP_SIMD_WIDTH) * ELEMSZ_OUT + I1 * (-blk_w) * ELEMSZ_OUT;

           V0 = in[dataAddr].dist(7, 6, 5, 4, 3, 2, 1, 0);
           (out + (blk_h * blk_w) - VCOP_SIMD_WIDTH)[outAddr] = V0;
        }

    }
}


/*------------------------------------------------------------------------*/
/* This is the part where we do 270 degree rotate. Basically, a 2D array  */
/* with the following orientation                                         */
/*   A = 1 2 3                                                            */
/*       4 5 6                                                            */
/*       7 8 9                                                            */
/*                                                                        */
/*  becomes A = 7 4 1                                                     */
/*              8 5 2                                                     */
/*              9 6 3                                                     */
/*                                                                        */
/* This is the rotate kernel to rotate an given image block by 270 deg.   */
/* The rotation is carried out in two steps, first the block is           */
/* transposed and the transposed results are written out starting from    */
/* the last column moving towards the first column. Thus, the block gets  */
/* folded along the middle column as shown below.                         */
/* e.g.  INPUT                                                            */
/*                col_a col_b col_c col_d col_e                           */
/*                                                                        */
/*      OUTPUT                                                            */
/*                col_e col_d col_c col_b col_a                           */
/*                                                                        */
/* Next, the 9th word (of zeros) that gets added as part of offset_np1()  */
/* operation is removed by reading and writing out 8 words, skipping the  */
/* 9th and again reading and writing out the subsequent 8 words.          */
/*------------------------------------------------------------------------*/

void vcop_rotate_270
(
     __vptr_uint8  in,
     __vptr_uint8  inter,
     __vptr_uint8  out,
     int img_w,
     int img_h,
     int out_w,
     int out_h,
     int blk_w,
     int blk_h,
     int in_type,
     int inter_type,
     int out_type,
     int angle,
     int round_shift
)
{

    /*-------------------------------------------------------------------*/
    /* This is the tranpose block.                                       */
    /*-------------------------------------------------------------------*/

    for (int  I1 = 0; I1 < blk_h/TRANSPOSED_WIDTH_IN_BYTES; I1++ )
    {
        for (int I2 = 0; I2 < blk_w/VCOP_SIMD_WIDTH; I2++)
        {
            for (int I3 = 0; I3 < TRANSPOSED_WIDTH_IN_BYTES; I3++)
            {
                /*-------------------------------------------------------*/
                /* Input data is read 8 elements at a time, going        */
                /* column wise (vertically down) upto 32-bytes, and      */
                /* written out as adjacent columns going horizontally.   */
                /* However, the output column locations are in           */
                /* the decending order instead of ascending.             */
                /*-------------------------------------------------------*/

                __agen dataAddr;
                __agen outAddr;

                dataAddr = I3 * img_w * ELEMSZ_IN + I2 * VCOP_SIMD_WIDTH * ELEMSZ_IN + I1 * TRANSPOSED_WIDTH_IN_BYTES * img_w * ELEMSZ_IN;
                outAddr  = I3 * (-ELEMSZ_OUT) + I2 * TRANSPOSE_SIZE_ADD_1 * TRANSPOSED_WIDTH_IN_BYTES * ELEMSZ_OUT  + I1 * (-TRANSPOSED_WIDTH_IN_BYTES_ADD_1) * blk_w * ELEMSZ_OUT;

                V0  =  in[dataAddr];
                (inter + ((TRANSPOSED_WIDTH_IN_BYTES_ADD_1 * blk_w) + TRANSPOSED_WIDTH_IN_BYTES - 1 ) )[outAddr].offset_np1() = V0;
            }

        }
    }

   /*--------------------------------------------------------------------*/
   /* Here we remove every 9th word (zeros) that is part of VCOP         */
   /* offset_np1() implementation. This makes the data easy for DMA      */
   /* transfer.                                                          */
   /*--------------------------------------------------------------------*/

   for (int I1 = 0; I1 < blk_w * (blk_h/TRANSPOSED_WIDTH_IN_BYTES); I1++)
   {
       for (int I2 = 0; I2 <TRANSPOSED_WIDTH_IN_BYTES_ADD_1/VCOP_SIMD_WIDTH; I2++)
       {
           __agen dataAddr;
           __agen outAddr;

           dataAddr = I2 * VCOP_SIMD_WIDTH * ELEMSZ_OUT + I1 * TRANSPOSED_WIDTH_IN_BYTES_ADD_1 * ELEMSZ_OUT;
           outAddr  = I2 * VCOP_SIMD_WIDTH * ELEMSZ_OUT + I1 * TRANSPOSED_WIDTH_IN_BYTES * ELEMSZ_OUT;

           V0 = inter[dataAddr];
           out[outAddr] = V0;
        }

    }
}
