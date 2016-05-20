/*==========================================================================*/
/*      Copyright (C) 2009-2014 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include "configparser.h"
#include "object_detection_config.h"
#pragma RESET_MISRA ("required")

uint32_t objectDetection_numTestCases;
sObjectDetection_Config gConfig_objectDetection[MAX_TESTCASES];

sTokenMapping gsTokenMap_objectDetection[] =
{
  {(char *)"inFileName"            ,&gConfig_objectDetection[0].inFileName,                       STRING,  SINGLE},
  {(char *)"outFileName"           ,&gConfig_objectDetection[0].outFileName,                      STRING,  SINGLE},
  {(char *)"maxImageWidth"         ,&gConfig_objectDetection[0].maxImageWidth,                    INT_16,  SINGLE},
  {(char *)"maxImageHeight"        ,&gConfig_objectDetection[0].maxImageHeight,                   INT_16,  SINGLE},
  {(char *)"maxFrames"             ,&gConfig_objectDetection[0].maxFrames,                        INT_16,  SINGLE},
  {(char *)"maxScales"             ,&gConfig_objectDetection[0].maxScales,                        INT_16,  SINGLE},
  {(char *)"detectionMode"         ,&gConfig_objectDetection[0].detectionMode,                     INT_8,  SINGLE},
  {(char *)"roiPreset"             ,&gConfig_objectDetection[0].roiPreset,                         INT_8,  SINGLE},
  {(char *)"refreshInterval"       ,&gConfig_objectDetection[0].refreshInterval,                   INT_8,  SINGLE},

  {(char *)"enablePD"              ,&gConfig_objectDetection[0].pdConfig.enablePD,                 INT_8,  SINGLE},
  {(char *)"classifierTypePD"      ,&gConfig_objectDetection[0].pdConfig.classifierTypePD,         INT_8,  SINGLE},
  {(char *)"trackingMethodPD"      ,&gConfig_objectDetection[0].pdConfig.trackingMethodPD,         INT_8,  SINGLE},
  {(char *)"softCascadeThPD"       ,&gConfig_objectDetection[0].pdConfig.softCascadeThPD,         INT_32,  SINGLE},
  {(char *)"strongCascadeThPD"     ,&gConfig_objectDetection[0].pdConfig.strongCascadeThPD,       INT_32,  SINGLE},

  {(char *)"enableTSR"              ,&gConfig_objectDetection[0].tsrConfig.enableTSR,              INT_8,  SINGLE},
  {(char *)"classifierTypeTSR"      ,&gConfig_objectDetection[0].tsrConfig.classifierTypeTSR,      INT_8,  SINGLE},
  {(char *)"trackingMethodTSR"      ,&gConfig_objectDetection[0].tsrConfig.trackingMethodTSR,      INT_8,  SINGLE},
  {(char *)"recognitionMethodTSR"   ,&gConfig_objectDetection[0].tsrConfig.recognitionMethodTSR,   INT_8,  SINGLE},
  {(char *)"softCascadeThTSR"       ,&gConfig_objectDetection[0].tsrConfig.softCascadeThTSR,      INT_32,  SINGLE},
  {(char *)"strongCascadeThTSR"     ,&gConfig_objectDetection[0].tsrConfig.strongCascadeThTSR,    INT_32,  SINGLE}
} ;

/*----------------------------------------------------------------------------*/
/* Error strings which are mapped to OD errors                                */
/* Please refer User guide for more details on error strings                  */
/*----------------------------------------------------------------------------*/
static sErrorMapping gErrorStrings[32] =
{
  (XDAS_Int8 *)"TI_OD_UNSUPPORTED_IMAGE_WIDTH = 16\0",
  (XDAS_Int8 *)"TI_OD_UNSUPPORTED_IMAGE_HEIGHT = 17,\0",
  (XDAS_Int8 *)"TI_OD_UNSUPPORTED_NUM_SCALES = 18,\0",
  (XDAS_Int8 *)"TI_OD_UNSUPPORTED_DETECTION_MODE = 19,\0",
  (XDAS_Int8 *)"TI_OD_UNSUPPORTED_ROI_PRESET = 20,\0",
  (XDAS_Int8 *)"TI_OD_UNSUPPORTED_REFRESH_INTERVAL = 21,\0",
  (XDAS_Int8 *)"TI_OD_UNSUPPORTED_CLASSIFIER_TYPE = 22,\0",
  (XDAS_Int8 *)"TI_OD_UNSUPPORTED_TRACKING_METHOD = 23,\0",
  (XDAS_Int8 *)"TI_OD_UNSUPPORTED_RECOGNITION_METHOD = 24,\0",
  (XDAS_Int8 *)"TI_OD_UNSUPPORTED_SOFT_CASCADE_THRESHOLD = 25,\0",
  (XDAS_Int8 *)"TI_OD_UNSUPPORTED_STRONG_CASCADE_THRESHOLD = 26,\0",
  (XDAS_Int8 *)"TI_OD_UNSUPPORTED_META_DATA = 27,\0",
  (XDAS_Int8 *)"TI_OD_EDMA_MEMCPY_ERROR = 28,\0",
  (XDAS_Int8 *)"TI_OD_EDMA_SCATTER_GATHER_ERROR = 29,\0",
  (XDAS_Int8 *)"TI_OD_RESERVED_PARAMS_NOT_ZERO = 30,\0",
  (XDAS_Int8 *)"TI_OD_UNSUPPORTED_PARAMETER = 31,\0"
};

XDAS_Int32 TI_OD_Report_Error(XDAS_Int32 uiErrorMsg)
{
  int i;
  if(uiErrorMsg)
  {
    /*------------------------------------------------------------------------*/
    /* Loop through all the bits in error message and print error string.     */
    /*------------------------------------------------------------------------*/
    for (i = 16; i < 32; i ++)
    {
      if (uiErrorMsg & (1 << i))
      {
        printf("ERROR: %s \n",  gErrorStrings[(i - 16)].errorName);
      }
    }

    return IALG_EFAIL;
  }

  return IALG_EOK;
}
