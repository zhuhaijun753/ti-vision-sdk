/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_weight_computation_int.h
 *
 *  @brief      This header defines internal structures for weight computation
 *              kernel into BAM.
 */
#ifndef BAM_WEIGHT_COMPUTATION_INT_H_
#define BAM_WEIGHT_COMPUTATION_INT_H_

#include <stdint.h>
#include <vcop.h>

#include "evealgframework.h"
#include "bam_weight_computation.h"

#define NUM_IN_BLOCKS       ( 1 )
#define NUM_OUT_BLOCKS      ( 1 )
#define NUM_INTERNAL_BLOCKS ( 1 )

#define PARAMS_IDX         ( 0 )

#define VCOP_LK_Q_FORMATE_PEL_RESOLN (4)

#define IN_IDX  (BAM_WEIGHT_COMPUTATION_INPUT_PORT   ) 

#define OUT_IDX (BAM_WEIGHT_COMPUTATION_OUTPUT_PORT  )

typedef struct 
{
    /* Must always follow this order: pInternalBlock[], pInBlock[], pOutputBlock[], args */
    void *pInternalBlock[NUM_INTERNAL_BLOCKS];
    void *pInBlock[NUM_IN_BLOCKS];
    void *pOutBlock[NUM_OUT_BLOCKS];
    BAM_Weight_Computation_Args kernelArgs;
} BAM_Weight_Computation_Context;

#endif /* BAM_WEIGHT_COMPUTATION_INT_H_ */
