/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME                                                                 */
/*     vcop_nnInterpolate422IchromaPblockUpdate                             */
/*                                                                          */
/*     REVISION HISTORY                                                     */
/*     2/5/14..............Second Version........Saurabh Chandra            */
/*                                                                          */
/*     USAGE                                                                */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_nnInterpolate422IchromaPblockUpdate(                       */
/*             __vptr_uint16       numMappedPixels_ptr,                     */
/*             __vptr_uint16       pBlock16                                 */
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

/* Modify the Param Block of the vcop_nnInterpolate420SPchroma.k kernel */
void vcop_nnInterpolate422IchromaUPblockUpdate(
        __vptr_uint16       numMappedPixels_ptr,
        __vptr_uint16       pBlock16
)
{
#define NUM_ITERATIONS_TLU_1_PTR  (6)
#define NUM_ITERATIONS_LOOP_1_PTR (50)
        __vector VnumMappedPixels;
        __agen Addr0 = 0;

        VnumMappedPixels = numMappedPixels_ptr[Addr0].onept();

    for (int I1 = 0; I1 < 1; I1++) {

        __vector Vone, Vseven, Vshiftthree, Vshiftone, VlutLoop, Vloop1;

        Vone = 0x00000001;
        Vseven = 0x00000007;
        Vshiftthree = -3;
        Vshiftone = 1;
        VnumMappedPixels   = max(VnumMappedPixels, Vone);
        VlutLoop = VnumMappedPixels - Vone;
        Vloop1   = VnumMappedPixels + Vseven;
        Vloop1   = Vloop1 << Vshiftthree;
        Vloop1   = Vloop1 - Vone;

        (pBlock16 + NUM_ITERATIONS_TLU_1_PTR)[Addr0].onept() = VlutLoop;
        (pBlock16 + NUM_ITERATIONS_LOOP_1_PTR)[Addr0].onept() = Vloop1;
    }
}

void vcop_nnInterpolate422IchromaVPblockUpdate(
        __vptr_uint16       numMappedVPixels_ptr,
        __vptr_uint16       numMappedUPixels_ptr,
        __vptr_uint16       pBlock16,
        unsigned int        scatterStoreArray_ptr,
        __vptr_uint32       pBlock32
)
{
#define NUM_ITERATIONS_TLU_1_PTR  (6)
#define NUM_ITERATIONS_LOOP_1_PTR (50)
#define SCATTER_STORE_ARRY_V_PTR  (52)
        __vector VnumMappedVPixels, VnumMappedUPixels, VnumMappedPixels_1;
        __agen Addr0 = 0;

        VnumMappedVPixels = numMappedVPixels_ptr[Addr0].onept();
        VnumMappedUPixels = numMappedUPixels_ptr[Addr0].onept();

    for (int I1 = 0; I1 < 1; I1++) {

        __vector Vone, Vseven, Vshiftthree, Vshiftone, VlutLoop, Vloop1, VscatterStoreArray, VscatterStoreArrayV;

        VscatterStoreArray = scatterStoreArray_ptr;
        Vone = 0x00000001;
        Vseven = 0x00000007;
        Vshiftthree = -3;
        Vshiftone = 1;

        VnumMappedPixels_1   = max(VnumMappedVPixels, Vone);
        VlutLoop = VnumMappedPixels_1 - Vone;
        Vloop1   = VnumMappedPixels_1 + Vseven;
        Vloop1   = Vloop1 << Vshiftthree;
        Vloop1   = Vloop1 - Vone;
        VscatterStoreArrayV   = VnumMappedUPixels << Vshiftone;
        VscatterStoreArrayV   = VscatterStoreArrayV + VscatterStoreArray;

        (pBlock16 + NUM_ITERATIONS_TLU_1_PTR)[Addr0].onept() = VlutLoop;
        (pBlock16 + NUM_ITERATIONS_LOOP_1_PTR)[Addr0].onept() = Vloop1;
        (pBlock32 + SCATTER_STORE_ARRY_V_PTR)[Addr0].onept() = VscatterStoreArrayV;
    }
}
