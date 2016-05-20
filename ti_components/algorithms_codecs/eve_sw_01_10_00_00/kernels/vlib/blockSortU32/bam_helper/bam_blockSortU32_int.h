/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_blockSortU32_int.h
 *
 *  @brief      This header defines internal structures  for integrating block sort into BAM.
 */
#ifndef BAM_INT_BLOCKSORTU32_H_

#define BAM_INT_BLOCKSORTU32_H_

#include <stdint.h>
#include <vcop.h>

#include "evealgframework.h"
#include "../inc/merge_sort.h"
#include "bam_blockSortU32.h"

#define NUM_IN_BLOCKS 1
#define NUM_OUT_BLOCKS 1
#define NUM_INTERNAL_BLOCKS 4


#define OUT_IDX (BAM_BLOCKSORTU32_OUTPUT_PORT)            /* 0 */
#define PARAMS_IDX 0         /* 0 */
#define OFFSETS_IDX 1
#define BACKUP_PARAMS_IDX 2         /* 0 */
#define BACKUP_OFFSETS_IDX 3

/* CHECK_MISRA("-20.2")  -> Disable rule 20.2  */
/* Usage of a reserved name for naming a language entity */
/* Deviation allowed as name is not used for any language entiry */
typedef struct _bam_blockSortU32_context
{
    /* Must always follow this order: pInternalBlock[], pInBlock[], pOutputBlock[], args */
    void *pInternalBlock[NUM_INTERNAL_BLOCKS];
    void *pInBlock[NUM_IN_BLOCKS];
    void *pOutBlock[NUM_OUT_BLOCKS];
    BAM_BlockSortU32_Args kernelArgs;
    SortContext sort;
} BAM_BlockSortU32_Context;
/* RESET_MISRA("20.2")  -> Reset rule 20.2*/

#endif
