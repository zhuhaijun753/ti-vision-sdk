/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2015 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include "configparser.h"
#include "ld_config.h"
#pragma RESET_MISRA ("required")

uint32_t ld_numTestCases;
sLD_Config gConfig_LD[LD_NUM_MAX_TESTCASES];

sTokenMapping gsTokenMap_LD[] =
{
  {(char *)"numTestCases"             ,&ld_numTestCases                         , INT_32, SINGLE},
  {(char *)"inFileName"               ,&gConfig_LD[0].inFileName                , STRING, SINGLE},
  {(char *)"outFileName"              ,&gConfig_LD[0].outFileName               , STRING, SINGLE},
  {(char *)"maxImageWidth"            ,&gConfig_LD[0].maxImageWidth             , INT_16, SINGLE},
  {(char *)"maxImageHeight"           ,&gConfig_LD[0].maxImageHeight            , INT_16, SINGLE},
  {(char *)"actualImgWidth"           ,&gConfig_LD[0].actualImgWidth            , INT_16, SINGLE},
  {(char *)"actualImgHeight"          ,&gConfig_LD[0].actualImgHeight           , INT_16, SINGLE},
  {(char *)"maxFrames"                ,&gConfig_LD[0].maxFrames                 , INT_16, SINGLE},
  {(char* )"roiWidth"                 ,&gConfig_LD[0].roiWidth                  , INT_16, SINGLE},
  {(char* )"roiHeight"                ,&gConfig_LD[0].roiHeight                 , INT_16, SINGLE},
  {(char* )"startX"                   ,&gConfig_LD[0].startX                    , INT_16, SINGLE},
  {(char* )"startY"                   ,&gConfig_LD[0].startY                    , INT_16, SINGLE},
  {(char *)"cannyHiThresh"            ,&gConfig_LD[0].cannyHiThresh             , INT_8 , SINGLE},
  {(char *)"cannyLoThresh"            ,&gConfig_LD[0].cannyLoThresh             , INT_8 , SINGLE},
  {(char *)"houghNmsThresh"           ,&gConfig_LD[0].houghNmsThresh            , INT_8 , SINGLE},
  {(char *)"maxRho"                   ,&gConfig_LD[0].maxRho                    , INT_16, SINGLE},
  {(char *)"startThetaLeft"           ,&gConfig_LD[0].startThetaLeft            , INT_16, SINGLE},
  {(char *)"endThetaLeft"             ,&gConfig_LD[0].endThetaLeft              , INT_16, SINGLE},
  {(char *)"startThetaRight"          ,&gConfig_LD[0].startThetaRight           , INT_16, SINGLE},
  {(char *)"endThetaRight"            ,&gConfig_LD[0].endThetaRight             , INT_16, SINGLE},
  {(char *)"thetaStepSize"            ,&gConfig_LD[0].thetaStepSize             , INT_8 , SINGLE},
  {(char *)"trackMethod"              ,&gConfig_LD[0].trackMethod               , INT_8 , SINGLE},
  {(char *)"enableWarning"            ,&gConfig_LD[0].enableWarning             , INT_8 , SINGLE},
  {(char *)"numHoughMaximasDet"       ,&gConfig_LD[0].numHoughMaximasDet        , INT_8 , SINGLE},
  {(char *)"numHoughMaximasTrack"     ,&gConfig_LD[0].numHoughMaximasTrack      , INT_8 , SINGLE},
  {(char *)"departThetaLeftMin"       ,&gConfig_LD[0].departThetaLeftMin        , INT_16, SINGLE},
  {(char *)"departThetaLeftMax"       ,&gConfig_LD[0].departThetaLeftMax        , INT_16, SINGLE},
  {(char *)"departRhoLeftMin"         ,&gConfig_LD[0].departRhoLeftMin          , INT_16, SINGLE},
  {(char *)"departRhoLeftMax"         ,&gConfig_LD[0].departRhoLeftMax          , INT_16, SINGLE},
  {(char *)"departThetaRightMin"      ,&gConfig_LD[0].departThetaRightMin       , INT_16, SINGLE},
  {(char *)"departThetaRightMax"      ,&gConfig_LD[0].departThetaRightMax       , INT_16, SINGLE},
  {(char *)"departRhoRightMin"        ,&gConfig_LD[0].departRhoRightMin         , INT_16, SINGLE},
  {(char *)"departRhoRightMax"        ,&gConfig_LD[0].departRhoRightMax         , INT_16, SINGLE},
} ;

