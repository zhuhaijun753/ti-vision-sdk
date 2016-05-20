/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#include <stdio.h>
#include "configparser.h"
#include "vcop_fast9_config.h"

sfast9_Config gConfig_fast9;
sTokenMapping gsTokenMap_fast9[MAX_ITEMS_TO_PARSE] =
{
  {(char* )"inputSrc",                &gConfig_fast9.inputSrc                 , STRING, SINGLE},
  {(char* )"inFileName",              &gConfig_fast9.inFileName               , STRING, SINGLE},
  {(char* )"outFileName",             &gConfig_fast9.outFileName              , STRING, SINGLE},
  {(char* )"pitch",                   &gConfig_fast9.pitch                    , INT_16, SINGLE},
  {(char* )"blkHeight",               &gConfig_fast9.blkHeight                , INT_16, SINGLE},
  {(char* )"comp_width",              &gConfig_fast9.comp_width               , INT_16, SINGLE},
  {(char* )"comp_height",             &gConfig_fast9.comp_height              , INT_16, SINGLE},
  {(char* )"Thr",                     &gConfig_fast9.Thr                      , INT_8, SINGLE},
  {(char* )"numIter",                 &gConfig_fast9.numIter                  , INT_8 , SINGLE},
  {(char* )"writeOutput",             &gConfig_fast9.writeOutput              , INT_32, SINGLE},
  {(char* )"seedForRND",              &gConfig_fast9.seedForRND               , INT_32, SINGLE},
} ;
