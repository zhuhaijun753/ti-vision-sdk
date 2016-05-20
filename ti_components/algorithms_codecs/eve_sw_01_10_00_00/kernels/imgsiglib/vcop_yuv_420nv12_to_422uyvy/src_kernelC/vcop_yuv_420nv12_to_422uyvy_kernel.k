/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*                                                                          */
/*    @file : vcop_yuv_420nv12_to_422uyvy_kernel.k                          */
/*                                                                          */
/*    @brief : This routine accepts an YUV 420 NV12 images of size width    */
/*             by height and with a stride of in_stride. The kernel         */
/*             performs format conversion and outputs a YUV 422 UYVY image. */
/*             The missing UV samples are filled up by upsampling by 2.     */
/*                                                                          */
/*     The recommended banks for each of the buffers is captured as A/B/C   */
/*     as part of the buffer pointer. A/B/C can either be IMBUF High,       */
/*     IMBUF low or WMEM.                                                   */
/*                                                                          */
/*    USAGE:                                                                */
/*    This routine is C-callable and can be called as:                      */
/*                                                                          */
/*    void vcop_yuv_420nv12_to_422uyvy                                      */
/*    (                                                                     */
/*        __vptr_uint8   in_img_A,                                          */
/*        __vptr_uint8   out_B,                                             */
/*        unsigned short width,                                             */
/*        unsigned short height,                                            */
/*        unsigned short in_stride,                                         */
/*        unsigned short out_stride                                         */
/*    )                                                                     */
/*                                                                          */
/*     in_img_A      : YUV 420 NV12 Image                                   */
/*     out_B         : YUV 422 UYVY output image                            */
/*     width         : Width of the input/output images                     */
/*     height        : Height of the input/output images                    */
/*     in_stride     : Stride for the input image                           */
/*     out_stride    : Stride of the output image                           */
/*                                                                          */
/*    Returns     :  None or void.                                          */
/*                                                                          */
/*    ASSUMPTIONS:                                                          */
/*      The missing UV samples for odd rows in output are same as UV        */
/*      values in the previous even row of output.                          */
/*                                                                          */
/*    PERFORMANCE MEASUREMENT:                                              */
/*      0.140625 cycles/pixel + 56 cycle VCOP overheads                     */
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

void vcop_yuv_420nv12_to_422uyvy
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
        for(int I2 = 0; I2 < (width + VCOP_SIMD_WIDTH - 1)/VCOP_SIMD_WIDTH; I2++) {
            __vector Vy1, Vy2, Vuv, Vuv1, Vuv2;
            __agen Addr_in_y, Addr_in_uv, Addr_out;

            Addr_in_y = I1*2*in_stride + I2*VCOP_SIMD_WIDTH;
            Addr_in_uv = I1*in_stride + I2*VCOP_SIMD_WIDTH;
            Addr_out = I1*2*out_stride + I2*VCOP_2SIMD_WIDTH;

            Vy1 =  (in_img_A)[Addr_in_y];
            Vy2 =  (in_img_A + in_stride)[Addr_in_y];
            Vuv =  (in_img_A + height*in_stride)[Addr_in_uv];

            Vuv1 = Vuv;
            Vuv2 = Vuv;

            out_B[Addr_out].interleave() = (Vuv1, Vy1);
            (out_B + out_stride)[Addr_out].interleave() = (Vuv2, Vy2);
        }
    }
}
