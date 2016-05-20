/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_blockAverage2x2.h
 *
 *  @brief      This header defines interfaces for integrating block average 2x2 into BAM.
 */

#ifndef BAM_BLOCK_AVERAGE2x2_H_
#define BAM_BLOCK_AVERAGE2x2_H_

#include <stdint.h>
#include "evealgframework.h"

typedef struct 
{
    uint16_t width; /* Must be multiple fo 16 */
    uint16_t height; /* Must be multiple fo 2 */
    uint16_t in_stride;
    uint16_t out_stride;
} BAM_BlockAverage2x2_Args;

extern BAM_KernelHelperFuncDef gBAM_TI_blockAverage2x2HelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_blockAverage2x2ExecFunc;

extern BAM_KernelInfo gBAM_TI_blockAverage2x2Kernel;

#define BAM_BLOCKAVERAGE2x2_INPUT_PORT      0
#define BAM_BLOCKAVERAGE2x2_OUTPUT_PORT     0

#endif /* BAM_BLOCK_AVERAGE2x2_H_ */
