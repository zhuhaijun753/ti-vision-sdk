/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#include <stdio.h>
#include <stdint.h>
#include "configparser.h"
#include "vcop_harrisScore_7x7_config.h"

sHarris_score_7x7_Config gConfig_harris_score_7x7;
sTokenMapping gsTokenMap_harris_score_7x7[] =
{
  {(char* )"inputBlock",        &gConfig_harris_score_7x7.inputBlock      , STRING, SINGLE},
  {(char* )"outputScore",       &gConfig_harris_score_7x7.outputScore     , STRING, SINGLE},
  {(char* )"width",             &gConfig_harris_score_7x7.width           , INT_16, SINGLE},
  {(char* )"height",            &gConfig_harris_score_7x7.height          , INT_16, SINGLE},
  {(char* )"srcPitch",          &gConfig_harris_score_7x7.srcPitch        , INT_16, SINGLE},
  {(char* )"destPitch",         &gConfig_harris_score_7x7.destPitch       , INT_16, SINGLE},
  {(char* )"sensitivityParam",  &gConfig_harris_score_7x7.sensitivityParam, INT_16, SINGLE},
  {(char* )"randSeed",          &gConfig_harris_score_7x7.randSeed        , INT_32, SINGLE},
  {(char* )"numIter",           &gConfig_harris_score_7x7.numIter         , INT_8 , SINGLE},
} ;

