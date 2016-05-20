/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
* @file bam_orientation_binning_exec_funcs.c
*
* @brief
*
* @author Anshu Jain(anshu.jain@ti.com)
*
* @version 0.0 (Aug 2013) : Base version.
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>
#include <math.h>

#include "bam_orientation_binning_helper_funcs.h"
#include "vcop_orientation_binning_kernel.h"

typedef float   float32_t;
typedef double  double64_t;


#define TB_PI       ((float32_t)3.14159265358979323846)
#define MAX_NUM_BINS (32)
BAM_Status BAM_orientation_binning_initInstance
(
    void *kernelContext
);
BAM_Status BAM_orientation_binning_initFrame
(
    void *kernelContext
);
BAM_Status BAM_orientation_binning_computeFrame
(
    void *kernelContext
);
/**
*******************************************************************************
* @fn        BAM_orientation_binning_initInstance
* @brief    Function for Sequnce level Initialization
*
* @inputs -  kernelContext :
*
* @return   none
* @param Comments:
*******************************************************************************
*/

BAM_Status BAM_orientation_binning_initInstance
(
    void *kernelContext
)
{
    BAM_orientation_binning_Context *context = (BAM_orientation_binning_Context*)kernelContext;
    int16_t (*sinTabPtr)[MAX_NUM_BINS];
    int16_t (*cosTabPtr)[MAX_NUM_BINS];
    int16_t i;
    uint32_t totalNumBins = (context->kernelArgs.numBins*2U);
    float32_t startAngle = (float32_t)(TB_PI/(float32_t)totalNumBins);
    double64_t value;
    double64_t sinValue;
    double64_t cosValue;
    sinTabPtr = (int16_t (*)[MAX_NUM_BINS])(void *)context->pInternalBlock[ORIENTATION_BINNING_INTERNAL_SIN_TAB_IDX];
    cosTabPtr = (int16_t (*)[MAX_NUM_BINS])(void *)context->pInternalBlock[ORIENTATION_BINNING_INTERNAL_COS_TAB_IDX];




  for(i = 0; i < context->kernelArgs.numBins; i++)
  {
    value = sin(((float32_t)i*(TB_PI/((float32_t)context->kernelArgs.numBins))) + startAngle);
    sinValue = (double64_t)((double64_t)value * (double64_t)((uint32_t)1 << 15));
    (*sinTabPtr)[i] = (int16_t)sinValue;
    value = cos(((float32_t)i*(TB_PI/((float32_t)context->kernelArgs.numBins))) + startAngle);
    cosValue = (double64_t)((double64_t)value * (double64_t)((uint32_t)1 << 15));
    (*cosTabPtr)[i] = (int16_t)cosValue;
  }
  return 0;
}


/**
*******************************************************************************
* @fn        BAM_orientation_binning_initFrame
* @brief    Function for Vloop init
*
* @inputs -  kernelContext :
*
* @return   none
* @param Comments:
*******************************************************************************
*/

BAM_Status BAM_orientation_binning_initFrame
(
    void *kernelContext
)
{
    BAM_orientation_binning_Context *context = (BAM_orientation_binning_Context*)kernelContext;
#if (!VCOP_HOST_EMULATION)
    if(context->kernelArgs.numBins & 1U)
    {
      vcop_orientation_binning_init(
                            (int16_t*)context->pInBlock[ORIENTATION_BINNING_IN_GRADX_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
                            (int16_t*)context->pInBlock[ORIENTATION_BINNING_IN_GRADY_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
                            (uint8_t*)context->pOutBlock[ORIENTATION_BINNING_OUT_BIN_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
                            (int16_t*)context->pInternalBlock[ORIENTATION_BINNING_INTERNAL_SIN_TAB_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
                            (int16_t*)context->pInternalBlock[ORIENTATION_BINNING_INTERNAL_COS_TAB_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
                            context->kernelArgs.numBins,
                            context->kernelArgs.blockW,
                            context->kernelArgs.blockH,
                            context->kernelArgs.pitch,
                            (uint16_t*)context->pInternalBlock[ORIENTATION_BINNING_INTERNAL_PARAMS_IDX]
                           );
      context->kernelCustom = &vcop_orientation_binning_vloops;
    }
    else
    {
      vcop_orientation_binning_even_init(
                            (int16_t*)context->pInBlock[ORIENTATION_BINNING_IN_GRADX_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
                            (int16_t*)context->pInBlock[ORIENTATION_BINNING_IN_GRADY_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
                            (uint8_t*)context->pInternalBlock[ORIENTATION_BINNING_INTERNAL_ABS_GRADX_IDX],
                            (uint8_t*)context->pInternalBlock[ORIENTATION_BINNING_INTERNAL_ABS_GRADY_IDX],
                            (uint8_t*)context->pOutBlock[ORIENTATION_BINNING_OUT_BIN_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
                            (int16_t*)context->pInternalBlock[ORIENTATION_BINNING_INTERNAL_SIN_TAB_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
                            (int16_t*)context->pInternalBlock[ORIENTATION_BINNING_INTERNAL_COS_TAB_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
                            context->kernelArgs.numBins,
                            context->kernelArgs.blockW,
                            context->kernelArgs.blockH,
                            context->kernelArgs.pitch,
                            (uint16_t*)context->pInternalBlock[ORIENTATION_BINNING_INTERNAL_PARAMS_IDX]
                           );

      context->kernelCustom = &vcop_orientation_binning_even_vloops;
    }
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
BAM_Status BAM_orientation_binning_computeFrame
(
    void *kernelContext
)
{
    BAM_orientation_binning_Context *context = (BAM_orientation_binning_Context *)kernelContext;

#if (VCOP_HOST_EMULATION)
    vcop_orientation_binning(
            (int16_t*)context->pInBlock[ORIENTATION_BINNING_IN_GRADX_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
            (int16_t*)context->pInBlock[ORIENTATION_BINNING_IN_GRADY_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
            (uint8_t*)context->pOutBlock[ORIENTATION_BINNING_OUT_BIN_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
            (int16_t*)context->pInternalBlock[ORIENTATION_BINNING_INTERNAL_SIN_TAB_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
            (int16_t*)context->pInternalBlock[ORIENTATION_BINNING_INTERNAL_COS_TAB_IDX],/*Input Integral Image block: expected to come from DMA SOURCE NODE */
            context->kernelArgs.numBins,
            context->kernelArgs.blockW,
            context->kernelArgs.blockH,
            context->kernelArgs.pitch
           );
#else
      context->kernelCustom(context->pInternalBlock[ORIENTATION_BINNING_INTERNAL_PARAMS_IDX]);
#endif

 return 0;
}

BAM_KernelExecFuncDef gBAM_TI_orientation_binningExecFunc =
{
    &BAM_orientation_binning_initInstance,    /* kernelInitInstance   */
    &BAM_orientation_binning_initFrame,                                      /* kernelInitFrame      */
    &BAM_orientation_binning_computeFrame, /* kernelCompute        */
    NULL,                                      /* kernelWait           */
    NULL,                                      /* kernelCtl            */
    NULL                                       /* Custom               */
};


