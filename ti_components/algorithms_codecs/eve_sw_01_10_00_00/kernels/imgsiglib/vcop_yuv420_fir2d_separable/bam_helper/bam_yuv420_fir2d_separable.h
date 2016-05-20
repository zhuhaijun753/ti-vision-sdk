/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_yuv420_fir2d_separable.h
 *
 *  @brief      This header defines interfaces for integrating YUV420 2d FIR filter kernel
 *              into BAM.
 */

#ifndef BAM_YUV420_FIR2D_SEPARABLE_H_
#define BAM_YUV420_FIR2D_SEPARABLE_H_

#define BAM_YUV420_FIR2D_MAX_COEFF_WIDTH   (3U)
#define BAM_YUV420_FIR2D_MAX_COEFF_HEIGHT  (3U)
#define BAM_YUV420_FIR2D_MAX_COEFF_SIZE  (BAM_YUV420_FIR2D_MAX_COEFF_WIDTH * BAM_YUV420_FIR2D_MAX_COEFF_HEIGHT)


typedef struct bam_yuv420_fir2dseparable_args
{
  uint16_t blockWidth;         /* width of input block, in elements */
  uint16_t pitch;        /* offset between input lines, in elems*/
  uint16_t blockHeight;         /* height of input block*/
  uint8_t  coefWidth;     /* width of coef block, in elements*/
  uint8_t  coefHeight;     /* width of coef block, in elements*/
  uint8_t  (*coefPtr)[BAM_YUV420_FIR2D_MAX_COEFF_SIZE];     /* width of coef block, in elements*/
  uint16_t rndBits;      /* bit position for rounding*/
} BAM_Yuv420_fir2dseparable_Args;

extern BAM_KernelHelperFuncDef gBAM_TI_yuv420Fir2dSeparableYHelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_yuv420Fir2dSeparableYExecFunc;

extern BAM_KernelInfo gBAM_TI_yuv420Fir2dSeparableYKernel;


extern BAM_KernelHelperFuncDef gBAM_TI_yuv420Fir2dSeparableUvHelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_yuv420Fir2dSeparableUvExecFunc;

extern BAM_KernelInfo gBAM_TI_yuv420Fir2dSeparableUvKernel;

#define BAM_YUV420_FIR2D_SEPARABLE_INPUT_PORT     (0)

#define BAM_YUV420_FIR2D_SEPARABLE_OUTPUT_PORT    (0)


#endif /* BAM_YUV420_FIR2D_SEPARABLE_H_ */

