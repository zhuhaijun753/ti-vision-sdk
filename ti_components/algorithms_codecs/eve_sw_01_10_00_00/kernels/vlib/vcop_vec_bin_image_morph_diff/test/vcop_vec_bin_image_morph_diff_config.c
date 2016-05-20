/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#include <stdio.h>
#include <stdint.h>
#include "configparser.h"
#include "vcop_vec_bin_image_morph_diff_config.h"

sBin_Morphology_Morph_Diff_Config gConfig_bin_morphology_morph_diff;
sTokenMapping gsTokenMap_bin_morphology_morph_diff[] =
{
  {(char* )"testCaseName",           &gConfig_bin_morphology_morph_diff.testCaseName           , STRING, SINGLE},
  {(char* )"performanceTestcase",    &gConfig_bin_morphology_morph_diff.performanceTestcase    ,  INT_8, SINGLE},
  {(char* )"inImageA",               &gConfig_bin_morphology_morph_diff.inImageA               , STRING, SINGLE},
  {(char* )"inImageB",               &gConfig_bin_morphology_morph_diff.inImageB               , STRING, SINGLE},
  {(char* )"outImage",               &gConfig_bin_morphology_morph_diff.outImage               , STRING, SINGLE},
  {(char* )"blkWidth",               &gConfig_bin_morphology_morph_diff.blkWidth               , INT_16, SINGLE},
  {(char* )"blkStride",              &gConfig_bin_morphology_morph_diff.blkStride              , INT_16, SINGLE},
  {(char* )"blkHeight",              &gConfig_bin_morphology_morph_diff.blkHeight              , INT_16, SINGLE},
  {(char* )"dataAbitShift",          &gConfig_bin_morphology_morph_diff.dataAbitShift          , INT_16, SINGLE},
  {(char* )"dataBbitShift",          &gConfig_bin_morphology_morph_diff.dataBbitShift          , INT_16, SINGLE},
  {(char* )"desc",                   &gConfig_bin_morphology_morph_diff.desc                   , STRING, SINGLE},
} ;

