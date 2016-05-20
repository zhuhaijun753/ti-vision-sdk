/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
* @file bam_location_matrix_helper_funcs.c
*
* @brief    This file contains all kernel helper functions for location_matrix
*           kernel
*
*
* @version 0.0 (Jan 2014) : Base version.
*/

#include <stdio.h>
#include <stdlib.h>

#include "bam_location_matrix_helper_funcs.h"
#include "vcop_location_matrix_kernel.h"
BAM_Status BAM_location_matrix_getMemRecFunc
(
    const void   *kernelArgs,
    BAM_MemRec   memRecInternal[],
    BAM_MemRec   memRecOutputDataBlock[],
    uint8_t      *numRecInternal,
    uint8_t      *numRecOutputDataBlock
);
/**
*******************************************************************************
* @fn        BAM_location_matrix_getMemRecFunc
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
BAM_Status BAM_location_matrix_getMemRecFunc
(
    const void   *kernelArgs,
    BAM_MemRec   memRecInternal[],
    BAM_MemRec   memRecOutputDataBlock[],
    uint8_t      *numRecInternal,
    uint8_t      *numRecOutputDataBlock
)
{
    const BAM_location_matrix_Args *args = (const BAM_location_matrix_Args *)kernelArgs;
    BAM_Status status = BAM_S_SUCCESS;
    uint32_t numBins = (uint32_t)(args->numBins);
    numBins++;
    numBins = (numBins >> 1U) << 1U;

    if(args->gradientMagSize <= 2)
    {

#if (!VCOP_HOST_EMULATION)
    if(args->gradientMagSize == 1)
    {
      memRecInternal[LOCATION_MATRIX_INTERNAL_PARAMS_IDX].size = sizeof(uint16_t)*
                                  vcop_vec_L_matrix_u8_Mag_param_count();
    }
    else
    {
      memRecInternal[LOCATION_MATRIX_INTERNAL_PARAMS_IDX].size = sizeof(uint16_t)*
                                  vcop_vec_L_matrix_u16_Mag_param_count();
    }
#else
    /* This field could be any non-zero number for host emulation, its not really used for host emualtion */
    memRecInternal[LOCATION_MATRIX_INTERNAL_PARAMS_IDX].size = 4;
#endif
    memRecInternal[LOCATION_MATRIX_INTERNAL_PARAMS_IDX].attrs.memAttrs = BAM_MEMATTRS_PERSIST;
    memRecInternal[LOCATION_MATRIX_INTERNAL_PARAMS_IDX].space = BAM_MEMSPACE_WBUF;


    memRecInternal[LOCATION_MATRIX_INTERNAL_BIN_IDX].size = numBins;
    memRecInternal[LOCATION_MATRIX_INTERNAL_BIN_IDX].attrs.memAttrs = BAM_MEMATTRS_PERSIST;
    memRecInternal[LOCATION_MATRIX_INTERNAL_BIN_IDX].space = BAM_MEMSPACE_WBUF;


    /*--------------------------------------------------------------------------*/
    /* Output pointer                                                          */
    /*--------------------------------------------------------------------------*/
    memRecOutputDataBlock[LOCATION_MATRIX_OUT_MATRIX1_IDX].size = (args->gradientMagSize * args->blockW * args->blockH * numBins) / (2U) ;
    memRecOutputDataBlock[LOCATION_MATRIX_OUT_MATRIX1_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    memRecOutputDataBlock[LOCATION_MATRIX_OUT_MATRIX1_IDX].space = BAM_MEMSPACE_IBUFLA;

    memRecOutputDataBlock[LOCATION_MATRIX_OUT_MATRIX2_IDX].size = (args->gradientMagSize * args->blockW * args->blockH * numBins) / (2U);
    memRecOutputDataBlock[LOCATION_MATRIX_OUT_MATRIX2_IDX].attrs.memAttrs = BAM_MEMATTRS_SCRATCH;
    memRecOutputDataBlock[LOCATION_MATRIX_OUT_MATRIX2_IDX].space = BAM_MEMSPACE_IBUFHA;
    }
    return status;
}

BAM_KernelInfo gBAM_TI_location_matrixKernel =
{
    0,  /*kernelId */
    sizeof(BAM_location_matrix_Context),/*kernelContextSize*/
    sizeof(BAM_location_matrix_Args),
    BAM_EVE, /* Core Type */
    BAM_NODE_COMPUTE, /*nodeType */
    LOCATION_MATRIX_NUM_IN_BLOCKS,      /*numInputDataBlocks*/
    LOCATION_MATRIX_NUM_OUT_BLOCKS,      /*numOutputDataBlocks */
    LOCATION_MATRIX_NUM_INTERNAL_BLOCKS       /*numRecInternal */
};


BAM_KernelHelperFuncDef gBAM_TI_location_matrixHelperFunc =
{
    &BAM_location_matrix_getMemRecFunc,
    NULL
};

