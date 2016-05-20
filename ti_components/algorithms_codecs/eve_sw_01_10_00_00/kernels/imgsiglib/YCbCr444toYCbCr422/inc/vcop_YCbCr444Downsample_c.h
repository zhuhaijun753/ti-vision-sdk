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


#ifndef __VCOP_YCbCr_Downsample_H__
#define __VCOP_YCbCr_Downsample_H__  1

void vcop_YCbCr444_Downsample422_char
(
    unsigned char  YCbCr[],
    unsigned int   npixels,
    unsigned char  Y[],
    unsigned char  Cb[],
    unsigned char  Cr[]
);


void vcop_YCbCr444_Downsample422_short
(
    unsigned short  YCbCr[],
    unsigned int    npixels,
    unsigned short  Y[],
    unsigned short  Cb[],
    unsigned short  Cr[]
);

void vcop_YCbCr422_Downsample422_char
(
    unsigned char  YCbCr[],
    unsigned int   npixels,
    unsigned char  Y[],
    unsigned char  Cb[],
    unsigned char  Cr[]
);

void vcop_YCbCr422_Downsample422_short
(
    unsigned short  YCbCr[],
    unsigned int    npixels,
    unsigned short  Y[],
    unsigned short  Cb[],
    unsigned short  Cr[]
);

#endif

/*-----------------------------------------------------------------*/
/* End of file: vcop_YCbCr_Downsample_c.h                          */
/*=================================================================*/
/* Texas Instruments Incorporated 2009-2012.                       */
/*-----------------------------------------------------------------*/

