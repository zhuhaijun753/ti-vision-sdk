/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*                                                                          */
/*     @file : vcop_multiblock_gradient_xy_host.c                           */
/*                                                                          */
/*     @brief : This file is being added to enable host emulation support   */
/*     with minimal changes to existing test code. Basically, this file     */
/*     re-implements the auto generated kernel C functions namely the init  */
/*     and vloops for the kernel.                                           */
/*                                                                          */
/*     Host emulation wrapper functions for Multi Block Gradient XY:        */
/*           vcop_multiblock_gradient_xy_init - Copies arguments to         */
/*             parameter block memory                                       */
/*           vcop_multiblock_gradient_xy_vloops - Invokes the API namely    */
/*             vcop_multiblock_gradient_xy defined in kernel file by        */
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
void vcop_multiblock_gradient_xy
(
    __vptr_uint8   pIn_A,
    __vptr_int16   pIntlvGradXY_B,
    unsigned short inputStride,
    unsigned short blkWidth,
    unsigned short blkHeight,
    unsigned short blkOffset,
    unsigned short numBlocks
);

typedef struct _vcop_multiblock_gradient_xy_args
{
    unsigned short inputStride;
    unsigned short blkWidth;
    unsigned short blkHeight;
    unsigned short blkOffset;
    unsigned short numBlocks;
} VCOP_Multi_Block_Gradient_XY_Args;

typedef struct _vcop_multiblock_gradient_xy_context
{
    void *pInBlock[1];
    void *pOutBlock[1];
    VCOP_Multi_Block_Gradient_XY_Args kernelArgs;
} VCOP_Multi_Block_Gradient_XY_Context;

unsigned short __pblock_vcop_multiblock_gradient_xy[sizeof(VCOP_Multi_Block_Gradient_XY_Context)/sizeof(unsigned short)];

unsigned int vcop_multiblock_gradient_xy_init(
    __vptr_uint8    pIn,
    __vptr_int16    pIntlvGradXY,
    unsigned short  inputStride,
    unsigned short  blkWidth,
    unsigned short  blkHeight,
    unsigned short  blkOffset,
    unsigned short  numBlocks,
    unsigned short  pblock[])
{
    int retVal = 0;

    VCOP_Multi_Block_Gradient_XY_Context *multiBlockGradXYHostContext = (VCOP_Multi_Block_Gradient_XY_Context *)pblock;

    multiBlockGradXYHostContext->pInBlock[0]            = pIn.addr;
    multiBlockGradXYHostContext->pOutBlock[0]           = pIntlvGradXY.addr;
    multiBlockGradXYHostContext->kernelArgs.inputStride = inputStride;
    multiBlockGradXYHostContext->kernelArgs.blkWidth    = blkWidth;
    multiBlockGradXYHostContext->kernelArgs.blkHeight   = blkHeight;
    multiBlockGradXYHostContext->kernelArgs.blkOffset   = blkOffset;
    multiBlockGradXYHostContext->kernelArgs.numBlocks   = numBlocks;

    return retVal;
}


void vcop_multiblock_gradient_xy_vloops(unsigned short pblock[])
{
    VCOP_Multi_Block_Gradient_XY_Context *multiBlockGradXYHostContext = (VCOP_Multi_Block_Gradient_XY_Context *)pblock;

    vcop_multiblock_gradient_xy(multiBlockGradXYHostContext->pInBlock[0], multiBlockGradXYHostContext->pOutBlock[0],
                                multiBlockGradXYHostContext->kernelArgs.inputStride, multiBlockGradXYHostContext->kernelArgs.blkWidth,
                                multiBlockGradXYHostContext->kernelArgs.blkHeight, multiBlockGradXYHostContext->kernelArgs.blkOffset,
                                multiBlockGradXYHostContext->kernelArgs.numBlocks);
}


unsigned int vcop_multiblock_gradient_xy_param_count(void)
{
    return (sizeof(VCOP_Multi_Block_Gradient_XY_Context));
}

#endif
