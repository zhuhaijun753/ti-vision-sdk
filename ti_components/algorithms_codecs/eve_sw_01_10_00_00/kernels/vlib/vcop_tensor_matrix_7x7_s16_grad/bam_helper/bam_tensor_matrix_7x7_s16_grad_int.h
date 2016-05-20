/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_tensor_matrix_7x7_s16_grad_int.h
 *
 *  @brief      This header defines internal structures for kernel that computes
 *              tensor matrix using the 7x7 patch window of signed gradient input into BAM.
 */
#ifndef BAM_TENSOR_MATRIX_7X7_S16_GRAD_INT_H_
#define BAM_TENSOR_MATRIX_7X7_S16_GRAD_INT_H_

#include <stdint.h>
#include <vcop.h>

#include "evealgframework.h"
#include "bam_tensor_matrix_7x7_s16_grad.h"

#define NUM_IN_BLOCKS       (2)
#define NUM_OUT_BLOCKS      (1)
#define NUM_INTERNAL_BLOCKS (4)

#define PARAMS_IDX          (0)
#define SCRATCH_IDX1        (1)
#define SCRATCH_IDX2        (2)
#define SCRATCH_IDX3        (3)

#define MAX_NUM_POINTS (32)
#define SCRATCH_SIZE (((uint16_t)((uint16_t)MAX_NUM_POINTS/(uint16_t)VCOP_SIMD_WIDTH))*8U*9U)

#define IN_IDX1  (BAM_TENSOR_MATRIX_7X7_S16_GRAD_INPUT_PORT_GRADX   ) 
#define IN_IDX2  (BAM_TENSOR_MATRIX_7X7_S16_GRAD_INPUT_PORT_GRADY   )

#define OUT_IDX1 (BAM_TENSOR_MATRIX_7X7_S16_GRAD_OUTPUT_TENSOR      )

typedef struct 
{
    /* Must always follow this order: pInternalBlock[], pInBlock[], pOutputBlock[], args */
    void *pInternalBlock[NUM_INTERNAL_BLOCKS];
    void *pInBlock[NUM_IN_BLOCKS];
    void *pOutBlock[NUM_OUT_BLOCKS];
    BAM_Tensor_Matrix_7x7_S16_Grad_Args kernelArgs;
} BAM_Tensor_Matrix_7x7_S16_Grad_Context;

#endif /* BAM_TENSOR_MATRIX_7X7_S16_GRAD_INT_H_ */
