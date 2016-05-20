/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_nonMaxSuppress_mxn_S32_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating nonMaxSuppress_mxn_S32 into a BAM graph
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_nonMaxSuppress_mxn_S32_int.h"
#include "bam_nonMaxSuppress_mxn_S32.h"
#include "vcop_nonMaxSuppress_mxn_32s_kernel.h"

/* Function Prototypes */
static BAM_Status BAM_nonMaxSuppress_mxn_S32_initFrame(void *kernelContext);
static BAM_Status BAM_nonMaxSuppress_mxn_S32_control(void *kernelContext, void *kernelCtlArg);

static BAM_Status BAM_nonMaxSuppress_mxn_S32_control(void *kernelContext, void *kernelCtlArg){

    BAM_NonMaxSuppress_mxn_S32_Context *context = (BAM_NonMaxSuppress_mxn_S32_Context *) kernelContext;
    BAM_NonMaxSuppress_mxn_S32_CtlArgs *ctlArg= (BAM_NonMaxSuppress_mxn_S32_CtlArgs *) kernelCtlArg;
    BAM_Status status = 0;

    if (ctlArg->ctlCmdId== BAM_NONMAXSUPPRESS_MxN_S32_CMD_SET_THRESHOLD){
        context->kernelArgs.threshold= ctlArg->threshold;
    }
    else if (ctlArg->ctlCmdId== BAM_NONMAXSUPPRESS_MxN_S32_CMD_GET_THRESHOLD){
        ctlArg->threshold= context->kernelArgs.threshold;
    }
    else {
        status= 1;
    }

    return status;
}

static BAM_Status BAM_nonMaxSuppress_mxn_S32_initFrame(void *kernelContext)
{
    BAM_NonMaxSuppress_mxn_S32_Context *context = (BAM_NonMaxSuppress_mxn_S32_Context *) kernelContext;
    BAM_Status status = 0;

#if !(VCOP_HOST_EMULATION)

    if ( context->kernelArgs.outputFormat == BAM_NONMAXSUPPRESS_MxN_S32_OUTPUT_FORMAT_BYTEMAP)
    {
      vcop_nonMaxSuppress_mxn_32s_init
      (
          (int32_t*)context->pInBlock[BAM_NONMAXSUPPRESS_MxN_S32_INPUT_PORT],
          (uint8_t*)context->pOutBlock[BAM_NONMAXSUPPRESS_MxN_S32_OUTPUT_PORT],
          (int32_t*)context->pInternalBlock[SCRATCH1_IDX],
          (int32_t*)context->pInternalBlock[SCRATCH2_IDX],
          context->kernelArgs.width,
          context->kernelArgs.height,
          context->kernelArgs.inStride,
          context->kernelArgs.outStride,
          context->kernelArgs.winW,
          context->kernelArgs.winH,
          context->kernelArgs.threshold,
          (uint16_t*)context->pInternalBlock[PARAMS_IDX]
      );
    }
    else
    {
      vcop_nonMaxSuppress_mxn_32s_bitPack_init
      (
          (int32_t*)context->pInBlock[BAM_NONMAXSUPPRESS_MxN_S32_INPUT_PORT],
          (uint8_t*)context->pOutBlock[BAM_NONMAXSUPPRESS_MxN_S32_OUTPUT_PORT],
          (int32_t*)context->pInternalBlock[SCRATCH1_IDX],
          (int32_t*)context->pInternalBlock[SCRATCH2_IDX],
          context->kernelArgs.width,
          context->kernelArgs.height,
          context->kernelArgs.inStride,
          context->kernelArgs.outStride,
          context->kernelArgs.winW,
          context->kernelArgs.winH,
          context->kernelArgs.threshold,
          (uint16_t*)context->pInternalBlock[PARAMS_IDX]
      );
    }
#endif
    return status;
}
#if (VCOP_HOST_EMULATION)
static BAM_Status BAM_nonMaxSuppress_mxn_S32_compute(void *kernelContext)
{
    BAM_NonMaxSuppress_mxn_S32_Context *context = (BAM_NonMaxSuppress_mxn_S32_Context *) kernelContext;
    BAM_Status status = 0;
    if ( context->kernelArgs.outputFormat == BAM_NONMAXSUPPRESS_MxN_S32_OUTPUT_FORMAT_BYTEMAP)
    {
      vcop_nonMaxSuppress_mxn_32s
      (
          (int32_t*)context->pInBlock[BAM_NONMAXSUPPRESS_MxN_S32_INPUT_PORT],
          (uint8_t*)context->pOutBlock[BAM_NONMAXSUPPRESS_MxN_S32_OUTPUT_PORT],
          (int32_t*)context->pInternalBlock[SCRATCH1_IDX],
          (int32_t*)context->pInternalBlock[SCRATCH2_IDX],
          context->kernelArgs.width,
          context->kernelArgs.height,
          context->kernelArgs.inStride,
          context->kernelArgs.outStride,
          context->kernelArgs.winW,
          context->kernelArgs.winH,
          context->kernelArgs.threshold);
    }
    else
    {
      vcop_nonMaxSuppress_mxn_32s_bitPack
      (
          (int32_t*)context->pInBlock[BAM_NONMAXSUPPRESS_MxN_S32_INPUT_PORT],
          (uint8_t*)context->pOutBlock[BAM_NONMAXSUPPRESS_MxN_S32_OUTPUT_PORT],
          (int32_t*)context->pInternalBlock[SCRATCH1_IDX],
          (int32_t*)context->pInternalBlock[SCRATCH2_IDX],
          context->kernelArgs.width,
          context->kernelArgs.height,
          context->kernelArgs.inStride,
          context->kernelArgs.outStride,
          context->kernelArgs.winW,
          context->kernelArgs.winH,
          context->kernelArgs.threshold);
    }

    return status;
}
#endif

BAM_KernelExecFuncDef gBAM_TI_nonMaxSuppress_mxn_S32_ExecFunc =
#if !(VCOP_HOST_EMULATION)
{ NULL, &BAM_nonMaxSuppress_mxn_S32_initFrame, NULL, NULL, &BAM_nonMaxSuppress_mxn_S32_control, &vcop_nonMaxSuppress_mxn_32s_vloops };
#else
{ NULL, &BAM_nonMaxSuppress_mxn_S32_initFrame, &BAM_nonMaxSuppress_mxn_S32_compute, NULL, &BAM_nonMaxSuppress_mxn_S32_control, NULL };
#endif

BAM_KernelExecFuncDef gBAM_TI_nonMaxSuppress_mxn_S32_binPack_ExecFunc =
#if !(VCOP_HOST_EMULATION)
{ NULL, &BAM_nonMaxSuppress_mxn_S32_initFrame, NULL, NULL, &BAM_nonMaxSuppress_mxn_S32_control, &vcop_nonMaxSuppress_mxn_32s_bitPack_vloops };
#else
{ NULL, &BAM_nonMaxSuppress_mxn_S32_initFrame, &BAM_nonMaxSuppress_mxn_S32_compute, NULL, &BAM_nonMaxSuppress_mxn_S32_control, NULL };
#endif


