/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_median_filter.h
 *
 *  @brief      This header defines interfaces for integrating median filter
 *              into BAM.
 */

#ifndef BAM_MEDIAN_FILTER_H_
#define BAM_MEDIAN_FILTER_H_

typedef struct bam_median_filter_args
{
    uint8_t   blockWidth;
    uint8_t   blockHeight;
    uint16_t  kernelWidth;
    uint16_t  kernelHeight;
    uint16_t  stepSizeHorz;
    uint16_t  stepSizeVert;
} BAM_Median_Filter_Args;

extern BAM_KernelHelperFuncDef gBAM_TI_medianFilterHelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_medianFilterExecFunc;

extern BAM_KernelInfo gBAM_TI_medianFilterKernel;

#define BAM_MEDIAN_FILTER_INPUT_PORT     (0U)
#define BAM_MEDIAN_FILTER_OUTPUT_PORT    (0U)

#define BAM_MEDIAN_FILTER_TEMP_PARAM     (0U)
#define BAM_MEDIAN_FILTER_HISTOGRAM      (1U)
#define BAM_MEDIAN_FILTER_TEMP_WGT       (2U)
#define BAM_MEDIAN_FILTER_TEMP_HISTO     (3U)
#define BAM_MEDIAN_FILTER_TEMP_BLK_HIST  (4U)
#define BAM_MEDIAN_FILTER_COARSE_HIST    (5U)

#endif /* BAM_MEDIAN_FILTER_H_ */

