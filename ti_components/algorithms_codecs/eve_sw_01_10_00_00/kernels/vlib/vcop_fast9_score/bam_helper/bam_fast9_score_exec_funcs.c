/*==========================================================================*/
/*      Copyright (C) 2009-2014 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_fast9_score_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating fast9 score
 *              function into BAM.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_fast9_score_int.h"
#include "bam_fast9_score.h"
#include "vcop_fast9_score_kernel.h" /* compiler should take care of include path */
#include "edma_utils_memcpy.h"

/* Function Prototypes */

static BAM_Status Bam_Fast9_Score_initInstance(void *kernelContext);
static BAM_Status Bam_Fast9_Score_initFrame(void *kernelContext);
static BAM_Status Bam_Fast9_Score_compute(void *kernelContext);

static BAM_Status Bam_Fast9_Score_initInstance(void *kernelContext)
{
  BAM_Fast9_Score_Context *context = (BAM_Fast9_Score_Context *) kernelContext;
  /* Take back up of output pointer as it gets incremented by kernel and we need to reset across ivision process */
  context->pOutBlockBase_OUT_SCORE_IDX = context->pOutBlock[OUT_SCORE_IDX];
  return 0;
}

static BAM_Status Bam_Fast9_Score_initFrame(void *kernelContext)
{
    BAM_Fast9_Score_Context *context = (BAM_Fast9_Score_Context *) kernelContext;
    BAM_Status status = 0;
    SCORE_INTERNAL_MEMORY_IBUFHA * internalIbufha = (SCORE_INTERNAL_MEMORY_IBUFHA *)context->pInternalBlock[SCORE_INTERNAL_IBUFHA_IDX];
    
if (context->kernelArgs.score_method)
    {
        EDMA_UTILS_memcpy2D(context->pInternalBlock[LUT_IDX],
                            (void *)LUT_EXT_IDX_SAD,
                            sizeof(LUT_EXT_IDX_SAD),
                            1U,
                            0,
                            0);
    }
else
    {
        EDMA_UTILS_memcpy2D(context->pInternalBlock[LUT_IDX],
                            (void *)LUT_EXT_IDX_THR,
                            sizeof(LUT_EXT_IDX_THR),
                            1U,
                            0,
                            0);
    }
    /* Since the kernel is updating the pointer during execute - need to reset at Frame Init */
    context->pOutBlock[OUT_SCORE_IDX] = context->pOutBlockBase_OUT_SCORE_IDX ;


#if (!VCOP_HOST_EMULATION)
if(context->kernelArgs.score_method)
    {
        vcop_fast9_score_kernel_init((uint32_t*)context->pInBlock[IN_IDX],
                              (uint32_t*)context->pInternalBlock[PTEMP_BUF_IDX],
                              (uint32_t*)context->pInternalBlock[PTEMP_IDX],
                              (uint8_t*)context->pInternalBlock[PTEMP_IDX],
                              context->kernelArgs.num_features,
                              context->kernelArgs.thr,
                              (uint8_t*)context->pInternalBlock[LUT_IDX],
                              (uint8_t*)internalIbufha->offset_out,
                              (uint16_t*)context->pInternalBlock[SCORE_B_IDX],
                              (uint16_t*)context->pInternalBlock[SCORE_D_IDX],
                              (uint16_t*)context->pOutBlock[OUT_SCORE_IDX],
                              (uint32_t*)context->pInternalBlock[PARAMS_IDX],
                              (uint16_t*)context->pInternalBlock[PARAMS_IDX]);
    }
else
    {
        vcop_fast9_thresh_score_init((uint32_t*)context->pInBlock[IN_IDX],
                                    (uint32_t*)context->pInternalBlock[PTEMP_BUF_IDX],
                                    (uint32_t*)context->pInternalBlock[PTEMP_IDX],
                                    (uint8_t*)context->pInternalBlock[PTEMP_IDX],
                                    context->kernelArgs.num_features,
                                    context->kernelArgs.thr,
                                    (uint8_t*)context->pInternalBlock[LUT_IDX],
                                    (uint8_t*)internalIbufha->offset_out,
                                    (uint8_t*)context->pInternalBlock[BSCORE_IDX],
                                    (uint8_t*)internalIbufha->Dscore,
                                    (uint16_t*)context->pInternalBlock[SCORE_B_IDX],
                                    (uint16_t*)context->pInternalBlock[SCORE_D_IDX],
                                    (uint16_t*)context->pOutBlock[OUT_SCORE_IDX],
                                    (uint32_t*)context->pInternalBlock[PARAMS_IDX],
                                    (uint16_t*)context->pInternalBlock[PARAMS_IDX]);
    }
#endif

    return status;
}

