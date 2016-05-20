/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME                                                                 */
/*     vcop_bilinearInterpolateYUV420SPchromaPblockUpdate                   */
/*                                                                          */
/*     REVISION HISTORY                                                     */
/*     2/5/14..............Second Version........Saurabh Chandra            */
/*                                                                          */
/*     USAGE                                                                */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_bilinearInterpolateYUV420SPchromaPblockUpdate(             */
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
void vcop_bilinearInterpolateYUV420SPchromaPblockUpdate(
        __vptr_uint16       numMappedPixels_ptr,
        __vptr_uint16       pBlock16,
        unsigned int        scatterStoreArray_ptr,
        __vptr_uint32       pBlock32
)
{
#define NUM_ITERATIONS_LOOP_1_PTR (6)
#define NUM_ITERATIONS_TLU_1_PTR  (34)
#define NUM_ITERATIONS_TLU_2_PTR  (70)
#define NUM_ITERATIONS_LOOP_2_PTR (112)
#define NUM_ITERATIONS_LOOP_3_PTR (122)
        __vector VnumMappedPixels;
        __agen Addr0 = 0;

        VnumMappedPixels = numMappedPixels_ptr[Addr0].onept();

    for (int I1 = 0; I1 < 1; I1++) {

        __vector Vone, VscatterStoreArray, Vfifteen, Vshiftfour, Vthree, Vshifttwo, Vshiftone, VlutLoop, Vloop1, Vloop5, Vloop4, VnumMappedPixels_1;

        VscatterStoreArray = scatterStoreArray_ptr;
        Vone = 0x00000001;
        Vfifteen = 0x0000000F;
        Vshiftfour = -4;
        Vthree = 0x00000003;
        Vshifttwo = -2;
        Vshiftone = 1;

        VnumMappedPixels_1   = max(VnumMappedPixels, Vone);
        VlutLoop = VnumMappedPixels_1 - Vone;
        Vloop1   = VnumMappedPixels_1 + Vfifteen;
        Vloop1   = Vloop1 << Vshiftfour;
        Vloop1   = Vloop1 - Vone;
        Vloop5   = VnumMappedPixels_1 + Vthree;
        Vloop5   = Vloop5 << Vshifttwo;
        Vloop5   = Vloop5 - Vone;
        Vloop4   = VnumMappedPixels << Vshiftone;
        Vloop4   = Vloop4 + VscatterStoreArray;

        (pBlock16 + NUM_ITERATIONS_LOOP_1_PTR)[Addr0].onept()  = Vloop1;
        (pBlock16 + NUM_ITERATIONS_TLU_1_PTR)[Addr0].onept() = VlutLoop;
        (pBlock16 + NUM_ITERATIONS_TLU_2_PTR)[Addr0].onept() = VlutLoop;
        (pBlock32 + NUM_ITERATIONS_LOOP_2_PTR)[Addr0].onept() = Vloop4;
        (pBlock16 + NUM_ITERATIONS_LOOP_3_PTR)[Addr0].onept() = Vloop5;
    }
}
