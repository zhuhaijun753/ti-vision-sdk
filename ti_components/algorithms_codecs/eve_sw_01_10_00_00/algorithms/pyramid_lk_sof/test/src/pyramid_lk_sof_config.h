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
  char inVideoSeqFile    [MAX_FILE_NAME_SIZE];
  char outVideoSeqFile   [MAX_FILE_NAME_SIZE];
  char currFrameFile     [MAX_FILE_NAME_SIZE];
  char prevFrameFile     [MAX_FILE_NAME_SIZE];
  char gtFileName        [MAX_FILE_NAME_SIZE];
  char outFileName       [MAX_FILE_NAME_SIZE];
  char refFileName       [MAX_FILE_NAME_SIZE];
  char statsFileName     [MAX_FILE_NAME_SIZE];
  char keyPointFile      [MAX_FILE_NAME_SIZE];
  int  inPutType         ;
  int  startFrame        ;
  int  numFrames         ;
  int  maxNumKeyPoints   ;
  int  maxPrevTrackPoints;
  int  numLevels         ;
  int  numLevelsPerCall  ;
  int  imWidth           ;
  int  imHeight          ;
  int  roiWidth          ;
  int  roiHeight         ;
  int  startX            ;
  int  startY            ;
  int  harrisScaling     ;
  int  nmsThreshold      ;
  unsigned char harrisWindowSize;
  unsigned char harrisScoreMethod;
  unsigned char suppressionMethod;
  char configLine        [MAX_CONFIG_LINE_SIZE] ;
  char configParam       [MAX_PARAM_STRING_SIZE];
  char keyPointDetectMethod;
  int  keyPointDetectInterval;
  int  fast9Threshold;
  int  trackErrThr    ;
  int  trackMinFlowQ4 ;
  int  trackNmsWinSize;
  uint8_t testCaseName[MAX_FILE_NAME_SIZE];
  uint8_t testCaseDesc[MAX_FILE_NAME_SIZE];
  uint8_t performanceTestcase ;
  int  maxItersLK[PYRAMID_LK_TRACKER_TI_MAXLEVELS];
  int  minErrValue[PYRAMID_LK_TRACKER_TI_MAXLEVELS];
  int  searchRange[PYRAMID_LK_TRACKER_TI_MAXLEVELS];
} config_params;
extern config_params gParams ;
extern sTokenMapping gsTokenMap_sof[];

#endif /* PYRAMID_LK_TRACKER_TB */
