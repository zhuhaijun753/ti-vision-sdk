/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#include <stdio.h>
#include "configparser.h"
#include "vcop_calc_inverse_structure_tensor_2x2_config.h"

scalc_inverse_structure_tensor_2x2_Config gConfig_calc_inverse_structure_tensor_2x2;
sTokenMapping gsTokenMap_calc_inverse_structure_tensor_2x2[MAX_ITEMS_TO_PARSE] =
{
  {(char* )"inputSrc",                &gConfig_calc_inverse_structure_tensor_2x2.inputSrc                 , STRING, SINGLE},
  {(char* )"inFileName1",             &gConfig_calc_inverse_structure_tensor_2x2.inFileName1              , STRING, SINGLE},
  {(char* )"inFileName2",             &gConfig_calc_inverse_structure_tensor_2x2.inFileName2              , STRING, SINGLE},
  {(char* )"outFileName",             &gConfig_calc_inverse_structure_tensor_2x2.outFileName              , STRING, SINGLE},
  {(char* )"inputStride",             &gConfig_calc_inverse_structure_tensor_2x2.inputStride              , INT_16, SINGLE},
  {(char* )"outputStride",            &gConfig_calc_inverse_structure_tensor_2x2.outputStride             , INT_16, SINGLE},
  {(char* )"numKeyPoints",            &gConfig_calc_inverse_structure_tensor_2x2.numKeyPoints             , INT_16, SINGLE},
  {(char* )"numIter",                 &gConfig_calc_inverse_structure_tensor_2x2.numIter                  , INT_8 , SINGLE},
  {(char* )"writeOutput",             &gConfig_calc_inverse_structure_tensor_2x2.writeOutput              , INT_32, SINGLE},
  {(char* )"seedForRND",              &gConfig_calc_inverse_structure_tensor_2x2.seedForRND               , INT_32, SINGLE},
} ;
