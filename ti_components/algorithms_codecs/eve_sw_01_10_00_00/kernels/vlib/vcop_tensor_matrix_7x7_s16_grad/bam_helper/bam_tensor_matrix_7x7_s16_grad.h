/*==========================================================================*/
/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_tensor_matrix_7x7_s16_grad.h
 *
 *  @brief      This header defines interfaces for integrating kernel that computes
 *              tensor matrix using the 7x7 patch window of signed gradient input into BAM.
 */

#ifndef BAM_TENSOR_MATRIX_7X7_S16_GRAD_H_
#define BAM_TENSOR_MATRIX_7X7_S16_GRAD_H_

typedef struct 
{
    uint16_t currLevel;
} BAM_Tensor_Matrix_7x7_S16_Grad_Ctrl_Args;

typedef struct 
{
  uint16_t         stride;
  uint16_t         n;
  BAM_Tensor_Matrix_7x7_S16_Grad_Ctrl_Args ctrlPtr;  
} BAM_Tensor_Matrix_7x7_S16_Grad_Args;

extern BAM_KernelHelperFuncDef gBAM_TI_tensorMatrix7x7S16GradHelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_tensorMatrix7x7S16GradExecFunc;

extern BAM_KernelInfo gBAM_TI_tensorMatrix7x7S16GradKernel;

#define BAM_TENSOR_MATRIX_7X7_S16_GRAD_INPUT_PORT_GRADX    ( 0  )
#define BAM_TENSOR_MATRIX_7X7_S16_GRAD_INPUT_PORT_GRADY    ( 1  )

#define BAM_TENSOR_MATRIX_7X7_S16_GRAD_OUTPUT_TENSOR       ( 0  )

#endif /* BAM_TENSOR_MATRIX_7X7_S16_GRAD_H_ */
