/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_vcop_hog_vector.h
 *
 *  @brief      This header defines interfaces for integrating hog vector compute kernel
 *              into BAM.
 */

#ifndef BAM_HOG_VECTOR_
#define BAM_HOG_VECTOR_

typedef enum
{
  EVE_VLIB_SLIDING_2x2_SUM_PLANAR,
  EVE_VLIB_SLIDING_2x2_SUM_DEINTERLEAVED,
  EVE_VLIB_SLIDING_2x2_SUM_MAX
} EVE_VLIB_Sliding2x2SumFormate ;

typedef struct 
{
    uint16_t     blockStride;
    uint16_t     blockWidth;
    uint16_t     blockHeight;
    uint8_t      sun2x2outFormat;
} BAM_sliding_2x2_sum_Args;

extern BAM_KernelHelperFuncDef gBAM_TI_sliding2x2SumHelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_sliding2x2SumExecFunc;

extern BAM_KernelInfo gBAM_TI_sliding2x2SumKernel;

#define BAM_SLIDING_2x2_SUM_INPUT_PORT     ( 0 )
#define BAM_SLIDING_2x2_SUM_OUTPUT_PORT1   ( 0 )
#define BAM_SLIDING_2x2_SUM_OUTPUT_PORT2   ( 1 )

#endif /* BAM_HOG_VECTOR_ */
