/*==========================================================================*/
/*      Copyright (C) 2009-2014 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

#ifndef OBJECT_DETECTION_CONFIG_H_
#define OBJECT_DETECTION_CONFIG_H_

#include <stdint.h>
#include <xdais_types.h>
#include "configparser.h"
#include "iobjdet_ti.h"

#define FILE_NAME_SIZE  (256)
#define MAX_TESTCASES (20)

typedef struct
{
    uint8_t  inFileName[FILE_NAME_SIZE];
    uint8_t  outFileName[FILE_NAME_SIZE];
    uint16_t maxImageWidth;
    uint16_t maxImageHeight;
    uint16_t maxFrames;
    uint16_t maxScales;
    uint8_t  detectionMode;
    uint8_t  roiPreset;
    uint8_t  refreshInterval;
    TI_OD_PDConfig   pdConfig;
    TI_OD_TSRConfig tsrConfig;
} sObjectDetection_Config;

 /**
 *  @struct sTokenMapping
 *  @brief  Token Mapping structure for Error reporting
 *          This structure contains error reporting strings which are mapped to
 *          Noise Filter errors
 *
 *  @param  errorName : Pointer to the error string
 *
*/
typedef struct sErrorMapping{
  XDAS_Int8 *errorName;
}sErrorMapping;

extern uint32_t objectDetection_numTestCases;
extern sObjectDetection_Config gConfig_objectDetection[MAX_TESTCASES];
extern sTokenMapping gsTokenMap_objectDetection[MAX_ITEMS_TO_PARSE];

extern XDAS_Int32 TI_OD_Report_Error(XDAS_Int32 uiErrorMsg);

#endif /*TI_OD_CONFIG_H_*/

