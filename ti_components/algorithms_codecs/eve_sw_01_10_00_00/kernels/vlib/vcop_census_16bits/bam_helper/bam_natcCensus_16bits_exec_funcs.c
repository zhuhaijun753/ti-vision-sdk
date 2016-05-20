/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_natcCensus_16bits_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating natural C version of census transform
 *              function into BAM.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_census_16bits_int.h"
#include "bam_natcCensus_16bits.h"
#include "vcop_census_16bits_cn.h"
#include "init_census_16bits_params.h"

static BAM_Status BAM_natcCensus_16bits_compute(void *kernelContext);

static BAM_Status BAM_natcCensus_16bits_compute(void *kernelContext)
{
    BAM_Census_16bits_Context *context = (BAM_Census_16bits_Context *) kernelContext;
    BAM_Status status = 0;

    vcop_census_16bits_cn(
                    (uint16_t*)context->pInBlock[CENSUS_16BITS_IN_IDX],
                    (uint8_t*)context->pOutBlock[CENSUS_16BITS_OUT_IDX],
                    context->kernelArgs.winWidth, 
                    context->kernelArgs.winHeight,
                    context->kernelArgs.winHorzStep,
                    context->kernelArgs.winVertStep,
                    context->kernelArgs.in_w,
                    context->kernelArgs.in_h,
                    context->kernelArgs.in_pitch,
                    context->kernelArgs.out_pitch
            );
    
    return status;
}


BAM_KernelExecFuncDef gBAM_TI_natcCensus_16bits_ExecFunc =
    { NULL, NULL, &BAM_natcCensus_16bits_compute, NULL, NULL, NULL };

