/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#include <stdio.h>
#include "configparser.h"
#include "vcop_census_8bits_config.h"

scensus_8bits_Config gConfig_census_8bits;
sTokenMapping gsTokenMap_census_8bits[MAX_ITEMS_TO_PARSE] =
{
  {(char* )"inputSrc",                &gConfig_census_8bits.inputSrc                 , STRING, SINGLE},
  {(char* )"inFileName",              &gConfig_census_8bits.inFileName               , STRING, SINGLE},
  {(char* )"outFileName",             &gConfig_census_8bits.outFileName              , STRING, SINGLE},
  {(char* )"winWidth",                &gConfig_census_8bits.winWidth                 , INT_8, SINGLE},
  {(char* )"winHeight",               &gConfig_census_8bits.winHeight                , INT_8, SINGLE},
  {(char* )"computeWidth",            &gConfig_census_8bits.computeWidth             , INT_16, SINGLE},
  {(char* )"computeHeight",           &gConfig_census_8bits.computeHeight            , INT_16, SINGLE},
  {(char* )"inStride",                &gConfig_census_8bits.inStride                 , INT_16, SINGLE},
  {(char* )"outStride",               &gConfig_census_8bits.outStride                , INT_16, SINGLE},
  {(char* )"winHorzStep",             &gConfig_census_8bits.winHorzStep              , INT_8, SINGLE},
  {(char* )"winVertStep",             &gConfig_census_8bits.winVertStep              , INT_8, SINGLE},
  {(char* )"numIter",                 &gConfig_census_8bits.numIter                  , INT_8 , SINGLE},
  {(char* )"writeOutput",             &gConfig_census_8bits.writeOutput              , INT_32, SINGLE},
  {(char* )"seedForRND",              &gConfig_census_8bits.seedForRND               , INT_32, SINGLE},
} ;
