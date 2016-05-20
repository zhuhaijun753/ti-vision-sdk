/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_glcm.h
 *
 *  @brief      This header defines interfaces for integrating gray-level
 *              co-occurrence matrix computation into BAM.
 */

#ifndef BAM_GLCM_H_
#define BAM_GLCM_H_

#define BAM_GLCM_MAX_NUM_DIRECTIONS (8U)

typedef struct
{
    uint16_t    blockWidth;
    uint16_t    blockHeight;
    uint16_t    blockStride;
    uint8_t     numLevels;
    uint8_t     numOffsets;
    int8_t      rowOffsets[BAM_GLCM_MAX_NUM_DIRECTIONS];
    int8_t      colOffsets[BAM_GLCM_MAX_NUM_DIRECTIONS];
} BAM_Glcm_Args;

extern BAM_KernelHelperFuncDef gBAM_TI_glcmHelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_glcmExecFunc;

extern BAM_KernelInfo gBAM_TI_glcmKernel;

typedef enum
{
  BAM_GLCM_INPUT_PORT   =    0,
  BAM_GLCM_NUM_INPUT_BLOCKS
} eBAM_GLCM_INPUT_PORTS;

typedef enum
{
  BAM_GLCM_OUTPUT_PORT   =    0,
  BAM_GLCM_NUM_OUTPUT_BLOCKS
} eBAM_GLCM_OUTPUT_PORTS;

#endif /* BAM_GLCM_H_ */
