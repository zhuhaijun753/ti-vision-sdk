/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#include <stdio.h>
#include <stdint.h>
#include "configparser.h"
#include "vcop_glcm_config.h"

sGlcm_Config gConfig_glcm;
sTokenMapping gsTokenMap_glcm[] =
{
  {(char* )"inImg",                  &gConfig_glcm.inImg                    , STRING, SINGLE},
  {(char* )"outGLCM",                &gConfig_glcm.outGLCM                  , STRING, SINGLE},
  {(char* )"imageWidth",             &gConfig_glcm.imageWidth               , INT_16, SINGLE},
  {(char* )"imageHeight",            &gConfig_glcm.imageHeight              , INT_16, SINGLE},
  {(char* )"imagePitch",             &gConfig_glcm.imagePitch               , INT_16, SINGLE},
  {(char* )"numLevels",              &gConfig_glcm.numLevels                , INT_8 , SINGLE},
  {(char* )"numOffsets",             &gConfig_glcm.numOffsets               , INT_8 , SINGLE},
  {(char* )"rowOffset0",             &gConfig_glcm.rowOffsets[0]            , INT_8 , SINGLE},
  {(char* )"rowOffset1",             &gConfig_glcm.rowOffsets[1]            , INT_8 , SINGLE},
  {(char* )"rowOffset2",             &gConfig_glcm.rowOffsets[2]            , INT_8 , SINGLE},
  {(char* )"rowOffset3",             &gConfig_glcm.rowOffsets[3]            , INT_8 , SINGLE},
  {(char* )"colOffset0",             &gConfig_glcm.colOffsets[0]            , INT_8 , SINGLE},
  {(char* )"colOffset1",             &gConfig_glcm.colOffsets[1]            , INT_8 , SINGLE},
  {(char* )"colOffset2",             &gConfig_glcm.colOffsets[2]            , INT_8 , SINGLE},
  {(char* )"colOffset3",             &gConfig_glcm.colOffsets[3]            , INT_8 , SINGLE},
  {(char* )"randSeed",               &gConfig_glcm.randSeed                 , INT_32, SINGLE},
  {(char* )"numIter",                &gConfig_glcm.numIter                  , INT_8 , SINGLE}
} ;
