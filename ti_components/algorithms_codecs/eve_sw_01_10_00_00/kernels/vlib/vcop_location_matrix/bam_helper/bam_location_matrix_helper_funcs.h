/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
* @file bam_location_matrix_helper_funcs.h
*
* @brief
*
* @version 0.0 (Jan 2014) : Base version.
*/

#ifndef BAM_LOCATION_MATRIX_HELPER_FUNCS_H_
#define BAM_LOCATION_MATRIX_HELPER_FUNCS_H_

#include "evealgframework.h"
#include "bam_location_matrix.h"
#include <vcop.h>
#include <stdint.h>

/*
1 Internal Block for param register
*/
#define LOCATION_MATRIX_NUM_INTERNAL_BLOCKS 2u

/* Two Input Blocks */
#define LOCATION_MATRIX_NUM_IN_BLOCKS 2u

/* Two ouput Blocks*/
#define LOCATION_MATRIX_NUM_OUT_BLOCKS 2u


/* Index for Internal Blocks */
#define LOCATION_MATRIX_INTERNAL_PARAMS_IDX (0u)
#define LOCATION_MATRIX_INTERNAL_BIN_IDX (1u)

/* Index for Input Blocks */
#define LOCATION_MATRIX_IN_BLK1_IDX    (0u)
#define LOCATION_MATRIX_IN_BLK2_IDX          (1u)

/* Index for output Block */
#define LOCATION_MATRIX_OUT_MATRIX1_IDX     (0u)
#define LOCATION_MATRIX_OUT_MATRIX2_IDX     (1u)

typedef struct bam_location_matrix_context
{
    void *pInternalBlock[LOCATION_MATRIX_NUM_INTERNAL_BLOCKS];
    void *pInBlock[LOCATION_MATRIX_NUM_IN_BLOCKS];
    void *pOutBlock[LOCATION_MATRIX_NUM_OUT_BLOCKS];
    BAM_location_matrix_Args  kernelArgs;
    BAM_KernelCustom kernelCustom;
} BAM_location_matrix_Context;

#endif /* BAM_LOCATION_MATRIX_HELPER_FUNCS_H_*/

