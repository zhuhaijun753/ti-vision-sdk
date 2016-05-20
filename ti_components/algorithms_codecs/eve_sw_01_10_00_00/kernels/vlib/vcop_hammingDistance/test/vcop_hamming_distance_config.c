/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#include <stdio.h>
#include <stdint.h>
#include "configparser.h"
#include "vcop_hamming_distance_config.h"

sHamming_distance_Config gConfig_hamming_distance;
sTokenMapping gsTokenMap_hamming_distance[] =
{
  {(char* )"inStr1",                 &gConfig_hamming_distance.inStr1                   , STRING, SINGLE},
  {(char* )"inStr2",                 &gConfig_hamming_distance.inStr2                   , STRING, SINGLE},
  {(char* )"outHamDist",             &gConfig_hamming_distance.outHamDist               , STRING, SINGLE},
  {(char* )"testCase",               &gConfig_hamming_distance.testCase                 , INT_8 , SINGLE},
  {(char* )"descLen",                &gConfig_hamming_distance.descLen                  , INT_32, SINGLE},
  {(char* )"descPitch",              &gConfig_hamming_distance.descPitch                , INT_32, SINGLE},
  {(char* )"numDesc1",               &gConfig_hamming_distance.numDesc1                 , INT_32, SINGLE},
  {(char* )"numDesc2",               &gConfig_hamming_distance.numDesc2                 , INT_32, SINGLE},
  {(char* )"mode",                   &gConfig_hamming_distance.mode                     , INT_32, SINGLE},
  {(char* )"minDistanceThres",       &gConfig_hamming_distance.minDistanceThres         , INT_16, SINGLE},
  {(char* )"matchConfidence",        &gConfig_hamming_distance.matchConfidence          , INT_16, SINGLE},
  {(char* )"randSeed1",              &gConfig_hamming_distance.randSeed1                , INT_32, SINGLE},
  {(char* )"randSeed2",              &gConfig_hamming_distance.randSeed2                , INT_32, SINGLE}
} ;
