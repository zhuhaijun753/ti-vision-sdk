/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_binary_masking.h
 *
 *  @brief      This header defines interfaces for integrating Binary Masking kernel
 *              into BAM.
 */

#ifndef BAM_BINARY_MASKING_H_
#define BAM_BINARY_MASKING_H_

#include "bam_common.h"

typedef struct
{
  uint16_t  maxBlockWidth;
  uint16_t  maxBlockHeight;
} BAM_BinaryMasking_Args;

typedef struct
{
  uint16_t  computeWidth;
  uint16_t  computeHeight;
  uint16_t  inputByteDataPitch;
  uint16_t  inputBitDataPitch;
  uint16_t  outputPitch;
} BAM_BinaryMasking_CtrlArgs;


extern BAM_KernelInfo gBAM_TI_binaryMaskingKernel;
extern BAM_KernelHelperFuncDef gBAM_TI_binaryMaskingHelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_binaryMaskingExecFunc;

typedef enum
{
  BAM_BINARY_MASKING_INPUT_BYTE_DATA_IMAGE_PORT= 0,
  BAM_BINARY_MASKING_INPUT_BIT_DATA_IMAGE_PORT,
  BAM_BINARY_MASKING_NUM_INPUT_BLOCKS
} eBAM_BINARY_MASKING_INPUT_PORTS;

typedef enum
{
  BAM_BINARY_MASKING_OUTPUT_PORT = 0,
  BAM_BINARY_MASKING_NUM_OUTPUT_BLOCKS
} eBAM_BINARY_MASKING_OUTPUT_PORTS;

#endif /* BAM_BINARY_MASKING_H_ */

