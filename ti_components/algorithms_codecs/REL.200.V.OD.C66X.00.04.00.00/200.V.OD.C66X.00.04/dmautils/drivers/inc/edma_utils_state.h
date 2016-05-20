/** ===========================================================================
* @file   dma_utils_state.h
*
* @path   $(STARTERWAREPATH)/drivers/inc
*
* @desc   This header is an internal header and is used to store the state
*         of edmaResources of all the EDMA usecases.
*
* =====================================================================
* Copyright (c) Texas Instruments Inc 2013
*
* Use of this software is controlled by the terms and conditions found
* in the license agreement under which this software has been supplied
* ===========================================================================*/

#ifndef DMA_UTILS_STATE_H
#define DMA_UTILS_STATE_H

#pragma CHECK_MISRA ("none")
#include "stdint.h"
#pragma RESET_MISRA ("required")

#include "edmacc_config.h"
#include "dma_resource.h"

/** ========================================================
 *  @name   DMA_utilsStateStruct
 *
 *  @desc   This structure maintains the state of dma resources allocated for
 *          EDMA utility usecases
 *
 *  @field logicalChanNo[]
 *              This stores the event corresponding to a given channel number for
 *              all channels
 *
 *  @field tccVal[]
 *              This stores the transfer completion code corresponding to a given
 *              channel number for all channels
 *
 *  @field baseParam
 *              This stores the base parameter(end of linked parameter)
 *              corresponding to a given channel number for all channels
 *
 *  ===============================================================
 */

typedef struct dma_utilsStateStruct
{
    int8_t              logicalChanNo[NUM_MAX_CHANNELS];
    int8_t              tccVal[NUM_MAX_CHANNELS];
    volatile uint32_t     *baseParam[NUM_MAX_CHANNELS];
} DMA_utilsStateStruct;

/* ==================================================
 *  @func   DMA_utils_resetStateStruct
 *
 *  @desc   This function reset the state structure for all the
 *          EDMA utility usecases
 *
 *
 *  @modif    This function modifies gDmaUtilsStateStruct structure
 *
 *  @inputs   NONE
 *
 *  @return   NONE
 *
 *  =======================================================
 */
void DMA_utils_resetStateStruct(void);


/* ==================================================
 *  @func   DMA_utils_updateStateStruct
 *
 *  @desc   This functions updates the state structure for Utilities
 *          based on the resources allocated by using resource Allocator
  *
 *  @modif    This function modifies gDmaUtilsStateStruct structure
 *
 *  @inputs   This function takes following Inputs
 *              edmaResources :
 *                  Pointer to the resource structure defined in dma_resource.h.
 *                  User is expected to populate following fields of this
 *                  structure as an input and resourceAllocator will  populate
 *                  the remaining fields.
 *  @outputs
 *              startIndex :
 *                  The index at which edmaResources are stored in utilsStateStruct
 *                  Usecase should be using this index to fetch the data
 *                  corresponding to it.
 *
 *  @return    0 : Success
 *             -1 : Failure
 *
 *  =======================================================
 */
int32_t DMA_utils_updateStateStruct(const DMA_resourceStruct * edmaResources , uint8_t * startIndex);

/* ==================================================
 *  @func   DMA_utils_freeStateStruct
 *
 *  @desc   This functions frees the state structure for Utilities
 *          based on the startIndex and numEnteries
 *
 *  @modif    This function modifies gDmaUtilsStateStruct structure
 *
 *  @inputs   This function takes following Inputs
 *              startIndex :
 *                  The index at which edmaResources are stored in utilsStateStruct
 *
 *              numEnteries :
 *                  Number of enteries that needs to be freed from utilsStateStruct
 *                  starting from startIndex
 *
 *  @return    NONE
 *
 *  =======================================================
 */
void DMA_utils_freeStateStruct(uint8_t startIndex , uint8_t numEnteries);


#endif /*DMA_UTILS_STATE_H*/
/*!
*! Revision History
*! ================
*! 16-Oct-2013   Anshu: Initial Draft
*/
