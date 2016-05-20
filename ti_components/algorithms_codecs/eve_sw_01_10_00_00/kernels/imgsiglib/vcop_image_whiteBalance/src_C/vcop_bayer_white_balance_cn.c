/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/* ===========================================================================*/
/*   @file : vcop_bayer_white_balance.c                                    */

/*   @brief  : This file contains all the header files RGB to yuv conversion   */

/*   @author Gajanan Ambi(gajanan.ambi@ti.com)                                */

/*   @version 0.0 (September 2012) : Base version.                               */

/*============================================================================*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "vcop_bayer_white_balance_cn.h"

void natc_bayer_white_balance
(
unsigned short *in_buff,
unsigned short *out_buff,
unsigned int    img_width,
unsigned int    img_height,
unsigned int    gainFactor_R,
unsigned int    gainFactor_Gb,
unsigned int    gainFactor_Gr,
unsigned int    gainFactor_B,
unsigned int    gainFactor_shift,
unsigned int    input_stride,
unsigned int    output_stride,
unsigned char   bayerFormat
)
{
  unsigned int i,j;
  unsigned short pix_R,pix_Gb,pix_Gr,pix_B, round;

  if (gainFactor_shift>0) {
      round= 1<<(gainFactor_shift-1);
  }

  img_width= ((img_width/16) + 1)*16; /* Victor: to match kernel-C code although it is not the correct way */
  img_height+= 2; /* Victor: to match kernel-C code although it is not the correct way */

  if(bayerFormat == BGGR)
  {
    for(i = 0; i<img_height; i=i+2)
    {
      for(j = 0; j<img_width; j=j+2)
      {
        pix_B  = in_buff[(i*input_stride) + j];
        pix_Gb = in_buff[(i*input_stride) + j + 1];
        pix_Gr = in_buff[(i+1)*input_stride + j];
        pix_R  = in_buff[(i+1)*input_stride + j + 1];

        pix_B  = (pix_B*gainFactor_B + round)>>gainFactor_shift;
        pix_Gb = (pix_Gb*gainFactor_Gb + round)>>gainFactor_shift;
        pix_Gr = (pix_Gr*gainFactor_Gr + round)>>gainFactor_shift;
        pix_R  = (pix_R*gainFactor_R + round)>>gainFactor_shift;

        out_buff[(i*output_stride) + j]       = pix_B;
        out_buff[(i*output_stride) + j + 1]   = pix_Gb;
        out_buff[(i+1)*output_stride + j    ] = pix_Gr;
        out_buff[(i+1)*output_stride + j + 1] = pix_R;
      }
    }
  }
  else if(bayerFormat == GRBG)
  {
    for(i = 0; i<img_height; i=i+2)
    {
      for(j = 0; j<img_width; j=j+2)
      {
        pix_Gr = in_buff[(i*input_stride) + j];
        pix_R  = in_buff[(i*input_stride) + j + 1];
        pix_B  = in_buff[(i+1)*input_stride + j];
        pix_Gb = in_buff[(i+1)*input_stride + j + 1];

        pix_B  = (pix_B*gainFactor_B + round)>>gainFactor_shift;
        pix_Gb = (pix_Gb*gainFactor_Gb + round)>>gainFactor_shift;
        pix_Gr = (pix_Gr*gainFactor_Gr + round)>>gainFactor_shift;
        pix_R  = (pix_R*gainFactor_R + round)>>gainFactor_shift;

        out_buff[(i*output_stride) + j]       = pix_Gr;
        out_buff[(i*output_stride) + j + 1]   = pix_R;
        out_buff[(i+1)*output_stride + j    ] = pix_B;
        out_buff[(i+1)*output_stride + j + 1] = pix_Gb;
      }
    }
  }
  else if(bayerFormat == RGGB)
  {
    for(i = 0; i<img_height; i=i+2)
    {
      for(j = 0; j<img_width; j=j+2)
      {
        pix_R  = in_buff[(i*input_stride) + j];
        pix_Gb = in_buff[(i*input_stride) + j + 1];
        pix_Gr = in_buff[(i+1)*input_stride + j];
        pix_B  = in_buff[(i+1)*input_stride + j + 1];

        pix_B  = (pix_B*gainFactor_B + round)>>gainFactor_shift;
        pix_Gb = (pix_Gb*gainFactor_Gb + round)>>gainFactor_shift;
        pix_Gr = (pix_Gr*gainFactor_Gr + round)>>gainFactor_shift;
        pix_R  = (pix_R*gainFactor_R + round)>>gainFactor_shift;

        out_buff[(i*output_stride) + j]       = pix_R;
        out_buff[(i*output_stride) + j + 1]   = pix_Gb;
        out_buff[(i+1)*output_stride + j    ] = pix_Gr;
        out_buff[(i+1)*output_stride + j + 1] = pix_B;
      }
    }
  }
  else if(bayerFormat == GBRG)
  {
    for(i = 0; i<img_height; i=i+2)
    {
      for(j = 0; j<img_width; j=j+2)
      {
        pix_Gb = in_buff[(i*input_stride) + j];
        pix_B  = in_buff[(i*input_stride) + j + 1];
        pix_R  = in_buff[(i+1)*input_stride + j];
        pix_Gr = in_buff[(i+1)*input_stride + j + 1];

        pix_B  = (pix_B*gainFactor_B + round)>>gainFactor_shift;
        pix_Gb = (pix_Gb*gainFactor_Gb + round)>>gainFactor_shift;
        pix_Gr = (pix_Gr*gainFactor_Gr + round)>>gainFactor_shift;
        pix_R  = (pix_R*gainFactor_R + round)>>gainFactor_shift;

        out_buff[(i*output_stride) + j]       = pix_Gb;
        out_buff[(i*output_stride) + j + 1]   = pix_B;
        out_buff[(i+1)*output_stride + j    ] = pix_R;
        out_buff[(i+1)*output_stride + j + 1] = pix_Gr;
      }
    }
  }
  else
  {
    //PRINTF("\n Unsupported input bayer format");
  }
#if 0 //Bayer white balance dump
{
  FILE *Fp;
  Fp = fopen("Bayer_white_balance_1280x736.raw","wb");
  if(Fp == NULL)
  {
    printf("\nERROR !!! : Issue with bayer to rgb file");
  }

  for(i=0; i<img_height; i++)
  {
    for(j=0; j<img_width; j++)
    {
      unsigned short pix = in_buff[i*img_width+j];
      fwrite(&pix, 1, sizeof(short), Fp);
    }
  }
  fclose(Fp);
}
#endif

}

