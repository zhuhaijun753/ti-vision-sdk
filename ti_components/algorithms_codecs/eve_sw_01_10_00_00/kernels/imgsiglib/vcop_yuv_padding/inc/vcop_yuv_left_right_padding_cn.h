/*==========================================================================*/
/*      Copyright (C) 2009-2014 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*                                                                          */
/*     NAME                                                                 */
/*     vcop_yuv_left_right_padding_cn.h                                     */
/*                                                                          */
/*     DESCRIPTION                                                          */
/*         This is the c-reference header for the                           */
/*         vcop_yuv_left_right_padding_kernel  kernel                       */
/*                                                                          */
/*                                                                          */
/*     @version 0.1 (May 2014) : Base version.                              */
/*                                                                          */
/*==========================================================================*/

#ifndef _VCOP_LOCATION_MATRIX_CN
#define _VCOP_LOCATION_MATRIX_CN  1

void vcop_yuv_left_right_padding_u8_cn
(
    unsigned char *   in_left,
    unsigned char *   in_right,
    unsigned char *   out_left,
    unsigned char *   out_right,
    unsigned short    width,
    unsigned short    height,
    unsigned short    out_stride
);
void vcop_yuv_left_right_padding_u16_cn
(
    unsigned short *  in_left,
    unsigned short *  in_right,
    unsigned short *  out_left,
    unsigned short *  out_right,
    unsigned short    width,
    unsigned short    height,
    unsigned short    out_stride
);
#endif /* _VCOP_LOCATION_MATRIX_CN */

