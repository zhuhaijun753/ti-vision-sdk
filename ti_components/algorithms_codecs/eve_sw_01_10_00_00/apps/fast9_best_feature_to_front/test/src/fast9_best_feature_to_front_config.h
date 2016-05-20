/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#ifndef FAST9_BEST_FEATURE_TO_FRONT_CONFIG_H_
#define FAST9_BEST_FEATURE_TO_FRONT_CONFIG_H_

#pragma CHECK_MISRA ("none")
#include "configparser.h"
#include "stdint.h"
#pragma RESET_MISRA ("required")
#include <xdais_types.h>
#include "ifast9_best_feature_to_front_ti.h"

#define FILE_NAME_SIZE           (300)
#define DESCRIPTION_SIZE  (256)
#define FAST9_BFTF_NUM_MAX_TESTCASES 20

#define XY_IN_DMEM               (1)
#define MAX_NUMBER_OF_FEATURES   (256)


typedef struct
{
  uint8_t  inImage[FAST9_BFFT_TI_MAXLEVELS][FILE_NAME_SIZE];
  uint8_t  inXYList[FAST9_BFFT_TI_MAXLEVELS][FILE_NAME_SIZE];
  uint32_t outXY[FAST9_BFFT_TI_MAXLEVELS][FILE_NAME_SIZE];
  uint16_t srcImageWidth[FAST9_BFFT_TI_MAXLEVELS];
  uint16_t srcImageHeight[FAST9_BFFT_TI_MAXLEVELS];
  uint16_t total_features[FAST9_BFFT_TI_MAXLEVELS];
  uint8_t  fast9threshold;
  uint16_t bestNFeatures[FAST9_BFFT_TI_MAXLEVELS];
  uint8_t  numLevels;
  uint8_t  XYInDmem;
  uint8_t  fileBased;
  uint8_t  writeOutput;
  uint16_t maxFeatures;
  uint16_t maxbestNFeatures;
  uint8_t  suppressionMethod;
  uint8_t  testCaseName[FILE_NAME_SIZE];
  uint8_t  performanceTestcase;
  uint8_t  desc[DESCRIPTION_SIZE];
} sFast9BestFeatureToFront_Config;

extern uint32_t numTestCases;
extern sFast9BestFeatureToFront_Config gConfig_Fast9BestFeatureToFront[FAST9_BFTF_NUM_MAX_TESTCASES];
extern sTokenMapping gsTokenMap_Fast9BestFeatureToFront[MAX_ITEMS_TO_PARSE];

#define PRINT_ERROR_MSG()  printf("Error at line: %5d : in file %22s, of function : %s \n",__LINE__, __FILE__,__FUNCTION__)

#endif /* FAST9_BEST_FEATURE_TO_FRONT_CONFIG_H_*/