static BAM_Status Bam_Fast9_Score_compute(void *kernelContext)
{
    BAM_Fast9_Score_Context *context = (BAM_Fast9_Score_Context *) kernelContext;
    BAM_Status status = 0;
    
#if (VCOP_HOST_EMULATION)
    uint16_t *pUpdate;
    SCORE_INTERNAL_MEMORY_IBUFHA * internalIbufha = (SCORE_INTERNAL_MEMORY_IBUFHA *)context->pInternalBlock[SCORE_INTERNAL_IBUFHA_IDX];

if(context->kernelArgs.score_method)
    {
        vcop_fast9_score_kernel((uint32_t*)context->pInBlock[IN_IDX],
                              (uint32_t*)context->pInternalBlock[PTEMP_BUF_IDX],
                              (uint32_t*)context->pInternalBlock[PTEMP_IDX],
                              (uint8_t*)context->pInternalBlock[PTEMP_IDX],
                              context->kernelArgs.num_features,
                              context->kernelArgs.thr,
                              (uint8_t*)context->pInternalBlock[LUT_IDX],
                              (uint8_t*)internalIbufha->offset_out,
                              (uint16_t*)context->pInternalBlock[SCORE_B_IDX],
                              (uint16_t*)context->pInternalBlock[SCORE_D_IDX],
                              (uint16_t*)context->pOutBlock[OUT_SCORE_IDX],
                              NULL);

         pUpdate = (uint16_t *)(context->pOutBlock[OUT_SCORE_IDX])+((context->kernelArgs.num_features));

         context->pOutBlock[OUT_SCORE_IDX] = pUpdate;
    }
else
    {
         vcop_fast9_thresh_score((uint32_t*)context->pInBlock[IN_IDX],
                                 (uint32_t*)context->pInternalBlock[PTEMP_BUF_IDX],
                                 (uint32_t*)context->pInternalBlock[PTEMP_IDX],
                                 (uint8_t*)context->pInternalBlock[PTEMP_IDX],
                                 context->kernelArgs.num_features,
                                 context->kernelArgs.thr,
                                 (uint8_t*)context->pInternalBlock[LUT_IDX],
                                 (uint8_t*)internalIbufha->offset_out,
                                 (uint8_t*)context->pInternalBlock[BSCORE_IDX],
                                 (uint8_t*)internalIbufha->Dscore,
                                 (uint16_t*)context->pInternalBlock[SCORE_B_IDX],
                                 (uint16_t*)context->pInternalBlock[SCORE_D_IDX],
                                 (uint16_t*)context->pOutBlock[OUT_SCORE_IDX],
                                 NULL);

         pUpdate = (uint16_t *)(context->pOutBlock[OUT_SCORE_IDX])+((context->kernelArgs.num_features));

         context->pOutBlock[OUT_SCORE_IDX] = pUpdate;
    }
#else
    if(context->kernelArgs.score_method) {
        vcop_fast9_score_kernel_vloops(context->pInternalBlock[PARAMS_IDX]);
    } 
    else {
        vcop_fast9_thresh_score_vloops(context->pInternalBlock[PARAMS_IDX]);
    }
#endif
    return status;
}

BAM_KernelExecFuncDef gBAM_TI_fast9scoreExecFunc =
    { &Bam_Fast9_Score_initInstance, &Bam_Fast9_Score_initFrame, &Bam_Fast9_Score_compute, NULL, NULL, NULL };

