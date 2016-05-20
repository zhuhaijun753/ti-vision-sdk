/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_normalizedGradXyList.h
 *
 *  @brief      This header defines interfaces for integrating calculation of normalized
 *                  gradient X and Y into BAM.
 */

#ifndef BAM_NORMALIZEDGRADXYLIST_H_
#define BAM_NORMALIZEDGRADXYLIST_H_

#include <stdint.h>
#include "evealgframework.h"

typedef struct
{
  uint16_t maxWidth; /* width must be multiple of 8  for optimal performance*/
  uint16_t maxHeight;
} BAM_NormalizedGradXyList_Args;

typedef struct
{
  uint16_t width; /* width must be multiple of 8  for optimal performance*/
  uint16_t height;
  uint16_t pitchInData;
  uint16_t pitchEdgeMap;
  uint16_t frameStartX;
  uint16_t frameStartY;
  uint16_t numHorizontalBlk;
} BAM_NormalizedGradXyList_CtrlArgs;

extern BAM_KernelHelperFuncDef gBAM_TI_normalizedGradXyListHelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_normalizedGradXyListExecFunc;

extern BAM_KernelInfo gBAM_TI_normalizedGradXyListKernel;

typedef enum
{
  BAM_NORMALIZED_GRADXY_LIST_IN_DATA_PORT   =   0,
  BAM_NORMALIZED_GRADXY_LIST_IN_EDGEMAP_PORT,
  BAM_NORMALIZED_GRADXY_LIST_NUM_INPUT_BLOCKS
} eBAM_NORMALIZED_GRADXY_LIST_INPUT_PORTS;

typedef enum
{
  BAM_NORMALIZED_GRADXY_LIST_UNIT_XY_PORT = 0,
  BAM_NORMALIZED_GRADXY_LIST_XY_PORT,
  BAM_NORMALIZED_GRADXY_LIST_SIZE_PORT,
  BAM_NORMALIZED_GRADXY_LIST_NUM_OUTPUT_BLOCKS
} eBAM_NORMALIZED_GRADXY_LIST_OUTPUT_PORTS;

typedef enum
{
  BAM_NORMALIZED_GRADXY_LIST_INTERNAL_PARAM_BLOCKS = 0,
  BAM_NORMALIZED_GRADXY_LIST_INTERNAL_CONST_WBUF,
  BAM_NORMALIZED_GRADXY_LIST_INTERNAL_SCRATCH_IBUFLA,
  BAM_NORMALIZED_GRADXY_LIST_INTERNAL_SCRATCH_IBUFHA,
  BAM_NORMALIZED_GRADXY_LIST_INTERNAL_CONST_IBUFLA,
  BAM_NORMALIZED_GRADXY_LIST_INTERNAL_NUM_BLOCK
} eBAM_NORMALIZED_GRADXY_LIST_INTERNAL_BLOCKS;

#endif /* BAM_NORMALIZEDGRADXYLIST_H_ */

