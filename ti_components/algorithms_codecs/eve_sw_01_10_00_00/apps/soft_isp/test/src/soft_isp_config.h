/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#ifndef SOFT_ISP_CONFIG_H_
#define SOFT_ISP_CONFIG_H_

#include "configparser.h"
#include "stdint.h"

#define FILE_NAME_SIZE     (256)
#define CONFIG_LINE_SIZE   (300)
#define PARAM_STRING_SIZE  (30)
#define MAX_NUM_OFFSETS    (8)

#define CONFIG_LIST_FILE_NAME    ("..\\testvecs\\config\\config_list.txt")


typedef struct
{
  char       inImg[FILE_NAME_SIZE];
  char       gbceToneCurve[FILE_NAME_SIZE];
  char       outImg[FILE_NAME_SIZE];
  uint16_t   imageWidth;
  uint16_t   imageHeight;
  uint16_t   imagePitch;
  uint8_t    rPosition;
  uint8_t    sensorBitDepth;
  uint16_t   maxPixValue;

  /* Decompand params */
  uint8_t    enableDecompand;
  uint16_t   pout1;
  uint16_t   pout2;
  uint8_t    slope1;
  uint16_t   slope2;

  /* Black Clamp Params */
  uint16_t   blackClamp[4];
  uint16_t   cBalanceGain[4];
  uint8_t    cBalanceShift;

  /* Extract R pixels */
  uint8_t    enableExtractR;

  /* Stats Collector params */
  uint8_t    enableStats;
  uint16_t   statBlkWidth;
  uint16_t   statBlkHeight;
  uint16_t   saturationLimit;

  /* GBCE params */
  uint8_t    gbceMethod;

  uint32_t   randSeed;
  uint8_t    numIter;

  uint8_t   testCaseName[FILE_NAME_SIZE];
  uint8_t   testCaseDesc[FILE_NAME_SIZE];
  uint8_t   performanceTestcase;
  char      configLine[CONFIG_LINE_SIZE] ;
  char      configParam[PARAM_STRING_SIZE];

} sSoftIsp_Config;

extern sSoftIsp_Config gConfig_soft_isp;
extern sTokenMapping gsTokenMap_soft_isp[MAX_ITEMS_TO_PARSE];

#endif /* SOFT_ISP_CONFIG_H_ */

