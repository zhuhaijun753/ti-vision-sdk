/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_image_interleave_u8_exec_funcs.c
 *
 *  @brief      This file implements functions for integrating unsigned 8 bit interleave function into BAM
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_image_interleave_u8_int.h"
#include "bam_image_interleave_u8.h"
#include "vcop_image_interleave_kernel.h" /* compiler should take care of include path */

/* Function Prototypes */
static BAM_Status BAM_Image_interleave_u8_initFrame(void *kernelContext);
/*static BAM_Status BAM_Image_interleave_u8_computeFrame(void *kernelContext);*/


static BAM_Status BAM_Image_interleave_u8_initFrame(void *kernelContext)
{
    BAM_Image_Interleave_U8_Context *context = (BAM_Image_Interleave_U8_Context *) kernelContext;

    vcop_image_interleave_u8_init((uint8_t *)context->pInBlock[Y_IDX],
                                  (uint8_t *)context->pInBlock[UV_IDX],
                                  context->kernelArgs.inCols,
                                  context->kernelArgs.inRows,
                                  (uint8_t *)context->pOutBlock[0],
                                  (uint16_t *)context->pInternalBlock[PARAMS_IDX]);

    return 0;
}

/* No need to implement wrapper, the framework will call the vloop directly */
#if 0
static uint32_t BAM_Image_interleave_u8_computeFrame(void *kernelContext)
{
    BAM_Image_Interleave_U8_Context *context = (BAM_Image_Interleave_U8_Context *) kernelContext;

    vcop_image_interleave_u8_vloops(context->pInternalBlock[PARAMS_IDX]);

    return 0;
}
#endif

BAM_KernelExecFuncDef gBAM_TI_interleaveu8ExecFunc =
{ NULL, &BAM_Image_interleave_u8_initFrame, NULL, NULL, NULL, (BAM_KernelCustom)&vcop_image_interleave_u8_vloops };
