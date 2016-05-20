/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include "configparser.h"
#include "median_filter_config.h"
#pragma RESET_MISRA ("required")

sMedianFilter_Config gConfig_median_filter;

sTokenMapping gsTokenMap_median_filter[] =
{
  {(char* )"inImg",             &gConfig_median_filter.inImg                , STRING, SINGLE},
  {(char* )"outImg",            &gConfig_median_filter.outImg               , STRING, SINGLE},
  {(char* )"imageWidth",        &gConfig_median_filter.imageWidth           , INT_16, SINGLE},
  {(char* )"imageHeight",       &gConfig_median_filter.imageHeight          , INT_16, SINGLE},
  {(char* )"imagePitch",        &gConfig_median_filter.imagePitch           , INT_16, SINGLE},
  {(char *)"blockWidth",        &gConfig_median_filter.blockWidth           , INT_8 , SINGLE},
  {(char *)"blockHeight",       &gConfig_median_filter.blockHeight          , INT_8 , SINGLE},
  {(char *)"stepSizeHorz",      &gConfig_median_filter.stepSizeHorz         , INT_16, SINGLE},
  {(char *)"stepSizeVert",      &gConfig_median_filter.stepSizeVert         , INT_16, SINGLE},
  {(char* )"randSeed",          &gConfig_median_filter.randSeed             , INT_32, SINGLE},
  {(char* )"numIter",           &gConfig_median_filter.numIter              , INT_8 , SINGLE},
  {(char *)"testCaseName"        ,&gConfig_median_filter.testCaseName         , STRING, SINGLE},
  {(char* )"performanceTestcase" ,&gConfig_median_filter.performanceTestcase  , INT_8,  SINGLE},
  {(char *)"desc"                ,&gConfig_median_filter.desc                 , STRING, SINGLE},
};

