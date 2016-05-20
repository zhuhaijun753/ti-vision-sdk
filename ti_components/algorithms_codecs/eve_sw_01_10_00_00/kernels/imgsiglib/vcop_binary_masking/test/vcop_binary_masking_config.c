/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#include <stdio.h>
#include <stdint.h>
#include "configparser.h"
#include "vcop_binary_masking_config.h"

sBinary_masking_Config gConfig_binary_masking;
sTokenMapping gsTokenMap_binary_masking[] =
{
  {(char* )"inByteData",              &gConfig_binary_masking.inByteData    , STRING, SINGLE},
  {(char* )"inBitPackedData",         &gConfig_binary_masking.inBitPackedData    , STRING, SINGLE},
  {(char* )"outBitPackedData",        &gConfig_binary_masking.outBitPackedData   , STRING, SINGLE},
  {(char* )"blockWidth",              &gConfig_binary_masking.blockWidth   , INT_8, SINGLE},
  {(char* )"blockHeight",             &gConfig_binary_masking.blockHeight  ,  INT_8, SINGLE},
  {(char* )"inputByteDataPitch",      &gConfig_binary_masking.inputByteDataPitch   , INT_16, SINGLE},
  {(char* )"inputBitDataPitch",       &gConfig_binary_masking.inputBitDataPitch   , INT_16, SINGLE},
  {(char* )"outputPitch",             &gConfig_binary_masking.outputPitch  , INT_16, SINGLE},
  {(char* )"randSeed",                &gConfig_binary_masking.randSeed     , INT_32, SINGLE},
  {(char* )"numIter",                 &gConfig_binary_masking.numIter      ,  INT_8, SINGLE},
  {(char *)"testCaseName",            &gConfig_binary_masking.testCaseName         , STRING, SINGLE},
  {(char* )"performanceTestcase",     &gConfig_binary_masking.performanceTestcase  , INT_8,  SINGLE},
  {(char *)"desc",                    &gConfig_binary_masking.desc                 , STRING, SINGLE},
} ;

