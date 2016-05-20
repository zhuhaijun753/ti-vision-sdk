/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_blockSortU32_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating block sort into BAM.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_blockSortU32_int.h"
#include "bam_blockSortU32.h"
#include "../inc/merge_sort.h"
#include "edma_utils_memcpy.h"

#if VCOP_HOST_EMULATION
#include "../inc/vcop_sort_cn.h"
static int32_t beg[1000];
static int32_t end[1000];
#endif

/* Function Prototypes */
static BAM_Status BAM_blockSortU32_initInstance(void *kernelContext);
static BAM_Status BAM_blockSortU32_initFrame(void *kernelContext);
static BAM_Status BAM_blockSortU32_control(void *kernelContext, void *kernelCtlArg);
static BAM_Status BAM_blockSortU32_compute(void *kernelContext);

static BAM_Status BAM_blockSortU32_initInstance(void *kernelContext)
{
    BAM_BlockSortU32_Context *context = (BAM_BlockSortU32_Context *) kernelContext;
    BAM_Status status = 0;
#if !VCOP_HOST_EMULATION
    context->sort.my_pblock_ptr      =  (uint16_t*)(context->pInternalBlock[PARAMS_IDX]);
    context->sort.my_out_offset_ptr  =  (int32_t*)(context->pInternalBlock[OFFSETS_IDX]);
    context->sort.backup_my_pblock_ptr      =  (uint16_t*)(context->pInternalBlock[BACKUP_PARAMS_IDX]);
    context->sort.backup_my_out_offset_ptr  =  (int32_t*)(context->pInternalBlock[BACKUP_OFFSETS_IDX]);
    context->sort.num_funcs_exec     =  0;

    status=  mergeSort_init((void*)context->pInBlock[BAM_BLOCKSORTU32_INPUT_PORT], (void*)context->pOutBlock[BAM_BLOCKSORTU32_OUTPUT_PORT], (void*)context->pOutBlock[BAM_BLOCKSORTU32_OUTPUT_PORT], (uint32_t)context->kernelArgs.numElmts, &context->sort);
#endif

    return status;
}

static BAM_Status BAM_blockSortU32_initFrame(void *kernelContext)
{
    BAM_BlockSortU32_Context *context = (BAM_BlockSortU32_Context *) kernelContext;
    BAM_Status status = 0;

    /* Restore param block and output offset block into the internal memories */
    EDMA_UTILS_memcpy2D(context->pInternalBlock[PARAMS_IDX],
            context->pInternalBlock[BACKUP_PARAMS_IDX],
            2U*MAX_PARAMS, 1U, 0, 0);

    EDMA_UTILS_memcpy2D(context->pInternalBlock[OFFSETS_IDX],
            context->pInternalBlock[BACKUP_OFFSETS_IDX],
            8U* MAX_FUNC_CALLS * 4U, 1U, 0, 0);

    return status;
}

static BAM_Status BAM_blockSortU32_control(void *kernelContext, void *kernelCtlArg){

    BAM_BlockSortU32_Context *context = (BAM_BlockSortU32_Context *) kernelContext;
    BAM_BlockSortU32_CtlArgs *ctlArg= (BAM_BlockSortU32_CtlArgs *) kernelCtlArg;
    BAM_Status status = 0;

    if (ctlArg->ctlCmdId== BAM_BLOCKSORT_U32_CMD_SET_PTR){
        context->pInBlock[BAM_BLOCKSORTU32_INPUT_PORT]= ctlArg->inputPtr;
        context->pOutBlock[BAM_BLOCKSORTU32_OUTPUT_PORT]= ctlArg->outputPtr;
        /* Need to call BAM_blockSortU32_initInstance() in order to reflect the new setting of context->pInBlock[BAM_BLOCKSORTU32_INPUT_PORT] & context->pOutBlock[BAM_BLOCKSORTU32_OUTPUT_PORT] into the backup context->pInternalBlock[BACKUP_PARAMS_IDX] */
        BAM_blockSortU32_initInstance(kernelContext);
    }
    else {
        status= 1;
    }

    return status;
}


static BAM_Status BAM_blockSortU32_compute(void *kernelContext)
{
    BAM_BlockSortU32_Context *context = (BAM_BlockSortU32_Context *) kernelContext;
    uint16_t i;
    BAM_Status status = 0;

#if VCOP_HOST_EMULATION
    memcpy(context->pOutBlock[BAM_BLOCKSORTU32_OUTPUT_PORT],
            context->pInBlock[BAM_BLOCKSORTU32_INPUT_PORT],
            context->kernelArgs.numElmts*sizeof(uint32_t));

    vcop_sort_cn(context->kernelArgs.numElmts ,
            (uint32_t*)context->pOutBlock[BAM_BLOCKSORTU32_OUTPUT_PORT],
            beg, end);

#else
    for (i=0;i<context->sort.num_funcs_exec; i++) {
        context->sort.funcs_exec[i](context->sort.ptr_params[i]);
    }
#endif
    return status;
}

BAM_KernelExecFuncDef gBAM_TI_blockSortU32ExecFunc =
{ &BAM_blockSortU32_initInstance, &BAM_blockSortU32_initFrame, &BAM_blockSortU32_compute, NULL, &BAM_blockSortU32_control, NULL };

