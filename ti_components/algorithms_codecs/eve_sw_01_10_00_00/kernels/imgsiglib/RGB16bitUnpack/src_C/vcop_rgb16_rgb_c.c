/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/*-----------------------------------------------------------------*/
/* NAME : vcop_rgb16_rgb                                           */
/*                                                                 */
/*                                                                 */
/* DESCRIPTION:                                                    */
/* The function "vcop_rgb16_rgb" accepts packed 16-bit data in     */
/* the form of 5-5-5-bits or 5-6-5 bits "r", "g" and "b", and      */
/* writes out seperate 8-bit "r", 8-bit "g" and "b". The reason    */
/* for having this function, is to allow the vector core to work   */
/* in it's natural format of looking at similar data together,     */
/* rather than diverse data.                                       */
/*                                                                 */
/* API:                                                            */
/*                                                                 */
/* void vcop_rgb16_rgb                                             */
/* (                                                               */
/*     unsigned int   rgb16[],                                     */
/*     unsigned int   npixels,                                     */
/*     unsigned char  r[],                                         */
/*     unsigned char  g[],                                         */
/*     unsigned char  b[]                                          */
/* )                                                               */
/*                                                                 */
/* The function "vcop_rgb16_rgb" accepts packed 16-bit "r", "g"    */
/* and "b" data, for "npixels" pixels, and writing it into         */
/* seperate output buffers of "r", "g" and "b".                    */
/*                                                                 */
/*=================================================================*/


#include "../inc/vcop_rgb16_rgb_c.h"

void vcop_rgb555_rgb
(
    unsigned short rgb16[],
    unsigned int   npixels,
    unsigned char  r[],
    unsigned char  g[],
    unsigned char  b[]
)
{
    /*-----------------------------------------------------------*/
    /* Since we are packing 16-bit data in 32-bit buffers, we    */
    /* need to derive a basic byte pointer, so we can read the   */
    /* data at a more elementray level.                          */
    /*-----------------------------------------------------------*/

    unsigned char  *prgb16 = (unsigned char *)&rgb16[0];
    unsigned int   i;

    /*-----------------------------------------------------------*/
    /* For each of the pixels, read interleaved "r", "g", "b"    */
    /* and write out as seperate component planes.               */
    /*-----------------------------------------------------------*/

    for (i = 0; i < npixels; i++)
    {
        r[i] = prgb16[(2 * i)];
        b[i] = prgb16[(2 * i) + 1];

        g[i] = ( r[i] >> 5 ) | (( b[i] << 3 ) & 0x1F);
        
        r[i] = (r[i] & 0x1F) ;
        b[i] = ((b[i] << 1) >> 3);


    }
}


void vcop_rgb565_rgb
(
    unsigned short rgb16[],
    unsigned int   npixels,
    unsigned char  r[],
    unsigned char  g[],
    unsigned char  b[]
)
{
    /*-----------------------------------------------------------*/
    /* Since we are packing 16-bit data in 32-bit buffers, we    */
    /* need to derive a basic byte pointer, so we can read the   */
    /* data at a more elementray level.                          */
    /*-----------------------------------------------------------*/

    unsigned char  *prgb16 = (unsigned char *)&rgb16[0];
    unsigned int   i;

    /*-----------------------------------------------------------*/
    /* For each of the pixels, read interleaved "r", "g", "b"    */
    /* and write out as seperate component planes.               */
    /*-----------------------------------------------------------*/

    for (i = 0; i < npixels; i++)
    {
        r[i] = prgb16[(2 * i)];
        b[i] = prgb16[(2 * i) + 1];

        g[i] = ( r[i] >> 5 ) | (( b[i] << 3 ) & 0x3F);
        
        r[i] = (r[i] & 0x1F) ;
        b[i] = (b[i] >> 3);


    }
}

/*=================================================================*/
/* End of file: vcop_rgb16_rgb_c.c                                 */
/*-----------------------------------------------------------------*/
/* Texas Instruments Incorporated 2009-2012.                       */
/*-----------------------------------------------------------------*/
 
