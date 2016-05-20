/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME                                                                 */
/*     vcop_dsTLUindexAndFracPblockUpdate                                   */
/*                                                                          */
/*     REVISION HISTORY                                                     */
/*     2/5/14..............Second Version........Saurabh Chandra            */
/*                                                                          */
/*     USAGE                                                                */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_dsTLUindexAndFracPblockUpdate(                             */
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
void vcop_dsTLUindexAndFracBilInterpolatePblockUpdate(
        __vptr_uint16       numMappedPixels_ptr,
        __vptr_uint16       numEvenMappedPixels_ptr,
        __vptr_uint16       pBlock16,
        unsigned int        tluIndexArray_ptr,
        unsigned int        fracArray_ptr,
        __vptr_uint32       pBlock32
)
{
#define NUM_ITERATIONS_LOOP_1_PTR (6)
#define NUM_ITERATIONS_LOOP_2_PTR (78)
#define ODD_TLUINDEX_PTR  (96)
#define ODD_TLUINDEX1_PTR (100)
#define ODD_FRAC_PTR      (104)
#define ODD_FRAC1_PTR     (108)

        __vector VnumMappedPixels, VnumEvenMappedPixels, VnumOddMappedPixels;
        __agen Addr0 = 0;

        VnumMappedPixels = numMappedPixels_ptr[Addr0].onept();
        VnumEvenMappedPixels = numEvenMappedPixels_ptr[Addr0].onept();

    for (int I1 = 0; I1 < 1; I1++) {

        __vector Vone, VtluIndexArray, VOddtluIndexArray, VOddtluIndexArrayNext, Vfifteen, Vshiftfour, Vshiftone, Vloop1, Vloop2, VfracArray, VOddfracArray, VOddfracArrayNext;
        __vector Veight, Vsixteen;

        VtluIndexArray = tluIndexArray_ptr;
        VfracArray = fracArray_ptr;
        Vone = 0x00000001;
        Vfifteen = 0x0000000F;
        Vshiftfour = -4;
        Vsixteen = 16;
        Vshiftone = 1;
        Veight = 8;

        VnumOddMappedPixels = VnumMappedPixels - VnumEvenMappedPixels;

        Vloop1   = VnumEvenMappedPixels + Vfifteen;
        Vloop1   = Vloop1 << Vshiftfour;
        Vloop1   = max(Vloop1, Vone);
        Vloop1   = Vloop1 - Vone;
        Vloop2   = VnumOddMappedPixels + Vfifteen;
        Vloop2   = Vloop2 << Vshiftfour;
        Vloop2   = max(Vloop2, Vone);
        Vloop2   = Vloop2 - Vone;

        VOddtluIndexArray   = VnumEvenMappedPixels << Vshiftone;
        VOddtluIndexArray   = VOddtluIndexArray + VtluIndexArray;
        VOddtluIndexArrayNext = VOddtluIndexArray + Vsixteen;

        VOddfracArray   = VnumEvenMappedPixels + VfracArray;
        VOddfracArrayNext = VOddfracArray + Veight;

        (pBlock16 + NUM_ITERATIONS_LOOP_1_PTR)[Addr0].onept() = Vloop1;
        (pBlock16 + NUM_ITERATIONS_LOOP_2_PTR)[Addr0].onept() = Vloop2;
        (pBlock32 + ODD_TLUINDEX_PTR)[Addr0].onept() = VOddtluIndexArray;
        (pBlock32 + ODD_TLUINDEX1_PTR)[Addr0].onept() = VOddtluIndexArrayNext;
        (pBlock32 + ODD_FRAC_PTR)[Addr0].onept() = VOddfracArray;
        (pBlock32 + ODD_FRAC1_PTR)[Addr0].onept() = VOddfracArrayNext;

    }
}

void vcop_dsTLUindexAndFracNNInterpolatePblockUpdate(
        __vptr_uint16       numMappedPixels_ptr,
        __vptr_uint16       numEvenMappedPixels_ptr,
        __vptr_uint16       pBlock16,
        unsigned int        tluIndexArray_ptr,
        unsigned int        fracArray_ptr,
        __vptr_uint32       pBlock32
)
{
#define NUM_ITERATIONS_LOOP_1_NN_PTR (6)
#define NUM_ITERATIONS_LOOP_2_NN_PTR (62)
#define ODD_TLUINDEX_NN_PTR  (88)
#define ODD_TLUINDEX1_NN_PTR (92)
#define ODD_FRAC_NN_PTR      (68)
#define ODD_FRAC1_NN_PTR     (72)

        __vector VnumMappedPixels, VnumEvenMappedPixels, VnumOddMappedPixels;
        __agen Addr0 = 0;

        VnumMappedPixels = numMappedPixels_ptr[Addr0].onept();
        VnumEvenMappedPixels = numEvenMappedPixels_ptr[Addr0].onept();

    for (int I1 = 0; I1 < 1; I1++) {

        __vector Vone, VtluIndexArray, VOddtluIndexArray, VOddtluIndexArrayNext, Vfifteen, Vshiftfour, Vshiftone, Vloop1, Vloop2, VfracArray, VOddfracArray, VOddfracArrayNext;
        __vector Veight, Vsixteen;

        VtluIndexArray = tluIndexArray_ptr;
        VfracArray = fracArray_ptr;
        Vone = 0x00000001;
        Vfifteen = 0x0000000F;
        Vshiftfour = -4;
        Vsixteen = 16;
        Vshiftone = 1;
        Veight = 8;

        VnumOddMappedPixels = VnumMappedPixels - VnumEvenMappedPixels;

        Vloop1   = VnumEvenMappedPixels + Vfifteen;
        Vloop1   = Vloop1 << Vshiftfour;
        Vloop1   = max(Vloop1, Vone);
        Vloop1   = Vloop1 - Vone;
        Vloop2   = VnumOddMappedPixels + Vfifteen;
        Vloop2   = Vloop2 << Vshiftfour;
        Vloop2   = max(Vloop2, Vone);
        Vloop2   = Vloop2 - Vone;

        VOddtluIndexArray   = VnumEvenMappedPixels << Vshiftone;
        VOddtluIndexArray   = VOddtluIndexArray + VtluIndexArray;
        VOddtluIndexArrayNext = VOddtluIndexArray + Vsixteen;

        VOddfracArray   = VnumEvenMappedPixels + VfracArray;
        VOddfracArrayNext = VOddfracArray + Veight;

        (pBlock16 + NUM_ITERATIONS_LOOP_1_NN_PTR)[Addr0].onept() = Vloop1;
        (pBlock16 + NUM_ITERATIONS_LOOP_2_NN_PTR)[Addr0].onept() = Vloop2;
        (pBlock32 + ODD_TLUINDEX_NN_PTR)[Addr0].onept() = VOddtluIndexArray;
        (pBlock32 + ODD_TLUINDEX1_NN_PTR)[Addr0].onept() = VOddtluIndexArrayNext;
        (pBlock32 + ODD_FRAC_NN_PTR)[Addr0].onept() = VOddfracArray;
        (pBlock32 + ODD_FRAC1_NN_PTR)[Addr0].onept() = VOddfracArrayNext;

    }
}

