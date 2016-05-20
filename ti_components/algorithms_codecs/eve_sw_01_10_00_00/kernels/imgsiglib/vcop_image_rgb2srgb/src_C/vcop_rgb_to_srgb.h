/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/* ===========================================================================*/
/*   @file : vcop_rgb_to_srgb.h                                    */

/*   @brief  : This file contains all functions related to RGB to sRGB conversion   */

/*   @author Gajanan Ambi(gajanan.ambi@ti.com)                                */

/*   @version 0.0 (September 2012) : Base version.                               */

/*============================================================================*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#if 0
short rgb_to_srgb_coefs[9] =
{
    829, -393,  127,
   -248,  480,  10,
    14,   52,   270
};
#else
short rgb_to_srgb_coefs[9] =
{
    256, 0,  0,
    0,  256,  0,
    0,   0,   256
};

#endif
void vcop_rgb_to_srgb
(
 unsigned short *Rbuff,
 unsigned short *Gbuff,
 unsigned short *Bbuff,
 unsigned int    img_height,
 unsigned int    img_width,
 short          *coeff
);

