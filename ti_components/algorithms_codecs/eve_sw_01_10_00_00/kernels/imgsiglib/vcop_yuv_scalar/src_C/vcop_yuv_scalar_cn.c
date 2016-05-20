/*==========================================================================*/
/*      Copyright (C) 2009-2014 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*                                                                          */
/*     NAME                                                                 */
/*     vcop_yuv_scalar_cn.c                                                 */
/*                                                                          */
/*     DESCRIPTION                                                          */
/*         This is the c-reference implementation for the                   */
/*         YUV scalar  kernel                                               */
/*                                                                          */
/*                                                                          */
/*==========================================================================*/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "vcop_yuv_scalar_cn.h"

void vcop_resize_cn_y(uint8_t * inImage, uint8_t * outImage, uint16_t inWidth, uint16_t inHeight, uint16_t inPitch, uint16_t outWidth, uint16_t outHeight, uint16_t outPitch, uint16_t scaleRatioQ12,uint16_t srQShift,uint16_t fpQShift)
{
  uint16_t x, y, srcX, srcY, srcY1, srcX1;
  uint16_t yFracB;
  uint16_t yFracT;
  uint16_t xFracR;
  uint16_t xFracL;

  uint8_t in_00, in_01, in_10, in_11;
  uint32_t out, out_0, out_1;

  for(y = 0; y < outHeight; y++)
  {
    srcY = ((y * scaleRatioQ12) / (1 << (srQShift-fpQShift)));
    yFracB = srcY - ((srcY >> fpQShift) << fpQShift);
    yFracT = (1 << fpQShift) - yFracB;
    srcY   = (srcY >> fpQShift);
    srcY1  = srcY+1;
    srcY   = srcY  >= inHeight ? inHeight-1 : srcY;
    srcY1  = srcY1 >= inHeight ? inHeight-1 : srcY1;
    for(x = 0; x < outWidth; x++)
    {
      srcX = ((x * scaleRatioQ12) / (1 << (srQShift-fpQShift)));
      xFracR = srcX - ((srcX >> fpQShift) << fpQShift);
      xFracL = (1 << fpQShift) - xFracR;
      srcX   = (srcX >> fpQShift);
      srcX1  = srcX+1;
      srcX  = srcX  >= inWidth ? inWidth-1 : srcX;
      srcX1 = srcX1 >= inWidth ? inWidth-1 : srcX1;

      in_00 = inImage[srcY*inPitch + srcX];
      in_01 = inImage[srcY*inPitch + srcX1];
      in_10 = inImage[srcY1*inPitch + srcX];
      in_11 = inImage[srcY1*inPitch + srcX1];

      out_0 = in_00*xFracL + in_01*xFracR;
      out_1 = in_10*xFracL + in_11*xFracR;

      out   = out_0*yFracT + out_1*yFracB;
      out   = (out + (1<<(2*fpQShift-1))) >> (2*fpQShift);
      outImage[y*outPitch + x] = out;
    }
  }
}
void vcop_resize_cn_y_s(uint8_t * inImage, uint8_t * outImage, uint16_t inWidth, uint16_t inHeight, uint16_t inPitch, uint16_t outWidth, uint16_t outHeight, uint16_t outPitch, uint16_t scaleRatioQ12,uint16_t srQShift,uint16_t fpQShift)
{
  uint16_t x, y, srcX, srcY, srcY1, srcX1;
  uint16_t yFracB;
  uint16_t yFracT;
  uint16_t xFracR;
  uint16_t xFracL;

  uint32_t out, out_0, out_1;

  uint8_t * verResizeOut = (uint8_t *)malloc(inWidth*outHeight*sizeof(uint8_t));

  for(y = 0; y < outHeight; y++)
  {
    srcY = ((y * scaleRatioQ12) / (1 << (srQShift-fpQShift)));
    yFracB = srcY - ((srcY >> fpQShift) << fpQShift);
    yFracT = (1 << fpQShift) - yFracB;
    srcY   = (srcY >> fpQShift);
    srcY1  = srcY+1;
    srcY   = srcY  >= inHeight ? inHeight-1 : srcY;
    srcY1  = srcY1 >= inHeight ? inHeight-1 : srcY1;
    for(x = 0; x < inWidth; x++)
    {

      out_0 = inImage[srcY*inPitch + x];
      out_1 = inImage[srcY1*inPitch + x];
      out   = out_0*yFracT + out_1*yFracB;
      out   = (out + (1<<(fpQShift-1))) >> (fpQShift);
      verResizeOut[y*inWidth + x] = out;
    }
  }

  for(x = 0; x < outWidth; x++)
  {
    srcX = ((x * scaleRatioQ12) / (1 << (srQShift-fpQShift)));
    xFracR = srcX - ((srcX >> fpQShift) << fpQShift);
    xFracL = (1 << fpQShift) - xFracR;
    srcX   = (srcX >> fpQShift);
    srcX1  = srcX+1;
    srcX  = srcX  >= inWidth ? inWidth-1 : srcX;
    srcX1 = srcX1 >= inWidth ? inWidth-1 : srcX1;
    for(y = 0; y < outHeight; y++)
    {

      out_0 = verResizeOut[y*inWidth + srcX];
      out_1 = verResizeOut[y*inWidth + srcX1];
      out   = out_0*xFracL + out_1*xFracR;
      out   = (out + (1<<(fpQShift-1))) >> (fpQShift);
      outImage[y*outPitch + x] = out;
    }
  }


}
void vcop_resize_cn_uv(uint8_t * inImage, uint8_t * outImage, uint16_t inWidth, uint16_t inHeight, uint16_t inPitch, uint16_t outWidth, uint16_t outHeight, uint16_t outPitch, uint16_t scaleRatioQ12,uint16_t srQShift,uint16_t fpQShift)
{
  uint16_t x, y, srcX, srcY, srcY1, srcX1;
  uint16_t yFracB;
  uint16_t yFracT;
  uint16_t xFracR;
  uint16_t xFracL;

  uint8_t in_00, in_01, in_10, in_11;
  uint32_t out, out_0, out_1;

  outWidth  =   outWidth/2; 
  outHeight =   outHeight/2;
  inWidth   =   inWidth/2; 
  inHeight  =   inHeight/2;

  for(y = 0; y < outHeight; y++)
  {
    srcY = ((y * scaleRatioQ12) / (1 << (srQShift-fpQShift)));
    yFracB = srcY - ((srcY >> fpQShift) << fpQShift);
    yFracT = (1 << fpQShift) - yFracB;
    srcY   = (srcY >> fpQShift);
    srcY1  = srcY+1;
    srcY   = srcY  >= inHeight ? inHeight-1 : srcY;
    srcY1  = srcY1 >= inHeight ? inHeight-1 : srcY1;
    for(x = 0; x < outWidth; x++)
    {
      srcX = ((x * scaleRatioQ12) / (1 << (srQShift-fpQShift)));
      xFracR = srcX - ((srcX >> fpQShift) << fpQShift);
      xFracL = (1 << fpQShift) - xFracR;
      srcX   = (srcX >> fpQShift);
      srcX1  = srcX+1;
      srcX  = srcX  >= inWidth ? inWidth-1 : srcX;
      srcX1 = srcX1 >= inWidth ? inWidth-1 : srcX1;

      in_00 = inImage[srcY*inPitch + 2*srcX];
      in_01 = inImage[srcY*inPitch + 2*srcX1];
      in_10 = inImage[srcY1*inPitch + 2*srcX];
      in_11 = inImage[srcY1*inPitch + 2*srcX1];

      out_0 = in_00*xFracL + in_01*xFracR;
      out_1 = in_10*xFracL + in_11*xFracR;

      out   = out_0*yFracT + out_1*yFracB;
      out   = (out + (1<<(2*fpQShift-1))) >> (2*fpQShift);
      outImage[y*outPitch + 2*x] = out;

      in_00 = inImage[srcY*inPitch + 2*srcX+1];
      in_01 = inImage[srcY*inPitch + 2*srcX1+1];
      in_10 = inImage[srcY1*inPitch + 2*srcX+1];
      in_11 = inImage[srcY1*inPitch + 2*srcX1+1];

      out_0 = in_00*xFracL + in_01*xFracR;
      out_1 = in_10*xFracL + in_11*xFracR;

      out   = out_0*yFracT + out_1*yFracB;
      out   = (out + (1<<(2*fpQShift-1))) >> (2*fpQShift);
      outImage[y*outPitch + 2*x+1] = out;

    }
  }
}
void vcop_resize_cn_uv_s(uint8_t * inImage, uint8_t * outImage, uint16_t inWidth, uint16_t inHeight, uint16_t inPitch, uint16_t outWidth, uint16_t outHeight, uint16_t outPitch, uint16_t scaleRatioQ12,uint16_t srQShift,uint16_t fpQShift)
{
  uint16_t  x, y, srcX, srcY, srcY1, srcX1;
  uint16_t yFracB;
  uint16_t yFracT;
  uint16_t xFracR;
  uint16_t xFracL;

  uint32_t out, out_0, out_1;
  outWidth  =   outWidth/2; 
  outHeight =   outHeight/2;
  inWidth   =   inWidth/2; 
  inHeight  =   inHeight/2;

  uint8_t * verResizeOut = (uint8_t *)malloc(2*inWidth*outHeight*sizeof(uint8_t));

  for(y = 0; y < outHeight; y++)
  {
    srcY = ((y * scaleRatioQ12) / (1 << (srQShift-fpQShift)));
    yFracB = srcY - ((srcY >> fpQShift) << fpQShift);
    yFracT = (1 << fpQShift) - yFracB;
    srcY   = (srcY >> fpQShift);
    srcY1  = srcY+1;
    srcY   = srcY  >= inHeight ? inHeight-1 : srcY;
    srcY1  = srcY1 >= inHeight ? inHeight-1 : srcY1;
    for(x = 0; x < inWidth; x++)
    {

      out_0 = inImage[srcY*inPitch  + 2*x];
      out_1 = inImage[srcY1*inPitch + 2*x];
      out   = out_0*yFracT + out_1*yFracB;
      out   = (out + (1<<(fpQShift-1))) >> (fpQShift);
      verResizeOut[y*inWidth*2 + 2*x] = out;

      out_0 = inImage[srcY*inPitch  + 2*x+1];
      out_1 = inImage[srcY1*inPitch + 2*x+1];
      out   = out_0*yFracT + out_1*yFracB;
      out   = (out + (1<<(fpQShift-1))) >> (fpQShift);
      verResizeOut[y*inWidth*2 + 2*x+1] = out;

    }
  }

  for(x = 0; x < outWidth; x++)
  {
    srcX = ((x * scaleRatioQ12) / (1 << (srQShift-fpQShift)));
    xFracR = srcX - ((srcX >> fpQShift) << fpQShift);
    xFracL = (1 << fpQShift) - xFracR;
    srcX   = (srcX >> fpQShift);
    srcX1  = srcX+1;
    srcX  = srcX  >= inWidth ? inWidth-1 : srcX;
    srcX1 = srcX1 >= inWidth ? inWidth-1 : srcX1;
    for(y = 0; y < outHeight; y++)
    {

      out_0 = verResizeOut[y*inWidth*2 + 2*srcX];
      out_1 = verResizeOut[y*inWidth*2 + 2*srcX1];
      out   = out_0*xFracL + out_1*xFracR;
      out   = (out + (1<<(fpQShift-1))) >> (fpQShift);
      outImage[y*outPitch + 2*x] = out;
      out_0 = verResizeOut[y*inWidth*2 + 2*srcX+1];
      out_1 = verResizeOut[y*inWidth*2 + 2*srcX1+1];
      out   = out_0*xFracL + out_1*xFracR;
      out   = (out + (1<<(fpQShift-1))) >> (fpQShift);
      outImage[y*outPitch + 2*x+1] = out;

    }
  }


}

