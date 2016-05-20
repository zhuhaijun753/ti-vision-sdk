/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 ********************************************************************************
 * @file:      bam_image_filter_helper_funcs.c
 *
 * @brief:   This file defines functions for integrating filter kernels into BAM
 *
 * @author: Gajanan Ambi(gajanan.ambi@ti.com)
 *
 * @version 0.0 (Feb 2013) : Base version.
 ********************************************************************************
 */

#include <stdio.h>
#include <stdlib.h>

#include "evealgframework.h"
#include "bam_image_filter_helper_funcs.h"
#include "bam_image_filter.h" /*makerules should take care of include path*/
#include "vcop_filter_kernel.h"

/* Function Prototypes */
static BAM_Status BAM_Image_filter_getMemRecFunc
(
  const void *kernelArgs,
  BAM_MemRec *internalBlock,
  BAM_MemRec *outBlock,
  uint8_t    *numInternalBlocks,
  uint8_t    *numOutBlocks
);

#if 0
static BAM_Status BAM_Image_filter_setMemRecFunc
(
  const BAM_MemRec *internalBlock[],
  const BAM_MemRec *inBlock[],
  const BAM_MemRec *outBlock[],
  uint8_t           numInternalBlocks,
  uint8_t           numInBlocks,
  uint8_t           numOutBlocks,
  void             *kernelContext,
  void             *kernelArgs
);
#endif
/**
 *******************************************************************************
 * @fn        BAM_Image_filter_GetMemRecFunc
 * @brief     Function to allocate memory for filter .
 *
 * @inputs -  kernelArgs :
 * @inputs -  kernelContext :
 * @inputs -  internalBlock :
 * @inputs -  outBlock :
 * @inputs -  numInternalBlocks :
 * @inputs -  numOutBlocks :
 *
 * @return   none
 * @param Comments:
 *******************************************************************************
 */
static BAM_Status BAM_Image_filter_getMemRecFunc
(
    const void *kernelArgs,
    BAM_MemRec *internalBlock,
    BAM_MemRec *outBlock,
    uint8_t    *numInternalBlocks,
    uint8_t    *numOutBlocks
)
{
    BAM_Image_filter_Args *args = (BAM_Image_filter_Args *) kernelArgs;
#if !VCOP_HOST_EMULATION
    internalBlock[PARAMS_IDX].size = 2 * vcop_filter_uchar_char_char_param_count();
#else
    internalBlock[PARAMS_IDX].size = 4;
#endif    
    internalBlock[COEFFS_IDX].size = args->coeff_blk_width*args->coeff_blk_height;
    
    if (args->coeff_type== USHORT_TYPE || args->coeff_type== SHORT_TYPE) {
        internalBlock[COEFFS_IDX].size *= 2; 
    }
    else if (args->coeff_type== INT_TYPE) {
        internalBlock[COEFFS_IDX].size *= 4; 
    }
    else {
        ;
    }
    /*--------------------------------------------------------------------------*/
    /* Oputput pointer                                                                             */
    /*--------------------------------------------------------------------------*/
    outBlock[0].size = ((args->compute_blk_width) * (args->compute_blk_height));

    return 0;
}

/* Comment out below function as we are passing NULL as pointer to the setmemRec function in structure BAM_KernelHelperFuncDef
 * BAM automatically copies the different input, output, internal block's pointers into the kernel's context, as well as the arguments.
 */
#if 0
/**
 *******************************************************************************
 * @fn        BAM_Image_filter_SetMemRecFunc
 * @brief    .
 *
 * @inputs -  internalBlock :
 * @inputs -  inBlock :
 * @inputs -  outBlock :
 * @inputs -  numInternalBlocks :
 * @inputs -  numInBlocks :
 * @inputs -  numOutBlocks :
 * @inputs -  kernelContext :
 *
 * @return   none
 * @param Comments:
 *******************************************************************************
 */
static BAM_Status BAM_Image_filter_setMemRecFunc
(
  const BAM_MemRec *internalBlock[],
  const BAM_MemRec *inBlock[],
  const BAM_MemRec *outBlock[],
  uint8_t           numInternalBlocks,
  uint8_t           numInBlocks,
  uint8_t           numOutBlocks,
  void             *kernelContext,
  void             *kernelArgs
)
{
  BAM_Image_filter_Context *context = (BAM_Image_filter_Context *) kernelContext;
  BAM_Image_filter_Args *args = (BAM_Image_filter_Args *) kernelArgs;

  if (numInternalBlocks != 1)
  {
    PRINTF("ERROR: Unexpected numInternalBlocks recieved SetMemRecFunc()!!!");
  }
  if (numInBlocks != 1)
  {
    PRINTF("ERROR: Unexpected numInBlocks recieved SetMemRecFunc()!!!");
  }
  if (numOutBlocks != 1)
  {
    PRINTF("ERROR: Unexpected numOutBlocks recieved in SetMemRecFunc()!!!");
  }

  context->kernelArgs= *args;

  context->pInBlock[0] = inBlock[0]->base;
  context->pOutBlock[0] = outBlock[0]->base;
  context->pInternalBlock[PARAMS_IDX] = internalBlock[PARAMS_IDX]->base;

  return BAM_S_SUCCESS;
}
#endif

BAM_KernelInfo gBAM_TI_filterKernel =
{
  0, /*kernelId */
  sizeof(BAM_Image_filter_Context),/*kernelContextSize*/
  sizeof(BAM_Image_filter_Args),
  BAM_EVE, /*coreType */
  BAM_NODE_COMPUTE, /*nodeType */
  NUM_IN_BLOCKS,      /*1*/
  NUM_OUT_BLOCKS,      /*1 */
  NUM_INTERNAL_BLOCKS       /*2 */
};

BAM_KernelHelperFuncDef gBAM_TI_filterHelperFunc =
{
  &BAM_Image_filter_getMemRecFunc,
  NULL,/*(BAM_KernelSetMemRecFunc)&BAM_Image_filter_setMemRecFunc*/
};

