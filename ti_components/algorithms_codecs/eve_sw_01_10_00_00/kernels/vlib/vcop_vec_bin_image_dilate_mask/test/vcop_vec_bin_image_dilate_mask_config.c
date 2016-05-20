/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#include <stdio.h>
#include <stdint.h>
#include "configparser.h"
#include "vcop_vec_bin_image_dilate_mask_config.h"

sBin_Morphology_Dilate_Mask_Config gConfig_bin_morphology_dilate_mask;
sTokenMapping gsTokenMap_bin_morphology_dilate_mask[] =
{
  {(char* )"testCaseName",           &gConfig_bin_morphology_dilate_mask.testCaseName           , STRING, SINGLE},
  {(char* )"performanceTestcase",    &gConfig_bin_morphology_dilate_mask.performanceTestcase    ,  INT_8, SINGLE},
  {(char* )"inImage",                &gConfig_bin_morphology_dilate_mask.inImage                , STRING, SINGLE},
  {(char* )"outImage",               &gConfig_bin_morphology_dilate_mask.outImage               , STRING, SINGLE},
  {(char* )"seCoefficient",          &gConfig_bin_morphology_dilate_mask.seCoefficient          ,  INT_8, MULTI },
  {(char* )"blkWidth",               &gConfig_bin_morphology_dilate_mask.blkWidth               , INT_16, SINGLE},
  {(char* )"blkStride",              &gConfig_bin_morphology_dilate_mask.blkStride              , INT_16, SINGLE},
  {(char* )"blkHeight",              &gConfig_bin_morphology_dilate_mask.blkHeight              , INT_16, SINGLE},
  {(char* )"desc",                   &gConfig_bin_morphology_dilate_mask.desc                   , STRING, SINGLE},
} ;

