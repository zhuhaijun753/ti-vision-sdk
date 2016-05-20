/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME                                                                 */
/*     vcop_bilinearInterpolateYUV422IchromaPblockUpdate                    */
/*                                                                          */
/*     REVISION HISTORY                                                     */
/*     2/5/14..............Second Version........Saurabh Chandra            */
/*                                                                          */
/*     USAGE                                                                */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_bilinearInterpolateYUV422IchromaPblockUpdate(              */
/*             __vptr_uint16       numMappedPixels_ptr,                     */
/*             __vptr_uint16       pBlock16,                                */
/*             unsigned int        scatterStoreArray_ptr,                   */
/*             __vptr_uint32       pBlock32                                 */
/*     )                                                                    */
/*                                                                          */
/*     Returns        :  None or void.                                      */
/*                                                                          */
/*                                                                          */
/*     DESCRIPTION                                                          */
/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
#if VCOP_HOST_EMULATION
#include <vcop.h>
#endif

#include "vcop_remap.h"

/* Modify the Param Block of the vcop_bilinearInterpolate8b.k kernel */
void vcop_bilinearInterpolateYUV422IchromaUPblockUpdate(
        __vptr_uint16       numMappedPixels_ptr,
        __vptr_uint16       pBlock16
)
{
#define NUM_ITERATIONS_LOOP_1_PTR (6)
#define NUM_ITERATIONS_TLU_1_PTR  (34)
#define NUM_ITERATIONS_TLU_2_PTR  (66)
#define NUM_ITERATIONS_LOOP_2_PTR (98)
        __vector VnumMappedPixels;
        __agen Addr0 = 0;

        VnumMappedPixels = numMappedPixels_ptr[Addr0].onept();

    for (int I1 = 0; I1 < 1; I1++) {

        __vector Vone, Vfifteen, Vshiftfour, Vseven, Vshiftthree, Vshiftone, VlutLoop, Vloop1, Vloop4;

        Vone = 0x00000001;
        Vfifteen = 0x0000000F;
        Vshiftfour = -4;
        Vseven = 0x00000007;
        Vshiftthree = -3;
        Vshiftone = 1;

        VnumMappedPixels   = max(VnumMappedPixels, Vone);
        VlutLoop = VnumMappedPixels - Vone;
        Vloop1   = VnumMappedPixels + Vfifteen;
        Vloop1   = Vloop1 << Vshiftfour;
        Vloop1   = Vloop1 - Vone;
        Vloop4   = VnumMappedPixels + Vseven;
        Vloop4   = Vloop4 << Vshiftthree;
        Vloop4   = Vloop4 - Vone;

        (pBlock16 + NUM_ITERATIONS_LOOP_1_PTR)[Addr0].onept()  = Vloop1;
        (pBlock16 + NUM_ITERATIONS_TLU_1_PTR)[Addr0].onept() = VlutLoop;
        (pBlock16 + NUM_ITERATIONS_TLU_2_PTR)[Addr0].onept() = VlutLoop;
        (pBlock16 + NUM_ITERATIONS_LOOP_2_PTR)[Addr0].onept() = Vloop4;
    }
}

void vcop_bilinearInterpolateYUV422IchromaVPblockUpdate(
        __vptr_uint16       numMappedVPixels_ptr,
        __vptr_uint16       numMappedUPixels_ptr,
        __vptr_uint16       pBlock16,
        unsigned int        scatterStoreArray_ptr,
        __vptr_uint32       pBlock32
)
{
#define NUM_ITERATIONS_LOOP_1_PTR (6)
#define NUM_ITERATIONS_TLU_1_PTR  (34)
#define NUM_ITERATIONS_TLU_2_PTR  (66)
#define NUM_ITERATIONS_LOOP_2_PTR (98)
#define SCATTER_STORE_ARRY_V_PTR  (112)
        __vector VnumMappedVPixels, VnumMappedUPixels;
        __agen Addr0 = 0;

        VnumMappedVPixels = numMappedVPixels_ptr[Addr0].onept();
        VnumMappedUPixels = numMappedUPixels_ptr[Addr0].onept();

    for (int I1 = 0; I1 < 1; I1++) {

        __vector Vone, Vfifteen, Vshiftfour, Vseven, Vshiftthree, Vshiftone, VlutLoop, Vloop1, Vloop4, VscatterStoreArray, VscatterStoreArrayV;

        Vone = 0x00000001;
        Vfifteen = 0x0000000F;
        Vshiftfour = -4;
        Vseven = 0x00000007;
        Vshiftthree = -3;
        Vshiftone = 1;

        VscatterStoreArray = scatterStoreArray_ptr;
        VnumMappedVPixels   = max(VnumMappedVPixels, Vone);
        VlutLoop = VnumMappedVPixels - Vone;
        Vloop1   = VnumMappedVPixels + Vfifteen;
        Vloop1   = Vloop1 << Vshiftfour;
        Vloop1   = Vloop1 - Vone;
        Vloop4   = VnumMappedVPixels + Vseven;
        Vloop4   = Vloop4 << Vshiftthree;
        Vloop4   = Vloop4 - Vone;
        VscatterStoreArrayV   = VnumMappedUPixels << Vshiftone;
        VscatterStoreArrayV   = VscatterStoreArrayV + VscatterStoreArray;

        (pBlock16 + NUM_ITERATIONS_LOOP_1_PTR)[Addr0].onept()  = Vloop1;
        (pBlock16 + NUM_ITERATIONS_TLU_1_PTR)[Addr0].onept() = VlutLoop;
        (pBlock16 + NUM_ITERATIONS_TLU_2_PTR)[Addr0].onept() = VlutLoop;
        (pBlock16 + NUM_ITERATIONS_LOOP_2_PTR)[Addr0].onept() = Vloop4;
        (pBlock32 + SCATTER_STORE_ARRY_V_PTR)[Addr0].onept() = VscatterStoreArrayV;
    }
}
