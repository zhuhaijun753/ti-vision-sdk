/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME                                                                 */
/*     vcop_nnInterpolate420SPchroma                                        */
/*                                                                          */
/*     REVISION HISTORY                                                     */
/*     2/22/12..............Initial Version........Victor Cheng             */
/*                                                                          */
/*     USAGE                                                                */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_nnInterpolate420SPchroma(                                  */
/*          __vptr_uint8        src,                                        */
/*          __vptr_uint8        dst,                                        */
/*          unsigned short      outputBlockSize,                            */
/*          __vptr_uint16       tluIndexArray,                              */
/*          long                sat_high,                                   */
/*          long                sat_high_set,                               */
/*          long                sat_low,                                    */
/*          long                sat_low_set                                 */
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
/* Tile Approach                                                                */
/*------------------------------------------------------------------------------*/
/* Compute the interpolated pixel for chroma of YUV420 format using nearest neighbor interpolation method */
void vcop_nnInterpolate420SPchroma(
        __vptr_uint8        src,
        __vptr_uint16       dst,
        unsigned short      numMappedPixels,
        __vptr_uint16       tluIndexArray,
        __vptr_uint16       scatterStoreArray,
        __vptr_uint8        scratchHbuf8b,
        __vptr_uint16       scratchHbuf16b,
        long                sat_high,
        long                sat_high_set,
        long                sat_low,
        long                sat_low_set,
        unsigned short      dst_end_offset
)
{
    /* Perform TLU */
    _LOOKUP(1,2);
    for (int I1 = 0; I1 < numMappedPixels; I1++) {
            __vector Vindex, Vdata;
            __agen TLU_agen = 0;
            __agen ind_agen = I1*2;
            __agen out_agen = I1*2*sizeof(*scratchHbuf8b);
            Vindex = tluIndexArray[ind_agen];
            Vdata = src[TLU_agen].lookup(Vindex);
            scratchHbuf8b[out_agen].table_npt() = Vdata.saturate(sat_low, sat_low_set, sat_high, sat_high_set);
    }

    for (int I1 = 0; I1 < 1; I1++) {
        __vector Voffset;
        __agen Addr0;
        Addr0 = 0;
        Voffset = dst_end_offset;

        (scatterStoreArray + 2*numMappedPixels)[Addr0] = Voffset;
    }

    /* Copy src into scratchHbuf so it is interleaved */
    for (int I1 = 0; I1 < ALIGN_SIMD(numMappedPixels)/(VCOP_SIMD_WIDTH); I1++) {

        __agen Addr1, Addr2, Addr_out;
        __vector srcUV, scatterStore;

        Addr1 = I1*VCOP_SIMD_WIDTH*sizeof(*scratchHbuf16b);
        Addr2 = I1*VCOP_SIMD_WIDTH*sizeof(*scatterStoreArray);
        Addr_out = 0;

        srcUV = scratchHbuf16b[Addr1].npt();
        scatterStore = scatterStoreArray[Addr2].npt();

        dst[Addr_out].s_scatter(scatterStore)= srcUV;
    }
}

/*------------------------------------------------------------------------------*/
/* Bounding Box Approach                                                        */
/*------------------------------------------------------------------------------*/
/* Compute the interpolated pixel for chroma of YUV420 format using nearest neighbor interpolation method */
void vcop_nnInterpolate420SPchromaBB(
        __vptr_uint8        src,
        __vptr_uint8        dst,
        unsigned short      outputBlockSize,
        __vptr_uint16       tluIndexArray,
        long                sat_high,
        long                sat_high_set,
        long                sat_low,
        long                sat_low_set
)
{
    /* Perform TLU */
    _LOOKUP(1,2);
    for (int I1 = 0; I1 < outputBlockSize; I1++) {
            __vector Vindex, Vdata;
            __agen TLU_agen = 0;
            __agen ind_agen = I1*2;
            __agen out_agen = I1*2*sizeof(*dst);
            Vindex = tluIndexArray[ind_agen];
            Vdata = src[TLU_agen].lookup(Vindex);
            dst[out_agen].table_npt() = Vdata.saturate(sat_low, sat_low_set, sat_high, sat_high_set);
    }
}
