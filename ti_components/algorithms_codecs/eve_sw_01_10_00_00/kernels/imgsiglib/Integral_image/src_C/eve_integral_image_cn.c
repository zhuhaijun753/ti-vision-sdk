/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     NAME                                                                 */
/*     eve_integral_image_cn                                                */
/*                                                                          */
/*                                                                          */
/*     USAGE                                                                */
/*     This is the natural C code for integral image:                       */
/*                                                                          */
/*     void eve_integral_image_cn                                           */
/*     (                                                                    */
/*     unsigned short width,                                                */
/*     unsigned short height,                                               */
/*     unsigned short img_width,                                            */
/*     unsigned int   *acc_h,                                               */
/*     unsigned int   *acc_v,                                               */
/*     unsigned char  *inimgptr,                                            */
/*     unsigned short *Bimgptr0,                                            */
/*     unsigned short *Bimgptr1,                                            */
/*     unsigned int   *Cimgptr0,                                            */
/*     unsigned int   *Cimgptr1,                                            */
/*     unsigned int   *outimgptr                                            */
/*     );                                                                   */
/*                                                                          */
/*                                                                          */
/*     width             : width of block being processed                   */
/*     height            : height of block being processed                  */
/*     img_width         : width of image being processed in bytes          */
/*     *acc_h            : horizontal accumulator array.                    */
/*     *acc_v            : vertical accumulator array.                      */
/*     *inimgptr         : Pointer to an input array of char data.          */
/*     *Bimgptr0         : Pointer to an intermediate output array of type  */
/*                         16-bit half word, even data points.              */
/*     *Bimgptr1         : Pointer to an intermediate output array of type  */
/*                         16-bit half word, odd data points.               */
/*     *Cimgptr0         : Pointer to an intermediate output array of type  */
/*                         32-bit half word, odd data points.               */
/*     *Cimgptr1         : Pointer to an intermediate output array of type  */
/*                         32-bit half word, odd data points.               */
/*     *outimgptr        : Pointer to an output array of type 32-bit word.  */
/*                                                                          */
/*                                                                          */
/*     Returns :  None or void.                                             */
/*                                                                          */
/*                                                                          */
/*     DESCRIPTION                                                          */
/*             This routine accepts pointer to an input region, and carries */
/*     out integral image computation on a block of data. The output        */
/*     of this processing is integral image result of type word.            */
/*     This function is written as three loops to mimic the structure of    */
/*     corresponding assembly function.                                     */
/*                                                                          */
/*                                                                          */
/*==========================================================================*/
/*      Copyright (C) 2009-2012 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*-------------------------------------------------------------------------*/
/* Function: integral_image                                                */
/* This function calls the integral image EVE specific routine after       */
/* setting the required parameter registers.                               */
/*-------------------------------------------------------------------------*/
// #define __PRINT__    1

void eve_integral_image_cn
( 
 unsigned short width,
 unsigned short height,
 unsigned short img_width,
 unsigned int  *acc_h,
 unsigned int  *acc_v,
 unsigned char *inimgptr,
 unsigned int  *Bimgptr0,
 unsigned int  *Bimgptr1,
 unsigned int  *Cimgptr0, 
 unsigned int  *Cimgptr1, 
 unsigned int  *outimgptr
)
{

  int r, c, cc;
  int inter_w, inter_h;
  unsigned int *acc_h_2;
  unsigned int sum[200] = {0};

  acc_h_2 = acc_h + width/2;

#if __PRINT__

  printf("\nA:\n");
  for ( r = 0; r < height; r++)
  {
      for ( c = 0; c < width; c++)
          printf("%2x, ",  inimgptr[(r * img_width) + c]);
      printf("\n");
  }
#endif

  /*---------------------------------------------------------------------*/
  /* First add row-wise and write as transpose.                          */
  /*---------------------------------------------------------------------*/
 
  inter_w = height;
  inter_h = width/2;

  for ( r = 0; r < height; r++)
  {
      cc = 0;
      for ( c = 0; c < width; c += 2)
      {
          acc_h[cc]     = acc_h[cc] + inimgptr[(r * img_width) + c];
          acc_h_2[cc]   = acc_h_2[cc] + inimgptr[(r * img_width) + c + 1];

          Bimgptr0[(cc * inter_w) + r] = acc_h[cc];
          Bimgptr1[(cc * inter_w) + r] = acc_h_2[cc];
          cc++;
      }
   }

#if __PRINT__

  printf("\nB0:\n");
  for ( r = 0; r < inter_h; r++)
  {
      for ( c = 0; c < inter_w; c++)
          printf("%2x, ",  Bimgptr0[(r * inter_w) + c]);
      printf("\n");
  }

  printf("\nB1:\n");
  for ( r = 0; r < inter_h; r++)
  {
      for ( c = 0; c < inter_w; c++)
          printf("%2x, ",  Bimgptr1[(r * inter_w) + c]);
      printf("\n");
  }

  printf("\nACC_H:\n");
  for ( c = 0; c < width/2; c++)
      printf("%3x,", acc_h[c]);

  for ( c = 0; c < width/2; c++)
      printf("%3x,", acc_h_2[c]);

  printf("\n");

#endif

  /*---------------------------------------------------------------------*/
  /* Next add row-wise again and write as transpose.                     */
  /*---------------------------------------------------------------------*/
  
  for ( c = 0; c < inter_w; c++)
  {
      sum[c] = acc_v[c];

      for ( r = 0; r < inter_h; r++)
      { 
          Cimgptr0[(c * inter_h) + r] = sum[c] + Bimgptr0[(r * inter_w) + c];
          sum[c] = sum[c] + Bimgptr0[(r * inter_w) + c] + Bimgptr1[(r * inter_w) + c];
          Cimgptr1[(c * inter_h) + r] = sum[c];
      }
      acc_v[c] = sum[c];
  }

#if __PRINT__

  printf("\nC0:\n");
  for ( c = 0; c < inter_w; c++)
  {
      for ( r = 0; r < inter_h; r++)
          printf("%3x, ",  Cimgptr0[(c * inter_h) + r]);
      printf("\n");
  }

  printf("\nC1:\n");
  for ( c = 0; c < inter_w; c++)
  {
      for ( r = 0; r < inter_h; r++)
          printf("%3x, ",  Cimgptr1[(c * inter_h) + r]);
      printf("\n");
  }

  printf("\nACC_V:\n");
  for ( r = 0; r < height; r++)
      printf("%3x,\n", acc_v[r]);

#endif

  /*---------------------------------------------------------------------*/
  /* Interleave the output data to get final output.                     */
  /*---------------------------------------------------------------------*/

  for ( r = 0; r < height; r++)
  {
      for ( c = 0; c < width/2; c++)
      {
          outimgptr[(r * width) + (c*2)] = Cimgptr0[(r * width/2) + c];
          outimgptr[(r * width) + ((c*2) + 1)] = Cimgptr1[(r * width/2) + c];
      }
  }
     
#if __PRINT__
  printf("\nout:\n");
  for ( r = 0; r < height; r++)
  {
      for ( c = 0; c < width; c++)
          printf("%3x, ",  outimgptr[(r * width) + c]);
      printf("\n");
  }

#endif

   return;

}

