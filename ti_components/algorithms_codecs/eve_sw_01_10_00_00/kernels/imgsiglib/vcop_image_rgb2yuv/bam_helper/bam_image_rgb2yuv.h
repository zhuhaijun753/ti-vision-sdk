/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_image_rgb2yuv.h
 *
 *  @brief      This file defines functions for integrating rgb2yuv kernels into BAM
 */

/**
 ********************************************************************************
 * @file isp_bam_image_rgb2yuv_Helper_Funcs.h
 *
 * @brief
 *
 * @author Gajanan Ambi(gajanan.ambi@ti.com)
 *
 * @version 0.0 (November 2012) : Base version.
 ********************************************************************************
 */

#ifndef ISP_BAM_IMAGE_RGB2YUV_H_
#define ISP_BAM_IMAGE_RGB2YUV_H_

#define RGB2YUV_OUTPUT_YUYV 0
#define RGB2YUV_OUTPUT_UYVY 1

typedef struct _isp_bam_image_rgb2yuv_args
{
    void           *rgb2yuv_coefs;
    unsigned short blk_width;
    unsigned short blk_height;
    unsigned short input_stride;
    unsigned short output_stride;
    unsigned int   roundingFactor;
    unsigned short shift_val;
    unsigned short outputFormat;
} ISP_BAM_Image_rgb2yuv_Args;

extern BAM_KernelHelperFuncDef gBAM_TI_rgb2yuvHelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_rgb2yuvExecFunc;

extern BAM_KernelInfo gBAM_TI_rgb2yuvKernel;

#define BAM_IMAGE_RGB2YUV_INPUT_PORT_R  0
#define BAM_IMAGE_RGB2YUV_INPUT_PORT_G  1
#define BAM_IMAGE_RGB2YUV_INPUT_PORT_B  2

#define BAM_IMAGE_BAYER2RGB_OUTPUT_PORT_YUV 0
#endif

