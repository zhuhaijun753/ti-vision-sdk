/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include "configparser.h"
#include "harris_best_feature_to_front_config.h"
#pragma RESET_MISRA ("required")

uint32_t numTestCases;
sHarrisBestFeatureToFront_Config gConfig_harrisBestFeatureToFront[HARRIS_BFTF_NUM_MAX_TESTCASES];

sTokenMapping gsTokenMap_harrisBestFeatureToFront[MAX_ITEMS_TO_PARSE] =
{
  {(char *)"numTestCases" ,            &numTestCases                                            , INT_32, SINGLE},
  {(char *)"testCaseName" ,            &gConfig_harrisBestFeatureToFront[0].testCaseName        , STRING, SINGLE},
  {(char* )"performanceTestcase" ,     &gConfig_harrisBestFeatureToFront[0].performanceTestcase , INT_8,  SINGLE},
  {(char *)"desc" ,                    &gConfig_harrisBestFeatureToFront[0].desc                , STRING, SINGLE},
  /* Test Case 0 */
  {(char  * )"numLevels",              &gConfig_harrisBestFeatureToFront[0].numLevels             , INT_8 , SINGLE},
  {(char  * )"maxNumFeaturesIn",       &gConfig_harrisBestFeatureToFront[0].maxNumFeaturesIn      , INT_16 , SINGLE},
  {(char  * )"bestNFeaturesOut",       &gConfig_harrisBestFeatureToFront[0].bestNFeaturesOut      , INT_16 , SINGLE},
  {(char  * )"harrisSensitivityParam", &gConfig_harrisBestFeatureToFront[0].sensitivityParam      , INT_16 , SINGLE},

  {(char  * )"inImage0",               &gConfig_harrisBestFeatureToFront[0].inImage[0]            , STRING, SINGLE},
  {(char  * )"inImage1",               &gConfig_harrisBestFeatureToFront[0].inImage[1]            , STRING, SINGLE},
  {(char  * )"inImage2",               &gConfig_harrisBestFeatureToFront[0].inImage[2]            , STRING, SINGLE},
  {(char  * )"inXyList0",              &gConfig_harrisBestFeatureToFront[0].inXyList[0]           , STRING, SINGLE},
  {(char  * )"inXyList1",              &gConfig_harrisBestFeatureToFront[0].inXyList[1]           , STRING, SINGLE},
  {(char  * )"inXyList2",              &gConfig_harrisBestFeatureToFront[0].inXyList[2]           , STRING, SINGLE},
  {(char  * )"srcImageWidth",          &gConfig_harrisBestFeatureToFront[0].srcImageWidth         , INT_16, MULTI},
  {(char  * )"srcImageHeight",         &gConfig_harrisBestFeatureToFront[0].srcImageHeight        , INT_16, MULTI},
  {(char  * )"srcImagePitch",          &gConfig_harrisBestFeatureToFront[0].srcImagePitch         , INT_16, MULTI},
  {(char  * )"xyListInDmem",           &gConfig_harrisBestFeatureToFront[0].xyListInDmem          ,  INT_8, SINGLE},
  {(char  * )"numPoints",              &gConfig_harrisBestFeatureToFront[0].numPoints             , INT_16, MULTI},
  {(char  * )"outXyList",              &gConfig_harrisBestFeatureToFront[0].outXyList             , STRING, SINGLE},
  {(char  * )"outLevelIds",            &gConfig_harrisBestFeatureToFront[0].outLevelIds           , STRING, SINGLE},
  {(char  * )"fileBased",              &gConfig_harrisBestFeatureToFront[0].fileBased             , INT_8 , SINGLE},
  {(char  * )"randSeed",               &gConfig_harrisBestFeatureToFront[0].randSeed              , INT_32, SINGLE}
  /* Test Case 1 */
} ;

