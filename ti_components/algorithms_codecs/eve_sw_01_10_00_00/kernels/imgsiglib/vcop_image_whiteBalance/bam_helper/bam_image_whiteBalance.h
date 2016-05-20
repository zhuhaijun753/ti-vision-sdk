/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
* @file bam_image_whiteBalance.h
*
* @brief
*
* @author Gajanan Ambi(gajanan.ambi@ti.com)
*
* @version 0.0 (November 2012) : Base version.
*/

#ifndef ISP_BAM_IMAGE_WHITE_BALANCE_H_
#define ISP_BAM_IMAGE_WHITE_BALANCE_H_

typedef struct _isp_bam_image_whitebalance_args
{
    unsigned short blk_width;
    unsigned short blk_height;
    unsigned short input_stride;
    unsigned short output_stride;
    unsigned int   gain_factor_R;
    unsigned int   gain_factor_Gb;
    unsigned int   gain_factor_Gr;
    unsigned int   gain_factor_B;
    unsigned int   shift_val;
    unsigned char bayerFormat;
} ISP_BAM_Image_whiteBalance_Args;

extern BAM_KernelHelperFuncDef gBAM_TI_whiteBalanceHelperFunc;
extern BAM_KernelExecFuncDef   gBAM_TI_whiteBalanceExecFunc;

extern BAM_KernelInfo gBAM_TI_whiteBalanceKernel;

#define BAM_IMAGE_WB_INPUT_PORT  0

#define BAM_IMAGE_WB_OUTPUT_PORT 0

#endif /* BAMIMAGEPYRAMIDONELEVEL_H_ */

