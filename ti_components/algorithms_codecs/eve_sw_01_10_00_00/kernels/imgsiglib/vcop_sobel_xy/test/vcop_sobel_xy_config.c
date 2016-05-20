/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#include <stdio.h>
#include <stdint.h>
#include "configparser.h"
#include "vcop_sobel_xy_config.h"

sSobel_Xy_Config gConfig_sobel_xy;
sTokenMapping gsTokenMap_sobel_xy[] =
{
  {(char* )"inputData",               &gConfig_sobel_xy.inputData    , STRING, SINGLE},
  {(char* )"outputData",              &gConfig_sobel_xy.outputData   , STRING, SINGLE},
  {(char* )"blockWidth",              &gConfig_sobel_xy.blockWidth   , INT_8, SINGLE},
  {(char* )"blockHeight",             &gConfig_sobel_xy.blockHeight  ,  INT_8, SINGLE},
  {(char* )"inputPitch",              &gConfig_sobel_xy.inputPitch   , INT_16, SINGLE},
  {(char* )"outputPitch",             &gConfig_sobel_xy.outputPitch  , INT_16, SINGLE},
  {(char* )"kernelSize",              &gConfig_sobel_xy.kernelSize  , INT_8, SINGLE},
  {(char* )"threshold",               &gConfig_sobel_xy.threshold  , INT_16, SINGLE},
  {(char* )"randSeed",                &gConfig_sobel_xy.randSeed     , INT_32, SINGLE},
  {(char* )"numIter",                 &gConfig_sobel_xy.numIter      ,  INT_8, SINGLE},
  {(char *)"testCaseName",            &gConfig_sobel_xy.testCaseName         , STRING, SINGLE},
  {(char* )"performanceTestcase",     &gConfig_sobel_xy.performanceTestcase  , INT_8,  SINGLE},
  {(char *)"desc",                    &gConfig_sobel_xy.desc                 , STRING, SINGLE},
} ;

