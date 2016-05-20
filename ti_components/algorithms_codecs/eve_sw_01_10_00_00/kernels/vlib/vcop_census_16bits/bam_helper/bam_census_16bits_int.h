/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_census_16bits_int.h
 *
 *  @brief      This header defines internal structures for census 8bits kernel
 *              into BAM.
 */
#ifndef BAM_CENSUS_16BITS_INT_H_
#define BAM_CENSUS_16BITS_INT_H_

#include <stdint.h>
#include <vcop.h>

#include "evealgframework.h"
#include "bam_census_16bits.h"

/* CHECK_MISRA("-19.7")  -> Disable rule 19.7 */
/* Function-like macro definition */
/* Deviation is allowed because this is a simple macro */
#define MAX(a,b) (((a)>(b)) ? (a) : (b))
/*RESET_MISRA("19.7")  -> Reset rule 19.7 for GOTO */

#define NUM_IN_BLOCKS 1
#define NUM_OUT_BLOCKS 1
#define NUM_INTERNAL_BLOCKS 6

#define CENSUS_16BITS_IN_IDX 0     /* 0 */

#define CENSUS_16BITS_OUT_IDX 0   /* 0 */

#define CENSUS_16BITS_PARAMS_IDX          0         /* 0 */
#define CENSUS_16BITS_SCRATCH_BITMASK_IDX 1         /* 1 */
#define CENSUS_16BITS_SCRATCH_IDX         2         /* 2 */
#define CENSUS_16BITS_OFFSET_IDX          3         /* 3 */
#define CENSUS_16BITS_CODEWORDMASK_IDX    4         /* 4 */
#define CENSUS_16BITS_ROWMASK_IDX         5         /* 5 */

/* CHECK_MISRA("-20.2")  -> Disable rule 20.2 */
/* Usage of a reserved name for naming a language entity */
/* Deviation allowed because _bam_census_16bits_context is not reserved */
typedef struct _bam_census_16bits_context
{
    /* Must always follow this order: pInternalBlock[], pInBlock[], pOutputBlock[], args */
    void *pInternalBlock[NUM_INTERNAL_BLOCKS];
    void *pInBlock[NUM_IN_BLOCKS];
    void *pOutBlock[NUM_OUT_BLOCKS];
    BAM_Census_16bits_Args kernelArgs;
    uint16_t scratchStride;
} BAM_Census_16bits_Context;
/*RESET_MISRA("20.2")  -> Reset rule 20.2 */

#endif /* BAM_CENSUS_16BITS_INT_H_*/
