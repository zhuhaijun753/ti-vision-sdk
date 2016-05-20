/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME                                                                 */
/*     vcop_chromaTLUIndexCalcPblockUpdate                                  */
/*                                                                          */
/*     REVISION HISTORY                                                     */
/*     2/5/14..............Second Version........Saurabh Chandra            */
/*                                                                          */
/*     USAGE                                                                */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_chromaTLUIndexCalcPblockUpdate(                            */
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

/* Compute the bilinear interpolated luma pixels for U8BIT format */
void vcop_chromaTLUIndexCalcBilInterpolatePblockUpdate(
        __vptr_uint16       numMappedPixels_ptr,
        __vptr_uint16       pBlock16
)
{
#define NUM_ITERATIONS_LOOP_1_PTR (6)
        __vector VnumMappedPixels;
        __agen Addr0 = 0;

        VnumMappedPixels = numMappedPixels_ptr[Addr0].onept();

    for (int I1 = 0; I1 < 1; I1++) {

        __vector Vone, Vseven, Vshiftthree, Vloop1;

        Vone = 0x00000001;
        Vseven = 0x00000007;
        Vshiftthree = -3;

        VnumMappedPixels   = max(VnumMappedPixels, Vone);
        Vloop1   = VnumMappedPixels + Vseven;
        Vloop1   = Vloop1 << Vshiftthree;
        Vloop1   = Vloop1 - Vone;

        (pBlock16 + NUM_ITERATIONS_LOOP_1_PTR)[Addr0].onept()  = Vloop1;
    }
}

void vcop_chromaTLUIndexCalcNNInterpolatePblockUpdate(
        __vptr_uint16       numMappedPixels_ptr,
        __vptr_uint16       pBlock16
)
{
#define NUM_ITERATIONS_LOOP_1_PTR (6)
        __vector VnumMappedPixels;
        __agen Addr0 = 0;

        VnumMappedPixels = numMappedPixels_ptr[Addr0].onept();

    for (int I1 = 0; I1 < 1; I1++) {

        __vector Vone, Vfifteen, Vshiftfour, Vloop1;

        Vone = 0x00000001;
        Vfifteen = 0x0000000F;
        Vshiftfour = -4;

        VnumMappedPixels   = max(VnumMappedPixels, Vone);
        Vloop1   = VnumMappedPixels + Vfifteen;
        Vloop1   = Vloop1 << Vshiftfour;
        Vloop1   = Vloop1 - Vone;

        (pBlock16 + NUM_ITERATIONS_LOOP_1_PTR)[Addr0].onept()  = Vloop1;
    }
}
