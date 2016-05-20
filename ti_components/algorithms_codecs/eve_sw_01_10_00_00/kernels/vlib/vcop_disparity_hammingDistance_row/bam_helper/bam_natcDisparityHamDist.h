/*==========================================================================*/
/*      Copyright (C) 2009-2014 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_natcDisparityHamDist.h
 *
 *  @brief      This header defines interfaces for integrating hammind distance based disparity calculation  kernel
 *              into BAM.
 */

#ifndef BAM_NATCDISPARITY_HAMDIST_H_
#define BAM_NATCDISPARITY_HAMDIST_H_

#include "bam_disparityHamDist.h"


extern BAM_KernelHelperFuncDef gBAM_TI_natcDisparityHamDist_HelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_natcDisparityHamDist_ExecFunc;

extern BAM_KernelInfo gBAM_TI_natcDisparityHamDist_Kernel;


#endif /* BAM_NATCDISPARITY_HAMDIST_H_ */

