/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include "configparser.h"
#include "hough_for_circles_config.h"
#pragma RESET_MISRA ("required")

uint32_t houghForCircles_numTestCases;
sHoughForCircles_Config gConfig_houghForCircles[HOUGH_FOR_CIRCLES_NUM_MAX_TESTCASES];

sTokenMapping gsTokenMap_houghForCircles[] =
{
  {(char *)"numTestCases"        ,&houghForCircles_numTestCases              , INT_32, SINGLE},
  {(char *)"inImg"               ,&gConfig_houghForCircles[0].inImg          , STRING, SINGLE},
  {(char *)"edgeImg"             ,&gConfig_houghForCircles[0].edgeImg        , STRING, SINGLE},
  {(char *)"outputImage"         ,&gConfig_houghForCircles[0].outputImage   , STRING, SINGLE},
  {(char *)"imageWidth"          ,&gConfig_houghForCircles[0].imageWidth     , INT_16, SINGLE},
  {(char *)"imageHeight"         ,&gConfig_houghForCircles[0].imageHeight    , INT_16, SINGLE},
  {(char *)"imagePitch"          ,&gConfig_houghForCircles[0].imagePitch     , INT_16, SINGLE},
  {(char* )"maxPercentageEdges"  ,&gConfig_houghForCircles[0].maxPercentageEdges  , INT_32, SINGLE},
  {(char* )"circleType"          ,&gConfig_houghForCircles[0].circleType     , INT_8 , SINGLE},
  {(char* )"houghSpaceScaling"   ,&gConfig_houghForCircles[0].houghSpaceScaling , INT_8 , SINGLE},
  {(char* )"numRadius"           ,&gConfig_houghForCircles[0].numRadius      , INT_8 , SINGLE},
  {(char* )"radius"              ,&gConfig_houghForCircles[0].radius[0]      , INT_8, MULTI},
  {(char* )"houghScoreThreshold" ,&gConfig_houghForCircles[0].houghScoreThreshold[0] , INT_8, MULTI},
  {(char* )"randSeed"            ,&gConfig_houghForCircles[0].randSeed       , INT_32, SINGLE},
  {(char* )"genEdgeMap"          ,&gConfig_houghForCircles[0].genEdgeMap     , INT_8 , SINGLE},
  {(char *)"testCaseName"        ,&gConfig_houghForCircles[0].testCaseName         , STRING, SINGLE},
  {(char* )"performanceTestcase" ,&gConfig_houghForCircles[0].performanceTestcase  , INT_8,  SINGLE},
  {(char *)"desc"                ,&gConfig_houghForCircles[0].desc                 , STRING, SINGLE},
} ;

