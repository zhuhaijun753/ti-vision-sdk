/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#include <stdio.h>
#include "configparser.h"
#include "vcop_compute_rBrief_config.h"

scompute_rBrief_Config gConfig_compute_rBrief;
sTokenMapping gsTokenMap_compute_rBrief[MAX_ITEMS_TO_PARSE] =
{
  {(char* )"inputSrc",                &gConfig_compute_rBrief.inputSrc                 , STRING, SINGLE},
  {(char* )"inFileName",              &gConfig_compute_rBrief.inFileName               , STRING, SINGLE},
  {(char* )"outFileName",             &gConfig_compute_rBrief.outFileName              , STRING, SINGLE},
  {(char* )"numIter",                 &gConfig_compute_rBrief.numIter                  , INT_8 , SINGLE},
  {(char* )"writeOutput",             &gConfig_compute_rBrief.writeOutput              , INT_32, SINGLE},
  {(char* )"seedForRND",              &gConfig_compute_rBrief.seedForRND               , INT_32, SINGLE},
} ;
