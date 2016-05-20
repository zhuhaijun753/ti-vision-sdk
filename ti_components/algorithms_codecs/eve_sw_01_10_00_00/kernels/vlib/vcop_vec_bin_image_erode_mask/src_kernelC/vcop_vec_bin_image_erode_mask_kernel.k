/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME                                                                 */
/*     vcop_vec_bin_image_erode_mask_kernel                                 */
/*                                                                          */
/*     USAGE                                                                */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_vec_bin_image_erode_mask                                   */
/*     (                                                                    */
/*         __vptr_uint32 pIn,                                               */
/*         __vptr_uint32 complementMask0,                                   */
/*         __vptr_uint32 complementMask1,                                   */
/*         __vptr_uint32 complementMask2,                                   */
/*         __vptr_uint32 out,                                               */
/*         unsigned short cols,                                              */
/*         unsigned short pitch,                                             */
/*         unsigned short height                                             */
/*     )                                                                    */
/*                                                                          */
/*     in        :  32-bit packed input binary image                        */
/*     out       :  32-bit packed output binary image                       */
/*     complementMask0  :  compliment or not (~) of Column 0 of 3*3 mask    */
/*     complementMask1  :  compliment or not (~) of Column 1 of 3*3 mask    */
/*     complementMask2  :  compliment or not (~) of Column 2 of 3*3 mask    */
/*     cols      :  Number of columns (bits) in the binary image            */
/*     pitch     :  Pitch of the binary image in terms of bits              */
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

void vcop_vec_bin_image_erode_mask
(
    __vptr_uint32 pIn,
    __vptr_uint32 complementMask0,
    __vptr_uint32 complementMask1,
    __vptr_uint32 complementMask2,
    __vptr_uint32 out,
    unsigned short cols,
    unsigned short pitch,
    unsigned short height
)
{
    __vector  R0, R1, R2, R3, R4, R5, R6, R7,R12,R13,R14,R15;
    __vector  R8, R9, R10, R11;

    R12 = -1;
    R13 = -2;
    R14 =  31;
    R15 =  30;

    for(int I1 = 0; I1 < height; I1 ++ )
    {
        for (int I2 = 0; I2 < ALIGN_32SIMD(cols)/(32*VCOP_SIMD_WIDTH); I2++)
        {
             __agen Addr2;
            Addr2 = I1*(pitch/8) + I2*VECTORSZ;

            R8=~0U;

    /*---------------------------------------------------------------------*/
    /*  Due to register pressure, an inner is created to do the 3x3        */
    /*  operations as 3 1x3 operations.                                    */
    /*---------------------------------------------------------------------*/



            for(int I3=0;I3<3;I3++)
            {
                 __agen Addr1, Addr3;
                Addr1 = I1*(pitch/8) + I2*VECTORSZ + I3*(pitch/8);
                Addr3 = I3*VECTORSZ;

                R0 = pIn        [Addr1];
                R1 = (pIn + 1*4)[Addr1];
                R2 = complementMask0      [Addr3];
                R3 = complementMask1      [Addr3];
                R4 = complementMask2      [Addr3];

                R9  = R0<<R12 ;
                R10 = R0<<R13 ;

                R9 |= R1 <<R14;
                R10|= R1 <<R15;

                R5   = R0 | R2   ;

                R9   =  R9  | R3 ;
                R10  =  R10 | R4 ;

                R5  &=  R9       ;

                R8  &=  R5  & R10;
            }
             out[Addr2] =  R8;
        }
    }
}

/* ======================================================================== */
/*  End of file:  vcop_vec_bin_image_erode_mask_kernel.k                    */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */


