/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_multipoint_harrisScore_u16_helper_funcs.c
 *
 *  @brief      This file defines interfaces for integrating multi-point
 *              16-bit Harris score kernel into BAM
 */

#include <stdio.h>
#include <stdlib.h>

#include "evealgframework.h"
#include "bam_multipoint_harrisScore_u16_int.h"
#include "vcop_multipoint_harrisScore_u16_kernel.h" /* compiler should take care of include path */

/* Function Prototypes */
static BAM_Status BAM_Multipoint_Harris_Score_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks);

static BAM_Status BAM_Multipoint_Harris_Score_setMemRecFunc(const BAM_MemRec *memRecInternal[],
        const BAM_MemRec *memRecInputDataBlock[], const BAM_MemRec *memRecOutputDataBlock[], uint8_t numRecInternal,
        uint8_t numRecInputDataBlock, uint8_t numRecOutputDataBlock, void *kernelContext, const void *kernelArgs);


static BAM_Status BAM_Multipoint_Harris_Score_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks)
{
    const BAM_Multipoint_Harris_Score_Args *args = (const BAM_Multipoint_Harris_Score_Args *) kernelArgs;

#if (!VCOP_HOST_EMULATION)
    internalBlock[PARAMS_IDX].size = 2U*vcop_multipoint_harrisScore_7x7_u16_param_count();
#else
    /* Since the kernel contains param block update, this field should be at-least size
       of actual param block */
    internalBlock[PARAMS_IDX].size = 320U;
#endif

    internalBlock[SEQ_ARRAY_IDX].size = 8U*sizeof(uint16_t);
    internalBlock[SEQ_ARRAY_IDX].attrs.memAttrs = BAM_MEMATTRS_CONST;
    internalBlock[SEQ_ARRAY_IDX].space = BAM_MEMSPACE_WBUF;

    internalBlock[SCRATCH_A].size = 2U*(ALIGN_2SIMD(args->numPoints)*sizeof(int32_t));
    internalBlock[SCRATCH_A].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    internalBlock[SCRATCH_A].space = BAM_MEMSPACE_IBUFLA;

    internalBlock[SCRATCH_B].size = (2U*(((7U*36U*ALIGN_2SIMD(args->numPoints))/8U) + 32U)) +
                                    (2U*(ALIGN_SIMD(args->numPoints)*sizeof(uint32_t)));
    internalBlock[SCRATCH_B].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    internalBlock[SCRATCH_B].space = BAM_MEMSPACE_IBUFHA;

    internalBlock[SCRATCH_C].size = (((7U*36U*ALIGN_2SIMD(args->numPoints))/8U) + 32U) +
                                    (ALIGN_2SIMD(args->numPoints)*sizeof(uint32_t));
    internalBlock[SCRATCH_C].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    internalBlock[SCRATCH_C].space = BAM_MEMSPACE_WBUF;

    outBlock[OUT_IDX].size = 2U*sizeof(uint16_t)*args->totalNumPoints;
    outBlock[OUT_IDX].space = BAM_MEMSPACE_WBUF;

    return BAM_S_SUCCESS;
}


static BAM_Status BAM_Multipoint_Harris_Score_setMemRecFunc(const BAM_MemRec *memRecInternal[],
        const BAM_MemRec *memRecInputDataBlock[], const BAM_MemRec *memRecOutputDataBlock[], uint8_t numRecInternal,
        uint8_t numRecInputDataBlock, uint8_t numRecOutputDataBlock, void *kernelContext, const void *kernelArgs)
{
  uint16_t i;
  const BAM_Multipoint_Harris_Score_Args *args = (const BAM_Multipoint_Harris_Score_Args *) kernelArgs;
  BAM_Multipoint_Harris_Score_Context *context = (BAM_Multipoint_Harris_Score_Context *) kernelContext;

  /* Populate context with buffer details and kernel args */
  for(i = 0; i < numRecInternal; i++) {
      context->pInternalBlock[i] = memRecInternal[i]->base;
  }

  for(i = 0; i < numRecInputDataBlock; i++) {
      context->pInBlock[i] = memRecInputDataBlock[i]->base;
  }

  for(i = 0; i < numRecOutputDataBlock; i++) {
      context->pOutBlock[i] = memRecOutputDataBlock[i]->base;
  }

  memcpy(&(context->kernelArgs), kernelArgs, gBAM_TI_multipointHarrisScoreKernel.kernelArgSize);

  /* Communicate the address of the output buffer via the pointer passed using Kernel Args structure */
  /* CHECK_MISRA("-11.3")  -> Disable rule 11.3  */
  /* Function pointers converted to uint32_t */
  *(args->pOutScoreBuffer) = (uintptr_t)memRecOutputDataBlock[OUT_IDX]->base;
  /* RESET_MISRA("11.3")  -> Reset rule 11.3  */

  return BAM_S_SUCCESS;
}


BAM_KernelInfo gBAM_TI_multipointHarrisScoreKernel =
{
    0,                                      /* kernelId */
    sizeof(BAM_Multipoint_Harris_Score_Context),
    sizeof(BAM_Multipoint_Harris_Score_Args),
    BAM_EVE,                                /* coreType */
    BAM_NODE_COMPUTE,                       /* nodeType */
    NUM_IN_BLOCKS,                          /* 2 */
    NUM_OUT_BLOCKS,                         /* 1 */
    NUM_INTERNAL_BLOCKS                     /* 5 */
};

BAM_KernelHelperFuncDef gBAM_TI_multipointHarrisScoreHelperFunc =
{ &BAM_Multipoint_Harris_Score_getMemRecFunc, &BAM_Multipoint_Harris_Score_setMemRecFunc};

