/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_generateList_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating generateList into a BAM graph
 */

#include <stdio.h>
#include <stdlib.h>

#include "evealgframework.h"
#include "bam_generateList_int.h"
#include "vcop_generateList_kernel.h"


/* Function Prototypes */
static BAM_Status BAM_generateList_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks);

static BAM_Status BAM_generateList_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks)
{

#if !(VCOP_HOST_EMULATION)
    const BAM_GenerateList_Args *args = kernelArgs;

    internalBlock[GENERATELIST_PARAMS_IDX].size = 2u*vcop_generateList_param_count();
    internalBlock[UPDATE_PARAMS_IDX].size = 2u*vcop_updateGenerateList_param_count();
    internalBlock[COPY_XY_PARAMS_IDX].size = 2u * vcop_copyListToOutBuff_param_count();
#else
    const BAM_GenerateList_Args *args = (const BAM_GenerateList_Args *)kernelArgs;

    internalBlock[GENERATELIST_PARAMS_IDX].size = 4u;
    internalBlock[UPDATE_PARAMS_IDX].size       = 4u;
    internalBlock[COPY_XY_PARAMS_IDX].size        = 4u;
#endif
    internalBlock[VARIABLES_IDX].size = (8u*sizeof(uint8_t)) /*endRowPadVal*/
            + (sizeof(uint16_t)*ALIGN_SIMD(args->width)) + (sizeof(uint16_t)*args->height) /* xVal, yVal */
            + (2u*sizeof(uint16_t)) /* blockX, blockY */
            +(2u*sizeof(uint16_t)); /* numElmtsX, numElmtsY */
    internalBlock[INTERNAL_X_IDX].size= ALIGN_SIMD(args->maxNumElmts+1u + (2u*VCOP_SIMD_WIDTH))*sizeof(uint16_t);
    internalBlock[INTERNAL_X_IDX].attrs.memAttrs= BAM_MEMATTRS_CONST;
    internalBlock[INTERNAL_X_IDX].space= BAM_MEMSPACE_WBUF;
    internalBlock[INTERNAL_Y_IDX].size= ALIGN_SIMD(args->maxNumElmts+1u + (2u*VCOP_SIMD_WIDTH))*sizeof(uint16_t);
    internalBlock[INTERNAL_Y_IDX].attrs.memAttrs= BAM_MEMATTRS_CONST;
    internalBlock[INTERNAL_X_IDX].space= BAM_MEMSPACE_WBUF;

    outBlock[OUT_XY_IDX].size         = ALIGN_2SIMD((args->maxNumElmts+1u)*sizeof(uint16_t))*2u;
    outBlock[OUT_NUM_ELMNTS_IDX].size = ALIGN_2SIMD(sizeof(uint32_t));

    return BAM_S_SUCCESS;
}

BAM_KernelInfo gBAM_TI_generateListKernel =
{
        0,                                      /* kernelId */
        sizeof(BAM_GenerateList_Context),
        sizeof(BAM_GenerateList_Args),
        BAM_EVE,                                /* coreType */
        BAM_NODE_COMPUTE,                       /* nodeType */
        NUM_IN_BLOCKS,                          /* 1 */
        NUM_OUT_BLOCKS,                         /* 2 */
        NUM_INTERNAL_BLOCKS                     /* 2 */
};

BAM_KernelHelperFuncDef gBAM_TI_generateListHelperFunc =
{ &BAM_generateList_getMemRecFunc, NULL};

