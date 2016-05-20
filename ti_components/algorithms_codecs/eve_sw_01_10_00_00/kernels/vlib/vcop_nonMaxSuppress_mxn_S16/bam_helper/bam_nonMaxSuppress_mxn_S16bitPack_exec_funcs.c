/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_nonMaxSuppress_mxn_S16bitPack_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating nonMaxSuppress_mxn_S32 into a BAM graph
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_nonMaxSuppress_mxn_S16bitPack_int.h"
#include "bam_nonMaxSuppress_mxn_S16bitPack.h"
#include "vcop_nonMaxSuppress_mxn_16s_kernel.h"

/* Function Prototypes */
static BAM_Status BAM_nonMaxSuppress_mxn_S16bitPack_initFrame(void *kernelContext);
static BAM_Status BAM_nonMaxSuppress_mxn_S16bitPack_control(void *kernelContext, void *kernelCtlArg);

static BAM_Status BAM_nonMaxSuppress_mxn_S16bitPack_control(void *kernelContext, void *kernelCtlArg){

    BAM_NonMaxSuppress_mxn_S16bitPack_Context *context = (BAM_NonMaxSuppress_mxn_S16bitPack_Context *) kernelContext;
    BAM_NonMaxSuppress_mxn_S16bitPack_CtlArgs *ctlArg= (BAM_NonMaxSuppress_mxn_S16bitPack_CtlArgs *) kernelCtlArg;
    BAM_Status status = 0;

    context->ctrlArgs = *ctlArg;


    return status;
}

static BAM_Status BAM_nonMaxSuppress_mxn_S16bitPack_initFrame(void *kernelContext)
{
    BAM_NonMaxSuppress_mxn_S16bitPack_Context *context = (BAM_NonMaxSuppress_mxn_S16bitPack_Context *) kernelContext;
    BAM_Status status = 0;

#if !(VCOP_HOST_EMULATION)
    vcop_nonMaxSuppress_mxn_16sbitPack_init
    (
        (int16_t*)context->pInBlock[BAM_NONMAXSUPPRESS_MXN_S16BITPACK_INPUT_PORT],
        (uint8_t*)context->pOutBlock[BAM_NONMAXSUPPRESS_MXN_S16BITPACK_OUTPUT_PORT],
        (uint16_t*)context->pInternalBlock[BAM_NONMAXSUPPRESS_MXN_S16BITPACK_INTERNAL_SCRATCHBUF1],
        (uint16_t*)context->pInternalBlock[BAM_NONMAXSUPPRESS_MXN_S16BITPACK_INTERNAL_SCRATCHBUF2],
        context->ctrlArgs.computeWidth +  (context->ctrlArgs.winW - (uint16_t)1U),
        context->ctrlArgs.computeHeight + (context->ctrlArgs.winH - (uint16_t)1U),
        context->ctrlArgs.inStride,
        context->ctrlArgs.outStride / (uint16_t)8U,
        context->ctrlArgs.winW,
        context->ctrlArgs.winH,
        (int16_t)context->ctrlArgs.threshold,
        (uint16_t*)context->pInternalBlock[BAM_NONMAXSUPPRESS_MXN_S16BITPACK_INTERNAL_PARAMS_IDX]
    );
#endif
    return status;
}

#if (VCOP_HOST_EMULATION)
static BAM_Status BAM_nonMaxSuppress_mxn_S16bitPack_compute(void *kernelContext)
{
    BAM_NonMaxSuppress_mxn_S16bitPack_Context *context = (BAM_NonMaxSuppress_mxn_S16bitPack_Context *) kernelContext;
    BAM_Status status = 0;
    vcop_nonMaxSuppress_mxn_16sbitPack
    (
        (int16_t*)context->pInBlock[BAM_NONMAXSUPPRESS_MXN_S16BITPACK_INPUT_PORT],
        (uint8_t*)context->pOutBlock[BAM_NONMAXSUPPRESS_MXN_S16BITPACK_OUTPUT_PORT],
        (uint16_t*)context->pInternalBlock[BAM_NONMAXSUPPRESS_MXN_S16BITPACK_INTERNAL_SCRATCHBUF1],
        (uint16_t*)context->pInternalBlock[BAM_NONMAXSUPPRESS_MXN_S16BITPACK_INTERNAL_SCRATCHBUF2],
        context->ctrlArgs.computeWidth + (context->ctrlArgs.winW - 1U),
        context->ctrlArgs.computeHeight + (context->ctrlArgs.winH - 1U),
        context->ctrlArgs.inStride,
        context->ctrlArgs.outStride / 8U,
        context->ctrlArgs.winW,
        context->ctrlArgs.winH,
        context->ctrlArgs.threshold
    );

    return status;
}
#endif

BAM_KernelExecFuncDef gBAM_TI_nonMaxSuppress_mxn_S16bitPack_ExecFunc =
#if !(VCOP_HOST_EMULATION)
{
  NULL,
  &BAM_nonMaxSuppress_mxn_S16bitPack_initFrame,
  NULL,
  NULL,
  &BAM_nonMaxSuppress_mxn_S16bitPack_control,
  &vcop_nonMaxSuppress_mxn_16sbitPack_vloops };
#else
{
  NULL,
  &BAM_nonMaxSuppress_mxn_S16bitPack_initFrame,
  &BAM_nonMaxSuppress_mxn_S16bitPack_compute,
  NULL,
  &BAM_nonMaxSuppress_mxn_S16bitPack_control,
  NULL };
#endif

