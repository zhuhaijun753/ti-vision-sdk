/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/


#include <stdio.h>
#include <stdlib.h>

#include "vcop_image_pyramid_u16_c.h"

void vcop_image_pyramid_uv_u8
(
  unsigned char  *pIn,
  unsigned int    blk_width,
  unsigned int    blk_height,
  unsigned char  *pOut
)
{
  unsigned int i,j;
  unsigned char pix_00,pix_01,pix_10,pix_11;
  unsigned int temp; 
  unsigned int rnd_bits = 2;
  for(i = 0; i<blk_height; i = i+2)
  {
    for(j = 0; j<blk_width; j = j+4)
    {
      pix_00 = pIn[(i*blk_width)+j];
      pix_01 = pIn[(i*blk_width)+j+2];
      pix_10 = pIn[((i+1)*blk_width)+j];
      pix_11 = pIn[((i+1)*blk_width)+j+2];

      temp = pix_00+pix_01+pix_10+pix_11;

      temp = temp + (1<<(rnd_bits - 1));
      *pOut++ = temp>>rnd_bits;

      pix_00 = pIn[(i*blk_width)+(j+1)];
      pix_01 = pIn[(i*blk_width)+(j+1)+2];
      pix_10 = pIn[((i+1)*blk_width)+(j+1)];
      pix_11 = pIn[((i+1)*blk_width)+(j+1)+2];

      temp = pix_00+pix_01+pix_10+pix_11;

      temp = temp + (1<<(rnd_bits - 1));
      *pOut++ = temp>>rnd_bits;
      
    }
  }
}

