/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#include <stdio.h>
#include "configparser.h"
#include "vcop_fast9_score_config.h"

sfast9_score_Config gConfig_fast9_score;
sTokenMapping gsTokenMap_fast9_score[MAX_ITEMS_TO_PARSE] =
{
  {(char* )"inputSrc",                &gConfig_fast9_score.inputSrc                 , STRING, SINGLE},
  {(char* )"inFileName",              &gConfig_fast9_score.inFileName               , STRING, SINGLE},
  {(char* )"outFileName",             &gConfig_fast9_score.outFileName              , STRING, SINGLE},
  {(char* )"pitch",                   &gConfig_fast9_score.pitch                    , INT_16, SINGLE},
  {(char* )"num_features",            &gConfig_fast9_score.num_features             , INT_16, SINGLE},
  {(char* )"Thr",                     &gConfig_fast9_score.Thr                      , INT_8,  SINGLE},
  {(char* )"ScoreOffset",             &gConfig_fast9_score.ScoreOffset              , INT_16, SINGLE},
  {(char* )"numIter",                 &gConfig_fast9_score.numIter                  , INT_8 , SINGLE},
  {(char* )"writeOutput",             &gConfig_fast9_score.writeOutput              , INT_32, SINGLE},
  {(char* )"seedForRND",              &gConfig_fast9_score.seedForRND               , INT_32, SINGLE},
  {(char* )"scoreMethod",              &gConfig_fast9_score.scoreMethod             , INT_8, SINGLE},
} ;
