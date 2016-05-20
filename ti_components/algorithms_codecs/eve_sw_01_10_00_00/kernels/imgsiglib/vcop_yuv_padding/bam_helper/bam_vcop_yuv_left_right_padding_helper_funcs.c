/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_vcop_yuv_left_right_padding_helper_funcs.c
 *
 *  @brief      This file defines interfaces for integrating YUV
 *              Padding into BAM
 */

#include <stdio.h>
#include <stdlib.h>

#include "evealgframework.h"
#include "bam_vcop_yuv_left_right_padding_int.h"
#include "vcop_yuv_left_right_padding_kernel.h" /* compiler should take care of include path */

/* Function Prototypes */
static BAM_Status BAM_yuvLeftRightPadding_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks);

static BAM_Status BAM_yuvLeftRightPadding_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks)
{
    const BAM_yuvLeftRightPadding_Args *args = (const BAM_yuvLeftRightPadding_Args *) kernelArgs;

#if (!VCOP_HOST_EMULATION)
    internalBlock[PARAMS_IDX1].size = 2U*vcop_yuv_left_right_padding_u8_param_count();
    internalBlock[PARAMS_IDX2].size = 2U*vcop_yuv_left_right_padding_u16_param_count();
#else
    internalBlock[PARAMS_IDX1].size = 4;
    internalBlock[PARAMS_IDX2].size = 4;
#endif

    outBlock[OUT_LEFT_IDX].size   = (args->out_stride*args->height);
    outBlock[OUT_LEFT_IDX].space  = BAM_MEMSPACE_IBUFLA;
    outBlock[OUT_RIGHT_IDX].size  = (args->out_stride*args->height);
    outBlock[OUT_RIGHT_IDX].space = BAM_MEMSPACE_IBUFHA;

    outBlock[OUT_CHROMA_LEFT_IDX].size   = ((args->out_stride*args->height)/2);
    outBlock[OUT_CHROMA_LEFT_IDX].space  = BAM_MEMSPACE_IBUFLA;
    outBlock[OUT_CHROMA_RIGHT_IDX].size  = ((args->out_stride*args->height)/2);
    outBlock[OUT_CHROMA_RIGHT_IDX].space = BAM_MEMSPACE_IBUFHA;
    return BAM_S_SUCCESS;
}

BAM_KernelInfo gBAM_TI_yuvLeftRightPaddingKernel =
{
    0,                                      /* kernelId */
    sizeof(BAM_yuvLeftRightPadding_Context),
    sizeof(BAM_yuvLeftRightPadding_Args),
    BAM_EVE,                                /* coreType */
    BAM_NODE_COMPUTE,                       /* nodeType */
    NUM_IN_BLOCKS,                          /* 3 */
    NUM_OUT_BLOCKS,                         /* 1 */
    NUM_INTERNAL_BLOCKS                     /* 1 */
};

BAM_KernelHelperFuncDef gBAM_TI_yuvLeftRightPaddingHelperFunc =
{ &BAM_yuvLeftRightPadding_getMemRecFunc, NULL};

