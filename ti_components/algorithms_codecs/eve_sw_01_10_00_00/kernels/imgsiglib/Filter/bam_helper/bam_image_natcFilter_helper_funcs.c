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
#include "bam_image_natcFilter.h" /*makerules should take care of include path*/
#include "vcop_filter_kernel.h"

/* Function Prototypes */
static BAM_Status BAM_Image_natcFilter_getMemRecFunc
(
  const void *kernelArgs,
  BAM_MemRec *internalBlock,
  BAM_MemRec *outBlock,
  uint8_t    *numInternalBlocks,
  uint8_t    *numOutBlocks
);

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
static BAM_Status BAM_Image_natcFilter_getMemRecFunc
(
    const void *kernelArgs,
    BAM_MemRec *internalBlock,
    BAM_MemRec *outBlock,
    uint8_t    *numInternalBlocks,
    uint8_t    *numOutBlocks
)
{
    BAM_Image_filter_Args *args = (BAM_Image_filter_Args *) kernelArgs;

    internalBlock[PARAMS_IDX].size = 2;
    
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
    /* Oputput pointer                                                          */
    /*--------------------------------------------------------------------------*/
    outBlock[0].size = ((args->compute_blk_width) * (args->compute_blk_height));

    return 0;
}


BAM_KernelInfo gBAM_TI_natcFilterKernel =
{
  0, /*kernelId */
  sizeof(BAM_Image_filter_Context),/*kernelContextSize*/
  sizeof(BAM_Image_filter_Args),
  BAM_EVE_ARP32, /*coreType */
  BAM_NODE_COMPUTE, /*nodeType */
  NUM_IN_BLOCKS,      /*1*/
  NUM_OUT_BLOCKS,      /*1 */
  NUM_INTERNAL_BLOCKS       /*2 */
};

BAM_KernelHelperFuncDef gBAM_TI_natcFilterHelperFunc =
{
  &BAM_Image_natcFilter_getMemRecFunc,
  NULL,/*(BAM_KernelSetMemRecFunc)&BAM_Image_filter_setMemRecFunc*/
};

