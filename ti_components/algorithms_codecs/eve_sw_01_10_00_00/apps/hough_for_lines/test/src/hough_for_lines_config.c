/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include "configparser.h"
#include "hough_for_lines_config.h"
#pragma RESET_MISRA ("required")

uint32_t houghForLines_numTestCases;
sHoughForLines_Config gConfig_houghForLines[HOUGH_FOR_LINES_NUM_MAX_TESTCASES];

sTokenMapping gsTokenMap_houghForLines[] =
{
  {(char *)"numTestCases"        ,&houghForLines_numTestCases              , INT_32, SINGLE},
  {(char *)"edgeMapList"         ,&gConfig_houghForLines[0].edgeMapList    , STRING, SINGLE},
  {(char *)"votedRhoThetaSpace" ,&gConfig_houghForLines[0].votedRhoThetaSpace, STRING, SINGLE},
  {(char *)"refImage"        ,&gConfig_houghForLines[0].refImage       , STRING, SINGLE},
  {(char *)"srcImageWidth"   ,&gConfig_houghForLines[0].srcImageWidth  , INT_16, SINGLE},
  {(char *)"srcImageHeight"  ,&gConfig_houghForLines[0].srcImageHeight , INT_16, SINGLE},
  {(char* )"listSize",        &gConfig_houghForLines[0].listSize        , INT_32, SINGLE},
  {(char* )"thetaStart",      &gConfig_houghForLines[0].thetaStart      , INT_16, SINGLE},
  {(char* )"thetaEnd",        &gConfig_houghForLines[0].thetaEnd        , INT_16, SINGLE},
  {(char* )"thetaStepSize",   &gConfig_houghForLines[0].thetaStepSize   , INT_8, SINGLE},
  {(char* )"rhoMaxLength",    &gConfig_houghForLines[0].rhoMaxLength    , INT_16, SINGLE},
  {(char* )"randSeed",        &gConfig_houghForLines[0].randSeed        , INT_32, SINGLE},
  {(char* )"testCaseName",           &gConfig_houghForLines[0].testCaseName           , STRING, SINGLE},
  {(char* )"performanceTestcase",    &gConfig_houghForLines[0].performanceTestcase    ,  INT_8, SINGLE},
  {(char* )"desc",                   &gConfig_houghForLines[0].desc                   , STRING, SINGLE}

} ;

