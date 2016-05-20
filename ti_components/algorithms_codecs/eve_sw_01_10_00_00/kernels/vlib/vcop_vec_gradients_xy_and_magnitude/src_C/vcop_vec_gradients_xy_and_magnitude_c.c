/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME                                                                 */
/*     vcop_vec_gradients_xy_and_magnitude_cn                               */
/*                                                                          */
/*     USAGE                                                                */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_vec_gradients_xy_and_magnitude_cn                          */
/*     (                                                                    */
/*         uint8_t  pIn[],                                            */
/*         int16_t          pGradX[],                                         */
/*         int16_t          pGradY[],                                         */
/*         int16_t          pMag[],                                           */
/*         uint16_t width,                                            */
/*         uint16_t height                                            */
/*     )                                                                    */
/*                                                                          */
/*     pIn       :  8-bit input image                                       */
/*     pGradX    :  gradient value in X direction                           */
/*     pGradY    :  gradient value in Y direction                           */
/*     pMag      :  gradient magnitude                                      */
/*     width     :  width of the input image                                */
/*     height    :  height of the input image                               */
/*                                                                          */
/*     Returns :  None or void.                                             */
/*                                                                          */
/*                                                                          */
/*     DESCRIPTION                                                          */
/*            This routine accepts a 8-bit input image and returns gradient */
/*     value in X direction, Y direction and its magnitude.                 */
/*                                                                          */
/*     ASSUMPTIONS                                                          */
/*                                                                          */
/*==========================================================================*/
/*      Copyright (C) 2010 Texas Instruments Incorporated.                  */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/

#include "../inc/vcop_vec_gradients_xy_and_magnitude_c.h"

void vcop_vec_gradients_xy_and_magnitude_cn
(
    uint8_t  pIn[],
    int16_t          pGradX[],
    int16_t          pGradY[],
    int16_t          pMag[],
    uint16_t width,
    uint16_t height,
    uint16_t pitch
)
{
  int32_t i , j;
  uint32_t inT, inL, inR, inB;
  uint8_t * rowPtr;
  for (j = 0; j < height; j++)
  {
    rowPtr = &pIn[j * pitch];
    for (i = 0; i < width; i++)
    {

      inT = rowPtr[i+1];
      inL = rowPtr[i+pitch];
      inR = rowPtr[i+pitch+2];
      inB = rowPtr[i+2*pitch+1];

      pGradX[i + (j*width)] = inR - inL;
      pGradY[i + (j*width)] = inB - inT;
      pMag[i + (j*width)]   = abs(pGradX[i + (j*width)]) + abs(pGradY[i + (j*width)]);
    }
  }
}

void vcop_vec_gradients_xy_and_magnitude_cn2
(
        uint8_t  pIn[],
        int16_t          pGradX[],
        int16_t          pGradY[],
        int16_t          pMag[],
        uint16_t width,
        uint16_t height,
        uint16_t srcStride,
        uint16_t dstStride
)
{
    int i4, i3;
    uint32_t inT, inL, inR, inB;
    int16_t pGx, pGy;

    for (i3 = 0; i3 < height; i3++) {
        for(i4= 0; i4 < width; i4++) {
            inT = pIn[(i3 + 0)*srcStride + i4 + 1];
            inL = pIn[(i3 + 1)*srcStride + i4    ];
            inR = pIn[(i3 + 1)*srcStride + i4 + 2];
            inB = pIn[(i3 + 2)*srcStride + i4 + 1];

            pGradX[i3 * dstStride + i4] =  pGx= inR - inL;
            pGradY[i3 * dstStride + i4] =  pGy= inB - inT;
            pMag  [i3 * dstStride + i4] =  abs(pGx) + abs(pGy);
        }
    }
}


void vcop_gradients_xy_list_cn
(
    uint8_t   *pIn,
    uint32_t  *pUpperLeftXy,
    uint8_t   *pEdgeMap,
    int32_t   *pGradXY,
    uint32_t  *pEdgeListXY,
    uint16_t  *pListSize,
    uint16_t   width,
    uint16_t   height,
    uint16_t   pitchInData,
    uint16_t   pitchEdgeMap
)
{
  int32_t i , j;
  uint32_t inT, inL, inR, inB;
  uint8_t * rowPtr;
  uint8_t edgeMap;
  uint16_t listCount = 0;
  int16_t gradX, gradY;
  for (j = 0; j < height; j++)
  {
    rowPtr = &pIn[j * pitchInData];
    for (i = 0; i < width; i++)
    {
      inT = rowPtr[i+1];
      inL = rowPtr[i+pitchInData];
      inR = rowPtr[i+pitchInData+2];
      inB = rowPtr[i+2*pitchInData+1];

      edgeMap = pEdgeMap[(i + j* pitchEdgeMap) ];

      if (edgeMap )
      {
        gradX = inR - inL;
        gradY = inB - inT;
        pGradXY[listCount] = ( gradX << 16U) + gradY;
        pEdgeListXY[listCount] = ((uint32_t)i << 16U) + j + (*pUpperLeftXy);
        listCount++;
      }
    }
  }

  *pListSize = listCount;
}

