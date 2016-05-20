/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_blockAverage2x2_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating block average 2x2 into BAM, used for image pyamid applet.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_blockAverage2x2_int.h"
#include "bam_blockAverage2x2.h"
#include "vcop_blockAverage2x2_kernel.h"

/* Function Prototypes */
static BAM_Status BAM_blockAverage2x2_initFrame(void *kernelContext);

static BAM_Status BAM_blockAverage2x2_initFrame(void *kernelContext)
{
    BAM_BlockAverage2x2_Context *context = (BAM_BlockAverage2x2_Context *) kernelContext;
    BAM_Status status = 0;

#if !(VCOP_HOST_EMULATION)

    vcop_blockAverage2x2_uchar_init((uint8_t*)context->pInBlock[BAM_BLOCKAVERAGE2x2_INPUT_PORT],
                           (uint8_t*)context->pOutBlock[BAM_BLOCKAVERAGE2x2_OUTPUT_PORT],
                           context->kernelArgs.in_stride,
                           context->kernelArgs.out_stride,
                           context->kernelArgs.width,
                           context->kernelArgs.height,
                           (uint16_t *)context->pInternalBlock[PARAMS_IDX]);

#endif
    return status;
}

#if (VCOP_HOST_EMULATION)
static BAM_Status BAM_blockAverage2x2_compute(void *kernelContext)
{
    BAM_BlockAverage2x2_Context *context = (BAM_BlockAverage2x2_Context *) kernelContext;
    BAM_Status status = 0;

    vcop_blockAverage2x2_uchar((unsigned char*)context->pInBlock[BAM_BLOCKAVERAGE2x2_INPUT_PORT],
            (unsigned char*)context->pOutBlock[BAM_BLOCKAVERAGE2x2_OUTPUT_PORT],
            context->kernelArgs.in_stride,
            context->kernelArgs.out_stride,
            context->kernelArgs.width,
            context->kernelArgs.height
    );

    return 0;
}
#endif


BAM_KernelExecFuncDef gBAM_TI_blockAverage2x2ExecFunc =
#if !(VCOP_HOST_EMULATION)
{ NULL, &BAM_blockAverage2x2_initFrame, NULL, NULL, NULL, &vcop_blockAverage2x2_uchar_vloops };
#else
{ NULL, &BAM_blockAverage2x2_initFrame, &BAM_blockAverage2x2_compute, NULL, NULL, NULL};
#endif

