/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_yuv420_fir2d_separable_int.h
 *
 *  @brief      This header defines internal structures  YUV420 filter kernel
 *              into BAM.
 */

#ifndef BAM_YUV420_FIR2D_SEPARABLE_INT_H_
#define BAM_YUV420_FIR2D_SEPARABLE_INT_H_

#include <stdint.h>
#include <vcop.h>

#include "evealgframework.h"
#include "bam_yuv420_fir2d_separable.h"

#define NUM_IN_BLOCKS       (1U)
#define NUM_OUT_BLOCKS      (1U)
#define NUM_INTERNAL_BLOCKS (4U)

#define YUV420_FIR2D_SEPARABLE_IN_IDX (0)     /* 0 */

#define YUV420_FIR2D_SEPARABLE_OUT_IDX (0)   /* 0 */

#define YUV420_FIR2D_SEPARABLE_INTERNAL_PARAMS_IDX    (0)                /* 0 */
#define YUV420_FIR2D_SEPARABLE_INTERNAL_INTERM_IDX    (1U)                /* 0 */
#define YUV420_FIR2D_SEPARABLE_INTERNAL_COEF_HORZ_IDX (2U)                /* 0 */
#define YUV420_FIR2D_SEPARABLE_INTERNAL_COEF_VERT_IDX (3U)                /* 0 */



typedef struct bam_yuv420_fir2d_separable_context
{
    /* Must always follow this order: pInternalBlock[], pInBlock[], pOutputBlock[], args */
    void *pInternalBlock[NUM_INTERNAL_BLOCKS];
    void *pInBlock[NUM_IN_BLOCKS];
    void *pOutBlock[NUM_OUT_BLOCKS];
    BAM_Yuv420_fir2dseparable_Args kernelArgs;
} BAM_Yuv420_fir2dseparable_Context;

#endif /* BAM_YUV420_FIR2D_SEPARABLE_INT_H_*/

