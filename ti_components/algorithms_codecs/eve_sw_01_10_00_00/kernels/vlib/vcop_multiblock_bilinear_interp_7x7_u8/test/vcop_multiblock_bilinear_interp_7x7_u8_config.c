/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#include <stdio.h>
#include "configparser.h"
#include "vcop_multiblock_bilinear_interp_7x7_u8_config.h"

smultiblock_bilinear_interp_7x7_u8_Config gConfig_multiblock_bilinear_interp_7x7_u8;
sTokenMapping gsTokenMap_multiblock_bilinear_interp_7x7_u8[MAX_ITEMS_TO_PARSE] =
{
  {(char* )"inputSrc",                &gConfig_multiblock_bilinear_interp_7x7_u8.inputSrc                 , STRING, SINGLE},
  {(char* )"inFileName1",             &gConfig_multiblock_bilinear_interp_7x7_u8.inFileName1              , STRING, SINGLE},
  {(char* )"inFileName2",             &gConfig_multiblock_bilinear_interp_7x7_u8.inFileName2              , STRING, SINGLE},
  {(char* )"outFileName",             &gConfig_multiblock_bilinear_interp_7x7_u8.outFileName              , STRING, SINGLE},
  {(char* )"input1Stride",            &gConfig_multiblock_bilinear_interp_7x7_u8.input1Stride             , INT_16, SINGLE},
  {(char* )"input2Stride",            &gConfig_multiblock_bilinear_interp_7x7_u8.input2Stride             , INT_16, SINGLE},
  {(char* )"outputStride",            &gConfig_multiblock_bilinear_interp_7x7_u8.outputStride             , INT_16, SINGLE},
  {(char* )"blkWidth",                &gConfig_multiblock_bilinear_interp_7x7_u8.blkWidth                 , INT_16, SINGLE},
  {(char* )"blkHeight",               &gConfig_multiblock_bilinear_interp_7x7_u8.blkHeight                , INT_16, SINGLE},
  {(char* )"blkOffset",               &gConfig_multiblock_bilinear_interp_7x7_u8.blkOffset                , INT_16, SINGLE},
  {(char* )"numKeyPoints",            &gConfig_multiblock_bilinear_interp_7x7_u8.numKeyPoints             , INT_16, SINGLE},
  {(char* )"numIter",                 &gConfig_multiblock_bilinear_interp_7x7_u8.numIter                  , INT_8 , SINGLE},
  {(char* )"writeOutput",             &gConfig_multiblock_bilinear_interp_7x7_u8.writeOutput              , INT_32, SINGLE},
  {(char* )"seedForRND",              &gConfig_multiblock_bilinear_interp_7x7_u8.seedForRND               , INT_32, SINGLE},
} ;
