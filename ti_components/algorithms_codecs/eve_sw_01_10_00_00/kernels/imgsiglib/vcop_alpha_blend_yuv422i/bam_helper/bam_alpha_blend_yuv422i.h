/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_alpha_blend_yuv422i.h
 *
 *  @brief      This header defines interfaces for integrating YUV422 Interleaved
 *              Alpha Blending into BAM.
 */

#ifndef BAM_ALPHA_BLEND_YUV422I_H_
#define BAM_ALPHA_BLEND_YUV422I_H_

typedef struct bam_alpha_blend_yuv422i_args
{
    uint16_t width;
    uint16_t height;
    uint16_t in_img1_stride;
    uint16_t in_img2_stride;
    uint16_t out_stride;
} BAM_Alpha_Blend_YUV422i_Args;

extern BAM_KernelHelperFuncDef gBAM_TI_alphaBlendYUV422iHelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_alphaBlendYUV422iExecFunc;

extern BAM_KernelInfo gBAM_TI_alphaBlendYUV422iKernel;

#define BAM_ALPHA_BLEND_YUV422I_INPUT_PORT_IMG1      (0U)
#define BAM_ALPHA_BLEND_YUV422I_INPUT_PORT_IMG2      (1U)
#define BAM_ALPHA_BLEND_YUV422I_INPUT_PORT_ALPHA     (2U)

#define BAM_ALPHA_BLEND_YUV422I_OUTPUT_PORT          (0U)

#endif /* BAM_ALPHA_BLEND_YUV422I_H_ */
