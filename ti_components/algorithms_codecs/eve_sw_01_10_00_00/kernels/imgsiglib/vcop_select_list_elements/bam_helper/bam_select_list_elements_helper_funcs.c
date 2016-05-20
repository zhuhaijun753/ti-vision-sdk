/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_select_list_elements_helper_funcs.c
 *
 *  @brief      This file implements interfaces for integrating select list elements
 *              kernel into BAM.
 */

#include <stdio.h>
#include <stdlib.h>

#include "evealgframework.h"
#include "bam_select_list_elements_int.h"
#include "vcop_select_list_elements_kernel.h" /* compiler should take care of include path */

/* Function Prototypes */
static BAM_Status BAM_Select_list_elements_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks);

static BAM_Status BAM_Select_list_elements_getMemRecFunc(
                      const void *kernelArgs,
                      BAM_MemRec internalBlock[SELECT_LIST_ELEMENTS_INTERNAL_NUM_BLOCK],
                      BAM_MemRec outBlock[BAM_SELECT_LIST_ELEMENTS_NUM_OUTPUT_BLOCKS],
                      uint8_t *numInternalBlocks,
                      uint8_t *numOutBlocks)
{
    const BAM_Select_list_elements_Args * args = ( const BAM_Select_list_elements_Args *)kernelArgs;

#if !VCOP_HOST_EMULATION
    internalBlock[SELECT_LIST_ELEMENTS_INTERNAL_PARAMS_IDX].size = sizeof(uint16_t) * vcop_select_list_elements_param_count();
    internalBlock[SELECT_LIST_ELEMENTS_INTERNAL_PBLOCK_UPDATE_PARAMS_IDX].size = sizeof(uint16_t) *
                                              vcop_select_list_elements_param_block_update_param_count();
#else
    internalBlock[SELECT_LIST_ELEMENTS_INTERNAL_PARAMS_IDX].size = 4U;
    internalBlock[SELECT_LIST_ELEMENTS_INTERNAL_PBLOCK_UPDATE_PARAMS_IDX].size = 4U;
#endif
    internalBlock[SELECT_LIST_ELEMENTS_INTERNAL_PBLOCK_UPDATE_PARAMS_IDX].space = BAM_MEMSPACE_WBUF ;

    internalBlock[SELECT_LIST_ELEMENTS_INTERNAL_SELECTION_MASK_PTR_IDX].size = args->maxSelectionMaxSize * sizeof(uint8_t);
    internalBlock[SELECT_LIST_ELEMENTS_INTERNAL_SELECTION_MASK_PTR_IDX].space = BAM_MEMSPACE_WBUF;
    internalBlock[SELECT_LIST_ELEMENTS_INTERNAL_SELECTION_MASK_PTR_IDX].attrs.memAttrs = BAM_MEMATTRS_CONST;

    outBlock[BAM_SELECT_LIST_ELEMENTS_OUTPUT_LIST_PORT].size = args->maxListChunkSize * sizeof(uint32_t);
    outBlock[BAM_SELECT_LIST_ELEMENTS_OUTPUT_LIST_PORT].space = BAM_MEMSPACE_IBUFHA;

    outBlock[BAM_SELECT_LIST_ELEMENTS_OUTPUT_LIST_SIZE_PORT].size = VCOP_SIMD_WIDTH * sizeof(uint16_t);
    outBlock[BAM_SELECT_LIST_ELEMENTS_OUTPUT_LIST_SIZE_PORT].space = BAM_MEMSPACE_IBUFHA;

    return BAM_S_SUCCESS;
}

BAM_KernelInfo gBAM_TI_selecListElementsKernel =
{
    0,                                      /* kernelId */
    sizeof(BAM_Select_list_elements_Context),
    sizeof(BAM_Select_list_elements_Args),
    BAM_EVE,                                /* coreType */
    BAM_NODE_COMPUTE,                       /* nodeType */
    BAM_SELECT_LIST_ELEMENTS_NUM_INPUT_BLOCKS,                          /* 1 */
    BAM_SELECT_LIST_ELEMENTS_NUM_OUTPUT_BLOCKS,                         /* 2 */
    SELECT_LIST_ELEMENTS_INTERNAL_NUM_BLOCK                     /* 3 */
};

BAM_KernelHelperFuncDef gBAM_TI_selecListElementsHelperFunc =
{ &BAM_Select_list_elements_getMemRecFunc, NULL};

