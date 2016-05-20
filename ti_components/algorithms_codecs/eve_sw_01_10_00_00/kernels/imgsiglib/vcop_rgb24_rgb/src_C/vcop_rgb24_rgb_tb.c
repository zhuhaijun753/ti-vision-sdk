/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*-----------------------------------------------------------------*/
/* NAME : vcop_rgb24_rgb : Test bench data                         */ 
/*                                                                 */
/* DESCRIPTION:                                                    */
/* The function "vcop_rgb24_rgb" accepts packed 24-bit data in     */
/* the form of 8-bit "r", "g" and "b", and writes out seperate     */
/* 8-bit "r", 8-bit "g" and "b". The reason for having this        */
/* function, is to allow the vector core to work in it's           */
/* natural format of looking at similar data together, rather      */
/* than diverse data.                                              */
/*                                                                 */
/* API:                                                            */
/*                                                                 */
/* void vcop_rgb24_rgb                                             */
/* (                                                               */
/*     unsigned int   rgb24[],                                     */
/*     unsigned int   npixels,                                     */
/*     unsigned char  r[],                                         */
/*     unsigned char  g[],                                         */
/*     unsigned char  b[]                                          */
/* )                                                               */
/*                                                                 */
/* The function "vcop_rgb24_rgb" accepts packed 24-bit "r", "g"    */
/* and "b" data, for "npixels" pixels, and writing it into         */
/* seperate output buffers of "r", "g" and "b". Since we are       */
/* packing 24-bit pixels in 32-bit memory, the actual size of      */
/* the input buffer "rgb24" is (3 * npixels) >> 2 and each of      */
/* the output buffers "r", "g" and "b" are of size "npixels".      */
/*                                                                 */
/*=================================================================*/
/*-----------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

#define NUM_PIXELS 24

#pragma DATA_SECTION (rgb24, "Adata");
unsigned int rgb24[((3 * NUM_PIXELS) >> 2)] =
{
    0x02030201, 0x04030403, 0x06050405, 0x06070605,
    0x08070807, 0x0A090809, 0x0A0B0A09, 0x0C0B0C0B,
    0x0E0D0C0D, 0x0E0F0E0D, 0x100F100F, 0x12111011,
    0x12131211, 0x14131413, 0x16151415, 0x16171615,
    0x18171817, 0x1A191819
};

#pragma DATA_SECTION (r, "Bdata");
#pragma DATA_SECTION (g, "Bdata");
#pragma DATA_SECTION (b, "Bdata");

unsigned char r[NUM_PIXELS] = {0};
unsigned char g[NUM_PIXELS] = {0};
unsigned char b[NUM_PIXELS] = {0};

unsigned char Er[NUM_PIXELS] =
{
    0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
    0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10,
    0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18
};

unsigned char Eg[NUM_PIXELS] =
{
    0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 
    0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 
    0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19
};

unsigned char Eb[NUM_PIXELS] =
{
    0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 
    0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 
    0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A
};



int main()
{
    int i;
    
    vcop_rgb24_rgb
    (
        rgb24,
        NUM_PIXELS,
        r,
        g,
        b
    );

    for ( i = 0; i < NUM_PIXELS; i++)
    printf ("r:0x%.2x, g:0x%.2x, b:0x%.2x \n",
             (r[i] & 0xFF), (g[i] & 0xFF), (b[i] & 0xFF)
           );

   if 
   (
       (memcmp (r, Er, sizeof(r)))
    || (memcmp (g, Eg, sizeof(g)))
    || (memcmp (b, Eb, sizeof(b)))
   )
   printf ("Fail \n");
   else
   printf ("Pass \n");
}

/*=================================================================*/
/* End of file: vcop_rgb24_rgb_tb.c                                */
/*-----------------------------------------------------------------*/
/*-----------------------------------------------------------------*/


