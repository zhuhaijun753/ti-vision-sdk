/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#include <stdio.h>
#include "configparser.h"
#include "vcop_weight_computation_config.h"

sweight_computation_Config gConfig_weight_computation;
sTokenMapping gsTokenMap_weight_computation[MAX_ITEMS_TO_PARSE] =
{
  {(char* )"inputSrc",                &gConfig_weight_computation.inputSrc                 , STRING, SINGLE},
  {(char* )"inFileName",              &gConfig_weight_computation.inFileName               , STRING, SINGLE},
  {(char* )"outFileName",             &gConfig_weight_computation.outFileName              , STRING, SINGLE},
  {(char* )"numKeyPoints",            &gConfig_weight_computation.numKeyPoints             , INT_16, SINGLE},
  {(char* )"qFormatMaxFactor",        &gConfig_weight_computation.qFormatMaxFactor         , INT_16, SINGLE},
  {(char* )"outputStride",            &gConfig_weight_computation.outputStride             , INT_16, SINGLE},
  {(char* )"numIter",                 &gConfig_weight_computation.numIter                  , INT_8 , SINGLE},
  {(char* )"writeOutput",             &gConfig_weight_computation.writeOutput              , INT_32, SINGLE},
  {(char* )"seedForRND",              &gConfig_weight_computation.seedForRND               , INT_32, SINGLE},
} ;
