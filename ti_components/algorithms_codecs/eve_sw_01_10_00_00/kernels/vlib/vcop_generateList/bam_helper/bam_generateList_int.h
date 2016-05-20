/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_generateList_int.h
 *
 *  @brief      This file defines interfaces for integrating generate list kernel into BAM.
 */
#ifndef BAM_GENERATELIST_INT_H_
#define BAM_GENERATELIST_INT_H_

#include <stdint.h>
#include <vcop.h>

#include "evealgframework.h"
#include "bam_generateList.h"

#define NUM_IN_BLOCKS 1
#define NUM_OUT_BLOCKS 2
#define NUM_INTERNAL_BLOCKS 6

#define OUT_XY_IDX (BAM_GENERATELIST_OUTPUT_XY_PORT)                            /* 0 */
#define OUT_NUM_ELMNTS_IDX (BAM_GENERATELIST_OUTPUT_NUM_ELMNTS_PORT)            /* 1 */

#define GENERATELIST_PARAMS_IDX           0
#define UPDATE_PARAMS_IDX                 1
#define COPY_XY_PARAMS_IDX                2
#define VARIABLES_IDX                     3
#define INTERNAL_X_IDX                    4
#define INTERNAL_Y_IDX                    5

typedef struct
{
    /* Must always follow this order: pInternalBlock[], pInBlock[], pOutputBlock[], args */
    void *pInternalBlock[NUM_INTERNAL_BLOCKS];
    void *pInBlock[NUM_IN_BLOCKS];
    void *pOutBlock[NUM_OUT_BLOCKS];
    BAM_GenerateList_Args kernelArgs;

    /* Private variables */
    uint8_t *endRowPadVal;
    uint16_t *xVal;
    uint16_t *yVal;
    uint16_t *blockX;
    uint16_t *blockY;
    uint16_t *numElmtsX;
    uint16_t *numElmtsY;
    uint16_t offsetX;
    uint16_t offsetY;
    uint16_t listXoffset;
    uint16_t listYoffset;
    uint16_t runningNumFeatures;
    uint32_t blockCount;
} BAM_GenerateList_Context;

#endif /* BAM_GENERATELIST_INT_H_ */
