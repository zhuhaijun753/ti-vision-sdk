/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/* ===========================================================================*/
/*   @file : vcop_interleave.c                                    */

/*   @brief  :    */

/*   @author Gajanan Ambi(gajanan.ambi@ti.com)                                */

/*   @version 0.0 (September 2012) : Base version.                               */

/*============================================================================*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "vcop_interleave.h"

void vcop_image_interleave_u8
(
unsigned char  *in_buff_Y,
unsigned char  *in_buff_UV,
unsigned int    blk_width,
unsigned int    blk_height,
unsigned char  *output_buff
)
{
  unsigned int i,j;

  for(i = 0; i<blk_height; i++)
  {
    for(j = 0; j<blk_width; j++)
    {
      *output_buff++ = *in_buff_UV++;
      *output_buff++ = *in_buff_Y++;
    }
  }
}
                  
