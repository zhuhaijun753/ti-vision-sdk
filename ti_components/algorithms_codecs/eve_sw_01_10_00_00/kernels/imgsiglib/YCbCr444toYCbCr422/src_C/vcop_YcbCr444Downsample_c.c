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
/*     unsigned char   YCbCr[],                                    */
/*     unsigned int   npixels,                                     */
/*     unsigned char  Y[],                                         */
/*     unsigned char  Cb[],                                        */
/*     unsigned char  Cr[]                                         */
/* )                                                               */
/*                                                                 */
/*                                                                 */
/*=================================================================*/


#include "../inc/vcop_YCbCr444Downsample_c.h"

void vcop_YCbCr444_Downsample422_char
(
    unsigned char  YCbCr[],
    unsigned int   npixels,
    unsigned char  Y[],
    unsigned char  Cb[],
    unsigned char  Cr[]
)
{
    unsigned int   i;

    /*-----------------------------------------------------------*/
    /* YCbCr 444 is of the format Y Cb Cr Y Cb Cr Y Cb Cr...     */
    /* and is written out as seperate component planes.          */
    /*-----------------------------------------------------------*/

    for (i = 0; i < npixels; i++)
    {
        Y[i]  =  YCbCr[(3 * i) + 0];
    }

    for (i = 0; i < npixels; i++)
    {
        Cb[i] =  (YCbCr[(6 * i) + 1] + YCbCr[(6 * i) + 4])/2;
    }
 
    for (i = 0; i < npixels; i++)
    {
        Cr[i] =  (YCbCr[(6 * i) + 2] + YCbCr[(6 * i) + 5])/2;
    }

}

void vcop_YCbCr444_Downsample422_short
(
    unsigned short  YCbCr[],
    unsigned int    npixels,
    unsigned short  Y[],
    unsigned short  Cb[],
    unsigned short  Cr[]
)
{
    unsigned int   i;

    /*-----------------------------------------------------------*/
    /* YCbCr 444 is of the format Y Cb Cr Y Cb Cr Y Cb Cr...     */
    /* and is written out as seperate component planes.          */
    /*-----------------------------------------------------------*/

    for (i = 0; i < npixels; i++)
    {
        Y[i]  =  YCbCr[(3 * i) + 0];
    }

    for (i = 0; i < npixels; i++)
    {
        Cb[i] =  (YCbCr[(6 * i) + 1] + YCbCr[(6 * i) + 4])/2;
    }
 
    for (i = 0; i < npixels; i++)
    {
        Cr[i] =  (YCbCr[(6 * i) + 2] + YCbCr[(6 * i) + 5])/2;
    }
}


