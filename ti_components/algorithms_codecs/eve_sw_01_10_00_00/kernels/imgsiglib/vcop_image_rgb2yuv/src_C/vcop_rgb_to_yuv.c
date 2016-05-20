/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/* ===========================================================================*/
/*   @file : vcop_rgb_to_yuv.c                                    */

/*   @brief  : This file contains all functions related to RGB to YUV conversion   */

/*   @author Gajanan Ambi(gajanan.ambi@ti.com)                                */

/*   @version 0.0 (September 2012) : Base version.                               */

/*============================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vcop_rgb_to_yuv.h"

unsigned char CLIP (int x)
{
  unsigned char y;
  y = (x > 255) ? 255: ((x < 0)) ? 0: x;
  return (y);
}

void vcop_rgb_to_yuv
(
unsigned short *r_buff,
unsigned short *g_buff,
unsigned short *b_buff,
unsigned int img_height,
unsigned int img_width,
short       *coefs,
unsigned char *YUV_buff,
unsigned char shift,
unsigned char outputFormat
)
{
  unsigned int i,j;
  
  unsigned short redByte1;
  unsigned short greenByte1;
  unsigned short blueByte1;
  
  unsigned short redByte2;
  unsigned short greenByte2;
  unsigned short blueByte2;

  int temp_y0;
  int temp_y1;
  int temp_u0;
  int temp_v0;
  int temp_ur0;
  int temp_ug0;
  int temp_vb0;
  int temp_vg0;
  
  short coef_ry0  = coefs[0];
  short coef_gy0  = coefs[1];
  short coef_by0  = coefs[2];
  
  short coef_ru0  = coefs[3];
  short coef_gu0  = coefs[4];
  short coef_bu0  = coefs[5];
  
  short coef_rv0  = coefs[6];
  short coef_gv0  = coefs[7];
  short coef_bv0  = coefs[8];

  for(i=0; i<img_height; i++)
  {
    for(j=0; j<(img_width/2); j++)
    {
      //Get First pixel Data            
      redByte1   =  r_buff[(i*img_width)+(2*j)];  
      greenByte1 =  g_buff[(i*img_width)+(2*j)];  
      blueByte1  =  b_buff[(i*img_width)+(2*j)];

      //Get Second Pixel Data     
      redByte2   = r_buff[(i*img_width)+(2*j)+1];  
      greenByte2 = g_buff[(i*img_width)+(2*j)+1];  
      blueByte2  = b_buff[(i*img_width)+(2*j)+1];

      temp_y0    = (coef_ry0*redByte1 + coef_gy0*greenByte1 + coef_by0*blueByte1 + 128) >> (8+shift);
      temp_y1    = (coef_ry0*redByte2 + coef_gy0*greenByte2 + coef_by0*blueByte2 + 128) >> (8+shift);
      
      temp_ur0   = coef_ru0*redByte1;
      temp_ug0   = coef_gu0*greenByte1;
      //temp_u0    = ((temp_ur0 + temp_ug0 + coef_bu0*blueByte1 + 128) >> (8+shift)) + 128;
      temp_u0    = ((temp_ur0 + temp_ug0 + coef_bu0*blueByte1 + 524288) >> (8+shift));
      
      temp_vb0   = coef_bv0*blueByte2;
      temp_vg0   = coef_gv0*greenByte2;
      //temp_v0    = ((temp_vb0 + temp_vg0 + coef_rv0*redByte2 + 128) >> (8+shift)) + 128;
      temp_v0    = ((temp_vb0 + temp_vg0 + coef_rv0*redByte2 + 524288) >> (8+shift));
      
      temp_y0 = CLIP(temp_y0);
      temp_u0 = CLIP(temp_u0);
      temp_y1 = CLIP(temp_y1);
      temp_v0 = CLIP(temp_v0);
      
      if(outputFormat == RGB2YUV_COLOR_FORMAT_UYVY)
      {
        YUV_buff[(i*img_width*2)+(4*j)]   = temp_u0;  
        YUV_buff[(i*img_width*2)+(4*j)+1] = temp_y0;
        YUV_buff[(i*img_width*2)+(4*j)+2] = temp_v0;
        YUV_buff[(i*img_width*2)+(4*j)+3] = temp_y1;
      }
      else
      {
        YUV_buff[(i*img_width*2)+(4*j)]   = temp_y0;  
        YUV_buff[(i*img_width*2)+(4*j)+1] = temp_u0;
        YUV_buff[(i*img_width*2)+(4*j)+2] = temp_y1;
        YUV_buff[(i*img_width*2)+(4*j)+3] = temp_v0;
      }
    }
  }
  
#if 0 // File dump for yuv data
{
  FILE *Fp;
  unsigned char pix;
  Fp = fopen("Reference_yuv.yuv","wb");
  if(Fp == NULL)
  {
    printf("\nERROR !!! : Issue with bayer to yuv file");
  }

  for(i=0; i<img_height; i++)
  {
    for(j=0; j<(img_width*2); j++)
    {
      pix = YUV_buff[(i*img_width*2) + j];
      fwrite(&pix, 1, 1, Fp);
    }
  }
  fclose(Fp);
}
#endif
}

