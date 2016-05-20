/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_extract_bit_field_u32_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating extract
 *              bit field function into BAM.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_extract_bit_field_u32_int.h"
#include "vcop_extract_bit_field_u32_kernel.h" /* compiler should take care of include path */

/* Function Prototypes */
static BAM_Status Bam_Extract_Bit_Field_initFrame(void *kernelContext);

static BAM_Status Bam_Extract_Bit_Field_initFrame(void *kernelContext)
{
    BAM_Extract_Bit_Field_Context *context = (BAM_Extract_Bit_Field_Context *) kernelContext;

#if (!VCOP_HOST_EMULATION)
    vcop_extract_bit_field_u32_init((uint32_t*)context->pInBlock[IN_LIST_IDX],
                           context->kernelArgs.length,
                           context->kernelArgs.bit_mask,
                           context->kernelArgs.shift,
                           (uint8_t*)context->pOutBlock[OUT_LIST_IDX],
                           (uint16_t *)context->pInternalBlock[PARAMS_IDX]);
#endif

    return 0;
}

#if VCOP_HOST_EMULATION
static BAM_Status Bam_Extract_Bit_Field_compute(void *kernelContext);

static BAM_Status Bam_Extract_Bit_Field_compute(void *kernelContext)
{
    BAM_Extract_Bit_Field_Context *context = (BAM_Extract_Bit_Field_Context *) kernelContext;

    vcop_extract_bit_field_u32((uint32_t*)context->pInBlock[IN_LIST_IDX],
                           context->kernelArgs.length,
                           context->kernelArgs.bit_mask,
                           context->kernelArgs.shift,
                           (uint32_t*)context->pOutBlock[OUT_LIST_IDX]);

    return 0;
}
#endif

BAM_KernelExecFuncDef gBAM_TI_extract_bit_field_u32ExecFunc =
#if (!VCOP_HOST_EMULATION)
{
    NULL,
    &Bam_Extract_Bit_Field_initFrame,
    NULL,
    NULL,
    NULL,
    &vcop_extract_bit_field_u32_vloops
};
#else
{
    NULL,
    &Bam_Extract_Bit_Field_initFrame,
    &Bam_Extract_Bit_Field_compute,
    NULL,
    NULL,
    NULL
};
#endif

