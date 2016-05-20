/** ===========================================================================
* @file   edma3lld_support.c
*
* @path   $(STARTERWAREPATH)/drivers/src/
*
* @desc   This  File contains functions to use EDMA3_LLD to allocate
*             resources related to EDMA
*
* =====================================================================
* Copyright (c) Texas Instruments Inc 2013
*
* Use of this software is controlled by the terms and conditions found
* in the license agreement under which this software has been supplied
*/

#include "edma3lld_support.h"

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
                              DMA_resourceStruct * edmaResources)
{
  int32_t     status = 0;

#ifdef USE_EDMA3LLD
  uint32_t    channelCnt;
  EDMA3_RM_ResDesc resDesc;
  EDMA3_RM_Result  edma3RmResult = EDMA3_RM_SOK;

  for ( channelCnt = 0 ; channelCnt < edmaResources->numChannels ; channelCnt++ )
  {
      if ( edmaResources->dmaAttr[channelCnt] == DMA_CHAN_ATTR_EDMA)
      {
          resDesc.resId = EDMA3_RM_RES_ANY;
          resDesc.type  = EDMA3_RM_RES_DMA_CHANNEL;
          edma3RmResult = EDMA3_RM_allocResource(edma3RmHandle, &resDesc);
      }
      else
      {
          resDesc.resId = EDMA3_RM_RES_ANY;
          resDesc.type  = EDMA3_RM_RES_QDMA_CHANNEL;
          edma3RmResult = EDMA3_RM_allocResource(edma3RmHandle, &resDesc);
      }

      if ( edma3RmResult != EDMA3_RM_SOK )
      {
        status = -1;
        break;
      }
      edmaResources->logicalChannelNo[channelCnt] = resDesc.resId;

      resDesc.resId = EDMA3_RM_RES_ANY;
      resDesc.type  = EDMA3_RM_RES_TCC;
      edma3RmResult |= EDMA3_RM_allocResource(edma3RmHandle, &resDesc);
      if ( edma3RmResult != EDMA3_RM_SOK )
      {
        status = -1;
        break;
      }
      edmaResources->tccVal[channelCnt] = resDesc.resId;

      resDesc.resId =  EDMA3_RM_RES_ANY;
      resDesc.type  =  EDMA3_RM_RES_PARAM_SET;
      edma3RmResult |=  EDMA3_RM_allocContiguousResource(edma3RmHandle,
                                  &resDesc,
                                  edmaResources->numParam[channelCnt]);

      if ( edma3RmResult != EDMA3_RM_SOK )
      {
        status = -1;
        break;
      }

      edmaResources->baseParam[channelCnt] =
                (volatile uint32_t *) &edmaCc->PARAMENTRY[resDesc.resId];

  }
#endif

   return status;
}

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
                              DMA_resourceStruct * edmaResources)
{
  int32_t     status = 0;

#ifdef USE_EDMA3LLD
  uint32_t    channelCnt;

  EDMA3_RM_ResDesc resDesc;
  EDMA3_RM_Result  edma3RmResult = EDMA3_RM_SOK;

  for ( channelCnt = 0 ; channelCnt < edmaResources->numChannels ; channelCnt++ )
  {
      if ( edmaResources->dmaAttr[channelCnt] == DMA_CHAN_ATTR_EDMA)
      {
          resDesc.resId = edmaResources->logicalChannelNo[channelCnt];
          resDesc.type  = EDMA3_RM_RES_DMA_CHANNEL;
          edma3RmResult = EDMA3_RM_freeResource(edma3RmHandle, &resDesc);
      }
      else
      {
          resDesc.resId = edmaResources->logicalChannelNo[channelCnt];
          resDesc.type  = EDMA3_RM_RES_QDMA_CHANNEL;
          edma3RmResult = EDMA3_RM_freeResource(edma3RmHandle, &resDesc);
      }

      resDesc.resId = edmaResources->tccVal[channelCnt];
      resDesc.type  = EDMA3_RM_RES_TCC;
      edma3RmResult |= EDMA3_RM_freeResource(edma3RmHandle, &resDesc);

      resDesc.resId = ((uint32_t) edmaResources->baseParam[channelCnt] - (uint32_t)edmaCc->PARAMENTRY)
                      >> CSL_EDMACC_DCHMAP_PAENTRY_SHIFT;
      resDesc.type  = EDMA3_RM_RES_PARAM_SET;
      edma3RmResult |= EDMA3_RM_freeContiguousResource(edma3RmHandle, &resDesc,  edmaResources->numParam[channelCnt]);

  }

  if (edma3RmResult != EDMA3_RM_SOK )
  {
      status = -1;
  }
#endif
  return status;
}


