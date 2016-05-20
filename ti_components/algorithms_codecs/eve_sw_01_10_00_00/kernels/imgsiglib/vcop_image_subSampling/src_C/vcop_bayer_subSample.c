/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/* ===========================================================================*/
/*   @file : vcop_bayer_subSample.c                                    */

/*   @brief  :    */

/*   @author Gajanan Ambi(gajanan.ambi@ti.com)                                */

/*   @version 0.0 (November 2012) : Base version.                               */

/*============================================================================*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "vcop_bayer_subSample.h"

void vcop_bayer_subSample
(
unsigned short *in_buff,
unsigned short *out_buff,
unsigned int img_width,
unsigned int img_height,
unsigned int subSample_x,
unsigned int subSample_y,
unsigned int numOfSamples
)
{
  unsigned int i,j,samples,w,h;
  unsigned short pix_R,pix_Gb,pix_Gr,pix_B;
  unsigned int numOfBlocks_X/*,numOfBlocks_Y*/;

  numOfBlocks_X = img_width/subSample_x;
  /*numOfBlocks_Y = img_height/subSample_y;*/
  
  for(i=0,h = 0; i<img_height; i=i+subSample_y,h = h+2)
  {
    for(j=0,w = 0; j<img_width; j=j+subSample_x,w = w+(2*numOfSamples))
    {
      for(samples = 0; samples<(numOfSamples); samples++)
      {
        pix_B  = in_buff[(i*img_width) + (j) + (samples*2)];
        pix_Gb = in_buff[(i*img_width) + (j) + (samples*2) + 1];
        pix_Gr = in_buff[((i+1)*img_width) + (j) + (samples*2)];
        pix_R  = in_buff[((i+1)*img_width) + (j) + (samples*2) + 1];

        out_buff[(h *numOfBlocks_X * numOfSamples *2)+w + (samples*2)]       = pix_B;
        out_buff[(h *numOfBlocks_X * numOfSamples *2)+w + (samples*2) + 1]   = pix_Gb;
        out_buff[((h+1) *numOfBlocks_X * numOfSamples *2)+w + (samples*2)]   = pix_Gr;
        out_buff[((h+1) *numOfBlocks_X * numOfSamples *2)+w + (samples*2)+1] = pix_R;
      }
    }
  }
#if 0 //Sub-Sampled bayer dump
  {
    FILE *Fp;
    Fp = fopen("Reference_Bayer_SubSampleOut.raw","wb");
    if(Fp == NULL)
    {
      printf("\nERROR !!! : Issue with bayer to rgb file");
    }

    fwrite(out_buff,((img_width/16)*4*(img_height/16)),sizeof(short),Fp);    
    fclose(Fp);
  }
#endif
}

                  
