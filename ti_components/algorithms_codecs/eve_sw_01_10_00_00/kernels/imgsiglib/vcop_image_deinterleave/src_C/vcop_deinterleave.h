/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/* ===========================================================================*/
/*   @file : vcop_deinterleave.h                                    */

/*   @brief  :   */

/*   @author Gajanan Ambi(gajanan.ambi@ti.com)                                */

/*   @version 0.0 (March 2012) : Base version.                               */

/*============================================================================*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void vcop_image_deinterleave_u8
(
  unsigned char *in_buff,
  unsigned int    blk_width,
  unsigned int    blk_height,
  unsigned char  *out_buff_y,
  unsigned char  *out_buff_uv
);

                  
