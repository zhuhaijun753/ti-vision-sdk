/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*-----------------------------------------------------------------*/
/* NAME : vcop_rgb16_rgb : Test bench data                         */ 
/*                                                                 */
/*                                                                 */
/* DESCRIPTION:                                                    */
/* The function "vcop_rgb16_rgb" accepts packed 16-bit data in     */
/* the form of 8-bit "r", "g" and "b", and writes out seperate     */
/* 8-bit "r", 8-bit "g" and "b". The reason for having this        */
/* function, is to allow the vector core to work in it's           */
/* natural format of looking at similar data together, rather      */
/* than diverse data.                                              */
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
/*=================================================================*/


#ifndef _VCOP_RGB16_RGB_H
#define _VCOP_RGB16_RGB_H  1

void vcop_rgb555_rgb
(
    unsigned short rgb16[],
    unsigned int   npixels,
    unsigned char  r[],
    unsigned char  g[],
    unsigned char  b[]
);

void vcop_rgb565_rgb
(
    unsigned short rgb16[],
    unsigned int   npixels,
    unsigned char  r[],
    unsigned char  g[],
    unsigned char  b[]
);


#endif

/*-----------------------------------------------------------------*/
/* End of file: vcop_rgb16_rgb_c.h                                 */
/*=================================================================*/
/* Texas Instruments Incorporated 2009-2012.                       */
/*-----------------------------------------------------------------*/

