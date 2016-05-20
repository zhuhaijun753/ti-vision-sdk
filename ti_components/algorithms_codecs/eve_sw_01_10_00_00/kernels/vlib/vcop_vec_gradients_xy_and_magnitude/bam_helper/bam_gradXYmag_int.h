/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_gradXYmag_int.h
 *
 *  @brief      This header defines internal structures  for integrating gradient XY and magnitude
 */
#ifndef BAM_GRADXYMAG_INT_H

#define BAM_GRADXYMAG_INT_H

#include <stdint.h>
#include <vcop.h>

#include "evealgframework.h"
#include "bam_gradXYmag.h"

#define NUM_IN_BLOCKS 1
#define NUM_OUT_BLOCKS 3
#define NUM_INTERNAL_BLOCKS 1

#define OUT_X_IDX (BAM_GRADXYMAG_X_OUTPUT_PORT)            /* 0 */
#define OUT_Y_IDX (BAM_GRADXYMAG_Y_OUTPUT_PORT)            /* 1 */
#define OUT_MAG_IDX (BAM_GRADXYMAG_MAG_OUTPUT_PORT)            /* 2 */

#define PARAMS_IDX 0         /* 0 */


typedef struct
{
    /* Must always follow this order: pInternalBlock[], pInBlock[], pOutputBlock[], args */
    void *pInternalBlock[NUM_INTERNAL_BLOCKS];
    void *pInBlock[NUM_IN_BLOCKS];
    void *pOutBlock[NUM_OUT_BLOCKS];
    BAM_GradXYmag_Args kernelArgs;
    BAM_KernelCustom kernelCustom;
} BAM_GradXYmag_Context;

#endif
