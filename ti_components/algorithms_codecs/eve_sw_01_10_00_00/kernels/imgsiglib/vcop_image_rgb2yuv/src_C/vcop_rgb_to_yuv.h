/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/* ===========================================================================*/
/*   @file : vcop_rgb_to_yuv.h                                    */

/*   @brief  : This file contains all the header files RGB to yuv conversion   */

/*   @author Gajanan Ambi(gajanan.ambi@ti.com)                                */

/*   @version 0.0 (September 2012) : Base version.                               */

/*============================================================================*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define RGB2YUV_COLOR_FORMAT_YUYV (0)
#define RGB2YUV_COLOR_FORMAT_UYVY (1)

short rgb_to_yuv_coefs[9] =
{
     66, 129,  25,
    -38, -74, 112,
    112, -94, -18
};

void vcop_rgb_to_yuv
(
unsigned short *r_buff,
unsigned short *g_buff,
unsigned short *b_buff,
unsigned int img_height,
unsigned int img_width,
short       *coefs,
unsigned char *YUV_buff,
unsigned char shift,
unsigned char outputFormat
);

                  
