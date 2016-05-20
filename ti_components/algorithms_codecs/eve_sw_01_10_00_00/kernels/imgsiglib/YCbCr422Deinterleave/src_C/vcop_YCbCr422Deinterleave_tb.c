/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/*-----------------------------------------------------------------*/
/* NAME : vcop_YCbCrDeinterleave : Test bench data                 */ 
/*                                                                 */
/*                                                                 */
/* DESCRIPTION:                                                    */
/* The function "vcop_YCbCrDeinterleave" accepts 8 or 16-bit data */
/* in the form of 8 or 16-bit "Y", "Cb" and "Cr", and writes out   */
/* 8-bit "Y", 8-bit "Cb" and "Cr". The input data can be of 444 or */
/* 422 format, the output can be of 444, 422 or 420 formats.       */
/* function, is to allow the vector core to work in it's           */
/* natural format of looking at similar data together, rather      */
/* than diverse data.                                              */
/*                                                                 */
/* API:                                                            */
/*                                                                 */
/* void vcop_YCbCrDeinterleave                                     */
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

#include "../inc/vcop_YCbCr422Deinterleave_c.h"

#define NUM_SAMPLES1  12
#define NUM_PIXELS1   (NUM_SAMPLES1 * 3)

#define NUM_SAMPLES2  16
#define NUM_SAMPLES2_DIV2  8
#define NUM_PIXELS2   (NUM_SAMPLES2 * 2)

#pragma DATA_SECTION (YCbCr444, "Adata");
unsigned char YCbCr444[NUM_PIXELS1] =
{
    0x7F, 0x9A, 0x3D, 0xFF, 0x7F, 0x9F, 0x3D, 0xFA, 0x88,
    0x7F, 0x9A, 0x3D, 0xFF, 0x7F, 0x9F, 0x3D, 0xFA, 0x88,
    0x7F, 0x9A, 0x3D, 0xFF, 0x7F, 0x9F, 0x3D, 0xFA, 0x88,
    0x7F, 0x9A, 0x3D, 0xFF, 0x7F, 0x9F, 0x3D, 0xFA, 0x88
};

#pragma DATA_SECTION (YCbCr422, "Adata");
unsigned char YCbCr422[NUM_PIXELS2] =
{
    0x7F, 0x9A, 0x3D, 0xFF, 0x7F, 0x9F, 0x3D, 0xFA, 
    0x7F, 0x9A, 0x3D, 0xFF, 0x7F, 0x9F, 0x3D, 0xFA,
    0x7F, 0x9A, 0x3D, 0xFF, 0x7F, 0x9F, 0x3D, 0xFA,
    0x7F, 0x9A, 0x3D, 0xFF, 0x7F, 0x9F, 0x3D, 0xFA,
};

#pragma DATA_SECTION (Y1, "Bdata");
unsigned char Y1[NUM_SAMPLES1] = {0};

#pragma DATA_SECTION (Cb1, "Bdata");
unsigned char Cb1[NUM_SAMPLES1] = {0};

#pragma DATA_SECTION (Cr1, "Bdata");
unsigned char Cr1[NUM_SAMPLES1] = {0};

#pragma DATA_SECTION (EY1, "EOutdata");
unsigned char EY1[NUM_SAMPLES1] =
{
    0x7F, 0xFF, 0x3D,  
    0x7F, 0xFF, 0x3D,  
    0x7F, 0xFF, 0x3D, 
    0x7F, 0xFF, 0x3D
};

#pragma DATA_SECTION (ECb1, "EOutdata");
unsigned char ECb1[NUM_SAMPLES1] =
{
    0x9A, 0x7F, 0xFA,  
    0x9A, 0x7F, 0xFA,  
    0x9A, 0x7F, 0xFA, 
    0x9A, 0x7F, 0xFA 
};

#pragma DATA_SECTION (ECr1, "EOutdata");
unsigned char ECr1[NUM_SAMPLES1] =
{
    0x3D, 0x9F, 0x88,  
    0x3D, 0x9F, 0x88,  
    0x3D, 0x9F, 0x88, 
    0x3D, 0x9F, 0x88 
};

#pragma DATA_SECTION (Y2, "Bdata");
unsigned char Y2[NUM_SAMPLES2] = {0};

#pragma DATA_SECTION (Cb2, "Bdata");
unsigned char Cb2[NUM_SAMPLES2_DIV2] = {0};

