/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
* @file bam_image_rgb2srgb.h
*
* @brief
*
* @author Gajanan Ambi(gajanan.ambi@ti.com)
*
* @version 0.0 (November 2012) : Base version.
*/

#ifndef ISP_BAM_IMAGE_RGB2SRGB_H_
#define ISP_BAM_IMAGE_RGB2SRGB_H_

typedef struct _isp_bam_image_rgb2srgb_args
{
    void           *rgb2srgb_coefs;
    unsigned short blk_width;
    unsigned short blk_height;
    unsigned short input_stride;
    unsigned short output_stride;
} ISP_BAM_Image_rgb2srgb_Args;

extern BAM_KernelHelperFuncDef gBAM_TI_rgb2srgbHelperFunc;
extern BAM_KernelExecFuncDef   gBAM_TI_rgb2srgbExecFunc;

extern BAM_KernelInfo gBAM_TI_rgb2srgbKernel;

#define BAM_IMAGE_RGB2sRGB_INPUT_PORT_R 0
#define BAM_IMAGE_RGB2sRGB_INPUT_PORT_G 1
#define BAM_IMAGE_RGB2sRGB_INPUT_PORT_B 2

#define BAM_IMAGE_RGB2sRGB_OUTPUT_PORT_R 0
#define BAM_IMAGE_RGB2sRGB_OUTPUT_PORT_G 1
#define BAM_IMAGE_RGB2sRGB_OUTPUT_PORT_B 2

#endif /* ISP_BAM_IMAGE_RGB2SRGB_H_ */

