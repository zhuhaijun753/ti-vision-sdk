/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/* ===========================================================================*/
/*   @file : vcop_image_pyramid_u8.h                                          */
/*                                                                            */
/*   @brief  : This file contains all the header for image pyramid            */
/*                                                                            */
/*   @version 0.0 (Feb 2012) : Base version.                                  */
/*                                                                            */
/*============================================================================*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void vcop_image_pyramid_uv_u8
(
  unsigned char  *pIn,
  unsigned int    blk_width,
  unsigned int    blk_height,
  unsigned char  *pOut
);
