/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#include <stdio.h>
#include <stdint.h>
#include "configparser.h"
#include "vcop_vec_bin_image_erode_mask_config.h"

sBin_Morphology_Erode_Mask_Config gConfig_bin_morphology_erode_mask;
sTokenMapping gsTokenMap_bin_morphology_erode_mask[] =
{
  {(char* )"testCaseName",           &gConfig_bin_morphology_erode_mask.testCaseName           , STRING, SINGLE},
  {(char* )"performanceTestcase",    &gConfig_bin_morphology_erode_mask.performanceTestcase    ,  INT_8, SINGLE},
  {(char* )"inImage",                &gConfig_bin_morphology_erode_mask.inImage                , STRING, SINGLE},
  {(char* )"outImage",               &gConfig_bin_morphology_erode_mask.outImage               , STRING, SINGLE},
  {(char* )"seCoefficient",          &gConfig_bin_morphology_erode_mask.seCoefficient          ,  INT_8, MULTI },
  {(char* )"blkWidth",               &gConfig_bin_morphology_erode_mask.blkWidth               , INT_16, SINGLE},
  {(char* )"blkStride",              &gConfig_bin_morphology_erode_mask.blkStride              , INT_16, SINGLE},
  {(char* )"blkHeight",              &gConfig_bin_morphology_erode_mask.blkHeight              , INT_16, SINGLE},
  {(char* )"desc",                   &gConfig_bin_morphology_erode_mask.desc                   , STRING, SINGLE},
} ;

