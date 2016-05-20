/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_prune_big_list_int.h
 *  @version 0.1 (Sept 2014) : Updated to add predication based on threshold
 *  @brief      This header defines internal BAM structures for prune
 *              big list function.
 */

#ifndef BAM_PRUNE_BIG_LIST_INT_H_
#define BAM_PRUNE_BIG_LIST_INT_H_

#include <stdint.h>
#include <vcop.h>

#include "evealgframework.h"
#include "bam_prune_big_list.h"

#define NUM_IN_BLOCKS 2
#define NUM_OUT_BLOCKS 2
#define NUM_INTERNAL_BLOCKS 1

#define IN_LIST_IDX (BAM_PRUNE_BIG_LIST_INPUT_PORT_IN_LIST)
#define INDEX_LIST_IDX (BAM_PRUNE_BIG_LIST_INPUT_PORT_IDX_LIST)

#define OUT_LIST_IDX (BAM_PRUNE_BIG_LIST_OUTPUT_PORT_OUT_LIST)
#define OUT_LIST_SIZE (BAM_PRUNE_BIG_LIST_OUTPUT_PORT_SIZE_OUT)

#define PARAMS_IDX (BAM_PRUNE_BIG_LIST_TEMP_PARAM)

typedef struct bam_prune_big_list_context
{
    /* Must always follow this order: pInternalBlock[], pInBlock[], pOutputBlock[], args */
    void *pInternalBlock[NUM_INTERNAL_BLOCKS];
    void *pInBlock[NUM_IN_BLOCKS];
    void *pOutBlock[NUM_OUT_BLOCKS];
    BAM_Prune_Big_List_Args kernelArgs;
    void *pInBlockBase_INDEX_LIST ;
} BAM_Prune_Big_List_Context;

#endif /* BAM_PRUNE_BIG_LIST_INT_H_ */
