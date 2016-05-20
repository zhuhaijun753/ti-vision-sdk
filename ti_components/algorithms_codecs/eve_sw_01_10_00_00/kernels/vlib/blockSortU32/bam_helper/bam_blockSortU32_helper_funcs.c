/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_blockSortU32_helper_funcs.c
 *
 *  @brief      This file defines interfaces for integrating blockSortU32 into a BAM graph
 */

#include <stdio.h>
#include <stdlib.h>

#include "evealgframework.h"
#include "bam_blockSortU32_int.h"
#include "merge_sort.h"

/* Function Prototypes */
static BAM_Status BAM_blockSortU32_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks);

static BAM_Status BAM_blockSortU32_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks)
{
#if !(VCOP_HOST_EMULATION)
    const BAM_BlockSortU32_Args *args = kernelArgs;
#else
    const BAM_BlockSortU32_Args *args = (const BAM_BlockSortU32_Args *)kernelArgs;
#endif
    internalBlock[PARAMS_IDX].size = 2u*MAX_PARAMS;
    internalBlock[OFFSETS_IDX].size= 8u * MAX_FUNC_CALLS * 4u;
    internalBlock[BACKUP_PARAMS_IDX].size = 2u*MAX_PARAMS;
    internalBlock[BACKUP_PARAMS_IDX].space= BAM_MEMSPACE_EXTMEM;
    internalBlock[BACKUP_OFFSETS_IDX].size= 8u * MAX_FUNC_CALLS * 4u;
    internalBlock[BACKUP_OFFSETS_IDX].space= BAM_MEMSPACE_EXTMEM;

    outBlock[OUT_IDX].size = args->numElmts * sizeof(uint32_t);

    return BAM_S_SUCCESS;
}

BAM_KernelInfo gBAM_TI_blockSortU32Kernel =
{
        0,                                      /* kernelId */
        sizeof(BAM_BlockSortU32_Context),
        sizeof(BAM_BlockSortU32_Args),
        BAM_EVE,                                /* coreType */
        BAM_NODE_COMPUTE,                       /* nodeType */
        NUM_IN_BLOCKS,                          /* 1 */
        NUM_OUT_BLOCKS,                         /* 1 */
        NUM_INTERNAL_BLOCKS                     /* 4 */
};

BAM_KernelHelperFuncDef gBAM_TI_blockSortU32HelperFunc =
{ &BAM_blockSortU32_getMemRecFunc, NULL};