void vcop_scaler_luma_vertical_cn(uint8_t *inBlkPtr, uint8_t *interBlkPtr, uint16_t *yIndexPtr, uint8_t *yFracPtr, uint16_t inBlockWidth, uint16_t blockHeight,uint16_t LUT_DATA_SIZE,uint16_t fpQShift)
{
  uint8_t blkX;
  uint8_t blkY;
  for(blkY = 0; blkY < blockHeight; blkY++)
  {
    for(blkX = 0; blkX < inBlockWidth; blkX++)
    {
      interBlkPtr[blkY*inBlockWidth + blkX] = ((inBlkPtr[yIndexPtr[blkY]*LUT_DATA_SIZE+blkX]*yFracPtr[blkY] + inBlkPtr[yIndexPtr[blockHeight+blkY]*LUT_DATA_SIZE+blkX]*yFracPtr[blockHeight+blkY]) + (1<<(fpQShift-1))) >> (fpQShift);
    }
  }
}

void vcop_scaler_luma_Horizontal_cn(uint8_t *interBlkPtr, uint8_t *outBlkPtr, uint16_t *xIndexPtr, uint8_t *xFracPtr, uint16_t inBlockWidth, uint16_t blockWidth, uint16_t blockHeight,uint16_t LUT_DATA_SIZE,uint16_t fpQShift)
{
  uint8_t blkX;
  uint8_t blkY;

  for(blkY = 0; blkY < blockHeight; blkY++)
  {
    for(blkX = 0; blkX < blockWidth; blkX++)
    {
      outBlkPtr[blkY*blockWidth + blkX] = ((interBlkPtr[blkY*inBlockWidth+(xIndexPtr[blkX]*LUT_DATA_SIZE)/blockHeight]*xFracPtr[blkX] + interBlkPtr[blkY*inBlockWidth+(xIndexPtr[blockWidth+blkX]*LUT_DATA_SIZE)/blockHeight]*xFracPtr[blockWidth+blkX]) + (1<<(fpQShift-1))) >> (fpQShift);
    }
  }
}

