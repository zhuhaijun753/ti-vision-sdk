/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_hough_for_circles_int.h
 *
 *  @brief      This header defines internal structures for Hough for
 *              circles kernel.
 */

#ifndef BAM_HOUGH_FOR_CIRCLES_INT_H_
#define BAM_HOUGH_FOR_CIRCLES_INT_H_

#include <stdint.h>
#include <vcop.h>

#include "evealgframework.h"
#include "bam_hough_for_circles.h"

/* For Compute Hough Space index BAM node */

typedef enum
{
  HOUGH_FOR_CIRCLES_INTERNAL_PARAMS_IDX = 0,
  HOUGH_FOR_CIRCLES_INTERNAL_SCRATCH_IDX,
  HOUGH_FOR_CIRCLES_INTERNAL_RADIUS_PTR_IDX,
  HOUGH_FOR_CIRCLES_INTERNAL_NUM_BLOCK
} eBAM_HOUGH_FOR_CIRCLES_INTERNAL_BLOCKS;

typedef struct
{
    /* Must always follow this order: pInternalBlock[], pInBlock[], pOutputBlock[], args */
    void *pInternalBlock[HOUGH_FOR_CIRCLES_INTERNAL_NUM_BLOCK];
    void *pInBlock[BAM_HOUGH_FOR_CIRCLES_NUM_INPUT_BLOCKS];
    void *pOutBlock[BAM_HOUGH_FOR_CIRCLES_NUM_OUTPUT_BLOCKS];
    BAM_HoughForCircles_Args kernelInitArgs;
    BAM_HoughForCircles_CtrlArgs kernelCtrlArgs;
    uint16_t * paramBlockUpdatePblock;
    int8_t * currentRadiusPtr[2];/* Need two buffers to store Ping Pong Addresses */
    uint8_t radIdx;
    uint8_t pingPongFlag;
} BAM_HoughForCircles_Context;


/* For Circle Detect BAM node */

typedef enum
{
  HOUGH_FOR_CIRCLES_DETECT_INTERNAL_PARAMS_IDX = 0,
  HOUGH_FOR_CIRCLES_DETECT_INTERNAL_HOUGH_SPACE_IDX,
  HOUGH_FOR_CIRCLES_DETECT_INTERNAL_UPPERXY_IDX,
  HOUGH_FOR_CIRCLES_DETECT_INTERNAL_XSEQ_IDX,
  HOUGH_FOR_CIRCLES_DETECT_INTERNAL_NUM_BLOCK
} eBAM_HOUGH_FOR_CIRCLES_DETECT_INTERNAL_BLOCKS;

typedef struct
{
    /* Must always follow this order: pInternalBlock[], pInBlock[], pOutputBlock[], args */
    void *pInternalBlock[HOUGH_FOR_CIRCLES_DETECT_INTERNAL_NUM_BLOCK];
    void *pInBlock[BAM_HOUGH_FOR_CIRCLES_DETECT_NUM_INPUT_BLOCKS];
    void *pOutBlock[BAM_HOUGH_FOR_CIRCLES_DETECT_NUM_OUTPUT_BLOCKS];
    BAM_HoughForCirclesDetect_Args kernelInitArgs;
    BAM_HoughForCirclesDetect_CtrlArgs kernelCtrlArgs;
    uint16_t *pBlockHoughSpaceInit;
    uint16_t *pBlockHoughSpaceVote;
    uint16_t *pBlockCircleDetect;
    uint16_t *pBlockHoughSpaceVoteUpdateParams;
    uint8_t numBlks;
    uint16_t numElemsInLastBlk;
    uint8_t blkIdx;
    uint8_t pingPongFlag;
} BAM_HoughForCirclesDetect_Context;

#endif /* BAM_HOUGH_FOR_CIRCLES_INT_H_*/
