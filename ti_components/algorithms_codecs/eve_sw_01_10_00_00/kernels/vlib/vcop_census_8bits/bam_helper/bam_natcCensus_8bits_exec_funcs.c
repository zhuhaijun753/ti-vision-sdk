/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_natcCensus_8bits_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating natural C version of census transform
 *              function into BAM.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_census_8bits_int.h"
#include "bam_natcCensus_8bits.h"
#include "vcop_census_8bits_cn.h"
#include "init_census_8bits_params.h"

static BAM_Status BAM_natcCensus_8bits_compute(void *kernelContext);

static BAM_Status BAM_natcCensus_8bits_compute(void *kernelContext)
{
    BAM_Census_8bits_Context *context = (BAM_Census_8bits_Context *) kernelContext;
    BAM_Status status = 0;

    vcop_census_8bits_cn(
                    (uint8_t*)context->pInBlock[CENSUS_8BITS_IN_IDX],
                    (uint8_t*)context->pOutBlock[CENSUS_8BITS_OUT_IDX],
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


BAM_KernelExecFuncDef gBAM_TI_natcCensus_8bits_ExecFunc =
    { NULL, NULL, &BAM_natcCensus_8bits_compute, NULL, NULL, NULL };

