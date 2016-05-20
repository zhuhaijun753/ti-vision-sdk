/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
* @file bam_nxn_block_sum_interleaved.h
*
* @brief
*
*
* @version 0.0 (Jan 2014) : Base version.
*/


#ifndef BAM_NXN_BLOCK_SUM_INTERLEAVED_H_
#define BAM_NXN_BLOCK_SUM_INTERLEAVED_H_

#include "bam_common.h"

typedef struct
{
    uint16_t    nValue;
    uint16_t    numBins;
    uint16_t    blockW;
    uint16_t    blockH;
    uint16_t    pitch;
    uint16_t    shiftValue;
} BAM_nxn_block_sum_interleaved_Args;

extern BAM_KernelHelperFuncDef gBAM_TI_nxn_block_sum_interleavedHelperFunc;
extern BAM_KernelExecFuncDef   gBAM_TI_nxn_block_sum_interleavedExecFunc;

extern BAM_KernelInfo gBAM_TI_nxn_block_sum_interleavedKernel;

#define BAM_NXN_BLOCK_SUM_INTERLEAVED_INPUT_PTR_PORT    (0)

#define BAM_NXN_BLOCK_SUM_INTERLEAVED_OUTPUT_PTR1_PORT  (0)
#define BAM_NXN_BLOCK_SUM_INTERLEAVED_OUTPUT_PTR2_PORT  (1)


#endif /* BAM_NXN_BLOCK_SUM_INTERLEAVED_H_ */

