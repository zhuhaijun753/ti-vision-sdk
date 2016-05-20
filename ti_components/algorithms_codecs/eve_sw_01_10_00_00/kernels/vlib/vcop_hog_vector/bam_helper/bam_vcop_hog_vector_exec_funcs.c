/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_vcop_hog_vector_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating hog vector compute kernel
 *              function into BAM.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_vcop_hog_vector_int.h"
#include "bam_vcop_hog_vector.h"
#include "vcop_hog_vector_kernel.h" /* compiler should take care of include path */

/* Function Prototypes */
static BAM_Status Bam_sliding_2x2_sum_initFrame(void *kernelContext);
static BAM_Status BAM_sliding_2x2_sum_compute(void *kernelContext);

static BAM_Status Bam_sliding_2x2_sum_initFrame(void *kernelContext)
{
    BAM_sliding_2x2_sum_Context *context = (BAM_sliding_2x2_sum_Context *) kernelContext;
    BAM_Status status = 0;
    if(context->kernelArgs.sun2x2outFormat >= EVE_VLIB_SLIDING_2x2_SUM_MAX)
    {
      status = BAM_E_FAIL;
    }
    else 
    {
#if !(VCOP_HOST_EMULATION)
    if(context->kernelArgs.sun2x2outFormat == EVE_VLIB_SLIDING_2x2_SUM_DEINTERLEAVED)
    {
      vcop_ti_pd_2x2_sum_init((uint16_t*)context->pInBlock[IN_IDX],
                              (uint16_t*)context->pOutBlock[OUT_IDX1],
                              (uint16_t*)context->pOutBlock[OUT_IDX2],
                                context->kernelArgs.blockWidth,
                                context->kernelArgs.blockHeight,
                                context->kernelArgs.blockStride,
                                (uint16_t*)context->pInternalBlock[PARAMS_IDX]);
      context->kernelCustom = &vcop_ti_pd_2x2_sum_vloops;
    }
    /* CHECK_MISRA("-14.1")  -> Disable rule 14.1  */
    /* Currently sun2x2outFormat will not be grater than EVE_VLIB_SLIDING_2x2_SUM_PLANAR, hence code is unreachable but  */
    /* as the implementation of the function changes, it will not be unreachable.   */
    /* UNREACH.GEN or INVARIANT_CONDITION.UNREACH */
    else if(context->kernelArgs.sun2x2outFormat == EVE_VLIB_SLIDING_2x2_SUM_PLANAR)
    {
      vcop_ti_pd_2x2_sum_planar_init((uint16_t*)context->pInBlock[IN_IDX],
                              (uint16_t*)context->pOutBlock[OUT_IDX1],
                                context->kernelArgs.blockWidth,
                                context->kernelArgs.blockHeight,
                                context->kernelArgs.blockStride,
                                (uint16_t*)context->pInternalBlock[PARAMS_IDX]);
      context->kernelCustom = &vcop_ti_pd_2x2_sum_planar_vloops;
    }
    else
    {
      status = BAM_E_FAIL;
   }
  /* RESET_MISRA("14.1")  -> Reset rule 14.1      */
#endif
   }
    return status;
}

static BAM_Status BAM_sliding_2x2_sum_compute(void *kernelContext)
{
    BAM_sliding_2x2_sum_Context *context = (BAM_sliding_2x2_sum_Context *) kernelContext;
    BAM_Status status = 0;
#if (VCOP_HOST_EMULATION)
    if(context->kernelArgs.sun2x2outFormat == EVE_VLIB_SLIDING_2x2_SUM_DEINTERLEAVED)
    {
      vcop_ti_pd_2x2_sum((uint16_t*)context->pInBlock[IN_IDX],
                              (uint16_t*)context->pOutBlock[OUT_IDX1],
                              (uint16_t*)context->pOutBlock[OUT_IDX2],
                                context->kernelArgs.blockWidth,
                                context->kernelArgs.blockHeight,
                                context->kernelArgs.blockStride);
    }
    else if(context->kernelArgs.sun2x2outFormat == EVE_VLIB_SLIDING_2x2_SUM_PLANAR)
    {
      vcop_ti_pd_2x2_sum_planar((uint16_t*)context->pInBlock[IN_IDX],
                                (uint16_t*)context->pOutBlock[OUT_IDX1],
                                context->kernelArgs.blockWidth,
                                context->kernelArgs.blockHeight,
                                context->kernelArgs.blockStride);
    }
#else
    context->kernelCustom((uint16_t*)context->pInternalBlock[PARAMS_IDX]);
#endif
    return status;

}

BAM_KernelExecFuncDef gBAM_TI_sliding2x2SumExecFunc =
{ NULL, &Bam_sliding_2x2_sum_initFrame, &BAM_sliding_2x2_sum_compute, NULL, NULL, NULL};
