/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#include "stdint.h"
#include "vcop_fast9score_c.h"
#include "fast9_score_bftf.h"

#include <stdlib.h>

#define N_POINTS (32)
#define MIN(a, b) ((a) < (b) ? (a) : (b))

static unsigned char lut_index_sad[136] =
{
     3,  3,  3,  3,  3,  3,  3,  3,
     4,  4,  4,  4,  4,  4,  4,  4,
    13, 13, 13, 13, 13, 13, 13, 13,
    22, 22, 22, 22, 22, 22, 22, 22,
    30, 30, 30, 30, 30, 30, 30, 30,
    38, 38, 38, 38, 38, 38, 38, 38,
    45, 45, 45, 45, 45, 45, 45, 45,
    52, 52, 52, 52, 52, 52, 52, 52,
    51, 51, 51, 51, 51, 51, 51, 51,
    50, 50, 50, 50, 50, 50, 50, 50,
    41, 41, 41, 41, 41, 41, 41, 41,
    32, 32, 32, 32, 32, 32, 32, 32,
    24, 24, 24, 24, 24, 24, 24, 24,
    16, 16, 16, 16, 16, 16, 16, 16,
     9,  9,  9,  9,  9,  9,  9,  9,
     2,  2,  2,  2,  2,  2,  2,  2,
    27, 27, 27, 27, 27, 27, 27, 27
};

static unsigned char lut_index_thresh[200] =
{
     3,  3,  3,  3,  3,  3,  3,  3,
     4,  4,  4,  4,  4,  4,  4,  4,
    13, 13, 13, 13, 13, 13, 13, 13,
    22, 22, 22, 22, 22, 22, 22, 22,
    30, 30, 30, 30, 30, 30, 30, 30,
    38, 38, 38, 38, 38, 38, 38, 38,
    45, 45, 45, 45, 45, 45, 45, 45,
    52, 52, 52, 52, 52, 52, 52, 52,
    51, 51, 51, 51, 51, 51, 51, 51,
    50, 50, 50, 50, 50, 50, 50, 50,
    41, 41, 41, 41, 41, 41, 41, 41,
    32, 32, 32, 32, 32, 32, 32, 32,
    24, 24, 24, 24, 24, 24, 24, 24,
    16, 16, 16, 16, 16, 16, 16, 16,
     9,  9,  9,  9,  9,  9,  9,  9,
     2,  2,  2,  2,  2,  2,  2,  2,
     3,  3,  3,  3,  3,  3,  3,  3,
     4,  4,  4,  4,  4,  4,  4,  4,
    13, 13, 13, 13, 13, 13, 13, 13,
    22, 22, 22, 22, 22, 22, 22, 22,
    30, 30, 30, 30, 30, 30, 30, 30,
    38, 38, 38, 38, 38, 38, 38, 38,
    45, 45, 45, 45, 45, 45, 45, 45,
    52, 52, 52, 52, 52, 52, 52, 52,
    27, 27, 27, 27, 27, 27, 27, 27
};

int FAST9ScoreCompute(
    unsigned char *src,
    unsigned short srcImageWidth,
    unsigned short srcImageHeight,
    unsigned short srcBufferPitch,
    unsigned int   * cornerListXY,
    unsigned int   cornerListSize,
    unsigned char  fast9Th,
    unsigned char  sad_method,
    unsigned short *outScore
)
{

  unsigned char *intBuf = (unsigned char *) malloc(N_POINTS * 8 *8);
  short x, y, row, col ;
  unsigned char *tempSrc, *tempDst ;
  unsigned int i, keyPoints, k ;

  for(i =0 ; i < cornerListSize ; i+= N_POINTS)
  {
    /*-------------------------------------------------------------------*/
    /* Do N points together and take care of last if N are not remaining */
    /*-------------------------------------------------------------------*/
    keyPoints  = MIN(N_POINTS, cornerListSize - i);

    /*-------------------------------------------------------------------*/
    /* Copy 8x8 region around the key point to a linear memory           */
    /*-------------------------------------------------------------------*/
    for(k = 0 ; k < keyPoints; k++)
    {
      y = cornerListXY[i + k] & 0xFFFF ;
      x = cornerListXY[i + k] >> 16 ;

      /*-------------------------------------------------*/
      /* Come to top left of the block as x,y are center */
      /*-------------------------------------------------*/
      x -= 3 ;
      y -= 3 ;

      /*--------------------------------*/
      /* Copy the content in 8x8 region */
      /*--------------------------------*/
      for(row = 0; row < 8 ; row++)
      {
        for(col = 0; col < 8 ; col++)
        {
          tempDst  = intBuf + k*8*8 + row*8 + col ;
          tempSrc  = src    + (row + y)*srcBufferPitch + (col + x);
          *tempDst = *tempSrc ;
        }
      }
    }
    /*--------------------------------------*/
    /* Get the score of N Key points        */
    /*--------------------------------------*/

  if(sad_method)
    {
        fast9_sad_score(intBuf,
          (unsigned short)keyPoints,
          lut_index_sad,
          fast9Th,
          (outScore + i));
    }
  else
    {
      fast9_thresh_score(intBuf,
              (unsigned short)keyPoints,
              lut_index_thresh,
              fast9Th,
              (outScore+i));
    }

  }
  free(intBuf);
  return 0 ;

}

