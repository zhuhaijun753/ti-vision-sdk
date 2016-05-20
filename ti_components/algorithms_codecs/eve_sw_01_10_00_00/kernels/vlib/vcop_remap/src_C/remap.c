/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*                                                                          */
/*     @file : remap.c                                                      */
/*                                                                          */
/*     @brief : This file contains C reference implementation for remap     */
/*              kernel                                                      */
/*                                                                          */
/*                                                                          */
/*     @author Venkat R Peddigari (a0393744@ti.com)                         */
/*                                                                          */
/*     @version 1.0 (October 2013) : Base version.                          */
/*                                                                          */
/*==========================================================================*/

/* Include the lib interface header files */
#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include "remap.h"
#include "remap_common.h"
#include "vcop_remap.h"


#define LUMA_INDEX (0)
#define CHROMA_INDEX (1)

static uint8_t tempBuf[32*1024*4*2] = {0};

//#define LOGIC_2 (1)

/* Bilinear interpolation */
static void _natc_bilinearInterpolate(
         int32_t *src32, uint8_t *dst, uint16_t numMappedPixels, uint16_t *tluIndexArray, uint8_t *tluFracArray, \
         uint16_t *scatterOffset, uint16_t src_stride, Format dstFormat, uint8_t chroma, uint8_t mnQShift, uint8_t oQShift,
         uint16_t qScale, uint8_t *scratchPtr, RemapParms *params){

    uint16_t i;
    int32_t *pix00, *pix01, *pix10, *pix11;
    int32_t mult, temp, o;
    uint8_t *qScale_xFracPtr, *qScale_yFracPtr;
    uint16_t *m, *n;
    uint8_t maskx = 0x0F;
    uint8_t shifty = 4;

    qScale_xFracPtr= scratchPtr;
    qScale_yFracPtr= qScale_xFracPtr + numMappedPixels;
    m= (uint16_t*)(qScale_yFracPtr + numMappedPixels);
    n= m + numMappedPixels;
    pix00= (int32_t*)(n + numMappedPixels);
    pix10= pix00 + numMappedPixels;
    pix01= pix00;
    pix11= pix10;

    mult = 1;

    if(chroma == CHROMA_INDEX) {

        /* mult = 2 is needed for 420 Chroma as U and V are interleaved */
        if (dstFormat == YUV_420SP) {
            mult = 2;
        }
        /* stride is half for 422 Chroma as U and V are de-interleaved */
        if (dstFormat== YUV_422ILE || dstFormat== YUV_422IBE) {
            src_stride = src_stride/2;
        }
    }

    for (i=0; i < numMappedPixels; i++)
        qScale_xFracPtr[i] = qScale - (tluFracArray[i] & maskx);

    for (i=0; i < numMappedPixels; i++)
        qScale_yFracPtr[i] = qScale - (tluFracArray[i] >> shifty);

    /* pix00= *(src32 + tluIndexArray[i]); */
    for (i=0; i < numMappedPixels; i++)
        pix00[i]= *(src32 + tluIndexArray[i]);

    /* compute pix00 * (qScale - xFrac) */
    for (i=0; i < numMappedPixels; i++)
        pix00[i]= pix00[i]*qScale_xFracPtr[i];

    /* pix10= *(src32 + 1 + tluIndexArray[i]); */
    for (i=0; i < numMappedPixels; i++)
        pix10[i]= *(src32 + (mult*1 + tluIndexArray[i]));

    /* compute pix10 * xFrac */
    for (i=0; i < numMappedPixels; i++)
        pix10[i]= pix10[i]*(tluFracArray[i] & maskx);

    /* compute m = pix00 * (qScale - xFrac) + pix10 * xFrac */
    for (i=0; i < numMappedPixels; i++){
        temp= pix00[i] + pix10[i];
        temp= (temp + (1<<(mnQShift-1))) >> mnQShift;
        if (temp >= 65535) {
            temp= 65535;
        }
        m[i]= (uint16_t)temp;
    }

    /* compute m * (qScale - yFrac) */
    for (i=0; i < numMappedPixels; i++) {
        temp= m[i] * qScale_yFracPtr[i];
        if (temp >= 65535) {
            temp= 65535;
        }
        m[i]= (uint16_t)temp;
    }

    /* pix01= *(src32 + src_stride + tluIndexArray[i]) */
    for (i=0; i < numMappedPixels; i++)
        pix01[i]= *(src32 + (src_stride + tluIndexArray[i]));

    /* compute pix01 * (qScale - xFrac) */
    for (i=0; i < numMappedPixels; i++)
        pix01[i]= pix01[i]*qScale_xFracPtr[i];

    /* pix11= *(src32 + 1 + src_stride + tluIndexArray[i]; */
    for (i=0; i < numMappedPixels; i++)
        pix11[i]= *(src32 + (mult*1 + src_stride + tluIndexArray[i]));

    /* compute pix11 * xFrac */
    for (i=0; i < numMappedPixels; i++)
        pix11[i]= pix11[i]*(tluFracArray[i] & maskx);

    /* compute n = pix01 * (qScale - xFrac) + pix11 * xFrac; */
    for (i=0; i < numMappedPixels; i++){
        temp= pix01[i] + pix11[i];
        temp= (temp + (1<<(mnQShift-1))) >> mnQShift;
        if (temp >= 65535) {
            temp= 65535;
        }
        n[i]= temp;
    }

    /* compute n * yFrac; */
    for (i=0; i < numMappedPixels; i++) {
        temp= n[i] * (tluFracArray[i] >> shifty);
        if (temp >= 65535) {
            temp= 65535;
        }
        n[i]= temp;
    }

    /* compute final output o = m * (qScale - yFrac) + n * yFrac; */
    for (i=0; i < numMappedPixels; i++){
        o = m[i] + n[i];
        o= (o  + (1<<(params->rightShift + oQShift-1)))>> (params->rightShift + oQShift);
        if (o >= params->sat_high)
            o= params->sat_high_set;
        else if (o < params->sat_low)
            o= params->sat_low_set;

#if INPUTTILE
    if (chroma== 0) {
        if (dstFormat== S8BIT)
            *((int8_t*)dst + scatterOffset[i]) = (int8_t)o;
        else if (dstFormat== U8BIT)
            *((uint8_t*)dst + scatterOffset[i]) = (uint8_t)o;
        else if (dstFormat== S16BIT)
            *((int16_t*)dst + scatterOffset[i]) = (int16_t)o;
        else if (dstFormat== U16BIT)
            *((uint16_t*)dst + scatterOffset[i]) = (uint16_t)o;
        else if (dstFormat== YUV_422ILE)
            *((uint8_t*)dst + 2*scatterOffset[i]) = (uint8_t)o;
        else if (dstFormat== YUV_422IBE)
            *((uint8_t*)dst + 2*scatterOffset[i]) = (uint8_t)o;
    }
    else {
        if (dstFormat== YUV_422ILE || dstFormat== YUV_422IBE)
            *((uint8_t*)dst + 2*scatterOffset[i]) = (uint8_t)o;
        else
            *((uint8_t*)dst + scatterOffset[i]) = (uint8_t)o;
    }

#else
        if (chroma== 0) {
            if (dstFormat== S8BIT)
                *((int8_t*)dst + i) = (int8_t)o;
            else if (dstFormat== U8BIT)
                *((uint8_t*)dst + i) = (uint8_t)o;
            else if (dstFormat== S16BIT)
                *((int16_t*)dst + i) = (int16_t)o;
            else if (dstFormat== U16BIT)
                *((uint16_t*)dst + i) = (uint16_t)o;
            else if (dstFormat== YUV_422ILE)
                *((uint8_t*)dst + 2*i) = (uint8_t)o;
            else if (dstFormat== YUV_422IBE)
                *((uint8_t*)dst + 2*i) = (uint8_t)o;
        }
        else {
            if (dstFormat== YUV_422ILE || dstFormat== YUV_422IBE)
                *((uint8_t*)dst + 4*i) = (uint8_t)o;
            else
                *((uint8_t*)dst + 2*i) = (uint8_t)o;
        }
#endif
    }

}

/* Nearest neighbour */
static void _natc_nnInterpolate(int32_t *src32, uint8_t *dst, uint16_t numMappedPixels,
        uint16_t *tluIndexArray, uint8_t *tluFracArray, uint16_t *scatterOffset, \
        uint16_t src_stride, Format dstFormat, uint8_t chroma, uint8_t QShift, uint8_t *scratchPtr, RemapParms *params){

    uint16_t i;
    int32_t o;
    uint8_t *roundedXFracArray, *roundedYFracArray;
    uint16_t *tluIndexArrayNN;
    uint8_t maskx = 0x0F;
    uint8_t shifty = 4;
    uint8_t mult;

    mult = 1;

    if(chroma == CHROMA_INDEX) {

        /* mult = 2 is needed for 420 Chroma as U and V are interleaved */
        if (dstFormat == YUV_420SP) {
            mult = 2;
        }
        /* stride is half for 422 Chroma as U and V are de-interleaved */
        if (dstFormat== YUV_422ILE || dstFormat== YUV_422IBE) {
            src_stride = src_stride/2;
        }
    }

    roundedXFracArray= (uint8_t*) scratchPtr;
    roundedYFracArray= roundedXFracArray + numMappedPixels;
    tluIndexArrayNN= (uint16_t*)(roundedYFracArray + numMappedPixels);

    /* Round x fractional part to the nearest integer */
    for (i=0; i < numMappedPixels; i++)
        roundedXFracArray[i]= ((tluFracArray[i] & maskx) + (1<<(QShift-1) )) >> QShift;

    /* Round y fractional part to the nearest integer */
    for (i=0; i < numMappedPixels; i++) {
        roundedYFracArray[i]= ((tluFracArray[i] >> shifty) + (1<<(QShift-1) )) >> QShift;
    }

    /* We need to multiply  roundedYFracArray with the input stride in order to
     * produce the offset to next row .
     * Store this intermediary result directly into tluIndexArrayNN
     */
    for (i=0; i < numMappedPixels; i++) {
        tluIndexArrayNN[i]= roundedYFracArray[i]*src_stride;
    }

    /*
     * Add tluIndexArray to tluIndexArrayNN
     */
    for (i=0; i < numMappedPixels; i++) {
        tluIndexArrayNN[i]+= tluIndexArray[i];
    }

    /*
     * Add to tluIndexArrayNN the rounded x fractional part
     */
    for (i=0; i < numMappedPixels; i++) {
        tluIndexArrayNN[i]+= mult*roundedXFracArray[i];
    }

    /* compute final output o  */
    for (i=0; i < numMappedPixels; i++){

        if (dstFormat== S8BIT || dstFormat== U8BIT)
            o= *(src32 + tluIndexArrayNN[i]);
        else if (dstFormat== YUV_420SP)
            o= *(src32 + tluIndexArrayNN[i]);
        else
            o= *(src32 + tluIndexArrayNN[i]);

        if (o >= params->sat_high)
            o= params->sat_high_set;
        else if (o < params->sat_low)
            o= params->sat_low_set;

#if INPUTTILE
        if (dstFormat== S8BIT)
            *((int8_t*)dst + scatterOffset[i]) = (int8_t)o;
        else if (dstFormat== U8BIT)
            *((uint8_t*)dst + scatterOffset[i]) = (uint8_t)o;
        else if (dstFormat== YUV_420SP)
            *((int8_t*)dst + scatterOffset[i]) = (int8_t)o;
        else
            *((uint8_t*)dst + 2*scatterOffset[i]) = (uint8_t)o;
#else
        if (dstFormat== S8BIT)
            *((int8_t*)dst + i) = (int8_t)o;
        else if (dstFormat== U8BIT)
            *((uint8_t*)dst + i) = (uint8_t)o;
        else if (dstFormat== YUV_420SP)
            *((int8_t*)dst + 2*i) = (int8_t)o;
        else
            *((uint8_t*)dst + 4*i) = (uint8_t)o;
#endif
    }

}

