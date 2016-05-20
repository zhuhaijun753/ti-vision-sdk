/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_multiblock_gradient_xy_int.h
 *
 *  @brief      This header defines internal structures for multi block gradient
 *              XY compute kernel into BAM.
 */
#ifndef BAM_MULTIBLOCK_GRADIENT_XY_INT_H_
#define BAM_MULTIBLOCK_GRADIENT_XY_INT_H_

#include <stdint.h>
#include <vcop.h>

#include "evealgframework.h"
#include "bam_multiblock_gradient_xy.h"

#define NUM_IN_BLOCKS 1
#define NUM_OUT_BLOCKS 1
#define NUM_INTERNAL_BLOCKS 1

#define PARAMS_IDX 0

#define IN_IDX  (BAM_MULTIBLOCK_GRADIENT_XY_INPUT_PORT  ) 

#define OUT_IDX (BAM_MULTIBLOCK_GRADIENT_XY_OUTPUT_PORT )

typedef struct 
{
    /* Must always follow this order: pInternalBlock[], pInBlock[], pOutputBlock[], args */
    void *pInternalBlock[NUM_INTERNAL_BLOCKS];
    void *pInBlock[NUM_IN_BLOCKS];
    void *pOutBlock[NUM_OUT_BLOCKS];
    BAM_Multiblock_Gradient_XY_Args kernelArgs;
} BAM_Multiblock_Gradient_XY_Context;

#endif /* BAM_MULTIBLOCK_GRADIENT_XY_INT_H_ */
