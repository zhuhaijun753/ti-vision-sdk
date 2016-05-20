/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*-----------------------------------------------------------------*/
/* NAME : vcop_YCbCrDownsample : Test bench data                   */ 
/*                                                                 */
/*                                                                 */
/* DESCRIPTION:                                                    */
/* The function "vcop_YCbCrDownsample" accepts  8 or 16-bit data   */
/* in the form of 8 or 16-bit "Y", "Cb" and "Cr", and writes out   */
/* 8-bit "Y", 8-bit "Cb" and "Cr". The input data can be of 444 or */
/* 422 format, the output can be of 444, 422 or 420 formats.       */
/* function, is to allow the vector core to work in it's           */
/* natural format of looking at similar data together, rather      */
/* than diverse data.                                              */
/*                                                                 */
/* API:                                                            */
/*                                                                 */
/* void vcop_YCbCrDownsample                                       */
/* (                                                               */
/*     unsigned int   YCbCr[],                                     */
/*     unsigned int   npixels,                                     */
/*     unsigned char  Y[],                                         */
/*     unsigned char  Cb[],                                        */
/*     unsigned char  Cr[]                                         */
/* )                                                               */
/*                                                                 */
/*                                                                 */
/*=================================================================*/


#include <stdio.h>
#include <stdlib.h>

#include "../inc/vcop_YCbCr444Downsample_c.h"

typedef unsigned short Uint16;
typedef unsigned char  Uint8;

#define NUM_SAMPLES1  48
#define NUM_PIXELS1   (NUM_SAMPLES1 * 3)

#pragma DATA_SECTION (YCbCr444_char, "Adata");
unsigned char YCbCr444_char[NUM_PIXELS1] =
{
    //Y   Cb    Cr    Y     Cb    Cr    Y     Cb    Cr    Y     Cb    Cr    Y     Cb    Cr    Y     
    0x10, 0x20, 0x30, 0x10, 0x20, 0x30, 0x10, 0x20, 0x30, 0x10, 0x20, 0x30, 0x10, 0x20, 0x30, 0x10,
    0x20, 0x30, 0x10, 0x20, 0x30, 0x10, 0x20, 0x30, 0x10, 0x20, 0x30, 0x10, 0x20, 0x30, 0x10, 0x20,
    0x30, 0x10, 0x20, 0x30, 0x10, 0x20, 0x30, 0x10, 0x20, 0x30, 0x10, 0x20, 0x30, 0x10, 0x20, 0x30,
    0x10, 0x20, 0x30, 0x10, 0x20, 0x30, 0x10, 0x20, 0x30, 0x10, 0x20, 0x30, 0x10, 0x20, 0x30, 0x10,
                                                                                                
    0x20, 0x30, 0x10, 0x20, 0x30, 0x10, 0x20, 0x30, 0x10, 0x20, 0x30, 0x10, 0x20, 0x30, 0x10, 0x20,
    0x30, 0x10, 0x20, 0x30, 0x10, 0x20, 0x30, 0x10, 0x20, 0x30, 0x10, 0x20, 0x30, 0x10, 0x20, 0x30,
    0x10, 0x20, 0x30, 0x10, 0x20, 0x30, 0x10, 0x20, 0x30, 0x10, 0x20, 0x30, 0x10, 0x20, 0x30, 0x10,
                                                                                                
    0x20, 0x30, 0x10, 0x20, 0x30, 0x10, 0x20, 0x30, 0x10, 0x20, 0x30, 0x10, 0x20, 0x30, 0x10, 0x20,
    0x30, 0x10, 0x20, 0x30, 0x10, 0x20, 0x30, 0x10, 0x20, 0x30, 0x10, 0x20, 0x30, 0x10, 0x20, 0x30,
};

