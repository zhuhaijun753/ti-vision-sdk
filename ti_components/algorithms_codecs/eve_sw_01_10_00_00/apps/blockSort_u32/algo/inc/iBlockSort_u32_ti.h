/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       iblockSort_u32_ti.h
 *
 *  @brief      This file defines the ivision interface for block sort Applet
 *  @version 0.0 (Dec 2013) : Base version.
 */

/** @ingroup    iBLOCK_SORT_U32 */
/*@{*/
#ifndef IBLOCK_SORT_U32_TI_H
#define IBLOCK_SORT_U32_TI_H

#include <ivision.h>
#include <ti/xdais/ires.h>
#include <stdint.h>

#define BLOCKSORTU32_MAX_ELEMTS 2048    /* Current max number of elements that can be sorted per block is 2048 */

/**
 * @brief The unique const funtion table for the BLOCK_SORT_U32_TI.
 */
extern const IVISION_Fxns BLOCK_SORT_U32_TI_VISION_FXNS;

/**
 * @brief IRES interface of the BLOCK_SORT_U32_TI_ algorithm
 */
extern const IRES_Fxns BLOCK_SORT_U32_TI_IRES;

/**

  @struct BLOCK_SORT_U32_TI_CreateParams
  @brief  This structure contains all the parameters which controls
          block sort applet at create time

  @param  visionParams
          Common parmeters for all ivison based modules

  @param  imgFrameWidth
          Width in bytes for the input image

  @param  imgFrameHeight
          height in number of lines for the input image

 @param  blockWidth
         width of each block to be sorted. 

 @param  blockHeight
         height of each block to be sorted

 @param  singleBlockSrcAddr
         If blockWidth== imgFrameWidth and blockHeight= imgFrameHeight then only one block needs to be processed. 
         Data can already be residing in VCOP's image buffer, to bypass EDMA. 
         Use this member to specify the source address of the data, in image buffer low.

 @param  singleBlockDstAddr
         If blockWidth== imgFrameWidth and blockHeight= imgFrameHeight then only one block needs to be processed. 
         Data can already be residing in VCOP's image buffer, to bypass EDMA. 
         Use this member to specify the destination address of where the data should be written to in image buffer high.

 */
typedef struct
{
    IVISION_Params visionParams;
    uint16_t imgFrameWidth;
    uint16_t imgFrameHeight;
    uint16_t blockWidth;
    uint16_t blockHeight;
    uint32_t *singleBlockSrcAddr;
    uint32_t *singleBlockDstAddr;
} BLOCK_SORT_U32_TI_CreateParams;


/**

  @struct BLOCK_SORT_U32_TI_outArgs
  @brief  This structure contains all the parameters which controls
          the applet at create time

  @param  visionParams
          Common outArgs for all ivison based modules

  @param  activeImgWidth
          Width in bytes of the area that will be accessed by the EDMA when reading the frame.
          For this function, it should always be equal to (imgFrameWidth)

  @param  activeImgHeight
          Height in number of rows of the area that will be accessed by the EDMA when reading the frame.
          For this function, it should always be equal to (imgFrameHeight)

  @param  outputBlockWidth
          Output block width in number of pixels returned by BAM_createGraph(). For this function, it will always be equal to blockWidth set at creation time.

  @param  outputBlockheight
          Output block height in number of rows returned by BAM_createGraph(). For this function, it will always be equal to blockHeight set at creation time.

 */

typedef struct
{
    IVISION_OutArgs iVisionOutArgs;
    uint16_t activeImgWidth;
    uint16_t activeImgHeight;
    uint16_t outputBlockWidth;
    uint16_t outputBlockHeight;

} BLOCK_SORT_U32_TI_outArgs;

/*@}*/
/* iBLOCK_SORT_U32 */

#endif /*IBLOCK_SORT_U32_TI_H */
/*==========================================================================*/
/*     END of the FILE                                                      */
/*==========================================================================*/


