/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#include <stdio.h>
#include "configparser.h"
#include "vcop_multiblock_gradient_xy_config.h"

smultiblock_gradient_xy_Config gConfig_multiblock_gradient;
sTokenMapping gsTokenMap_multiblock_gradient[MAX_ITEMS_TO_PARSE] =
{
  {(char* )"inputSrc",                &gConfig_multiblock_gradient.inputSrc                 , STRING, SINGLE},
  {(char* )"inFileName",              &gConfig_multiblock_gradient.inFileName               , STRING, SINGLE},
  {(char* )"outFileName",             &gConfig_multiblock_gradient.outFileName              , STRING, SINGLE},
  {(char* )"inputStride",             &gConfig_multiblock_gradient.inputStride              , INT_16, SINGLE},
  {(char* )"blkWidth",                &gConfig_multiblock_gradient.blkWidth                 , INT_16, SINGLE},
  {(char* )"blkHeight",               &gConfig_multiblock_gradient.blkHeight                , INT_16, SINGLE},
  {(char* )"blkOffset",               &gConfig_multiblock_gradient.blkOffset                , INT_16, SINGLE},
  {(char* )"numBlocks",               &gConfig_multiblock_gradient.numBlocks                , INT_16, SINGLE},
  {(char* )"numIter",                 &gConfig_multiblock_gradient.numIter                  , INT_8 , SINGLE},
  {(char* )"writeOutput",             &gConfig_multiblock_gradient.writeOutput              , INT_32, SINGLE},
  {(char* )"seedForRND",              &gConfig_multiblock_gradient.seedForRND               , INT_32, SINGLE},
} ;