#pragma DATA_SECTION (YCbCr444_short, "Adata");
unsigned short YCbCr444_short[NUM_PIXELS1] =
{

    //Y    Cb     Cr     Y      Cb     Cr     Y      Cb     Cr
    0x100, 0x200, 0x300, 0x100, 0x200, 0x300, 0x100, 0x200, 0x300, 
    0x100, 0x200, 0x300, 0x100, 0x200, 0x300, 0x100, 0x200, 0x300,
    0x100, 0x200, 0x300, 0x100, 0x200, 0x300, 0x100, 0x200, 0x300,
    0x100, 0x200, 0x300, 0x100, 0x200, 0x300, 0x100, 0x200, 0x300,
    0x100, 0x200, 0x300, 0x100, 0x200, 0x300, 0x100, 0x200, 0x300,
    0x100, 0x200, 0x300, 0x100, 0x200, 0x300, 0x100, 0x200, 0x300,
    0x100, 0x200, 0x300, 0x100, 0x200, 0x300, 0x100, 0x200, 0x300,
    0x100, 0x200, 0x300, 0x100, 0x200, 0x300, 0x100, 0x200, 0x300,
    0x100, 0x200, 0x300, 0x100, 0x200, 0x300, 0x100, 0x200, 0x300,
    0x100, 0x200, 0x300, 0x100, 0x200, 0x300, 0x100, 0x200, 0x300,
    0x100, 0x200, 0x300, 0x100, 0x200, 0x300, 0x100, 0x200, 0x300,
    0x100, 0x200, 0x300, 0x100, 0x200, 0x300, 0x100, 0x200, 0x300,
    0x100, 0x200, 0x300, 0x100, 0x200, 0x300, 0x100, 0x200, 0x300,
    0x100, 0x200, 0x300, 0x100, 0x200, 0x300, 0x100, 0x200, 0x300,
    0x100, 0x200, 0x300, 0x100, 0x200, 0x300, 0x100, 0x200, 0x300,
    0x100, 0x200, 0x300, 0x100, 0x200, 0x300, 0x100, 0x200, 0x300,
};

#pragma DATA_SECTION (YCbCr_char_shift, "Bdata");
char YCbCr_char_shift[24] =
{  
   -0, -24, -16,  -8,  -0, -24, -16,  -8,
   -8,  -0, -24, -16,  -8,  -0, -24, -16,
  -16,  -8,  -0, -24, -16,  -8,  -0, -24,
};

#pragma DATA_SECTION (YCbCr_short_shift, "Bdata");
char YCbCr_short_shift[24] =
{  
   -0, -16,  -0, -16,  -0, -16, -0, -16,
  -16,  -0, -16,  -0, -16, -0, -16,  -0,
   -0, -16,  -0, -16,  -0, -16, -0, -16,
};

#pragma DATA_SECTION (Y1, "Cdata");
unsigned char Y1[NUM_SAMPLES1] = {0};

#pragma DATA_SECTION (Cb1, "Cdata");
unsigned char Cb1[NUM_SAMPLES1/2] = {0};

#pragma DATA_SECTION (Cr1, "Cdata");
unsigned char Cr1[NUM_SAMPLES1/2] = {0};

#pragma DATA_SECTION (EY1, "EOutdata");
unsigned char EY1[NUM_SAMPLES1] =
{
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
};

#pragma DATA_SECTION (ECb1, "EOutdata");
unsigned char ECb1[NUM_SAMPLES1/2] =
{
    0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20,
};

#pragma DATA_SECTION (ECr1, "EOutdata");
unsigned char ECr1[NUM_SAMPLES1/2] =
{
    0x30, 0x30, 0x30, 0x30,
    0x30, 0x30, 0x30, 0x30,
    0x30, 0x30, 0x30, 0x30,
    0x30, 0x30, 0x30, 0x30,
    0x30, 0x30, 0x30, 0x30,
};

#pragma DATA_SECTION (Y2, "Cdata");
unsigned short Y2[NUM_SAMPLES1] = {0};

#pragma DATA_SECTION (Cb2, "Cdata");
unsigned short Cb2[NUM_SAMPLES1/2] = {0};

#pragma DATA_SECTION (Cr2, "Cdata");
unsigned short Cr2[NUM_SAMPLES1/2] = {0};

#pragma DATA_SECTION (EY2, "EOutdata");
unsigned short EY2[NUM_SAMPLES1] =
{
    0x100, 0x100, 0x100, 0x100, 0x100, 0x100, 0x100, 0x100,
    0x100, 0x100, 0x100, 0x100, 0x100, 0x100, 0x100, 0x100,
    0x100, 0x100, 0x100, 0x100, 0x100, 0x100, 0x100, 0x100,
    0x100, 0x100, 0x100, 0x100, 0x100, 0x100, 0x100, 0x100,
    0x100,
};

