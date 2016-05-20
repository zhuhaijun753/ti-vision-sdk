/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_remap_int.h
 *
 *  @brief      This header defines internal structures for remap kernel
 *              into BAM.
 */
#ifndef BAM_MEMCPY_INT_H_
#define BAM_MEMCPY_INT_H_

#include <stdint.h>
#include <vcop.h>

#include "evealgframework.h"

#include "bam_memcpy.h"

#define MEMCPY_NUM_IN_BLOCKS        (1U)
#define MEMCPY_NUM_OUT_BLOCKS       (1U)
#define MEMCPY_NUM_INTERNAL_BLOCKS  (1U)

/* Input Blocks Pointer Indexes */
#define MEMCPY_INPUT_BLOCK_PTR_IDX  (0U)

/* Output Blocks Pointer Indexes */
#define MEMCPY_OUTPUT_BLOCK_PTR_IDX (0U)

/* Internal Blocks Pointer Indexes */
#define MEMCPY_PBLOCK_PTR_IDX       (0U)


typedef struct bam_memcpy_context
{
    /* Must always follow this order: pInternalBlock[], pInBlock[], pOutputBlock[], args */
    void *pInternalBlock[MEMCPY_NUM_INTERNAL_BLOCKS];
    void *pInBlock[MEMCPY_NUM_IN_BLOCKS];
    void *pOutBlock[MEMCPY_NUM_OUT_BLOCKS];
    BAM_Memcpy_Args kernelArgs;
} BAM_Memcpy_Context;

#endif /* BAM_MEMCPY_INT_H_*/
