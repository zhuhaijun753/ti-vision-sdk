/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#include <stdio.h>
#include <stdint.h>
#include "configparser.h"
#include "vcop_nonMaxSuppress_mxn_32s_config.h"

sNms_mxn_32s_Config gConfig_nms_mxn_32s;
sTokenMapping gsTokenMap_nms_mxn_32s[] =
{
  {(char* )"inputImage",        &gConfig_nms_mxn_32s.inputImage       , STRING, SINGLE},
  {(char* )"outputImage",       &gConfig_nms_mxn_32s.outputImage      , STRING, SINGLE},
  {(char* )"width",             &gConfig_nms_mxn_32s.width            , INT_16, SINGLE},
  {(char* )"height",            &gConfig_nms_mxn_32s.height           , INT_16, SINGLE},
  {(char* )"inputStride",       &gConfig_nms_mxn_32s.inputStride      , INT_16, SINGLE},
  {(char* )"outputStride",      &gConfig_nms_mxn_32s.outputStride     , INT_16, SINGLE},
  {(char* )"windowWidth",       &gConfig_nms_mxn_32s.windowWidth      , INT_16, SINGLE},
  {(char* )"windowHeight",      &gConfig_nms_mxn_32s.windowHeight     , INT_16, SINGLE},
  {(char* )"nmsThreshold",      &gConfig_nms_mxn_32s.nmsThreshold     , INT_16, SINGLE},
  {(char* )"outputFormat",      &gConfig_nms_mxn_32s.outputFormat     , INT_8, SINGLE},
  {(char* )"randSeed",          &gConfig_nms_mxn_32s.randSeed         , INT_32, SINGLE},
  {(char* )"numIter",           &gConfig_nms_mxn_32s.numIter          , INT_8 , SINGLE},
  {(char* )"testCaseName",           &gConfig_nms_mxn_32s.testCaseName           , STRING, SINGLE},
  {(char* )"performanceTestcase",    &gConfig_nms_mxn_32s.performanceTestcase    ,  INT_8, SINGLE},
  {(char* )"desc",                   &gConfig_nms_mxn_32s.desc                   , STRING, SINGLE},

} ;

