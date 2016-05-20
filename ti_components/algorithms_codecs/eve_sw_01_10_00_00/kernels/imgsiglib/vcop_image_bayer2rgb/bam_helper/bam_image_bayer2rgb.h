/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 * @file isp_bam_image_bayer2rgb_Helper_Funcs.h
 *
 * @brief
 *
 * @author Gajanan Ambi(gajanan.ambi@ti.com)
 *
 * @version 0.0 (November 2012) : Base version.
 */

#ifndef ISP_BAM_IMAGE_BAYER2RGB_H_
#define ISP_BAM_IMAGE_BAYER2RGB_H_

typedef struct _isp_bam_image_bayer2rgb_args
{
    unsigned short blk_width;
    unsigned short blk_height;
    unsigned short input_stride;
    unsigned short output_stride;
    unsigned char  bayerFormat;
} ISP_BAM_Image_Bayer2rgb_Args;

extern BAM_KernelHelperFuncDef gBAM_TI_bayer2rgbHelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_bayer2rgbExecFunc;

extern BAM_KernelInfo gBAM_TI_bayer2rgbKernel;

#define BAM_IMAGE_BAYER2RGB_INPUT_PORT  0

#define BAM_IMAGE_BAYER2RGB_OUTPUT_PORT_R 0
#define BAM_IMAGE_BAYER2RGB_OUTPUT_PORT_G 1
#define BAM_IMAGE_BAYER2RGB_OUTPUT_PORT_B 2

#endif /* ISP_BAM_IMAGE_BAYER2RGB_H_ */

