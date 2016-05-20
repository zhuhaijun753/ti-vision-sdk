/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_gradXYmag.h
 *
 *  @brief      This header defines interfaces for integrating block average 2x2 into BAM.
 */

#ifndef BAM_GRADXYMAG_H_
#define BAM_GRADXYMAG_H_

typedef enum
{
  EVE_VLIB_GRADIENT_MAGNITUDE_SAT_8BITS,
  EVE_VLIB_GRADIENT_MAGNITUDE_9BITS,
  EVE_VLIB_GRADIENT_MAGNITUDE_MAX
} EVE_VLIB_GradientMagnitudeMethod ;

typedef struct
{
  uint16_t pitch; 
  uint16_t width; /* width must be multiple of 16  for optimal performance*/
  uint16_t height;
  uint8_t  gradientMethod;
} BAM_GradXYmag_Args;

extern BAM_KernelHelperFuncDef gBAM_TI_gradXYmagHelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_gradXYmagExecFunc;

extern BAM_KernelInfo gBAM_TI_gradXYmagKernel;

#define BAM_GRADXYMAG_INPUT_PORT         0
#define BAM_GRADXYMAG_X_OUTPUT_PORT      0
#define BAM_GRADXYMAG_Y_OUTPUT_PORT      1
#define BAM_GRADXYMAG_MAG_OUTPUT_PORT    2

#endif /* BAM_GRADXYMAG_H_ */
