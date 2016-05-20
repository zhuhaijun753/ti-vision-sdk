/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
* @file bam_nxn_block_sum_exec_funcs.c
*
* @brief
*
* @version 0.0 (Jan 2014) : Base version.
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_nxn_block_sum_helper_funcs.h"
#include "vcop_nxn_block_sum_kernel.h"

BAM_Status BAM_nxn_block_sum_initFrame
(
    void *kernelContext
);
BAM_Status BAM_nxn_block_sum_computeFrame
(
    void *kernelContext
);

/**
*******************************************************************************
* @fn        BAM_nxn_block_sum_initFrame
* @brief    Function for Vloop init
*
* @inputs -  kernelContext :
*
* @return   none
* @param Comments:
*******************************************************************************
*/
BAM_Status BAM_nxn_block_sum_initFrame
(
    void *kernelContext
)
{
    BAM_nxn_block_sum_Context *context = (BAM_nxn_block_sum_Context*)kernelContext;
    if(context->kernelArgs.inputSize < 3)
    {
#if (!VCOP_HOST_EMULATION)
    if(context->kernelArgs.inputSize == 1)
    {
      vcop_nxn_sum_u8_init(
                    (uint8_t *)context->pInBlock[NXN_BLOCK_SUM_IN_PTR1_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
                    (uint8_t *)context->pInBlock[NXN_BLOCK_SUM_IN_PTR2_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
                    (uint16_t *)context->pOutBlock[NXN_BLOCK_SUM_OUT_PTR1_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
                    (uint16_t *)context->pOutBlock[NXN_BLOCK_SUM_OUT_PTR2_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
                    (uint32_t *)context->pInternalBlock[NXN_BLOCK_SUM_INTERNAL_TEMP_PTR1_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
                    (uint32_t *)context->pInternalBlock[NXN_BLOCK_SUM_INTERNAL_TEMP_PTR2_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
                    context->kernelArgs.nValue,
                    context->kernelArgs.blockW,
                    context->kernelArgs.blockH,
                    context->kernelArgs.pitch1,
                    context->kernelArgs.pitch2,
                    (uint16_t *)context->pInternalBlock[NXN_BLOCK_SUM_INTERNAL_PARAMS_IDX]
                   );
      context->kernelCustom = &vcop_nxn_sum_u8_vloops;
    }
    else if(context->kernelArgs.inputSize == 2)
    {
      vcop_nxn_sum_u8_u16_init(
                    (uint8_t *)context->pInBlock[NXN_BLOCK_SUM_IN_PTR1_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
                    (uint16_t *)context->pInBlock[NXN_BLOCK_SUM_IN_PTR2_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
                    (uint16_t *)context->pOutBlock[NXN_BLOCK_SUM_OUT_PTR1_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
                    (uint16_t *)context->pOutBlock[NXN_BLOCK_SUM_OUT_PTR2_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
                    (uint32_t *)context->pInternalBlock[NXN_BLOCK_SUM_INTERNAL_TEMP_PTR1_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
                    (uint32_t *)context->pInternalBlock[NXN_BLOCK_SUM_INTERNAL_TEMP_PTR2_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
                    context->kernelArgs.nValue,
                    context->kernelArgs.blockW,
                    context->kernelArgs.blockH,
                    context->kernelArgs.pitch1,
                    context->kernelArgs.pitch2,
                    (uint16_t *)context->pInternalBlock[NXN_BLOCK_SUM_INTERNAL_PARAMS_IDX]
                   );
      context->kernelCustom = &vcop_nxn_sum_u8_u16_vloops;
    }
    else
    {
      vcop_nxn_sum_u16_init(
                    (uint16_t *)context->pInBlock[NXN_BLOCK_SUM_IN_PTR1_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
                    (uint16_t *)context->pInBlock[NXN_BLOCK_SUM_IN_PTR2_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
                    (uint16_t *)context->pOutBlock[NXN_BLOCK_SUM_OUT_PTR1_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
                    (uint16_t *)context->pOutBlock[NXN_BLOCK_SUM_OUT_PTR2_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
                    (uint32_t *)context->pInternalBlock[NXN_BLOCK_SUM_INTERNAL_TEMP_PTR1_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
                    (uint32_t *)context->pInternalBlock[NXN_BLOCK_SUM_INTERNAL_TEMP_PTR2_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
                    context->kernelArgs.nValue,
                    context->kernelArgs.blockW,
                    context->kernelArgs.blockH,
                    context->kernelArgs.pitch1,
                    context->kernelArgs.pitch2,
                    (uint16_t *)context->pInternalBlock[NXN_BLOCK_SUM_INTERNAL_PARAMS_IDX]
                   );
      context->kernelCustom = &vcop_nxn_sum_u16_vloops;
    }
#endif
    }
    return 0;
}


/**
*******************************************************************************
* @fn       BAM_bop_compute_features_computeFrame
* @brief    Function to call Vloop
*
* @inputs -  kernelContext :
*
* @return   none
* @param Comments:
*******************************************************************************
*/
BAM_Status BAM_nxn_block_sum_computeFrame
(
    void *kernelContext
)
{
    BAM_nxn_block_sum_Context *context = (BAM_nxn_block_sum_Context *)kernelContext;

#if (VCOP_HOST_EMULATION)
    if(context->kernelArgs.inputSize == 1)
    {
      vcop_nxn_sum_u8(
              (uint8_t *)context->pInBlock[NXN_BLOCK_SUM_IN_PTR1_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
              (uint8_t *)context->pInBlock[NXN_BLOCK_SUM_IN_PTR2_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
              (uint16_t *)context->pOutBlock[NXN_BLOCK_SUM_OUT_PTR1_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
              (uint16_t *)context->pOutBlock[NXN_BLOCK_SUM_OUT_PTR2_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
              (uint32_t *)context->pInternalBlock[NXN_BLOCK_SUM_INTERNAL_TEMP_PTR1_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
              (uint32_t *)context->pInternalBlock[NXN_BLOCK_SUM_INTERNAL_TEMP_PTR2_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
              context->kernelArgs.nValue,
              context->kernelArgs.blockW,
              context->kernelArgs.blockH,
              context->kernelArgs.pitch1,
              context->kernelArgs.pitch2
             );
    }
    else if(context->kernelArgs.inputSize == 2)
    {
      vcop_nxn_sum_u8_u16(
              (uint8_t *)context->pInBlock[NXN_BLOCK_SUM_IN_PTR1_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
              (uint8_t *)context->pInBlock[NXN_BLOCK_SUM_IN_PTR2_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
              (uint16_t *)context->pOutBlock[NXN_BLOCK_SUM_OUT_PTR1_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
              (uint16_t *)context->pOutBlock[NXN_BLOCK_SUM_OUT_PTR2_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
              (uint32_t *)context->pInternalBlock[NXN_BLOCK_SUM_INTERNAL_TEMP_PTR1_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
              (uint32_t *)context->pInternalBlock[NXN_BLOCK_SUM_INTERNAL_TEMP_PTR2_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
              context->kernelArgs.nValue,
              context->kernelArgs.blockW,
              context->kernelArgs.blockH,
              context->kernelArgs.pitch1,
              context->kernelArgs.pitch2
             );
    }
    else
    {
    vcop_nxn_sum_u16(
            (uint16_t *)context->pInBlock[NXN_BLOCK_SUM_IN_PTR1_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
            (uint16_t *)context->pInBlock[NXN_BLOCK_SUM_IN_PTR2_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
            (uint16_t *)context->pOutBlock[NXN_BLOCK_SUM_OUT_PTR1_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
            (uint16_t *)context->pOutBlock[NXN_BLOCK_SUM_OUT_PTR2_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
            (uint32_t *)context->pInternalBlock[NXN_BLOCK_SUM_INTERNAL_TEMP_PTR1_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
            (uint32_t *)context->pInternalBlock[NXN_BLOCK_SUM_INTERNAL_TEMP_PTR2_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
            context->kernelArgs.nValue,
            context->kernelArgs.blockW,
            context->kernelArgs.blockH,
            context->kernelArgs.pitch1,
            context->kernelArgs.pitch2
           );
    }

#else
    context->kernelCustom(context->pInternalBlock[NXN_BLOCK_SUM_INTERNAL_PARAMS_IDX]);
#endif

    return 0;
}

BAM_KernelExecFuncDef gBAM_TI_nxn_block_sumExecFunc =
{
    NULL,    /* kernelInitInstance   */
    &BAM_nxn_block_sum_initFrame,                                      /* kernelInitFrame      */
    &BAM_nxn_block_sum_computeFrame, /* kernelCompute        */
    NULL,                                      /* kernelWait           */
    NULL,                                      /* kernelCtl            */
    NULL                                       /* Custom               */
};



