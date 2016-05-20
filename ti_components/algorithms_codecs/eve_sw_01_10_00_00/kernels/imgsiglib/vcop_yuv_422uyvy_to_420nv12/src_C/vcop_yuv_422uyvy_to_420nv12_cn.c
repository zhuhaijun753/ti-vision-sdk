/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*                                                                          */
/*     @file : vcop_yuv_422uyvy_to_420nv12_cn                               */
/*                                                                          */
/*     @brief : This is the c-reference for the vcop_yuv_422uyvy_to_420nv12 */
/*         kernel. This routine accepts an YUV 422 UYVY input image and     */
/*         converts it into an YUV 420 NV12 image. The output UV values     */
/*         are obtained by averaging (with rounding) the even and odd row   */
/*         samples.                                                         */
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

#include <stdio.h>
#include <string.h>
#include "vcop_yuv_422uyvy_to_420nv12_cn.h"

void vcop_yuv_422uyvy_to_420nv12_cn
(
    unsigned char *img,
    unsigned char *out,
    unsigned short width,
    unsigned short height,
    unsigned short in_stride,
    unsigned short out_stride
)
{
    int i, j;
    unsigned char y1, y2, uv1, uv2, uv;

    for(i = 0; i < height/2; i++) {
        for(j = 0; j < width; j++) {

            // Load even row samples
            uv1 = img[(2*i)*in_stride + 2*j];
            y1 = img[(2*i)*in_stride + 2*j + 1];

            // Load odd row samples
            uv2 = img[(2*i + 1)*in_stride + 2*j];
            y2 = img[(2*i + 1)*in_stride + 2*j + 1];

            uv = (uv1 + uv2 + 1)/2;

            out[(2*i)*out_stride + j] = y1;
            out[(2*i + 1)*out_stride + j] = y2;
            out[height*out_stride + i*out_stride + j] = uv;
        }
    }
}
