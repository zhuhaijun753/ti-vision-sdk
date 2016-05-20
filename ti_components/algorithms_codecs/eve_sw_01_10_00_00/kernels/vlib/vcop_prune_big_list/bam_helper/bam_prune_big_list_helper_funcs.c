/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_prune_big_list_exec_funcs.c
 *  @version 0.1 (Sept 2014) : Updated to add predication based on threshold
 *  @brief      This file defines interfaces for integrating prune
 *              big list function into BAM
 */

#include <stdio.h>
#include <stdlib.h>

#include "evealgframework.h"
#include "bam_prune_big_list_int.h"
#include "vcop_prune_big_list_kernel.h" /* compiler should take care of include path */

/* Function Prototypes */
static BAM_Status BAM_Prune_Big_List_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks);

static BAM_Status BAM_Prune_Big_List_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks)
{
    const BAM_Prune_Big_List_Args *args = (const BAM_Prune_Big_List_Args *) kernelArgs;

#if (!VCOP_HOST_EMULATION)
    internalBlock[PARAMS_IDX].size = 2U*vcop_prune_big_list_param_count();
#else
    /* This field could be any non-zero number for host emulation */
    internalBlock[PARAMS_IDX].size = 4U;
#endif
    
    outBlock[OUT_LIST_IDX].size = (args->maxFeatures) * sizeof(uint32_t);  /* Output is a list of bestN integers */
    outBlock[OUT_LIST_IDX].space = BAM_MEMSPACE_IBUFLA;

    outBlock[OUT_LIST_SIZE].size = 4U*8U; /* To store the count of non-bestN values */
    outBlock[OUT_LIST_SIZE].space = BAM_MEMSPACE_IBUFHA; 

    return BAM_S_SUCCESS;
}

BAM_KernelInfo gBAM_TI_prune_big_listKernel =
{
    0,                                      /* kernelId */
    sizeof(BAM_Prune_Big_List_Context),
    sizeof(BAM_Prune_Big_List_Args),
    BAM_EVE,                                /* coreType */
    BAM_NODE_COMPUTE,                       /* nodeType */
    NUM_IN_BLOCKS,                          /* 2 */
    NUM_OUT_BLOCKS,                         /* 1 */
    NUM_INTERNAL_BLOCKS                     /* 1 */
};

BAM_KernelHelperFuncDef gBAM_TI_prune_big_listHelperFunc =
{ &BAM_Prune_Big_List_getMemRecFunc, NULL};
