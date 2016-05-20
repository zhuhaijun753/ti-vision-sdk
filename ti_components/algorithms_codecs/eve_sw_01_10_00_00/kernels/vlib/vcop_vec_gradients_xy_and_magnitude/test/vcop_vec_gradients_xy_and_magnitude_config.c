/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#include <stdio.h>
#include <stdint.h>
#include "configparser.h"
#include "vcop_vec_gradients_xy_and_magnitude_config.h"

sGradient_xy_magnitude_Config gConfig_gradient_xy_magnitude;
sTokenMapping gsTokenMap_gradient_xy_magnitude[] =
{
  {(char* )"inputData",            &gConfig_gradient_xy_magnitude.inputData    , STRING, SINGLE},
  {(char* )"width",                &gConfig_gradient_xy_magnitude.width           , INT_16, SINGLE},
  {(char* )"height",               &gConfig_gradient_xy_magnitude.height          , INT_16, SINGLE},
  {(char* )"inDataPitch",          &gConfig_gradient_xy_magnitude.inDataPitch, INT_16, SINGLE},
  {(char* )"edgeMapPitch",         &gConfig_gradient_xy_magnitude.edgeMapPitch, INT_16, SINGLE},
  {(char* )"randSeed",             &gConfig_gradient_xy_magnitude.randSeed        , INT_32, SINGLE},
  {(char* )"numIter",              &gConfig_gradient_xy_magnitude.numIter         , INT_8 , SINGLE},
} ;

