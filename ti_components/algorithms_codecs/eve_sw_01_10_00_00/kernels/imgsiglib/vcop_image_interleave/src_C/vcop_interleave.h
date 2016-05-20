/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/* ===========================================================================*/
/*   @file : vcop_interleave.h                                    */

/*   @brief  : This file contains all the header for data interleave  */

/*   @version 0.0 (Feb 2012) : Base version.                               */

/*============================================================================*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void vcop_image_interleave_u8
(
unsigned char  *in_buff_Y,
unsigned char  *in_buff_UV,
unsigned int    blk_width,
unsigned int    blk_height,
unsigned char  *output_buff
);

                  
