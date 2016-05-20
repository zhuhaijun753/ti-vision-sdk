/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#include <stdio.h>
#include <stdint.h>
#include "configparser.h"
#include "vcop_hough_for_circles_config.h"

sHough_for_circles_Config gConfig_hough_for_circles;
sTokenMapping gsTokenMap_hough_for_circles[] =
{
  {(char* )"gradDir",              &gConfig_hough_for_circles.gradDir              , STRING, SINGLE},
  {(char* )"xyList",               &gConfig_hough_for_circles.xyList               , STRING, SINGLE},
  {(char* )"houghIdx",             &gConfig_hough_for_circles.houghIdx             , STRING, SINGLE},
  {(char* )"testCase",             &gConfig_hough_for_circles.testCase             ,  INT_8, SINGLE},
  {(char* )"listSize",             &gConfig_hough_for_circles.listSize             , INT_16, SINGLE},
  {(char* )"imgWidth",             &gConfig_hough_for_circles.imgWidth             , INT_16, SINGLE},
  {(char* )"imgHeight",            &gConfig_hough_for_circles.imgHeight            , INT_16, SINGLE},
  {(char* )"radius",               &gConfig_hough_for_circles.radius               ,  INT_8, SINGLE},
  {(char* )"houghSpaceDownScale",  &gConfig_hough_for_circles.houghSpaceDownScale  ,  INT_8, SINGLE},
  {(char* )"houghScoreThreshold",  &gConfig_hough_for_circles.houghScoreThreshold  ,  INT_8, SINGLE},
  {(char* )"startX",               &gConfig_hough_for_circles.startX               , INT_16, SINGLE},
  {(char* )"startY",               &gConfig_hough_for_circles.startY               , INT_16, SINGLE},
  {(char* )"randSeedGrad",         &gConfig_hough_for_circles.randSeedGrad         , INT_32, SINGLE},
  {(char* )"randSeedXY",           &gConfig_hough_for_circles.randSeedXY           , INT_32, SINGLE},
  {(char* )"randSeedHoughIdx",     &gConfig_hough_for_circles.randSeedHoughIdx     , INT_32, SINGLE},
  {(char* )"numIter",              &gConfig_hough_for_circles.numIter              ,  INT_8, SINGLE},
} ;

