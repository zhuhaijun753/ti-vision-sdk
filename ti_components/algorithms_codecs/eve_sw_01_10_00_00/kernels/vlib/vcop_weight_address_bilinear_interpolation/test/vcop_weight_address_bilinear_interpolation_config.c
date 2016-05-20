/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#include <stdio.h>
#include "configparser.h"
#include "vcop_weight_address_bilinear_interpolation_config.h"

sweight_address_bilinear_interpolation_Config gConfig_weight_address_bilinear_interpolation;
sTokenMapping gsTokenMap_weight_address_bilinear_interpolation[MAX_ITEMS_TO_PARSE] =
{
  {(char* )"inputSrc",                &gConfig_weight_address_bilinear_interpolation.inputSrc                 , STRING, SINGLE},
  {(char* )"inFileName1",             &gConfig_weight_address_bilinear_interpolation.inFileName1              , STRING, SINGLE},
  {(char* )"inFileName2",             &gConfig_weight_address_bilinear_interpolation.inFileName2              , STRING, SINGLE},
  {(char* )"inFileName3",             &gConfig_weight_address_bilinear_interpolation.inFileName3              , STRING, SINGLE},
  {(char* )"outFileName1",            &gConfig_weight_address_bilinear_interpolation.outFileName1             , STRING, SINGLE},
  {(char* )"outFileName2",            &gConfig_weight_address_bilinear_interpolation.outFileName2             , STRING, SINGLE},
  {(char* )"numKeyPoints",            &gConfig_weight_address_bilinear_interpolation.numKeyPoints             , INT_16, SINGLE},
  {(char* )"qFormatMaxFactor",        &gConfig_weight_address_bilinear_interpolation.qFormatMaxFactor         , INT_16, SINGLE},
  {(char* )"qShift",                  &gConfig_weight_address_bilinear_interpolation.qShift                   , INT_16, SINGLE},
  {(char* )"blkStride",               &gConfig_weight_address_bilinear_interpolation.blkStride                , INT_16, SINGLE},
  {(char* )"outputStride",            &gConfig_weight_address_bilinear_interpolation.outputStride             , INT_16, SINGLE},
  {(char* )"numIter",                 &gConfig_weight_address_bilinear_interpolation.numIter                  , INT_8 , SINGLE},
  {(char* )"writeOutput",             &gConfig_weight_address_bilinear_interpolation.writeOutput              , INT_32, SINGLE},
  {(char* )"seedForRND",              &gConfig_weight_address_bilinear_interpolation.seedForRND               , INT_32, SINGLE},
} ;
