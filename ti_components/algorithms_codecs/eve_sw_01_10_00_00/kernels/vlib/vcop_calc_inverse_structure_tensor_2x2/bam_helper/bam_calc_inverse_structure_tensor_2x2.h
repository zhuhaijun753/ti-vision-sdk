/*==========================================================================*/
/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_calc_inverse_structure_tensor_2x2.h
 *
 *  @brief      This header defines interfaces for integrating kernel that computes
 *              inverse of the 2x2 structure tensor into BAM.
 */

#ifndef BAM_CALC_INVERSE_STRUCTURE_TENSOR_2X2_H_
#define BAM_CALC_INVERSE_STRUCTURE_TENSOR_2X2_H_

typedef struct 
{
    uint16_t currLevel;
} BAM_Calc_Inverse_Structure_Tensor_2x2_Ctrl_Args;

typedef struct 
{
    uint16_t    inputStride;
    uint16_t    outputStride;
    uint16_t    numKeyPoints;
    BAM_Calc_Inverse_Structure_Tensor_2x2_Ctrl_Args ctrlPtr;
} BAM_Calc_Inverse_Structure_Tensor_2x2_Args;

extern BAM_KernelHelperFuncDef gBAM_TI_calcInverseStructureTensor2x2HelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_calcInverseStructureTensor2x2ExecFunc;

extern BAM_KernelInfo gBAM_TI_calcInverseStructureTensor2x2Kernel;

#define BAM_CALC_INVERSE_STRUCTURE_TENSOR_2X2_INPUT_PORT_TENSOR     (0)
#define BAM_CALC_INVERSE_STRUCTURE_TENSOR_2X2_INPUT_PORT_NRSB       (1)
#define BAM_CALC_INVERSE_STRUCTURE_TENSOR_2X2_INPUT_PORT_NORM       (2)
                                                                    
#define BAM_CALC_INVERSE_STRUCTURE_TENSOR_2X2_OUTPUT_PORT_OUT1      (0)

#endif /* BAM_CALC_INVERSE_STRUCTURE_TENSOR_2X2_H_ */
