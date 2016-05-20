/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME                                                                 */
/*     vcop_nnInterpolate422Ichroma                                         */
/*                                                                          */
/*     REVISION HISTORY                                                     */
/*     2/22/12..............Initial Version........Victor Cheng             */
/*                                                                          */
/*     USAGE                                                                */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_nnInterpolate422Ichroma(                                   */
/*          __vptr_uint8        src,                                        */
/*          __vptr_uint8        dst,                                        */
/*          unsigned short      outputBlockSize,                            */
/*          __vptr_uint8        xFracArray,                                 */
/*          __vptr_uint8        yFracArray,                                 */
/*          __vptr_uint16       tluIndexArray,                              */
/*          __vptr_uint16       scratch,                                    */
/*          __vptr_uint8        scratchHbuf,                                */
/*          __vptr_uint8        scattered_ofst,                             */
/*          __vptr_uint16       stride_ptr,                                 */
/*          unsigned char       mult,                                       */
/*          unsigned char       QShift,                                     */
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
/* Compute the interpolated pixel for chroma of YUV422 format using nearest neighbor interpolation method */
void vcop_nnInterpolate422Ichroma(
        __vptr_uint8        src,
        __vptr_uint8        dst,
        unsigned short      numMappedPixels,
        __vptr_uint16       tluIndexArray,
        __vptr_uint16       scatterStoreArray,
        __vptr_uint8        scratchHbuf,
        unsigned short      src_size,
        long                sat_high,
        long                sat_high_set,
        long                sat_low,
        long                sat_low_set
)
{
    /* Perform TLU */
    _LOOKUP(1,1);
    for (int I1 = 0; I1 < numMappedPixels; I1++) {
            __vector Vindex, Vdata;
            __agen TLU_agen = 0;
            __agen ind_agen = I1*2;
            __agen out_agen = I1*sizeof(*scratchHbuf);
            Vindex = tluIndexArray[ind_agen];
#if VCOP_HOST_EMULATION
            Vdata = src[TLU_agen].lookup(Vindex);
#else
            Vdata = src[TLU_agen].lookup(Vindex.saturate(0,src_size));
#endif
            scratchHbuf[out_agen].table_npt() = Vdata.saturate(sat_low, sat_low_set, sat_high, sat_high_set);
    }

    /* Copy src into scratchHbuf so it is interleaved */
    for (int I1 = 0; I1 < ALIGN_SIMD(numMappedPixels)/(VCOP_SIMD_WIDTH); I1++) {

        __agen Addr1, Addr2, Addr_out;
        __vector Vin1, scatterStore, Vone;
        Vone = 1;

        Addr1 = I1*VCOP_SIMD_WIDTH*sizeof(*scratchHbuf);
        Addr2 = I1*VCOP_SIMD_WIDTH*sizeof(*scatterStoreArray);
        Addr_out = 0;

        Vin1= scratchHbuf[Addr1].npt();
        scatterStore = scatterStoreArray[Addr2].npt();

        scatterStore = scatterStore << Vone;

        dst[Addr_out].s_scatter(scatterStore)= Vin1;

    }
}


/*------------------------------------------------------------------------------*/
/* Bounding Box Approach                                                        */
/*------------------------------------------------------------------------------*/
/* Compute the interpolated pixel for chroma of YUV422 format using nearest neighbor interpolation method */
void vcop_nnInterpolate422IchromaBB(
        __vptr_uint8        src,
        __vptr_uint8        dst,
        unsigned short      outputBlockSize,
        __vptr_uint16       tluIndexArray,
        __vptr_uint8        scratchHbuf,
        __vptr_uint8        scattered_ofst,
        long                sat_high,
        long                sat_high_set,
        long                sat_low,
        long                sat_low_set
)
{
    /* Perform TLU */
    _LOOKUP(1,1);
    for (int I1 = 0; I1 < outputBlockSize; I1++) {
            __vector Vindex, Vdata;
            __agen TLU_agen = 0;
            __agen ind_agen = I1*2;
            __agen out_agen = I1*sizeof(*dst);
            Vindex = tluIndexArray[ind_agen];
            Vdata = src[TLU_agen].lookup(Vindex);
            scratchHbuf[out_agen].table_npt() = Vdata.saturate(sat_low, sat_low_set, sat_high, sat_high_set);
    }

    __vector scat_ofst;
    __agen Addr0=0;
    scat_ofst= scattered_ofst[Addr0].npt();
    /* Copy src into scratchHbuf so it is interleaved */
    for (int I1 = 0; I1 < ALIGN_SIMD(outputBlockSize)/(VCOP_SIMD_WIDTH); I1++) {

        __agen Addr1, Addr2;
        __vector Vin1;

        Addr1 = I1*VCOP_SIMD_WIDTH*sizeof(*src);
        Addr2 = I1*4*VCOP_SIMD_WIDTH*sizeof(*src);

        Vin1= scratchHbuf[Addr1].npt();
        dst[Addr2].p_scatter(scat_ofst)= Vin1;

    }
}
