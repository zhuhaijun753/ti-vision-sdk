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

void natc_gamma_correction
(
unsigned short *r_buff,
unsigned short *g_buff,
unsigned short *b_buff,
unsigned short *out_r_buff,
unsigned short *out_g_buff,
unsigned short *out_b_buff,
unsigned int    img_width,
unsigned int    img_height,
unsigned int    input_stride,
unsigned int    output_stride,
short          *LUT
);


