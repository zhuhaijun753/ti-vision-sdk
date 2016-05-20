/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_binary_masking_int.h
 *
 *  @brief      This header defines internal structures for binary masking
 *               kernel.
 */

#ifndef BAM_BINARY_MASKING_INT_H_
#define BAM_BINARY_MASKING_INT_H_

#include <stdint.h>
#include <vcop.h>

#include "evealgframework.h"
#include "bam_binary_masking.h"

typedef enum
{
  BINARY_MASKING_INTERNAL_PARAMS_IDX = 0,
  BINARY_MASKING_INTERNAL_NUM_BLOCK
} eBAM_BINARY_MASKING_INTERNAL_BLOCKS;

typedef struct
{
    /* Must always follow this order: pInternalBlock[], pInBlock[], pOutputBlock[], args */
    void *pInternalBlock[BINARY_MASKING_INTERNAL_NUM_BLOCK];
    void *pInBlock[BAM_BINARY_MASKING_NUM_INPUT_BLOCKS];
    void *pOutBlock[BAM_BINARY_MASKING_NUM_OUTPUT_BLOCKS];
    BAM_BinaryMasking_Args     kernelInitArgs;
    BAM_BinaryMasking_CtrlArgs kernelCtrlArgs;
} BAM_BinaryMasking_Context;

#endif /* BAM_BINARY_MASKING_INT_H_*/

