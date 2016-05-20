/** ===========================================================================
* @file   edma3lld_support.h
*
* @path   $(STARTERWAREPATH)/inc
*
* @desc   This header defines functions to integrate EDMA3LLD with Starterware
*
* =====================================================================
* Copyright (c) Texas Instruments Inc 2013
*
* Use of this software is controlled by the terms and conditions found
* in the license agreement under which this software has been supplied
* ===========================================================================*/

#ifndef EDMA3LLD_SUPPORT_H_
#define EDMA3LLD_SUPPORT_H_

#include "stdint.h"
#include "edma_baseaddr.h"
#include "dma_resource.h"

#ifdef USE_EDMA3LLD
#include "edma3_rm.h"
#else
typedef void *EDMA3_RM_Handle;
#endif


/* ==================================================
 *  @func   EDMA3LLD_SUPPORT_requestResources
 *
 *  @desc   This functions useses EDMA3 LLD library for requesting EDMA resources.
 *
 *  @modif    This function modifies edmaResources structure
 *
 *  @inputs   This function takes following Inputs
 *              edma3RmHandle:
 *                  Handle to EDMA3LLD resource manager
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
int32_t EDMA3LLD_SUPPORT_requestResources(
                              EDMA3_RM_Handle    edma3RmHandle,
                              CSL_EdmaccRegsOvly edmaCc,
                              DMA_resourceStruct * edmaResources);


/* ==================================================
 *  @func   EDMA3LLD_SUPPORT_releaseResources
 *
 *  @desc   This functions useses EDMA3 LLD library for releasing requested EDMA resources.
 *
 *  @modif    This function modifies internal global resource structure
 *
 *  @inputs   This function takes following Inputs
 *              edma3RmHandle:
 *                  Handle to EDMA3LLD resource manager
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
int32_t EDMA3LLD_SUPPORT_releaseResources(
                              EDMA3_RM_Handle    edma3RmHandle,
                              CSL_EdmaccRegsOvly edmaCc,
                              DMA_resourceStruct * edmaResources);

#endif /* EDMA3LLD_SUPPORT_H_ */
