/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME                                                                 */
/*     vcop_nnInterpolate420SPchromaPblockUpdate                               */
/*                                                                          */
/*     REVISION HISTORY                                                     */
/*     2/5/14..............Second Version........Saurabh Chandra            */
/*                                                                          */
/*     USAGE                                                                */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_nnInterpolate420SPchromaPblockUpdate(                      */
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

/* Modify the Param Block of the vcop_nnInterpolate420SPchroma.k kernel */
void vcop_nnInterpolate420SPchromaPblockUpdate(
        __vptr_uint16       numMappedPixels_ptr,
        __vptr_uint16       pBlock16,
        unsigned int        scatterStoreArray_ptr,
        __vptr_uint32       pBlock32
)
{
#define NUM_ITERATIONS_TLU_1_PTR  (6)
#define NUM_ITERATIONS_LOOP_1_PTR (44)
#define NUM_ITERATIONS_LOOP_2_PTR (54)
        __vector VnumMappedPixels;
        __agen Addr0 = 0;

        VnumMappedPixels = numMappedPixels_ptr[Addr0].onept();

    for (int I1 = 0; I1 < 1; I1++) {

        __vector Vone, VscatterStoreArray, Vseven, Vshiftthree, Vshiftone, VlutLoop, Vloop1, Vloop2, VnumMappedPixels_1;

        VscatterStoreArray = scatterStoreArray_ptr;
        Vone = 0x00000001;
        Vseven = 0x00000007;
        Vshiftthree = -3;
        Vshiftone = 1;
        VnumMappedPixels_1   = max(VnumMappedPixels, Vone);
        VlutLoop = VnumMappedPixels_1 - Vone;
        Vloop2   = VnumMappedPixels_1 + Vseven;
        Vloop2   = Vloop2 << Vshiftthree;
        Vloop2   = Vloop2 - Vone;
        Vloop1   = VnumMappedPixels << Vshiftone;
        Vloop1   = Vloop1 + VscatterStoreArray;

        (pBlock16 + NUM_ITERATIONS_TLU_1_PTR)[Addr0].onept() = VlutLoop;
        (pBlock32 + NUM_ITERATIONS_LOOP_1_PTR)[Addr0].onept() = Vloop1;
        (pBlock16 + NUM_ITERATIONS_LOOP_2_PTR)[Addr0].onept() = Vloop2;
    }
}
