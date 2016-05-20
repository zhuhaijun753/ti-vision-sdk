/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       iharris_best_feature_to_front_ti.h
 *
 *  @brief      This file defines the ivision interface for Harris score based
 *              best feature to front applet
 *  @version 0.0 (Dec 2013) : Base version.
 */

/** @ingroup    ti_ivision_HARRIS_BEST_FEATURE_TO_FRONT */
/*@{*/
#ifndef IHARRIS_BEST_FEATURE_TO_FRONT_TI_H
#define IHARRIS_BEST_FEATURE_TO_FRONT_TI_H

#include <ivision.h>
#include <ti/xdais/ires.h>

/**
 * @brief The unique const funtion table for the HARRIS_BEST_FEATURE_TO_FRONT_TI.
 */
extern const IVISION_Fxns HARRIS_BEST_FEATURE_TO_FRONT_TI_VISION_FXNS;

/**
* @brief IRES interface of the HARRIS_BEST_FEATURE_TO_FRONT_TI_ algorithm
*/
extern const IRES_Fxns HARRIS_BEST_FEATURE_TO_FRONT_TI_IRES;

/**
* @brief Maximum number of features allowed by this applet across all levels
*/
#define HARRIS_BEST_FEATURE_TO_FRONT_TI_MAXNUMFEATURES   (2048U)

/**
* @brief Maximum number of levels allowed by this applet.
  This is currently restricted to 3 due to the nature of data arrangement of XY list
  assumed by prune list. The XY list for two different levels should lie with an
  offset of 2k points (8k bytes). Only 3 levels can fit into WBUF with this requirement.
  Also since currently it accepts the pyramids via IVISION BUF PLANES - it is restricted
  to IVISION_MAX_NUM_PLANES (4)
*/
#define HARRIS_BEST_FEATURE_TO_FRONT_TI_MAXNUMLEVELS     (3U)

typedef enum
{
  IHARRIS_BEST_FEATURE_TO_FRONT_ERRORTYPE_MAXNUMFEATURES_EXCEEDED = IALG_CUSTOMFAILBASE,
  IHARRIS_BEST_FEATURE_TO_FRONT_ERRORTYPE_MAXLEVELS_EXCEEDED

} IHARRIS_BEST_FEATURE_TO_FRONT_ErrorType;

/**
  @brief User provides most of the infomration through buffer descriptor
         during process call. Below enums define the purpose of buffer

  HARRIS_BEST_FEATURE_TO_FRONT_TI_BUFDESC_IN_IMAGEBUFFER: This buffer descriptor provides the
  actual image data required by applet. This applet works on multi level so
  user can provide multiple buffers. Lets say this applet is used for
  3 levels of image pyramid. then user should provide
  inBufs->bufDesc[HARRIS_BEST_FEATURE_TO_FRONT_TI_BUFDESC_IN_IMAGEBUFFER]->numPlanes = 3
  and
  inBufs->bufDesc[HARRIS_BEST_FEATURE_TO_FRONT_TI_BUFDESC_IN_IMAGEBUFFER]->bufPlanes[level] contains
  the details of each planes buffer pointer and dimensions

  HARRIS_BEST_FEATURE_TO_FRONT_TI_BUFDESC_IN_XY_LIST:
  This buffer descriptor (inBufs->bufDesc[HARRIS_BEST_FEATURE_TO_FRONT_TI_BUFDESC_IN_XY_LIST])
  should point to a  buf descriptor containing XY planes for different levels. This applet works
  on multi level so user can provide multiple buffers. Lets say this applet is used for
  3 levels of image pyramid. then user should provide
  inBufs->bufDesc[HARRIS_BEST_FEATURE_TO_FRONT_TI_BUFDESC_IN_XY_LIST]->numPlanes = 3
  and  inBufs->bufDesc[HARRIS_BEST_FEATURE_TO_FRONT_TI_BUFDESC_IN_XY_LIST]->bufPlanes[level]
  contains the pointers to that particuar level's XY list

  It is user responsbility to have the X and Y list to have valid data which points in
  image region excluding 4 pixels boarder on each side. The applet doesn't perfrom any check
  for this condition and the behavior is undefined if it is not satisfied.
  Since it is a 1D buffer, The size of list has to be indicated by
  inBufs->bufDesc[HARRIS_BEST_FEATURE_TO_FRONT_TI_BUFDESC_IN_XY_LIST]->bufPlanes[level].width* height
  for a 100 points - it should be 4*100 or 400*1

*/

