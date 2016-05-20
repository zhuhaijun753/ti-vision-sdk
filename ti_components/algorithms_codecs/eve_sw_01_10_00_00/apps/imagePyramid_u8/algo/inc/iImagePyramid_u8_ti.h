/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       iImagePyramid_u8_ti.h
 *
 *  @brief      This file defines the ivision interface for image pyramid detection Applet
 *  @version 0.0 (Dec 2013) : Base version.
 */

/** @ingroup    iIMAGEPYRAMID_U8 */
/*@{*/
#ifndef IIMAGE_PYRAMID_U8_TI_H
#define IIMAGE_PYRAMID_U8_TI_H

#include <ivision.h>
#include <ti/xdais/ires.h>
#include <stdint.h>

#define IMGPYRAMID_MAX_NUM_LEVELS (5U)

/**
 * @brief The unique const funtion table for the IMAGE_PYRAMID_U8_TI.
 */
extern const IVISION_Fxns IMAGE_PYRAMID_U8_TI_VISION_FXNS;

/**
 * @brief IRES interface of the IMAGE_PYRAMID_U8_TI_ algorithm
 */
extern const IRES_Fxns IMAGE_PYRAMID_U8_TI_IRES;

typedef enum {
    IMAGE_PYRAMID_U8_TI_2x2_AVERAGE= 0,
    IMAGE_PYRAMID_U8_TI_5x5_GAUSSIAN= 1,
    IMAGE_PYRAMID_U8_TI_MAX= 2
} IMAGE_PYRAMID_U8_TI_FilterType;
/**

  @struct IMAGE_PYRAMID_U8_TI_CreateParams
  @brief  This structure contains all the parameters which controls
          FAST9 corner detect applet at create time

  @param  visionParams
          Common parmeters for all ivison based modules

  @param  imgFrameWidth
          Width in bytes for the input image

  @param  imgFrameHeight
          height in number of lines for the input image

  @param  numLevels
          Number of image pyramid levels

  @param  filterType
          Filter type can be IMAGE_PYRAMID_U8_TI_2x2_AVERAGE or IMAGE_PYRAMID_U8_TI_5x5_GAUSSIAN

 */
typedef struct
{
    IVISION_Params visionParams;
    uint16_t imgFrameWidth;
    uint16_t imgFrameHeight;
    uint8_t numLevels;
    uint8_t filterType;
} IMAGE_PYRAMID_U8_TI_CreateParams;


/**

  @struct IMAGE_PYRAMID_U8_TI_outArgs
  @brief  This structure contains all the parameters which controls
          the applet at create time

  @param  visionParams
          Common outArgs for all ivison based modules

  @param  activeImgWidth
          Width in bytes of the area that will be accessed by the EDMA when reading the frame.
          For this function, it should always be equal to (imgFrameWidth + TOTAL_FILTER_SZ)

  @param  activeImgHeight
          Height in number of rows of the area that will be accessed by the EDMA when reading the frame.
          For this function, it should always be equal to (imgFrameHeight + TOTAL_FILTER_SZ)

  @param  outputBlockWidth
          Output block width in number of pixels returned by BAM_createGraph(). That's useful information to understand performance.

  @param  outputBlockheight
          Output block height in number of rows returned by BAM_createGraph(). That's useful information to understand performance.

 */

typedef struct
{
    IVISION_OutArgs iVisionOutArgs;
    uint16_t activeImgWidth;
    uint16_t activeImgHeight;
    uint16_t outputBlockWidth;
    uint16_t outputBlockHeight;

} IMAGE_PYRAMID_U8_TI_outArgs;

/*@}*/
/* iIMAGE_PYRAMID_U8 */

#endif /*IIMAGE_PYRAMID_U8_TI_H */
/*==========================================================================*/
/*     END of the FILE                                                      */
/*==========================================================================*/


