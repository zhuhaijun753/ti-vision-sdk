/*==========================================================================*/
/*      Copyright (C) 2009-2014 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/** @file stereoVision_testfuncs.c
 *
 *  @brief  This file contains test code for stereoVision algorithm
 *
 *
 *  @date   21 Aug 2014
 *
 *  Description
 *    This file contains test code to validate the frame level applet for
 *    hamming-based disparity calculation. It also checks the output against c reference
 *    outputs and profiles the performance and computes the system
 *    overheads.
 */

#ifndef _STEREO_VISION_FUNCS_H_
#define _STEREO_VISION_FUNCS_H_

#pragma CHECK_MISRA ("none")
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <vcop.h>

#include "evestarterware.h"
#include "alg_osal.h"

#include "xdais_types.h"
#include "iDisparity_ti.h"
#include "iCensus_ti.h"
#include "../vlib/vcop_census_8bits/inc/vcop_census_8bits_cn.h"
#include "../vlib/vcop_census_16bits/inc/vcop_census_16bits_cn.h"
#include "../vlib/vcop_disparity_hammingDistance_row/inc/vcop_disparity_hammingDistance_row_cn.h"
#include "../vlib/vcop_disparity_sad8_row/inc/vcop_disparity_sad8_row_cn.h"
#include "../vlib/vcop_disparity_sad16_row/inc/vcop_disparity_sad16_row_cn.h"

#include "ti_image_file_io.h"

#define MIN(a,b) ((a)<(b)?(a):(b))

void convertCensus32bitsTo8bits(
        uint32_t *disparity_input, 
        uint8_t *disparity_input8bits, 
        uint32_t size);

int32_t validateCensus(
        uint8_t *census_inputLeft, 
        uint8_t *census_inputRight,
        uint8_t *disparity_inputLeft,
        uint8_t *disparity_inputRight,
        uint8_t *refDisparity_inputLeft,
        uint8_t *refDisparity_inputRight,
        CENSUS_TI_CreateParams *census_createParams,
        uint16_t srcImagePitch,
        uint16_t dstImagePitch,
        uint16_t left_n_rows,
        uint8_t numBytesPerCensus
);

int32_t validateHamDistDisparity(
        uint8_t *disparity_inputLeft,
        uint8_t *disparity_inputRight,
        uint8_t *dispOutput,
        uint8_t *dispRefOutput,
        uint16_t *minCostOutput,
        uint16_t *minCostRefOutput,
        uint16_t *prevAdjCostOutput,
        uint16_t *nextAdjCostOutput,
        uint16_t *prevAdjCostRefOutput,
        uint16_t *nextAdjCostRefOutput,
        uint16_t *natC_allCostOutput,
        uint16_t *natC_allCostRLOutput,
        CENSUS_TI_CreateParams *census_createParams,
        DISPARITY_TI_CreateParams *disparity_createParams,
        uint16_t imageWidth,
        uint16_t imageHeight,
        uint16_t dstImagePitch
);

void convertDisparityFalseColor(
        uint8_t *image_red, 
        uint8_t *image_grn, 
        uint8_t *image_blu, 
        uint8_t *dispOutput,
        uint16_t *costOutput,
        uint16_t width,
        uint16_t height, 
        uint8_t numDisparities,
        float maxMinCostRatio);

void convertDisparityFalseColorYUV444(
        uint8_t *image_y,
        uint8_t *image_u,
        uint8_t *image_v,
        uint8_t *dispOutput,
        uint16_t *costOutput,
        uint16_t width,
        uint16_t height,
        uint8_t numDisparities,
        float maxMinCostRatio);

void convertDisparityFalseColorYUV420SP(
        uint8_t *image_y,
        uint8_t *image_uv,
        uint8_t *dispOutput,
        uint16_t *costOutput,
        uint16_t width,
        uint16_t height,
        uint8_t numDisparities,
        float maxMinCostRatio);

float computeErrorsGroundTruth(
        uint8_t *dispOut,
        uint8_t *gtImage,
        uint8_t *diffImage,
        uint16_t dispWidth,
        uint16_t dispHeight,
        uint16_t gtWidth,
        uint16_t gtHeight,
        uint8_t filterWidth,
        uint8_t filterHeight,
        uint8_t numDisparities,
        uint8_t gtScale,
        uint8_t *maxDiffPtr
);

int32_t computeSADdisparity8bits(
        uint8_t *disparity_inputLeft, 
        uint8_t *disparity_inputRight,
        uint8_t *dispOutput,
        uint16_t *minCostOutput,
        uint16_t *natC_allCostOutput,
        DISPARITY_TI_CreateParams *disparity_createParams,
        uint16_t imageWidth,
        uint16_t imageHeight,
        uint16_t srcImagePitch,
        uint16_t dstImagePitch
);


void vcop_disparity_hammingDistance_row_ref_cn
(
        uint8_t *left,
        uint8_t *right,
        uint16_t leftStride,
        uint16_t rightStride,
        uint8_t winWidth,
        uint8_t winHeight,
        uint8_t *disparityOutput,
        uint16_t *minCostOutput,
        uint16_t *allCostOutput,
        uint16_t width,
        uint8_t numDisparities,
        uint8_t disparityStep,
        uint8_t codeWordLen,
        uint8_t searchDir
); 

void vcop_disparity_hammingDistance_first_row_cn
(
        uint8_t *left,
        uint8_t *right,
        uint16_t leftStride,
        uint16_t rightStride,
        uint8_t winWidth,
        uint8_t winHeight,
        uint8_t *disparityOutput,
        uint16_t *minCostOutput,
        uint16_t *allCostOutput,
        uint16_t width,
        uint16_t allCostOutputStride,
        uint8_t numDisparities,
        uint8_t disparityStep,
        uint8_t codeWordLen,
        uint8_t searchDir
);

void vcop_disparity_hammingDistance_nth_row_cn
(
        uint8_t *left,
        uint8_t *right,
        uint16_t leftStride,
        uint16_t rightStride,
        uint8_t winWidth,
        uint8_t winHeight,
        uint8_t *disparityOutput,
        uint16_t *minCostOutput,
        uint16_t *prevAllCostOutput,
        uint16_t *allCostOutput,
        uint16_t width,
        uint16_t allCostOutputStride,
        uint8_t numDisparities,
        uint8_t disparityStep,
        uint8_t codeWordLen,
        uint8_t searchDir
);

#endif


