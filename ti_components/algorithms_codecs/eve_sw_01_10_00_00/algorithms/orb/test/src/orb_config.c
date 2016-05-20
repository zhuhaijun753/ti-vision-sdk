/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include "configparser.h"
#include "orb_config.h"
#pragma RESET_MISRA ("required")

uint32_t orb_numTestCases;
sORB_Config gConfig_ORB[ORB_NUM_MAX_TESTCASES];

sTokenMapping gsTokenMap_ORB[] =
{
  {(char  * )"numTestCases",           &orb_numTestCases                       , INT_32, SINGLE},
  {(char  * )"inImage",                &gConfig_ORB[0].inImage                 , STRING, SINGLE},
  {(char  * )"outImage",               &gConfig_ORB[0].outImage                , STRING, SINGLE},
  {(char  * )"imgFrameWidth",          &gConfig_ORB[0].imgFrameWidth           , INT_16, SINGLE},
  {(char  * )"imgFrameHeight",         &gConfig_ORB[0].imgFrameHeight          , INT_16, SINGLE},
  {(char  * )"imgFramePitch",          &gConfig_ORB[0].imgFramePitch           , INT_16, SINGLE},
  {(char  * )"fast9CornerSelectMethod",&gConfig_ORB[0].fast9CornerSelectMethod , INT_8, SINGLE},
    

  {(char  * )"numLevels",              &gConfig_ORB[0].numLevels               , INT_8,  SINGLE},
  {(char  * )"fast9Threshold",         &gConfig_ORB[0].fast9Threshold          , INT_8 , SINGLE},
  {(char  * )"startX",                 &gConfig_ORB[0].startX                  , INT_16, SINGLE},
  {(char  * )"startY",                 &gConfig_ORB[0].startY                  , INT_16, SINGLE},

  {(char  * )"harrisSensitivityParam", &gConfig_ORB[0].harrisSensitivityParam  , INT_16, SINGLE},
  {(char  * )"totalFeatures",          &gConfig_ORB[0].totalFeatures           , INT_16, SINGLE},

  {(char  * )"fileBased",              &gConfig_ORB[0].fileBased               , INT_8 , SINGLE}
} ;
