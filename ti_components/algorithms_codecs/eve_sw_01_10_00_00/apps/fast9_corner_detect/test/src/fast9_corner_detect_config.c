/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include "configparser.h"
#include "fast9_corner_detect_config.h"
#pragma RESET_MISRA ("required")

uint32_t fast9CornerDetect_numTestCases;
sFast9CornerDetect_Config gConfig_fast9CornerDetect[FAST9_NUM_MAX_TESTCASES];

sTokenMapping gsTokenMap_fast9CornerDetect[] =
{
  {(char *)"numTestCases"     ,&fast9CornerDetect_numTestCases                 , INT_32, SINGLE},
  {(char *)"testCaseName"        ,&gConfig_fast9CornerDetect[0].testCaseName         , STRING, SINGLE},
  {(char* )"performanceTestcase" ,&gConfig_fast9CornerDetect[0].performanceTestcase  , INT_8,  SINGLE},
  {(char *)"fileBased"       ,&gConfig_fast9CornerDetect[0].fileBased         , INT_8 , SINGLE},
  {(char *)"numLevels"       ,&gConfig_fast9CornerDetect[0].numLevels         , INT_8 , SINGLE},
  {(char *)"inImage0"        ,&gConfig_fast9CornerDetect[0].inImage[0]        , STRING, SINGLE},
  {(char *)"inImage1"        ,&gConfig_fast9CornerDetect[0].inImage[1]        , STRING, SINGLE},
  {(char *)"inImage2"        ,&gConfig_fast9CornerDetect[0].inImage[2]        , STRING, SINGLE},
  {(char *)"inImage3"        ,&gConfig_fast9CornerDetect[0].inImage[3]        , STRING, SINGLE},
  {(char *)"outImage0"       ,&gConfig_fast9CornerDetect[0].outImage[0]       , STRING, SINGLE},
  {(char *)"outImage1"       ,&gConfig_fast9CornerDetect[0].outImage[1]       , STRING, SINGLE},
  {(char *)"outImage2"       ,&gConfig_fast9CornerDetect[0].outImage[2]       , STRING, SINGLE},
  {(char *)"outImage3"       ,&gConfig_fast9CornerDetect[0].outImage[3]       , STRING, SINGLE},
  {(char *)"srcImageWidth"  ,&gConfig_fast9CornerDetect[0].srcImageWidth  , INT_16, MULTI},
  {(char *)"srcImageHeight" ,&gConfig_fast9CornerDetect[0].srcImageHeight , INT_16, MULTI},
  {(char *)"srcImagePitch"  ,&gConfig_fast9CornerDetect[0].srcImagePitch  , INT_16, MULTI},
  {(char *)"fast9Threshold" ,&gConfig_fast9CornerDetect[0].fast9Threshold , INT_8, MULTI},
  {(char *)"frameStartX"    ,&gConfig_fast9CornerDetect[0].frameStartX    , INT_16, MULTI},
  {(char *)"frameStartY"    ,&gConfig_fast9CornerDetect[0].frameStartY    , INT_16, MULTI},
  {(char *)"desc"            ,&gConfig_fast9CornerDetect[0].desc              , STRING, SINGLE},

/* Test case 1 */

} ;

