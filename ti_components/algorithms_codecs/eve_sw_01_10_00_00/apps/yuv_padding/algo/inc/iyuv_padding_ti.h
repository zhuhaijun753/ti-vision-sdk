/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       iyuv_padding_ti.h
 *
 *  @brief      This file defines the ivision interface for YUV Padding Applet
 *  @version 0.0 (Mar 2014) : Base version.
 */

/** @ingroup    iYUV_PADDING */
/*@{*/
#ifndef IYUV_PADDING_TI_H
#define IYUV_PADDING_TI_H

#include <ivision.h>
#include <ti/xdais/ires.h>
#include <stdint.h>


/**
 * @brief The unique const funtion table for the YUV_PADDING_TI.
 */
extern const IVISION_Fxns YUV_PADDING_TI_VISION_FXNS;

/**
 * @brief IRES interface of the YUV_PADDING_TI_ algorithm
 */
extern const IRES_Fxns YUV_PADDING_TI_IRES;

/**
 * @brief Buffer index for input image data
  This buffer width has to be greater than or equal to the
  processing width aligned to 64. This buffer height has to
  be greater than or equal to the processing height aligned to 64
 */
#define YUV_PADDING_TI_IN_IMAGE_BUF_IDX (0)

/**
 * @brief Buffer index for output input image data
  Both input and output will be pointing to same memory
  region with an offset for inplace padding use case
  This buffer width has to be greater than or equal to the
  processing width aligned to 64 + left and right padding. This buffer
  height has to be greater than or equal to the processing height
  aligned to 64 + top and bottom padding
 */
#define YUV_PADDING_TI_OUT_IMAGE_BUF_IDX (0)

/**

  @struct YUV_PADDING__TI_CreateParams
  @brief  This structure contains all the parameters which controls
          YUV Padding Applet at create time

  @param  visionParams
          Common parmeters for all ivison based modules

  @param  maxImageWidth
          MAximum image with supported

  @param  topPadding
          Number of row to be padded on top

  @param  leftPadding
          Number of coloms to be padded on left

  @param  BottomPadding
          Number of row to be padded on bottom

  @param  rightPadding
          Number of coloms to be padded on rignts


 */
typedef struct
{
    IVISION_Params visionParams;
    uint16_t maxImageWidth    ;
    uint16_t topPadding    ;
    uint16_t leftPadding   ;
    uint16_t rightPadding  ;
    uint16_t BottomPadding ;
} YUV_PADDING_TI_CreateParams;


/**

  @struct YUV_PADDINGTI_outArgs
  @brief  This structure contains all the parameters which controls
          the applet at create time

  @param  visionParams
          Common outArgs for all ivison based modules
 */

typedef struct
{
    IVISION_OutArgs iVisionOutArgs;
} YUV_PADDING_TI_outArgs;

/*@}*/
/* iYUV_PADDING */

#endif /*YUV_PADDING */
/*==========================================================================*/
/*     END of the FILE                                                      */
/*==========================================================================*/