/* Deinterleave luma and chroma */
static void _natc_deInterleaveYUV422I(uint8_t *src, int32_t *dst32, int32_t *dst32_u, int32_t *dst32_v, uint16_t size, Format dstFormat){
    uint32_t i;
    uint8_t *srcY, *srcUV;

    if (dstFormat== YUV_422IBE){
        srcY= src;
        srcUV= src +1;
    }
    else {
        srcY= src + 1;
        srcUV= src;
    }

    for (i=0;i<size;i++){
        dst32[i]= srcY[2*i];
        if (i & 1)
            dst32_v[i>>1]= srcUV[2*i];
        else
            dst32_u[i>>1]= srcUV[2*i];
    }
}


/* Computes the remapped output for a given output block */
int32_t vcop_remap_c(
        uint8_t *blockInfoPtr,
        uint8_t *inputImagePtr,
        uint8_t *ChromaTLUIndexPtr,
        uint8_t *outputPtr,
        RemapParms *params
){
#if (!INPUTTILE)
    convertMapBlockInfo *blockInfo;
    uint16_t j, chromaDiv;
#endif
    uint16_t i;
    uint16_t *tluIndexArray, *tluIndexArrayU, *tluIndexArrayV, *tluIndexArrayUV;
    uint8_t  *tluFracArray, *tluFracArrayU, *tluFracArrayV, *tluFracArrayUV;
    uint16_t src_stride;
    uint8_t *src, *src_uv;
    int32_t *src32_y, *src32_u, *src32_v, *src32_uv;
    uint8_t *dst, *dst_y, *dst_uv, *dst_u, *dst_v;
    int32_t *dst32, *dst32_u, *dst32_v, *dst32_uv, *scratchPtr;
    uint8_t mnQShift, oQShift;
    uint16_t qScale;
    uint16_t outputBlockSize, blockSize;
    uint16_t srcSize;
    uint16_t lumaLineIndex, chromaLineIndex, lumaLineFrac, chromaLineFrac;
    uint16_t lumaColIndex, chromaColIndex, lumaColFrac, chromaColFrac, yfracOffset, xfracOffset;
    uint16_t width;
    uint16_t height;
    Format srcFormat;
    Format format;
    uint8_t maskx = 0x0F;
    uint8_t masky = 0xF0;
    uint8_t shifty = 4;

#if INPUTTILE
    uint16_t   tileWidth, tileHeight, inputTileSize, maxNumPixelsinTile, numMappedPixels, numEvenMappedPixels, numOddMappedPixels;
    uint16_t  *tluScOffsetArray, *tluScOffsetArrayUV, *tluScOffsetArrayU, *tluScOffsetArrayV;
#endif

    width           = params->maps.outputBlockDim.width;
    height          = params->maps.outputBlockDim.height;
    srcFormat       = params->maps.srcFormat;
    outputBlockSize = width * height;
    srcSize         = sizeofFormat(srcFormat);

#if INPUTTILE
    tileWidth        = params->maps.inputTileDim.width;
    tileHeight       = params->maps.inputTileDim.height;
    inputTileSize    = (tileWidth + HORZ_TILE_PADDING) * (tileHeight + VERT_TILE_PADDING);

    maxNumPixelsinTile  = params->maps.maxNumPixelsinTile;

    blockInfoPtr            = blockInfoPtr + 32 - 3*sizeof(uint16_t);
    numMappedPixels     = *((uint16_t *)blockInfoPtr);
    numEvenMappedPixels = *((uint16_t *)blockInfoPtr + 1);

    /* sizeof(uint16_t) -> sizeof(tileInfo->numPixels) */
    tluIndexArray    = (uint16_t *)(blockInfoPtr  + 3*sizeof(uint16_t));
    tluFracArray     = (uint8_t *) (tluIndexArray + ALIGN_TLU(maxNumPixelsinTile));
    tluScOffsetArray = (uint16_t *)(tluFracArray  + ALIGN_TLU(maxNumPixelsinTile));

#else
    /* blockInfo points to ConvertMapBlockInfo structure */
    blockInfo       = (convertMapBlockInfo *)blockInfoPtr;
    /* tluIndexArray points to TLU Index of Luma block */
    tluIndexArray   = (uint16_t*)(blockInfo + 1);
    tluFracArray    = (uint8_t *)(tluIndexArray + outputBlockSize);
    inputTileSize   =  params->maps.maxInputBlockSize;
#endif

    if (srcFormat == YUV_420SP) {
        tluIndexArrayUV = (uint16_t *)ChromaTLUIndexPtr;
        tluIndexArrayU  = tluIndexArrayUV;
        tluIndexArrayV  = tluIndexArrayUV;
#if INPUTTILE
        tluFracArrayUV  = (uint8_t*)(tluIndexArrayUV + numEvenMappedPixels);
#else
        tluFracArrayUV  = (uint8_t*)(tluIndexArrayUV + outputBlockSize/2);
#endif
        tluFracArrayU   = tluFracArrayUV;
        tluFracArrayV   = tluFracArrayUV;

#if INPUTTILE
        tluScOffsetArrayUV  = (uint16_t*)(tluFracArrayUV + numEvenMappedPixels);
        tluScOffsetArrayU   = tluScOffsetArrayUV;
        tluScOffsetArrayV   = tluScOffsetArrayUV;
#endif

    }
    else if (srcFormat== YUV_422ILE || srcFormat== YUV_422IBE) {
        tluIndexArrayU  = (uint16_t*)(ChromaTLUIndexPtr);
#if INPUTTILE
        numOddMappedPixels = numMappedPixels - numEvenMappedPixels;

        tluIndexArrayV  = tluIndexArrayU + numEvenMappedPixels;
        tluFracArrayU   = (uint8_t*)(tluIndexArrayV + numOddMappedPixels);
        tluFracArrayV   = tluFracArrayU + numEvenMappedPixels;
#else
        tluIndexArrayV  = tluIndexArrayU + outputBlockSize/2;
        tluFracArrayU   = (uint8_t*)(tluIndexArrayV + outputBlockSize/2);
        tluFracArrayV   = tluFracArrayU + outputBlockSize/2;
#endif
#if INPUTTILE
        tluScOffsetArrayUV  = (uint16_t*)(tluFracArrayV + numOddMappedPixels);
        tluScOffsetArrayU   = tluScOffsetArrayUV;
        tluScOffsetArrayV   = tluScOffsetArrayUV + numEvenMappedPixels;
#endif

    }

#if INPUTTILE
    src_stride  = tileWidth + HORZ_TILE_PADDING;
#else
    src_stride  = blockInfo->inputBlockWidth;
#endif
    if (srcFormat== YUV_422ILE || srcFormat== YUV_422IBE || srcFormat== YUV_420SP) {
        mnQShift= 0;
        oQShift= 2*params->maps.qShift;
    }
    else {
        /* U16/S16 Format */
        if (srcSize== 2) {
            mnQShift= params->maps.qShift;
            oQShift= params->maps.qShift;
        }
        else {
            /* U8/S8 Format */
            mnQShift= 0;
            oQShift= 2*params->maps.qShift;
        }
    }

    qScale= (1<<params->maps.qShift);

    /* src, src_uv points to Input Image Luma and Chroma block respectively */
    src    = (uint8_t*)(inputImagePtr);
    src_uv= src + ALIGN_TLU(inputTileSize);

    /* Deinterleave src into into tempBuf */
    dst32      = (int32_t*)tempBuf;
    dst32_uv   = dst32 + inputTileSize;
    dst32_u    = dst32_uv;
    dst32_v    = dst32_u + inputTileSize/2;
    scratchPtr = dst32_v + inputTileSize/2;


    if (srcFormat== YUV_422ILE || srcFormat== YUV_422IBE) {
        _natc_deInterleaveYUV422I((uint8_t*)src, dst32, dst32_u, dst32_v, inputTileSize, srcFormat);
    }
    else {
        for (i=0;i<(inputTileSize);i++) {

            if (srcFormat== S8BIT)
                *(dst32 + i)= *((int8_t*)src + i);
            else if (srcFormat== U8BIT || srcFormat== YUV_420SP)
                *(dst32 + i)= *((uint8_t*)src + i);
            else if (srcFormat== S16BIT)
                *(dst32 + i)= *((int16_t*)src + i);
            else
                *(dst32 + i)= *((uint16_t*)src + i);
        }
    }

    if (srcFormat== YUV_420SP) {
        for (i=0;i<inputTileSize/2;i++)
            *(dst32_uv + i)= *((uint8_t*)src_uv + i);
    }

    /* dst, dst_uv points to Remapped output Luma and Chroma block respectively */
    dst      = (uint8_t*)(outputPtr);
    dst_uv   = dst + outputBlockSize;

    /* Set src, dst for Y, U and V for all formats */
    src32_y  = dst32;

    if (srcFormat== YUV_422ILE) {
        src32_u  = dst32_u;
        src32_v  = dst32_v;
        dst_y    = dst+1;
        dst_u    = dst;
        dst_v    = dst+2;
    }
    else if (srcFormat== YUV_422IBE) {
        src32_u  = dst32_u;
        src32_v  = dst32_v;
        dst_y    = dst;
        dst_u    = dst+1;
        dst_v    = dst+3;
    }
    else {/* U8, U16, 420. For U8 and U16, src, dst for U, V is not used */
        src32_uv = dst32_uv;
        src32_u  = src32_uv;
        src32_v  = src32_uv + 1;
        dst_y    = dst;
        dst_u    = dst_uv;
        dst_v    = dst_uv+1;
    }

    /* Bilinear or Nearest Neighbor Interpolation for Luma components */
    /* Supported formats for Bilinear Interpolation : U8, S8, U16, S16, 420 Luma, 422 Luma */
    if (srcFormat == YUV_420SP)
        format = U8BIT;
    else
        format= srcFormat;

#if INPUTTILE
    blockSize = numMappedPixels;
#else
    blockSize = outputBlockSize;
#endif
    if (params->interpolationLuma== BILINEAR) {

        _natc_bilinearInterpolate(src32_y, dst_y, blockSize, tluIndexArray, tluFracArray, \
                   tluScOffsetArray, src_stride, format, LUMA_INDEX, mnQShift, oQShift, qScale, (uint8_t*)scratchPtr, params);

    }
    /* Supported formats for Nearest Neighbor Interpolation : U8, S8, 420 Luma */
    else {

        _natc_nnInterpolate(src32_y, dst_y, blockSize, tluIndexArray, tluFracArray, \
                   tluScOffsetArray, src_stride, format, LUMA_INDEX, params->maps.qShift, (uint8_t*)scratchPtr, params);
    }


    /* For Formats with Chroma components */
    if (srcFormat == YUV_422ILE || srcFormat == YUV_422IBE || srcFormat == YUV_420SP) {

        /* On the Fly TLU Calculation for Chroma components is done below */
        if (srcFormat== YUV_422ILE || srcFormat== YUV_422IBE) {

#if (!INPUTTILE)
            chromaDiv=2;
#endif

#if INPUTTILE
            /* De-interleave tluIndexArray into tluIndexArrayU and tluIndexArrayV */
            /* For V, subtracting Luma Index by 1 because the first Y component linked to V is 2nd Y */
            /* Luma width needs to be a multiple of 2 for the below logic to hold good */
            for (i=0; i < numEvenMappedPixels; i++) {
                tluIndexArrayU[i]= (tluIndexArray[i])/2;
            }
            for (i=0; i < numOddMappedPixels; i++) {
                if(tluIndexArray[numEvenMappedPixels + i] > 0)
                {
                    tluIndexArrayV[i]= (tluIndexArray[numEvenMappedPixels + i] - 1)/2;
                } else
                {
                    tluIndexArrayV[i]= tluIndexArray[numEvenMappedPixels + i];
                }
            }

            /* De-interleave xFrac into xFracU and xFracV */
            for (i=0; i < numEvenMappedPixels; i++) {
                xfracOffset     = (tluIndexArray[i] & 0x0001) << params->maps.qShift;
                lumaColFrac     = tluFracArray[i] & maskx;
                tluFracArrayU[i]= (lumaColFrac + xfracOffset)/2;
            }
            for (i=0; i < numOddMappedPixels; i++) {
                if(tluIndexArray[numEvenMappedPixels+i] > 0)
                {
                    xfracOffset     = ((tluIndexArray[numEvenMappedPixels+i] - 1) & 0x0001) << params->maps.qShift;
                } else
                {
                    xfracOffset     = 0;
                }
                lumaColFrac     = tluFracArray[numEvenMappedPixels+i] & maskx;
                tluFracArrayV[i]= (lumaColFrac + xfracOffset)/2;
            }

            /* De-interleave yFrac into yFracU and yFracV */
            for (i=0; i < numEvenMappedPixels; i++) {
                tluFracArrayU[i]= tluFracArrayU[i] | (tluFracArray[i] & masky);
            }
            for (i=0; i < numOddMappedPixels; i++) {
                tluFracArrayV[i]= tluFracArrayV[i] | (tluFracArray[numEvenMappedPixels+i] & masky);
            }

            /* De-interleave yFrac into yFracU and yFracV */
            for (i=0; i < numEvenMappedPixels; i++) {
                tluScOffsetArrayU[i]= tluScOffsetArray[i];
            }
            for (i=0; i < numOddMappedPixels; i++) {
                tluScOffsetArrayV[i]= tluScOffsetArray[numEvenMappedPixels + i] - 1;
            }

#else
            /* De-interleave tluIndexArray into tluIndexArrayU and tluIndexArrayV */
            /* For V, subtracting Luma Index by 1 because the first Y component linked to V is 2nd Y */
            /* Luma width needs to be a multiple of 2 for the below logic to hold good */
            for (i=0; i < blockSize/2; i++) {
                tluIndexArrayU[i]= (tluIndexArray[2*i])/2;
                if(tluIndexArray[2*i+1] > 0)
                {
                    tluIndexArrayV[i]= (tluIndexArray[2*i+1] - 1)/2;
                } else
                {
                    tluIndexArrayV[i]= tluIndexArray[2*i+1];
                }
            }

            /* De-interleave xFrac into xFracU and xFracV */
            for (i=0; i < blockSize/2; i++) {
                xfracOffset     = (tluIndexArray[2*i] & 0x0001) << params->maps.qShift;
                lumaColFrac     = tluFracArray[2*i] & maskx;
                tluFracArrayU[i]= (lumaColFrac + xfracOffset)/2;

                if(tluIndexArray[2*i+1] > 0)
                {
                    xfracOffset     = ((tluIndexArray[2*i+1] - 1) & 0x0001) << params->maps.qShift;
                } else
                {
                    xfracOffset     = 0;
                }
                lumaColFrac     = tluFracArray[2*i+1] & maskx;
                tluFracArrayV[i]= (lumaColFrac + xfracOffset)/2;
            }

            /* De-interleave yFrac into yFracU and yFracV */
            for (i=0; i < blockSize/2; i++) {
                tluFracArrayU[i]= tluFracArrayU[i] | (tluFracArray[2*i] & masky);
                tluFracArrayV[i]= tluFracArrayV[i] | (tluFracArray[2*i+1] & masky);
            }
#endif
        }
            /* YUV_420SP */
        else {

#if (!INPUTTILE)
            chromaDiv = 4;
#endif
            /* Compute the chroma index on the fly using the luma LUT index array, input block stride */
            /* Let tluIndexArray[i] be Integral TLL Index for the Luma point (x.a , y.b). Then :
                          lumaLineIndexUV = y
                          lumaColIndexUV  = x
                          Logic to calculate U (Chroma) Indexes, considering (x/2 * y/2) U pixels:
                          chromaLineIndexU = x/2
                          chromaColIndexU  = y/2
                          if(x == even)
                              chromaLineFracU = lumaLinefracUV/2
                          else if(x == odd)
                              chromaLineFracU = lumaLinefracUV/2 + 1
                          Do the same logic for Y
                     */
#if INPUTTILE
            for (i = 0; i < numEvenMappedPixels; i++) {
                /* Calculate chroma y */
                lumaLineIndex   = (tluIndexArray[i] * ((1 << 16)/src_stride)) >> 16;
                chromaLineIndex = lumaLineIndex >> 1;

                /* Calculate chroma y frac (in Q format) */
                yfracOffset     = (lumaLineIndex & 0x0001) << params->maps.qShift;
                lumaLineFrac    = tluFracArray[i] >> shifty;
                chromaLineFrac  = (lumaLineFrac + yfracOffset) >> 1;

                /* Calculate chroma x */
                lumaColIndex    = tluIndexArray[i] - (lumaLineIndex*src_stride);
                chromaColIndex  = lumaColIndex >> 1;
                /* Since U and V are deinterleaved */
                chromaColIndex  = chromaColIndex*2;

                /* Calculate chroma x frac */
                xfracOffset     = (lumaColIndex & 0x0001) << params->maps.qShift;
                lumaColFrac     = tluFracArray[i] & maskx;
                chromaColFrac   = (lumaColFrac + xfracOffset) >> 1;

                /* Calculate chroma TLU : chromax + chromay*stride */
                tluIndexArrayUV[i] =  chromaColIndex + (chromaLineIndex * src_stride);

                /* Calculate chroma frac */
                tluFracArrayUV[i]  = (chromaLineFrac << shifty) | (chromaColFrac & maskx);

                /* Calculate Chroma Scatter Offset in output block */
                /* Calculate chroma y */
                lumaLineIndex   = (tluScOffsetArray[i] * ((1 << 16)/width)) >> 16;
                chromaLineIndex = lumaLineIndex >> 1;
                /* Calculate chroma x */
                lumaColIndex    = tluScOffsetArray[i] - (lumaLineIndex*width);
                chromaColIndex  = lumaColIndex >> 1;
                /* Since U and V are deinterleaved */
                chromaColIndex  = chromaColIndex*2;

                tluScOffsetArrayUV[i] =  chromaColIndex + (chromaLineIndex * width);

            }

#else
            for (j=0; j < height/2; j++) {
                for (i=0; i < width/2; i++) {
                    /* Calculate chroma y */
                    lumaLineIndex   = (tluIndexArray[2*j*width+2*i] * ((1 << 16)/src_stride)) >> 16;
                    chromaLineIndex = lumaLineIndex >> 1;

                    /* Calculate chroma y frac (in Q format) */
#if LOGIC_2
                    yfracOffset     = lumaLineIndex & 0x0001; //- (chromaLineIndex*2);
                    chromaLineFrac  = (tluFracArray[2*j*width+2*i] >> shifty)*yfracOffset;
#else
                    yfracOffset     = (lumaLineIndex & 0x0001) << params->maps.qShift;
                    lumaLineFrac    = tluFracArray[2*j*width+2*i] >> shifty;
                    chromaLineFrac  = (lumaLineFrac + yfracOffset) >> 1;
#endif
                    /* Calculate chroma x */
                    lumaColIndex    = tluIndexArray[2*j*width+2*i] - (lumaLineIndex*src_stride);
                    chromaColIndex  = lumaColIndex >> 1;
                    /* Since U and V are deinterleaved */
                    chromaColIndex  = chromaColIndex*2;

                    /* Calculate chroma x frac */
#if LOGIC_2
                    xfracOffset     = lumaColIndex & 0x0001;
                    chromaColFrac   = (tluFracArray[2*j*width+2*i] & maskx)*xfracOffset;
#else
                    xfracOffset     = (lumaColIndex & 0x0001) << params->maps.qShift;
                    lumaColFrac     = tluFracArray[2*j*width+2*i] & maskx;
                    chromaColFrac   = (lumaColFrac + xfracOffset) >> 1;
#endif
                    /* Calculate chroma TLU : chromax + chromay*stride */
                    tluIndexArrayUV[i + j*width/2] =  chromaColIndex + (chromaLineIndex * src_stride);

                    /* Calculate chroma frac */
                    tluFracArrayUV[i + j*width/2] = (chromaLineFrac << shifty) | (chromaColFrac & maskx);

                }
            }
#endif
        }

#if INPUTTILE
        blockSize = numEvenMappedPixels;
#else
        blockSize = outputBlockSize/chromaDiv;
#endif

        /* Bilinear or Nearest Neighbor Interpolation for Chroma components */
        /* Supported formats for Bilinear Interpolation : 420 Chroma, 422 Chroma */
        if (params->interpolationChroma == BILINEAR) {
            _natc_bilinearInterpolate(src32_u, dst_u, blockSize, tluIndexArrayU, tluFracArrayU, \
                            tluScOffsetArrayU, src_stride, srcFormat, CHROMA_INDEX, mnQShift, oQShift, qScale, (uint8_t*)scratchPtr, params);


#if INPUTTILE
            if (srcFormat== YUV_422ILE || srcFormat== YUV_422IBE) {
                blockSize = numOddMappedPixels;
            }
#endif
            /* Bilinear interpolation for V */
            _natc_bilinearInterpolate(src32_v, dst_v, blockSize, tluIndexArrayV, tluFracArrayV, \
                            tluScOffsetArrayV, src_stride, srcFormat, CHROMA_INDEX, mnQShift, oQShift, qScale, (uint8_t*)scratchPtr, params);
        }
        /* Supported formats for Nearest Neighbor Interpolation : 420 Chroma, 422 Chroma*/
        else {
            _natc_nnInterpolate(src32_u, dst_u, blockSize, tluIndexArrayU, tluFracArrayU, \
                            tluScOffsetArrayU, src_stride, srcFormat, CHROMA_INDEX, params->maps.qShift, (uint8_t*)scratchPtr, params);


#if INPUTTILE
            if (srcFormat== YUV_422ILE || srcFormat== YUV_422IBE) {
                blockSize = numOddMappedPixels;
            }
#endif

            /* Nearest neighbor interpolation for V  */
            _natc_nnInterpolate(src32_v, dst_v, blockSize, tluIndexArrayV, tluFracArrayV, \
                            tluScOffsetArrayV, src_stride, srcFormat, CHROMA_INDEX, params->maps.qShift, (uint8_t*)scratchPtr, params);
        }
    }

    return 0;
}
/* ======================================================================== */
/*                       End of file                                        */
/* ======================================================================== */
