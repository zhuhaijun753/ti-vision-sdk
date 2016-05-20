/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_blockAverage2x2_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating blockAverage2x2 into a BAM graph
 */

#include <stdio.h>
#include <stdlib.h>

#include "evealgframework.h"
#include "bam_blockSortU32_int.h"
#include "merge_sort.h"

/* Function Prototypes */
static BAM_Status BAM_natcBlockSortU32_getMemRecFunc(const void *kernelArgs, BAM_MemRec *internalBlock,
        BAM_MemRec *outBlock, uint8_t *numInternalBlocks, uint8_t *numOutBlocks);

static BAM_Status BAM_natcBlockSortU32_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks)
{
#if !(VCOP_HOST_EMULATION)
    const BAM_BlockSortU32_Args *args = kernelArgs;
#else
    const BAM_BlockSortU32_Args *args = (const BAM_BlockSortU32_Args *)kernelArgs;
#endif
    internalBlock[PARAMS_IDX].size = 2U*MAX_PARAMS;
    internalBlock[OFFSETS_IDX].size= 8U * MAX_FUNC_CALLS * 4U;
    internalBlock[BACKUP_PARAMS_IDX].size = 2U*MAX_PARAMS;
    internalBlock[BACKUP_PARAMS_IDX].space= BAM_MEMSPACE_EXTMEM;
    internalBlock[BACKUP_OFFSETS_IDX].size= 8U * MAX_FUNC_CALLS * 4U;
    internalBlock[BACKUP_OFFSETS_IDX].space= BAM_MEMSPACE_EXTMEM;

    /* The size of the output block should be a quarter of the processing block
     * It is expected that the application must have intialized args->out_stride accordingly whereas the height needs to be derived from args->height
     * */
    outBlock[OUT_IDX].size = args->numElmts * sizeof(uint32_t);

    return BAM_S_SUCCESS;
}

BAM_KernelInfo gBAM_TI_natcBlockSortU32Kernel =
{
        0,                                      /* kernelId */
        sizeof(BAM_BlockSortU32_Context),
        sizeof(BAM_BlockSortU32_Args),
        BAM_EVE_ARP32,                                /* coreType */
        BAM_NODE_COMPUTE,                       /* nodeType */
        NUM_IN_BLOCKS,                          /* 1 */
        NUM_OUT_BLOCKS,                         /* 1 */
        NUM_INTERNAL_BLOCKS                     /* 4 */
};

BAM_KernelHelperFuncDef gBAM_TI_natcBlockSortU32HelperFunc =
{ &BAM_natcBlockSortU32_getMemRecFunc, NULL};

