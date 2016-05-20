/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME                                                                 */
/*     vcop_vec_bin_image_erode_cross_kernel                                */
/*                                                                          */
/*     USAGE                                                                */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_vec_bin_image_erode_cross                                  */
/*     (                                                                    */
/*         __vptr_uint32 pIn,                                               */
/*         __vptr_uint32 out,                                               */
/*         unsigned short cols,                                              */
/*         unsigned short pitch,                                             */
/*         unsigned short height                                             */
/*     )                                                                    */
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
/*     performs erosion using a 3x3 cross kernel and writes as a 8-bit      */
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
/*     multiple of 32. This is because word npt read (of pIn) has to        */
/*     be word aligned.                                                     */
/*                                                                          */
/*==========================================================================*/
/*      Copyright (C) 2010 Texas Instruments Incorporated.                  */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#if VCOP_HOST_EMULATION
#include <vcop.h>
#endif


#define ELEMSZ          sizeof(*pIn)
#define VECTORSZ        (VCOP_SIMD_WIDTH*ELEMSZ)
#define ALIGN_32SIMD(a) ((a + 32*VCOP_SIMD_WIDTH-1) & ~(32*VCOP_SIMD_WIDTH-1))

void vcop_vec_bin_image_erode_cross
(
    __vptr_uint32 pIn,
    __vptr_uint32 out,
    unsigned short cols,
    unsigned short pitch,
    unsigned short height
)
{
     __vector  in00, in01, in10, in11, in20, in21, R6, R7,R12;
     __vector  R8, R9, R10, R11, R13, t1, t2,t3, t4;

    R10 =  31;
    R11 =  30;
    R12 = -2;
    R13 = -1;

    for(int I1 = 0; I1 < height; I1 ++ )
    {
        for (int I2 = 0; I2 < ALIGN_32SIMD(cols)/(32*VCOP_SIMD_WIDTH); I2++)
        {
            __agen Addr1;

            Addr1 = I1*(pitch/8) + I2*VECTORSZ;

            in00 = (pIn)                  [Addr1];
            in01 = (pIn + 1*4)            [Addr1];
            in10 = (pIn + pitch/8)        [Addr1];
            in11 = (pIn + pitch/8   + 1*4)[Addr1];
            in20 = (pIn + pitch*2/8)      [Addr1];
            in21 = (pIn + pitch*2/8 + 1*4)[Addr1];

    /*---------------------------------------------------------------------*/
    /*  The same register is used for accumulating for effectively         */
    /*  pipelining of 3 source instructions (SHFTOR and AND3).             */
    /*---------------------------------------------------------------------*/

            R6  = in00<<R13 ;
            R7  = in10<<R13 ;

            R6 |= in01 <<R10;
            R7 |= in11 <<R10;

            R8  = in10<<R12 ;
            R9  = in20<<R13 ;

            in10 &= R6 & R7 ;

            R8 |= in11 <<R11;
            R9 |= in21 <<R10;

            R8 &= in10 & R9 ;

            out[Addr1] = R8;
        }
    }
}

/* ======================================================================== */
/*  End of file: vcop_vec_bin_image_erode_cross_kernel.k                    */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */


