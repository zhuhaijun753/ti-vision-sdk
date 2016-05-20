/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       iglcm_ti.h
 *
 *  @brief      This file defines the ivision interface for Gray-level
 *              Co-occurrence matrix applet
 *
 *  @version 0.1 (Jan 2014) : Base version.
 */

/** @ingroup    ti_ivision_GLCM */
/*@{*/
#ifndef IGLCM_TI_H_
#define IGLCM_TI_H_

#include <ivision.h>
#include <ti/xdais/ires.h>

/**
 * @brief The unique const funtion table for the GLCM_TI.
 */
extern const IVISION_Fxns GLCM_TI_VISION_FXNS;

/**
* @brief IRES interface of the GLCM_TI algorithm
*/
extern const IRES_Fxns GLCM_TI_IRES;

/**
* @brief Maximum number of directions that can be analysed together
*/
#define GLCM_MAX_NUM_DIRECTIONS   (8U)


typedef enum
{
  IGLCM_ERRORTYPE_MAXNUMDIRECTIONS_EXCEEDED = IALG_CUSTOMFAILBASE,
  IGLCM_ERRORTYPE_INSUFFICIENT_MEMORY

} IGLCM_ErrorType;

/**
  @brief User provides most of the infomration through buffer descriptor
         during process call. Below enums define the purpose of buffer

  GLCM_TI_BUFDESC_IN_IMAGEBUFFER: This buffer descriptor provides the
  actual image data required by applet.

*/

typedef enum
{
  GLCM_TI_BUFDESC_IN_IMAGEBUFFER = 0,
  GLCM_TI_BUFDESC_IN_TOTAL
} IGlcm_InBufOrder ;


/**
  @brief User provides most of the infomration through buffer descriptor
         during process call. Below enums define the purpose of out buffer

  GLCM_TI_BUFDESC_OUT_GLCM:
  This buffer descriptor (outBufs->bufDesc[GLCM_TI_BUFDESC_OUT_GLCM]) should
  point to a buffer capable of holding the GLCM outputs for all the different
  offsets required by the user. So the size of this buffer is
  2*numDirections*(numLevels)^2 bytes

*/

typedef enum
{
  GLCM_TI_BUFDESC_OUT_GLCM = 0,
  GLCM_TI_BUFDESC_OUT_TOTAL
} IGlcm_OutBufOrder ;

/**

  @struct GLCM_TI_CreateParams
  @brief  This structure contains all the parameters which controls
          GLCM applet at create time

  @param  visionParams
          Common parmeters for all ivison based modules

  @param  imageWidth
          Width in bytes for the input image

  @param  imageHeight
          height in number of lines for the input image

  @param  loPixelVal
          Lowest pixel value in the image. All pixels less than loPixelVal will
          be put into the first bin (0).

  @param  hiPixelVal
          Highest pixel value in the image. All pixels more than hiPixelVal
          will be binned into the last bin (numLevels-1).

  @param  numLevels
          Number of gray-levels to be used for GLCM computation, The maximum numLevels
          permitted by the applet is GLCM_TI_MAXNUMLEVELS.

  @param  numDirections
          Number of directions over which analysis need to be performed. At a time
          a maximum of GLCM_MAX_NUM_DIRECTIONS directions can be analysed together.
          The directions of analysis is specified as a pair of (row offset,
          column offset). Clubbing multiple directions of analysis together can
          lead to few pixels in the right and bottom border not voting into the
          output GLCM.

  @param  rowOffset
          Array of number of rows between the pixel of interest and its neighbor.
          The array should contain as many elements as numDirections.

  @param  colOffset
          Array of number of columns between the pixel of interest and its neighbor.
          The array should contain as many elements as numDirections.

*/

typedef struct
{
  IVISION_Params visionParams;
  uint16_t       imageWidth;
  uint16_t       imageHeight;
  uint8_t        loPixelVal;
  uint8_t        hiPixelVal;
  uint8_t        numLevels;
  uint8_t        numDirections;
  int8_t        *rowOffset;
  int8_t        *colOffset;
} GLCM_TI_CreateParams;


/*@}*/
/* ti_ivision_GLCM */

#endif /*IGLCM_TI_H_ */
/*==========================================================================*/
/*     END of the FILE                                                      */
/*==========================================================================*/

