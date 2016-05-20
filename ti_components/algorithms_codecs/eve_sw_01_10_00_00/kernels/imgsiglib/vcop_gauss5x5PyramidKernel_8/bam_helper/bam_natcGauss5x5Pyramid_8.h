/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_gauss5x5Pyramid.h
 *
 *  @brief      This header defines interfaces for integrating block average 2x2 into BAM.
 */

#ifndef BAM_GAUSS5x5PYRAMID_NATC_H_
#define BAM_GAUSS5x5PYRAMID_NATC_H_

#include "bam_gauss5x5Pyramid_8.h"

extern BAM_KernelHelperFuncDef gBAM_TI_natcGauss5x5PyramidHelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_natcGauss5x5PyramidExecFunc;

extern BAM_KernelInfo gBAM_TI_natcGauss5x5PyramidKernel;

#endif /* BAM_BLOCK_AVERAGE2x2_H_ */
