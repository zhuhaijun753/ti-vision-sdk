/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/*-----------------------------------------------------------------*/
/* NAME : vcop_YCbCrDeinterleave : Test bench data                 */ 
/*                                                                 */
/*                                                                 */
/* DESCRIPTION:                                                    */
/* The function "vcop_YCbCrDeinterleave" accepts  8 or 16-bit data */
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
/*     unsigned char   YCbCr[],                                    */
/*     unsigned int   npixels,                                     */
/*     unsigned char  Y[],                                         */
/*     unsigned char  Cb[],                                        */
/*     unsigned char  Cr[]                                         */
/* )                                                               */
/*                                                                 */
/*                                                                 */
/*=================================================================*/


#include "../inc/vcop_YCbCr444Deinterleave_c.h"

void vcop_YCbCr444_Deinterleave444_char
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
        Cb[i] =  YCbCr[(3 * i) + 1];
        Cr[i] =  YCbCr[(3 * i) + 2];
    }
}

void vcop_YCbCr444_Deinterleave444_short
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
        Cb[i] =  YCbCr[(3 * i) + 1];
        Cr[i] =  YCbCr[(3 * i) + 2];
    }
}

void vcop_YCbCr422_Deinterleave422_char
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
    /* YCbCr 422 is of the format Y Cb Y Cr Y Cb Y Cr Y Cb...    */
    /* and is written out as seperate component planes.          */
    /*-----------------------------------------------------------*/

    for (i = 0; i < npixels; i++)
    {
        Y[2 * i]  =  YCbCr[(4 * i) + 0];
        Cb[i] =  YCbCr[(4 * i) + 1];
        Y[(2 * i) + 1]  =  YCbCr[(4 * i) + 2];
        Cr[i] =  YCbCr[(4 * i) + 3];
    }
}

void vcop_YCbCr422_Deinterleave422_short
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
    /* YCbCr 422 is of the format Y Cb Y Cr Y Cb Y Cr Y Cb...    */
    /* and is written out as seperate component planes.          */
    /*-----------------------------------------------------------*/

    for (i = 0; i < npixels; i++)
    {
        Y[2 * i]  =  YCbCr[(4 * i) + 0];
        Cb[i] =  YCbCr[(4 * i) + 1];
        Y[(2 * i) + 1]  =  YCbCr[(4 * i) + 2];
        Cr[i] =  YCbCr[(4 * i) + 3];
    }
}

/*=================================================================*/
/* End of file: vcop_YCbCrDeinterleave_c.c                         */
/*-----------------------------------------------------------------*/
/* Texas Instruments Incorporated 2009-2012.                       */
/*-----------------------------------------------------------------*/
 
