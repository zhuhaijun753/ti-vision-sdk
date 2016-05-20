/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME                                                                 */
/*     vcop_bilinearInterpolate8b                                           */
/*                                                                          */
/*     REVISION HISTORY                                                     */
/*     2/22/12..............Initial Version........Victor Cheng             */
/*     12/2/13..............Second Version........Saurabh Chandra           */
/*                                                                          */
/*     USAGE                                                                */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_bilinearInterpolate8b(                                     */
/*           __vptr_uint8        src,                                       */
/*           __vptr_uint8        dst,                                       */
/*           unsigned short      maxNumMappedPixels,                        */
/*           unsigned short      numMappedPixels,                           */
/*           __vptr_uint16       tluIndexArray,                             */
/*           __vptr_uint8        fracArray,                                 */
/*           __vptr_uint16       scatterStoreArray,                         */
/*           __vptr_uint16       scratchLUT,                                */
/*           __vptr_uint8        scratchPixel,                              */
/*           __vptr_uint16       stride_ptr,                                */
/*           unsigned char       mnQShift,                                  */
/*           unsigned char       oQShift,                                   */
/*           unsigned short      qScale,                                    */
/*           unsigned char       rightShift,                                */
/*           long                sat_high,                                  */
/*           long                sat_high_set,                              */
/*           long                sat_low,                                   */
/*           long                sat_low_set,                               */
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

/* Compute the bilinear interpolated luma pixels for U8BIT format */
/*------------------------------------------------------------------------------*/
/* Tile and Bounding Box Approach                                               */
/*------------------------------------------------------------------------------*/
void vcop_bilinearInterpolate8b(
        __vptr_uint8        src,
        __vptr_uint8        dst,
        unsigned short      maxNumMappedPixels,
        unsigned short      numMappedPixels,
        __vptr_uint16       tluIndexArray,
        __vptr_uint8        fracArray,
        __vptr_uint16       scatterStoreArray,
        __vptr_uint16       scratchLUT,                  /* size: 4*2*ALIGN_2SIMD(outputBlockSize) bytes */
        __vptr_uint8        scratchPixel,
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
#define index00_ptr (scratchLUT)
#define index01_ptr (scratchLUT + sizeof(*scratchLUT)*ALIGN_2SIMD(maxNumMappedPixels))

    __vector Vstride;
    __agen Addr0=0;

    Vstride= stride_ptr[Addr0].onept();

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


/* Perform TLU for pix00, pix10 */
#define pix00_ptr scratchPixel
    _LOOKUP(1,2);
    for (int I1 = 0; I1 < numMappedPixels; I1++) {
            __vector Vindex, Vdata;
            __agen TLU_agen = 0;
            __agen ind_agen = I1*2;
            __agen out_agen = I1*2*sizeof(*dst);
            Vindex = index00_ptr[ind_agen];
            Vdata = src[TLU_agen].lookup(Vindex);
            pix00_ptr[out_agen].table_npt() = Vdata;
    }

/* Perform TLU for pix01, pix11 */
#define pix01_ptr (scratchPixel + sizeof(*dst)*2*maxNumMappedPixels)
    _LOOKUP(1,2);
    for (int I1 = 0; I1 < numMappedPixels; I1++) {
            __vector Vindex, Vdata;
            __agen TLU_agen = 0;
            __agen ind_agen = I1*2;
            __agen out_agen = I1*2*sizeof(*dst);
            Vindex = index01_ptr[ind_agen];
            Vdata = src[TLU_agen].lookup(Vindex);
            pix01_ptr[out_agen].table_npt() = Vdata;
    }

    __vector v_qScale;
    v_qScale= qScale;

    for (int I1 = 0; I1 < ALIGN_SIMD(numMappedPixels)/VCOP_SIMD_WIDTH; I1++) {
        __vector temp1, temp2, xFrac, yFrac, qScale_xFrac, qScale_yFrac, pix00, pix10, pix01, pix11, fracMap, scatterStore;
        __agen Addr1, Addr2, Addr3, Addr_out;
        __vector Vmaskx;
        __vector Vshifty;

        Vmaskx = 0x000000000F;
        Vshifty = -4;

        Addr1 = I1*VCOP_SIMD_WIDTH*sizeof(*fracArray);
        Addr2 = I1*2*VCOP_SIMD_WIDTH*sizeof(*pix01_ptr);
        Addr3 = I1*VCOP_SIMD_WIDTH*sizeof(*scatterStoreArray);
        Addr_out = 0;

        fracMap = fracArray[Addr1].npt();
        scatterStore = scatterStoreArray[Addr3].npt();

        (pix00, pix10)= pix00_ptr[Addr2].deinterleave();
        (pix01, pix11)= pix01_ptr[Addr2].deinterleave();

        xFrac = fracMap & Vmaskx;
        yFrac = fracMap << Vshifty;

        temp1= xFrac*pix10;
        temp2= xFrac*pix11;

        qScale_xFrac= v_qScale - xFrac;
        qScale_yFrac= v_qScale - yFrac;

        temp1+= qScale_xFrac*pix00;
        temp2+= qScale_xFrac*pix01;

        temp1= qScale_yFrac*temp1;
        temp2= yFrac*temp2;

        temp1= temp1 + temp2;

        dst[Addr_out].s_scatter(scatterStore)= temp1.round(mnQShift+oQShift).saturate(sat_low, sat_low_set, sat_high, sat_high_set);
    }
}


void vcop_bilinearInterpolate8b_highSpeed(
        __vptr_uint8        src,
        __vptr_uint8        dst,
        unsigned short      outputBlockSize,
        __vptr_uint16       tluIndexArray,
        __vptr_uint8        fracArray,
        __vptr_uint16       scratch,                  /* size: 4*2*ALIGN_2SIMD(outputBlockSize) bytes */
        __vptr_uint8        scratchHbuf,
        unsigned short      stride,
        unsigned int        inSize,
         __vptr_uint8        inLUT,
       unsigned char       mnQShift,
        unsigned char       oQShift,
        unsigned short      qScale,
        unsigned char       mult,
        unsigned char       rightShift,
        long                sat_high,
        long                sat_high_set,
        long                sat_low,
        long                sat_low_set
)
{
    __agen Addr0=0;
    __agen Addr1,Addr2;
    __vector in_0,in_1;               //Top-left pixel
    __vector in_2,in_3;               //Top-left pixel
   __vector first_0,first_1;               //Top-left pixel

    for (int I2 = 0; I2 < ALIGN_2SIMD(inSize)/(2*VCOP_SIMD_WIDTH); I2++)
    {

      Addr1 = I2*4*VCOP_SIMD_WIDTH;
      Addr2 = I2*2*VCOP_SIMD_WIDTH;

      (in_0, in_1) = (src)[Addr2].deinterleave();
      (in_2, in_3) = (src+stride)[Addr2].deinterleave();

      (inLUT)[Addr1].interleave() = (in_0, in_1);
      (inLUT + 16)[Addr1].interleave() = (in_2, in_3);
    }

    _LOOKUP(2,2);
    for (int I1 = 0; I1 < outputBlockSize; I1++)
    {
            __vector Vindex, Vdata;
            __agen TLU_agen = 0;
            __agen ind_agen = I1*2;
            __agen out_agen = I1*4*sizeof(*dst);
            Vindex = tluIndexArray[ind_agen].onept();
            Vdata = inLUT[TLU_agen].lookup(Vindex);
            scratchHbuf[out_agen].table_npt() = Vdata;
    }

    __vector v_qScale;
    v_qScale= qScale;

    for (int I1 = 0; I1 < ALIGN_SIMD(outputBlockSize)/VCOP_SIMD_WIDTH; I1++)
    {
        __vector temp1, temp2, xFrac, yFrac, qScale_xFrac, qScale_yFrac, pix00, pix10, pix01, pix11, fracMap;
        __agen Addr_out;
        __vector Vmaskx;
        __vector Vmasky;
        __vector Vshiftx;
        __vector Vshifty;

        Vmaskx = 0x000000000F;
        Vshifty = -4;

        Addr1     = I1*VCOP_SIMD_WIDTH*sizeof(*fracArray);
        Addr2     = I1*4*VCOP_SIMD_WIDTH*sizeof(*scratchHbuf);
        Addr_out  = I1*VCOP_SIMD_WIDTH*sizeof(*dst);

        fracMap = fracArray[Addr1].npt();
        (in_0, in_1) = scratchHbuf[Addr2].deinterleave(); //in_0 --> TL BL (of 0-3 ouput points) ; in_1 --> TR BR ((of 0-3 ouput points)
        (in_2, in_3) = (scratchHbuf+16)[Addr2].deinterleave();//in_2 --> TL BL(of 4-7 ouput points) ; in_3 --> TR BR ((of 4-7 ouput points)

        // TL BL
        // TR BR
        (pix00,pix01) = (in_0,in_2).deinterleave();
        (pix10,pix11) = (in_1,in_3).deinterleave();

        xFrac = fracMap & Vmaskx;
        yFrac = fracMap << Vshifty;

        temp1= xFrac*pix10;
        temp2= xFrac*pix11;

        qScale_xFrac= v_qScale - xFrac;
        qScale_yFrac= v_qScale - yFrac;

        temp1+= qScale_xFrac*pix00;
        temp2+= qScale_xFrac*pix01;

        temp1= qScale_yFrac*temp1;
        temp2= yFrac*temp2;

        temp1= temp1 + temp2;

        dst[Addr_out].npt()= temp1.round(mnQShift+oQShift).saturate(sat_low, sat_low_set, sat_high, sat_high_set);
    }
}


