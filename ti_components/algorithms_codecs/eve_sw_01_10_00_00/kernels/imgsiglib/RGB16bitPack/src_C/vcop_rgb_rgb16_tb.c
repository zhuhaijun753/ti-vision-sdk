/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/*-----------------------------------------------------------------*/
/* NAME : vcop_rgb_rgb16 : Test bench data                         */ 
/*                                                                 */
/* DESCRIPTION:                                                    */
/* The function "vcop_rgb_rgb16" accepts un-packed data in         */
/* the form of packed 16-bit "r", "g" and "b" with 5-bits each,    */
/* resulting in RGB555 or RGB565 data.                             */
/*                                                                 */
/* API:                                                            */
/*                                                                 */
/* void vcop_rgb_rgb16                                             */
/* (                                                               */
/*     unsigned int   in_rgb1[],                                   */
/*     unsigned int   npixels,                                     */
/*     unsigned char  out_rgb555[], // out_rgb565                  */
/* );                                                              */
/*                                                                 */
/* The function "vcop_rgb_rgb16" accepts unpacked "r", "g"         */
/* and "b" data, for "npixels" pixels, and writes packed 16-bit    */
/* RGB555 or RGB565 data.                                          */
/*                                                                 */
/*=================================================================*/


#include <stdio.h>
#include <stdlib.h>

#include "../inc/vcop_rgb_rgb16_c.h"

#define NUM_PIXELS   16

#pragma DATA_SECTION (in_rgb1, "Adata");
unsigned char in_rgb1[NUM_PIXELS * 3] =
{
    0x1A, 0x1C, 0x1F, 0x1F, 0x0F, 0x0F, 0x1F, 0x1C, 
    0x1F, 0x1A, 0x0F, 0x0F, 0x1A, 0x1C, 0x1F, 0x1F, 
    0x0F, 0x0F, 0x1F, 0x1C, 0x1F, 0x1A, 0x0F, 0x0F, 
    0x1A, 0x1C, 0x1F, 0x1F, 0x0F, 0x0F, 0x1F, 0x1C, 
    0x1F, 0x1A, 0x0F, 0x0F, 0x1A, 0x1C, 0x1F, 0x1F, 
    0x0F, 0x0F, 0x1F, 0x1C, 0x1F, 0x1A, 0x0F, 0x0F, 
};

#pragma DATA_SECTION (rgb1, "Cdata");
unsigned short out_rgb555[NUM_PIXELS] = {0};

#pragma DATA_SECTION (Ergb555, "EOutdata");
unsigned short Ergb555[NUM_PIXELS] =
{
    0x7F9A, 0x3DFF, 0x7F9F, 0x3DFA, 
    0x7F9A, 0x3DFF, 0x7F9F, 0x3DFA,
    0x7F9A, 0x3DFF, 0x7F9F, 0x3DFA,
    0x7F9A, 0x3DFF, 0x7F9F, 0x3DFA,
};

#pragma DATA_SECTION (in_rgb2, "Adata");
unsigned char in_rgb2[NUM_PIXELS * 3] =
{
    0x1A, 0x3C, 0x0F, 0x1F, 0x2F, 0x07, 0x1F, 0x3C, 
    0x0F, 0x1A, 0x2F, 0x07, 0x1A, 0x3C, 0x0F, 0x1F,
    0x2F, 0x07, 0x1F, 0x3C, 0x0F, 0x1A, 0x2F, 0x07,
    0x1A, 0x3C, 0x0F, 0x1F, 0x2F, 0x07, 0x1F, 0x3C,
    0x0F, 0x1A, 0x2F, 0x07, 0x1A, 0x3C, 0x0F, 0x1F,
    0x2F, 0x07, 0x1F, 0x3C, 0x0F, 0x1A, 0x2F, 0x07,  
};

#pragma DATA_SECTION (out_rgb565, "Cdata");
unsigned short out_rgb565[NUM_PIXELS] = {0};

#pragma DATA_SECTION (Ergb565, "EOutdata");
unsigned short Ergb565[NUM_PIXELS] =
{
    0x7F9A, 0x3DFF, 0x7F9F, 0x3DFA, 
    0x7F9A, 0x3DFF, 0x7F9F, 0x3DFA,
    0x7F9A, 0x3DFF, 0x7F9F, 0x3DFA,
    0x7F9A, 0x3DFF, 0x7F9F, 0x3DFA,
};

void print_output();
int  verify_output();

int main()
{
    int ok;
    
    vcop_rgb_rgb555
    (
        in_rgb1,
        NUM_PIXELS,
        out_rgb555
    );

    vcop_rgb_rgb565
    (
        in_rgb2,
        NUM_PIXELS,
        out_rgb565
    );

   print_output();
   ok = verify_output();
 
   if (ok )   printf(ok ? "\n\nR, G, B planes pack to RGB 16-bit -- C code: PASS\n" : "FAIL\n"); 

   return;
}

void print_output()
{
   int i;

   printf("\n\n RGB555 - DATA  \n");
   for (i = 0; i < NUM_PIXELS; ++i)
   {
      printf("0x%2.2x, ", out_rgb555[i]); 
   }
 
   printf("\n\n RGB565 - DATA  \n");
   for (i = 0; i < NUM_PIXELS; ++i)
   {
      printf("0x%2.2x, ", out_rgb565[i]); 
   }
}

int verify_output()
{
   int ok = 1;
   int i;

   for (i = 0; i < NUM_PIXELS; ++i)
   {
      if (out_rgb555[i] != Ergb555[i])
          ok = 0;
   }
 
   for (i = 0; i < NUM_PIXELS; ++i)
   {
      if (out_rgb565[i] != Ergb565[i])
          ok = 0;
   }

  return (ok);

}

/*=================================================================*/
/* End of file: vcop_rgb_rgb16_tb.c                                */
/*-----------------------------------------------------------------*/
/* Texas Instruments Incorporated 2009-2012.                       */
/*-----------------------------------------------------------------*/


