/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_census_8bits_int.h
 *
 *  @brief      This header defines internal structures for census 8bits kernel
 *              into BAM.
 */
#ifndef BAM_CENSUS_8BITS_INT_H_
#define BAM_CENSUS_8BITS_INT_H_

#include <stdint.h>
#include <vcop.h>

#include "evealgframework.h"
#include "bam_census_8bits.h"

#define MAX(a,b) (((a)>(b)) ? (a) : (b))

#define NUM_IN_BLOCKS 1
#define NUM_OUT_BLOCKS 1
#define NUM_INTERNAL_BLOCKS 6

#define CENSUS_8BITS_IN_IDX 0     /* 0 */

#define CENSUS_8BITS_OUT_IDX 0   /* 0 */

#define CENSUS_8BITS_PARAMS_IDX          0         /* 0 */
#define CENSUS_8BITS_SCRATCH_BITMASK_IDX 1         /* 1 */
#define CENSUS_8BITS_SCRATCH_IDX         2         /* 2 */
#define CENSUS_8BITS_OFFSET_IDX          3         /* 3 */
#define CENSUS_8BITS_CODEWORDMASK_IDX    4         /* 4 */
#define CENSUS_8BITS_ROWMASK_IDX         5         /* 5 */

typedef struct _bam_census_8bits_context
{
    /* Must always follow this order: pInternalBlock[], pInBlock[], pOutputBlock[], args */
    void *pInternalBlock[NUM_INTERNAL_BLOCKS];
    void *pInBlock[NUM_IN_BLOCKS];
    void *pOutBlock[NUM_OUT_BLOCKS];
    BAM_Census_8bits_Args kernelArgs;
    uint16_t scratchStride;
} BAM_Census_8bits_Context;

#endif /* BAM_CENSUS_8BITS_INT_H_*/
