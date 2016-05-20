/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*                                                                          */
/*     @file : vcop_weight_computation_host.c                               */
/*                                                                          */
/*     @brief : This file is being added to enable host emulation support   */
/*     with minimal changes to existing test code. Basically, this file     */
/*     re-implements the auto generated kernel C functions namely the init  */
/*     and vloops for the kernel.                                           */
/*                                                                          */
/*     Host emulation wrapper functions for Weight Computation:             */
/*           vcop_weight_computation_init - Copies arguments to             */
/*             parameter block memory                                       */
/*           vcop_weight_computation_vloops - Invokes the API namely        */
/*             vcop_weight_computation defined in kernel file by            */
/*             passing the arguments from parameter block memory            */
/*                                                                          */
/*  @author Venkat R Peddigari (a0393744@ti.com)                            */
/*                                                                          */
/*  @version 1.0 (November 2013) : Base version.                            */
/*                                                                          */
/*==========================================================================*/

#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include "vcop.h"

#if VCOP_HOST_EMULATION
void vcop_weight_computation
(
    __vptr_uint16  pXYList_A,
    __vptr_uint16  pOutWts_B,
    unsigned short numKeyPoints,
    unsigned short qFormatMaxFactor,
    unsigned short truncateBits,
    unsigned short outputStride
);

typedef struct _vcop_weight_computation_args
{
    unsigned short numKeyPoints;
    unsigned short qFormatMaxFactor;
    unsigned short truncateBits;
    unsigned short outputStride;
} VCOP_WEIGHT_COMPUTATION_Args;


typedef struct _vcop_weight_computation_context
{
    void *pInBlock[1];
    void *pOutBlock[1];
    VCOP_WEIGHT_COMPUTATION_Args kernelArgs;
} VCOP_WEIGHT_COMPUTATION_Context;

unsigned short __pblock_vcop_weight_computation[sizeof(VCOP_WEIGHT_COMPUTATION_Context)/sizeof(unsigned short)];

unsigned int vcop_weight_computation_init(
    __vptr_uint16  pXYList_A,
    __vptr_uint16   pOutWts_B,
    unsigned short numKeyPoints,
    unsigned short qFormatMaxFactor,
    unsigned short truncateBits,
    unsigned short outputStride,
    unsigned short  pblock[])
{
    int retVal = 0;

    VCOP_WEIGHT_COMPUTATION_Context *weightComputationHostContext = (VCOP_WEIGHT_COMPUTATION_Context *)pblock;

    weightComputationHostContext->pInBlock[0]                 = pXYList_A.addr;
    weightComputationHostContext->pOutBlock[0]                = pOutWts_B.addr;
    weightComputationHostContext->kernelArgs.numKeyPoints     = numKeyPoints;
    weightComputationHostContext->kernelArgs.qFormatMaxFactor = qFormatMaxFactor;
    weightComputationHostContext->kernelArgs.truncateBits     = truncateBits;
    weightComputationHostContext->kernelArgs.outputStride     = outputStride;
    
    return retVal;
}


void vcop_weight_computation_vloops(unsigned short pblock[])
{
    VCOP_WEIGHT_COMPUTATION_Context *weightComputationHostContext = (VCOP_WEIGHT_COMPUTATION_Context *)pblock;

    vcop_weight_computation(weightComputationHostContext->pInBlock[0], weightComputationHostContext->pOutBlock[0],
                                weightComputationHostContext->kernelArgs.numKeyPoints, 
                                weightComputationHostContext->kernelArgs.qFormatMaxFactor,
                                weightComputationHostContext->kernelArgs.truncateBits,
                                weightComputationHostContext->kernelArgs.outputStride);
}


unsigned int vcop_weight_computation_param_count(void)
{
    return (sizeof(VCOP_WEIGHT_COMPUTATION_Context));
}

#endif
