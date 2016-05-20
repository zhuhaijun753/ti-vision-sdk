/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_image_pyramid_u8.h
 *
 *  @brief      This header defines interfaces for integrating one level puramid function into BAM
 */

#ifndef BAM_IMAGE_DEINTERLEAVE_UCHAR_H_
#define BAM_IMAGE_DEINTERLEAVE_UCHAR_H_

typedef struct _bam_image_deinterleave_u8_args
{
    unsigned short inCols;
    unsigned short inRows;
} BAM_Image_Deinterleave_U8_Args;

extern BAM_KernelHelperFuncDef gBAM_TI_deinterleaveu8HelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_deinterleaveu8ExecFunc;

extern BAM_KernelInfo gBAM_TI_deinterleaveu8Kernel;

#define BAM_IMAGE_DEINTERLEAVE_U8_INPUT_PORT            0
#define BAM_IMAGE_DEINTERLEAVE_U8_OUTPUT_PORT1          0
#define BAM_IMAGE_DEINTERLEAVE_U8_OUTPUT_PORT2          1

#endif /* BAMIMAGEPYRAMIDONELEVEL_H_ */
