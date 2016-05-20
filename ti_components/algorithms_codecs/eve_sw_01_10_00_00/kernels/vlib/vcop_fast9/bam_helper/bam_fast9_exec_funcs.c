/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_median_filter_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating fast9 kernel
 *              function into BAM.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_fast9_int.h"
#include "bam_fast9.h"
#include "vcop_fast9_kernel.h"

/* Function Prototypes */
static BAM_Status Bam_Fast9_initFrame(void *kernelContext);

static BAM_Status Bam_Fast9_initFrame(void *kernelContext)
{
    BAM_Fast9_Context *context = (BAM_Fast9_Context *) kernelContext;
    BAM_Status status = 0;

#if (!VCOP_HOST_EMULATION)
    vcop_fast9_init((uint8_t *)context->pInBlock[FAST9_IN_IDX],
                    (uint8_t *)context->pInternalBlock[FAST9_SCRATCH_OUT0_PTR_IDX],
                    (uint8_t *)context->pInternalBlock[FAST9_SCRATCH_OUT1_PTR_IDX],
                    (uint16_t *)context->pInternalBlock[FAST9_SCRATCH_OUT4_PTR_IDX],
                    (uint8_t *)context->pOutBlock[FAST9_OUT_IDX],
                    context->kernelArgs.threshold,
                    context->kernelArgs.pitch,
                    context->kernelArgs.in_w,
                    context->kernelArgs.in_h,
                    context->pInternalBlock[FAST9_PARAMS_IDX]);
#endif

    return status;
}

#if (VCOP_HOST_EMULATION)
static BAM_Status Bam_Fast9_compute(void *kernelContext);

static BAM_Status Bam_Fast9_compute(void *kernelContext)
{
    BAM_Fast9_Context *context = (BAM_Fast9_Context *) kernelContext;
    BAM_Status status = 0;

    vcop_fast9((uint8_t *)context->pInBlock[FAST9_IN_IDX],
                    (uint8_t *)context->pInternalBlock[FAST9_SCRATCH_OUT0_PTR_IDX],
                    (uint8_t *)context->pInternalBlock[FAST9_SCRATCH_OUT1_PTR_IDX],
                    (uint16_t *)context->pInternalBlock[FAST9_SCRATCH_OUT4_PTR_IDX],
                    (uint8_t *)context->pOutBlock[FAST9_OUT_IDX],
                    context->kernelArgs.threshold,
                    context->kernelArgs.pitch,
                    context->kernelArgs.in_w,
                    context->kernelArgs.in_h);

    return status;
}
#endif

static BAM_Status Bam_Fast9_control(void *kernelContext, void *kernelCtlArg);

static BAM_Status Bam_Fast9_control(void *kernelContext, void *kernelCtlArg){

    BAM_Fast9_Context *context = (BAM_Fast9_Context *) kernelContext;
    BAM_Fast9_ctrlArgs *ctlArg= (BAM_Fast9_ctrlArgs *) kernelCtlArg;
    BAM_Status status = 0;

    context->kernelArgs.threshold  = ctlArg->threshold;
    context->kernelArgs.pitch      = ctlArg->pitch;
    context->kernelArgs.in_w       = ctlArg->in_w;
    context->kernelArgs.in_h       = ctlArg->in_h;

    return status;
}


BAM_KernelExecFuncDef gBAM_TI_fast9ExecFunc =
#if (!VCOP_HOST_EMULATION)
    { NULL, &Bam_Fast9_initFrame, NULL, NULL, &Bam_Fast9_control, &vcop_fast9_vloops };
#else
    { NULL, &Bam_Fast9_initFrame, &Bam_Fast9_compute, NULL, &Bam_Fast9_control, NULL };
#endif

