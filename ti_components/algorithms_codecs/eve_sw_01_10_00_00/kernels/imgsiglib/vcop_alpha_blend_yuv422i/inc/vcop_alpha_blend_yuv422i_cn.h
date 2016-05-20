/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*                                                                          */
/*     @file : vcop_alpha_blend_yuv422i_cn.h                                */
/*                                                                          */
/*     @brief : This file contains declarations for the C reference         */
/*         function for alpha blending of two YUV 422 Interleaved images.   */
/*                                                                          */
/*     vcop_alpha_blend_yuv420nv12_cn                                       */
/*         This is the c-reference for the vcop_alpha_blend_yuv422i         */
/*         kernel. This routine accepts two YUV 422 interleaved input       */
/*         images and an 2D array containing alpha values and outputs       */
/*         alpha belended image of same format. Both YUV 422 UYVY and 422   */
/*         YUYV are supported.                                              */
/*                                                                          */
/*     USAGE:                                                               */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_alpha_blend_yuv422i_cn                                     */
/*     (                                                                    */
/*         unsigned char *img1,                                             */
/*         unsigned char *img2,                                             */
/*         unsigned char *alphaFrame,                                       */
/*         unsigned char *out,                                              */
/*         unsigned short width,                                            */
/*         unsigned short height,                                           */
/*         unsigned short in_img1_stride,                                   */
/*         unsigned short in_img2_stride,                                   */
/*         unsigned short out_stride                                        */
/*     )                                                                    */
/*                                                                          */
/*     img1           : YUV 422 Interleaved Image 1                         */
/*     img2           : YUV 422 Interleaved Image 2                         */
/*     alphaFrame     : Alpha values for Y pixels, ranges from [0-16]       */
/*     out            : Alpha blended output image (YUV 422 Interleaved)    */
/*     width          : Width of the input/output images                    */
/*     height         : Height of the input/output images                   */
/*     in_img1_stride : Stride for the input image 1                        */
/*     in_img2_stride : Stride for the input image 2                        */
/*     out_stride     : Stride of the output image                          */
/*                                                                          */
/*     Returns :  None or void.                                             */
/*                                                                          */
/*     @version 1.0 (Oct 2013) : Base version.                              */
/*                                                                          */
/*==========================================================================*/

#ifndef _VCOP_ALPHA_BLEND_YUV422I_CN
#define _VCOP_ALPHA_BLEND_YUV422I_CN  1


void vcop_alpha_blend_yuv422i_cn
(
    unsigned char *img1,
    unsigned char *img2,
    unsigned char *alphaFrame,
    unsigned char *out,
    unsigned short width,
    unsigned short height,
    unsigned short in_img1_stride,
    unsigned short in_img2_stride,
    unsigned short out_stride
);

#endif /* _VCOP_ALPHA_BLEND_YUV422I_CN */
