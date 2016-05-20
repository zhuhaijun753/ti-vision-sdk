/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*                                                                          */
/*     @file : vcop_yuv_420nv12_to_422uyvy_cn                               */
/*                                                                          */
/*     @brief : This is the c-reference for the vcop_yuv_420nv12_to_422uyvy */
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

#include <stdio.h>
#include <string.h>
#include "vcop_yuv_420nv12_to_422uyvy_cn.h"

void vcop_yuv_420nv12_to_422uyvy_cn
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
    unsigned char y1, y2, uv;

    for(i = 0; i < height/2; i++) {
        for(j = 0; j < width; j++) {
            y1 = img[(2*i)*in_stride + j];
            y2 = img[(2*i + 1)*in_stride + j];
            uv = img[height*in_stride + i*in_stride + j];

            // Fill up even rows in UYVY format
            out[(2*i)*out_stride + 2*j] = uv;
            out[(2*i)*out_stride + 2*j + 1] = y1;

            // Fill up odd rows in UYVY format
            out[(2*i + 1)*out_stride + 2*j] = uv;
            out[(2*i + 1)*out_stride + 2*j + 1] = y2;
        }
    }
}
