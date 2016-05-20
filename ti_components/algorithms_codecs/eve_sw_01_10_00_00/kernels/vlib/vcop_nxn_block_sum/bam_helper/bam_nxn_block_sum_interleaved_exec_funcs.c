/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
* @file bam_nxn_block_sum_interleaved_exec_funcs.c
*
* @brief
*
* @version 0.0 (Jan 2014) : Base version.
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_nxn_block_sum_interleaved_helper_funcs.h"
#include "vcop_nxn_block_sum_kernel.h"
BAM_Status BAM_nxn_block_sum_interleaved_computeFrame
(
    void *kernelContext
);
BAM_Status BAM_nxn_block_sum_interleaved_initFrame
(
    void *kernelContext
);
/**
*******************************************************************************
* @fn        BAM_nxn_block_sum_interleaved_initFrame
* @brief    Function for Vloop init
*
* @inputs -  kernelContext :
*
* @return   none
* @param Comments:
*******************************************************************************
*/
BAM_Status BAM_nxn_block_sum_interleaved_initFrame
(
    void *kernelContext
)
{
    BAM_nxn_block_sum_interleaved_Context *context = (BAM_nxn_block_sum_interleaved_Context*)kernelContext;

#if (!VCOP_HOST_EMULATION)
    vcop_nxn_sum_interleaved_init(
                  (uint8_t *)context->pInBlock[NXN_BLOCK_SUM_INTERLEAVED_IN_PTR_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
                  (uint16_t *)context->pOutBlock[NXN_BLOCK_SUM_INTERLEAVED_OUT_PTR1_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
                  (uint16_t *)context->pOutBlock[NXN_BLOCK_SUM_INTERLEAVED_OUT_PTR2_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
                  (uint32_t *)context->pInternalBlock[NXN_BLOCK_SUM_INTERLEAVED_INTERNAL_TEMP_PTR1_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
                  (uint32_t *)context->pInternalBlock[NXN_BLOCK_SUM_INTERLEAVED_INTERNAL_TEMP_PTR2_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
                  context->kernelArgs.nValue,
                  context->kernelArgs.blockW,
                  context->kernelArgs.blockH,
                  context->kernelArgs.pitch,
                  context->kernelArgs.shiftValue,
                  (uint16_t *)context->pInternalBlock[NXN_BLOCK_SUM_INTERLEAVED_INTERNAL_PARAMS_IDX]
                 );
#endif

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
#if (VCOP_HOST_EMULATION)
BAM_Status BAM_nxn_block_sum_interleaved_computeFrame
(
    void *kernelContext
)
{
    BAM_nxn_block_sum_interleaved_Context *context = (BAM_nxn_block_sum_interleaved_Context *)kernelContext;

#if (VCOP_HOST_EMULATION)
    vcop_nxn_sum_interleaved(
                  (uint8_t *)context->pInBlock[NXN_BLOCK_SUM_INTERLEAVED_IN_PTR_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
                  (uint16_t *)context->pOutBlock[NXN_BLOCK_SUM_INTERLEAVED_OUT_PTR1_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
                  (uint16_t *)context->pOutBlock[NXN_BLOCK_SUM_INTERLEAVED_OUT_PTR2_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
                  (uint32_t *)context->pInternalBlock[NXN_BLOCK_SUM_INTERLEAVED_INTERNAL_TEMP_PTR1_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
                  (uint32_t *)context->pInternalBlock[NXN_BLOCK_SUM_INTERLEAVED_INTERNAL_TEMP_PTR2_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
                  context->kernelArgs.nValue,
                  context->kernelArgs.blockW,
                  context->kernelArgs.blockH,
                  context->kernelArgs.pitch,
                  context->kernelArgs.shiftValue
                 );
#else
    vcop_nxn_sum_interleaved_vloops(context->pInternalBlock[NXN_BLOCK_SUM_INTERLEAVED_INTERNAL_PARAMS_IDX]);
#endif

    return 0;
}
#endif

BAM_KernelExecFuncDef gBAM_TI_nxn_block_sum_interleavedExecFunc =
#if (!VCOP_HOST_EMULATION)
{
    NULL,    /* kernelInitInstance   */
    &BAM_nxn_block_sum_interleaved_initFrame,                                      /* kernelInitFrame      */
    NULL, /* kernelCompute        */
    NULL,                                      /* kernelWait           */
    NULL,                                      /* kernelCtl            */
    &vcop_nxn_sum_interleaved_vloops /* Custom               */
};
#else
{
    NULL,    /* kernelInitInstance   */
    &BAM_nxn_block_sum_interleaved_initFrame,                                      /* kernelInitFrame      */
    &BAM_nxn_block_sum_interleaved_computeFrame, /* kernelCompute        */
    NULL,                                      /* kernelWait           */
    NULL,                                      /* kernelCtl            */
    NULL                                       /* Custom               */
};
#endif



