/*==========================================================================*/
/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_weight_computation.h
 *
 *  @brief      This header defines interfaces for integrating weight computation
 *              kernel into BAM.
 */

#ifndef BAM_WEIGHT_COMPUTATION_H_
#define BAM_WEIGHT_COMPUTATION_H_

typedef struct 
{
	uint16_t currLevel;
} BAM_Weight_Computation_Ctrl_Args;

typedef struct 
{
	uint16_t numKeyPoints;
	uint16_t outputStride;
    BAM_Weight_Computation_Ctrl_Args ctrlPtr;
} BAM_Weight_Computation_Args;

extern BAM_KernelHelperFuncDef gBAM_TI_weightComputationHelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_weightComputationExecFunc;

extern BAM_KernelInfo gBAM_TI_weightComputationKernel;

#define BAM_WEIGHT_COMPUTATION_INPUT_PORT     (0  )

#define BAM_WEIGHT_COMPUTATION_OUTPUT_PORT    (0)

#endif /* BAM_WEIGHT_COMPUTATION_H_ */
