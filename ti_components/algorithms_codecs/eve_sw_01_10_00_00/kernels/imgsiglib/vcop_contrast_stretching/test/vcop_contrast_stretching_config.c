/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#include <stdio.h>
#include <stdint.h>
#include "configparser.h"
#include "vcop_contrast_stretching_config.h"

sContrastStretching_Config gConfig_contrast_stretching;
sTokenMapping gsTokenMap_contrast_stretching[] =
{
  {(char* )"inputImage",        &gConfig_contrast_stretching.inputImage           , STRING, SINGLE},
  {(char* )"outputImage",       &gConfig_contrast_stretching.outputImage          , STRING, SINGLE},
  {(char* )"imageWidth",        &gConfig_contrast_stretching.imageWidth           , INT_16, SINGLE},
  {(char* )"imageHeight",       &gConfig_contrast_stretching.imageHeight          , INT_16, SINGLE},
  {(char* )"inputPitch",        &gConfig_contrast_stretching.inputPitch           , INT_16, SINGLE},
  {(char* )"outputPitch",       &gConfig_contrast_stretching.outputPitch          , INT_16, SINGLE},
  {(char* )"randSeed",          &gConfig_contrast_stretching.randSeed             , INT_32, SINGLE},
  {(char* )"numIter",           &gConfig_contrast_stretching.numIter              , INT_8 , SINGLE}
} ;

