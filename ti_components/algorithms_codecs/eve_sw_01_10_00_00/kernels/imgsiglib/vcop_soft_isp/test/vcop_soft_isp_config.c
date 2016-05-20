/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#include <stdio.h>
#include <stdint.h>
#include "configparser.h"
#include "vcop_soft_isp_config.h"

sSoftISP_Config gConfig_soft_isp;
sTokenMapping gsTokenMap_soft_isp[] =
{
  {(char* )"inImg",             &gConfig_soft_isp.inImg                , STRING, SINGLE},
  {(char* )"gbceToneCurve",     &gConfig_soft_isp.gbceToneCurve        , STRING, SINGLE},
  {(char* )"outDecompandImg",   &gConfig_soft_isp.outDecompandImg      , STRING, SINGLE},
  {(char* )"outBalancedImg",    &gConfig_soft_isp.outBalancedImg       , STRING, SINGLE},
  {(char* )"outRImg",           &gConfig_soft_isp.outRImg              , STRING, SINGLE},
  {(char* )"outCFAImg",         &gConfig_soft_isp.outCFAImg            , STRING, SINGLE},
  {(char* )"outImg",            &gConfig_soft_isp.outImg               , STRING, SINGLE},
  {(char* )"outStats",          &gConfig_soft_isp.outStats             , STRING, SINGLE},
  {(char* )"imageWidth",        &gConfig_soft_isp.imageWidth           , INT_16, SINGLE},
  {(char* )"imageHeight",       &gConfig_soft_isp.imageHeight          , INT_16, SINGLE},
  {(char* )"imagePitch",        &gConfig_soft_isp.imagePitch           , INT_16, SINGLE},
  {(char* )"sensorBitDepth",    &gConfig_soft_isp.sensorBitDepth       , INT_8 , SINGLE},
  {(char* )"maxPixValue",       &gConfig_soft_isp.maxPixValue          , INT_16, SINGLE},
  {(char* )"enableDecompand",   &gConfig_soft_isp.enableDecompand      , INT_8 , SINGLE},
  {(char* )"p1",                &gConfig_soft_isp.p1                   , INT_16, SINGLE},
  {(char* )"pk",                &gConfig_soft_isp.pk                   , INT_16, SINGLE},
  {(char* )"r1",                &gConfig_soft_isp.r1                   , INT_8 , SINGLE},
  {(char* )"r1r2",              &gConfig_soft_isp.r1r2                 , INT_16, SINGLE},
  {(char* )"decompandShift",    &gConfig_soft_isp.decompandShift       , INT_8 , SINGLE},
  {(char* )"blackClamp0",       &gConfig_soft_isp.blackClamp[0]        , INT_8 , SINGLE},
  {(char* )"blackClamp1",       &gConfig_soft_isp.blackClamp[1]        , INT_8 , SINGLE},
  {(char* )"blackClamp2",       &gConfig_soft_isp.blackClamp[2]        , INT_8 , SINGLE},
  {(char* )"blackClamp3",       &gConfig_soft_isp.blackClamp[3]        , INT_8 , SINGLE},
  {(char* )"cBalanceGain0",     &gConfig_soft_isp.cBalanceGain[0]      , INT_8 , SINGLE},
  {(char* )"cBalanceGain1",     &gConfig_soft_isp.cBalanceGain[1]      , INT_8 , SINGLE},
  {(char* )"cBalanceGain2",     &gConfig_soft_isp.cBalanceGain[2]      , INT_8 , SINGLE},
  {(char* )"cBalanceGain3",     &gConfig_soft_isp.cBalanceGain[3]      , INT_8 , SINGLE},
  {(char* )"cBalanceShift",     &gConfig_soft_isp.cBalanceShift        , INT_8 , SINGLE},
  {(char* )"enableStats",       &gConfig_soft_isp.enableStats          , INT_8 , SINGLE},
  {(char* )"saturationLimit",   &gConfig_soft_isp.saturationLimit      , INT_16, SINGLE},
  {(char* )"gbceMethod",        &gConfig_soft_isp.gbceMethod           , INT_8 , SINGLE},
  {(char* )"randSeed",          &gConfig_soft_isp.randSeed             , INT_32, SINGLE},
  {(char* )"numIter",           &gConfig_soft_isp.numIter              , INT_8 , SINGLE}
} ;
