/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include "configparser.h"
#include "rbrief_config.h"
#pragma RESET_MISRA ("required")

uint32_t rbrief_numTestCases;
sRbrief_Config gConfig_rbrief[RBEIEF_NUM_MAX_TESTCASES];

sTokenMapping gsTokenMap_rbrief[] =
{
  {(char *)"numTestCases"     ,&rbrief_numTestCases                 , INT_32, SINGLE},

  /* Test case 0 */
  {(char *)"0fileBased"       ,&gConfig_rbrief[0].fileBased         , INT_8 , SINGLE},
  {(char *)"0numLevels"       ,&gConfig_rbrief[0].numLevels         , INT_8 , SINGLE},
  {(char *)"0inImage0"        ,&gConfig_rbrief[0].inImage[0]        , STRING, SINGLE},
  {(char *)"0srcImageWidth0"  ,&gConfig_rbrief[0].srcImageWidth[0]  , INT_16, SINGLE},
  {(char *)"0srcImageHeight0" ,&gConfig_rbrief[0].srcImageHeight[0] , INT_16, SINGLE},
  {(char *)"0srcImagePitch0"  ,&gConfig_rbrief[0].srcImagePitch[0]  , INT_16, SINGLE},

  {(char *)"0inImage1"        ,&gConfig_rbrief[0].inImage[1]        , STRING, SINGLE},
  {(char *)"0srcImageWidth1"  ,&gConfig_rbrief[0].srcImageWidth[1]  , INT_16, SINGLE},
  {(char *)"0srcImageHeight1" ,&gConfig_rbrief[0].srcImageHeight[1] , INT_16, SINGLE},
  {(char *)"0srcImagePitch1"  ,&gConfig_rbrief[0].srcImagePitch[1]  , INT_16, SINGLE},

  {(char *)"0inImage2"        ,&gConfig_rbrief[0].inImage[2]        , STRING, SINGLE},
  {(char *)"0srcImageWidth2"  ,&gConfig_rbrief[0].srcImageWidth[2]  , INT_16, SINGLE},
  {(char *)"0srcImageHeight2" ,&gConfig_rbrief[0].srcImageHeight[2] , INT_16, SINGLE},
  {(char *)"0srcImagePitch2"  ,&gConfig_rbrief[0].srcImagePitch[2]  , INT_16, SINGLE},

  {(char *)"0inImage3"        ,&gConfig_rbrief[0].inImage[3]        , STRING, SINGLE},
  {(char *)"0srcImageWidth3"  ,&gConfig_rbrief[0].srcImageWidth[3]  , INT_16, SINGLE},
  {(char *)"0srcImageHeight3" ,&gConfig_rbrief[0].srcImageHeight[3] , INT_16, SINGLE},
  {(char *)"0srcImagePitch3"  ,&gConfig_rbrief[0].srcImagePitch[3]  , INT_16, SINGLE},

  {(char *)"0outImage"        ,&gConfig_rbrief[0].outImage          , STRING, SINGLE},
  {(char *)"0maxNumFeatures"  ,&gConfig_rbrief[0].maxNumFeatures    , INT_16, SINGLE},
  {(char *)"0xyLevelListFile" ,&gConfig_rbrief[0].xyLevelListFile   , STRING, SINGLE},

  {(char* )"testCaseName",           &gConfig_rbrief[0].testCaseName           , STRING, SINGLE},
  {(char* )"performanceTestcase",    &gConfig_rbrief[0].performanceTestcase    ,  INT_8, SINGLE},
  {(char* )"desc",                   &gConfig_rbrief[0].desc                   , STRING, SINGLE}


/* Test case 1 */

} ;

