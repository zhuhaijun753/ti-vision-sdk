/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_remap_bilinear_interpolateUV_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating Remap Bilinear
 *              interpolate 8 bit kernel into BAM.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_remap_bilinear_interpolateUV_int.h"
#include "bam_remap_bilinear_interpolateUV.h"
#include "vcop_bilinearinterpolateUV.h"
#include "vcop_memcpy.h"
#include "remap_common.h"

#define BLOCK_MAP_16_BITS (0U)

/* Function Prototypes */
static BAM_Status Bam_RemapBilinearinterpolateUV_initFrame(void *kernelContext);

static BAM_Status Bam_RemapBilinearinterpolateUV_initFrame(void *kernelContext)
{
    BAM_RemapBilinearinterpolateUV_Context *context = (BAM_RemapBilinearinterpolateUV_Context *) kernelContext;
    BAM_Status status = 0;
#if (!VCOP_HOST_EMULATION)
    uint8_t *actualLutPtr = (uint8_t *)((*(uint8_t (*)[])context->pInBlock[REMAP_BILINEAR_INTERPOLATEUV_IN_LUT_IDX]) +
                                 sizeof(convertMapBlockInfo));

#if !BLOCK_MAP_16_BITS
    uint8_t *actualfracPtr = (uint8_t *)((*(uint8_t (*)[])((void *)actualLutPtr)) +
                              (2U*context->kernelArgs.outBlockWidth * context->kernelArgs.outBlockHeight));
#endif

   if(context->kernelArgs.ctrlArgs.byPassInput == 0)
   {
    vcop_bilinearInterpolateUV_init((uint8_t *)context->pInBlock[REMAP_BILINEAR_INTERPOLATEUV_IN_DATA_IDX],
                    (uint8_t *)context->pOutBlock[REMAP_BILINEAR_INTERPOLATEUV_OUT_DATA_IDX],
                    context->kernelArgs.outBlockWidth * context->kernelArgs.outBlockHeight,
                    (uint16_t *)(void *)actualLutPtr,
#if !BLOCK_MAP_16_BITS
                    actualfracPtr,
#endif
                    (uint16_t *)context->pInternalBlock[REMAP_BILINEAR_INTERPOLATEUV_INTERTNAL_SCRATCH_IDX],
                    (uint8_t *)context->pInternalBlock[REMAP_BILINEAR_INTERPOLATEUV_INTERTNAL_SCRATCH_HBUF_IDX],
                    context->kernelArgs.ctrlArgs.maxInputBlockStride,
                    context->kernelArgs.ctrlArgs.maxInBlockSize,
                    (uint8_t *)context->pInternalBlock[REMAP_BILINEAR_INTERPOLATEUV_INTERTNAL_INDATA_LUT],
                    context->kernelArgs.mnQShift,
                    context->kernelArgs.oQShift,
                    context->kernelArgs.qScale,
                    context->kernelArgs.mult,
                    context->kernelArgs.rightShift,
                    context->kernelArgs.sat_high,
                    context->kernelArgs.sat_high_set,
                    context->kernelArgs.sat_low,
                    context->kernelArgs.sat_low_set,
                    context->pInternalBlock[REMAP_BILINEAR_INTERPOLATEUV_INTERTNAL_PARAMS_IDX]);
       context->kernelCustom = &vcop_bilinearInterpolateUV_vloops;
  }
   else
   {
     vcop_memcpy2d_init((uint16_t *)context->pInBlock[REMAP_BILINEAR_INTERPOLATEUV_IN_DATA_IDX],
                    (uint16_t *)context->pOutBlock[REMAP_BILINEAR_INTERPOLATEUV_OUT_DATA_IDX],
                    context->kernelArgs.outBlockWidth*2U,
                    context->kernelArgs.outBlockHeight,
                    context->kernelArgs.ctrlArgs.maxInputBlockStride,
                    context->pInternalBlock[REMAP_BILINEAR_INTERPOLATEUV_INTERTNAL_PARAMS_IDX]);

      context->kernelCustom = &vcop_memcpy2d_vloops;
   }
#endif

    return status;
}

static BAM_Status Bam_RemapBilinearinterpolateUV_compute(void *kernelContext);

static BAM_Status Bam_RemapBilinearinterpolateUV_compute(void *kernelContext)
{
    BAM_RemapBilinearinterpolateUV_Context *context = (BAM_RemapBilinearinterpolateUV_Context *) kernelContext;
    BAM_Status status = 0;
#if (VCOP_HOST_EMULATION)
    uint8_t * actualLutPtr = (uint8_t *)context->pInBlock[REMAP_BILINEAR_INTERPOLATEUV_IN_LUT_IDX] +
                                 sizeof(convertMapBlockInfo);
#if !BLOCK_MAP_16_BITS
   uint8_t * actualfracPtr = actualLutPtr +  2U*context->kernelArgs.outBlockWidth * context->kernelArgs.outBlockHeight;
#endif

   if(context->kernelArgs.ctrlArgs.byPassInput == 0)
   {
    vcop_bilinearInterpolateUV((uint8_t *)context->pInBlock[REMAP_BILINEAR_INTERPOLATEUV_IN_DATA_IDX],
                    (uint8_t *)context->pOutBlock[REMAP_BILINEAR_INTERPOLATEUV_OUT_DATA_IDX],
                    context->kernelArgs.outBlockWidth * context->kernelArgs.outBlockHeight,
                    (uint16_t *)actualLutPtr,
#if !BLOCK_MAP_16_BITS
                    actualfracPtr,
#endif
                    (uint16_t *)context->pInternalBlock[REMAP_BILINEAR_INTERPOLATEUV_INTERTNAL_SCRATCH_IDX],
                    (uint8_t *)context->pInternalBlock[REMAP_BILINEAR_INTERPOLATEUV_INTERTNAL_SCRATCH_HBUF_IDX],
                    context->kernelArgs.ctrlArgs.maxInputBlockStride,
                    context->kernelArgs.ctrlArgs.maxInBlockSize,
                    (uint8_t *)context->pInternalBlock[REMAP_BILINEAR_INTERPOLATEUV_INTERTNAL_INDATA_LUT],
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
     vcop_memcpy2d((uint16_t *)context->pInBlock[REMAP_BILINEAR_INTERPOLATEUV_IN_DATA_IDX],
                    (uint16_t *)context->pOutBlock[REMAP_BILINEAR_INTERPOLATEUV_OUT_DATA_IDX],
                    context->kernelArgs.outBlockWidth*2U,
                    context->kernelArgs.outBlockHeight,
                    context->kernelArgs.ctrlArgs.maxInputBlockStride);
   }
#else
    context->kernelCustom(context->pInternalBlock[REMAP_BILINEAR_INTERPOLATEUV_INTERTNAL_PARAMS_IDX]);

#endif
    return status;
}

static BAM_Status Bam_RemapBilinearinterpolateUV_control(void *kernelContext, void *ctlArg);

static BAM_Status Bam_RemapBilinearinterpolateUV_control(void *kernelContext, void *ctlArg)
{
  BAM_Status status = 0;
  BAM_RemapBilinearinterpolateUV_Context *context = (BAM_RemapBilinearinterpolateUV_Context *) kernelContext;
  BAM_RemapBilinearinterpolateUV_ctrlArgs *args   = (BAM_RemapBilinearinterpolateUV_ctrlArgs *) ctlArg;
  context->kernelArgs.ctrlArgs = *args;
  return status;
}

BAM_KernelExecFuncDef gBAM_TI_remapBilinearinterpolateUVExecFunc =
    { NULL, &Bam_RemapBilinearinterpolateUV_initFrame, &Bam_RemapBilinearinterpolateUV_compute, NULL, &Bam_RemapBilinearinterpolateUV_control, NULL };

