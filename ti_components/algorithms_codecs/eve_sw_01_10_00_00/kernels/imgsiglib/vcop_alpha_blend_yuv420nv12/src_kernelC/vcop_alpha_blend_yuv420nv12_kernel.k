/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*                                                                          */
/*    @file : vcop_alpha_blend_yuv420nv12_kernel.k                          */
/*                                                                          */
/*    @brief : This routine accepts two YUV 420 NV12 images of size width   */
/*             by height and with a stride of in_stride. An frame of alpha  */
/*             values for each Y pixel is also provided. The kernel outputs */
/*             a YUV 420 NV12 image that is an alpha belended version of    */
/*             the two input images.                                        */
/*                                                                          */
/*     The recommended banks for each of the buffers is captured as A/B/C   */
/*     as part of the buffer pointer. A/B/C can either be IMBUF High,       */
/*     IMBUF low or WMEM. In case of don't care it is marked as X.          */
/*                                                                          */
/*    USAGE:                                                                */
/*    This routine is C-callable and can be called as:                      */
/*                                                                          */
/*    void vcop_alpha_blend_yuv420nv12                                      */
/*    (                                                                     */
/*        __vptr_uint8   in_img1_X,                                         */
/*        __vptr_uint8   in_img2_X,                                         */
/*        __vptr_uint8   alphaFrame_X,                                      */
/*        __vptr_uint8   out_X,                                             */
/*        unsigned short width,                                             */
/*        unsigned short height,                                            */
/*        unsigned short in_img1_stride,                                    */
/*        unsigned short in_img2_stride,                                    */
/*        unsigned short out_stride                                         */
/*    )                                                                     */
/*                                                                          */
/*    in_img1_X      : YUV 420 NV12 Image 1                                 */
/*    in_img2_X      : YUV 420 NV12 Image 2                                 */
/*    alphaFrame_X   : Alpha values for Y pixels, ranges from [0-16]        */
/*    out_X          : Alpha blended output image (YUV 420 NV12)            */
/*    width          : Width of the input/output images                     */
/*    height         : Height of the input/output images                    */
/*    in_img1_stride : Stride for the input image 1                         */
/*    in_img2_stride : Stride for the input image 2                         */
/*    out_stride     : Stride of the output image                           */
/*                                                                          */
/*    Returns        :  None or void.                                       */
/*                                                                          */
/*    ASSUMPTIONS:                                                          */
/*      Alpha value ranges from 0 to 16.                                    */
/*                                                                          */
/*    PERFORMANCE MEASUREMENT:                                              */
/*      0.375 cycle/pix execution time + 92 cycle VCOP overheads            */
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

void vcop_alpha_blend_yuv420nv12
(
    __vptr_uint8   in_img1_X,
    __vptr_uint8   in_img2_X,
    __vptr_uint8   alphaFrame_X,
    __vptr_uint8   out_X,
    unsigned short width,
    unsigned short height,
    unsigned short in_img1_stride,
    unsigned short in_img2_stride,
    unsigned short out_stride
)
{
    __vector V16;

    /*-----------------------------------------------------------*/
    /* Alpha blending of Y data.                                 */
    /*-----------------------------------------------------------*/

    V16 = 16;

    for(int I1 = 0; I1 < height; I1++) {
        for(int I2 = 0; I2 < (width + VCOP_2SIMD_WIDTH - 1)/VCOP_2SIMD_WIDTH; I2++) {
            __vector Vy1_e, Vy1_o, Vy2_e, Vy2_o, Vy_e, Vy_o;
            __vector Valpha_e, Valpha_o;
            __vector dy_e, dy_o;
            __agen Addr_in1, Addr_in2, Addr_alpha, Addr_out;

            Addr_in1 = I1*in_img1_stride + I2*VCOP_2SIMD_WIDTH;
            Addr_in2 = I1*in_img2_stride + I2*VCOP_2SIMD_WIDTH;
            Addr_alpha = I1*width + I2*VCOP_2SIMD_WIDTH;
            Addr_out = I1*out_stride + I2*VCOP_2SIMD_WIDTH;

            (Vy1_e, Vy1_o) =  in_img1_X[Addr_in1].deinterleave();
            (Vy2_e, Vy2_o) =  in_img2_X[Addr_in2].deinterleave();
            (Valpha_e, Valpha_o) = alphaFrame_X[Addr_alpha].deinterleave();

            dy_e = Vy1_e - Vy2_e;
            dy_o = Vy1_o - Vy2_o;

            Vy_e = Valpha_e*dy_e;
            Vy_o = Valpha_o*dy_o;

            Vy_e += Vy2_e*V16;
            Vy_o += Vy2_o*V16;

            out_X[Addr_out].interleave() = (Vy_e, Vy_o).truncate(4);
        }
    }

    /*-----------------------------------------------------------*/
    /* Alpha blending of UV data.                                */
    /*-----------------------------------------------------------*/
    for(int I1 = 0; I1 < height/2; I1++) {
        for(int I2 = 0; I2 < (width + VCOP_2SIMD_WIDTH - 1)/VCOP_2SIMD_WIDTH; I2++) {
            __vector Vuv1_e, Vuv1_o, Vuv2_e, Vuv2_o, Vuv_e, Vuv_o;
            __vector Valpha_e, Valpha_o;
            __vector dy_e, dy_o;
            __agen Addr_in1, Addr_in2, Addr_alpha, Addr_out;

            Addr_in1 = I1*in_img1_stride + I2*VCOP_2SIMD_WIDTH;
            Addr_in2 = I1*in_img2_stride + I2*VCOP_2SIMD_WIDTH;
            Addr_alpha = I1*2*width + I2*VCOP_2SIMD_WIDTH;
            Addr_out = I1*out_stride + I2*VCOP_2SIMD_WIDTH;

            (Vuv1_e, Vuv1_o) =  (in_img1_X + height*in_img1_stride)[Addr_in1].deinterleave();
            (Vuv2_e, Vuv2_o) =  (in_img2_X + height*in_img2_stride)[Addr_in2].deinterleave();
            (Valpha_e, Valpha_o) = alphaFrame_X[Addr_alpha].deinterleave();

            dy_e = Vuv1_e - Vuv2_e;
            dy_o = Vuv1_o - Vuv2_o;

            Vuv_e = Valpha_e*dy_e;
            Vuv_o = Valpha_o*dy_o;

            Vuv_e += Vuv2_e*V16;
            Vuv_o += Vuv2_o*V16;

            (out_X + height*out_stride)[Addr_out].interleave() = (Vuv_e, Vuv_o).truncate(4);
        }
    }
}
