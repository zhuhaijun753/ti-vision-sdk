/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*                                                                          */
/*    @file : vcop_prune_big_list_kernel.k                                  */
/*                                                                          */
/*    @brief : This routine accepts an input list and an array of indices.  */
/*         The outputs is a pruned list of 'bestN' elements from input      */
/*         based on the ordering in the index list provided.                */
/*                                                                          */
/*     The recommended banks for each of the buffers is captured as A/B/C   */
/*     as part of the buffer pointer. A/B/C can either be IMBUF High,       */
/*     IMBUF low or WMEM.                                                   */
/*                                                                          */
/*    USAGE:                                                                */
/*    This routine is C-callable and can be called as:                      */
/*                                                                          */
/*    void vcop_prune_big_list                                              */
/*    (                                                                     */
/*        __vptr_uint32   inList_A,                                         */
/*        __vptr_uint16   inSortedIndexList_B,                              */
/*        __vptr_uint32   outList_C,                                        */
/*        unsigned short  bestN                                             */
/*    )                                                                     */
/*                                                                          */
/*    inList_A            : Input list to be pruned.                        */
/*    inSortedIndexList_B : List of sorted indexes. The index list is       */
/*                          expected to be of 32-bit with the lower 16-bit  */
/*                          representing the index. The upper 16-bits can   */
/*                          contain some payload data. This list should be  */
/*                          at-least 'bestN' in size.                       */
/*    outList_C           : Pruned and packed output list.                  */
/*    bestN               : Number of elements expected to be available in  */
/*                          the output list.                                */
/*                                                                          */
/*    Returns     :  None or void.                                          */
/*                                                                          */
/*    PERFORMANCE MEASUREMENT:                                              */
/*      1 cycles/pixel + 54 cycle VCOP overheads                            */
/*                                                                          */
/*    @author  : Anoop K P(a-kp@ti.com)                                     */
/*                                                                          */
/*    @version : 1.0 (Nov 2013) : Base version.                             */
/*                                                                          */
/*==========================================================================*/

#if VCOP_HOST_EMULATION
  #include <vcop.h>
#endif

#define IDX_ELEMSZ (sizeof(*inSortedIndexList_B))
#define IDX1_ELEMSZ (sizeof(*inSortedIndexList32_B))
#define OUT_ELEMSZ (sizeof(*outList_C))
#define VCOP_2SIMD_WIDTH        (2 * VCOP_SIMD_WIDTH)

void vcop_prune_big_list
(
    __vptr_uint32   inList_A,
    __vptr_uint16   inSortedIndexList_B,
    __vptr_uint32   inSortedIndexList32_B,
    __vptr_uint32   outList_C,
    __vptr_uint32   nonBestNSize_C,
    unsigned short  threshold,
    unsigned short  bestN
)
{
    __vector Vindex, Vtabledata, count;
    __agen addr0 = 0;
    _LOOKUP(1, 1);

    for(int I1 = 0; I1 < bestN; I1++) {
        __agen table_addr, index_addr, out_addr;
        table_addr = 0;
        index_addr = I1*2*IDX_ELEMSZ;
        out_addr = I1*OUT_ELEMSZ;

        Vindex = (inSortedIndexList_B)[index_addr].onept();
        Vtabledata = inList_A[table_addr].lookup(Vindex);
        outList_C[out_addr].table_npt() = Vtabledata;
    }

    for(int I1 = 0; I1 < 1; I1++)
    {
        __agen index_addr;

        index_addr = 0;
        Vindex = 0xffff0000;
        (inSortedIndexList32_B + bestN*IDX1_ELEMSZ)[index_addr] = Vindex;
        (inSortedIndexList32_B + (bestN+VCOP_SIMD_WIDTH)*IDX1_ELEMSZ)[index_addr] = Vindex;
    }

    __vector mask1, mask2;
    __vector Vt, count1, count2;
    __vector VSh, Vdata1, Vdata2;
    __vector flag1, flag2, flag, Value;
    __vector Vindex1, Vindex2;

    count = 0;
    Vt = threshold;
    VSh = -16;
    Value = 255;

    for(int I2 = 0; I2 < (bestN+VCOP_2SIMD_WIDTH-1)/VCOP_2SIMD_WIDTH; I2++)
    {
        __agen index_addr;
        index_addr = I2*IDX1_ELEMSZ*VCOP_2SIMD_WIDTH;
        Vindex1 = (inSortedIndexList32_B)[index_addr];
        Vindex2 = (inSortedIndexList32_B+VCOP_SIMD_WIDTH*IDX1_ELEMSZ)[index_addr];

        Vdata1 = Vindex1 << VSh;
        Vdata2 = Vindex2 << VSh;

        mask1 = pack(Vt >= Vdata1);
        mask2 = pack(Vt >= Vdata2);

        flag1 = (Value > mask1);
        flag2 = (Value > mask2);

        flag = flag1 | flag2;
        count1 = count_bits(mask1);

        count2 = count_bits(mask2);
        count += count1;

        count += count2;
        nonBestNSize_C[addr0] = count;
        if (flag[0]) goto end_loop1;
    }
    end_loop1:;
}
