/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_hough_for_lines.h
 *
 *  @brief      This header defines interfaces for integrating hough for lines
 *              into BAM.
 */

#ifndef BAM_HOUGH_FOR_LINES_H_
#define BAM_HOUGH_FOR_LINES_H_

#include "bam_common.h"

#define HOUGH_FOR_LINES_MAX_THETA_RANGE   (360U)
#define HOUGH_FOR_LINES_MAX_LIST_SIZE     (4000U)
#define HOUGH_FOR_LINES_RHO_MAX_LENGTH    (800U)
#define HOUGH_FOR_LINES_RHO_MAX_LENGTH_INBYTES (HOUGH_FOR_LINES_RHO_MAX_LENGTH * sizeof(uint16_t))

#define HOUGH_FOR_LINES_IMG_BUF_A_B_OFFSET (0x20000U)

typedef struct bam_hough_for_lines_ctrl_args
{
    uint16_t    imgWidth;
    uint16_t    imgHeight;
    uint16_t    listSize;
    uint16_t    rhoMaxLength;
    uint16_t    thetaStart;
    uint16_t    thetaEnd;
    uint8_t     thetaStepSize;
} BAM_HoughForLines_CtrlArgs;

extern BAM_KernelHelperFuncDef gBAM_TI_houghForLinesHelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_houghForLinesExecFunc;

extern BAM_KernelInfo gBAM_TI_houghForLinesKernel;

typedef enum
{
  BAM_HOUGH_FOR_LINES_EDGE_LIST_PORT   =   0,
  BAM_HOUGH_FOR_LINES_VOTED_RHO_THETA_IN_PORT,
  BAM_HOUGH_FOR_LINES_NUM_INPUT_BLOCKS
} eBAM_HOUGH_FOR_LINES_INPUT_PORTS;

typedef enum
{
  BAM_HOUGH_FOR_LINES_NUM_OUTPUT_BLOCKS
} eBAM_HOUGH_FOR_LINES_OUTPUT_PORTS;

#endif /* BAM_HOUGH_FOR_LINES_H_ */

