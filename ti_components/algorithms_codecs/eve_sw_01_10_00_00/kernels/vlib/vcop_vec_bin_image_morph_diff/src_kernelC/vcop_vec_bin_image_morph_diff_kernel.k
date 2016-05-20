/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME                                                                 */
/*     vcop_vec_bin_image_morph_diff                                        */
/*                                                                          */
/*     USAGE                                                                */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_vec_bin_image_morph_diff                                   */
/*     (                                                                    */
/*         unsigned short         blk_w,                                    */
/*         unsigned short         line_ofst,                                */
/*         unsigned short         blk_h,                                    */
/*         __vptr_uint32          data1_ptr,                                */
/*         unsigned short         data1_bit_shift,                          */
/*         __vptr_uint32          data2_ptr                                 */
/*         unsigned short         data2_bit_shift,                          */
/*         __vptr_uint32          output_ptr                                */
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
/*     multiple of 32.                                                      */
/*                                                                          */
/*==========================================================================*/
/*      Copyright (C) 2010 Texas Instruments Incorporated.                  */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#if VCOP_HOST_EMULATION
#include <vcop.h>
#endif

#define ELEMSZ          sizeof(*data1_ptr)
#define VECTORSZ        (VCOP_SIMD_WIDTH*ELEMSZ)
#define ALIGN_32SIMD(a) ((a + 32*VCOP_SIMD_WIDTH-1) & ~(32*VCOP_SIMD_WIDTH-1))


void vcop_vec_bin_image_morph_diff
(
    unsigned short         blk_w,
    unsigned short         line_ofst,
    unsigned short         blk_h,
    __vptr_uint32          data1_ptr,
    unsigned short         data1_bit_shift,
    __vptr_uint32          data2_ptr,
    unsigned short         data2_bit_shift,
    __vptr_uint32          output_ptr
)
{
    __vector Vdata1, Vdata2, Vin1, Vin1_1, Vin2, Vin2_1, Vdiff;
    __vector Vdata1shift, Vdata1shift_opp, Vdata2shift, Vdata2shift_opp;

    Vdata1shift     =     -data1_bit_shift;
    Vdata1shift_opp = 32 - data1_bit_shift;
    Vdata2shift     =     -data2_bit_shift;
    Vdata2shift_opp = 32 - data2_bit_shift;

    for (int I1 = 0; I1 < blk_h; I1++)
    {
        for (int I2 = 0; I2 < ALIGN_32SIMD(blk_w)/(32*VCOP_SIMD_WIDTH); I2++)
        {
            __agen A0, A1;
            A0 = I1*(line_ofst/8) + I2*VECTORSZ;

            Vin1   =  data1_ptr       [A0];
            Vin1_1 = (data1_ptr + 1*4)[A0];
            Vin2   =  data2_ptr       [A0];
            Vin2_1 = (data2_ptr + 1*4)[A0];

            Vdata1   = Vin1   << Vdata1shift;
            Vdata1  |= Vin1_1 << Vdata1shift_opp;

            Vdata2   = Vin2   << Vdata2shift;
            Vdata2  |= Vin2_1 << Vdata2shift_opp;

            Vdiff = Vdata1 ^ Vdata2;

            output_ptr[A0] = Vdiff;
        }
    }
}
