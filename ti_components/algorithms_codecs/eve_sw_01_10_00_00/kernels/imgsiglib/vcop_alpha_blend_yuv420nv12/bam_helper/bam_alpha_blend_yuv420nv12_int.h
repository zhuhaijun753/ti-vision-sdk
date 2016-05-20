/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_alpha_blend_yuv420nv12_int.h
 *
 *  @brief      This header defines internal structures for YUV420 NV12
 *              Alpha Blending into BAM.
 */

#ifndef BAM_ALPHA_BLEND_YUV420NV12_INT_H
#define BAM_ALPHA_BLEND_YUV420NV12_INT_H

#include <stdint.h>
#include <vcop.h>

#include "evealgframework.h"
#include "bam_alpha_blend_yuv420nv12.h"

#ifndef NATC
#define NATC 0
#endif

#define NUM_IN_BLOCKS       (3U)
#define NUM_OUT_BLOCKS      (1U)
#define NUM_INTERNAL_BLOCKS (1U)

#define ALPHA_BLEND_YUV420_IN_IMG1_IDX  (BAM_ALPHA_BLEND_YUV420NV12_INPUT_PORT_IMG1)    /* 0 */
#define ALPHA_BLEND_YUV420_IN_IMG2_IDX  (BAM_ALPHA_BLEND_YUV420NV12_INPUT_PORT_IMG2)    /* 1 */
#define ALPHA_BLEND_YUV420_IN_ALPHA_IDX (BAM_ALPHA_BLEND_YUV420NV12_INPUT_PORT_ALPHA)   /* 2 */

#define ALPHA_BLEND_YUV420_OUT_IDX      (BAM_ALPHA_BLEND_YUV420NV12_OUTPUT_PORT)        /* 0 */

#define PARAMS_IDX (0U)                                            /* 0 */


typedef struct bam_alpha_blend_yuv420nv12_context
{
    /* Must always follow this order: pInternalBlock[], pInBlock[], pOutputBlock[], args */
    void *pInternalBlock[NUM_INTERNAL_BLOCKS];
    void *pInBlock[NUM_IN_BLOCKS];
    void *pOutBlock[NUM_OUT_BLOCKS];
    BAM_Alpha_Blend_YUV420nv12_Args kernelArgs;
} BAM_Alpha_Blend_YUV420nv12_Context;

#endif /* BAM_ALPHA_BLEND_YUV420NV12_INT_H */

