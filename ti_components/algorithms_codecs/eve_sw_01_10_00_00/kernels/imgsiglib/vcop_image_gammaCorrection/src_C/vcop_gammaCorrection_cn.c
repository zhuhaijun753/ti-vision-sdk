/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/* ===========================================================================*/
/*   @file : vcop_gammaCorrection.c                                    */

/*   @brief  : This file contains all functions Gamma Correction   */

/*   @author Gajanan Ambi(gajanan.ambi@ti.com)                                */

/*   @version 0.0 (September 2012) : Base version.                               */

/*============================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vcop_gammaCorrection_cn.h"

void natc_gamma_correction
(
unsigned short *r_buff,
unsigned short *g_buff,
unsigned short *b_buff,
unsigned short *out_r_buff,
unsigned short *out_g_buff,
unsigned short *out_b_buff,
unsigned int    img_width,
unsigned int    img_height,
unsigned int    input_stride,
unsigned int    output_stride,
short          *LUT
)
{
  unsigned int i,j;

  unsigned short red_12bit;
  unsigned short green_12bit;
  unsigned short blue_12bit;

  unsigned short red_10bit;
  unsigned short green_10bit;
  unsigned short blue_10bit;

  for(i=0; i<img_height; i++)
  {
    for(j=0; j<img_width; j++)
    {
      //Get First pixel Data
      red_12bit   =  r_buff[(i*input_stride)+j];
      green_12bit =  g_buff[(i*input_stride)+j];
      blue_12bit  =  b_buff[(i*input_stride)+j];

      red_10bit   = red_12bit>>2;
      green_10bit = green_12bit>>2;
      blue_10bit  = blue_12bit>>2;

      red_10bit   = LUT[((red_10bit>>2)<<4) + (red_10bit&0x3)]; /* we use the same TLU as the kernel-C version. The table has been reformatted in order take advantage of parallel lookup in kernel-C */
      green_10bit = LUT[((green_10bit>>2)<<4) + (green_10bit&0x3)];
      blue_10bit  = LUT[((blue_10bit>>2)<<4) + (blue_10bit&0x3)];

      red_12bit   = red_10bit<<2;
      green_12bit = green_10bit <<2;
      blue_12bit  = blue_10bit <<2;

      out_r_buff[(i*output_stride)+j] = red_12bit;
      out_g_buff[(i*output_stride)+j] = green_12bit;
      out_b_buff[(i*output_stride)+j] = blue_12bit ;
    }
  }
}

