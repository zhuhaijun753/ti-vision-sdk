/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*                                                                          */
/*    @file : vcop_extract_bit_field_u32_kernel.k                           */
/*                                                                          */
/*    @brief : This routine accepts an array of 32-bit values. The outputs  */
/*         is a list of extracted 8-bit bit-fields.                         */
/*                                                                          */
/*     The recommended banks for each of the buffers is captured as A/B/C   */
/*     as part of the buffer pointer. A/B/C can either be IMBUF High,       */
/*     IMBUF low or WMEM.                                                   */
/*                                                                          */
/*    USAGE:                                                                */
/*    This routine is C-callable and can be called as:                      */
/*                                                                          */
/*    void vcop_extract_bit_field_u32                                       */
/*    (                                                                     */
/*        __vptr_uint32  *inArray_A,                                        */
/*        unsigned short  length,                                           */
/*        unsigned int    bit_mask,                                         */
/*        unsigned char   shift,                                            */
/*        __vptr_uint8   *outList_B                                         */
/*    )                                                                     */
/*                                                                          */
/*     inArray_A    : Input list to be pruned                               */
/*     length       : Length of the input array                             */
/*     bit_mask     : Bit mask indicating the bits to be selected.          */
/*     shift        : Shift required to align LSB                           */
/*     outList_B    : List of extracted bit-fields                          */
/*                                                                          */
/*    Returns     :  None or void.                                          */
/*                                                                          */
/*    PERFORMANCE MEASUREMENT:                                              */
/*      1 cycles/pixel + 54 cycle VCOP overheads                            */
/*                                                                          */
/*    @author  : Anoop K P(a-kp@ti.com)                                     */
/*                                                                          */
/*    @version : 1.0 (Dec 2013) : Base version.                             */
/*                                                                          */
/*==========================================================================*/

#if VCOP_HOST_EMULATION
  #include <vcop.h>
#endif

#define IN_ELEMSZ (sizeof(*inArray_A))
#define IN_VECTORSZ (VCOP_SIMD_WIDTH*IN_ELEMSZ)

#define OUT_ELEMSZ (sizeof(*outList_B))
#define OUT_VECTORSZ (VCOP_SIMD_WIDTH*OUT_ELEMSZ)

void vcop_extract_bit_field_u32
(
    __vptr_uint32   inArray_A,
    unsigned short  length,
    unsigned int    bit_mask,
    unsigned char   shift,
    __vptr_uint8    outList_B
)
{
    __vector Vmask;

    Vmask = bit_mask;

    for(int I1 = 0; I1 < (length + VCOP_SIMD_WIDTH - 1)/VCOP_SIMD_WIDTH; I1++) {
        __agen Addr_in, Addr_out;
        __vector Vin, Vout;

        Addr_in = I1*IN_VECTORSZ;
        Addr_out = I1*OUT_VECTORSZ;

        Vin = inArray_A[Addr_in];

        Vout = Vin & Vmask;

        outList_B[Addr_out] = Vout.truncate(shift);
    }
}
