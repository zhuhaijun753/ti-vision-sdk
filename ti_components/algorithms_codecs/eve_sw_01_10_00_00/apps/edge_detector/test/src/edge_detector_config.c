/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include "configparser.h"
#include "edge_detector_config.h"
#pragma RESET_MISRA ("required")

uint32_t edgeDetector_numTestCases;
sEdgeDetector_Config gConfig_edgeDetector[EDGE_DETECTOR_NUM_MAX_TESTCASES];

sTokenMapping gsTokenMap_edgeDetector[] =
{
  {(char *)"numTestCases"        ,&edgeDetector_numTestCases              , INT_32, SINGLE},
  {(char *)"inImage"             ,&gConfig_edgeDetector[0].inImage    , STRING, SINGLE},
  {(char *)"outImage"            ,&gConfig_edgeDetector[0].outImage   , STRING, SINGLE},
  {(char *)"imageWidth"          ,&gConfig_edgeDetector[0].imageWidth     , INT_16, SINGLE},
  {(char *)"imageHeight"         ,&gConfig_edgeDetector[0].imageHeight    , INT_16, SINGLE},
  {(char *)"imagePitch"          ,&gConfig_edgeDetector[0].imagePitch     , INT_16, SINGLE},
  {(char* )"outputPitch"         ,&gConfig_edgeDetector[0].outputPitch  , INT_16, SINGLE},
  {(char* )"kernelSize"          ,&gConfig_edgeDetector[0].kernelSize     , INT_8 , SINGLE},
  {(char* )"threshold1"          ,&gConfig_edgeDetector[0].threshold1 , INT_16 , SINGLE},
  {(char* )"threshold2"          ,&gConfig_edgeDetector[0].threshold2, INT_16 , SINGLE},
  {(char* )"outputFormat"        ,&gConfig_edgeDetector[0].outputFormat, INT_8 , SINGLE},
  {(char* )"method"              ,&gConfig_edgeDetector[0].method, INT_8 , SINGLE},
  {(char* )"randSeed"            ,&gConfig_edgeDetector[0].randSeed       , INT_32, SINGLE},
  {(char *)"testCaseName"        ,&gConfig_edgeDetector[0].testCaseName         , STRING, SINGLE},
  {(char* )"performanceTestcase" ,&gConfig_edgeDetector[0].performanceTestcase  , INT_8,  SINGLE},
  {(char *)"desc"                ,&gConfig_edgeDetector[0].desc                 , STRING, SINGLE},
} ;

