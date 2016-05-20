/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_multipoint_harrisScore_u16_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating multi-point
 *              16-bit Harris score kernel into BAM.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_multipoint_harrisScore_u16_int.h"
#include "vcop_multipoint_harrisScore_u16_kernel.h" /* compiler should take care of include path */

/* Function Prototypes */
static BAM_Status Bam_Multipoint_Harris_Score_initInstance(void *kernelContext);
static BAM_Status Bam_Multipoint_Harris_Score_initFrame(void *kernelContext);


static BAM_Status Bam_Multipoint_Harris_Score_initInstance(void *kernelContext)
{
  BAM_Multipoint_Harris_Score_Context *context = (BAM_Multipoint_Harris_Score_Context *) kernelContext;
  /* Take back up of output pointer as it gets incremented by kernel and we need to reset across ivision process */
  context->pOutBlockBase_OUT_IDX = context->pOutBlock[OUT_IDX];
  return 0;
}


static BAM_Status Bam_Multipoint_Harris_Score_initFrame(void *kernelContext)
{
  uint16_t i;
  BAM_Multipoint_Harris_Score_Args *args;
  BAM_Multipoint_Harris_Score_InArgs *inArgs;
  BAM_Multipoint_Harris_Score_Context *context = (BAM_Multipoint_Harris_Score_Context *) kernelContext;
  uint32_t (*pInArgsIdx)[];

  args = (BAM_Multipoint_Harris_Score_Args *)&(context->kernelArgs);
  pInArgsIdx = (uint32_t (*)[])context->pInBlock[IN_ARGS_IDX];
  /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
  /* Function pointers converted to uint32_t */
  inArgs = (BAM_Multipoint_Harris_Score_InArgs *)((*pInArgsIdx)[0]);
  /* RESET_MISRA("11.3")  -> Reset rule 11.3  */

  /* It assumes that max 2K (11 bits) points per level */
  context->kernelArgs.start_idx = ((uint16_t)inArgs->level << 11U);

  if(inArgs->firstTimeFlag)
  {
    context->pOutBlock[OUT_IDX] = context->pOutBlockBase_OUT_IDX ;
  }

  /* CHECK_MISRA("-17.1,17.4")  -> Disable rule 17.1,17.4  */
  /* Pointer arithmetic is needed here to update the output pointer */
  /* The harmful side effect of voilating this rule (accessing outside valid memory) */
  /* shall be checked by another code checker like Klocwork */
  for(i = 0U; i < 8U; i++) {
    *((uint16_t *)(context->pInternalBlock[SEQ_ARRAY_IDX]) + i) = i;
  }
  /* RESET_MISRA("17.1,17.4")  -> Reset rule 17.1,17.4  */

#if (!VCOP_HOST_EMULATION)

  int32_t  *vertSumX2_B, *vertSumY2_C, *vertSumXY_B, *Ixx_A, *Iyy_C, *Ixy_A;
  int32_t  *detL_B;
  int32_t  *detH_B;
  uint32_t offset;

  offset = (((7U*36U*ALIGN_2SIMD(args->numPoints))/8U) + 32U)/sizeof(uint32_t);
  vertSumX2_B = (int32_t *)context->pInternalBlock[SCRATCH_B];
  vertSumY2_C = (int32_t *)context->pInternalBlock[SCRATCH_C];

  /* CHECK_MISRA("-17.1,17.4")  -> Disable rule 17.1,17.4  */
  /* Pointer arithmetic is needed here to update the output pointer */
  /* The harmful side effect of voilating this rule (accessing outside valid memory) */
  /* shall be checked by another code checker like Klocwork */
  vertSumXY_B = vertSumX2_B + offset;
  Ixx_A  = (int32_t *)context->pInternalBlock[SCRATCH_A];
  Iyy_C  = vertSumY2_C + offset;
  Ixy_A  = Ixx_A + ALIGN_2SIMD(args->numPoints);
  detL_B = vertSumXY_B + offset;
  detH_B = detL_B + ALIGN_SIMD(args->numPoints);


  vcop_multipoint_harrisScore_7x7_u16_init((uint8_t*)context->pInBlock[IN_IMG_IDX],
      (uint16_t *)context->pOutBlock[OUT_IDX],
      context->kernelArgs.numPoints,
      context->kernelArgs.inputStride,
      context->kernelArgs.interBlockOffset,
      context->kernelArgs.sensitivityParam,
      context->kernelArgs.start_idx - 8,
      (uint16_t *)context->pInternalBlock[SEQ_ARRAY_IDX],
      vertSumX2_B,
      vertSumY2_C,
      vertSumXY_B,
      Ixx_A,
      Iyy_C,
      Ixy_A,
      (uint16_t *)(void *)Ixx_A,
      (uint16_t *)(void *)Iyy_C,
      (uint16_t *)(void *)Ixy_A,
      (int16_t *)(void *)Ixx_A + 1,
      (int16_t *)(void *)Iyy_C + 1,
      (int16_t *)(void *)Ixy_A + 1,
      (uint32_t *)(void *)detL_B,
      detH_B,
      (int32_t *)context->pInternalBlock[PARAMS_IDX],
      context->pInternalBlock[PARAMS_IDX]);
  /* RESET_MISRA("17.1,17.4")  -> Reset rule 17.1,17.4  */

  context->pOutBlock[OUT_IDX] = (void *)((uint32_t*)context->pOutBlock[OUT_IDX] + inArgs->numTotalPointsInThisLevel);
#else
  {
    static int32_t extraAdvanceInPrevLevel = 0 ;
    if(!inArgs->firstTimeFlag)
    {
      context->pOutBlock[OUT_IDX] = (void *)(((uint32_t *)context->pOutBlock[OUT_IDX]) - extraAdvanceInPrevLevel);
    }

    extraAdvanceInPrevLevel = inArgs->numTotalPointsInThisLevel % context->kernelArgs.numPoints;
    if(extraAdvanceInPrevLevel)
    {
      extraAdvanceInPrevLevel = context->kernelArgs.numPoints - extraAdvanceInPrevLevel;
    }
  }
#endif

  return 0;
}

#if VCOP_HOST_EMULATION
static BAM_Status Bam_Multipoint_Harris_Score_compute(void *kernelContext)
{
  BAM_Multipoint_Harris_Score_Context *context = (BAM_Multipoint_Harris_Score_Context *) kernelContext;
  BAM_Multipoint_Harris_Score_Args *args;
  int32_t  *vertSumX2_B, *vertSumY2_C, *vertSumXY_B, *Ixx_A, *Iyy_C, *Ixy_A;
  uint32_t *detL_B;
  int32_t  *detH_B;

  args = (BAM_Multipoint_Harris_Score_Args *)&(context->kernelArgs);

  vertSumX2_B = (int32_t *)context->pInternalBlock[SCRATCH_B];
  vertSumY2_C = (int32_t *)context->pInternalBlock[SCRATCH_C];
  vertSumXY_B = vertSumX2_B + (7*36*ALIGN_2SIMD(args->numPoints)/8 + 32)/sizeof(int32_t);
  Ixx_A  = (int32_t *)context->pInternalBlock[SCRATCH_A];
  Iyy_C  = vertSumY2_C + (7*36*ALIGN_2SIMD(args->numPoints)/8 + 32)/sizeof(int32_t);
  Ixy_A  = Ixx_A + ALIGN_2SIMD(args->numPoints);
  detL_B = (uint32_t *)vertSumXY_B + (7*36*ALIGN_2SIMD(args->numPoints)/8 + 32)/sizeof(uint32_t);
  detH_B = (int32_t *)detL_B + ALIGN_SIMD(args->numPoints);

  vcop_multipoint_harrisScore_7x7_u16((uint8_t*)context->pInBlock[IN_IMG_IDX],
      (uint16_t *)context->pOutBlock[OUT_IDX],
      context->kernelArgs.numPoints,
      context->kernelArgs.inputStride,
      context->kernelArgs.interBlockOffset,
      context->kernelArgs.sensitivityParam,
      context->kernelArgs.start_idx - 8,
      (uint16_t *)context->pInternalBlock[SEQ_ARRAY_IDX],
      vertSumX2_B,
      vertSumY2_C,
      vertSumXY_B,
      Ixx_A,
      Iyy_C,
      Ixy_A,
      (uint16_t *)Ixx_A,
      (uint16_t *)Iyy_C,
      (uint16_t *)Ixy_A,
      (int16_t *)Ixx_A + 1,
      (int16_t *)Iyy_C + 1,
      (int16_t *)Ixy_A + 1,
      detL_B,
      detH_B,
      (int32_t *)context->pInternalBlock[PARAMS_IDX]);

  context->kernelArgs.start_idx += context->kernelArgs.numPoints;
  context->pOutBlock[OUT_IDX] = ((uint16_t *)context->pOutBlock[OUT_IDX]) + 2*context->kernelArgs.numPoints;

  return 0;
}
#endif


BAM_KernelExecFuncDef gBAM_TI_multipointHarrisScoreExecFunc =
#if (!VCOP_HOST_EMULATION)
    {&Bam_Multipoint_Harris_Score_initInstance, &Bam_Multipoint_Harris_Score_initFrame, NULL, NULL, NULL, &vcop_multipoint_harrisScore_7x7_u16_vloops};
#else
    {&Bam_Multipoint_Harris_Score_initInstance, &Bam_Multipoint_Harris_Score_initFrame, Bam_Multipoint_Harris_Score_compute, NULL, NULL, NULL};
#endif

