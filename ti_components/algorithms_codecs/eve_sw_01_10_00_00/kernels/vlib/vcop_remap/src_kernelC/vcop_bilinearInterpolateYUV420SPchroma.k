/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME                                                                 */
/*     vcop_bilinearInterpolateYUV420SPchroma                               */
/*                                                                          */
/*     REVISION HISTORY                                                     */
/*     3/19/14..............Initial Version.......Saurabh Chandra           */
/*                                                                          */
/*     USAGE                                                                */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_bilinearInterpolateYUV420SPchroma(                         */
/*          __vptr_uint8        src,                                        */
/*          __vptr_uint8        dst,                                        */
/*          unsigned short      outputBlockSize,                            */
/*          __vptr_uint8        xFracArray,                                 */
/*          __vptr_uint8        yFracArray,                                 */
/*          __vptr_uint16       tluIndexArray,                              */
/*          __vptr_uint16       scratch,                                    */
/*          __vptr_uint8        scratchHbuf,                                */
/*          __vptr_uint16       stride_ptr,                                 */
/*          unsigned char       mnQShift,                                   */
/*          unsigned char       oQShift,                                    */
/*          unsigned short      qScale,                                     */
/*          unsigned char       mult,                                       */
/*          unsigned char       rightShift,                                 */
/*          long                sat_high,                                   */
/*          long                sat_high_set,                               */
/*          long                sat_low,                                    */
/*          long                sat_low_set                                 */
/*     )                                                                    */
/*                                                                          */
/*     Returns        :  None or void.                                      */
/*                                                                          */
/*                                                                          */
/*     DESCRIPTION                                                          */
/* pix00= *(src32 + tluIndexArray[i]);                                      */
/* pix00 * (qScale - xFrac)                                                 */
/* pix10= *(src32 + 1 + tluIndexArray[i]);                                  */
/*  compute pix10 * xFrac                                                   */
/*  m = pix00 * (qScale - xFrac) + pix10 * xFrac                            */
/*  compute m * (qScale - yFrac)                                            */
/*  pix01= *(src32 + src_stride + tluIndexArray[i])                         */
/*  compute pix01 * (qScale - xFrac)                                        */
/*  pix11= *(src32 + 1 + src_stride + tluIndexArray[i];                     */
/*  compute pix11 * xFrac                                                   */
/*  compute n = pix01 * (qScale - xFrac) + pix11 * xFrac;                   */
/*  compute n * yFrac;                                                      */
/*  compute final output o = m * (qScale - yFrac) + n * yFrac;              */
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
/* Compute the bilinear interpolated chroma pixels for YUV420 format */
void vcop_bilinearInterpolateYUV420SPchroma(
        __vptr_uint8        src,
        __vptr_uint8        dst,
        unsigned short      maxNumMappedPixels,
        unsigned short      numMappedPixels,
        __vptr_uint16       tluIndexArray,
        __vptr_uint8        xFracArray,
        __vptr_uint8        yFracArray,
        __vptr_uint16       scatterStoreArray,
        __vptr_uint8          scattered_ofst,
        __vptr_uint16       scratch,                  /* size: 4*2*ALIGN_2SIMD(outputBlockSize) bytes */
        __vptr_uint8        scratchHbuf,
        unsigned char       stride,
        unsigned char       mnQShift,
        unsigned char       oQShift,
        unsigned short      qScale,
        unsigned char       rightShift,
        unsigned short      src_size,
        long                sat_high,
        long                sat_high_set,
        long                sat_low,
        long                sat_low_set,
        unsigned short      dst_end_offset
)
{
/* Calculate the different indexes which will be used for TLU */
#define index00_ptr (scratch)
#define index01_ptr (scratch + sizeof(*scratch)*ALIGN_2SIMD(maxNumMappedPixels))

    __vector Vstride;
    __agen Addr0=0;
    Vstride= stride;

    for (int I1 = 0; I1 < ALIGN_2SIMD(numMappedPixels)/(2*VCOP_SIMD_WIDTH); I1++) {

        __agen Addr2;

        __vector index00_1,index00_2;               //Top-left pixel
        __vector index01_1,index01_2;               //Bottom-left pixel

        Addr2 = I1*2*VCOP_SIMD_WIDTH*sizeof(*tluIndexArray);

        (index00_1, index00_2) = tluIndexArray[Addr2].deinterleave();

        index01_1= index00_1 + Vstride;
        index01_2= index00_2 + Vstride;

        index00_ptr[Addr2].interleave() = (index00_1, index00_2);
        index01_ptr[Addr2].interleave() = (index01_1, index01_2);
    }

/* Perform TLU for pix00U, pix00V, pix10U, pix10U */
#define pix00_ptr scratchHbuf
    _LOOKUP(1,4);
    for (int I1 = 0; I1 < numMappedPixels; I1++) {
            __vector Vindex, Vdata;
            __agen TLU_agen = 0;
            __agen ind_agen = I1*2;
            __agen out_agen = I1*4*sizeof(*dst);
            Vindex = index00_ptr[ind_agen];
#if VCOP_HOST_EMULATION
            Vdata = src[TLU_agen].lookup(Vindex);
#else
            Vdata = src[TLU_agen].lookup(Vindex.saturate(0,src_size));
#endif
            pix00_ptr[out_agen].table_npt() = Vdata;
    }

/* Perform TLU for pix01U, pix01V, pix11U, pix11V */
#define pix01_ptr (scratchHbuf + sizeof(*dst)*4*maxNumMappedPixels)
    _LOOKUP(1,4);
    for (int I1 = 0; I1 < numMappedPixels; I1++) {
            __vector Vindex, Vdata;
            __agen TLU_agen = 0;
            __agen ind_agen = I1*2;
            __agen out_agen = I1*4*sizeof(*dst);
            Vindex = index01_ptr[ind_agen];
#if VCOP_HOST_EMULATION
            Vdata = src[TLU_agen].lookup(Vindex);
#else
            Vdata = src[TLU_agen].lookup(Vindex.saturate(0,src_size));
#endif
            pix01_ptr[out_agen].table_npt() = Vdata;
    }

    for (int I1 = 0; I1 < 1; I1++) {
        __vector Voffset;
        Voffset = dst_end_offset;

        (scatterStoreArray + 2*numMappedPixels)[Addr0] = Voffset;
    }

    __vector v_qScale, v_UVoffset;
    v_qScale= qScale;
    v_UVoffset=scattered_ofst[Addr0].npt();

/* pix00UV_1, pix00UV_2 will have 4 sets of pix00U, pix00V, pix10U, pix10V  */
/* pix01UV_1, pix01UV_2 will have 4 sets of pix01U, pix01V, pix11U, pix11V  */
/* deinterleave2() separates the 4 points (00, 10, 01, 11) for interpolation as below: */
/* pix00UV will have 4 sets of pix00U, pix00V                               */
/* pix10UV will have 4 sets of pix10U, pix10V                               */
/* pix01UV will have 4 sets of pix01U, pix01V                               */
/* pix11UV will have 4 sets of pix11U, pix11V                               */

    for (int I1 = 0; I1 < ALIGN_HALFSIMD(numMappedPixels)/4; I1++) {
        __vector temp1, temp2, xFrac, yFrac, qScale_xFrac, qScale_yFrac, scatterStore;
        __vector pix00UV_1, pix00UV_2, pix01UV_1, pix01UV_2, pix00UV, pix10UV, pix01UV, pix11UV;
        __agen Addr1, Addr2, Addr3, Addr_out;
        Addr1 = I1*4*sizeof(*xFracArray);
        Addr2 = I1*2*VCOP_SIMD_WIDTH*sizeof(*pix01_ptr);
        Addr3 = I1*4*sizeof(*scatterStoreArray);
        Addr_out = 0;

        xFrac= xFracArray[Addr1].us2();
        yFrac= yFracArray[Addr1].us2();
        scatterStore = scatterStoreArray[Addr3].us2();

        pix00UV_1= pix00_ptr[Addr2].npt();
        pix00UV_2= (pix00_ptr+VCOP_SIMD_WIDTH)[Addr2].npt();

        pix01UV_1= pix01_ptr[Addr2].npt();
        pix01UV_2= (pix01_ptr+VCOP_SIMD_WIDTH)[Addr2].npt();

        (pix00UV, pix10UV) = (pix00UV_1, pix00UV_2).deinterleave2();
        (pix01UV, pix11UV) = (pix01UV_1, pix01UV_2).deinterleave2();

        temp1= xFrac*pix10UV;
        temp2= xFrac*pix11UV;

        qScale_xFrac= v_qScale - xFrac;
        qScale_yFrac= v_qScale - yFrac;

        temp1+= qScale_xFrac*pix00UV;
        temp2+= qScale_xFrac*pix01UV;

        temp1= qScale_yFrac*temp1;
        temp2= yFrac*temp2;

        temp1= temp1 + temp2;
        scatterStore += v_UVoffset;
        dst[Addr_out].s_scatter(scatterStore)= temp1.round(mnQShift+oQShift).saturate(sat_low, sat_low_set, sat_high, sat_high_set);
    }
}

/*------------------------------------------------------------------------------*/
/* Bounding Box Approach                                                        */
/*------------------------------------------------------------------------------*/
/* Compute the bilinear interpolated luma pixels for YUV422 format */
void vcop_bilinearInterpolateYUV420SPchromaBB(
        __vptr_uint8        src,
        __vptr_uint8        dst,
        unsigned short      outputBlockSize,
        __vptr_uint8        xFracArray,
        __vptr_uint8        yFracArray,
        __vptr_uint16       tluIndexArray,
        __vptr_uint16       scratch,      /* size: 4*2*ALIGN_2SIMD(outputBlockSize) bytes */
        __vptr_uint8        scratchHbuf,
        __vptr_uint16       stride_ptr,
        unsigned char       mnQShift,
        unsigned char       oQShift,
        unsigned short      qScale,
        unsigned char       rightShift,
        long                sat_high,
        long                sat_high_set,
        long                sat_low,
        long                sat_low_set
)
{
/* Calculate the different indexes which will be used for TLU */
#define index00BB_ptr (scratch)
#define index01BB_ptr (scratch + sizeof(*scratch)*ALIGN_2SIMD(outputBlockSize))

    __vector Vstride;
    __agen Addr0=0;

    Vstride= stride_ptr[Addr0].onept();

    for (int I1 = 0; I1 < ALIGN_2SIMD(outputBlockSize)/(2*VCOP_SIMD_WIDTH); I1++) {

        __agen Addr2;

        __vector index00_1,index00_2;               //Top-left pixel
        __vector index01_1,index01_2;               //Bottom-left pixel

        Addr2 = I1*2*VCOP_SIMD_WIDTH*sizeof(*tluIndexArray);

        (index00_1, index00_2) = tluIndexArray[Addr2].deinterleave();

        index01_1= index00_1 + Vstride;
        index01_2= index00_2 + Vstride;

        index00BB_ptr[Addr2].interleave() = (index00_1, index00_2);
        index01BB_ptr[Addr2].interleave() = (index01_1, index01_2);
    }

/* Perform TLU for pix00U, pix00V, pix10U, pix10U */
#define pix00BB_ptr scratchHbuf
    _LOOKUP(1,4);
    for (int I1 = 0; I1 < outputBlockSize; I1++) {
            __vector Vindex, Vdata;
            __agen TLU_agen = 0;
            __agen ind_agen = I1*2;
            __agen out_agen = I1*4*sizeof(*dst);
            Vindex = index00BB_ptr[ind_agen];
            Vdata = src[TLU_agen].lookup(Vindex);
            pix00BB_ptr[out_agen].table_npt() = Vdata;
    }

/* Perform TLU for pix01U, pix01V, pix11U, pix11V */
#define pix01BB_ptr (scratchHbuf + sizeof(*dst)*4*outputBlockSize)
    _LOOKUP(1,4);
    for (int I1 = 0; I1 < outputBlockSize; I1++) {
            __vector Vindex, Vdata;
            __agen TLU_agen = 0;
            __agen ind_agen = I1*2;
            __agen out_agen = I1*4*sizeof(*dst);
            Vindex = index01BB_ptr[ind_agen];
            Vdata = src[TLU_agen].lookup(Vindex);
            pix01BB_ptr[out_agen].table_npt() = Vdata;
    }

    __vector v_qScale;
    v_qScale= qScale;

/* pix00UV_1, pix00UV_2 will have 4 sets of pix00U, pix00V, pix10U, pix10V  */
/* pix01UV_1, pix01UV_2 will have 4 sets of pix01U, pix01V, pix11U, pix11V  */
/* deinterleave2() separates the 4 points (00, 10, 01, 11) for interpolation as below: */
/* pix00UV will have 4 sets of pix00U, pix00V                               */
/* pix10UV will have 4 sets of pix10U, pix10V                               */
/* pix01UV will have 4 sets of pix01U, pix01V                               */
/* pix11UV will have 4 sets of pix11U, pix11V                               */

    for (int I1 = 0; I1 < ALIGN_SIMD(outputBlockSize)/4; I1++) {
        __vector temp1, temp2, xFrac, yFrac, qScale_xFrac, qScale_yFrac;
        __vector pix00UV_1, pix00UV_2, pix01UV_1, pix01UV_2, pix00UV, pix10UV, pix01UV, pix11UV;
        __agen Addr1, Addr2, Addr_out;
        Addr1 = I1*4*sizeof(*xFracArray);
        Addr2 = I1*2*VCOP_SIMD_WIDTH*sizeof(*pix01BB_ptr);
        Addr_out = I1*VCOP_SIMD_WIDTH*sizeof(*dst);

        xFrac= xFracArray[Addr1].us2();
        yFrac= yFracArray[Addr1].us2();

        pix00UV_1= pix00BB_ptr[Addr2].npt();
        pix00UV_2= (pix00BB_ptr+VCOP_SIMD_WIDTH)[Addr2].npt();

        pix01UV_1= pix01BB_ptr[Addr2].npt();
        pix01UV_2= (pix01BB_ptr+VCOP_SIMD_WIDTH)[Addr2].npt();

        (pix00UV, pix10UV) = (pix00UV_1, pix00UV_2).deinterleave2();
        (pix01UV, pix11UV) = (pix01UV_1, pix01UV_2).deinterleave2();

        temp1= xFrac*pix10UV;
        temp2= xFrac*pix11UV;

        qScale_xFrac= v_qScale - xFrac;
        qScale_yFrac= v_qScale - yFrac;

        temp1+= qScale_xFrac*pix00UV;
        temp2+= qScale_xFrac*pix01UV;

        temp1= qScale_yFrac*temp1;
        temp2= yFrac*temp2;

        temp1= temp1 + temp2;

        dst[Addr_out].npt()= temp1.round(mnQShift+oQShift).saturate(sat_low, sat_low_set, sat_high, sat_high_set);

    }
}
