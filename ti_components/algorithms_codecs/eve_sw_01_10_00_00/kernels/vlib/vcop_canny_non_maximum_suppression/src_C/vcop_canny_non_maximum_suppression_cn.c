/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME                                                                 */
/*     vcop_canny_non_maximum_suppression_cn                                */
/*                                                                          */
/*                                                                          */
/*     USAGE                                                                */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_canny_non_maximum_suppression_cn                           */
/*     (                                                                    */
/*         short          pMag[],                                           */
/*         short          pGx[],                                            */
/*         short          pGy[],                                            */
/*         unsigned char  pEdge[],                                          */
/*         int            Mag2_array[],                                     */
/*         unsigned char  Index[],                                          */
/*         int            mag1_array[],                                     */
/*         int            mag3_array[],                                     */
/*         unsigned short width,                                            */
/*         unsigned short pitch,                                            */
/*         unsigned short height                                            */
/*      )                                                                   */
/*                                                                          */
/*     pMag       :  Gradient Magnitude array                               */
/*     pGx        :  Gradient in X direction array                          */
/*     pGy        :  Gradient in Y direction array                          */
/*     pEdge      :  Non-maximum suppressed Edge array                      */
/*     Index      :  Temporary array to store the edge indices              */
/*     mag1_array :  Non-maximum suppressed Edge array                      */
/*     mag3_array :  Non-maximum suppressed Edge array                      */
/*     Mag2_array :  Non-maximum suppressed Edge array                      */
/*     width      :  width of pMag,pGx and pGy images                       */
/*     pitch      :  width of pMag,pGx and pGy images                       */
/*     height     :  width of pMag,pGx and pGy images                       */
/*                                                                          */
/*     Returns :  None or void.                                             */
/*                                                                          */
/*                                                                          */
/*     DESCRIPTION                                                          */
/*             This routine accepts an pGx,pGy and pMag arrays and outputs  */
/*     the non-maxima suppressed edge image in pEdge array.                 */
/*                                                                          */
/*     ASSUMPTIONS                                                          */
/*                                                                          */
/*                                                                          */
/*==========================================================================*/
/*      Copyright (C) 2010 Texas Instruments Incorporated.                  */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#include <stdio.h>
#include <stdint.h>

#include <stdlib.h>
#include <math.h>
#include <string.h>

#define Q_FORMAT_SHIFT (14U)
#define TAN_22_5_Q (6786)
#define TAN_67_5_Q (39554)

void vcop_canny_bin_indexing_cn(
    int16_t   *pGx,
    int16_t   *pGy,
    uint8_t   *pIndex,
    uint16_t   computeWidth,
    uint16_t   computeHeight,
    uint16_t   pitch)
{
  uint32_t i, j;
  uint8_t currentIndex;
  int16_t gx, gy;
  uint32_t absGx, absGyQ;
  uint8_t condition1, condition2, condition3;

  for ( j = 0 ; j < computeHeight; j++ )
  {
    for ( i = 0 ; i < computeWidth; i++)
    {
      gx = pGx[i + j * pitch];
      gy = pGy[i + j * pitch];

      absGx =  abs(gx);
      absGyQ =  (abs(gy) << Q_FORMAT_SHIFT);

      condition1 = ( absGyQ > absGx * TAN_22_5_Q );
      condition2 = ( absGyQ  > absGx * TAN_67_5_Q );
      condition3 = (( gx ^ gy ) < 0 );

      currentIndex = (condition1 << 2 ) | ( condition2 << 1) | (condition3 );

      pIndex[i + j * pitch] = currentIndex;
    }
  }

}

#define MAX(a,b) ((a)>(b) ? (a) : (b))

void vcop_canny_nms_max_cases_cn
(
    uint16_t   *pMag,
    uint16_t   *pCase1Max,
    uint16_t   *pCase2Max,
    uint16_t   *pCase3Max,
    uint16_t   *pCase4Max,
    uint16_t computeWidth,
    uint16_t computeHeight,
    uint16_t pitch
)

{
  uint32_t i, j;
  uint16_t topL, topC, topR;
  uint16_t midL, midC, midR;
  uint16_t botL, botC, botR;
  uint16_t maxVal;

  for ( j = 0 ; j < computeHeight; j++ )
  {
    for ( i = 0 ; i < computeWidth; i++)
    {
      topL = pMag[i + j * pitch + 0];
      topC = pMag[i + j * pitch + 1];
      topR = pMag[i + j * pitch + 2];

      midL = pMag[i + (j + 1) * pitch + 0];
      midC = pMag[i + (j + 1) * pitch + 1];
      midR = pMag[i + (j + 1) * pitch + 2];

      botL = pMag[i + (j + 2) * pitch + 0];
      botC = pMag[i + (j + 2) * pitch + 1];
      botR = pMag[i + (j + 2) * pitch + 2];

      maxVal = MAX( midL, midR );
      pCase1Max[ i + j * pitch] = (midC >= maxVal) ? midC : 0;

      maxVal = MAX( topC, botC );
      pCase3Max[ i + j * pitch] = (midC >= maxVal) ? midC : 0;

      maxVal = MAX( topL, botR );
      pCase4Max[ i + j * pitch] = (midC >= maxVal) ? midC : 0;

      maxVal = MAX( botL, topR );
      pCase2Max[ i + j * pitch] = (midC >= maxVal) ? midC : 0;
    }


  }

}

void vcop_canny_nms_double_thresholding_cn
(
    uint8_t    *pIndex,
    uint16_t   *pCase1Max,
    uint16_t   *pCase2Max,
    uint16_t   *pCase3Max,
    uint16_t   *pCase4Max,
    uint8_t    *pOutVal,
    uint8_t     lowThreshold,
    uint8_t     highThreshold,
    uint16_t width,
    uint16_t height,
    uint16_t pitch,
    uint16_t outputPitch
)
{
  uint32_t i, j;
  uint8_t currentCase;
  uint16_t centerPix;
  uint8_t outVal;
  for ( j = 0 ; j < height; j++ )
  {
    for ( i = 0 ; i < width; i++)
    {
      currentCase = pIndex[(i + 1) + (j + 1) * pitch];
      if ( currentCase < 4)
      {
        centerPix = pCase1Max[i + j * pitch];
      }
      else if( currentCase == 4)
      {
        centerPix = pCase2Max[i + j * pitch];
      }
      else if( currentCase == 5)
      {
        centerPix = pCase4Max[i + j * pitch];
      }
      else
      {
        centerPix = pCase3Max[i + j * pitch];
      }

      if ( centerPix < lowThreshold )
      {
        outVal = 0;
      }
      else
      {
        if ( centerPix < highThreshold )
        {
          outVal = 1;
        }
        else
        {
          outVal = 255;
        }
      }
      pOutVal[i + j * outputPitch] = outVal;

    }
  }
}

/* ======================================================================== */
/*  End of file:  vcop_canny_non_maximum_suppression_cn.c                    */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2012 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */


