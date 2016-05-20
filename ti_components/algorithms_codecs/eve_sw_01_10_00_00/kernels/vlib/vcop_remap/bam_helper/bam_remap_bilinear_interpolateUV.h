/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_remap_bilinear_interpolateUV.h
 *
 *  @brief      This header defines interfaces for integrating Remap Bilinear
 *              interpolate 8 bit kernel into BAM.
 */

#ifndef BAM_REMAP_BILINEAR_INTERPOLATEUV_H_
#define BAM_REMAP_BILINEAR_INTERPOLATEUV_H_

typedef struct bam_remap_bilinear_interpolateUV_ctrlArgs
{
  uint32_t      maxInBlockSize;
  uint16_t      maxInputBlockStride;
  uint8_t       byPassInput;
} BAM_RemapBilinearinterpolateUV_ctrlArgs;


typedef struct bam_remap_bilinear_interpolateUV_args
{
  uint16_t      outBlockWidth;
  uint16_t      outBlockHeight;
  uint8_t       mnQShift;
  uint8_t       oQShift;
  uint16_t      qScale;
  uint8_t       mult;
  uint8_t       rightShift;
  int64_t       sat_high;
  int64_t       sat_high_set;
  int64_t       sat_low;
  int64_t       sat_low_set;
  BAM_RemapBilinearinterpolateUV_ctrlArgs ctrlArgs;
} BAM_RemapBilinearinterpolateUV_Args;

extern BAM_KernelHelperFuncDef gBAM_TI_remapBilinearinterpolateUVHelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_remapBilinearinterpolateUVExecFunc;

extern BAM_KernelInfo gBAM_TI_remapBilinearinterpolateUVKernel;

#define BAM_REMAP_BILINEAR_INTERPOLATEUV_INPUT_PORT   (0U)
#define BAM_REMAP_BILINEAR_INTERPOLATEUV_LUT_PORT     (1U)


#define BAM_REMAP_BILINEAR_INTERPOLATEUV_OUTPUT_PORT  (0U)


#endif /* BAM_REMAP_BILINEAR_INTERPOLATEUV_H_ */

