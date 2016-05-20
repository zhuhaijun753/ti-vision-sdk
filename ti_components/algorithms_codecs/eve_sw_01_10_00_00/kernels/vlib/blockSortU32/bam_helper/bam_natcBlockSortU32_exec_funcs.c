/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_natcBlockSortU32_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating the natural C version of BlockSortU32 into a BAM graph
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "../inc/vcop_sort_cn.h"
#include "bam_blockSortU32_int.h"
#include "bam_blockSortU32.h"
#include "../inc/merge_sort.h"

#if VCOP_HOST_EMULATION
static int32_t beg[1000];
static int32_t end[1000];
#else
/* CHECK_MISRA("-8.7")  -> Disable rule 8.7 */
/* Name visibility is too wide */
/* Deviation is allowed because these arrays must go to far sections */
static far int32_t beg[1000];
static far int32_t end[1000];
/*RESET_MISRA("8.7")  -> Reset rule 8.7  */
#endif


/* Function Prototypes */
static BAM_Status BAM_natcBlockSortU32_computeFrame(void *kernelContext);
static BAM_Status BAM_natcBlockSortU32_control(void *kernelContext, void *kernelCtlArg);

static BAM_Status BAM_natcBlockSortU32_control(void *kernelContext, void *kernelCtlArg){

    BAM_BlockSortU32_Context *context = (BAM_BlockSortU32_Context *) kernelContext;
    BAM_BlockSortU32_CtlArgs *ctlArg= (BAM_BlockSortU32_CtlArgs *) kernelCtlArg;
    BAM_Status status = 0;

    if (ctlArg->ctlCmdId== BAM_BLOCKSORT_U32_CMD_SET_PTR){
        context->pInBlock[BAM_BLOCKSORTU32_INPUT_PORT]= ctlArg->inputPtr;
        context->pOutBlock[BAM_BLOCKSORTU32_OUTPUT_PORT]= ctlArg->outputPtr;
    }
    else {
        status= 1;
    }

    return status;
}

static BAM_Status BAM_natcBlockSortU32_computeFrame(void *kernelContext)
{
    BAM_BlockSortU32_Context *context = (BAM_BlockSortU32_Context *) kernelContext;
    BAM_Status status = 0;

    memcpy(context->pOutBlock[BAM_BLOCKSORTU32_OUTPUT_PORT], context->pInBlock[BAM_BLOCKSORTU32_INPUT_PORT], context->kernelArgs.numElmts*4);
    vcop_sort_cn(context->kernelArgs.numElmts, (uint32_t*)context->pOutBlock[BAM_BLOCKSORTU32_OUTPUT_PORT], beg, end);

    return status;
}

BAM_KernelExecFuncDef gBAM_TI_natcBlockSortU32ExecFunc =
{ NULL, NULL, &BAM_natcBlockSortU32_computeFrame, NULL, &BAM_natcBlockSortU32_control, NULL };

