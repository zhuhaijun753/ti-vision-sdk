/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       ihough_for_lines_ti.h
 *
 *  @brief      This file defines the ivision interface for Hough for lines
 *               applet
 *  @version 0.0 (July 2014) : Base version.
 */

/** @ingroup    ti_ivision_HOUGH_FOR_LINES */
/*@{*/
#ifndef IHOUGH_FOR_LINES_TI_H_
#define IHOUGH_FOR_LINES_TI_H_

#include <ivision.h>
#include <ti/xdais/ires.h>

/**
 * @brief The unique const funtion table for the HOUGH_FOR_LINES_TI.
 */
extern const IVISION_Fxns HOUGH_FOR_LINES_TI_VISION_FXNS;

/**
* @brief IRES interface of the HOUGH_FOR_LINES_TI_ algorithm
*/
extern const IRES_Fxns HOUGH_FOR_LINES_TI_IRES;

/**
* @brief Maximum size in terms of number of edge points of the list supported
*/
#define HOUGH_FOR_LINES_TI_MAXLISTSIZE   (65536)


/**
* @brief Maximum value of rhoMaxLength supported
*/
#define HOUGH_FOR_LINES_TI_MAXRHOLENGTH   (800U)


typedef enum
{
  IHOUGH_FOR_LINES_ERRORTYPE_THETA_BEYOND_RANGE = IALG_CUSTOMFAILBASE,
  IHOUGH_FOR_LINES_ERRORTYPE_INVALID_THETA_START_END,
  IHOUGH_FOR_LINES_ERRORTYPE_MAXRHOLENGTH_EXCEEDED,
  IHOUGH_FOR_LINES_ERRORTYPE_MAX_ERROR_CODE
} IHOUGH_FOR_LINES_ErrorType;

/**
  @brief User provides most of the infomration through buffer descriptor
         during process call. Below enums define the purpose of buffer

  HOUGH_FOR_LINES_TI_BUFDESC_IN_XY_LIST:
  This buffer descriptor (inBufs->bufDesc[HOUGH_FOR_LINES_TI_BUFDESC_IN_XY_LIST])
  should point to a  buf descriptor containing XY list of the edge points in an image. This list is
  expected to be in packed 32 bit format with X coordinate followed by Y coordinate for each
  edge point. Each X or Y is a 16  bit entry.
*/

typedef enum
{
  HOUGH_FOR_LINES_TI_BUFDESC_IN_XY_LIST = 0,
  HOUGH_FOR_LINES_TI_BUFDESC_IN_TOTAL
} IHOUGH_FOR_LINES_InBufOrder ;


/**
  @brief User provides most of the infomration through buffer descriptor
         during process call. Below enums define the purpose of out buffer

  HOUGH_FOR_LINES_TI_BUFDESC_OUT_RHO_THETA_SPACE:
  This buffer descriptor (outBufs->bufDesc[HOUGH_FOR_LINES_TI_BUFDESC_OUT_RHO_THETA_SPACE]) should
  point to the output buffer which will contain the output Hough Space of the input data


*/

typedef enum
{
  HOUGH_FOR_LINES_TI_BUFDESC_OUT_RHO_THETA_SPACE = 0,
  HOUGH_FOR_LINES_TI_BUFDESC_OUT_TOTAL
} IHOUGH_FOR_LINES_OutBufOrder ;

/**

  @struct HOUGH_FOR_LINES_TI_CreateParams
  @brief  This structure contains all the parameters needed
              at create time for this applet

*/

typedef struct
{
  IVISION_Params visionParams;
} HOUGH_FOR_LINES_TI_CreateParams;


/**

  @struct HOUGH_FOR_LINES_InArgs
  @brief  This structure contains all the parameters which are given as an
          input to Filter at frame level

  @param  iVisionInArgs
          Common InArgs  for all ivison based modules

  @param   listSize
            Size of the list of edge points in terms of number of points. This should be less than
            64k points.

  @param  thetaStart
              Starting theta in degrees for the region in which lines are supposed to be detected.
              Should be between 0 to 360

  @param  thetaEnd
                End theta in degrees for the region in which lines are supposed to be detected.
                Should be between 0 to 360

  @param  thetaStepSize
                Steps in which theta should be incremented while moving from thetaMin to thetaMax

  @param  rhoMaxLength
                Maximum rho value in rho theta space. rhoMaxLength should be less than the diameter
                of image. Also Max rhoMaxLength supported is HOUGH_FOR_LINES_TI_MAXRHOLENGTH

  @param  imgWidth
                Image frame width

  @param  imgHeight
                Image frame height

*/
typedef struct
{
  IVISION_InArgs  iVisionInArgs;
  uint16_t        listSize;
  uint16_t        thetaStart;
  uint16_t        thetaEnd;
  uint8_t         thetaStepSize;
  uint16_t        rhoMaxLength;
  uint16_t        imgWidth;
  uint16_t        imgHeight;
} HOUGH_FOR_LINES_InArgs;


/**

  @struct HOUGH_FOR_LINES_OutArgs
  @brief  This structure contains all the parameters which are given as an
          output by Filter  at frame level

  @param  iVisionOutArgs
          Common outArgs for all ivison based modules

*/
typedef struct
{
  IVISION_OutArgs iVisionOutArgs;
} HOUGH_FOR_LINES_OutArgs;

/*@}*/
/* ti_ivision_HOUGH_FOR_LINES */

#endif /*IHOUGH_FOR_LINES_TI_H_ */
/*==========================================================================*/
/*     END of the FILE                                                      */
/*==========================================================================*/

