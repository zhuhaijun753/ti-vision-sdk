/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*                                                                          */
/*     @file : vcop_yuv_420nv12_to_422uyvy_cn.h                             */
/*                                                                          */
/*     @brief : This file contains declarations for the C reference         */
/*         function for YUV420 NV12 to YUV 422 UYVY format conversion.      */
/*                                                                          */
/*     vcop_yuv_420nv12_to_422uyvy_cn                                       */
/*         This is the c-reference for the vcop_yuv_420nv12_to_422uyvy      */
/*         kernel. This routine accepts an YUV 420 NV12 input image and     */
/*         converts it into an YUV 422 UYVY image. The missing UV values    */
/*         are obtained by upsampling by 2.                                 */
/*                                                                          */
/*     USAGE:                                                               */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_yuv_420nv12_to_422uyvy_cn                                  */
/*     (                                                                    */
/*         unsigned char *img,                                              */
/*         unsigned char *out,                                              */
/*         unsigned short width,                                            */
/*         unsigned short height,                                           */
/*         unsigned short in_stride,                                        */
/*         unsigned short out_stride                                        */
/*     )                                                                    */
/*                                                                          */
/*     img           : YUV 420 NV12 Image                                   */
/*     out           : YUV 422 UYVY output image                            */
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

#ifndef _VCOP_YUV_420NV12_TO_422UYVY_CN
#define _VCOP_YUV_420NV12_TO_422UYVY_CN  1


void vcop_yuv_420nv12_to_422uyvy_cn
(
    unsigned char *img,
    unsigned char *out,
    unsigned short width,
    unsigned short height,
    unsigned short in_stride,
    unsigned short out_stride
);

#endif /* _VCOP_YUV_420NV12_TO_422UYVY_CN */
