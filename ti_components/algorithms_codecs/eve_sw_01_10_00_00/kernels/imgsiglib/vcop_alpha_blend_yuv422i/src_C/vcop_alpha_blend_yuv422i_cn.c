/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     @file : vcop_alpha_blend_yuv422i_cn                                  */
/*                                                                          */
/*     @brief : This is the c-reference for the vcop_alpha_blend_yuv422i    */
/*         kernel. This routine accepts two YUV 422 Interleaved input       */
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
/*     out_stride    : Stride of the output image                           */
/*                                                                          */
/*     Returns :  None or void.                                             */
/*                                                                          */
/*     @version 1.0 (Oct 2013) : Base version.                              */
/*                                                                          */
/*==========================================================================*/

#include <stdio.h>
#include <string.h>
#include "vcop_alpha_blend_yuv422i_cn.h"

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
)
{
    int i, j;
    unsigned short y1, y2, y, uv1, uv2, uv, alpha;

    for(i = 0; i < height; i++) {
        for(j = 0; j < width; j++) {
            alpha = alphaFrame[i*width + j];

            // Alpha blending of UV
            uv1 = img1[i*in_img1_stride + 2*j];
            uv2 = img2[i*in_img2_stride + 2*j];
            uv = (alpha*(uv1 - uv2) + uv2*16)>>4;
            out[i*out_stride + 2*j] = (unsigned char)uv;

            // Alpha blending of Y
            y1 = img1[i*in_img1_stride + 2*j + 1];
            y2 = img2[i*in_img2_stride + 2*j + 1];
            y = (alpha*(y1 - y2) + y2*16)>>4;
            out[i*out_stride + 2*j + 1] = (unsigned char)y;
        }
    }
}
