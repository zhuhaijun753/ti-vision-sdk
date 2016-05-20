/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#ifndef BLOCK_STATISTICS_CONFIG_H_
#define BLOCK_STATISTICS_CONFIG_H_

#include "configparser.h"
#include "stdint.h"

#define FILE_NAME_SIZE       (256)
#define CONFIG_LINE_SIZE     (300)
#define PARAM_STRING_SIZE    (30)

#define CONFIG_LIST_FILE_NAME    ("..\\testvecs\\config\\config_list.txt")

typedef struct
{
  char      inImg[FILE_NAME_SIZE];
  char      outImg[FILE_NAME_SIZE];
  uint16_t  imageWidth;
  uint16_t  imageHeight;
  uint16_t  imagePitch;
  uint16_t  statBlockWidth;
  uint16_t  statBlockHeight;
  uint32_t  randSeed;
  uint8_t   numIter;

  uint8_t   testCaseName[FILE_NAME_SIZE];
  uint8_t   testCaseDesc[FILE_NAME_SIZE];
  uint8_t   performanceTestcase;
  char      configLine[CONFIG_LINE_SIZE] ;
  char      configParam[PARAM_STRING_SIZE];

} sBlockStatistics_Config;

extern sBlockStatistics_Config gConfig_block_statistics;
extern sTokenMapping gsTokenMap_block_statistics[MAX_ITEMS_TO_PARSE];

#endif /* BLOCK_STATISTICS_CONFIG_H_ */

