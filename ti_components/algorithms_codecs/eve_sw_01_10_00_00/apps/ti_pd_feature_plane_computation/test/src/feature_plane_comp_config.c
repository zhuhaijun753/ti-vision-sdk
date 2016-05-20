/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include "configparser.h"
#include "feature_plane_comp_config.h"
#pragma RESET_MISRA ("required")

uint32_t featurePlaneComp_numTestCases;
sFeaturePlaneComp_Config gConfig_featurePlaneComp[FEATURE_PLANE_COMP_NUM_MAX_TESTCASES];

sTokenMapping gsTokenMap_featurePlaneComp[MAX_ITEMS_TO_PARSE] =
{
  {(char *)"numTestCases"       ,&featurePlaneComp_numTestCases                  , INT_32, SINGLE},
  {(char *)"fileBased"          ,&gConfig_featurePlaneComp[0].fileBased          , INT_8 , SINGLE},
  {(char *)"inImage"            ,&gConfig_featurePlaneComp[0].inImage            , STRING, SINGLE},
  {(char *)"outImage"           ,&gConfig_featurePlaneComp[0].outImage           , STRING, SINGLE},
  {(char *)"refImage"           ,&gConfig_featurePlaneComp[0].refImage           , STRING, SINGLE},
  {(char *)"srcImageWidth"      ,&gConfig_featurePlaneComp[0].srcImageWidth      , INT_16, SINGLE},
  {(char *)"srcImageHeight"     ,&gConfig_featurePlaneComp[0].srcImageHeight     , INT_16, SINGLE},
  {(char *)"srcImagePitch"      ,&gConfig_featurePlaneComp[0].srcImagePitch      , INT_16, SINGLE},
  {(char *)"cellSize"           ,&gConfig_featurePlaneComp[0].cellSize           , INT_16, SINGLE},
  {(char *)"blockSize"          ,&gConfig_featurePlaneComp[0].blockSize          , INT_16, SINGLE},
  {(char *)"blockOverlap"       ,&gConfig_featurePlaneComp[0].blockOverlap       , INT_16, SINGLE},
  {(char *)"sreachStep"         ,&gConfig_featurePlaneComp[0].sreachStep         , INT_16, SINGLE},
  {(char *)"scaleSteps"         ,&gConfig_featurePlaneComp[0].scaleSteps         , INT_16, SINGLE},
  {(char *)"numScales"          ,&gConfig_featurePlaneComp[0].numScales          , INT_16, SINGLE},
  {(char *)"enableFilter"       ,&gConfig_featurePlaneComp[0].enableFilter       , INT_16, SINGLE},
  {(char *)"enableContrastStretching" ,&gConfig_featurePlaneComp[0].enableContrastStretching, INT_16, SINGLE},
  {(char *)"extFilterParam"     ,&gConfig_featurePlaneComp[0].extFilterParam     , INT_8, SINGLE},
  {(char *)"numBins"            ,&gConfig_featurePlaneComp[0].numBins            , INT_16, SINGLE},
  {(char *)"gradientMethod"     ,&gConfig_featurePlaneComp[0].gradientMethod     , INT_16, SINGLE},
  {(char *)"enableGardMagPlane" ,&gConfig_featurePlaneComp[0].enableGardMagPlane , INT_8, SINGLE},
  {(char *)"enableCellSum"      ,&gConfig_featurePlaneComp[0].enableCellSum      , INT_8, SINGLE},
  {(char *)"enableYPlane"       ,&gConfig_featurePlaneComp[0].enableYPlane       , INT_8, SINGLE},
  {(char *)"enableUVPlane"      ,&gConfig_featurePlaneComp[0].enableUVPlane      , INT_8, SINGLE},
  {(char *)"startFrame"         ,&gConfig_featurePlaneComp[0].startFrame         , INT_32, SINGLE},
  {(char *)"numFrames"          ,&gConfig_featurePlaneComp[0].numFrames          , INT_32, SINGLE},
  {(char *)"outFormat"          ,&gConfig_featurePlaneComp[0].outFormat          , INT_8 , SINGLE},
  {(char *)"testCaseName"       ,&gConfig_featurePlaneComp[0].testCaseName       , STRING, SINGLE},
  {(char *)"testCaseDesc"       ,&gConfig_featurePlaneComp[0].testCaseDesc       , STRING, SINGLE},
  {(char* )"performanceTestcase",&gConfig_featurePlaneComp[0].performanceTestcase, INT_8,  SINGLE},
  {(char* )"RoiSelectionMethod", &gConfig_featurePlaneComp[0].RoiSelectionMethod , INT_8,  SINGLE},
  {(char *)"RoiCenterX"         ,&gConfig_featurePlaneComp[0].RoiCenterX         , INT_16, SINGLE},
  {(char *)"RoiCenterY"         ,&gConfig_featurePlaneComp[0].RoiCenterY         , INT_16, SINGLE},
  {(char *)"RoiWidth"           ,&gConfig_featurePlaneComp[0].RoiWidth           , INT_16, SINGLE},
  {(char *)"RoiHeight"          ,&gConfig_featurePlaneComp[0].RoiHeight          , INT_16, SINGLE},
  {(char *)"scaleParams"        ,gConfig_featurePlaneComp[0].scaleParams         , INT_16, MULTI},
  {(char *)"scaleRatioQ12"      ,&gConfig_featurePlaneComp[0].scaleRatioQ12      , INT_16, MULTI},

} ;

