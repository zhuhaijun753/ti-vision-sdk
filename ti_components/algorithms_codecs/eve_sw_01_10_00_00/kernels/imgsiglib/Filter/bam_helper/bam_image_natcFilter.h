/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 ********************************************************************************
 * @file:      bam_image_filter.h
 *
 * @brief:    This file defines functions for integrating filter kernels into BAM
 *
 * @author: Gajanan Ambi(gajanan.ambi@ti.com)
 *
 * @version: 0.0 (Feb 2013) : Base version.
 ********************************************************************************
 */

#ifndef BAM_IMAGE_NATCFILTER_H_
#define BAM_IMAGE_NATCFILTER_H_

#include "bam_image_filter.h"

extern BAM_KernelHelperFuncDef gBAM_TI_natcFilterHelperFunc;
extern BAM_KernelExecFuncDef   gBAM_TI_natcFilterExecFunc;

extern BAM_KernelInfo gBAM_TI_natcFilterKernel;

#endif

