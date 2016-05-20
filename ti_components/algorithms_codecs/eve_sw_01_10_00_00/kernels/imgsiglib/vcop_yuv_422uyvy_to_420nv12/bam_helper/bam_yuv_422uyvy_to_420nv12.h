/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_yuv_422uyvy_to_420nv12.h
 *
 *  @brief      This header defines interfaces for integrating YUV422 UYVY
 *              to YUV420 NV12 format conversion into BAM.
 */

#ifndef BAM_YUV_422UYVY_TO_420NV12_H_
#define BAM_YUV_422UYVY_TO_420NV12_H_

typedef struct bam_yuv_422uyvy_to_420nv12_args
{
    uint16_t width;
    uint16_t height;
    uint16_t in_stride;
    uint16_t out_stride;
} BAM_Yuv_422uyvy_to_420nv12_Args;

extern BAM_KernelHelperFuncDef gBAM_TI_yuv422uyvy_to_420nv12HelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_yuv422uyvy_to_420nv12ExecFunc;

extern BAM_KernelInfo gBAM_TI_yuv422uyvy_to_420nv12Kernel;

#define BAM_YUV_422UYVY_TO_420NV12_INPUT_PORT_IMG       (0U)
#define BAM_YUV_422UYVY_TO_420NV12_OUTPUT_PORT          (0U)

#endif /* BAM_YUV_422UYVY_TO_420NV12_H_ */
