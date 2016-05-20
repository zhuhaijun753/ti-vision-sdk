/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include "configparser.h"
#include "feature_matching_config.h"
#pragma RESET_MISRA ("required")

sFeatureMatching_Config gConfig_feature_matching;

sTokenMapping gsTokenMap_feature_matching[] =
{
  {(char  * )"testCaseName",           &gConfig_feature_matching.testCaseName          , STRING, SINGLE},
  {(char  * )"testCaseDesc",           &gConfig_feature_matching.testCaseDesc          , STRING, SINGLE},
  {(char  * )"performanceTestcase",    &gConfig_feature_matching.performanceTestcase   , INT_8 , SINGLE},


  {(char  * )"inFeatureList1",         &gConfig_feature_matching.inFeatureList1        , STRING, SINGLE},
  {(char  * )"inFeatureList2",         &gConfig_feature_matching.inFeatureList2        , STRING, SINGLE},
  {(char  * )"outCorrespondence",      &gConfig_feature_matching.outCorrespondence     , STRING, SINGLE},

  {(char  * )"numDescriptors1",        &gConfig_feature_matching.numDescriptors1       , INT_16, SINGLE},
  {(char  * )"numDescriptors2",        &gConfig_feature_matching.numDescriptors2       , INT_16, SINGLE},
  {(char  * )"descriptorLength",       &gConfig_feature_matching.descriptorLength      , INT_16, SINGLE},
  {(char  * )"minDistanceThres",       &gConfig_feature_matching.minDistanceThres      , INT_16, SINGLE},
  {(char  * )"matchConfidence",        &gConfig_feature_matching.matchConfidence       , INT_16, SINGLE},

  {(char  * )"randSeed1",              &gConfig_feature_matching.randSeed1             , INT_32, SINGLE},
  {(char  * )"randSeed2",              &gConfig_feature_matching.randSeed2             , INT_32, SINGLE}
} ;

