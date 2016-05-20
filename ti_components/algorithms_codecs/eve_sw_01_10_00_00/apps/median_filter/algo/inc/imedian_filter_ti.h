/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
*  @file:       imedian_filter_ti.h
*
*  @brief:      This file defines the ivision interface for Median Filter
*               applet
*
*  @version:    0.2 (July 2014) : Base version.
*/

/** @ingroup    ti_iMEDIAN_FILTER */
/*@{*/

#ifndef IMEDIAN_FILTER_TI_H
#define IMEDIAN_FILTER_TI_H

#include <ivision.h>
#include <ti/xdais/ires.h>

/**
 * @brief The unique const funtion table for the MEDIAN_FILTER_TI.
 */
extern const IVISION_Fxns MEDIAN_FILTER_TI_VISION_FXNS;

/**
* @brief IRES interface of the MEDIAN_FILTER_TI algorithm
*/
extern const IRES_Fxns MEDIAN_FILTER_TI_IRES;


typedef enum
{
  IMEDIAN_FILTER_ERRORTYPE_INSUFFICIENT_MEMORY = IALG_CUSTOMFAILBASE

} IMEDIAN_FILTER_ErrorType;

/**
  @brief User provides most of the infomration through buffer descriptor
         during process call. Below enums define the purpose of buffer

  MEDIAN_FILTER_TI_BUFDESC_IN_IMAGEBUFFER: This buffer descriptor provides the
  actual image data required by applet.

*/

typedef enum
{
  MEDIAN_FILTER_TI_BUFDESC_IN_IMAGEBUFFER = 0,
  MEDIAN_FILTER_TI_BUFDESC_IN_TOTAL
} IMedianFilter_InBufOrder ;


/**
  @brief User provides most of the infomration through buffer descriptor
         during process call. Below enums define the purpose of out buffer

  MEDIAN_FILTER_TI_BUFDESC_OUT_IMAGEBUFFER:
  This buffer descriptor (outBufs->bufDesc[MEDIAN_FILTER_TI_BUFDESC_OUT_IMAGEBUFFER]) should
  point to a buffer capable of holding the MEDIAN_FILTER output.

*/

typedef enum
{
  MEDIAN_FILTER_TI_BUFDESC_OUT_IMAGEBUFFER = 0,
  MEDIAN_FILTER_TI_BUFDESC_OUT_TOTAL
} IMedianFilter_OutBufOrder ;

/**
  @brief Control Command indices for the MEDIAN_FILTER_TI algorithm

  TI_MEDIAN_FILTER_CONTROL_GET_BUF_SIZE
  The algorithm expects the input and output buffers to be satisfy certain
  contraints. These details are communicated to the user using a control
  call with this index. Given the input create time parameters, the control
  call return the buffer constraints through the output parameters of
  MEDIAN_FILTER_TI_CreateParams structure.

*/
typedef enum
{
  TI_MEDIAN_FILTER_CONTROL_GET_BUF_SIZE,
  TI_MEDIAN_FILTER_CONTROL_MAX
} TI_MEDIAN_FILTER_ControlCommand;

/**

  @struct MEDIAN_FILTER_TI_CreateParams
  @brief  This structure contains all the parameters which controls
          MEDIAN_FILTER applet at create time

  @param  visionParams
          Common parmeters for all ivison based modules

  @param  imageWidth
          Width in bytes for the input image

  @param  imageHeight
          height in number of lines for the input image

  @param  blockWidth
          Width of the block over which median has to be computed

  @param  blockHeight
          height of the block over which median has to be computed

  @param  stepSizeHorz
          Number of pixels by which the block has to be advanced horizontally

  @param  stepSizeVert
          Number of lines by which the block has to be advanced vertically

  @param  minInputBufHeight
          Minimum height expected for input buffer. The algorihtm will
          access the extra lines after valid imageHeight during
          processing, but the image content there will not effect the
          final output.

  @param  extraInputMem
          Extra number of bytes required after the last valid input
          pixel (for a buffer size of imageWidth by imageHeight).

  @param  minOutputBufStride
          Minimum output buffer stride (in bytes) expected to be provided
          to hold the output for the given input image dimension.

  @param  minOutputBufHeight
          Minimum height of the output buffer to hold processed output
          for the given input image dimension.

*/

typedef struct
{
  IVISION_Params visionParams;
  uint16_t       imageWidth;
  uint16_t       imageHeight;
  uint8_t        blockWidth;
  uint8_t        blockHeight;
  uint16_t       stepSizeHorz;
  uint16_t       stepSizeVert;
  
  /* Output parameters */
  uint16_t       minInputBufHeight;
  uint16_t       extraInputMem;
  uint16_t       minOutputBufStride;
  uint16_t       minOutputBufHeight;
} MEDIAN_FILTER_TI_CreateParams;

/*@}*/
/* ti_iMEDIAN_FILTER */

#endif  /* IMEDIAN_FILTER_TI_H */
