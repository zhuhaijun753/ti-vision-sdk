/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_image_pyramid_one_level_uv_u8.h
 *
 *  @brief      This header defines interfaces for integrating one level UV puramid function into BAM
 */

#ifndef BAM_IMAGE_PYRAMID_ONE_LEVEL_USHORT_H_
#define BAM_IMAGE_PYRAMID_ONE_LEVEL_USHORT_H_

typedef struct _bam_image_pyramid_uv_u8_args
{
    unsigned short inCols;
    unsigned short inRows;
} BAM_Image_Pyramid_UV_U8_Args;

extern BAM_KernelHelperFuncDef gBAM_TI_downsampleuvu8HelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_downsampleuvu8ExecFunc;

extern BAM_KernelInfo gBAM_TI_downsampleuvu8Kernel;

#define BAM_IMAGE_PYRAMID_UV_U8_INPUT_PORT  0
#define BAM_IMAGE_PYRAMID_UV_U8_OUTPUT_PORT 0

#endif /* BAMIMAGEPYRAMIDONELEVEL_H_ */
