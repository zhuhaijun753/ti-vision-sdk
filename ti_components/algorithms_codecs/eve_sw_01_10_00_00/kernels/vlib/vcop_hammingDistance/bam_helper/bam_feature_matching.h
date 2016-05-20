/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_feature_matching.h
 *
 *  @brief      This header defines interfaces for integrating Hamming distance
 *              based corrrespondence matching computations into BAM.
 */

#ifndef BAM_FEATURE_MATCHING_H_
#define BAM_FEATURE_MATCHING_H_

typedef struct
{
  uint32_t    descriptorSize;
  uint32_t    descriptorPitch;
  uint32_t    numDescriptors1;
  uint32_t    numDescriptors2;
  uint8_t     mode;
} BAM_featureMatching_Args;

typedef struct
{
  uint32_t    numDescFullList1;
  uint32_t    numDescFullList2;
  uint16_t    minDistanceThres;
  uint16_t    matchConfidence;
  uint32_t    numDesc1PerIter;
  uint32_t    numDesc2PerIter;
} BAM_featureMatching_CtlArgs;

extern BAM_KernelHelperFuncDef gBAM_TI_featureMatchingHelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_featureMatchingExecFunc;

extern BAM_KernelInfo gBAM_TI_featureMatchingKernel;

typedef enum
{
  BAM_FEATURE_MATCHING_STRING_1_PORT =    0,
  BAM_FEATURE_MATCHING_STRING_2_PORT,
  BAM_FEATURE_MATCHING_NUM_INPUT_BLOCKS
} eBAM_FEATURE_MATCHING_INPUT_PORTS;

typedef enum
{
  BAM_FEATURE_MATCHING_OUTPUT_PORT   =    0,
  BAM_FEATURE_MATCHING_NUM_OUTPUT_BLOCKS
} eBAM_FEATURE_MATCHING_OUTPUT_PORTS;

#endif /* BAM_FEATURE_MATCHING_H_ */
