/*==========================================================================*/
/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_calc_determinant_tensor_matrix.h
 *
 *  @brief      This header defines interfaces for integrating kernel that computes
 *              determinant of the tensor matrix into BAM.
 */

#ifndef BAM_CALC_DETERMINANT_TENSOR_MATRIX_H_
#define BAM_CALC_DETERMINANT_TENSOR_MATRIX_H_

typedef struct 
{
    uint16_t currLevel;
} BAM_Calc_Determinant_Tensor_Matrix_Ctrl_Args;

typedef struct 
{
    uint16_t    n;
    BAM_Calc_Determinant_Tensor_Matrix_Ctrl_Args ctrlPtr;
} BAM_Calc_Determinant_Tensor_Matrix_Args;

extern BAM_KernelHelperFuncDef gBAM_TI_calcDeterminantTensorMatrixHelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_calcDeterminantTensorMatrixExecFunc;

extern BAM_KernelInfo gBAM_TI_calcDeterminantTensorMatrixKernel;

#define BAM_CALC_DETERMINANT_TENSOR_MATRIX_INPUT_PORT_XX     (0U  )
#define BAM_CALC_DETERMINANT_TENSOR_MATRIX_INPUT_PORT_YY     (1U  )
#define BAM_CALC_DETERMINANT_TENSOR_MATRIX_INPUT_PORT_XY     (2U  )
#define BAM_CALC_DETERMINANT_TENSOR_MATRIX_OUTPUT_PORT_NRSB  (0U )
#define BAM_CALC_DETERMINANT_TENSOR_MATRIX_OUTPUT_PORT_NORM  (1U )

#endif /* BAM_CALC_DETERMINANT_TENSOR_MATRIX_H_ */
