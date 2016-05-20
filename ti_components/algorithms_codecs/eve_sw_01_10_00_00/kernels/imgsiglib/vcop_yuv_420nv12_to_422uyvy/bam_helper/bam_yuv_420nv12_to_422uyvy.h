/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_yuv_420nv12_to_422uyvy.h
 *
 *  @brief      This header defines interfaces for integrating YUV420 NV12
 *              to YUV422 UYVY format conversion into BAM.
 */

#ifndef BAM_YUV_420NV12_TO_422UYVY_H_
#define BAM_YUV_420NV12_TO_422UYVY_H_

typedef struct bam_yuv_420nv12_to_422uyvy_args
{
    uint16_t width;
    uint16_t height;
    uint16_t in_stride;
    uint16_t out_stride;
} BAM_Yuv_420nv12_to_422uyvy_Args;

extern BAM_KernelHelperFuncDef gBAM_TI_yuv420nv12_to_422uyvyHelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_yuv420nv12_to_422uyvyExecFunc;

extern BAM_KernelInfo gBAM_TI_yuv420nv12_to_422uyvyKernel;

#define BAM_YUV_420NV12_TO_422UYVY_INPUT_PORT_IMG       (0U)
#define BAM_YUV_420NV12_TO_422UYVY_OUTPUT_PORT          (0U)

#endif /* BAM_YUV_420NV12_TO_422UYVY_H_ */
