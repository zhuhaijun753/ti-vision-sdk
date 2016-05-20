/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include "configparser.h"
#include "filter_2d_config.h"
#pragma RESET_MISRA ("required")

uint32_t filter2d_numTestCases;
sFilter2d_Config gConfig_filter2d[FILTER_2D_NUM_MAX_TESTCASES];

sTokenMapping gsTokenMap_filter2d[] =
{
  {(char *)"numTestCases"    ,&filter2d_numTestCases              , INT_32, SINGLE},
  {(char *)"fileBased"       ,&gConfig_filter2d[0].fileBased      , INT_8 , SINGLE},
  {(char *)"inImage"         ,&gConfig_filter2d[0].inImage        , STRING, SINGLE},
  {(char *)"outImage"        ,&gConfig_filter2d[0].outImage       , STRING, SINGLE},
  {(char *)"refImage"        ,&gConfig_filter2d[0].refImage       , STRING, SINGLE},
  {(char *)"imageFormat"   ,&gConfig_filter2d[0].imageFormat, INT_8, SINGLE},
  {(char *)"srcImageWidth"   ,&gConfig_filter2d[0].srcImageWidth  , INT_16, SINGLE},
  {(char *)"srcImageHeight"  ,&gConfig_filter2d[0].srcImageHeight , INT_16, SINGLE},
  {(char *)"srcImagePitch"   ,&gConfig_filter2d[0].srcImagePitch  , INT_16, SINGLE},
  {(char *)"enableContrastStretching"   ,&gConfig_filter2d[0].enableContrastStretching  , INT_8, SINGLE},
  {(char *)"minPercentileThreshold"   ,&gConfig_filter2d[0].minPercentileThreshold  , INT_8, SINGLE},
  {(char *)"maxPercentileThreshold"   ,&gConfig_filter2d[0].maxPercentileThreshold  , INT_8, SINGLE},
  {(char *)"enableFilter"   ,&gConfig_filter2d[0].enableFilter  , INT_8, SINGLE},
  {(char *)"filterCoeffWidth"   ,&gConfig_filter2d[0].filterCoeffWidth  , INT_8, SINGLE},
  {(char *)"filterCoeffHeight"   ,&gConfig_filter2d[0].filterCoeffHeight  , INT_8, SINGLE},
  {(char *)"filterCoeffs"   ,&gConfig_filter2d[0].filterCoeffs  , INT_8, MULTI},
  {(char *)"testCaseName"        ,&gConfig_filter2d[0].testCaseName         , STRING, SINGLE},
  {(char* )"performanceTestcase" ,&gConfig_filter2d[0].performanceTestcase  , INT_8,  SINGLE},
  {(char *)"desc"                ,&gConfig_filter2d[0].desc                 , STRING, SINGLE},
} ;

