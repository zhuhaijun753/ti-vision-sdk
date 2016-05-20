/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#include <stdio.h>
#include <stdint.h>
#include "configparser.h"
#include "vcop_yuv420_fir2d_separable_config.h"

sYUV420_fir2d_separable_Config gConfig_yuv420_fir2d_separable;
sTokenMapping gsTokenMap_yuv420_fir2d_separable[] =
{
  {(char* )"inputData",            &gConfig_yuv420_fir2d_separable.inputData    , STRING, SINGLE},
  {(char* )"horzCoefficients",     &gConfig_yuv420_fir2d_separable.horzCoefficients           , INT_8, MULTI},
  {(char* )"vertCoefficients",     &gConfig_yuv420_fir2d_separable.vertCoefficients           , INT_8, MULTI},
  {(char* )"numCoefficients",      &gConfig_yuv420_fir2d_separable.numCoefficients           , INT_8, SINGLE},
  {(char* )"width",                &gConfig_yuv420_fir2d_separable.width           , INT_16, SINGLE},
  {(char* )"height",               &gConfig_yuv420_fir2d_separable.height          , INT_16, SINGLE},
  {(char* )"pitch",                &gConfig_yuv420_fir2d_separable.pitch, INT_16, SINGLE},
  {(char* )"roundBits",            &gConfig_yuv420_fir2d_separable.roundBits, INT_8, SINGLE},
  {(char* )"randSeed",             &gConfig_yuv420_fir2d_separable.randSeed        , INT_32, SINGLE},
  {(char* )"numIter",              &gConfig_yuv420_fir2d_separable.numIter         , INT_8 , SINGLE},
  {(char *)"testCaseName",         &gConfig_yuv420_fir2d_separable.testCaseName         , STRING, SINGLE},
  {(char* )"performanceTestcase",  &gConfig_yuv420_fir2d_separable.performanceTestcase  , INT_8,  SINGLE},
  {(char *)"desc",                 &gConfig_yuv420_fir2d_separable.desc                 , STRING, SINGLE},
} ;

