/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
* @file bam_orientation_binning.h
*
* @brief
*
*
* @version 0.0 (Jan 2014) : Base version.
*/


#ifndef BAM_ORIENTATION_BINNING_H_
#define BAM_ORIENTATION_BINNING_H_

#include "bam_common.h"


typedef struct
{
    uint16_t numBins;
    uint16_t pitch;
    uint16_t blockW;
    uint16_t blockH;
} BAM_orientation_binning_Args;

extern BAM_KernelHelperFuncDef gBAM_TI_orientation_binningHelperFunc;
extern BAM_KernelExecFuncDef   gBAM_TI_orientation_binningExecFunc;

extern BAM_KernelInfo gBAM_TI_orientation_binningKernel;

#define BAM_ORIENTATION_BINNING_INPUT_GRADX_PORT     (0)
#define BAM_ORIENTATION_BINNING_INPUT_GRADY_PORT    (1)

#define BAM_ORIENTATION_BINNING_OUTPUT_OUTBIN_VEC    (0)

#endif /* BAM_ORIENTATION_BINNING_H_ */

