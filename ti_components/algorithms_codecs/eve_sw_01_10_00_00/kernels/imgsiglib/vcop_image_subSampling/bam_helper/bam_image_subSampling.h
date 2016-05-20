/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
* @file bam_image_subSampling.h
*
* @brief
*
* @author Gajanan Ambi(gajanan.ambi@ti.com)
*
* @version 0.0 (November 2012) : Base version.
*/

#ifndef ISP_BAM_IMAGE_SUB_SAMPLING_H_
#define ISP_BAM_IMAGE_SUB_SAMPLING_H_

typedef struct _isp_bam_image_subsampling_args
{
    unsigned short blk_width;
    unsigned short blk_height;
    unsigned short input_stride;
    unsigned short output_stride;
    unsigned short subSample_X;
    unsigned short subSample_Y;
    unsigned short numOfSample;
} ISP_BAM_Image_subSampling_Args;

extern BAM_KernelHelperFuncDef gBAM_TI_subSamplingHelperFunc;
extern BAM_KernelExecFuncDef   gBAM_TI_subSamplingExecFunc;

extern BAM_KernelInfo gBAM_TI_subSamplingKernel;

#define BAM_IMAGE_SUB_SAMPLING_INPUT_PORT  0

#define BAM_IMAGE_SUB_SAMPLING_OUTPUT_PORT 0

#endif

