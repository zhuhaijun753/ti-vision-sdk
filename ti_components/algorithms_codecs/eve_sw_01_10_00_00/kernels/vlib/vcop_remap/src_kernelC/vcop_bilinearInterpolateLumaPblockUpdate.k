/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME                                                                 */
/*     vcop_bilinearInterpolateLumaPblockUpdate                             */
/*                                                                          */
/*     REVISION HISTORY                                                     */
/*     2/5/14..............Second Version........Saurabh Chandra            */
/*                                                                          */
/*     USAGE                                                                */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_bilinearInterpolateLumaPblockUpdate(                       */
/*             __vptr_uint16       numMappedPixels_ptr,                     */
/*             __vptr_uint16       pBlock16,                                */
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

/* Modify the Param Block of any of the Luma Bilinear Interpolation kernels. */
/* like vcop_bilinearInterpolate8b.k, vcop_bilinearInterpolate16b.k, vcop_bilinearInterpolateYUV422Iluma.k kernel */

void vcop_bilinearInterpolateLumaPblockUpdate(
        __vptr_uint16       numMappedPixels_ptr,
        __vptr_uint16       pBlock16
)
{
#define NUM_ITERATIONS_LOOP_1_PTR (6)
#define NUM_ITERATIONS_TLU_1_PTR  (34)
#define NUM_ITERATIONS_TLU_2_PTR  (58)
#define NUM_ITERATIONS_LOOP_3_PTR (82)
        __vector VnumMappedPixels;
        __agen Addr0 = 0;

        VnumMappedPixels = numMappedPixels_ptr[Addr0].onept();

    for (int I1 = 0; I1 < 1; I1++) {

        __vector Vone, Vfifteen, Vshiftfour, Vseven, Vshiftthree, VlutLoop, Vloop1, Vloop5 ;

        Vone = 0x00000001;
        Vfifteen = 0x0000000F;
        Vshiftfour = -4;
        Vseven = 0x00000007;
        Vshiftthree = -3;

        VlutLoop = VnumMappedPixels - Vone;
        Vloop1   = VnumMappedPixels + Vfifteen;
        Vloop1   = Vloop1 << Vshiftfour;
        Vloop1   = Vloop1 - Vone;
        Vloop5   = VnumMappedPixels + Vseven;
        Vloop5   = Vloop5 << Vshiftthree;
        Vloop5   = Vloop5 - Vone;

        (pBlock16 + NUM_ITERATIONS_LOOP_1_PTR)[Addr0].onept()  = Vloop1;
        (pBlock16 + NUM_ITERATIONS_TLU_1_PTR)[Addr0].onept() = VlutLoop;
        (pBlock16 + NUM_ITERATIONS_TLU_2_PTR)[Addr0].onept() = VlutLoop;
        (pBlock16 + NUM_ITERATIONS_LOOP_3_PTR)[Addr0].onept() = Vloop5;
    }
}
