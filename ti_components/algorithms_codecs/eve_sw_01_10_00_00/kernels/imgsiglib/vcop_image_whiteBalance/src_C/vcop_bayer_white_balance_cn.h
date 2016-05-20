/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/* ===========================================================================*/
/*   @file : vcop_white_balance.h                                    */

/*   @brief  : This file contains all the header files RGB to yuv conversion   */

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

void natc_bayer_white_balance
(
unsigned short *in_buff,
unsigned short *out_buff,
unsigned int    img_width,
unsigned int    img_height,
unsigned int    gainFactor_R,
unsigned int    gainFactor_Gb,
unsigned int    gainFactor_Gr,
unsigned int    gainFactor_B,
unsigned int    gainFactor_shift,
unsigned int    input_stride,
unsigned int    output_stride,
unsigned char   bayerFormat
);


