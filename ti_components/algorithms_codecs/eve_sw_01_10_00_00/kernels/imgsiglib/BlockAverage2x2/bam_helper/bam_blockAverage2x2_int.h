/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_blockAverage2x2_int.h
 *
 *  @brief      This header defines internal structures  for integrating block average 2x2 into BAM, used for image pyamid applet.
 */
#ifndef BAM_BLOCKAVERAGE2x2_INT_H
#define BAM_BLOCKAVERAGE2x2_INT_H

#include <stdint.h>
#include <vcop.h>

#include "evealgframework.h"
#include "bam_blockAverage2x2.h"

#define NUM_IN_BLOCKS 1
#define NUM_OUT_BLOCKS 1
#define NUM_INTERNAL_BLOCKS 1

#define OUT_IDX (BAM_BLOCKAVERAGE2x2_OUTPUT_PORT)            /* 0 */
#define PARAMS_IDX 0         /* 0 */


typedef struct
{
    /* Must always follow this order: pInternalBlock[], pInBlock[], pOutputBlock[], args */
    void *pInternalBlock[NUM_INTERNAL_BLOCKS];
    void *pInBlock[NUM_IN_BLOCKS];
    void *pOutBlock[NUM_OUT_BLOCKS];
    BAM_BlockAverage2x2_Args kernelArgs;
} BAM_BlockAverage2x2_Context;

#endif

