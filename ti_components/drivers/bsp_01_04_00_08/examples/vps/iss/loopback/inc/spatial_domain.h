/************************************************************************************//**
* TI ISP Library Refernce Code
* This library is a software module developed for simulation of vision and ISP
* algorithms ported on TI's embedded platforms
* Copyright (C) 2014 Texas Instruments Incorporated - http://www.ti.com/
* ALL RIGHTS RESERVED
* @author       Hrushikesh Garud (A0393878)
* @version      1.0
*
****************************************************************************************/

#ifndef SPATIAL_DOMAIN_H
#define SPATIAL_DOMAIN_H
# include "Image_Data_Handling.h"
//typedef unsigned char kz_pixel_t;  /* for 8 bit-per-pixel images */
#define uiNR_OF_GREY (256)

#define false 0
#define true 1

typedef struct
{
    int hist[256];
}Histogram;

/******************************************************************************//**
* FUNCTION: int SDF_computeHistogram(Image *ptr, int *h, char channel);
* perfoms
*         For a given image computes histogram of a color channel specified
* Returns
*         -1 for non 8/24/32 bit image, empty image or NULL value in histogram
*         pointer
*
*         0 if specified channel not available in the image
*
*         1 on success
*******************************************************************************/
int SDF_computeHistogram(Image *ptr, Histogram *h, char channel);

#endif