#pragma DATA_SECTION (ECb2, "EOutdata");
unsigned short ECb2[NUM_SAMPLES1/2] =
{
    0x200, 0x200, 0x200, 0x200,
    0x200, 0x200, 0x200, 0x200,
    0x200, 0x200, 0x200, 0x200,
    0x200, 0x200, 0x200, 0x200,
    0x200, 0x200,
};

#pragma DATA_SECTION (ECr2, "EOutdata");
unsigned short ECr2[NUM_SAMPLES1/2] =
{
    0x300, 0x300, 0x300, 0x300,
    0x300, 0x300, 0x300, 0x300,
    0x300, 0x300, 0x300, 0x300,
    0x300, 0x300, 0x300, 0x300,
    0x300, 0x300,
};
void print_output();
int  verify_output();

int main()
{
    int ok;
   
    vcop_YCbCr444_Downsample422_char
    (
        &YCbCr444_char[0],
        NUM_PIXELS1/4,
        Y1,
        Cb1,
        Cr1
    );

    vcop_YCbCr444_Downsample422_short
    (
        &YCbCr444_short[0],
        NUM_PIXELS1/2,
        Y2,
        Cb2,
        Cr2
    );

   print_output();
   ok = verify_output();
 
   if (ok )   printf("\n\nYCbCr444, 8 and 16-bit Downsample to Y, Cb, Cr 422 planes -- C code: PASS\n\n\n"); 
   else printf("\n\nFAIL\n\n");

   return ok;
}

void print_output()
{
   int i;

   printf("\n\n Y - DATA  \n");
   for (i = 0; i < NUM_PIXELS1/4 - 4; ++i)
   {
      printf("0x%2.2x, ", Y1[i]); 
      if (!((i+1) % 8 ))
          printf("\n");
   }
 
   printf("\n\n Cb - DATA  \n");
   for (i = 0; i < NUM_SAMPLES1/2 - 4; ++i)
   {
      printf("0x%2.2x, ", Cb1[i]); 
      if (!((i+1) % 4 ))
          printf("\n");
   }

   printf("\n\n Cr - DATA  \n");
   for (i = 0; i < NUM_SAMPLES1/2 - 4; ++i)
   {
      printf("0x%2.2x, ", Cr1[i]); 
      if (!((i+1) % 4 ))
          printf("\n");
   }

   printf("\n\n Y - DATA  \n");
   for (i = 0; i < NUM_PIXELS1/4 - 3; ++i)
   {
      printf("0x%2.2x, ", Y2[i]); 
      if (!((i+1) % 8 ))
          printf("\n");
   }
 
   printf("\n\n Cb - DATA  \n");
   for (i = 0; i < NUM_SAMPLES1/2 - 6; ++i)
   {
      printf("0x%2.2x, ", Cb2[i]); 
      if (!((i+1) % 4 ))
          printf("\n");
   }

   printf("\n\n Cr - DATA  \n");
   for (i = 0; i < NUM_SAMPLES1/2 - 6; ++i)
   {
      printf("0x%2.2x, ", Cr2[i]);
      if (!((i+1) % 4 ))
          printf("\n");
   }
}

int verify_output()
{
   int ok = 1;
   int i;

   for (i = 0; i < NUM_PIXELS1/4 - 4; ++i)
   {
      if (Y1[i] != EY1[i])
          ok = 0;
   }
 
   for (i = 0; i < NUM_SAMPLES1/2 - 4; ++i)
   {
      if (Cb1[i] != ECb1[i])
          ok = 0;
   }

   for (i = 0; i < NUM_SAMPLES1/2 - 4; ++i)
   {
      if (Cr1[i] != ECr1[i])
          ok = 0;
   }

   for (i = 0; i < NUM_PIXELS1/4 - 3; ++i)
   {
      if (Y2[i] != EY2[i])
          ok = 0;
   }
 
   for (i = 0; i < NUM_SAMPLES1/2 - 6; ++i)
   {
      if (Cb2[i] != ECb2[i])
          ok = 0;
   }

   for (i = 0; i < NUM_SAMPLES1/2 - 6; ++i)
   {
      if (Cr2[i] != ECr2[i])
          ok = 0;
   }


  return (ok);

}

/*=================================================================*/
/* End of file: vcop_YCbCrDownsample_tb.c                          */
/*-----------------------------------------------------------------*/
/* Texas Instruments Incorporated 2009-2012.                       */
/*-----------------------------------------------------------------*/


