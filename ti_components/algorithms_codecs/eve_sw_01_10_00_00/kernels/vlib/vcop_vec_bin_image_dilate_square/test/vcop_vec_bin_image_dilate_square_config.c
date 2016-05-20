/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#include <stdio.h>
#include <stdint.h>
#include "configparser.h"
#include "vcop_vec_bin_image_dilate_square_config.h"

sBin_Morphology_Dilate_Square_Config gConfig_bin_morphology_dilate_square;
sTokenMapping gsTokenMap_bin_morphology_dilate_square[] =
{
  {(char* )"testCaseName",           &gConfig_bin_morphology_dilate_square.testCaseName           , STRING, SINGLE},
  {(char* )"performanceTestcase",    &gConfig_bin_morphology_dilate_square.performanceTestcase    ,  INT_8, SINGLE},
  {(char* )"inImage",                &gConfig_bin_morphology_dilate_square.inImage                , STRING, SINGLE},
  {(char* )"outImage",               &gConfig_bin_morphology_dilate_square.outImage               , STRING, SINGLE},
  {(char* )"blkWidth",               &gConfig_bin_morphology_dilate_square.blkWidth               , INT_16, SINGLE},
  {(char* )"blkStride",              &gConfig_bin_morphology_dilate_square.blkStride              , INT_16, SINGLE},
  {(char* )"blkHeight",              &gConfig_bin_morphology_dilate_square.blkHeight              , INT_16, SINGLE},
  {(char* )"desc",                   &gConfig_bin_morphology_dilate_square.desc                   , STRING, SINGLE},
} ;

