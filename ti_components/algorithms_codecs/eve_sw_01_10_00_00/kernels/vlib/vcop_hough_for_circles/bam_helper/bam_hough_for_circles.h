/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_hough_for_circles.h
 *
 *  @brief      This header defines interfaces for integrating hough for
 *              circles into BAM.
 */

#ifndef BAM_HOUGH_FOR_CIRCLES_H_
#define BAM_HOUGH_FOR_CIRCLES_H_

#include "bam_common.h"

#define BAM_HOUGH_FOR_CIRCLES_MAX_NUM_RADIUS   (32U)

/* For Compute Hough Space index BAM node */

typedef struct
{
  uint16_t maxNumEdgePoints;
  uint8_t  circleType;
  uint8_t  houghSpaceDownShift;
} BAM_HoughForCircles_Args;

typedef struct
{
  uint8_t  numRadius;
  int8_t  radius[BAM_HOUGH_FOR_CIRCLES_MAX_NUM_RADIUS];
  uint16_t houghSpaceSaturateX;
  uint16_t houghSpaceSaturateY;
  uint16_t houghSpacePitch;
} BAM_HoughForCircles_CtrlArgs;

extern BAM_KernelHelperFuncDef gBAM_TI_houghForCirclesHelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_houghForCirclesExecFunc;

extern BAM_KernelInfo gBAM_TI_houghForCirclesKernel;

typedef enum
{
  BAM_HOUGH_FOR_CIRCLES_NORM_GRAD_PORT = 0,
  BAM_HOUGH_FOR_CIRCLES_XY_LIST_PORT,
  BAM_HOUGH_FOR_CIRCLES_XY_LIST_SIZE_WBUF_PORT,
  BAM_HOUGH_FOR_CIRCLES_NUM_INPUT_BLOCKS
} eBAM_HOUGH_FOR_CIRCLES_INPUT_PORTS;

typedef enum
{
  BAM_HOUGH_FOR_CIRCLES_HOUGH_IDX_PORT = 0,
  BAM_HOUGH_FOR_CIRCLES_NUM_OUTPUT_BLOCKS
} eBAM_HOUGH_FOR_CIRCLES_OUTPUT_PORTS;

/* For Circle Detect BAM node */

typedef struct
{
  uint16_t numElemsPerBlock;
  uint16_t maxHoughSpacePitch;
  uint16_t maxHoughSpaceHeight;
} BAM_HoughForCirclesDetect_Args;

typedef struct
{
  uint8_t  maxRadius;
  uint32_t numEdgePoints;
  uint16_t numEdgePointsChunk;
  uint8_t  houghScoreThreshold;
  uint16_t houghSpaceWidth;
  uint16_t houghSpaceHeight;
  uint16_t houghSpacePitch;
  uint8_t  houghSpaceShift;
  uint16_t startX;/* In terms of non scaled coordinates */
  uint16_t startY;/* In terms of non scaled coordinates */
} BAM_HoughForCirclesDetect_CtrlArgs;

extern BAM_KernelHelperFuncDef gBAM_TI_houghForCirclesDetectHelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_houghForCirclesDetectExecFunc;

extern BAM_KernelInfo gBAM_TI_houghForCirclesDetectKernel;

typedef enum
{
  BAM_HOUGH_FOR_CIRCLES_DETECT_HOUGH_IDX_PORT = 0,
  BAM_HOUGH_FOR_CIRCLES_DETECT_NUM_INPUT_BLOCKS
} eBAM_HOUGH_FOR_CIRCLES_DETECT_INPUT_PORTS;

typedef enum
{
  BAM_HOUGH_FOR_CIRCLES_DETECT_CENTER_XY_PORT = 0,
  BAM_HOUGH_FOR_CIRCLES_DETECT_HOUGH_SCORE_PORT,
  BAM_HOUGH_FOR_CIRCLES_DETECT_NUM_CIRCLES_PORT,
  BAM_HOUGH_FOR_CIRCLES_DETECT_NUM_OUTPUT_BLOCKS
} eBAM_HOUGH_FOR_CIRCLES_DETECT_OUTPUT_PORTS;

#endif /* BAM_HOUGH_FOR_CIRCLES_H_ */

