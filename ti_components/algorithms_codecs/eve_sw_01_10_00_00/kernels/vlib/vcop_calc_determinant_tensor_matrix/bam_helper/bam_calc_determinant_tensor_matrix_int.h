/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_calc_determinant_tensor_matrix_int.h
 *
 *  @brief      This header defines internal structures for kernel that computes
 *              determinant of the tensor matrix into BAM.
 */
#ifndef BAM_CALC_DETERMINANT_TENSOR_MATRIX_INT_H_
#define BAM_CALC_DETERMINANT_TENSOR_MATRIX_INT_H_

#include <stdint.h>
#include <vcop.h>

#include "evealgframework.h"
#include "bam_calc_determinant_tensor_matrix.h"

#define NUM_IN_BLOCKS       (3)
#define NUM_OUT_BLOCKS      (2)
#define NUM_INTERNAL_BLOCKS (1)

#define PARAMS_IDX (0)

#define IN_IDX1  (BAM_CALC_DETERMINANT_TENSOR_MATRIX_INPUT_PORT_XX   )   
#define IN_IDX2  (BAM_CALC_DETERMINANT_TENSOR_MATRIX_INPUT_PORT_YY   )   
#define IN_IDX3  (BAM_CALC_DETERMINANT_TENSOR_MATRIX_INPUT_PORT_XY   )   
                                                                    
#define OUT_IDX1 (BAM_CALC_DETERMINANT_TENSOR_MATRIX_OUTPUT_PORT_NRSB)   
#define OUT_IDX2 (BAM_CALC_DETERMINANT_TENSOR_MATRIX_OUTPUT_PORT_NORM)   

typedef struct 
{
    /* Must always follow this order: pInternalBlock[], pInBlock[], pOutputBlock[], args */
    void *pInternalBlock[NUM_INTERNAL_BLOCKS];
    void *pInBlock[NUM_IN_BLOCKS];
    void *pOutBlock[NUM_OUT_BLOCKS];
    BAM_Calc_Determinant_Tensor_Matrix_Args kernelArgs;
} BAM_Calc_Determinant_Tensor_Matrix_Context;

#endif /* BAM_CALC_DETERMINANT_TENSOR_MATRIX_INT_H_ */
