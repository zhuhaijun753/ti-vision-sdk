/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       ieve_integral_image_ti.h
 *
 *  @brief      This file defines the interface for integral Image Applet
 *  @version 0.0 (Jul 30, 2014) : Base version.
 */

/** @ingroup    ti_ivision_INTEGRAL_IMAGE */
/*@{*/
#ifndef IEVE_INTEGRAL_IMAGE_TI_H
#define IEVE_INTEGRAL_IMAGE_TI_H

#include <ivision.h>
#include <ti/xdais/ires.h>

/**
 * @brief The unique const funtion table for the INTEGRAL_IMAGE_TI.
 */
extern const IVISION_Fxns INTEGRAL_IMAGE_TI_VISION_FXNS;

/**
* @brief IRES interface of the INTEGRAL_IMAGE_TI_ algorithm
*/
extern const IRES_Fxns INTEGRAL_IMAGE_TI_IRES;

/**
    @brief  User provides most of the information through buffer descriptor 
            during process call. Below enums define the purpose of buffer
            There is 1 input buffers descriptor
            
            INTEGRAL_IMAGE_BUFDESC_IN_IMAGEBUFFER: This buffer descriptor provides the
            actual 8-bits image data required by algorithm. 
*/
typedef enum 
{
    INTEGRAL_IMAGE_BUFDESC_IN_IMAGEBUFFER = 0,
    INTEGRAL_IMAGE_BUFDESC_IN_TOTAL
} INTEGRAL_IMAGE_InBufOrder ;
   
/**
    @brief  User provides most of the information through buffer descriptor 
            during process call. Below enums define the purpose of out buffer
            There is 1 input buffers descriptor
            
            INTEGRAL_IMAGE_BUFDESC_OUT: This buffer is filled up by the algorithm and will contain 
            the inegral image output.
*/
typedef enum 
{
    INTEGRAL_IMAGE_BUFDESC_OUT = 0,
    INTEGRAL_IMAGE_BUFDESC_OUT_TOTAL
} INTEGRAL_IMAGE_OutBufOrder ;

/**

  @struct INTEGRAL_IMAGE_TI_CreateParams
  @brief  This structure contains all the parameters which controls
          Integral Image applet at create time

  @param  visionParams
          Common parmeters for all ivison based modules

  @param  imgFrameWidth
          Width in bytes for the input image

  @param  imgFrameHeight
          Width in bytes for the input image

*/
typedef struct
{
  IVISION_Params visionParams;
  uint32_t imgFrameWidth;
  uint32_t imgFrameHeight;
} INTEGRAL_IMAGE_TI_CreateParams;

/**

  @struct INTEGRAL_IMAGE_TI_outArgs
  @brief  This structure contains all the parameters which controls
          the applet at create time

  @param  iVisionOutArgs
          Common outArgs for all ivison based modules

  @param  blockWidth
          Processing block width in number of pixels returned by BAM_createGraph(). That's useful information to understand performance.

  @param  blockheight
          Processing block height in number of rows returned by BAM_createGraph(). That's useful information to understand performance.

 */

typedef struct
{
    IVISION_OutArgs iVisionOutArgs;
    uint16_t blockWidth;
    uint16_t blockHeight;

} INTEGRAL_IMAGE_TI_outArgs;

/*@}*/
/* ti_ivision_INTEGRAL_IMAGE */

#endif /*IEVE_INTEGRAL_IMAGE_TI_H */
/*==========================================================================*/
/*     END of the FILE                                                      */
/*==========================================================================*/


