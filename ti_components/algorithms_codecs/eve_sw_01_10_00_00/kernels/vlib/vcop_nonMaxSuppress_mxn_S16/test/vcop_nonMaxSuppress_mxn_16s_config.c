/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#include <stdio.h>
#include <stdint.h>
#include "configparser.h"
#include "vcop_nonMaxSuppress_mxn_16s_config.h"

sNms_mxn_16s_Config gConfig_nms_mxn_16s;
sTokenMapping gsTokenMap_nms_mxn_16s[] =
{
  {(char* )"inputImage",        &gConfig_nms_mxn_16s.inputImage       , STRING, SINGLE},
  {(char* )"outputImage",       &gConfig_nms_mxn_16s.outputImage      , STRING, SINGLE},
  {(char* )"width",             &gConfig_nms_mxn_16s.width            , INT_16, SINGLE},
  {(char* )"height",            &gConfig_nms_mxn_16s.height           , INT_16, SINGLE},
  {(char* )"inputStride",       &gConfig_nms_mxn_16s.inputStride      , INT_16, SINGLE},
  {(char* )"outputStride",      &gConfig_nms_mxn_16s.outputStride     , INT_16, SINGLE},
  {(char* )"windowWidth",       &gConfig_nms_mxn_16s.windowWidth      , INT_16, SINGLE},
  {(char* )"windowHeight",      &gConfig_nms_mxn_16s.windowHeight     , INT_16, SINGLE},
  {(char* )"nmsThreshold",      &gConfig_nms_mxn_16s.nmsThreshold     , INT_16, SINGLE},
  {(char* )"randSeed",          &gConfig_nms_mxn_16s.randSeed         , INT_32, SINGLE},
  {(char* )"numIter",           &gConfig_nms_mxn_16s.numIter          , INT_8 , SINGLE},
} ;

