/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_fast9_int.h
 *
 *  @brief      This header defines internal structures for fast9 kernel
 *              into BAM.
 */
#ifndef BAM_FAST9_INT_H_
#define BAM_FAST9_INT_H_

#include <stdint.h>
#include <vcop.h>

#include "evealgframework.h"
#include "bam_fast9.h"

#define NUM_IN_BLOCKS (1)
#define NUM_OUT_BLOCKS (1)
#define NUM_INTERNAL_BLOCKS (4)

#define FAST9_IN_IDX (0)     /* 0 */

#define FAST9_OUT_IDX (0)   /* 0 */

#define FAST9_PARAMS_IDX (0)                /* 0 */
#define FAST9_SCRATCH_OUT0_PTR_IDX (1)                  /* 1 */
#define FAST9_SCRATCH_OUT1_PTR_IDX (2)          /* 2 */
#define FAST9_SCRATCH_OUT4_PTR_IDX (3)         /* 3 */

typedef struct bam_fast9_context
{
    /* Must always follow this order: pInternalBlock[], pInBlock[], pOutputBlock[], args */
    void *pInternalBlock[NUM_INTERNAL_BLOCKS];
    void *pInBlock[NUM_IN_BLOCKS];
    void *pOutBlock[NUM_OUT_BLOCKS];
    BAM_Fast9_Args kernelArgs;
} BAM_Fast9_Context;

#endif /* BAM_FAST9_INT_H_*/
