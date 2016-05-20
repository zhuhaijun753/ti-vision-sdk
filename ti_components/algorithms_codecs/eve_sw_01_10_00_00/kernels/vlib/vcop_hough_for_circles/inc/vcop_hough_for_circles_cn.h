/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*                                                                          */
/*  @file : vcop_hough_for_circle_cn.h                                      */
/*                                                                          */
/*  @brief : This file contains declarations for the C reference            */
/*  function for Hough Transform computation for circles.                   */
/*                                                                          */
/*  vcop_hough_circle_compute_idx_cn                                        */
/*      This is the c-reference for the vcop_hough_circle_compute_idx       */
/*      kernel. This routine computes the indexes in Hough Space into       */
/*      which the edge point specified by xyList votes for a particular     */
/*      radius.                                                             */
/*                                                                          */
/*  USAGE:                                                                  */
/*  This routine is C-callable and can be called as:                        */
/*                                                                          */
/* int32_t vcop_hough_circle_compute_idx_cn                                 */
/* (                                                                        */
/*   int16   *gradUnitVecXY,                                                */
/*   uint16  *xyList,                                                       */
/*   uint16  *houghSpaceIndex,                                              */
/*   uint16_t numEdgePoints,                                                */
/*   int8_t   radius,                                                       */
/*   uint8_t  downShift,                                                    */
/*   uint16_t houghSpaceWidth                                               */
/* )                                                                        */
/*                                                                          */
/*  gradUnitVecXY   : [in] List of unit gradient vectors packed as (GradX,  */
/*                    GradY) in Q1.8 format                                 */
/*  xyList          : [in] List of corresponding X,Y co-ordidnates in       */
/*                    packed format                                         */
/*  houghSpaceIndex : [out] Pointer to output hough space indices           */
/*  numEdgePoints   : Number of edge points for which gradient infomation   */
/*                    is provided                                           */
/*  radius          : Radius for which indexes in Hough Space need to be    */
/*                    computed                                              */
/*  downShift       : Downsampling factor in Hough space                    */
/*  houghSpaceWidth : Width of the output downsampled Hough space. It is    */
/*                    assumed that houghSpaceHeight <= houghSpaceWidth.     */
/*                                                                          */
/*  Returns       :  Status = 0 if it runs sucessfully                      */
/*                                                                          */
/*  @version 0.1 (Sept 2014) : Base version.                                */
/*                                                                          */
/*==========================================================================*/

#ifndef VCOP_HOUGH_FOR_CIRCLES_CN_H_
#define VCOP_HOUGH_FOR_CIRCLES_CN_H_

int32_t vcop_hough_circle_compute_idx_cn
(
  int16_t  *gradUnitVecXY,
  uint16_t *xyList,
  uint16_t *houghSpaceIndex,
  uint16_t  numEdgePoints,
  int8_t    radius,
  uint8_t   downShift,
  uint16_t  houghSpaceSaturateX,
  uint16_t  houghSpaceSaturateY,
  uint16_t  houghSpacePitch
);

int32_t vcop_hough_circle_vote_to_hough_space_cn
(
  uint16_t  *houghSpaceIndex,
  uint8_t   *houghSpacePtr,
  unsigned short numEdgePoints
);

int32_t vcop_hough_for_circle_detect_cn
(
  uint8_t  *houghSpacePtr,
  uint32_t *pUpperLeftXY,
  uint32_t *xSequence,
  uint16_t *pNumCircles,
  uint32_t *pCenterListXY,
  uint8_t  *pHoughScoreList,
  uint8_t   houghScoreThreshold,
  uint16_t  houghSpaceWidth,
  uint16_t  houghSpaceHeight,
  uint16_t  houghSpacePitch,
  uint8_t   houghSpaceShift
);

#endif /* VCOP_HOUGH_FOR_CIRCLES_CN_H_ */

