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
/*     unsigned char  out_rgb555[], // out_rgb565                  */
/* );                                                              */
/*                                                                 */
/* The function "vcop_rgb_rgb16" accepts unpacked "r", "g"         */
/* and "b" data, for "npixels" pixels, and writes packed 16-bit    */
/* RGB555 or RGB565 data.                                          */
/*                                                                 */
/*=================================================================*/


#ifndef _VCOP_RGB_RGB16_H
#define _VCOP_RGB_RGB16_H  1

void vcop_rgb_rgb555
(
    unsigned char  *in_rgb,
    unsigned int   npixels,
    unsigned short *rgb555
);

void vcop_rgb_rgb565
(
    unsigned char  *in_rgb,
    unsigned int   npixels,
    unsigned short *rgb565
);

#endif

/*-----------------------------------------------------------------*/
/* End of file: vcop_rgb_rgb16_c.h                                 */
/*=================================================================*/
/* Texas Instruments Incorporated 2009-2012.                       */
/*-----------------------------------------------------------------*/

