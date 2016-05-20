/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_remap_merge.h
 *
 *  @brief     This header defines interfaces for integrating the combination of
 *                Remap, Format Convert and Merge kernels into BAM.
 */

#ifndef BAM_REMAP_MERGE_H_
#define BAM_REMAP_MERGE_H_

#include "remap.h"
#include "remap_common.h"
#include "bam_remap.h"                        /* KERNEL NODE  */
#include "bam_memcpy.h"                       /* KERNEL NODE  */
#include "bam_alpha_blend_yuv420nv12.h"       /* KERNEL NODE  */
#include "bam_alpha_blend_yuv422i.h"          /* KERNEL NODE  */
#include "bam_yuv_420nv12_to_422uyvy.h"       /* KERNEL NODE  */
#include "bam_yuv_422uyvy_to_420nv12.h"       /* KERNEL NODE  */


/** ========================================================
 *  @name   BAM_Remap_Merge_Args
 *
 *  @desc   This structure specifies the properties needed for configuring DMA
 *
 *  @field remapKernelArgs
 *          parameters to configure Remap kernel
 *
 *  @field enableMerge
 *          enable or disable Alpha blending kernel
 *
 *  @field dstFormat
 *          Format of output
 *
 *  @field memcpyKernelArgs
 *          parameters to configure Memcpy kernel
 *
 *  @field formatConvertKernelArgs
 *          parameters to configure Format Convert kernel
 *
 *  @field alphaBlendKernelArgs
 *          parameters to configure Alpha Blend kernel
 *  ===============================================================
 */
typedef struct bam_remap_merge_args
{
    BAM_Remap_Args                    remapKernelArgs;
    uint8_t                           enableMerge;
    Format                            dstFormat;
    BAM_Memcpy_Args                   memcpyKernelArgs;
    BAM_Yuv_420nv12_to_422uyvy_Args   formatConvertKernelArgs;
    BAM_Alpha_Blend_YUV420nv12_Args   alphaBlendKernelArgs;
} BAM_Remap_Merge_Args;


extern BAM_KernelHelperFuncDef gBAM_TI_remapMergeHelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_remapMergeExecFunc;

extern BAM_KernelInfo gBAM_TI_remapMergeKernel;

#define BAM_REMAP_MERGE_INPUT_PORT_IMAGE_BLOCK     (0U)
#define BAM_REMAP_MERGE_INPUT_PORT_LUT             (1U)
#define BAM_REMAP_MERGE_INPUT_PORT_MERGE_BLOCK     (2U)
#define BAM_REMAP_MERGE_INPUT_PORT_ALPHA_BLOCK     (3U)

#define BAM_REMAP_MERGE_OUTPUT_PORT                (0U)


#endif /* BAM_REMAP_MERGE_H_ */

