/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#ifndef _VCOP_HAMMING_DISTANCE_CONFIG_H_
#define _VCOP_HAMMING_DISTANCE_CONFIG_H_

#include "configparser.h"
#define FILE_NAME_SIZE       (256)
#define CONFIG_LINE_SIZE     (300)
#define PARAM_STRING_SIZE    (30)

#define CONFIG_LIST_FILE_NAME    ("../testvecs/config/config_list.txt")

typedef struct
{
  char       inStr1[FILE_NAME_SIZE];
  char       inStr2[FILE_NAME_SIZE];
  char       outHamDist[FILE_NAME_SIZE];
  uint8_t    testCase;
  uint32_t   descLen;
  uint32_t   descPitch;
  uint32_t   numDesc1;
  uint32_t   numDesc2;
  uint32_t   mode;
  uint16_t   minDistanceThres;
  uint16_t   matchConfidence;
  uint32_t   randSeed1;
  uint32_t   randSeed2;

  uint8_t   testCaseName[FILE_NAME_SIZE];
  uint8_t   testCaseDesc[FILE_NAME_SIZE];
  uint8_t   performanceTestcase;
  char      configLine[CONFIG_LINE_SIZE] ;
  char      configParam[PARAM_STRING_SIZE];

} sHamming_distance_Config;

extern sHamming_distance_Config gConfig_hamming_distance;
extern sTokenMapping gsTokenMap_hamming_distance[MAX_ITEMS_TO_PARSE];

#endif  /* _VCOP_HAMMING_DISTANCE_CONFIG_H_ */
