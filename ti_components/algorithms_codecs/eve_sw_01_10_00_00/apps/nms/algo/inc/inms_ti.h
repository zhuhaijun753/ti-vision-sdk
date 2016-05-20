/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       inms_ti.h
 *
 *  @brief      This file defines the ivision interface for Non Maximum Suppression (NMS)
 *               applet
 *  @version 0.0 (Aug 2014) : Base version.
 */

/** @ingroup    ti_ivision_NMS */
/*@{*/
#ifndef INMS_TI_H_
#define INMS_TI_H_

#include <ivision.h>
#include <ti/xdais/ires.h>

/**
 * @brief The unique const funtion table for the NMS_TI.
 */
extern const IVISION_Fxns NMS_TI_VISION_FXNS;

/**
* @brief IRES interface of the NMS_TI_ algorithm
*/
extern const IRES_Fxns NMS_TI_IRES;

typedef enum
{
  NMS_TI_ERRORTYPE_IMAGE_DIMENSION_UNSUPPORTED = IALG_CUSTOMFAILBASE,
  NMS_TI_ERRORTYPE_WIDTH_NON_MULTIPLE_OF_8,
  NMS_TI_ERRORTYPE_MAX_ERROR_CODE
} NMS_TI_ErrorType;

/*
 *  @brief  Depth of input data in terms of bytes
 */
typedef enum
{
  NMS_TI_INPUT_BYTE_DEPTH_16BIT = sizeof(uint16_t),
  NMS_TI_INPUT_BYTE_DEPTH_MAX
} NMS_TI_InputByteDepth;

/**
  @brief User provides most of the infomration through buffer descriptor
         during process call. Below enums define the purpose of buffer

  NMS_TI_BUFDESC_IN_IMAGEBUFFER:
  This buffer descriptor (inBufs->bufDesc[NMS_TI_BUFDESC_IN_IMAGEBUFFER])
  should point to a  buf descriptor pointing to input image data. Input image width
  and height should be multiple of 8

  NMS_TI_BUFDESC_IN_TOTAL :
  Total number of input buffers
*/

typedef enum
{
  NMS_TI_BUFDESC_IN_IMAGEBUFFER = 0,
  NMS_TI_BUFDESC_IN_TOTAL
} NMS_TI_InBufOrder ;


/**
  @brief User provides most of the infomration through buffer descriptor
         during process call. Below enums define the purpose of out buffer

  NMS_TI_BUFDESC_OUT_LIST_XY:
  This buffer descriptor (outBufs->bufDesc[NMS_TI_BUFDESC_OUT_LIST_XY]) should
  point to the output buffer which will contain XY list of the after NMS with thresholding.
  This list is expected to be in packed 32 bit format with X coordinate followed by Y
  coordinate for each  edge point. Each X or Y is a 16  bit entry.

  NMS_TI_BUFDESC_OUT_TOTAL:
  Total Number of output buffers

*/

typedef enum
{
  NMS_TI_BUFDESC_OUT_LIST_XY = 0,
  NMS_TI_BUFDESC_OUT_TOTAL
} NMS_TI_OutBufOrder ;

/**

  @struct NMS_TI_CreateParams
  @brief  This structure contains all the parameters needed
              at create time for this applet

  @brief  inputByteDepth
             Describes the bit depth for the input data. It can be 2 or 4  bytes.
             Refer INMS_InputByteDepth for valid enteries

*/

typedef struct
{
  IVISION_Params visionParams;
  uint8_t        inputByteDepth;
} NMS_TI_CreateParams;


/**

  @struct NMS_TI_ControlInArgs
  @brief  This structure contains all the parameters needed
             for control call of this applet

  @brief  imageBuf
             This is the input buffer which is provided in process call.
             Control function will determine the region for which this
             kernel would be running for the input dimensions given
             by the user. User is expected to allocate this much memory
             for inout buffer

 @param  windowWidth
                Width of the window for NMS

  @param  windowHeight
                Height of the window for NMS

*/
typedef struct
{
  IVISION_InBufs * imageBuf;
  uint8_t         windowWidth;
  uint8_t         windowHeight;
}NMS_TI_ControlInArgs;


/**

  @struct NMS_TI_ControlOutArgs
  @brief  This structure contains all the parameters that are
             returned by  control call of this applet

 @brief  effectiveImageWidth
            effective image width for which this applet is working. User should
             atleast allocate this much memory

 @brief  effectiveImageHeight
           effective image height for which this applet is working. User should
            atleast allocate this much memory

*/
typedef struct
{
  uint16_t         effectiveImageWidth;
  uint16_t         effectiveImageHeight;
}NMS_TI_ControlOutArgs;

/**

  @struct NMS_InArgs
  @brief  This structure contains all the parameters which are given as an
          input to this applet at frame level

  @param  iVisionInArgs
                Common InArgs  for all ivison based modules

  @param   nmsThreshold
                Threshold to be used with NMS

  @param  windowWidth
                Width of the window for NMS

  @param  windowHeight
                Height of the window for NMS
*/
typedef struct
{
  IVISION_InArgs  iVisionInArgs;
  int32_t         nmsThreshold;
  uint8_t         windowWidth;
  uint8_t         windowHeight;
} NMS_TI_InArgs;


/**

  @struct NMS_OutArgs
  @brief  This structure contains all the parameters which are given as an
          output by this applet  at frame level

  @param  iVisionOutArgs
             Common outArgs for all ivison based modules

@param  numListPoints
              Number of points in the list after NMS and thresholding

*/
typedef struct
{
  IVISION_OutArgs iVisionOutArgs;
  uint32_t         numListPoints;
} NMS_TI_OutArgs;

/*@}*/
/* ti_ivision_NMS */

#endif /*INMS_TI_H_ */
/*==========================================================================*/
/*     END of the FILE                                                      */
/*==========================================================================*/

