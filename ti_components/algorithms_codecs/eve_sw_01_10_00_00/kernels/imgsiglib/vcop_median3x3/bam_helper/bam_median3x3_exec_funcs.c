/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_median3x3_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating 3x3 median filter 
 *              into BAM.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_median3x3_int.h"
#include "bam_median3x3.h"
#include "vcop_median3x3_kernel.h" /* compiler should take care of include path */

static BAM_Status Bam_Median3x3_initFrame(void *kernelContext);


static BAM_Status Bam_Median3x3_initFrame(void *kernelContext)
{
  BAM_Status status = 0;

#if (!VCOP_HOST_EMULATION)
    BAM_Median3x3_Context *context = (BAM_Median3x3_Context *) kernelContext;

    vcop_median3x3_uchar_init((uint8_t*)context->pInBlock[IN_IDX], 
      (uint8_t*)context->pOutBlock[OUT_IDX],
      (uint8_t*)context->pInternalBlock[SCRATCH_VERT_IDX],
      (uint8_t*)context->pInternalBlock[SCRATCH_HORZ_IDX],
      context->kernelArgs.blockWidth,
      context->kernelArgs.blockHeight,
      context->pInternalBlock[PARAMS_IDX]);
#endif

    return status;
}

#if (VCOP_HOST_EMULATION)
static BAM_Status Bam_Median3x3_computeFrame(void *kernelContext)
{
    BAM_Median3x3_Context *context = (BAM_Median3x3_Context *) kernelContext;

    vcop_median3x3_uchar((uint8_t*)context->pInBlock[IN_IDX], 
        (uint8_t*)context->pOutBlock[OUT_IDX],
        (uint8_t*)context->pInternalBlock[SCRATCH_VERT_IDX],
        (uint8_t*)context->pInternalBlock[SCRATCH_HORZ_IDX],
        (int)context->kernelArgs.blockWidth, (int)context->kernelArgs.blockHeight);

    return 0;
}
#endif

BAM_KernelExecFuncDef gBAM_TI_median3x3ExecFunc =
#if (VCOP_HOST_EMULATION)
    { NULL, &Bam_Median3x3_initFrame, &Bam_Median3x3_computeFrame, NULL, NULL, NULL };
#else
    { NULL, &Bam_Median3x3_initFrame, NULL, NULL, NULL, &vcop_median3x3_uchar_vloops };
#endif

