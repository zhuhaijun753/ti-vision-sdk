/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#ifndef PYRAMID_LK_TRACKER_TB
#define PYRAMID_LK_TRACKER_TB
#include "configparser.h"
#include <stdint.h>
#include "xdais_types.h"
#include "ipyramid_lk_tracker_ti.h"

#define MAX_CONFIG_LINE_SIZE     (300)
#define MAX_FILE_NAME_SIZE       (200)
#define MAX_PARAM_STRING_SIZE    (30)
#define MAX_INPUT_LINE_SIZE      (300)
#define MAX_INPUT_VALUE_SIZE     (20)

#define MAX_NUM_KEY_POINTS

#define CONFIG_LIST_FILE_NAME    ("..\\testvecs\\config\\config_list.txt")

typedef struct 
{
  char configLine[MAX_CONFIG_LINE_SIZE];
  char configParam[MAX_PARAM_STRING_SIZE];
  char currFrameFile     [MAX_FILE_NAME_SIZE];
  char prevFrameFile     [MAX_FILE_NAME_SIZE];
  char inKeyPointsFile   [MAX_FILE_NAME_SIZE];
  char outKeyPointsFile  [MAX_FILE_NAME_SIZE];
  char refKeyPointsFile  [MAX_FILE_NAME_SIZE];
  uint8_t testCaseName[MAX_FILE_NAME_SIZE];
  uint8_t testCaseDesc[MAX_FILE_NAME_SIZE];
  int  numKeyPoints;
  int  numLevels   ;
  int  imWidth     ;
  int  imHeight    ;
  uint8_t performanceTestcase ;
  int  maxItersLK[PYRAMID_LK_TRACKER_TI_MAXLEVELS];
  int  minErrValue[PYRAMID_LK_TRACKER_TI_MAXLEVELS];
  int  searchRange[PYRAMID_LK_TRACKER_TI_MAXLEVELS];
} config_params;
extern config_params gParams ;
extern sTokenMapping gsTokenMap_sof[];

#endif /* PYRAMID_LK_TRACKER_TB */


