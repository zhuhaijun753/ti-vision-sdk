/*==========================================================================*/
/*      Copyright (C) 2009-2014 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*                                                                          */
/*     NAME                                                                 */
/*     vcop_nxn_block_sum_cn.c                                              */
/*                                                                          */
/*     DESCRIPTION                                `                         */
/*         This is the c-reference implementation for the                   */
/*         nx bloc sum of 8 bit or 16 bit data                              */
/*                                                                          */
/*                                                                          */
/*     @version 0.1 (May 2014) : Base version.                              */
/*                                                                          */
/*==========================================================================*/
#include "stdlib.h"
#include "vcop_nxn_block_sum_cn.h"

void vcop_nxn_sum_u8_cn
(
  unsigned char  *   inPtr1,
  unsigned char  *   inPtr2,
  unsigned short *   outPtr1,
  unsigned short *   outPtr2,
  unsigned short     n,
  unsigned short     width,
  unsigned short     height,
  unsigned short     pitch1,
  unsigned short     pitch2
)
{
  int i, j, k, l;

  for(i = 0; i < height; i+=n)
  {
    for(j = 0; j < width; j+=n)
    {
      outPtr1[(i/n)*(width/n) + (j/n)] = 0;
      outPtr2[(i/n)*(width/n) + (j/n)] = 0;
      for(k = 0; k < n; k++)
      {
        for(l = 0; l < n; l++)
        {
          outPtr1[(i/n)*(width/n) + (j/n)] += inPtr1[i*pitch1+j + k*pitch1+l];
          outPtr2[(i/n)*(width/n) + (j/n)] += inPtr2[i*pitch2+j + k*pitch2+l];
        }
      }
    }
  }

}

void vcop_nxn_sum_u16_cn
(
  unsigned short *   inPtr1,
  unsigned short *   inPtr2,
  unsigned short *   outPtr1,
  unsigned short *   outPtr2,
  unsigned short     n,
  unsigned short     width,
  unsigned short     height,
  unsigned short     pitch1,
  unsigned short     pitch2
)
{
  int i, j, k, l;

  for(i = 0; i < height; i+=n)
  {
    for(j = 0; j < width; j+=n)
    {
      outPtr1[(i/n)*(width/n) + (j/n)] = 0;
      outPtr2[(i/n)*(width/n) + (j/n)] = 0;
      for(k = 0; k < n; k++)
      {
        for(l = 0; l < n; l++)
        {
          outPtr1[(i/n)*(width/n) + (j/n)] += inPtr1[i*pitch1+j + k*pitch1+l];
          outPtr2[(i/n)*(width/n) + (j/n)] += inPtr2[i*pitch2+j + k*pitch2+l];
        }
      }
    }
  }
}

void vcop_nxn_sum_interleaved_cn
(
  unsigned char *   inPtr,
  unsigned short *   outPtr1,
  unsigned short *   outPtr2,
  unsigned short     n,
  unsigned short     width,
  unsigned short     height,
  unsigned short     pitch,
  unsigned short     shiftValue
)
{
  int i, j, k, l;

    for(i = 0; i < height; i+=n)
    {
      for(j = 0; j < width; j+=n)
      {
          outPtr1[(i/n)*(width/n) + (j/n)] = 0;
          outPtr2[(i/n)*(width/n) + (j/n)] = 0;
          for(k = 0; k < n; k++)
          {
            for(l = 0; l < n; l++)
            {
              outPtr1[(i/n)*(width/n) + (j/n)] += inPtr[i*pitch*2+j*2 + k*pitch*2+l*2];
              outPtr2[(i/n)*(width/n) + (j/n)] += inPtr[i*pitch*2+j*2 + k*pitch*2+l*2+1];
            }
          }
          outPtr1[(i/n)*(width/n) + (j/n)] <<= shiftValue;
          outPtr2[(i/n)*(width/n) + (j/n)] <<= shiftValue;
       }
    }
}
