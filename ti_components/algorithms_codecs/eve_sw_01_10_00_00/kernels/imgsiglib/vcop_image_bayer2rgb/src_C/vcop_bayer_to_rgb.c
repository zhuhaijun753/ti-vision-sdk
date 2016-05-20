/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/* ===========================================================================*/
/*   @file : vcop_reference_bayerCFA_interpolate.c                                    */

/*   @brief  : This file contains all functions related to bayer to RGB conversion   */

/*   @author Gajanan Ambi(gajanan.ambi@ti.com)                                */

/*   @version 0.0 (September 2012) : Base version.                               */

/*============================================================================*/

#include "vcop_bayer_to_rgb.h"

/* ===========================================================================*/
/* ===========================================================================*/
void vcop_bayer_to_rgb
(
 unsigned short *in_buff,
 unsigned short *Rbuff,
 unsigned short *Gbuff,
 unsigned short *Bbuff,
 unsigned int  img_height,
 unsigned int  img_width,
 unsigned char bayerFormat
)
{
  unsigned int i,j;
  unsigned int Roffset,Goffset1,Goffset2,Boffset,outOffset1,outOffset2;
  unsigned short Bright,Bleft,Rright,Rleft,Gright,Gleft;
  unsigned short Btop,Bbottom,Rtop,Rbottom;

  if(bayerFormat == BGGR)
  {
    for(i=0; i<(img_height/2); i++)
    {
      for(j=0; j<(img_width/2); j++)
      {
        Boffset   = (i * 2 * img_width) + (j * 2);
        Goffset1  = (i * 2 * img_width) + ((j * 2) + 1);
        Goffset2  = (((i * 2) + 1) * img_width) + (j * 2);
        Roffset   = (((i * 2) + 1) * img_width) + (j * 2) + 1;

        outOffset1 = (i * 2 * img_width) + (j * 2);
        outOffset2 = ((i * 2 + 1) * img_width) + (j * 2);
        
        Rbuff[outOffset1] = in_buff[Roffset];
        Bbuff[outOffset1] = in_buff[Boffset];
        Gbuff[outOffset1] = in_buff[Goffset1];
        Gbuff[outOffset2] = in_buff[Goffset2];
      }
    }
  }
  else if(bayerFormat == GRBG)
  {
    for(i=0; i<(img_height/2); i++)
    {
      for(j=0; j<(img_width/2); j++)
      {
        Goffset1  = (i * 2 * img_width) + (j * 2);
        Roffset   = (i * 2 * img_width) + ((j * 2) + 1);
        Boffset   = (((i * 2) + 1) * img_width) + (j * 2);
        Goffset2  = (((i * 2) + 1) * img_width) + (j * 2) + 1;
  
        outOffset1 = (i * 2 * img_width) + (j * 2);
        outOffset2 = ((i * 2 + 1) * img_width) + (j * 2);
        
        Rbuff[outOffset1] = in_buff[Roffset];
        Bbuff[outOffset1] = in_buff[Boffset];
        Gbuff[outOffset1] = in_buff[Goffset1];
        Gbuff[outOffset2] = in_buff[Goffset2];
      }
    }
  }
  else if(bayerFormat == RGGB)
  {
    for(i=0; i<(img_height/2); i++)
    {
      for(j=0; j<(img_width/2); j++)
      {
        Roffset  = (i * 2 * img_width) + (j * 2);
        Goffset1 = (i * 2 * img_width) + ((j * 2) + 1);
        Goffset2 = (((i * 2) + 1) * img_width) + (j * 2);
        Boffset  = (((i * 2) + 1) * img_width) + (j * 2) + 1;
  
        outOffset1 = (i * 2 * img_width) + (j * 2);
        outOffset2 = ((i * 2 + 1) * img_width) + (j * 2);
        
        Rbuff[outOffset1] = in_buff[Roffset];
        Bbuff[outOffset1] = in_buff[Boffset];
        Gbuff[outOffset1] = in_buff[Goffset1];
        Gbuff[outOffset2] = in_buff[Goffset2];
      }
    }
  }
  else if(bayerFormat == GBRG)
  {
    for(i=0; i<(img_height/2); i++)
    {
      for(j=0; j<(img_width/2); j++)
      {
        Goffset1 = (i * 2 * img_width) + (j * 2);
        Boffset  = (i * 2 * img_width) + ((j * 2) + 1);
        Roffset  = (((i * 2) + 1) * img_width) + (j * 2);
        Goffset2 = (((i * 2) + 1) * img_width) + (j * 2) + 1;
  
        outOffset1 = (i * 2 * img_width) + (j * 2);
        outOffset2 = ((i * 2 + 1) * img_width) + (j * 2);
        
        Rbuff[outOffset1] = in_buff[Roffset];
        Bbuff[outOffset1] = in_buff[Boffset];
        Gbuff[outOffset1] = in_buff[Goffset1];
        Gbuff[outOffset2] = in_buff[Goffset2];
      }
    }
  }
  else
  {
    printf("\n Unsupported input bayer format");
  }
  
  /*------------------------------------------------------------*/
  /* Interpolation Step 1 (Horizontal compute):                 */
  /* ------------------------------------------                 */
  /* Where bx = (Bleft + Bright)/2                              */
  /*                                                            */
  /* Where rx = (Rleft + Rright)/2                              */
  /*                                                            */
  /*------------------------------------------------------------*/
  for(i=0; i<(img_height/2); i++)
  {
    for(j=0; j<(img_width/2); j++)
    {
      Bleft  =  Bbuff[(i * 2 * img_width) + (j * 2)];
      Bright =  Bbuff[(i * 2 * img_width) + (j * 2) + 2];
      
      Rleft  =  Rbuff[(i * 2 * img_width) + (j * 2)];
      Rright =  Rbuff[(i * 2 * img_width) + (j * 2) + 2];
      
      Bbuff[(i * 2 * img_width) + (j * 2) + 1] = (Bleft + Bright) >> 1;
      Rbuff[(i * 2 * img_width) + (j * 2) + 1] = (Rleft + Rright) >> 1;
    }
  }

  /*------------------------------------------------------------*/
  /* Where gx = (Gleft + Gright)/2                              */
  /*------------------------------------------------------------*/

  for(i=0; i<img_height; i++)
  {
    for(j=0; j<(img_width/2); j++)
    {
      Gleft  =  Gbuff[(i * 1 * img_width) + (j * 2)];
      Gright =  Gbuff[(i * 1 * img_width) + (j * 2) + 2];
      
      Gbuff[(i * 1 * img_width) + (j * 2) + 1] = (Gleft + Gright) >> 1;
    }
  }

  /*------------------------------------------------------------*/
  /* Interpolation Step 2 (Vertical compute):                   */
  /* ------------------------------------------                 */
  /* Here by = (Btop  + Bbottom)/2                              */
  /* Also bz = (Bleft + Bright + Btop + Bbottom)/4              */
  /* This can be also computed in a 2nd pass as:                */
  /* bz = (Btop_new + Bbottom_new)/2                            */
  /*                                                            */
  /* Here ry = (Rtop  + Rbottom)/2                              */
  /* Also rz = (Rleft + Rright + Rtop + Rbottom)/4              */
  /* This can be also computed in a 2nd pass as:                */
  /* rz = (Rtop_new + Rbottom_new)/2                            */
  /*                                                            */
  /*------------------------------------------------------------*/

  for(i=0; i<(img_height/2); i++)
  {
    for(j=0; j<img_width; j++)
    {
      Btop     =  Bbuff[(i * 2 * img_width) + j];
      Bbottom  =  Bbuff[(((i * 2) + 2) * img_width) + j];
      
      Rtop     =  Rbuff[(i * 2 * img_width) + (j * 1)];
      Rbottom  =  Rbuff[(((i * 2) + 2) * img_width) + (j * 1)];
      
      Bbuff[(((i * 2) + 1) * img_width) + (j * 1)] = (Btop + Bbottom) >> 1;
      Rbuff[(((i * 2) + 1) * img_width) + (j * 1)] = (Rtop + Rbottom) >> 1;
    }
  }
#if 0 //Bayer to rgb dump
{
  FILE *Fp;
  Fp = fopen("NoHeader_Inp1_1280x736_rgb.raw","wb");
  if(Fp == NULL)
  {
    printf("\nERROR !!! : Issue with bayer to rgb file");
  }
  
  for(i=0; i<img_height; i++)
  {
    for(j=0; j<img_width; j++)
    {
      unsigned short R = Rbuff[i*img_width+j];
      unsigned short G = Gbuff[i*img_width+j];
      unsigned short B = Bbuff[i*img_width+j];

      unsigned char r = R >> shift; //Shift = 4
      unsigned char g = G >> shift;
      unsigned char b = B >> shift;

      fwrite(&r, 1, 1, Fp);
      fwrite(&g, 1, 1, Fp);
      fwrite(&b, 1, 1, Fp);
    }
  }
  fclose(Fp);
}
#endif
}

