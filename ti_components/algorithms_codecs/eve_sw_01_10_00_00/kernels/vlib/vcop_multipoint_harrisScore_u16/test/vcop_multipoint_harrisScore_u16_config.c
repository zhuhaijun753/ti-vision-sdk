/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#include <stdio.h>
#include <stdint.h>
#include "configparser.h"
#include "vcop_multipoint_harrisScore_u16_config.h"

sMultipoint_harris_score_Config gConfig_multipoint_harris_score;
sTokenMapping gsTokenMap_multipoint_harris_score[] =
{
  {(char* )"inImageBlocks",          &gConfig_multipoint_harris_score.inImageBlocks            , STRING, SINGLE},
  {(char* )"outHarrisScore",         &gConfig_multipoint_harris_score.outHarrisScore           , STRING, SINGLE},
  {(char* )"numPoints",              &gConfig_multipoint_harris_score.numPoints                , INT_16, SINGLE},
  {(char* )"interBlockOffset",       &gConfig_multipoint_harris_score.interBlockOffset         , INT_16, SINGLE},
  {(char* )"inputStride",            &gConfig_multipoint_harris_score.inputStride              , INT_16, SINGLE},
  {(char* )"sensitivityParam",       &gConfig_multipoint_harris_score.sensitivityParam         , INT_16, SINGLE},
  {(char* )"start_id",               &gConfig_multipoint_harris_score.start_id                 , INT_16, SINGLE},
  {(char* )"randSeed",               &gConfig_multipoint_harris_score.randSeed                 , INT_32, SINGLE},
  {(char* )"numIter",                &gConfig_multipoint_harris_score.numIter                  , INT_8 , SINGLE}
} ;
