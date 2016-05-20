/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#include <stdio.h>
#include <stdint.h>
#include "configparser.h"
#include "vcop_intensity_scaling_config.h"

sIntensityScaling_Config gConfig_intensity_scaling;
sTokenMapping gsTokenMap_intensity_scaling[] =
{
  {(char* )"inImg",            &gConfig_intensity_scaling.inImg               , STRING, SINGLE},
  {(char* )"outImg",           &gConfig_intensity_scaling.outImg              , STRING, SINGLE},
  {(char* )"imageWidth",       &gConfig_intensity_scaling.imageWidth          , INT_16, SINGLE},
  {(char* )"imageHeight",      &gConfig_intensity_scaling.imageHeight         , INT_16, SINGLE},
  {(char* )"imagePitch",       &gConfig_intensity_scaling.imagePitch          , INT_16, SINGLE},
  {(char* )"loPixelVal",       &gConfig_intensity_scaling.loPixelVal          , INT_8 , SINGLE},
  {(char* )"hiPixelVal",       &gConfig_intensity_scaling.hiPixelVal          , INT_8 , SINGLE},
  {(char* )"numLevels",        &gConfig_intensity_scaling.numLevels           , INT_8 , SINGLE},
  {(char* )"randSeed",         &gConfig_intensity_scaling.randSeed            , INT_32, SINGLE},
  {(char* )"numIter",          &gConfig_intensity_scaling.numIter             , INT_8 , SINGLE}
};
