/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#include <stdio.h>
#include "configparser.h"
#include "vcop_foreach_multiblock_bilinear_interp_7x7_u8_config.h"

sforeach_multiblock_bilinear_interp_7x7_u8_Config gConfig_foreach_multiblock_bilinear_interp_7x7_u8;
sTokenMapping gsTokenMap_foreach_multiblock_bilinear_interp_7x7_u8[MAX_ITEMS_TO_PARSE] =
{
  {(char* )"inputSrc",                &gConfig_foreach_multiblock_bilinear_interp_7x7_u8.inputSrc                 , STRING, SINGLE},
  {(char* )"inFileName1",             &gConfig_foreach_multiblock_bilinear_interp_7x7_u8.inFileName1              , STRING, SINGLE},
  {(char* )"inFileName2",             &gConfig_foreach_multiblock_bilinear_interp_7x7_u8.inFileName2              , STRING, SINGLE},
  {(char* )"outFileName",             &gConfig_foreach_multiblock_bilinear_interp_7x7_u8.outFileName              , STRING, SINGLE},
  {(char* )"input1Stride",            &gConfig_foreach_multiblock_bilinear_interp_7x7_u8.input1Stride             , INT_16, SINGLE},
  {(char* )"input2Stride",            &gConfig_foreach_multiblock_bilinear_interp_7x7_u8.input2Stride             , INT_16, SINGLE},
  {(char* )"outputStride",            &gConfig_foreach_multiblock_bilinear_interp_7x7_u8.outputStride             , INT_16, SINGLE},
  {(char* )"outBlkWidth",             &gConfig_foreach_multiblock_bilinear_interp_7x7_u8.outBlkWidth              , INT_16, SINGLE},
  {(char* )"outBlkHeight",            &gConfig_foreach_multiblock_bilinear_interp_7x7_u8.outBlkHeight             , INT_16, SINGLE},
  {(char* )"numKeyPoints",            &gConfig_foreach_multiblock_bilinear_interp_7x7_u8.numKeyPoints             , INT_16, SINGLE},
  {(char* )"numIter",                 &gConfig_foreach_multiblock_bilinear_interp_7x7_u8.numIter                  , INT_8 , SINGLE},
  {(char* )"writeOutput",             &gConfig_foreach_multiblock_bilinear_interp_7x7_u8.writeOutput              , INT_32, SINGLE},
  {(char* )"seedForRND",              &gConfig_foreach_multiblock_bilinear_interp_7x7_u8.seedForRND               , INT_32, SINGLE},
} ;
