/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_yuv_422uyvy_to_420nv12_int.h
 *
 *  @brief      This header defines internal structures for YUV422 UYVY
 *              to YUV420 NV12 format conversion into BAM.
 */

#ifndef BAM_YUV_422UYVY_TO_420NV12_INT_H
#define BAM_YUV_422UYVY_TO_420NV12_INT_H

#include <stdint.h>
#include <vcop.h>

#include "evealgframework.h"
#include "bam_yuv_422uyvy_to_420nv12.h"

#ifndef NATC
#define NATC 0
#endif

#define YUV_422UYVY_TO_420NV12_NUM_IN_BLOCKS       (1U)
#define YUV_422UYVY_TO_420NV12_NUM_OUT_BLOCKS      (1U)
#define YUV_422UYVY_TO_420NV12_NUM_INTERNAL_BLOCKS (1U)

#define YUV_422UYVY_TO_420NV12_IN_IMG_IDX (BAM_YUV_422UYVY_TO_420NV12_INPUT_PORT_IMG)      /* 0 */
#define YUV_422UYVY_TO_420NV12_OUT_IDX    (BAM_YUV_422UYVY_TO_420NV12_OUTPUT_PORT)         /* 0 */
#define PARAMS_IDX (0U)                                            /* 0 */

typedef struct bam_yuv_422uyvy_to_420nv12_context
{
    /* Must always follow this order: pInternalBlock[], pInBlock[], pOutputBlock[], args */
    void *pInternalBlock[YUV_422UYVY_TO_420NV12_NUM_INTERNAL_BLOCKS];
    void *pInBlock[YUV_422UYVY_TO_420NV12_NUM_IN_BLOCKS];
    void *pOutBlock[YUV_422UYVY_TO_420NV12_NUM_OUT_BLOCKS];
    BAM_Yuv_422uyvy_to_420nv12_Args kernelArgs;
} BAM_Yuv_422uyvy_to_420nv12_Context;

#endif /* BAM_YUV_422UYVY_TO_420NV12_INT_H */

