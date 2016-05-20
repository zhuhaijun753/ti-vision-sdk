/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#include <stdio.h>
#include <stdint.h>
#include "configparser.h"
#include "vcop_vec_bin_image_erode_cross_config.h"

sBin_Morphology_Erode_Cross_Config gConfig_bin_morphology_erode_cross;
sTokenMapping gsTokenMap_bin_morphology_erode_cross[] =
{
  {(char* )"testCaseName",           &gConfig_bin_morphology_erode_cross.testCaseName           , STRING, SINGLE},
  {(char* )"performanceTestcase",    &gConfig_bin_morphology_erode_cross.performanceTestcase    ,  INT_8, SINGLE},
  {(char* )"inImage",                &gConfig_bin_morphology_erode_cross.inImage                , STRING, SINGLE},
  {(char* )"outImage",               &gConfig_bin_morphology_erode_cross.outImage               , STRING, SINGLE},
  {(char* )"blkWidth",               &gConfig_bin_morphology_erode_cross.blkWidth               , INT_16, SINGLE},
  {(char* )"blkStride",              &gConfig_bin_morphology_erode_cross.blkStride              , INT_16, SINGLE},
  {(char* )"blkHeight",              &gConfig_bin_morphology_erode_cross.blkHeight              , INT_16, SINGLE},
  {(char* )"desc",                   &gConfig_bin_morphology_erode_cross.desc                   , STRING, SINGLE},
} ;

