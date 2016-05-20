/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/*-----------------------------------------------------------------*/
/* NAME : vcop_rgb_to_yuv   : Test bench                           */
/*                                                                 */
/*                                                                 */
/* DESCRIPTION:                                                    */
/*                                                                 */
/* The function rgb_to_yuv, converts rgb to interleaved yuv.       */
/* by applying coefficients weighting red, blue and green,         */
/* to luma. Similarly we aplly a weighted product of red,          */
/* blue and green to U and V.                                      */
/*                                                                 */
/* A possible set of coefficients, to use is suggnsted at:         */
/* http://msdn.microsoft.com/en-us/library/ms893078.aspx           */
/*                                                                 */
/* Y = ( (  66 * R + 129 * G +  25 * B + 128) >> 8) +  16          */
/* U = ( ( -38 * R -  74 * G + 112 * B + 128) >> 8) + 128          */
/* V = ( ( 112 * R -  94 * G -  18 * B + 128) >> 8) + 128          */
/*                                                                 */
/* The values from this equation, will have to be clamped          */
/* between 0..255.                                                 */
/*                                                                 */
/* This benchmark is intended to highlight the value of predicated */
/* stores to memory.                                               */
/*                                                                 */
/* API:                                                            */
/* void rgb_to_yuv                                                 */
/* (                                                               */
/*     unsigned char    iPtrR[],                                   */
/*     unsigned char    iPtrG[],                                   */
/*     unsigned char    iPtrB[],                                   */
/*     unsigned short   width,                                     */
/*     short            coefs[],                                   */
/*     unsigned char    iPtrOut[]                                  */
/* )                                                               */
/*                                                                 */
/* The function "rgb_to_yuv" accepts red, green and blue pixels    */
/* in arrays "iPtrR", "iPtrG" and "iPtrB" into an interleaved      */
/* array of YUYV pixels stored in "iPtrOut" by applying a 3x3      */
/* array of coefficients to convert from RGB to YUV space.         */
/*                                                                 */
/*=================================================================*/


#include <stdio.h>
#include <stdlib.h>
#include "../inc/vcop_rgb_to_yuv_c.h"

#pragma DATA_SECTION (R, "Adata")
unsigned char R[32] =
{
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
    0xFF, 0xFE, 0xFD, 0xFC, 0xFB, 0xFA, 0xF8, 0xF7,
    0xCF, 0xCC, 0xCD, 0xCA, 0xCE, 0xC4, 0xC3, 0xC2
};

#pragma DATA_SECTION (G, "Adata")
unsigned char G[32] =
{
    0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77,
    0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F,
    0x8F, 0x8E, 0x8D, 0x8C, 0x8B, 0x8A, 0x88, 0x87,
    0x9F, 0x9C, 0x9D, 0x9A, 0x9E, 0x94, 0x93, 0x92
};

#pragma DATA_SECTION (B, "Adata")
unsigned char B[32] =
{
    0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7,
    0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF,
    0xCF, 0xCE, 0xCD, 0xCC, 0xCB, 0xCA, 0xC8, 0xC7,
    0xDF, 0xDC, 0xDD, 0xDA, 0xDE, 0xD4, 0xD3, 0xD2
};

#pragma DATA_SECTION (YUV, "Bdata")
unsigned char YUV[64] = {0};

#pragma DATA_SECTION (EOut, "EOutdata");
unsigned char EOut[64] =
{
   0xAD,  0x4A,  0x4B,  0x4A,  0xAD, 0x4B,  0x4B,  0x4C,
   0xAD,  0x4D,  0x4B,  0x4E,  0xAD, 0x4F,  0x4B,  0x50,
   0xAA,  0x47,  0x52,  0x48,  0xAA, 0x49,  0x52,  0x49,
   0xAA,  0x4A,  0x52,  0x4B,  0xAA, 0x4C,  0x52,  0x4D,
   0x8B,  0x9E,  0xAD,  0x9D,  0x8B, 0x9C,  0xAD,  0x9B,
   0x8B,  0x9B,  0xAD,  0x9A,  0x8B, 0x98,  0xAD,  0x97, 
   0x95,  0x9B,  0x91,  0x99,  0x95, 0x9A,  0x91,  0x97,
   0x95,  0x9A,  0x91,  0x92,  0x95, 0x91,  0x91,  0x90
};

unsigned short width = 32;

short coefs[9] =
{
     66, 129,  25,
    -38, -74, 112,
    112, -94, -18
};

int main()
{
    rgb_to_yuv 
    (
        R,
        G,
        B,
        width,
        coefs,
        YUV
    );

    if (memcmp (YUV, EOut, sizeof(YUV))) printf ("Fail \n");
    else printf ("Pass \n");

}

/*-----------------------------------------------------------------*/
/*  End of file: vcop_rgb_to_yuv_tb.c                              */
/*=================================================================*/
/* Texas Instruments Incorporated 2009-2012.                       */
/*-----------------------------------------------------------------*/

