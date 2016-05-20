/** ===========================================================================
* @file   dma_resource.h
*
* @path   $(STARTERWAREPATH)/inc
*
* @desc   This  File contains the structure which dma_func API's expect from
*         the resource managere
*
* =====================================================================
* Copyright (c) Texas Instruments Inc 2013
*
* Use of this software is controlled by the terms and conditions found
* in the license agreement under which this software has been supplied
* ===========================================================================*/

#ifndef DMA_RESOURCE_H
#define DMA_RESOURCE_H

#include "edmacc_config.h"

/** ====================================================
 *  @name   DMA_chanAttr
 *
 *  @desc   Describes the attribute of a DMA channel ie whether its
 *                a EDMA channel or QDMA channel
 *
 *  @field  DMA_CHAN_ATTR_EDMA
 *             EDMA channel Attribute
 *
 *  @field  DMA_CHAN_ATTR_QDMA
 *             QDMA channel Attribute
 *  ====================================================
 */
typedef enum chan_attr
{
    DMA_CHAN_ATTR_EDMA,
    DMA_CHAN_ATTR_QDMA
} DMA_chanAttr;


/** ========================================================
 *  @name   DMA_ResourceStruct
 *
 *  @desc   This structure is common between EDMA and QDMA channels and is used
 *          to hold the resources allocated by the resource manager and is
 *          expected to be used by dma_funcs API's
 *
 *  @field  numChannels
 *              Number of channels for which resources have been allocated. This
 *              is an input to the request allocator
 *
 *  @field  dmaAttr[]
 *              DMA attribute for all numChannels (whether its EDMA transfer
 *              or QDMA transfer). Refer to enum DMA_chanAttr defined in
 *              this header  for valid values. This is an input to resource
 *              allocator
 *
 *  @field  numParam[]
 *              This stores the number of param set corresponding to a given
 *              channel number for all requested numChannels channels. This is
 *              an input to resource allocator
 *
 *  @field queNo[]
 *              This stores the que number corresponding to a given channel
 *              number for requested channel. This field is used to configure
 *              DMAQNUM (for EDMA channels) or QDMAQNUM (for QDMA channels).
 *              This is an input from resource allocator. It is to be noted that
 *              only last bit of this field is considered for configuring the
 *              Que. This is because we have only two ques.
 *
 * @field trigWordIndex[]
 *              The index of the param entry writing at which will trigger
 *              QDMA channel. This field is only valid for QDMA channels
 *              and is ignored for EDMA channels. Index can take value from
 *              0-7.
 *
 *  @field  logicalChannelNo[]
 *              This is logical channel number/event number allocated for
 *              channels requested. EDMA has only two physical channels but
 *              can support total 16 logical channels. In case of QDMA channel
 *              this field tells the actual QDMA channel number. In case of
 *              EDMA this field indicates the event that needs to be set in
 *              the event enable register. This field will be used to configure
 *              DCHMAP ( for EDMA channels) or QCHMAP (for QDMA chanenls).
 *              This is an output from resource allocator.
 *
 *  @field tccVal[]
 *              This stores the transfer completion code corresponding to
 *              a given channel number for channels requested. This field is
 *              configured using OPT[12:17] field of param set. This is an
 *              output from resource allocator.
 *
 *
 *  @field baseParam[]
 *              This stores the base param set corresponding to a given
 *              channel number for requested channel. Resource allocator
 *              should make sure to leave a space on numParam parameter sets
 *              after this base address for a particular channel.This is an
 *              output from resource allocator.
 *
 *  ===============================================================
 */
typedef struct dma_resourceStruct
{
    uint8_t            numChannels;
    uint8_t            dmaAttr[NUM_MAX_CHANNELS];
    uint8_t            numParam[NUM_MAX_CHANNELS];
    uint8_t            queNo[NUM_MAX_CHANNELS];
    uint8_t            trigWordIndex[NUM_QDMA_CHANNELS];
    uint8_t            logicalChannelNo[NUM_MAX_CHANNELS];
    uint8_t            tccVal[NUM_MAX_CHANNELS];
    volatile uint32_t   *baseParam[NUM_MAX_CHANNELS];
}DMA_resourceStruct;

#endif /* DMA_RESOURCE_H */

/*!
*! Revision History
*! ================
*! 16-Oct-2013   Anshu: Initial Draft
*/

