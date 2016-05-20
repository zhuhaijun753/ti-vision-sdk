/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
* @file bam_orientation_binning_helper_funcs.c
*
* @brief    This file contains all kernel helper functions for orientation_binning
*           kernel
*
* @version 0.0 (Jan 2014) : Base version.
*/

#include <stdio.h>
#include <stdlib.h>

#include "bam_orientation_binning_helper_funcs.h"
#include "vcop_orientation_binning_kernel.h"
BAM_Status BAM_orientation_binning_getMemRecFunc
(
    const void   *kernelArgs,
    BAM_MemRec   memRecInternal[],
    BAM_MemRec   memRecOutputDataBlock[],
    uint8_t      *numRecInternal,
    uint8_t      *numRecOutputDataBlock
);
/**
*******************************************************************************
* @fn        BAM_orientation_binning_getMemRecFunc
* @brief
*
* @inputs -  kernelArgs :
* @inputs -  kernelContext :
* @inputs -  memRecInternal :
* @inputs -  memRecOutputDataBlock :
* @inputs -  numRecInternal :
* @inputs -  numRecOutputDataBlock :
*
* @return   none
* @param Comments:
*******************************************************************************
*/
BAM_Status BAM_orientation_binning_getMemRecFunc
(
    const void   *kernelArgs,
    BAM_MemRec   memRecInternal[],
    BAM_MemRec   memRecOutputDataBlock[],
    uint8_t      *numRecInternal,
    uint8_t      *numRecOutputDataBlock
)
{
    uint16_t  absGradSize = 4U;
    const BAM_orientation_binning_Args *args = (const BAM_orientation_binning_Args *)kernelArgs;

#if (!VCOP_HOST_EMULATION)
    memRecInternal[ORIENTATION_BINNING_INTERNAL_PARAMS_IDX].size = (vcop_orientation_binning_param_count())* sizeof(uint16_t);
#else
    /* This field could be any non-zero number for host emulation, its not really used for host emualtion */
    memRecInternal[ORIENTATION_BINNING_INTERNAL_PARAMS_IDX].size = 4;
#endif
    memRecInternal[ORIENTATION_BINNING_INTERNAL_PARAMS_IDX].attrs.memAttrs = BAM_MEMATTRS_PERSIST;
    memRecInternal[ORIENTATION_BINNING_INTERNAL_PARAMS_IDX].space = BAM_MEMSPACE_WBUF;

    memRecInternal[ORIENTATION_BINNING_INTERNAL_SIN_TAB_IDX].size = args->numBins * sizeof(uint16_t);
    memRecInternal[ORIENTATION_BINNING_INTERNAL_SIN_TAB_IDX].attrs.memAttrs = BAM_MEMATTRS_PERSIST;
    memRecInternal[ORIENTATION_BINNING_INTERNAL_SIN_TAB_IDX].space = BAM_MEMSPACE_WBUF;

    memRecInternal[ORIENTATION_BINNING_INTERNAL_COS_TAB_IDX].size = args->numBins * sizeof(uint16_t);
    memRecInternal[ORIENTATION_BINNING_INTERNAL_COS_TAB_IDX].attrs.memAttrs = BAM_MEMATTRS_PERSIST;
    memRecInternal[ORIENTATION_BINNING_INTERNAL_COS_TAB_IDX].space = BAM_MEMSPACE_WBUF;

    if((args->numBins & 1U) == NULL)
    {
      absGradSize =(args->blockW) * (args->blockH);
    }
    memRecInternal[ORIENTATION_BINNING_INTERNAL_ABS_GRADX_IDX].size = absGradSize;
    memRecInternal[ORIENTATION_BINNING_INTERNAL_ABS_GRADX_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    memRecInternal[ORIENTATION_BINNING_INTERNAL_ABS_GRADX_IDX].space = BAM_MEMSPACE_IBUFLA;
 
    memRecInternal[ORIENTATION_BINNING_INTERNAL_ABS_GRADY_IDX].size = absGradSize;
    memRecInternal[ORIENTATION_BINNING_INTERNAL_ABS_GRADY_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    memRecInternal[ORIENTATION_BINNING_INTERNAL_ABS_GRADY_IDX].space = BAM_MEMSPACE_IBUFHA;
    
    /*--------------------------------------------------------------------------*/
    /* Oputput pointer                                                          */
    /*--------------------------------------------------------------------------*/
    memRecOutputDataBlock[ORIENTATION_BINNING_OUT_BIN_IDX].size = (args->blockW) * (((args->blockH+1)/2)*2);
    memRecOutputDataBlock[ORIENTATION_BINNING_OUT_BIN_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    memRecOutputDataBlock[ORIENTATION_BINNING_OUT_BIN_IDX].space = BAM_MEMSPACE_WBUF;

    return BAM_S_SUCCESS;
}

BAM_KernelInfo gBAM_TI_orientation_binningKernel =
{
    0,  /*kernelId */
    sizeof(BAM_orientation_binning_Context),/*kernelContextSize*/
    sizeof(BAM_orientation_binning_Args),
    BAM_EVE, /* Core Type */
    BAM_NODE_COMPUTE, /*nodeType */
    ORIENTATION_BINNING_NUM_IN_BLOCKS,      /*numInputDataBlocks*/
    ORIENTATION_BINNING_NUM_OUT_BLOCKS,      /*numOutputDataBlocks */
    ORIENTATION_BINNING_NUM_INTERNAL_BLOCKS       /*numRecInternal */
};


BAM_KernelHelperFuncDef gBAM_TI_orientation_binningHelperFunc =
{
    &BAM_orientation_binning_getMemRecFunc,
    NULL
};

