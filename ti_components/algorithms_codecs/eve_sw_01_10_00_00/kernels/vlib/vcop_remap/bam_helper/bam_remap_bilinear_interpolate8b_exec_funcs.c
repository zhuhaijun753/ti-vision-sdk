/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_remap_bilinear_interpolate8b_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating Remap Bilinear
 *              interpolate 8 bit kernel into BAM.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_remap_bilinear_interpolate8b_int.h"
#include "bam_remap_bilinear_interpolate8b.h"
#include "vcop_bilinearInterpolate8b.h"
#include "vcop_memcpy.h"
#include "remap_common.h"

#define BLOCK_MAP_16_BITS (0U)

/* Function Prototypes */
static BAM_Status Bam_RemapBilinearInterpolate8b_initFrame(void *kernelContext);

static BAM_Status Bam_RemapBilinearInterpolate8b_initFrame(void *kernelContext)
{
    BAM_RemapBilinearInterpolate8b_Context *context = (BAM_RemapBilinearInterpolate8b_Context *) kernelContext;
    BAM_Status status = 0;
    uint8_t *actualLutPtr = (uint8_t *)((*(uint8_t (*)[])context->pInBlock[REMAP_BILINEAR_INTERPOLATE8B_IN_LUT_IDX]) +
                                 sizeof(convertMapBlockInfo));
#if !BLOCK_MAP_16_BITS
    uint8_t *actualfracPtr = (uint8_t *)((*(uint8_t (*)[])((void *)actualLutPtr)) +
                              (2U*context->kernelArgs.outBlockWidth * context->kernelArgs.outBlockHeight));
#endif

#if (!VCOP_HOST_EMULATION)
   if(context->kernelArgs.ctrlArgs.byPassInput == 0)
   {
    vcop_bilinearInterpolate8b_highSpeed_init((uint8_t *)context->pInBlock[REMAP_BILINEAR_INTERPOLATE8B_IN_DATA_IDX],
                    (uint8_t *)context->pOutBlock[REMAP_BILINEAR_INTERPOLATE8B_OUT_DATA_IDX],
                    context->kernelArgs.outBlockWidth * context->kernelArgs.outBlockHeight,
                    (uint16_t *)(void *)actualLutPtr,
#if !BLOCK_MAP_16_BITS
                    actualfracPtr,
#endif
                    (uint16_t *)context->pInternalBlock[REMAP_BILINEAR_INTERPOLATE8B_INTERTNAL_SCRATCH_IDX],
                    (uint8_t *)context->pInternalBlock[REMAP_BILINEAR_INTERPOLATE8B_INTERTNAL_SCRATCH_HBUF_IDX],
                    context->kernelArgs.ctrlArgs.maxInputBlockStride,
                    context->kernelArgs.ctrlArgs.maxInBlockSize,
                    (uint8_t *)context->pInternalBlock[REMAP_BILINEAR_INTERPOLATE8B_INTERTNAL_INDATA_LUT],
                    context->kernelArgs.mnQShift,
                    context->kernelArgs.oQShift,
                    context->kernelArgs.qScale,
                    context->kernelArgs.mult,
                    context->kernelArgs.rightShift,
                    context->kernelArgs.sat_high,
                    context->kernelArgs.sat_high_set,
                    context->kernelArgs.sat_low,
                    context->kernelArgs.sat_low_set,
                    context->pInternalBlock[REMAP_BILINEAR_INTERPOLATE8B_INTERTNAL_PARAMS_IDX]);
      context->kernelCustom = &vcop_bilinearInterpolate8b_highSpeed_vloops;
   }
   else
   {
     vcop_memcpy2d_init((uint16_t *)context->pInBlock[REMAP_BILINEAR_INTERPOLATE8B_IN_DATA_IDX],
                    (uint16_t *)context->pOutBlock[REMAP_BILINEAR_INTERPOLATE8B_OUT_DATA_IDX],
                    context->kernelArgs.outBlockWidth,
                    context->kernelArgs.outBlockHeight,
                    context->kernelArgs.ctrlArgs.maxInputBlockStride,
                    context->pInternalBlock[REMAP_BILINEAR_INTERPOLATE8B_INTERTNAL_PARAMS_IDX]);

      context->kernelCustom = &vcop_memcpy2d_vloops;
   }
#endif

    return status;
}

