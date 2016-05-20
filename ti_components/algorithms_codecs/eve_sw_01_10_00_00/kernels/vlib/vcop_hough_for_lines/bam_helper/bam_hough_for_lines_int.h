/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_hough_for_lines_int.h
 *
 *  @brief      This header defines internal structures for  Hough For Lines kernel .
 */

#ifndef BAM_HOUGH_FOR_LINES_INT_H_
#define BAM_HOUGH_FOR_LINES_INT_H_

#include <stdint.h>
#include <vcop.h>

#include "evealgframework.h"
#include "bam_hough_for_lines.h"

#define SQRTof2_Q8      (362U)
/* CHECK_MISRA("-19.7")  -> Disable rule 19.7  */
/* These are simple non-harmful macros.   */
#define max(x,y)         ((x) > (y) ? (x) : (y))
/* RESET_MISRA("19.7")  -> Reset rule 19.7     */

typedef enum
{
  HOUGH_FOR_LINES_INTERNAL_PARAMS_IDX   =    0,
  HOUGH_FOR_LINES_INTERNAL_INDEX_ARRAY_IDX,
  HOUGH_FOR_LINES_INTERNAL_VOTED_RHOARRAY_8COPY_IDX,
  HOUGH_FOR_LINES_INTERNAL_TRANSPOSE_BUF_IDX,
  HOUGH_FOR_LINES_INTERNAL_COSIN_MUL_NORM_IDX,
  HOUGH_FOR_LINES_INTERNAL_SCATTER_OFFSET_IDX,
  HOUGH_FOR_LINES_INTERNAL_NUM_BLOCK
} eBAM_HOUGH_FOR_LINES_INTERNAL_BLOCKS;


#define NUM_IN_BLOCKS (BAM_HOUGH_FOR_LINES_NUM_INPUT_BLOCKS)
#define NUM_OUT_BLOCKS (BAM_HOUGH_FOR_LINES_NUM_OUTPUT_BLOCKS)
#define NUM_INTERNAL_BLOCKS (HOUGH_FOR_LINES_INTERNAL_NUM_BLOCK)

typedef struct
{
    /* Must always follow this order: pInternalBlock[], pInBlock[], pOutputBlock[], args */
    void *pInternalBlock[NUM_INTERNAL_BLOCKS];
    void *pInBlock[NUM_IN_BLOCKS];
    BAM_HoughForLines_CtrlArgs kernelArgs;
    uint16_t  * paramBlockKernel1;
    uint16_t  * paramBlockKernel2;
    uint16_t    currThetaIdx;
    uint16_t    normalizationFactorQ8;
    uint8_t     pingPong;
    int16_t     *pCosSinMulNorm[2];
} BAM_HoughForLines_Context;

#endif /* BAM_HOUGH_FOR_LINES_INT_H_*/


