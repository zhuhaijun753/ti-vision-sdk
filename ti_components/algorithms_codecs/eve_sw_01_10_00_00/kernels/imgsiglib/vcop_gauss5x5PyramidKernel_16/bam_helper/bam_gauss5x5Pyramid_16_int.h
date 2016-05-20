/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_gauss5x5Pyramid_int.h
 *
 *  @brief      This header defines internal structures  for integrating 5x5 gaussian pyramid into BAM, used for image pyamid applet.
 */
#ifndef BAM_GAUSS5x5_16_PYRAMID_INT_H_
#define BAM_GAUSS5x5_16_PYRAMID_INT_H_

#include <stdint.h>
#include <vcop.h>

#include "evealgframework.h"
#include "bam_gauss5x5Pyramid_16.h"

#define NUM_IN_BLOCKS 1
#define NUM_OUT_BLOCKS 1
#define NUM_INTERNAL_BLOCKS 3

#define OUT_IDX (BAM_GAUSS5x5PYRAMID_OUTPUT_PORT)            /* 0 */
#define PARAMS_H_IDX 0         /* 0 */
#define PARAMS_V_IDX 1         /* 1 */
#define PARAMS_TEMP_IDX 2         /* 2 */


typedef struct
{
    /* Must always follow this order: pInternalBlock[], pInBlock[], pOutputBlock[], args */
    void *pInternalBlock[NUM_INTERNAL_BLOCKS];
    void *pInBlock[NUM_IN_BLOCKS];
    void *pOutBlock[NUM_OUT_BLOCKS];
    BAM_Gauss5x5Pyramid16_Args kernelArgs;
} BAM_Gauss5x5Pyramid16_Context;

#endif
