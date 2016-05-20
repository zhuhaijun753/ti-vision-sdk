/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_natcBlockSortU32.h
 *
 *  @brief      This header defines interfaces for integrating block average 2x2 into BAM.
 */

#ifndef BAM_BLOCK_NATCBLOCKSORTU32_H_
#define BAM_BLOCK_NATCBLOCKSORTU32_H_

#include "bam_blockSortU32.h"

extern BAM_KernelHelperFuncDef gBAM_TI_natcBlockSortU32HelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_natcBlockSortU32ExecFunc;

extern BAM_KernelInfo gBAM_TI_natcBlockSortU32Kernel;

#endif /* BAM_BLOCK_NATCBLOCKSORTU32_H_ */