typedef enum
{
  HARRIS_BEST_FEATURE_TO_FRONT_TI_BUFDESC_IN_IMAGEBUFFER = 0,
  HARRIS_BEST_FEATURE_TO_FRONT_TI_BUFDESC_IN_XY_LIST,
  HARRIS_BEST_FEATURE_TO_FRONT_TI_BUFDESC_IN_TOTAL
} IHarris_BFFT_InBufOrder ;


/**
  @brief User provides most of the infomration through buffer descriptor
         during process call. Below enums define the purpose of out buffer

  HARRIS_BEST_FEATURE_TO_FRONT_TI_BUFDESC_OUT_XY_LIST:
  This buffer descriptor (outBufs->bufDesc[HARRIS_BEST_FEATURE_TO_FRONT_TI_BUFDESC_OUT_XY_LIST]) should
  point to a plane capable of holding XY list of bestNFeaturesOut. so the size of this buffer is
  bestNFeaturesOut*(4) bytes

  HARRIS_BEST_FEATURE_TO_FRONT_TI_BUFDESC_OUT_LEVEL_ID:
  This buffer descriptor (outBufs->bufDesc[HARRIS_BEST_FEATURE_TO_FRONT_TI_BUFDESC_IN_LEVEL_ID]) should
  point to a plane capable of holding level corresponding to XY list. so the size of this buffer is
  bestNFeaturesOut*(1) bytes. There is 1:1 mapping in XY array and level array

*/

typedef enum
{
  HARRIS_BEST_FEATURE_TO_FRONT_TI_BUFDESC_OUT_XY_LIST = 0,
  HARRIS_BEST_FEATURE_TO_FRONT_TI_BUFDESC_OUT_LEVEL_ID,
  HARRIS_BEST_FEATURE_TO_FRONT_TI_BUFDESC_OUT_TOTAL
} IHarris_BFFT_OutBufOrder ;

/**

  @struct HARRIS_BEST_FEATURE_TO_FRONT_TI_CreateParams
  @brief  This structure contains all the parameters which controls
          FAST9 corner detect applet at create time

  @param  visionParams
          Common parmeters for all ivison based modules

  @param  maxNumFeaturesIn
          Number of max Features for which the applet will be used
          User need to make sure that total features summed up across all levels
          should be any value <= HARRIS_BEST_FEATURE_TO_FRONT_TI_MAXNUMFEATURES

  @param  bestNFeaturesOut
          Number of best Features user want as out User need to make sure that
          bestNFeaturesOut < maxNumFeaturesIn

  @param  sensitivityParam
          Value of sensitivity parameter (known as kappa in literature). The format of this
          is Q1.15. Which means for a value of 0.04 you should set 0.04*pow(2,15) =~ 1310
*/

typedef struct
{
  IVISION_Params visionParams;
  uint16_t       maxNumFeaturesIn;
  uint16_t       bestNFeaturesOut;
  uint16_t       sensitivityParam;
  uint8_t        xyListInDmem;
} HARRIS_BEST_FEATURE_TO_FRONT_TI_CreateParams;


/*@}*/
/* ti_ivision_HARRIS_BEST_FEATURE_TO_FRONT */

#endif /*IHARRIS_BEST_FEATURE_TO_FRONT_TI_H */
/*==========================================================================*/
/*     END of the FILE                                                      */
/*==========================================================================*/

