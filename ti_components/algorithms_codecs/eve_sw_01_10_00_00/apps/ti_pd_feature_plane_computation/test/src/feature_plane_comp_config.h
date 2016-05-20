/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#ifndef FEATURE_PLANE_COMP_CONFIG_H_
#define FEATURE_PLANE_COMP_CONFIG_H_

#include "configparser.h"
#include "stdint.h"
#include "xdais_types.h"
#include "iti_pd_feature_plane_computation_ti.h"

#define FILE_NAME_SIZE  (256)
#define FEATURE_PLANE_COMP_NUM_MAX_TESTCASES 20
#define MAX_SCALE_STEPS (8)

typedef struct
{
    uint8_t inImage[FILE_NAME_SIZE];
    uint8_t outImage[FILE_NAME_SIZE];
    uint8_t refImage[FILE_NAME_SIZE];
    uint8_t testCaseName[FILE_NAME_SIZE];
    uint8_t testCaseDesc[FILE_NAME_SIZE];
    uint16_t srcImageWidth;
    uint16_t srcImageHeight;
    uint16_t srcImagePitch;
    uint32_t startFrame;
    uint32_t numFrames;
    uint8_t fileBased;
    uint16_t cellSize;
    uint16_t blockSize;
    uint16_t blockOverlap;
    uint16_t sreachStep;
    uint16_t scaleSteps;
    uint16_t numScales;
    uint16_t enableFilter;
    uint16_t enableContrastStretching;
    uint8_t extFilterParam;
    uint16_t numBins;
    uint16_t gradientMethod;
    uint8_t enableGardMagPlane;
    uint8_t enableCellSum;
    uint8_t enableYPlane;
    uint8_t enableUVPlane;
    uint8_t outFormat;
    uint8_t performanceTestcase ;
    uint8_t RoiSelectionMethod;
    uint16_t RoiCenterX;
    uint16_t RoiCenterY;
    uint16_t RoiWidth  ;
    uint16_t RoiHeight ;
    uint16_t scaleRatioQ12[MAX_SCALE_STEPS];
    uint16_t scaleParams[FEATURE_PLANE_COMP_MAX_TOTAL_SCALES*5];
} sFeaturePlaneComp_Config;

extern uint32_t featurePlaneComp_numTestCases;
extern sFeaturePlaneComp_Config gConfig_featurePlaneComp[FEATURE_PLANE_COMP_NUM_MAX_TESTCASES];
extern sTokenMapping gsTokenMap_featurePlaneComp[MAX_ITEMS_TO_PARSE];

#endif /*FEATURE_PLANE_COMP_CONFIG_H_*/

