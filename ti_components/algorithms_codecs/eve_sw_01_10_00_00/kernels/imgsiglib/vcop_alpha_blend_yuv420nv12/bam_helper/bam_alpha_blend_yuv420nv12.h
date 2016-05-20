/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_alpha_blend_yuv420nv12.h
 *
 *  @brief      This header defines interfaces for integrating YUV420 NV12
 *              Alpha Blending into BAM.
 */

#ifndef BAM_ALPHA_BLEND_YUV420NV12_H_
#define BAM_ALPHA_BLEND_YUV420NV12_H_

typedef struct bam_alpha_blend_yuv420nv12_args
{
    uint16_t width;
    uint16_t height;
    uint16_t in_img1_stride;
    uint16_t in_img2_stride;
    uint16_t out_stride;
} BAM_Alpha_Blend_YUV420nv12_Args;

extern BAM_KernelHelperFuncDef gBAM_TI_alphaBlendYUV420nv12HelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_alphaBlendYUV420nv12ExecFunc;

extern BAM_KernelInfo gBAM_TI_alphaBlendYUV420nv12Kernel;

#define BAM_ALPHA_BLEND_YUV420NV12_INPUT_PORT_IMG1      (0U)
#define BAM_ALPHA_BLEND_YUV420NV12_INPUT_PORT_IMG2      (1U)
#define BAM_ALPHA_BLEND_YUV420NV12_INPUT_PORT_ALPHA     (2U)

#define BAM_ALPHA_BLEND_YUV420NV12_OUTPUT_PORT          (0U)

#endif /* BAM_ALPHA_BLEND_YUV420NV12_H_ */
