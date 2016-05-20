/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*                                                                          */
/*    @file : vcop_alpha_blend_yuv422i_kernel.k                             */
/*                                                                          */
/*    @brief : This routine accepts two YUV 422 interleaved images of size  */
/*             width by height and with a stirde of in_stride. An frame of  */
/*             alpha values for each Y pixel is also provided. The kernel   */
/*             outputs a YUV 422 interleaved image that is an alpha         */
/*             belended version of the two input images.                    */
/*                                                                          */
/*     The recommended banks for each of the buffers is captured as A/B/C   */
/*     as part of the buffer pointer. A/B/C can either be IMBUF High,       */
/*     IMBUF low or WMEM. In case of don't care it is marked as X.          */
/*                                                                          */
/*    USAGE:                                                                */
/*    This routine is C-callable and can be called as:                      */
/*                                                                          */
/*    void vcop_alpha_blend_yuv422i                                         */
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
/*    in_img1_X        : YUV 422 interleaved Image 1                        */
/*    in_img2_X        : YUV 422 interleaved Image 2                        */
/*    alphaFrame_X     : Alpha values for Y pixels, ranges from [0-16]      */
/*    out_X            : Alpha blended output image (YUV 422 interleaved)   */
/*    width          : Width of the input/output images                     */
/*    height         : Height of the input/output images                    */
/*    in_img1_stride : Stride for the input image 1                         */
/*    in_img2_stride : Stride for the input image 2                         */
/*    out_stride     : Stride of the output image                           */
/*                                                                          */
/*    Returns     :  None or void.                                          */
/*                                                                          */
/*    ASSUMPTIONS:                                                          */
/*      Alpha value ranges from 0 to 16.                                    */
/*                                                                          */
/*    PERFORMANCE MEASUREMENT:                                              */
/*      0.5 cycle/pix execution time + 64 cycle VCOP overheads              */
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

void vcop_alpha_blend_yuv422i
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

    V16 = 16;

    for(int I1 = 0; I1 < height; I1++) {
        for(int I2 = 0; I2 < (2*width + VCOP_2SIMD_WIDTH - 1)/VCOP_2SIMD_WIDTH; I2++) {
            __vector Vy1, Vy2, Vuv1, Vuv2, Vy, Vuv;
            __vector Valpha;
            __vector dy, duv;
            __agen Addr_in1, Addr_in2, Addr_alpha, Addr_out;

            Addr_in1 = I1*in_img1_stride + I2*VCOP_2SIMD_WIDTH;
            Addr_in2 = I1*in_img2_stride + I2*VCOP_2SIMD_WIDTH;
            Addr_alpha = I1*width + I2*VCOP_SIMD_WIDTH;
            Addr_out = I1*out_stride + I2*VCOP_2SIMD_WIDTH;

            (Vuv1, Vy1) =  in_img1_X[Addr_in1].deinterleave();
            (Vuv2, Vy2) =  in_img2_X[Addr_in2].deinterleave();
            Valpha = alphaFrame_X[Addr_alpha];

            dy = Vy1 - Vy2;
            duv = Vuv1 - Vuv2;

            Vuv = Valpha*duv;
            Vy = Valpha*dy;

            Vuv += Vuv2*V16;
            Vy += Vy2*V16;

            out_X[Addr_out].interleave() = (Vuv, Vy).truncate(4);
        }
    }
}
