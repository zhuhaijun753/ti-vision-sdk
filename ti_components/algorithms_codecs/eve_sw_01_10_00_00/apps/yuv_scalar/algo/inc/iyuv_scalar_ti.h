/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       iyuv_scalar_ti.h
 *
 *  @brief      This file defines the ivision interface for YUV Scalar Applet
 *  @version 0.0 (Mar 2014) : Base version.
 */

/** @ingroup    iYUV_SCALAR */
/*@{*/
#ifndef IYUV_SCALAR_TI_H
#define IYUV_SCALAR_TI_H

#include <ivision.h>
#include <ti/xdais/ires.h>
#include <stdint.h>


/**
 * @brief The unique const funtion table for the YUV_SCALAR_TI.
 */
extern const IVISION_Fxns YUV_SCALAR_TI_VISION_FXNS;

/**
 * @brief IRES interface of the YUV_SCALAR_TI_ algorithm
 */
extern const IRES_Fxns YUV_SCALAR_TI_IRES;


/**
  @brief  Below enums define the types supported scaling methods

  YUV_SCALAR_TI_METHOD_BI_LINEAR_INTERPOLATION: Bi-Linear interpolation based scaling

*/typedef enum
{
  YUV_SCALAR_TI_METHOD_BI_LINEAR_INTERPOLATION,
  YUV_SCALAR_TI_METHOD_MAX
} YUV_SCALAR_TI_ScalingMethods; 

/**

  @struct YUV_SCALAR_TI_CreateParams
  @brief  This structure contains all the parameters which YUV scalar
          applet at create time

  @param  visionParams
          Common parmeters for all ivison based modules

  @param  maxWidth
         The maximum output width. 

  @param  maxWidth
         The maximum output height. 

  @param  scaleRatioQ12
             Scalaing rati in Q12 format. 
  @param  scalingMethod
          Scaling methos to be used. Refer 
           YUV_SCALAR_TI_ScalingMethods for suported methods
  @param  fracQFmt 
          Q format for fraction pixel location represenatation (as well as filter co-efficients). 
  @param  outStartX
          Horizontal offset in the ouput image (Refer the user guide for more information)

  @param  outStartY
          Vertical offset in the ouput image (Refer the user guide for more information)

 */
typedef struct
{
    IVISION_Params visionParams;
    uint16_t maxWidth;
    uint16_t maxHeight;
    uint16_t scaleRatioQ12;
    uint8_t  scalingMethod;
    uint8_t  fracQFmt;
    uint16_t outStartX;
    uint16_t outStartY;
} YUV_SCALAR_TI_CreateParams;




/**

  @struct YUV_SCALAR_TI_InArgs
  @brief  This structure contains all the parameters which controls
          the applet at create time

  @param  iVisionInArgs
          Common inArgs for all ivison based modules
 */

typedef struct
{
    IVISION_InArgs iVisionInArgs;
} YUV_SCALAR_TI_InArgs;

/**

  @struct YUV_SCALAR_TI_outArgs
  @brief  This structure contains all the parameters which controls
          the applet at create time

  @param  visionParams
          Common outArgs for all ivison based modules
 */

typedef struct
{
    IVISION_OutArgs iVisionOutArgs;
} YUV_SCALAR_TI_outArgs;

/*@}*/
/* iYUV_SCALAR */

#endif /*IYUV_SCALAR_TI_H */
/*==========================================================================*/
/*     END of the FILE                                                      */
/*==========================================================================*/


