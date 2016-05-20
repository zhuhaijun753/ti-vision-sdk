/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include "configparser.h"
#include "soft_isp_config.h"
#pragma RESET_MISRA ("required")

sSoftIsp_Config gConfig_soft_isp;

sTokenMapping gsTokenMap_soft_isp[] =
{
  {(char* )"inImg",             &gConfig_soft_isp.inImg                , STRING, SINGLE},
  {(char* )"gbceToneCurve",     &gConfig_soft_isp.gbceToneCurve        , STRING, SINGLE},
  {(char* )"outImg",            &gConfig_soft_isp.outImg               , STRING, SINGLE},
  {(char* )"imageWidth",        &gConfig_soft_isp.imageWidth           , INT_16, SINGLE},
  {(char* )"imageHeight",       &gConfig_soft_isp.imageHeight          , INT_16, SINGLE},
  {(char* )"imagePitch",        &gConfig_soft_isp.imagePitch           , INT_16, SINGLE},
  {(char* )"rPosition",         &gConfig_soft_isp.rPosition            , INT_8 , SINGLE},
  {(char* )"sensorBitDepth",    &gConfig_soft_isp.sensorBitDepth       , INT_8 , SINGLE},
  {(char* )"maxPixValue",       &gConfig_soft_isp.maxPixValue          , INT_16, SINGLE},
  {(char* )"enableDecompand",   &gConfig_soft_isp.enableDecompand      , INT_8 , SINGLE},
  {(char* )"pout1",             &gConfig_soft_isp.pout1                , INT_16, SINGLE},
  {(char* )"pout2",             &gConfig_soft_isp.pout2                , INT_16, SINGLE},
  {(char* )"slope1",            &gConfig_soft_isp.slope1               , INT_8 , SINGLE},
  {(char* )"slope2",            &gConfig_soft_isp.slope2               , INT_16, SINGLE},
  {(char* )"blackClamp0",       &gConfig_soft_isp.blackClamp[0]        , INT_8 , SINGLE},
  {(char* )"blackClamp1",       &gConfig_soft_isp.blackClamp[1]        , INT_8 , SINGLE},
  {(char* )"blackClamp2",       &gConfig_soft_isp.blackClamp[2]        , INT_8 , SINGLE},
  {(char* )"blackClamp3",       &gConfig_soft_isp.blackClamp[3]        , INT_8 , SINGLE},
  {(char* )"cBalanceGain0",     &gConfig_soft_isp.cBalanceGain[0]      , INT_8 , SINGLE},
  {(char* )"cBalanceGain1",     &gConfig_soft_isp.cBalanceGain[1]      , INT_8 , SINGLE},
  {(char* )"cBalanceGain2",     &gConfig_soft_isp.cBalanceGain[2]      , INT_8 , SINGLE},
  {(char* )"cBalanceGain3",     &gConfig_soft_isp.cBalanceGain[3]      , INT_8 , SINGLE},
  {(char* )"cBalanceShift",     &gConfig_soft_isp.cBalanceShift        , INT_8 , SINGLE},
  {(char* )"enableExtractR",    &gConfig_soft_isp.enableExtractR       , INT_8 , SINGLE},
  {(char* )"enableStats",       &gConfig_soft_isp.enableStats          , INT_8 , SINGLE},
  {(char* )"statBlkWidth",      &gConfig_soft_isp.statBlkWidth         , INT_16, SINGLE},
  {(char* )"statBlkHeight",     &gConfig_soft_isp.statBlkHeight        , INT_16, SINGLE},
  {(char* )"saturationLimit",   &gConfig_soft_isp.saturationLimit      , INT_16, SINGLE},
  {(char* )"gbceMethod",        &gConfig_soft_isp.gbceMethod           , INT_8 , SINGLE},
  {(char* )"randSeed",          &gConfig_soft_isp.randSeed             , INT_32, SINGLE},
  {(char* )"numIter",           &gConfig_soft_isp.numIter              , INT_8 , SINGLE},
  {(char* )"testCaseName",        &gConfig_soft_isp.testCaseName         , STRING, SINGLE},
  {(char* )"performanceTestcase", &gConfig_soft_isp.performanceTestcase  ,  INT_8, SINGLE},
  {(char* )"desc",                &gConfig_soft_isp.testCaseDesc         , STRING, SINGLE},
} ;