#pragma DATA_SECTION (Cr2, "Bdata");
unsigned char Cr2[NUM_SAMPLES2_DIV2] = {0};

#pragma DATA_SECTION (EY2, "EOutdata");
unsigned char EY2[NUM_SAMPLES2] =
{
    0x7F, 0x3D, 0x7F, 0x3D, 
    0x7F, 0x3D, 0x7F, 0x3D,
    0x7F, 0x3D, 0x7F, 0x3D,
    0x7F, 0x3D, 0x7F, 0x3D
};

#pragma DATA_SECTION (ECb2, "EOutdata");
unsigned char ECb2[NUM_SAMPLES2_DIV2] =
{
    0x9A, 0x9F,  
    0x9A, 0x9F, 
    0x9A, 0x9F, 
    0x9A, 0x9F 
};

#pragma DATA_SECTION (ECr2, "EOutdata");
unsigned char ECr2[NUM_SAMPLES2_DIV2] =
{
    0xFF, 0xFA, 
    0xFF, 0xFA,
    0xFF, 0xFA,
    0xFF, 0xFA
};

void print_output();
int  verify_output();

int main()
{
    int ok;
    
    vcop_YCbCr444_Deinterleave444_char
    (
        YCbCr444,
        NUM_SAMPLES1,
        Y1,
        Cb1,
        Cr1
    );

    vcop_YCbCr422_Deinterleave422_char
    (
        YCbCr422,
        NUM_SAMPLES2_DIV2,
        Y2,
        Cb2,
        Cr2
    );

   print_output();
   ok = verify_output();
 
   if (ok )   printf("\n\nYCbCr422, 8 and 16-bit Deinterleave to Y, Cb, Cr planes -- C code: PASS\n\n\n"); 
   else printf("\n\nFAIL\n\n");

   return;
}

void print_output()
{
   int i;

   printf("\n\n Y - DATA  \n");
   for (i = 0; i < NUM_SAMPLES1; ++i)
   {
      printf("0x%2.2x, ", Y1[i]); 
   }
 
   printf("\n\n Cb - DATA  \n");
   for (i = 0; i < NUM_SAMPLES1; ++i)
   {
      printf("0x%2.2x, ", Cb1[i]); 
   }

   printf("\n\n Cr - DATA  \n");
   for (i = 0; i < NUM_SAMPLES1; ++i)
   {
      printf("0x%2.2x, ", Cr1[i]); 
   }

   printf("\n\n Y - DATA  \n");
   for (i = 0; i < NUM_SAMPLES2; ++i)
   {
      printf("0x%2.2x, ", Y2[i]); 
   }
 
   printf("\n\n Cb - DATA  \n");
   for (i = 0; i < NUM_SAMPLES2_DIV2; ++i)
   {
      printf("0x%2.2x, ", Cb2[i]); 
   }

   printf("\n\n Cr - DATA  \n");
   for (i = 0; i < NUM_SAMPLES2_DIV2; ++i)
   {
      printf("0x%2.2x, ", Cr2[i]); 
   }

}

int verify_output()
{
   int ok = 1;
   int i;

   for (i = 0; i < NUM_SAMPLES1; ++i)
   {
      if (Y1[i] != EY1[i])
          ok = 0;
   }
 
   for (i = 0; i < NUM_SAMPLES1; ++i)
   {
      if (Cb1[i] != ECb1[i])
          ok = 0;
   }

   for (i = 0; i < NUM_SAMPLES1; ++i)
   {
      if (Cr1[i] != ECr1[i])
          ok = 0;
   }

   for (i = 0; i < NUM_SAMPLES2; ++i)
   {
      if (Y2[i] != EY2[i])
          ok = 0;
   }
 
   for (i = 0; i < NUM_SAMPLES2_DIV2; ++i)
   {
      if (Cb2[i] != ECb2[i])
          ok = 0;
   }

   for (i = 0; i < NUM_SAMPLES2_DIV2; ++i)
   {
      if (Cr2[i] != ECr2[i])
          ok = 0;
   }

  return (ok);

}

/*=================================================================*/
/* End of file: vcop_YCbCrDeinterleave_tb.c                        */
/*-----------------------------------------------------------------*/
/* Texas Instruments Incorporated 2009-2012.                       */
/*-----------------------------------------------------------------*/


