/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
* @file bam_orientation_binning_helper_funcs.h
*
* @brief
*
*  @author Anshu Jain(anshu.jain@ti.com)
*
* @version 0.0 (Aug 2013) : Base version.
*/

#ifndef BAM_ORIENTATION_BINNING_HELPER_FUNCS_H_
#define BAM_ORIENTATION_BINNING_HELPER_FUNCS_H_

#include "evealgframework.h"
#include "bam_orientation_binning.h"
#include <vcop.h>
#include <stdint.h>

/*
1 Internal Block for param register
2. Sin table
3. Cos table
*/
#define ORIENTATION_BINNING_NUM_INTERNAL_BLOCKS 5u

/*Two Input blocks for GradX and GradY*/
#define ORIENTATION_BINNING_NUM_IN_BLOCKS 2u

/*One output block for binned output image */
#define ORIENTATION_BINNING_NUM_OUT_BLOCKS 1u


/* Index for Internal Blocks */
#define ORIENTATION_BINNING_INTERNAL_PARAMS_IDX        (0u)
#define ORIENTATION_BINNING_INTERNAL_SIN_TAB_IDX       (1u)
#define ORIENTATION_BINNING_INTERNAL_COS_TAB_IDX       (2u)
#define ORIENTATION_BINNING_INTERNAL_ABS_GRADX_IDX     (3u)
#define ORIENTATION_BINNING_INTERNAL_ABS_GRADY_IDX     (4u)



/* Index for Input Blocks */
#define ORIENTATION_BINNING_IN_GRADX_IDX        (0u)
#define ORIENTATION_BINNING_IN_GRADY_IDX        (1u)



/* Index for output Block */
#define ORIENTATION_BINNING_OUT_BIN_IDX   (0u)

typedef struct bam_orientation_binning_context
{
    void *pInternalBlock[ORIENTATION_BINNING_NUM_INTERNAL_BLOCKS];
    void *pInBlock[ORIENTATION_BINNING_NUM_IN_BLOCKS];
    void *pOutBlock[ORIENTATION_BINNING_NUM_OUT_BLOCKS];
    BAM_orientation_binning_Args  kernelArgs;
    BAM_KernelCustom kernelCustom;
} BAM_orientation_binning_Context;

#endif /* BAM_ORIENTATION_BINNING_HELPER_FUNCS_H_*/

