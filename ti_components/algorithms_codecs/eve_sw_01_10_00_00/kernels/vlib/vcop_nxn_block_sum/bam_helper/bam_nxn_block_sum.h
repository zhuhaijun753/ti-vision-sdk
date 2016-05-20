/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
* @file bam_nxn_block_sum.h
*
* @brief
*
*
* @version 0.0 (Jan 2014) : Base version.
*/


#ifndef BAM_NXN_BLOCK_SUM_H_
#define BAM_NXN_BLOCK_SUM_H_

#include "bam_common.h"


typedef struct
{
    uint16_t    nValue;
    uint16_t    blockW;
    uint16_t    blockH;
    uint16_t    pitch1;
    uint16_t    pitch2;
    uint8_t     inputSize; /* Size of input data in number of bytes */
} BAM_nxn_block_sum_Args;

extern BAM_KernelHelperFuncDef gBAM_TI_nxn_block_sumHelperFunc;
extern BAM_KernelExecFuncDef   gBAM_TI_nxn_block_sumExecFunc;

extern BAM_KernelInfo gBAM_TI_nxn_block_sumKernel;

#define BAM_NXN_BLOCK_SUM_INPUT_PTR1_PORT    (0)
#define BAM_NXN_BLOCK_SUM_INPUT_PTR2_PORT  (1)

#define BAM_NXN_BLOCK_SUM_OUTPUT_PTR1_PORT  (0)
#define BAM_NXN_BLOCK_SUM_OUTPUT_PTR2_PORT  (1)


#endif /* BAM_NXN_BLOCK_SUM_H_ */

