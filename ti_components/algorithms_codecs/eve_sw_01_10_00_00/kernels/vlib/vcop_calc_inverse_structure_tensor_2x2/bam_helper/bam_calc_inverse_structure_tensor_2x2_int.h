/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_calc_inverse_structure_tensor_2x2_int.h
 *
 *  @brief      This header defines internal structures for kernel that computes
 *              inverse of the 2x2 structure tensor into BAM.
 */
#ifndef BAM_CALC_INVERSE_STRUCTURE_TENSOR_2X2_INT_H_
#define BAM_CALC_INVERSE_STRUCTURE_TENSOR_2X2_INT_H_

#include <stdint.h>
#include <vcop.h>

#include "evealgframework.h"
#include "bam_calc_inverse_structure_tensor_2x2.h"

#define NUM_IN_BLOCKS 3
#define NUM_OUT_BLOCKS 1
#define NUM_INTERNAL_BLOCKS 3

#define PARAMS_IDX                   (0)
#define SCRATCH_IDX1                 (1)
#define SCRATCH_IDX2                 (2)
#define VCOP_LK_Q_FORMATE_PEL_RESOLN (4)

#define IN_IDX1  (BAM_CALC_INVERSE_STRUCTURE_TENSOR_2X2_INPUT_PORT_TENSOR )
#define IN_IDX2  (BAM_CALC_INVERSE_STRUCTURE_TENSOR_2X2_INPUT_PORT_NRSB   )
#define IN_IDX3  (BAM_CALC_INVERSE_STRUCTURE_TENSOR_2X2_INPUT_PORT_NORM   )

#define OUT_IDX1 (BAM_CALC_INVERSE_STRUCTURE_TENSOR_2X2_OUTPUT_PORT_OUT1  )

typedef struct 
{
    /* Must always follow this order: pInternalBlock[], pInBlock[], pOutputBlock[], args */
    void *pInternalBlock[NUM_INTERNAL_BLOCKS];
    void *pInBlock[NUM_IN_BLOCKS];
    void *pOutBlock[NUM_OUT_BLOCKS];
    BAM_Calc_Inverse_Structure_Tensor_2x2_Args kernelArgs;
} BAM_Calc_Inverse_Structure_Tensor_2x2_Context;

#endif /* BAM_CALC_INVERSE_STRUCTURE_TENSOR_2X2_INT_H_ */
