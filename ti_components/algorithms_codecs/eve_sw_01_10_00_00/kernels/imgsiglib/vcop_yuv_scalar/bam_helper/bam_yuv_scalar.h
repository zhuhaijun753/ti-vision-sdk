/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file      bam_vcop_yuv_scalar.h
 *
 *  @brief      This header defines interfaces for integrating YUV Scalar kernel
 *              into BAM.
 */

#ifndef BAM_YUV_SCALAR_H_
#define BAM_YUV_SCALAR_H_

typedef struct 
{
  uint16_t srcBlockWidth;       
  uint16_t srcBlockPitch;        
  uint16_t dstBlockWidth;       
  uint16_t dstBlockHeight;       
  uint8_t  inputDataType;    /*0 --> Luma 1--> UV interleaved         */
} BAM_yuv_scalar_Ctrl_Args;

typedef struct 
{
  uint16_t srcBlockWidth;       
  uint16_t srcBlockPitch;        
  uint16_t dstBlockWidth;       
  uint16_t dstBlockHeight;       
  uint8_t  numTaps;              
  uint8_t  fracBits;             
} BAM_yuv_scalar_Args;

extern BAM_KernelHelperFuncDef  gBAM_TI_yuvScalarHelperFunc;
extern BAM_KernelExecFuncDef    gBAM_TI_yuvScalarExecFunc;
extern BAM_KernelInfo           gBAM_TI_yuvScalarKernel;

#define BAM_YUV_SCALAR_INPUT_DATA_PORT           (0)
#define BAM_YUV_SCALAR_INPUT_INDEX_PORT          (1)
#define BAM_YUV_SCALAR_INPUT_FRAC_COEFF_PORT     (2)
#define BAM_YUV_SCALAR_OUTPUT_DATA_PORT          (0)


#endif /* BAM_YUV_SCALAR_H_ */

