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
#ifndef BAM_REMAP_INT_H_
#define BAM_REMAP_INT_H_

#include <stdint.h>
#include <vcop.h>

#include "evealgframework.h"
#include "bam_remap.h"

#define REMAP_NUM_IN_BLOCKS       (2U)
#define REMAP_NUM_OUT_BLOCKS      (1U)
#define REMAP_NUM_INTERNAL_BLOCKS (REMAP_DEINTERLEAVED_CHROMA_U_V_PTR_IDX + 1U)                   /* 6 */

/* Input Blocks Pointer Indexes */
#define REMAP_INPUT_IMAGE_BLOCK_PTR_IDX     (0U)
#define REMAP_LUT_PTR_IDX                   (1U)


/* Output Blocks Pointer Indexes */
#define REMAP_OUT_LUMA_IDX                  (0U)


/* Internal Blocks Pointer Indexes */
#define REMAP_INTERPOLATION_BUF0_PTR_IDX    (0U)                                                  /* 0 */
#define REMAP_INTERPOLATION_BUF1_PTR_IDX    (REMAP_INTERPOLATION_BUF0_PTR_IDX + 1U)               /* 1 */
#define REMAP_MAX_INTERPOLATION_BUF_PTR_IDX (REMAP_INTERPOLATION_BUF1_PTR_IDX)                   /* 1 */

#define REMAP_PBLOCK_PTR_IDX                (REMAP_MAX_INTERPOLATION_BUF_PTR_IDX + 1U)            /* 2 */
#define REMAP_CHROMA_TLU_INDEX_PTR_IDX      (REMAP_MAX_INTERPOLATION_BUF_PTR_IDX + 2U)            /* 3 */

/* For YUV 420 SP and YUV 422 ILE and IBE */
#define REMAP_SCATTERED_DEST_OFFSET_VALUES_PTR_IDX (REMAP_MAX_INTERPOLATION_BUF_PTR_IDX + 3U)     /* 4 */

/* For YUV 422 ILE and IBE */
#define REMAP_DEINTERLEAVED_CHROMA_U_V_PTR_IDX     (REMAP_MAX_INTERPOLATION_BUF_PTR_IDX + 4U)     /* 5 */


typedef VcopRemapContext VCOP_Remap_Context;

typedef struct bam_remap_context
{
    /* Must always follow this order: pInternalBlock[], pInBlock[], pOutputBlock[], args */
    void *pInternalBlock[REMAP_NUM_INTERNAL_BLOCKS];
    void *pInBlock[REMAP_NUM_IN_BLOCKS];
    void *pOutBlock[REMAP_NUM_OUT_BLOCKS];
    BAM_Remap_Args kernelArgs;
    VCOP_Remap_Context vcopContext;
    int32_t (*vloopFunc)(VCOP_Remap_Context *vcopContext);
} BAM_Remap_Context;

#endif /* BAM_REMAP_INT_H_*/
