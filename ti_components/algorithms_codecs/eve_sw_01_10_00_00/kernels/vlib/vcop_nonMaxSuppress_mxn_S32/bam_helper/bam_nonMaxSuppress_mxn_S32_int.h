/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_nonMaxSuppress_mxn_S32_int.h
 *
 *  @brief      This header defines internal structures  for integrating non max suppression
 */
#ifndef BAM_NONMAXSUPPRESS_MxN_S32_INT_H

#define BAM_NONMAXSUPPRESS_MxN_S32_INT_H

#include <stdint.h>
#include <vcop.h>

#include "evealgframework.h"
#include "bam_nonMaxSuppress_mxn_S32.h"

#define NUM_IN_BLOCKS 1
#define NUM_OUT_BLOCKS 1
#define NUM_INTERNAL_BLOCKS 3

#define OUT_IDX (BAM_NONMAXSUPPRESS_MxN_S32_OUTPUT_PORT)            /* 0 */

#define PARAMS_IDX   0
#define SCRATCH1_IDX 1
#define SCRATCH2_IDX 2

typedef struct
{
    /* Must always follow this order: pInternalBlock[], pInBlock[], pOutputBlock[], args */
    void *pInternalBlock[NUM_INTERNAL_BLOCKS];
    void *pInBlock[NUM_IN_BLOCKS];
    void *pOutBlock[NUM_OUT_BLOCKS];
    BAM_NonMaxSuppress_mxn_S32_Args kernelArgs;
} BAM_NonMaxSuppress_mxn_S32_Context;

#endif