static BAM_Status Bam_RemapBilinearInterpolate8b_compute(void *kernelContext);

static BAM_Status Bam_RemapBilinearInterpolate8b_compute(void *kernelContext)
{
    BAM_RemapBilinearInterpolate8b_Context *context = (BAM_RemapBilinearInterpolate8b_Context *) kernelContext;
    BAM_Status status = 0;
#if (VCOP_HOST_EMULATION)
    uint8_t * actualLutPtr = (uint8_t *)context->pInBlock[REMAP_BILINEAR_INTERPOLATE8B_IN_LUT_IDX] +
                                 sizeof(convertMapBlockInfo);
#if !BLOCK_MAP_16_BITS
   uint8_t * actualfracPtr = actualLutPtr +  2U*context->kernelArgs.outBlockWidth * context->kernelArgs.outBlockHeight;
#endif

    if(context->kernelArgs.ctrlArgs.byPassInput == 0)
    {
    vcop_bilinearInterpolate8b_highSpeed((uint8_t *)context->pInBlock[REMAP_BILINEAR_INTERPOLATE8B_IN_DATA_IDX],
                    (uint8_t *)context->pOutBlock[REMAP_BILINEAR_INTERPOLATE8B_OUT_DATA_IDX],
                    context->kernelArgs.outBlockWidth * context->kernelArgs.outBlockHeight,
                    (uint16_t *)actualLutPtr,
#if !BLOCK_MAP_16_BITS
                    actualfracPtr,
#endif
                    (uint16_t *)context->pInternalBlock[REMAP_BILINEAR_INTERPOLATE8B_INTERTNAL_SCRATCH_IDX],
                    (uint8_t *)context->pInternalBlock[REMAP_BILINEAR_INTERPOLATE8B_INTERTNAL_SCRATCH_HBUF_IDX],
                    context->kernelArgs.ctrlArgs.maxInputBlockStride,
                    context->kernelArgs.ctrlArgs.maxInBlockSize,
                    (uint8_t *)context->pInternalBlock[REMAP_BILINEAR_INTERPOLATE8B_INTERTNAL_INDATA_LUT],
                    context->kernelArgs.mnQShift,
                    context->kernelArgs.oQShift,
                    context->kernelArgs.qScale,
                    context->kernelArgs.mult,
                    context->kernelArgs.rightShift,
                    context->kernelArgs.sat_high,
                    context->kernelArgs.sat_high_set,
                    context->kernelArgs.sat_low,
                    context->kernelArgs.sat_low_set);
    }
    else
    {
     vcop_memcpy2d((uint16_t *)context->pInBlock[REMAP_BILINEAR_INTERPOLATE8B_IN_DATA_IDX],
                    (uint16_t *)context->pOutBlock[REMAP_BILINEAR_INTERPOLATE8B_OUT_DATA_IDX],
                    context->kernelArgs.outBlockWidth,
                    context->kernelArgs.outBlockHeight,
                    context->kernelArgs.ctrlArgs.maxInputBlockStride);
    }
#else
    context->kernelCustom(context->pInternalBlock[REMAP_BILINEAR_INTERPOLATE8B_INTERTNAL_PARAMS_IDX]);
#endif

    return status;
}

static BAM_Status Bam_RemapBilinearInterpolate8b_control(void *kernelContext, void *ctlArg);

static BAM_Status Bam_RemapBilinearInterpolate8b_control(void *kernelContext, void *ctlArg)
{
  BAM_Status status = 0;
  BAM_RemapBilinearInterpolate8b_Context *context = (BAM_RemapBilinearInterpolate8b_Context *) kernelContext;
  BAM_RemapBilinearInterpolate8b_ctrlArgs *args = (BAM_RemapBilinearInterpolate8b_ctrlArgs *) ctlArg;
  context->kernelArgs.ctrlArgs = *args;
  return status;
}


BAM_KernelExecFuncDef gBAM_TI_remapBilinearInterpolate8bExecFunc =
    { NULL, &Bam_RemapBilinearInterpolate8b_initFrame, &Bam_RemapBilinearInterpolate8b_compute, NULL, &Bam_RemapBilinearInterpolate8b_control, NULL };

