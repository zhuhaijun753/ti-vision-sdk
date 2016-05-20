/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_alpha_blend_yuv422i_int.h
 *
 *  @brief      This header defines internal structures for YUV422 Interleaved
 *              Alpha Blending into BAM.
 */


#ifndef BAM_ALPHA_BLEND_YUV422I_INT_H
#define BAM_ALPHA_BLEND_YUV422I_INT_H

#include <stdint.h>
#include <vcop.h>

#include "evealgframework.h"
#include "bam_alpha_blend_yuv422i.h"

#ifndef NATC
#define NATC 0
#endif

#define ALPHA_BLEND_YUV422I_NUM_IN_BLOCKS       (3U)
#define ALPHA_BLEND_YUV422I_NUM_OUT_BLOCKS      (1U)
#define ALPHA_BLEND_YUV422I_NUM_INTERNAL_BLOCKS (1U)

#define ALPHA_BLEND_YUV422I_IN_IMG1_IDX  (BAM_ALPHA_BLEND_YUV422I_INPUT_PORT_IMG1)    /* 0 */
#define ALPHA_BLEND_YUV422I_IN_IMG2_IDX  (BAM_ALPHA_BLEND_YUV422I_INPUT_PORT_IMG2)    /* 1 */
#define ALPHA_BLEND_YUV422I_IN_ALPHA_IDX (BAM_ALPHA_BLEND_YUV422I_INPUT_PORT_ALPHA)   /* 2 */

#define ALPHA_BLEND_YUV422I_OUT_IDX      (BAM_ALPHA_BLEND_YUV422I_OUTPUT_PORT)        /* 0 */

#define PARAMS_IDX (0U)                                         /* 0 */


typedef struct bam_alpha_blend_yuv422i_context
{
    /* Must always follow this order: pInternalBlock[], pInBlock[], pOutputBlock[], args */
    void *pInternalBlock[ALPHA_BLEND_YUV422I_NUM_INTERNAL_BLOCKS];
    void *pInBlock[ALPHA_BLEND_YUV422I_NUM_IN_BLOCKS];
    void *pOutBlock[ALPHA_BLEND_YUV422I_NUM_OUT_BLOCKS];
    BAM_Alpha_Blend_YUV422i_Args kernelArgs;
} BAM_Alpha_Blend_YUV422i_Context;

#endif /* BAM_ALPHA_BLEND_YUV422I_INT_H */

