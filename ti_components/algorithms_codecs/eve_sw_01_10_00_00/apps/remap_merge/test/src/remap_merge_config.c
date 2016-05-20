/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include "configparser.h"
#include "remap_merge_config.h"
#pragma RESET_MISRA ("required")

uint16_t remapMerge_numTestCases;
sRemapMerge_Config gConfig_remapMerge[REMAP_MERGE_NUM_MAX_TESTCASES];

sTokenMapping gsTokenMap_remapMerge[] =
{
  {(char *)"numTestCases"         ,&remapMerge_numTestCases                    , INT_16, SINGLE},
  {(char *)"testCaseName"         ,&gConfig_remapMerge[0].testCaseName         , STRING, SINGLE},
  {(char* )"performanceTestcase"  ,&gConfig_remapMerge[0].performanceTestcase  , INT_8,  SINGLE},
  {(char *)"inImage"              ,&gConfig_remapMerge[0].inImage              , STRING, SINGLE},
  {(char *)"outImage"             ,&gConfig_remapMerge[0].outImage             , STRING, SINGLE},
  {(char *)"refImage"             ,&gConfig_remapMerge[0].refImage             , STRING, SINGLE},
  {(char *)"coordMapList"         ,&gConfig_remapMerge[0].coordMapList         , INT_8 , SINGLE},
  {(char *)"isSrcMapFloat"        ,&gConfig_remapMerge[0].isSrcMapFloat        , INT_8 , SINGLE},
  {(char *)"srcFormat"            ,&gConfig_remapMerge[0].srcFormat            , INT_8 , SINGLE},
  {(char *)"dstFormat"            ,&gConfig_remapMerge[0].dstFormat            , INT_8 , SINGLE},
  {(char *)"srcStride"            ,&gConfig_remapMerge[0].srcStride            , INT_32, SINGLE},
  {(char *)"srcHeight"            ,&gConfig_remapMerge[0].srcHeight            , INT_32, SINGLE},
  {(char *)"dstStride"            ,&gConfig_remapMerge[0].dstStride            , INT_32, SINGLE},
  {(char *)"roiWidth"             ,&gConfig_remapMerge[0].roiWidth             , INT_32, SINGLE},
  {(char *)"roiHeight"            ,&gConfig_remapMerge[0].roiHeight            , INT_32, SINGLE},
  {(char *)"blockWidthBB"         ,&gConfig_remapMerge[0].blockWidthBB         , INT_16, SINGLE},
  {(char *)"blockHeightBB"        ,&gConfig_remapMerge[0].blockHeightBB        , INT_16, SINGLE},
  {(char *)"blockWidthTile"       ,&gConfig_remapMerge[0].blockWidthTile       , INT_16, SINGLE},
  {(char *)"blockHeightTile"      ,&gConfig_remapMerge[0].blockHeightTile      , INT_16, SINGLE},
  {(char *)"tileWidth"            ,&gConfig_remapMerge[0].tileWidth            , INT_16, SINGLE},
  {(char *)"tileHeight"           ,&gConfig_remapMerge[0].tileHeight           , INT_16, SINGLE},
  {(char *)"enableMerge"          ,&gConfig_remapMerge[0].enableMerge          , INT_8 , SINGLE},
  {(char *)"remapApproach"        ,&gConfig_remapMerge[0].remapApproach        , INT_8 , SINGLE},
  {(char *)"interpolationLuma"    ,&gConfig_remapMerge[0].interpolationLuma    , INT_8 , SINGLE},
  {(char *)"interpolationChroma"  ,&gConfig_remapMerge[0].interpolationChroma  , INT_8 , SINGLE},
  {(char *)"mapQshift"            ,&gConfig_remapMerge[0].mapQshift            , INT_8 , SINGLE},
  {(char *)"rightShift"           ,&gConfig_remapMerge[0].rightShift           , INT_8 , SINGLE},
  {(char *)"sat_high"             ,&gConfig_remapMerge[0].sat_high             , INT_32, SINGLE},
  {(char *)"sat_high_set"         ,&gConfig_remapMerge[0].sat_high_set         , INT_32, SINGLE},
  {(char *)"sat_low"              ,&gConfig_remapMerge[0].sat_low              , INT_32, SINGLE},
  {(char *)"sat_low_set"          ,&gConfig_remapMerge[0].sat_low_set          , INT_32, SINGLE},
  {(char *)"desc"                 ,&gConfig_remapMerge[0].desc                 , STRING, SINGLE},
} ;

