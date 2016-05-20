/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/* ===========================================================================*/
/*   @file : vcop_reference_bayerCFA_interpolate.h                                    */

/*   @brief  : This file contains all functions related to bayer to RGB conversion   */

/*   @author Gajanan Ambi(gajanan.ambi@ti.com)                                */

/*   @version 0.0 (September 2012) : Base version.                               */

/*============================================================================*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//todo: Remove this
#define BGGR 1
#define GRBG 2
#define RGGB 3
#define GBRG 4

void vcop_bayer_to_rgb
(
 unsigned short *in_buff,
 unsigned short *Rbuff,
 unsigned short *Gbuff,
 unsigned short *Bbuff,
 unsigned int  img_height,
 unsigned int  img_width,
 unsigned char bayerFormat
);

