/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*                                                                          */
/*    @file : vcop_yuv_422uyvy_to_420nv12_kernel.k                          */
/*                                                                          */
/*    @brief : This routine accepts an YUV 422 UYVY images of size width    */
/*             by height and with a stride of in_stride. The kernel         */
/*             performs format conversion and outputs a YUV 420 NV12 image. */
/*             The output UV values are obtained by averaging the even      */
/*             and odd row samples from YUV 422 UYVY input.                 */
/*                                                                          */
/*     The recommended banks for each of the buffers is captured as A/B/C   */
/*     as part of the buffer pointer. A/B/C can either be IMBUF High,       */
/*     IMBUF low or WMEM.                                                   */
/*                                                                          */
/*    USAGE:                                                                */
/*    This routine is C-callable and can be called as:                      */
/*                                                                          */
/*    void vcop_yuv_422uyvy_to_420nv12                                      */
/*    (                                                                     */
/*        __vptr_uint8   in_img_A,                                          */
/*        __vptr_uint8   out_B,                                             */
/*        unsigned short width,                                             */
/*        unsigned short height,                                            */
/*        unsigned short in_stride,                                         */
/*        unsigned short out_stride                                         */
/*    )                                                                     */
/*                                                                          */
/*     in_img_A      : YUV 422 UYVY Image                                   */
/*     out_B         : YUV 420 NV12 output image                            */
/*     width         : Width of the input/output images                     */
/*     height        : Height of the input/output images                    */
/*     in_stride     : Stride for the input image                           */
/*     out_stride    : Stride of the output image                           */
/*                                                                          */
/*    Returns     :  None or void.                                          */
/*                                                                          */
/*    ASSUMPTIONS:                                                          */
/*      The output UV values are obtained by averaging the even and odd     */
/*      row samples (with rounding) from YUV 422 UYVY input.                */
/*                                                                          */
/*    PERFORMANCE MEASUREMENT:                                              */
/*      0.1875 cycles/pixel + 54 cycle VCOP overheads                       */
/*                                                                          */
/*    @author  : Anoop K P(a-kp@ti.com)                                     */
/*                                                                          */
/*    @version : 1.0 (Oct 2013) : Base version.                             */
/*                                                                          */
/*==========================================================================*/
#if (VCOP_HOST_EMULATION)
#include <vcop.h>
#endif

#define VCOP_2SIMD_WIDTH        (2 * VCOP_SIMD_WIDTH)

void vcop_yuv_422uyvy_to_420nv12
(
    __vptr_uint8   in_img_A,
    __vptr_uint8   out_B,
    unsigned short width,
    unsigned short height,
    unsigned short in_stride,
    unsigned short out_stride
)
{
    for(int I1 = 0; I1 < height/2; I1++) {
        for(int I2 = 0; I2 < (2*width + VCOP_2SIMD_WIDTH - 1)/VCOP_2SIMD_WIDTH; I2++) {
            __vector Vy1, Vy2, Vuv1, Vuv2, Vuv;
            __agen Addr_in, Addr_out_y, Addr_out_uv;

            Addr_in = I1*2*in_stride + I2*VCOP_2SIMD_WIDTH;
            Addr_out_y = I1*2*out_stride + I2*VCOP_SIMD_WIDTH;
            Addr_out_uv = I1*out_stride + I2*VCOP_SIMD_WIDTH;

            (Vuv1, Vy1) = (in_img_A)[Addr_in].deinterleave();
            (Vuv2, Vy2) = (in_img_A + in_stride)[Addr_in].deinterleave();

            Vuv = Vuv1 + Vuv2;

            out_B[Addr_out_y] = Vy1;
            (out_B + out_stride)[Addr_out_y] = Vy2;
            (out_B + height*out_stride)[Addr_out_uv] = Vuv.round(1);
        }
    }
}
