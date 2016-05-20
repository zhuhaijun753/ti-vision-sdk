/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#ifndef _VCOP_SOFT_ISP_CONFIG_H_
#define _VCOP_SOFT_ISP_CONFIG_H_

#include "configparser.h"
#define FILE_NAME_SIZE  (256)

#define GBCE_SIMPLE       (0)
#define GBCE_INTERPOLATED (1)

typedef struct
{
  char       inImg[FILE_NAME_SIZE];
  char       gbceToneCurve[FILE_NAME_SIZE];
  char       outDecompandImg[FILE_NAME_SIZE];
  char       outBalancedImg[FILE_NAME_SIZE];
  char       outRImg[FILE_NAME_SIZE];
  char       outCFAImg[FILE_NAME_SIZE];
  char       outImg[FILE_NAME_SIZE];
  char       outStats[FILE_NAME_SIZE];
  uint16_t   imageWidth;
  uint16_t   imageHeight;
  uint16_t   imagePitch;
  uint8_t    sensorBitDepth;
  uint16_t   maxPixValue;

  /* Decompand params */
  uint8_t    enableDecompand;
  uint16_t   p1;
  uint16_t   pk;
  uint8_t    r1;
  uint16_t   r1r2;
  uint8_t    decompandShift;

  /* Black Clamp Params */
  uint16_t   blackClamp[4];
  uint16_t   cBalanceGain[4];
  uint8_t    cBalanceShift;

  /* Stats Collector params */
  uint8_t    enableStats;
  uint16_t   saturationLimit;

  /* GBCE params */
  uint8_t    gbceMethod;

  uint32_t   randSeed;
  uint8_t    numIter;
} sSoftISP_Config;

extern sSoftISP_Config gConfig_soft_isp;
extern sTokenMapping gsTokenMap_soft_isp[MAX_ITEMS_TO_PARSE];

#endif  /* _VCOP_SOFT_ISP_CONFIG_H_ */
