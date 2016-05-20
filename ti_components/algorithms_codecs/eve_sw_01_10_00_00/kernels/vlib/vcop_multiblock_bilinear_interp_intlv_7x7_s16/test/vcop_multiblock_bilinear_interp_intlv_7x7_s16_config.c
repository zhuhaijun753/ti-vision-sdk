/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#include <stdio.h>
#include "configparser.h"
#include "vcop_multiblock_bilinear_interp_intlv_7x7_s16_config.h"

smultiblock_bilinear_interp_intlv_7x7_s16_Config gConfig_multiblock_bilinear_interp_intlv_7x7_s16;
sTokenMapping gsTokenMap_multiblock_bilinear_interp_intlv_7x7_s16[MAX_ITEMS_TO_PARSE] =
{
  {(char* )"inputSrc",                &gConfig_multiblock_bilinear_interp_intlv_7x7_s16.inputSrc                 , STRING, SINGLE},
  {(char* )"inFileName1",             &gConfig_multiblock_bilinear_interp_intlv_7x7_s16.inFileName1              , STRING, SINGLE},
  {(char* )"inFileName2",             &gConfig_multiblock_bilinear_interp_intlv_7x7_s16.inFileName2              , STRING, SINGLE},
  {(char* )"outFileName1",            &gConfig_multiblock_bilinear_interp_intlv_7x7_s16.outFileName1             , STRING, SINGLE},
  {(char* )"outFileName2",            &gConfig_multiblock_bilinear_interp_intlv_7x7_s16.outFileName2             , STRING, SINGLE},
  {(char* )"input1Stride",            &gConfig_multiblock_bilinear_interp_intlv_7x7_s16.input1Stride             , INT_16, SINGLE},
  {(char* )"input2Stride",            &gConfig_multiblock_bilinear_interp_intlv_7x7_s16.input2Stride             , INT_16, SINGLE},
  {(char* )"outputStride",            &gConfig_multiblock_bilinear_interp_intlv_7x7_s16.outputStride             , INT_16, SINGLE},
  {(char* )"blkWidth",                &gConfig_multiblock_bilinear_interp_intlv_7x7_s16.blkWidth                 , INT_16, SINGLE},
  {(char* )"blkHeight",               &gConfig_multiblock_bilinear_interp_intlv_7x7_s16.blkHeight                , INT_16, SINGLE},
  {(char* )"blkOffset",               &gConfig_multiblock_bilinear_interp_intlv_7x7_s16.blkOffset                , INT_16, SINGLE},
  {(char* )"numKeyPoints",            &gConfig_multiblock_bilinear_interp_intlv_7x7_s16.numKeyPoints             , INT_16, SINGLE},
  {(char* )"numIter",                 &gConfig_multiblock_bilinear_interp_intlv_7x7_s16.numIter                  , INT_8 , SINGLE},
  {(char* )"writeOutput",             &gConfig_multiblock_bilinear_interp_intlv_7x7_s16.writeOutput              , INT_32, SINGLE},
  {(char* )"seedForRND",              &gConfig_multiblock_bilinear_interp_intlv_7x7_s16.seedForRND               , INT_32, SINGLE},
} ;