#define TEMP_ROUND(x,n) ( (x + (uint32_t)( 1 << ((uint32_t)n-1))) / (uint32_t)(1U << (uint32_t)n))

void vcop_gradients_xy_mag_lut_index_calulcation_cn(
                        int16_t  *gradXY,
                        uint16_t *lutIdxPtr,
                        int8_t   *log4aPtr,
                        uint16_t width,
                        uint16_t height,
                        uint16_t pitch)
{
  int i,j;
  uint32_t magSquare;
  uint32_t roundedMagSquare;
  uint16_t finalLutIndex;
  int16_t gx;
  int16_t gy;
  int32_t log4a;
  int32_t leftShift;

  for ( j = 0 ; j < height; j++)
  {
    for (i = 0; i < 2 * width; i+= 2)
    {
      gx = gradXY[i + (j * pitch)];
      gy = gradXY[i + (j * pitch) + 1];

      magSquare = gx * gx + gy * gy;
      if ( magSquare == 0 )
      {
        finalLutIndex = 255;
        log4a = -1;
      }
      else
      {

        /* Out Aim is to find magSquare / 4^((int)log4(magSquare))*/
        /* Oringal range of magSquare / 4^((int)log4(magSquare)) is from [1,4) */
        /* We multiple by 2^8 in both side to increase the range to [256, 1024) */
        /* Later we will substract 256 so the final range of index will be [ 0 ,768) */

        /* First find (int) log4 (magSquare) */
        log4a = (log ((double) magSquare))/ (log (4.0));

        /* We have to multipe by 2^8 and divide by 2^(2.log4(a)) which is equivalent to
        shift operation of 8 - 2*log4(a) */
        leftShift = 8 - 2 * log4a;
        if ( leftShift < 0 )
        {
          roundedMagSquare = TEMP_ROUND ( magSquare, (uint32_t)(-leftShift));
        }
        else
        {
          roundedMagSquare = magSquare << leftShift;
        }
        finalLutIndex = roundedMagSquare - 256;
      }

      if ( finalLutIndex >= 768 )
      {
        finalLutIndex = 767;
      }


      lutIdxPtr[(i/2) + ( j * pitch) ] = finalLutIndex;
      log4aPtr[(i/2)  + ( j * pitch) ]  = log4a;
    }
  }
}

void vcop_reciprocal_sqrt_lookup_cn(
                uint16_t    *lutIdxPtr,
                uint8_t     *reciprocalLut,
                uint8_t     *reciprocalLutOutput,
                unsigned short listSize)
{
  uint32_t i;
  uint32_t lutIndex;

  for (i = 0; i < listSize; i++)
  {
    lutIndex = lutIdxPtr[i];
    reciprocalLutOutput[i] = reciprocalLut[ (lutIndex % 4) +
                                      (lutIndex / 4) * 32];
  }

}

void vcop_gradients_xy_unit_vecs_cn(
                        int16_t     *gradXY,
                        int8_t      *log4aPtr,
                        uint8_t     *reciprocalLutOutput,
                        int32_t     *unitXYPtr,
                        unsigned short listSize)
{
  uint32_t i;
  int16_t gx0;
  int16_t gy0;
  int8_t log4a0;
  uint8_t sqRootLut0;
  int16_t unitVecX0;
  int16_t unitVecY0;

  for (i = 0; i < 2 * listSize; i+=2)
  {
    gx0 = gradXY[i];
    gy0 = gradXY[i + 1];

    log4a0 = log4aPtr[(i/2)];

    sqRootLut0 = reciprocalLutOutput[(i/2)];

    unitVecX0 = (gx0 * sqRootLut0)>> (uint32_t)log4a0;

    unitVecY0 = (gy0 * sqRootLut0)>> (uint32_t)log4a0;

    unitXYPtr[(i/2)] = (unitVecY0 << 16U) | (0x0000FFFFU & (uint32_t)unitVecX0);
  }

}




/* ======================================================================== */
/*  End of file:  vcop_vec_gradients_xy_and_magnitude_c.c                   */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */


