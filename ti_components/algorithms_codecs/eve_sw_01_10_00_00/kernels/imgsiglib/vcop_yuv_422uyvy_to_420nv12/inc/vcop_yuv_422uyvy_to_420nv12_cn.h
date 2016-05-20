/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*                                                                          */
/*     @file : vcop_yuv_422uyvy_to_420nv12_cn.h                             */
/*                                                                          */
/*     @brief : This file contains declarations for the C reference         */
/*         function for YUV 422 UYVY to YUV420 NV12 format conversion.      */
/*                                                                          */
/*     vcop_yuv_422uyvy_to_420nv12_cn                                       */
/*         This is the c-reference for the vcop_yuv_422uyvy_to_420nv12      */
/*         kernel. This routine accepts an YUV 422 UYVY input image and     */
/*         converts it into an YUV 420 NV12 image. The output UV values     */
/*         are obtained by averaging the even and odd row samples.          */
/*                                                                          */
/*     USAGE:                                                               */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_yuv_422uyvy_to_420nv12_cn                                  */
/*     (                                                                    */
/*         unsigned char *img,                                              */
/*         unsigned char *out,                                              */
/*         unsigned short width,                                            */
/*         unsigned short height,                                           */
/*         unsigned short in_stride,                                        */
/*         unsigned short out_stride                                        */
/*     )                                                                    */
/*                                                                          */
/*     img           : YUV 422 UYVY Image                                   */
/*     out           : YUV 420 NV12 output image                            */
/*     width         : Width of the input/output images                     */
/*     height        : Height of the input/output images                    */
/*     in_stride     : Stride for the input image                           */
/*     out_stride    : Stride of the output image                           */
/*                                                                          */
/*     Returns :  None or void.                                             */
/*                                                                          */
/*     @version 1.0 (Oct 2013) : Base version.                              */
/*                                                                          */
/*==========================================================================*/

#ifndef _VCOP_YUV_422UYVY_TO_420NV12_CN
#define _VCOP_YUV_422UYVY_TO_420NV12_CN  1


void vcop_yuv_422uyvy_to_420nv12_cn
(
    unsigned char *img,
    unsigned char *out,
    unsigned short width,
    unsigned short height,
    unsigned short in_stride,
    unsigned short out_stride
);

#endif /* _VCOP_YUV_422UYVY_TO_420NV12_CN */
