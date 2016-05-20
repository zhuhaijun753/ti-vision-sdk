/*==========================================================================*/
/*      Copyright (C) 2009-2014 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*                                                                          */
/*     NAME                                                                 */
/*     vcop_yuv_left_right_padding_cn.c                                     */
/*                                                                          */
/*     DESCRIPTION                                `                         */
/*         This is the c-reference implementation for the                   */
/*         vcop_location_matrix  kernel                                     */
/*                                                                          */
/*                                                                          */
/*     @version 0.1 (May 2014) : Base version.                              */
/*                                                                          */
/*==========================================================================*/
#include "stdlib.h"
#include "vcop_yuv_left_right_padding_cn.h"

void vcop_yuv_left_right_padding_u8_cn
(
    unsigned char *   in_left,
    unsigned char *   in_right,
    unsigned char *   out_left,
    unsigned char *   out_right,
    unsigned short    width,
    unsigned short    height,
    unsigned short    out_stride
)
{
  int i,j;
  for(j =0; j < height; j++)
  {
    for(i =0; i < width; i++)
    {
      out_left[j*out_stride + i]  = in_left[j];
      out_right[j*out_stride + i] = in_right[j];
    }
  }
}
void vcop_yuv_left_right_padding_u16_cn
(
    unsigned short *  in_left,
    unsigned short *  in_right,
    unsigned short *  out_left,
    unsigned short *  out_right,
    unsigned short    width,
    unsigned short    height,
    unsigned short    out_stride
)
{
  int i,j;
  for(j =0; j < height; j++)
  {
    for(i =0; i < width; i++)
    {
      out_left[j*out_stride + i]  = in_left[j];
      out_right[j*out_stride + i] = in_right[j];
    }
  }
}
