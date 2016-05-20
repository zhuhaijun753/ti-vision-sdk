/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_intensity_scaling.h
 *
 *  @brief      This header defines interfaces for integrating intensity
 *              scaling kernel into BAM.
 */

#ifndef BAM_INTENSITY_SCALING_H_
#define BAM_INTENSITY_SCALING_H_

typedef struct
{
    uint16_t blockWidth;
    uint16_t blockHeight;
    uint16_t blockStride;
    uint8_t  loPixelVal;
    uint8_t  hiPixelVal;
    uint8_t  numLevels;
} BAM_Intensity_scaling_Args;


extern BAM_KernelHelperFuncDef gBAM_TI_intensityScalingHelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_intensityScalingExecFunc;

extern BAM_KernelInfo gBAM_TI_intensityScalingKernel;

typedef enum
{
  BAM_INTENSITY_SCALING_INPUT_PORT_IMG   =    0,
  BAM_INTENSITY_SCALING_NUM_INPUT_BLOCKS
} eBAM_INTENSITY_SCALING_INPUT_PORTS ;

typedef enum
{
  BAM_INTENSITY_SCALING_OUTPUT_PORT_IMG   =    0,
  BAM_INTENSITY_SCALING_NUM_OUTPUT_BLOCKS
} eBAM_INTENSITY_SCALING_OUTPUT_PORTS ;

#endif /* BAM_INTENSITY_SCALING_H_ */

