/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_remap_bilinear_interpolate8b.h
 *
 *  @brief      This header defines interfaces for integrating Remap Bilinear
 *              interpolate 8 bit kernel into BAM.
 */

#ifndef BAM_REMAP_BILINEAR_INTERPOLATE8B_H_
#define BAM_REMAP_BILINEAR_INTERPOLATE8B_H_

typedef struct bam_remap_bilinear_interpolate8b_ctrlArgs
{
  uint32_t      maxInBlockSize;
  uint16_t      maxInputBlockStride;
  uint8_t       byPassInput;
} BAM_RemapBilinearInterpolate8b_ctrlArgs;


typedef struct bam_remap_bilinear_interpolate8b_args
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
  BAM_RemapBilinearInterpolate8b_ctrlArgs ctrlArgs;
} BAM_RemapBilinearInterpolate8b_Args;

extern BAM_KernelHelperFuncDef gBAM_TI_remapBilinearInterpolate8bHelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_remapBilinearInterpolate8bExecFunc;

extern BAM_KernelInfo gBAM_TI_remapBilinearInterpolate8bKernel;

#define BAM_REMAP_BILINEAR_INTERPOLATE8B_INPUT_PORT   (0U)
#define BAM_REMAP_BILINEAR_INTERPOLATE8B_LUT_PORT     (1U)


#define BAM_REMAP_BILINEAR_INTERPOLATE8B_OUTPUT_PORT  (0U)


#endif /* BAM_REMAP_BILINEAR_INTERPOLATE8B_H_ */

