/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#include <stdio.h>
#include <stdint.h>
#include "configparser.h"
#include "vcop_prune_big_list_config.h"

sprune_big_list_Config gConfig_prune_big_list;
sTokenMapping gsTokenMap_prune_big_list[] =
{
  {(char* )"inList",                 &gConfig_prune_big_list.inList                   , STRING, SINGLE},
  {(char* )"inIdx",                  &gConfig_prune_big_list.inIdx                    , STRING, SINGLE},
  {(char* )"outList",                &gConfig_prune_big_list.outList                  , STRING, SINGLE},
  {(char* )"listLength",             &gConfig_prune_big_list.listLength               , INT_16, SINGLE},
  {(char* )"threshold",              &gConfig_prune_big_list.threshold                , INT_16, SINGLE},
  {(char* )"bestN",                  &gConfig_prune_big_list.bestN                    , INT_16, SINGLE},
  {(char* )"pattern",                &gConfig_prune_big_list.pattern                  , INT_8 , SINGLE},
  {(char* )"randSeed",               &gConfig_prune_big_list.randSeed                 , INT_32, SINGLE},
  {(char* )"numIter",                &gConfig_prune_big_list.numIter                  , INT_8 , SINGLE}
} ;
