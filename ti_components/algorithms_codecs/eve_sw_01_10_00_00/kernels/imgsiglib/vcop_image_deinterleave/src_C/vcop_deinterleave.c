/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/* ===========================================================================*/
/*   @file : vcop_deinterleave.c                                    */

/*   @brief  :    */

/*   @author Gajanan Ambi(gajanan.ambi@ti.com)                                */

/*   @version 0.0 (March 2012) : Base version.                               */

/*============================================================================*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "vcop_deinterleave.h"

void vcop_image_deinterleave_u8
(
unsigned char *in_buff,
unsigned int    blk_width,
unsigned int    blk_height,
unsigned char  *out_buff_y,
unsigned char  *out_buff_uv
)
{
  unsigned int i,j;
  
  for(i = 0; i<blk_height; i++)
  {
    for(j = 0; j<blk_width; j++)
    {
      *out_buff_uv++ = *in_buff++;
      *out_buff_y++ = *in_buff++;
    }
  }
}
                  
