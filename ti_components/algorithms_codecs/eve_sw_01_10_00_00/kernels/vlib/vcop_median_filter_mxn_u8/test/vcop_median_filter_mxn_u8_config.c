/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#include <stdio.h>
#include <stdint.h>

#include "vcop_median_filter_mxn_u8_config.h"

sMedianFilter_mxn_u8_Config gConfig_median_filter_mxn_u8;
sTokenMapping gsTokenMap_median_filter_mxn_u8[] =
{
  {(char* )"inImg",                  &gConfig_median_filter_mxn_u8.inImg                    , STRING, SINGLE},
  {(char* )"outImg",                 &gConfig_median_filter_mxn_u8.outImg                   , STRING, SINGLE},
  {(char* )"blkWidth",               &gConfig_median_filter_mxn_u8.blkWidth                 , INT_16, SINGLE},
  {(char* )"blkHeight",              &gConfig_median_filter_mxn_u8.blkHeight                , INT_16, SINGLE},
  {(char* )"blkPitch",               &gConfig_median_filter_mxn_u8.blkPitch                 , INT_16, SINGLE},
  {(char* )"kernelWidth",            &gConfig_median_filter_mxn_u8.kernelWidth              , INT_8 , SINGLE},
  {(char* )"kernelHeight",           &gConfig_median_filter_mxn_u8.kernelHeight             , INT_8 , SINGLE},
  {(char* )"stepSizeHorz",           &gConfig_median_filter_mxn_u8.stepSizeHorz             , INT_16, SINGLE},
  {(char* )"stepSizeVert",           &gConfig_median_filter_mxn_u8.stepSizeVert             , INT_16, SINGLE},
  {(char* )"randSeed",               &gConfig_median_filter_mxn_u8.randSeed                 , INT_32, SINGLE},
  {(char* )"numIter",                &gConfig_median_filter_mxn_u8.numIter                  , INT_8 , SINGLE}
};

