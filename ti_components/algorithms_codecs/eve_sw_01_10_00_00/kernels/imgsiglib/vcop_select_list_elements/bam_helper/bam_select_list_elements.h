/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_select_list_elements.h
 *
 *  @brief      This header defines interfaces for integrating select list elements
 *              kernel into BAM.
 */

#ifndef BAM_SELECT_LIST_ELEMENTS_H_
#define BAM_SELECT_LIST_ELEMENTS_H_

#include "bam_kernel_interface.h"

typedef struct bam_select_list_elements_args
{
    uint16_t maxListChunkSize;
    uint16_t maxSelectionMaxSize;
} BAM_Select_list_elements_Args;

typedef struct bam_select_list_elements_ctrlArgs
{
    uint16_t listChunkSize;
    uint32_t listSize;
    uint16_t selectionMaskSize;
    uint8_t  *selectionMaskPtr;
} BAM_Select_list_elements_ctrlArgs;

extern BAM_KernelHelperFuncDef  gBAM_TI_selecListElementsHelperFunc;
extern BAM_KernelExecFuncDef    gBAM_TI_selecListElementsExecFunc;
extern BAM_KernelInfo           gBAM_TI_selecListElementsKernel;

typedef enum
{
  BAM_SELECT_LIST_ELEMENTS_INPUT_LIST_PORT= 0,
  BAM_SELECT_LIST_ELEMENTS_NUM_INPUT_BLOCKS
} eBAM_SELECT_LIST_ELEMENTS_INPUT_PORTS;

typedef enum
{
  BAM_SELECT_LIST_ELEMENTS_OUTPUT_LIST_PORT = 0,
  BAM_SELECT_LIST_ELEMENTS_OUTPUT_LIST_SIZE_PORT,
  BAM_SELECT_LIST_ELEMENTS_NUM_OUTPUT_BLOCKS
} eBAM_SELECT_LIST_ELEMENTS_OUTPUT_PORTS;

#endif /* BAM_SELECT_LIST_ELEMENTS_H_ */

