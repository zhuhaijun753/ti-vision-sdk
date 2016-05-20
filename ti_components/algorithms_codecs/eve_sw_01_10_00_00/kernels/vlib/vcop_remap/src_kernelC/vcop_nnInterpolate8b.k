/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME                                                                 */
/*     vcop_nnInterpolate8b                                                 */
/*                                                                          */
/*     REVISION HISTORY                                                     */
/*     2/22/12..............Initial Version........Victor Cheng             */
/*                                                                          */
/*     USAGE                                                                */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_nnInterpolate8b(                                           */
/*             __vptr_uint8        src,                                     */
/*             __vptr_uint8        dst,                                     */
/*             unsigned short      outputBlockSize,                         */
/*             __vptr_uint16       tluIndexArray,                           */
/*             __vptr_uint16       scratch,                                 */
/*             __vptr_uint16       stride_ptr,                              */
/*             unsigned char       mult,                                    */
/*             unsigned char       QShift,                                  */
/*             long                sat_high,                                */
/*             long                sat_high_set,                            */
/*             long                sat_low,                                 */
/*             long                sat_low_set                              */
/*     )                                                                    */
/*                                                                          */
/*     Returns        :  None or void.                                      */
/*                                                                          */
/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
#if VCOP_HOST_EMULATION
#include <vcop.h>
#endif

#include "vcop_remap.h"

/*------------------------------------------------------------------------------*/
/* Bounding Box Approach                                                        */
/*------------------------------------------------------------------------------*/
/* Compute the interpolated pixel for luma using nearest neighbor interpolation method */
void vcop_nnInterpolate8b(
        __vptr_uint8        src,
        __vptr_uint8        dst,
        unsigned short      outputBlockSize,
        __vptr_uint16       tluIndexArray,
        __vptr_uint8        fracArray,
        __vptr_uint16       scratch,             /* size: 4*2*ALIGN_2SIMD(outputBlockSize) bytes */
        __vptr_uint16       stride_ptr,
        unsigned char       QShift,
        long                sat_high,
        long                sat_high_set,
        long                sat_low,
        long                sat_low_set
)
{

/* Calculate the different indexes which will be used for TLU */
#define index_ptr (scratch)

    __vector  Vstride, VQShift, negVQShift;
    __agen Addr0=0;

    negVQShift= -QShift;
    VQShift= QShift;
    Vstride= stride_ptr[Addr0].onept();

    for (int I1 = 0; I1 < ALIGN_2SIMD(outputBlockSize)/(2*VCOP_SIMD_WIDTH); I1++) {

        __agen Addr1, Addr2;

        __vector yFrac1, yFrac2, roundedYFrac1, roundedYFrac2;
        __vector tluIndex1, tluIndex2;
        __vector fracMap1, fracMap2;
        __vector Vmaskx;
        __vector Vshifty;

        Vmaskx = 0x000000000F;
        Vshifty = -4;

        Addr1 = I1*2*VCOP_SIMD_WIDTH*sizeof(*fracArray);
        Addr2 = I1*2*VCOP_SIMD_WIDTH*sizeof(*tluIndexArray);

        (tluIndex1, tluIndex2) = tluIndexArray[Addr2].deinterleave();
        (fracMap1, fracMap2) = fracArray[Addr1].deinterleave();

        yFrac1 = fracMap1 << Vshifty;
        yFrac2 = fracMap2 << Vshifty;

        roundedYFrac1= round(yFrac1, VQShift);
        roundedYFrac2= round(yFrac2, VQShift);

        tluIndex1+= roundedYFrac1*Vstride;
        tluIndex2+= roundedYFrac2*Vstride;

        index_ptr[Addr2].interleave() = (tluIndex1, tluIndex2);
    }

    /* Perform TLU */
    _LOOKUP(1,1);
    for (int I1 = 0; I1 < outputBlockSize; I1++) {
            __vector Vindex, Vdata;
            __agen TLU_agen = 0;
            __agen ind_agen = I1*2;
            __agen out_agen = I1*sizeof(*dst);
            Vindex = index_ptr[ind_agen];
            Vdata = src[TLU_agen].lookup(Vindex);
            dst[out_agen].table_npt() = Vdata.saturate(sat_low, sat_low_set, sat_high, sat_high_set);
    }
}
