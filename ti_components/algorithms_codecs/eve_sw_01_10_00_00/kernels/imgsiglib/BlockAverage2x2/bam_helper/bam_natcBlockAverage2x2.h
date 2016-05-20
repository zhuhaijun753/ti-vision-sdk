/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_blockAverage2x2.h
 *
 *  @brief      This header defines interfaces for integrating block average 2x2 into BAM.
 */

#ifndef BAM_BLOCK_NATCAVERAGE2x2_H_
#define BAM_BLOCK_NATCAVERAGE2x2_H_

#include "bam_blockAverage2x2.h"

extern BAM_KernelHelperFuncDef gBAM_TI_natcBlockAverage2x2HelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_natcBlockAverage2x2ExecFunc;

extern BAM_KernelInfo gBAM_TI_natcBlockAverage2x2Kernel;

#endif /* BAM_BLOCK_AVERAGE2x2_H_ */
