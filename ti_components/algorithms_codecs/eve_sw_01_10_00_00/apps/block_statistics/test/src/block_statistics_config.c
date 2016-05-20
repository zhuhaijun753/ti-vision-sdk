/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include "configparser.h"
#include "block_statistics_config.h"
#pragma RESET_MISRA ("required")

sBlockStatistics_Config gConfig_block_statistics;

sTokenMapping gsTokenMap_block_statistics[] =
{
  {(char*)"inImg",             &gConfig_block_statistics.inImg                , STRING, SINGLE},
  {(char*)"outImg",            &gConfig_block_statistics.outImg               , STRING, SINGLE},
  {(char*)"imageWidth",        &gConfig_block_statistics.imageWidth           , INT_16, SINGLE},
  {(char*)"imageHeight",       &gConfig_block_statistics.imageHeight          , INT_16, SINGLE},
  {(char*)"imagePitch",        &gConfig_block_statistics.imagePitch           , INT_16, SINGLE},
  {(char*)"statBlockWidth",    &gConfig_block_statistics.statBlockWidth       , INT_16, SINGLE},
  {(char*)"statBlockHeight",   &gConfig_block_statistics.statBlockHeight      , INT_16, SINGLE},
  {(char*)"randSeed",          &gConfig_block_statistics.randSeed             , INT_32, SINGLE},
  {(char*)"numIter",           &gConfig_block_statistics.numIter              , INT_8 , SINGLE},
  {(char*)"testCaseName",           &gConfig_block_statistics.testCaseName         , STRING, SINGLE},
  {(char*)"performanceTestcase",    &gConfig_block_statistics.performanceTestcase  ,  INT_8, SINGLE},
  {(char*)"desc",                   &gConfig_block_statistics.testCaseDesc         , STRING, SINGLE},
};

