/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_remap_int.h
 *
 *  @brief      This header defines internal structures for remap kernel
 *              into BAM.
 */
#ifndef BAM_REMAP_MERGE_INT_H_
#define BAM_REMAP_MERGE_INT_H_

#include <stdint.h>
#include <vcop.h>

#include "evealgframework.h"

#include "bam_remap_merge.h"

#include "remap.h"
#include "remap_common.h"

#include "bam_remap.h"                        /* KERNEL NODE  */
#include "bam_memcpy.h"                       /* KERNEL NODE  */
#include "bam_alpha_blend_yuv420nv12.h"       /* KERNEL NODE  */
#include "bam_alpha_blend_yuv422i.h"          /* KERNEL NODE  */
#include "bam_yuv_420nv12_to_422uyvy.h"       /* KERNEL NODE  */
#include "bam_yuv_422uyvy_to_420nv12.h"       /* KERNEL NODE  */
#include "bam_remap_int.h"
#include "bam_memcpy_int.h"
#include "bam_alpha_blend_yuv420nv12_int.h"
#include "bam_alpha_blend_yuv422i_int.h"
#include "bam_yuv_420nv12_to_422uyvy_int.h"
#include "bam_yuv_422uyvy_to_420nv12_int.h"

#define MAX_NUM_KERNELS                 (3U)

#define REMAP_MERGE_NUM_IN_BLOCKS       (BAM_REMAP_MERGE_INPUT_PORT_ALPHA_BLOCK + 1U)
#define REMAP_MERGE_NUM_OUT_BLOCKS      (1U)
#define REMAP_MERGE_NUM_INTERNAL_BLOCKS (REMAP_MERGE_KERNEL2_OUTPUT_PTR_IDX + 1U)                         /* 8 */

/* Input Blocks Pointer Indexes */
#define REMAP_MERGE_INPUT_IMAGE_BLOCK_PTR_IDX     (0U)
#define REMAP_MERGE_LUT_PTR_IDX                   (1U)
#define BAM_REMAP_MERGE_INPUT_PORT_MERGE_BLOCK    (2U)
#define BAM_REMAP_MERGE_INPUT_PORT_ALPHA_BLOCK    (3U)

/* Output Blocks Pointer Indexes */
#define REMAP_MERGE_OUT_LUMA_IDX                  (0U)

/* Internal Blocks Pointer Indexes */
/* KERNEL 1 refers to Remap Kernel */
/* KERNEL 2 can be Format Convert or Alpha Blend Kernel */
/* KERNEL 3 refers to Alpha Blend Kernel */
#define REMAP_MERGE_INTERPOLATION_BUF0_PTR_IDX           (REMAP_INTERPOLATION_BUF0_PTR_IDX)               /* 0 */                                            /* 0 */
#define REMAP_MERGE_INTERPOLATION_BUF1_PTR_IDX           (REMAP_INTERPOLATION_BUF1_PTR_IDX)               /* 1 */
#define REMAP_MERGE_PBLOCK_PTR_IDX                       (REMAP_PBLOCK_PTR_IDX)                           /* 2 */
#define REMAP_MERGE_CHROMA_TLU_INDEX_PTR_IDX             (REMAP_CHROMA_TLU_INDEX_PTR_IDX)                 /* 3 */
#define REMAP_MERGE_SCATTERED_DEST_OFFSET_VALUES_PTR_IDX (REMAP_SCATTERED_DEST_OFFSET_VALUES_PTR_IDX)     /* 4 */
#define REMAP_MERGE_DEINTERLEAVED_CHROMA_U_V_PTR_IDX     (REMAP_DEINTERLEAVED_CHROMA_U_V_PTR_IDX)         /* 5 */
#define REMAP_MERGE_KERNEL1_OUTPUT_PTR_IDX               (REMAP_MERGE_DEINTERLEAVED_CHROMA_U_V_PTR_IDX + 1U) /* 6 */
#define REMAP_MERGE_KERNEL2_OUTPUT_PTR_IDX               (REMAP_MERGE_KERNEL1_OUTPUT_PTR_IDX + 1U)           /* 7 */

typedef struct bam_remap_merge_context
{
    /* Must always follow this order: pInternalBlock[], pInBlock[], pOutputBlock[], args */
    void *pInternalBlock[REMAP_MERGE_NUM_INTERNAL_BLOCKS];
    void *pInBlock[REMAP_MERGE_NUM_IN_BLOCKS];
    void *pOutBlock[REMAP_MERGE_NUM_OUT_BLOCKS];
    BAM_Remap_Merge_Args               kernelArgs;
    BAM_Remap_Context                  remapContext;
    BAM_Memcpy_Context                 memcpyContext;
    BAM_Yuv_420nv12_to_422uyvy_Context formatConvertContext;
    BAM_Alpha_Blend_YUV420nv12_Context mergeContext;
    uint8_t         numInitFunc;
    BAM_KernelFunc  initFuncList[MAX_NUM_KERNELS];
    void           *kernelContext[MAX_NUM_KERNELS];
    uint8_t         numvloopFunc;
    BAM_KernelFunc  vloopFuncList[MAX_NUM_KERNELS];
    void           *pblockList[MAX_NUM_KERNELS];
} BAM_Remap_Merge_Context;


#endif /* BAM_REMAP_MERGE_INT_H_*/
