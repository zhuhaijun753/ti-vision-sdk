/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include "configparser.h"
#include "fast9_best_feature_to_front_config.h"
#pragma RESET_MISRA ("required")

uint32_t numTestCases;
sFast9BestFeatureToFront_Config gConfig_Fast9BestFeatureToFront[FAST9_BFTF_NUM_MAX_TESTCASES];

sTokenMapping gsTokenMap_Fast9BestFeatureToFront[MAX_ITEMS_TO_PARSE] =
{
  {(char *)"numTestCases" ,           &numTestCases                                           , INT_32, SINGLE},
  {(char *)"testCaseName" ,           &gConfig_Fast9BestFeatureToFront[0].testCaseName        , STRING, SINGLE},
  {(char* )"performanceTestcase" ,    &gConfig_Fast9BestFeatureToFront[0].performanceTestcase , INT_8,  SINGLE},
  {(char *)"desc" ,                   &gConfig_Fast9BestFeatureToFront[0].desc                , STRING, SINGLE},

  /* Test Case 0 */
  {(char *)"fileBased",               &gConfig_Fast9BestFeatureToFront[0].fileBased        , INT_8, SINGLE},
  {(char *)"numLevels",               &gConfig_Fast9BestFeatureToFront[0].numLevels        , INT_8, SINGLE},
  {(char *)"fast9threshold",          &gConfig_Fast9BestFeatureToFront[0].fast9threshold   , INT_8,  SINGLE},
  {(char *)"XYInDmem",                &gConfig_Fast9BestFeatureToFront[0].XYInDmem         , INT_8, SINGLE},
  {(char *)"writeOutput",             &gConfig_Fast9BestFeatureToFront[0].writeOutput      , INT_8, SINGLE},
  {(char *)"maxFeatures",             &gConfig_Fast9BestFeatureToFront[0].maxFeatures      , INT_16, SINGLE},
  {(char *)"maxbestNFeatures",        &gConfig_Fast9BestFeatureToFront[0].maxbestNFeatures , INT_16, SINGLE},
  {(char *)"suppressionMethod",       &gConfig_Fast9BestFeatureToFront[0].suppressionMethod, INT_8, SINGLE},

  {(char *)"inImage0",               &gConfig_Fast9BestFeatureToFront[0].inImage[0]       , STRING, SINGLE},
  {(char *)"inImage1",               &gConfig_Fast9BestFeatureToFront[0].inImage[1]       , STRING, SINGLE},
  {(char *)"inImage2",               &gConfig_Fast9BestFeatureToFront[0].inImage[2]       , STRING, SINGLE},
  {(char *)"inXYList0",              &gConfig_Fast9BestFeatureToFront[0].inXYList[0]      , STRING, SINGLE},
  {(char *)"inXYList1",              &gConfig_Fast9BestFeatureToFront[0].inXYList[1]      , STRING, SINGLE},
  {(char *)"inXYList2",              &gConfig_Fast9BestFeatureToFront[0].inXYList[2]      , STRING, SINGLE},
  {(char *)"outImage0",              &gConfig_Fast9BestFeatureToFront[0].outXY[0]         , STRING, SINGLE},
  {(char *)"outImage1",              &gConfig_Fast9BestFeatureToFront[0].outXY[1]         , STRING, SINGLE},
  {(char *)"outImage2",              &gConfig_Fast9BestFeatureToFront[0].outXY[2]         , STRING, SINGLE},
  {(char *)"srcImageWidth",          &gConfig_Fast9BestFeatureToFront[0].srcImageWidth    , INT_16, MULTI},
  {(char *)"srcImageHeight",         &gConfig_Fast9BestFeatureToFront[0].srcImageHeight   , INT_16, MULTI},
  {(char *)"total_features",         &gConfig_Fast9BestFeatureToFront[0].total_features   , INT_16, MULTI},
  {(char *)"bestNFeatures",          &gConfig_Fast9BestFeatureToFront[0].bestNFeatures    , INT_16, MULTI},

  /* Test Case 1 */
} ;
