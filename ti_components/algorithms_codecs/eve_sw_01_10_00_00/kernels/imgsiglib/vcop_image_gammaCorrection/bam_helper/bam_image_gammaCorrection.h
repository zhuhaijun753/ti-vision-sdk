/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
* @file bam_image_gammaCorrection.h
*
* @brief
*
* @author Gajanan Ambi(gajanan.ambi@ti.com)
*
* @version 0.0 (November 2012) : Base version.
*/

#define LUT_1_SIZE   (1024 *2) /* Each elememt is of short type*/
#define NUM_OF_LUT   (8)
#define LUT_N_SIZE   (LUT_1_SIZE * NUM_OF_LUT)

#ifndef ISP_BAM_IMAGE_GAMMA_CORRECTION_H_
#define ISP_BAM_IMAGE_GAMMA_CORRECTION_H_

typedef struct _isp_bam_image_gammacorrection_args
{
    void           *pLUT;
    unsigned short blk_width;
    unsigned short blk_height;
    unsigned short input_stride;
    unsigned short output_stride;
} ISP_BAM_Image_gammaCorrection_Args;

extern BAM_KernelHelperFuncDef gBAM_TI_gammaCorrectionHelperFunc;
extern BAM_KernelExecFuncDef   gBAM_TI_gammaCorrectionExecFunc;

extern BAM_KernelInfo gBAM_TI_gammaCorrectionKernel;

#define BAM_IMAGE_GAMMA_CORRECTION_INPUT_PORT_R 0
#define BAM_IMAGE_GAMMA_CORRECTION_INPUT_PORT_G 1
#define BAM_IMAGE_GAMMA_CORRECTION_INPUT_PORT_B 2

#define BAM_IMAGE_GAMMA_CORRECTION_OUTPUT_PORT_R 0
#define BAM_IMAGE_GAMMA_CORRECTION_OUTPUT_PORT_G 1
#define BAM_IMAGE_GAMMA_CORRECTION_OUTPUT_PORT_B 2

#endif /* ISP_BAM_IMAGE_GAMMA_CORRECTION_H_ */