void vcop_scaler_chroma_vertical_cn(uint8_t *inBlkPtr, uint8_t *interBlkPtr, uint16_t *yIndexPtr, uint8_t *yFracPtr, uint16_t inBlockWidth, uint16_t blockHeight,uint16_t LUT_DATA_SIZE,uint16_t fpQShift)
{
  uint8_t blkX;
  uint8_t blkY;
  for(blkY = 0; blkY < blockHeight; blkY++)
  {
    for(blkX = 0; blkX < inBlockWidth; blkX++)
    {
      interBlkPtr[blkY*inBlockWidth + blkX] = ((inBlkPtr[yIndexPtr[blkY]*LUT_DATA_SIZE+blkX]*yFracPtr[blkY] + inBlkPtr[yIndexPtr[blockHeight+blkY]*LUT_DATA_SIZE+blkX]*yFracPtr[blockHeight+blkY]) + (1<<(fpQShift-1))) >> (fpQShift);
    }
  }

}

void vcop_scaler_chroma_Horizontal_cn(uint8_t *interBlkPtr, uint8_t *outBlkPtr, uint16_t *xIndexPtr, uint8_t *xFracPtr, uint16_t inBlockWidth, uint16_t blockWidth, uint16_t blockHeight,uint16_t LUT_DATA_SIZE,uint16_t fpQShift)
{
  uint8_t blkX;
  uint8_t blkY;

  for(blkY = 0; blkY < blockHeight; blkY++)
  {
    for(blkX = 0; blkX < (blockWidth/2); blkX++)
    {
      outBlkPtr[blkY*blockWidth + 2*blkX]   = ((interBlkPtr[blkY*inBlockWidth+((xIndexPtr[blkX]*LUT_DATA_SIZE)/blockHeight)]*xFracPtr[blkX]   + interBlkPtr[blkY*inBlockWidth+((xIndexPtr[(blockWidth/2)+blkX]*LUT_DATA_SIZE)/blockHeight)]*xFracPtr[(blockWidth/2)+blkX])   + (1<<(fpQShift-1))) >> (fpQShift);
      outBlkPtr[blkY*blockWidth + 2*blkX+1] = ((interBlkPtr[blkY*inBlockWidth+((xIndexPtr[blkX]*LUT_DATA_SIZE)/blockHeight)+1]*xFracPtr[blkX] + interBlkPtr[blkY*inBlockWidth+((xIndexPtr[(blockWidth/2)+blkX]*LUT_DATA_SIZE)/blockHeight)+1]*xFracPtr[(blockWidth/2)+blkX]) + (1<<(fpQShift-1))) >> (fpQShift);
    }
  }
}
