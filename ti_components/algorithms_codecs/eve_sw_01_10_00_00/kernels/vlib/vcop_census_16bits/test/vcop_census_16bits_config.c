/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#include <stdio.h>
#include "configparser.h"
#include "vcop_census_16bits_config.h"

scensus_16bits_Config gConfig_census_16bits;
sTokenMapping gsTokenMap_census_16bits[MAX_ITEMS_TO_PARSE] =
{
  {(char* )"inputSrc",                &gConfig_census_16bits.inputSrc                 , STRING, SINGLE},
  {(char* )"inFileName",              &gConfig_census_16bits.inFileName               , STRING, SINGLE},
  {(char* )"outFileName",             &gConfig_census_16bits.outFileName              , STRING, SINGLE},
  {(char* )"winWidth",                &gConfig_census_16bits.winWidth                 , INT_8, SINGLE},
  {(char* )"winHeight",               &gConfig_census_16bits.winHeight                , INT_8, SINGLE},
  {(char* )"computeWidth",            &gConfig_census_16bits.computeWidth             , INT_16, SINGLE},
  {(char* )"computeHeight",           &gConfig_census_16bits.computeHeight            , INT_16, SINGLE},
  {(char* )"inStride",                &gConfig_census_16bits.inStride                 , INT_16, SINGLE},
  {(char* )"outStride",               &gConfig_census_16bits.outStride                , INT_16, SINGLE},
  {(char* )"winHorzStep",             &gConfig_census_16bits.winHorzStep              , INT_8, SINGLE},
  {(char* )"winVertStep",             &gConfig_census_16bits.winVertStep              , INT_8, SINGLE},
  {(char* )"numIter",                 &gConfig_census_16bits.numIter                  , INT_8 , SINGLE},
  {(char* )"writeOutput",             &gConfig_census_16bits.writeOutput              , INT_32, SINGLE},
  {(char* )"seedForRND",              &gConfig_census_16bits.seedForRND               , INT_32, SINGLE},
} ;
