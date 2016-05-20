/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
*  @file:       iblock_statistics_ti.h
*
*  @brief:      This file defines the ivision interface for Block Statistics
*               applet
*
*  @version:    0.2 (Aug 2014) : Base version.
*/

/** @ingroup    ti_iBLOCK_STATISTICS */
/*@{*/

#ifndef IBLOCK_STATISTICS_TI_H
#define IBLOCK_STATISTICS_TI_H

#include <ivision.h>
#include <ti/xdais/ires.h>

/**
 * @brief The unique const funtion table for the BLOCK_STATISTICS_TI.
 */
extern const IVISION_Fxns BLOCK_STATISTICS_TI_VISION_FXNS;

/**
* @brief IRES interface of the BLOCK_STATISTICS_TI algorithm
*/
extern const IRES_Fxns BLOCK_STATISTICS_TI_IRES;


typedef enum
{
  BLOCK_STATISTICS_TI_ERRORTYPE_INSUFFICIENT_MEMORY = IALG_CUSTOMFAILBASE

} BLOCK_STATISTICS_TI_ErrorType;

/**
  @brief User provides most of the infomration through buffer descriptor
         during process call. Below enums define the purpose of buffer

  BLOCK_STATISTICS_TI_BUFDESC_IN_IMAGEBUFFER: This buffer descriptor provides the
  image data for which statistics is required to be computed by the applet. The
  input image should be of uint8_t data type.

*/

typedef enum
{
  BLOCK_STATISTICS_TI_BUFDESC_IN_IMAGEBUFFER = 0,
  BLOCK_STATISTICS_TI_BUFDESC_IN_TOTAL
} BLOCK_STATISTICS_TI_InBufOrder;


/**
  @brief User provides most of the infomration through buffer descriptor
         during process call. Below enums define the purpose of out buffer

  BLOCK_STATISTICS_TI_BUFDESC_OUT_MIN: This buffer descriptor (outBufs->bufDesc
  [BLOCK_STATISTICS_TI_BUFDESC_OUT_MIN]) should point to a buffer capable of
  holding the block minimum output. This buffer should be of uint8_t type.

  BLOCK_STATISTICS_TI_BUFDESC_OUT_MAX: This buffer descriptor (outBufs->bufDesc
  [BLOCK_STATISTICS_TI_BUFDESC_OUT_MAX]) should point to a buffer capable of
  holding the block maximum output. This buffer should be of uint8_t type.

  BLOCK_STATISTICS_TI_BUFDESC_OUT_MEAN: This buffer descriptor (outBufs->bufDesc
  [BLOCK_STATISTICS_TI_BUFDESC_OUT_MEAN]) should point to a buffer capable of
  holding the block mean output. This buffer should be of uint16_t type.

  BLOCK_STATISTICS_TI_BUFDESC_OUT_VARIANCE: This buffer descriptor (outBufs->bufDesc
  [BLOCK_STATISTICS_TI_BUFDESC_OUT_VARIANCE]) should point to a buffer capable of
  holding the block variance output. This buffer should be of uint32_t type.
*/

typedef enum
{
  BLOCK_STATISTICS_TI_BUFDESC_OUT_MIN = 0,
  BLOCK_STATISTICS_TI_BUFDESC_OUT_MAX,
  BLOCK_STATISTICS_TI_BUFDESC_OUT_MEAN,
  BLOCK_STATISTICS_TI_BUFDESC_OUT_VARIANCE,
  BLOCK_STATISTICS_TI_BUFDESC_OUT_TOTAL
} BLOCK_STATISTICS_TI_OutBufOrder;

/**
  @struct BLOCK_STATISTICS_TI_CreateParams

  @brief  This structure contains all the parameters which controls
          BLOCK_STATISTICS applet at create time

  @param  visionParams
          Common parmeters for all ivison based modules

  @param  imageWidth
          Width in pixels of the input image

  @param  imageHeight
          Height of the input image

  @param  statBlockWidth
          Width of the block over which statistics has to be computed

  @param  statBlockHeight
          Height of the block over which statistics has to be computed
*/

typedef struct
{
  IVISION_Params visionParams;
  uint16_t       imageWidth;
  uint16_t       imageHeight;
  uint16_t       statBlockWidth;
  uint16_t       statBlockHeight;
} BLOCK_STATISTICS_TI_CreateParams;

/*@}*/
/* ti_iBLOCK_STATISTICS */

#endif  /* IBLOCK_STATISTICS_TI_H */
