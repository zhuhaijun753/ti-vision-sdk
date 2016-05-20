/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/*-----------------------------------------------------------------*/
/* NAME : vcop_rgb_rgb16                                           */
/*                                                                 */
/*                                                                 */
/* DESCRIPTION:                                                    */
/* The function "vcop_rgb_rgb16" accepts unpacked RGB data and     */
/* repacks the data in the form of RGB555 or RGB565 data.          */
/*                                                                 */
/* API:                                                            */
/*                                                                 */
/* void vcop_rgb_rgb16                                             */
/* (                                                               */
/*     unsigned int   in_rgb1[],                                   */
/*     unsigned int   npixels,                                     */
/*     unsigned char  out_rgb555[], // OR out_rgb565               */
/* );                                                              */
/*                                                                 */
/* The function "vcop_rgb_rgb16" accepts unpacked "r", "g"         */
/* and "b" data, for "npixels" pixels, and writes packed 16-bit    */
/* RGB555 or RGB565 data.                                          */
/*                                                                 */
/*=================================================================*/


#include "../inc/vcop_rgb_rgb16_c.h"

void vcop_rgb_rgb555
(
    unsigned char  *in_rgb,
    unsigned int   npixels,
    unsigned short *rgb555
)
{

    unsigned char  *prgb = &in_rgb[0];
    unsigned int   i;
    unsigned char r, g, b;

    /*-----------------------------------------------------------*/
    /* For each of the pixels, read unpacked "r", "g", "b"       */
    /* and write as packed rgb555 16-bit data.                   */
    /*-----------------------------------------------------------*/

    for (i = 0; i < npixels; i++)
    {
        r = prgb[(3 * i) + 0];
        g = prgb[(3 * i) + 1];
        b = prgb[(3 * i) + 2];

        rgb555[i] = ( b << 10 ) | (( g << 5 ) | ( r ) );
    }
}


void vcop_rgb_rgb565
(
    unsigned char  *in_rgb,
    unsigned int   npixels,
    unsigned short *rgb565
)
{
    unsigned char  *prgb = &in_rgb[0];
    unsigned int   i;
    unsigned char r, g, b;

    /*-----------------------------------------------------------*/
    /* For each of the pixels, read unpacked "r", "g", "b"       */
    /* and write as packed rgb565 16-bit data.                   */
    /*-----------------------------------------------------------*/

    for (i = 0; i < npixels; i++)
    {
        r = prgb[(3 * i) + 0];
        g = prgb[(3 * i) + 1];
        b = prgb[(3 * i) + 2];

        rgb565[i] = ( b << 11 ) | (( g << 5 ) | ( r ) );
    }
}

/*=================================================================*/
/* End of file: vcop_rgb_rgb16_c.c                                 */
/*-----------------------------------------------------------------*/
/* Texas Instruments Incorporated 2009-2012.                       */
/*-----------------------------------------------------------------*/
 
