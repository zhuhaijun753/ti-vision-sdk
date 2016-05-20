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

#ifndef ISP_BAM_IMAGE_NATCGAMMA_CORRECTION_H_
#define ISP_BAM_IMAGE_NATCGAMMA_CORRECTION_H_

#include "bam_image_gammaCorrection.h"

extern BAM_KernelHelperFuncDef gBAM_TI_natcGammaCorrectionHelperFunc;
extern BAM_KernelExecFuncDef   gBAM_TI_natcGammaCorrectionExecFunc;

extern BAM_KernelInfo gBAM_TI_natcGammaCorrectionKernel;

#endif /* ISP_BAM_IMAGE_GAMMA_CORRECTION_H_ */

