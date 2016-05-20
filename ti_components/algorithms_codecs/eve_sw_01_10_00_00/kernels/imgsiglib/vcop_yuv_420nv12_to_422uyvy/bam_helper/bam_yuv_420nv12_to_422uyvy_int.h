/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_yuv_420nv12_to_422uyvy_int.h
 *
 *  @brief      This header defines internal structures for YUV420 NV12
 *              to YUV422 UYVY format conversion into BAM.
 */

#ifndef BAM_YUV_420NV12_TO_422UYVY_INT_H
#define BAM_YUV_420NV12_TO_422UYVY_INT_H

#include <stdint.h>
#include <vcop.h>

#include "evealgframework.h"
#include "bam_yuv_420nv12_to_422uyvy.h"

#ifndef NATC
#define NATC 0
#endif

#define YUV_420NV12_TO_422UYVY_NUM_IN_BLOCKS       (1U)
#define YUV_420NV12_TO_422UYVY_NUM_OUT_BLOCKS      (1U)
#define YUV_420NV12_TO_422UYVY_NUM_INTERNAL_BLOCKS (1U)

#define YUV_420NV12_TO_422UYVY_IN_IMG_IDX (BAM_YUV_420NV12_TO_422UYVY_INPUT_PORT_IMG)      /* 0 */
#define YUV_420NV12_TO_422UYVY_OUT_IDX    (BAM_YUV_420NV12_TO_422UYVY_OUTPUT_PORT)         /* 0 */
#define PARAMS_IDX (0U)                                            /* 0 */


typedef struct bam_yuv_420nv12_to_422uyvy_context
{
    /* Must always follow this order: pInternalBlock[], pInBlock[], pOutputBlock[], args */
    void *pInternalBlock[YUV_420NV12_TO_422UYVY_NUM_INTERNAL_BLOCKS];
    void *pInBlock[YUV_420NV12_TO_422UYVY_NUM_IN_BLOCKS];
    void *pOutBlock[YUV_420NV12_TO_422UYVY_NUM_OUT_BLOCKS];
    BAM_Yuv_420nv12_to_422uyvy_Args kernelArgs;
} BAM_Yuv_420nv12_to_422uyvy_Context;

#endif /* BAM_YUV_420NV12_TO_422UYVY_INT_H */

