/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_image_pyramid_uv_u8_exec_funcs.c
 *
 *  @brief      This header defines interfaces for integrating one level puramid function into BAM
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "bam_image_pyramid_uv_u8_int.h"
#include "vcop_image_pyramid_uv_u8_kernel.h" /* makerules should take care of include path */

/* Function Prototypes */
static BAM_Status BAM_Image_pyramid_uv_u8_initFrame(void *kernelContext);
/*static BAM_Status BAM_Image_pyramid_uv_u8_computeFrame(void *kernelContext);*/

static BAM_Status BAM_Image_pyramid_uv_u8_initFrame(void *kernelContext)
{
    BAM_Image_Pyramid_UV_U8_Context *context = (BAM_Image_Pyramid_UV_U8_Context *) kernelContext;

    vcop_image_pyramid_uv_u8_init((uint8_t *)context->pInBlock[0],
                                  context->kernelArgs.inCols,
                                  context->kernelArgs.inRows,
                                  (uint8_t *)context->pOutBlock[0],
                                  (uint16_t *)context->pInternalBlock[PARAMS_IDX]);

    return 0;
}

/* No need to implement wrapper, the framework will call the vloop directly */
#if 0
static uint32_t BAM_Image_pyramid_uv_u8_computeFrame(void *kernelContext)
{
    BAM_Image_Pyramid_UV_U8_Context *context = (BAM_Image_Pyramid_UV_U8_Context *) kernelContext;

    vcop_image_pyramid_uv_u8_vloops(context->pInternalBlock[PARAMS_IDX]);

    return 0;
}
#endif

BAM_KernelExecFuncDef gBAM_TI_downsampleuvu8ExecFunc =
{ NULL, &BAM_Image_pyramid_uv_u8_initFrame, NULL, NULL, NULL, (BAM_KernelCustom)&vcop_image_pyramid_uv_u8_vloops };
