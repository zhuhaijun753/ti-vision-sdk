/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*     TEXAS INSTRUMENTS, INC.                                              */
/*                                                                          */
/*     @file : vcop_alpha_blend_yuv420nv12_cn                               */
/*                                                                          */
/*     @brief : This is the c-reference for the vcop_alpha_blend_yuv420nv12 */
/*         kernel. This routine accepts two YUV 420 NV12 input images and   */
/*         an 2D array containing alpha values and outputs alpha belended   */
/*         image.                                                           */
/*                                                                          */
/*     USAGE:                                                               */
/*     This routine is C-callable and can be called as:                     */
/*                                                                          */
/*     void vcop_alpha_blend_yuv420nv12_cn                                  */
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
/*     img1           : YUV 420 NV12 Image 1                                */
/*     img2           : YUV 420 NV12 Image 2                                */
/*     alphaFrame     : Alpha values for Y pixels, ranges from [0-16]       */
/*     out            : Alpha blended output image (YUV 420 NV12)           */
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

#include <stdio.h>
#include <string.h>
#include "vcop_alpha_blend_yuv420nv12_cn.h"

void vcop_alpha_blend_yuv420nv12_cn
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
    unsigned short y1, y2, y, alpha;
    unsigned short uv1, uv2, uv;

    // Alpha blending of Y
    for(i = 0; i < height; i++) {
        for(j = 0; j < width; j++) {
            alpha = alphaFrame[i*width + j];

            y1 = img1[i*in_img1_stride + j];
            y2 = img2[i*in_img2_stride + j];
            y = (alpha*(y1 - y2) + y2*16)>>4;
            out[i*out_stride + j] = (unsigned char)y;
        }
    }

    // Alpha blending of UV
    for(i = 0; i < height/2; i++) {
        for(j = 0; j < width; j++) {
            alpha = alphaFrame[2*i*width + j];

            uv1 = img1[height*in_img1_stride + i*in_img1_stride + j];
            uv2 = img2[height*in_img2_stride + i*in_img2_stride + j];
            uv = (alpha*(uv1 - uv2) + uv2*16)>>4;
            out[height*out_stride + i*out_stride + j] = (unsigned char)uv;
        }
    }
}
