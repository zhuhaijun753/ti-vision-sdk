/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_select_list_elements_int.h
 *
 *  @brief      This header defines internal structures for integrating select list elements
 *              kernel into BAM.
 */
#ifndef BAM_SELECT_LIST_ELEMENTS_INT_H_
#define BAM_SELECT_LIST_ELEMENTS_INT_H_

#include <stdint.h>
#include <vcop.h>

#include "evealgframework.h"
#include "bam_select_list_elements.h"

typedef enum
{
  SELECT_LIST_ELEMENTS_INTERNAL_PARAMS_IDX = 0,
  SELECT_LIST_ELEMENTS_INTERNAL_PBLOCK_UPDATE_PARAMS_IDX,
  SELECT_LIST_ELEMENTS_INTERNAL_SELECTION_MASK_PTR_IDX,
  SELECT_LIST_ELEMENTS_INTERNAL_NUM_BLOCK
} eBAM_SELECT_LIST_ELEMENTS_INTERNAL_BLOCKS;


typedef struct bam_select_list_elements_context
{
    /* Must always follow this order: pInternalBlock[], pInBlock[], pOutputBlock[], args */
    void *pInternalBlock[SELECT_LIST_ELEMENTS_INTERNAL_NUM_BLOCK];
    void *pInBlock[BAM_SELECT_LIST_ELEMENTS_NUM_INPUT_BLOCKS];
    void *pOutBlock[BAM_SELECT_LIST_ELEMENTS_NUM_OUTPUT_BLOCKS];
    BAM_Select_list_elements_Args     kernelArgs;
    BAM_Select_list_elements_ctrlArgs ctrlArgs;
    uint16_t                          blkIdx;
    uint16_t                          numBlks;
    uint16_t                          numElemsInLaskBlk;
} BAM_Select_list_elements_Context;

#endif /* BAM_SELECT_LIST_ELEMENTS_INT_H_ */

