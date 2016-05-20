/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#include <stdio.h>
#include "configparser.h"
#include "vcop_sad_error_measure_lk_config.h"

ssad_error_measure_lk_Config gConfig_sad_error_measure_lk;
sTokenMapping gsTokenMap_sad_error_measure_lk[MAX_ITEMS_TO_PARSE] =
{
  {(char* )"inputSrc",                &gConfig_sad_error_measure_lk.inputSrc                 , STRING, SINGLE},
  {(char* )"inFileName1",             &gConfig_sad_error_measure_lk.inFileName1              , STRING, SINGLE},
  {(char* )"inFileName2",             &gConfig_sad_error_measure_lk.inFileName2              , STRING, SINGLE},
  {(char* )"inFileName3",             &gConfig_sad_error_measure_lk.inFileName3              , STRING, SINGLE},
  {(char* )"outFileName",             &gConfig_sad_error_measure_lk.outFileName              , STRING, SINGLE},
  {(char* )"inputStride",             &gConfig_sad_error_measure_lk.inputStride              , INT_16, SINGLE},
  {(char* )"frmWidth",                &gConfig_sad_error_measure_lk.frmWidth                 , INT_16, SINGLE},
  {(char* )"frmHeight",               &gConfig_sad_error_measure_lk.frmHeight                , INT_16, SINGLE},
  {(char* )"blkWidth",                &gConfig_sad_error_measure_lk.blkWidth                 , INT_16, SINGLE},
  {(char* )"blkHeight",               &gConfig_sad_error_measure_lk.blkHeight                , INT_16, SINGLE},
  {(char* )"numKeyPoints",            &gConfig_sad_error_measure_lk.numKeyPoints             , INT_16, SINGLE},
  {(char* )"shiftValue",              &gConfig_sad_error_measure_lk.shiftValue               , INT_16, SINGLE},
  {(char* )"numIter",                 &gConfig_sad_error_measure_lk.numIter                  , INT_8 , SINGLE},
  {(char* )"writeOutput",             &gConfig_sad_error_measure_lk.writeOutput              , INT_32, SINGLE},
  {(char* )"seedForRND",              &gConfig_sad_error_measure_lk.seedForRND               , INT_32, SINGLE},
} ;
