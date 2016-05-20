/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#include <stdio.h>
#include <stdint.h>
#include "configparser.h"
#include "vcop_canny_non_maximum_suppression_config.h"

sCanny_non_maximum_suppression_Config gConfig_canny_non_maximum_suppression;
sTokenMapping gsTokenMap_canny_non_maximum_suppression[] =
{
  {(char* )"inputData",            &gConfig_canny_non_maximum_suppression.inputData    , STRING, SINGLE},
  {(char* )"width",                &gConfig_canny_non_maximum_suppression.width           , INT_16, SINGLE},
  {(char* )"height",               &gConfig_canny_non_maximum_suppression.height          , INT_16, SINGLE},
  {(char* )"inDataPitch",          &gConfig_canny_non_maximum_suppression.inDataPitch, INT_16, SINGLE},
  {(char* )"outputPitch",          &gConfig_canny_non_maximum_suppression.outputPitch, INT_16, SINGLE},
  {(char* )"lowThreshold",         &gConfig_canny_non_maximum_suppression.lowThreshold, INT_8, SINGLE},
  {(char* )"highThreshold",         &gConfig_canny_non_maximum_suppression.highThreshold, INT_8, SINGLE},
  {(char* )"randSeed",             &gConfig_canny_non_maximum_suppression.randSeed        , INT_32, SINGLE},
  {(char* )"numIter",              &gConfig_canny_non_maximum_suppression.numIter         , INT_8 , SINGLE},
  {(char *)"testCaseName",            &gConfig_canny_non_maximum_suppression.testCaseName         , STRING, SINGLE},
  {(char* )"performanceTestcase",     &gConfig_canny_non_maximum_suppression.performanceTestcase  , INT_8,  SINGLE},
  {(char *)"desc",                    &gConfig_canny_non_maximum_suppression.desc                 , STRING, SINGLE},

} ;

