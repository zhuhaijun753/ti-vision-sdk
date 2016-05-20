/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#include <stdio.h>
#include <stdint.h>
#include "configparser.h"
#include "vcop_median3x3_config.h"

sMedian3x3_Config gConfig_median3x3;
sTokenMapping gsTokenMap_median3x3[] =
{
  {(char* )"inImg",             &gConfig_median3x3.inImg                , STRING, SINGLE},
  {(char* )"outImg",            &gConfig_median3x3.outImg               , STRING, SINGLE},
  {(char* )"blockWidth",        &gConfig_median3x3.blockWidth           , INT_16, SINGLE},
  {(char* )"blockHeight",       &gConfig_median3x3.blockHeight          , INT_16, SINGLE},
  {(char* )"dataType",          &gConfig_median3x3.dataType             , INT_16, SINGLE},
  {(char* )"randSeed",          &gConfig_median3x3.randSeed             , INT_32, SINGLE},
  {(char* )"numIter",           &gConfig_median3x3.numIter              , INT_8 , SINGLE}
} ;
