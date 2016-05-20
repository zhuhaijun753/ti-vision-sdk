/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_median_filter_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating median filter
 *              function into BAM.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_median_filter_int.h"
#include "bam_median_filter.h"
#include "vcop_median_filter_mxn_u8.h"

/* Kernel wrapper context structure */
#pragma DATA_SECTION(medianContext, "DMEM");
static median_kernel_context medianContext = {NULL, NULL};

/* Function Prototypes */
static BAM_Status Bam_Median_Filter_initFrame(void *kernelContext);
static BAM_Status Bam_Median_Filter_compute(void *kernelContext);

static BAM_Status Bam_Median_Filter_initFrame(void *kernelContext)
{
    BAM_Median_Filter_Context *context = (BAM_Median_Filter_Context *) kernelContext;
    BAM_Status status = 0;

    /* Return error if assumptions in kernel are not satisfied */
    if(context->kernelArgs.kernelWidth <= 8U) {
        status = 1;
    }

    if(status == 0) {
        vcop_large_kernel_median_wrapper_init((uint8_t *)context->pInBlock[IN_IDX],
                                              (uint8_t *)context->pOutBlock[OUT_IDX],
                                              context->kernelArgs.blockWidth,
                                              context->kernelArgs.blockWidth,
                                              context->kernelArgs.blockHeight,
                                              context->kernelArgs.kernelWidth,
                                              context->kernelArgs.kernelHeight,
                                              context->kernelArgs.stepSizeHorz,
                                              context->kernelArgs.stepSizeVert,
                                              (int16_t *)context->pInternalBlock[HISTO_IDX],
                                              (int8_t  *)context->pInternalBlock[SCRATCH_WEIGHT_IDX],
                                              (int16_t *)context->pInternalBlock[SCRATCH_HISTO_IDX],
                                              (int16_t *)context->pInternalBlock[BLK_HIST_IDX],
                                              (int16_t *)context->pInternalBlock[COARSE_HIST_IDX],
                                              (uint16_t *)context->pInternalBlock[PARAMS_IDX],
                                              &medianContext);
    }

    return status;
}


static BAM_Status Bam_Median_Filter_compute(void *kernelContext)
{
    BAM_Status status = 0;

    vcop_large_kernel_median_wrapper_vloops(&medianContext);

    return status;
}


BAM_KernelExecFuncDef gBAM_TI_medianFilterExecFunc =
{ NULL, &Bam_Median_Filter_initFrame, &Bam_Median_Filter_compute, NULL, NULL, NULL };

