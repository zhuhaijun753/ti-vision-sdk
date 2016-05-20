/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/* ===========================================================================*/
/*   @file : vcop_bayer_subSample.h                                    */

/*   @brief  : This file contains all the header files RGB to yuv conversion   */

/*   @author Gajanan Ambi(gajanan.ambi@ti.com)                                */

/*   @version 0.0 (September 2012) : Base version.                               */

/*============================================================================*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void vcop_bayer_subSample
(
unsigned short *in_buff,
unsigned short *out_buff,
unsigned int img_width,
unsigned int img_height,
unsigned int subSample_x,
unsigned int subSample_y,
unsigned int numOfSamples
);

                  
