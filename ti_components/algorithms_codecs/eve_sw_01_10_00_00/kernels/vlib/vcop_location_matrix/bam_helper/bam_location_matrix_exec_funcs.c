/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
* @file bam_location_matrix_exec_funcs.c
*
* @brief
*
* @version 0.0 (Jan 2014) : Base version.
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_location_matrix_helper_funcs.h"
#include "vcop_location_matrix_kernel.h"
#define MAX_NUM_BINS (32)
BAM_Status BAM_location_matrix_computeFrame
(
    void *kernelContext
);
BAM_Status BAM_location_matrix_initFrame
(
    void *kernelContext
);
/**
*******************************************************************************
* @fn        BAM_location_matrix_initFrame
* @brief    Function for Vloop init
*
* @inputs -  kernelContext :
*
* @return   none
* @param Comments:
*******************************************************************************
*/
BAM_Status BAM_location_matrix_initFrame
(
    void *kernelContext
)
{
    BAM_location_matrix_Context *context = (BAM_location_matrix_Context*)kernelContext;
    uint8_t (*binIdx)[MAX_NUM_BINS] = (uint8_t (*)[MAX_NUM_BINS])(void*)context->pInternalBlock[LOCATION_MATRIX_INTERNAL_BIN_IDX];
    uint8_t i;
    uint8_t numBinsBy2 = (uint8_t)((context->kernelArgs.numBins+(uint8_t)1)/(uint8_t)2);
    if(context->kernelArgs.gradientMagSize <= 2)
    {

    for(i =0; i < numBinsBy2; i++)
    {
      (*binIdx)[i*2U]   = i;
      (*binIdx)[(i*2U)+1U] = numBinsBy2 + i;
    }

#if (!VCOP_HOST_EMULATION)
    if(context->kernelArgs.gradientMagSize == 1)
    {
      vcop_vec_L_matrix_u8_Mag_init(
              (uint8_t*)context->pInBlock[LOCATION_MATRIX_IN_BLK1_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
              (uint8_t*)context->pInBlock[LOCATION_MATRIX_IN_BLK2_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
              (uint8_t*)context->pOutBlock[LOCATION_MATRIX_OUT_MATRIX1_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
              (uint8_t*)context->pOutBlock[LOCATION_MATRIX_OUT_MATRIX2_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
              (uint32_t*)context->pOutBlock[LOCATION_MATRIX_OUT_MATRIX1_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
              (uint32_t*)context->pOutBlock[LOCATION_MATRIX_OUT_MATRIX2_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
              context->kernelArgs.blockW,
              context->kernelArgs.blockH,
              context->kernelArgs.numBins,
              (uint8_t*)context->pInternalBlock[LOCATION_MATRIX_INTERNAL_BIN_IDX],
              context->pInternalBlock[LOCATION_MATRIX_INTERNAL_PARAMS_IDX]
             );
      context->kernelCustom = &vcop_vec_L_matrix_u8_Mag_vloops;
    }
    else
    {
      vcop_vec_L_matrix_u16_Mag_init(
              (uint8_t*)context->pInBlock[LOCATION_MATRIX_IN_BLK1_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
              (uint16_t*)context->pInBlock[LOCATION_MATRIX_IN_BLK2_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
              (uint16_t*)context->pOutBlock[LOCATION_MATRIX_OUT_MATRIX1_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
              (uint16_t*)context->pOutBlock[LOCATION_MATRIX_OUT_MATRIX2_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
              (uint32_t*)context->pOutBlock[LOCATION_MATRIX_OUT_MATRIX1_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
              (uint32_t*)context->pOutBlock[LOCATION_MATRIX_OUT_MATRIX2_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
              context->kernelArgs.blockW,
              context->kernelArgs.blockH,
              context->kernelArgs.numBins,
              (uint8_t*)context->pInternalBlock[LOCATION_MATRIX_INTERNAL_BIN_IDX],
              context->pInternalBlock[LOCATION_MATRIX_INTERNAL_PARAMS_IDX]
             );
      context->kernelCustom = &vcop_vec_L_matrix_u16_Mag_vloops;
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
BAM_Status BAM_location_matrix_computeFrame
(
    void *kernelContext
)
{
    BAM_location_matrix_Context *context = (BAM_location_matrix_Context *)kernelContext;

#if (VCOP_HOST_EMULATION)
    if(context->kernelArgs.gradientMagSize == 1)
    {
     vcop_vec_L_matrix_u8_Mag(
            (uint8_t*)context->pInBlock[LOCATION_MATRIX_IN_BLK1_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
            (uint8_t*)context->pInBlock[LOCATION_MATRIX_IN_BLK2_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
            (uint8_t*)context->pOutBlock[LOCATION_MATRIX_OUT_MATRIX1_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
            (uint8_t*)context->pOutBlock[LOCATION_MATRIX_OUT_MATRIX2_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
            (uint32_t*)context->pOutBlock[LOCATION_MATRIX_OUT_MATRIX1_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
            (uint32_t*)context->pOutBlock[LOCATION_MATRIX_OUT_MATRIX2_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
            context->kernelArgs.blockW,
            context->kernelArgs.blockH,
            context->kernelArgs.numBins,
            (uint8_t*)context->pInternalBlock[LOCATION_MATRIX_INTERNAL_BIN_IDX]);
     }
     else
     {
     vcop_vec_L_matrix_u16_Mag(
            (uint8_t*)context->pInBlock[LOCATION_MATRIX_IN_BLK1_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
            (uint16_t*)context->pInBlock[LOCATION_MATRIX_IN_BLK2_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
            (uint16_t*)context->pOutBlock[LOCATION_MATRIX_OUT_MATRIX1_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
            (uint16_t*)context->pOutBlock[LOCATION_MATRIX_OUT_MATRIX2_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
            (uint32_t*)context->pOutBlock[LOCATION_MATRIX_OUT_MATRIX1_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
            (uint32_t*)context->pOutBlock[LOCATION_MATRIX_OUT_MATRIX2_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
            context->kernelArgs.blockW,
            context->kernelArgs.blockH,
            context->kernelArgs.numBins,
            (uint8_t*)context->pInternalBlock[LOCATION_MATRIX_INTERNAL_BIN_IDX]);
     }
#else
    context->kernelCustom(context->pInternalBlock[LOCATION_MATRIX_INTERNAL_PARAMS_IDX]);
#endif

    return 0;
}


BAM_KernelExecFuncDef gBAM_TI_location_matrixExecFunc =
{
    NULL,    /* kernelInitInstance   */
    &BAM_location_matrix_initFrame,                                      /* kernelInitFrame      */
    &BAM_location_matrix_computeFrame, /* kernelCompute        */
    NULL,                                      /* kernelWait           */
    NULL,                                      /* kernelCtl            */
    NULL                                       /* Custom               */
};

