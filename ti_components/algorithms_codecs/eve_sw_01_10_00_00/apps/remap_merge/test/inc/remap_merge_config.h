/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2013 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

#ifndef REMAP_MERGE_CONFIG_H_
#define REMAP_MERGE_CONFIG_H_

#include "configparser.h"
#include "stdint.h"
#include "xdais_types.h"
#include "iremap_merge_ti.h"

#define FILE_NAME_SIZE    (256)
#define DESCRIPTION_SIZE  (256)
#define REMAP_MERGE_NUM_MAX_TESTCASES  (20)

/* Add enum field to support more Global LUTs */
typedef enum
{
  remapMergeBigMap_int     = 0,
  remapMergeSmallMap_int   = 1
} eRemapMerge_CoordMapList ;

typedef enum
{
  remapMergeTileApproach      = 0,
  remapMergeBBApproach        = 1,
  remapMergeTileAndBBApproach = 2
} eRemapMerge_Approach ;


typedef struct
{
    uint8_t        testCaseName[FILE_NAME_SIZE];
    uint8_t        performanceTestcase;
    uint8_t        inImage[FILE_NAME_SIZE];
    uint8_t        outImage[FILE_NAME_SIZE];
    uint8_t        refImage[FILE_NAME_SIZE];
    uint8_t        coordMapList;
    uint8_t        isSrcMapFloat;
    Format         srcFormat;
    Format         dstFormat;
    uint32_t       srcStride;
    uint32_t       srcHeight;
    uint32_t       dstStride;
    uint32_t       roiWidth;
    uint32_t       roiHeight;
    uint16_t       blockWidthBB;
    uint16_t       blockHeightBB;
    uint16_t       blockWidthTile;
    uint16_t       blockHeightTile;
    uint16_t       tileWidth;
    uint16_t       tileHeight;
    uint8_t        enableMerge;
    uint8_t        remapApproach;
    Interpolation  interpolationLuma;
    Interpolation  interpolationChroma;
    uint8_t        mapQshift;
    uint8_t        rightShift; // optional right shift to convert from 16-bit to 8-bit for instance
    int32_t        sat_high; // saturation applied after right shift
    int32_t        sat_high_set;
    int32_t        sat_low;
    int32_t        sat_low_set;
    uint8_t        desc[DESCRIPTION_SIZE];
} sRemapMerge_Config;

extern uint16_t remapMerge_numTestCases;
extern sRemapMerge_Config gConfig_remapMerge[REMAP_MERGE_NUM_MAX_TESTCASES];
extern sTokenMapping gsTokenMap_remapMerge[MAX_ITEMS_TO_PARSE];

#endif /*REMAP_MERGE_CONFIG_H_*/

