/** ===========================================================================
* @file   dma_resource_allocator.h
*
* @path   $(STARTERWAREPATH)/inc
*
* @desc   This header defines functions to allocate EDMA resources. It is to be
*         noted that this resource manager doesn't support multiple instaces.
*
* =====================================================================
* Copyright (c) Texas Instruments Inc 2013
*
* Use of this software is controlled by the terms and conditions found
* in the license agreement under which this software has been supplied
* ===========================================================================*/

#ifndef DMA_RESOURCE_ALLOCATOR_H
#define DMA_RESOURCE_ALLOCATOR_H

#pragma CHECK_MISRA ("none")
#include "csl_edma.h"
#pragma RESET_MISRA ("required")

#pragma CHECK_MISRA ("none")
#include "stdint.h"
#pragma RESET_MISRA ("required")

#include "dma_resource.h"
#include "edma3lld_support.h"

/* ==================================================
 *  @func     DMA_resourceAllocator_setEdma3RmHandle
 *
 *  @desc     This functions set the resource manager Handle. A value of NULL
 *                is also a valid value for this function. For NUL handle we dont use
 *                EDMA3 LLD for resource allocation
 *
 *  @modif    This function modifies internal global resource structure
 *
 *  @inputs   NONE
 *
 *  @outputs  NONE
 *
 *  @return   NONE
 *
 *  =======================================================
 */
void DMA_resourceAllocator_setEdma3RmHandle(EDMA3_RM_Handle edma3RmHandle);

/* ==================================================
 *  @func     DMA_resourceAllocator_initResources
 *
 *  @desc     This functions initializes resets all the allocated resources
 *            of EDMA. After this call all the EDMA resources are freshly
 *            available
 *
 *  @modif    This function modifies internal global resource structure
 *
 *  @inputs   NONE
 *
 *  @outputs  NONE
 *
 *  @return   NONE
 *
 *  =======================================================
 */
void DMA_resourceAllocator_initResources(void);


/* ==================================================
 *  @func   DMA_resourceAllocator_allocateResources
 *
 *  @desc   This functions allocates EDMA resources for given number of
 *          channels. It also needs to know the EDMA attribute
 *          (EDMA/QDMA channel). How many param sets needed for each
 *          channel and which hardware que each channel should go to.
 *
 *  @modif    This function modifies edmaResources structure
 *
 *  @inputs   This function takes following Inputs
 *              edmaCc :
 *                  Pointer to the address space of EDMA module.
 *
 *              edmaResources :
 *                  Pointer to the resource structure defined in dma_resource.h.
 *                  User is expected to populate following fields of this
 *                  structure as an input and resourceAllocator will  populate
 *                  the remaining fields.
 *                      Input :
 *                          numChannels,
 *
 *                          dmaAttr[for Each channel requested],
 *
 *                          numParam[for Each channel requested], a value of
 *                          -1 means use default value which is 1
 *
 *                          queNo[for Each channel requested], - a value of
 *                          -1 means use default value.
 *
 *                      Output :
 *                          logicalChannelNo[for Each channel requested],
 *
 *                          tccVal[for Each channel requested],
 *
 *                          baseParam[for Each channel requested]
 *
 *  @outputs  edmaResources:
 *                      Contains the resources allocated for all the channels
 *
 *  @return    0 : Success
 *             -1 : Failure
 *
 *  =======================================================
 */

int32_t DMA_resourceAllocator_allocateResources(
                                            CSL_EdmaccRegsOvly edmaCc,
                                            DMA_resourceStruct * edmaResources);


/* ==================================================
 *  @func   DMA_resourceAllocator_deallocateResources
 *
 *  @desc   This functions deallocates EDMA resources which are allocated using
 *          DMA_resourceAllocator_allocateResources API
 *
 *
 *  @modif    This function modifies internal global resource structure
 *
 *  @inputs   This function takes following Inputs
 *              edmaCc :
 *                  Pointer to the address space of EDMA module.
 *
 *              edmaResources :
 *                  Pointer to the resource structure allocated using
 *                  DMA_resourceAllocator_allocateResources API
 *                          baseParam[for Each channel requested]
 *
 *  @return    0 : Success
 *             -1 : Failure
 *
 *  =======================================================
 */
int32_t DMA_resourceAllocator_deallocateResources(
                                            CSL_EdmaccRegsOvly edmaCc,
                                            const DMA_resourceStruct * edmaResources);


#endif /* DMA_RESOURCE_ALLOCATOR_H*/
/*!
*! Revision History
*! ================
*! 16-Oct-2013   Anshu: Initial Draft
*/

