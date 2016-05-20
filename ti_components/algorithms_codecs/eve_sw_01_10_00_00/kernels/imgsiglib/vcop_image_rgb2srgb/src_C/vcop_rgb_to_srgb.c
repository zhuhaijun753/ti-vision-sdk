/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/* ===========================================================================*/
/*   @file : vcop_rgb_to_srgb.c                                    */

/*   @brief  : This file contains all functions related to RGB to sRGB conversion   */

/*   @author Gajanan Ambi(gajanan.ambi@ti.com)                                */

/*   @version 0.0 (September 2012) : Base version.                               */

/*============================================================================*/

#include "vcop_rgb_to_srgb.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned short CLIP_16bit (int x)
{
  unsigned short y;
  //y = (x > 65535) ? 65535: ((x < 0)) ? 0: x;
  y = (x > 4095) ? 4095: ((x < 0)) ? 0: x;
  return (y);
}

void vcop_rgb_to_srgb
(
  unsigned short *r_buff,
  unsigned short *g_buff,
  unsigned short *b_buff,
  unsigned int    img_height,
  unsigned int    img_width,
  short          *coefs
)
{
  unsigned int i,j;
  
  unsigned short redByte;
  unsigned short greenByte;
  unsigned short blueByte;

  int temp_r;
  int temp_g;
  int temp_b;
  
  short coef_0  = coefs[0];
  short coef_1  = coefs[1];
  short coef_2  = coefs[2];
  
  short coef_3  = coefs[3];
  short coef_4  = coefs[4];
  short coef_5  = coefs[5];
  
  short coef_6  = coefs[6];
  short coef_7  = coefs[7];
  short coef_8  = coefs[8];

  for(i=0; i<img_height; i++)
  {
    for(j=0; j<img_width; j++)
    {
      /*Get input pixel Data   */         
      redByte   =  r_buff[(i*img_width)+j];  
      greenByte =  g_buff[(i*img_width)+j];  
      blueByte  =  b_buff[(i*img_width)+j];

      /*Appy the conversion filter*/         
      temp_r    = (coef_0*redByte + coef_1*greenByte + coef_2*blueByte + 128)>>8;
      temp_g    = (coef_3*redByte + coef_4*greenByte + coef_5*blueByte + 128)>>8;
      temp_b    = (coef_6*redByte + coef_7*greenByte + coef_8*blueByte + 128)>>8;
      
      /*Saturate to 16-bit data*/         
      temp_r = CLIP_16bit(temp_r);
      temp_g = CLIP_16bit(temp_g);
      temp_b = CLIP_16bit(temp_b);
       
      /*Store back converted data in output memory*/         
      r_buff[(i*img_width)+j] = temp_r;  
      g_buff[(i*img_width)+j] = temp_g;  
      b_buff[(i*img_width)+j] = temp_b;  
     }
  }

#if 0 //Bayer to rgb dump
{
 FILE *Fp;
 Fp = fopen("RGB_TO_sRGB_1280x736.raw","wb");
 if(Fp == NULL)
 {
   printf("\nERROR !!! : Issue with bayer to rgb file");
 }
 
 for(i=0; i<img_height; i++)
 {
   for(j=0; j<img_width; j++)
   {
     unsigned short R = r_buff[i*img_width+j];
     unsigned short G = g_buff[i*img_width+j];
     unsigned short B = b_buff[i*img_width+j];

     unsigned char r = R >> 4;
     unsigned char g = G >> 4;
     unsigned char b = B >> 4;

     fwrite(&r, 1, 1, Fp);
     fwrite(&g, 1, 1, Fp);
     fwrite(&b, 1, 1, Fp);
   }
 }
 fclose(Fp);
}
#endif
}

