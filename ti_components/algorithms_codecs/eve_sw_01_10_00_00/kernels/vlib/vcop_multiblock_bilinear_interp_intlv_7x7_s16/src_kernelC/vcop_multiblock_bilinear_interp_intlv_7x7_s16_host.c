/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*                                                                          */
/*     @file : vcop_multiblock_bilinear_interp_intlv_7x7_s16_host.c         */
/*                                                                          */
/*     @brief : This file is being added to enable host emulation support   */
/*     with minimal changes to existing test code. Basically, this file     */
/*     re-implements the auto generated kernel C functions namely the init  */
/*     and vloops for the kernel.                                           */
/*                                                                          */
/*     Host emulation wrapper functions for Multi Block Bilinear            */
/*     Interpolation Kernel for 16 bit gradient pixels stored in            */
/*     interleaved format i.e., GradientX followed by GradientY per pixel   */
/*           vcop_multiblock_bilinear_interp_intlv_7x7_s16_init -           */
/*             Copies arguments to parameter block memory                   */
/*           vcop_multiblock_bilinear_interp_intlv_7x7_s16_vloops - Invokes */
/*             the API namely vcop_multiblock_bilinear_interp_intlv_7x7_s16 */
/*             defined in kernel file by passing the arguments from         */
/*             parameter block memory                                       */
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
void vcop_multiblock_bilinear_interp_intlv_7x7_s16
(
    __vptr_int16       pIntlvGradXY_A,
    __vptr_uint16       pInpWts_X,
    __vptr_int16       pGradXBilinearInterpImg_B,
    __vptr_int16       pGradYBilinearInterpImg_C,
    unsigned short     input1Stride,
    unsigned short     input2Stride,
    unsigned short     outputStride,
    unsigned short     blkWidth,
    unsigned short     blkHeight,
    unsigned short     blkOffset,
    unsigned short     shiftValue,
    unsigned short     numKeyPoints
);

typedef struct _vcop_multiblock_bilinear_interp_intlv_7x7_s16_args
{
    unsigned short     input1Stride;
    unsigned short     input2Stride;
    unsigned short     outputStride;
    unsigned short     blkWidth;
    unsigned short     blkHeight;
    unsigned short     blkOffset;
    unsigned short     shiftValue;
    unsigned short     numKeyPoints;
} VCOP_Multiblock_Bilinear_Interp_Intlv_7x7_S16_Args;


typedef struct _vcop_multiblock_bilinear_interp_intlv_7x7_s16_context
{
    void *pInBlock[2];
    void *pOutBlock[2];
    VCOP_Multiblock_Bilinear_Interp_Intlv_7x7_S16_Args kernelArgs;
} VCOP_Multiblock_Bilinear_Interp_Intlv_7x7_S16_Context;

unsigned short __pblock_vcop_multiblock_bilinear_interp_intlv_7x7_s16[sizeof(VCOP_Multiblock_Bilinear_Interp_Intlv_7x7_S16_Context)/sizeof(unsigned short)];

unsigned int vcop_multiblock_bilinear_interp_intlv_7x7_s16_init(
    __vptr_int16       pIntlvGradXY_A,
    __vptr_uint16       pInpWts_X,
    __vptr_int16       pGradXBilinearInterpImg_B,
    __vptr_int16       pGradYBilinearInterpImg_C,
    unsigned short     input1Stride,
    unsigned short     input2Stride,
    unsigned short     outputStride,
    unsigned short     blkWidth,
    unsigned short     blkHeight,
    unsigned short     blkOffset,
    unsigned short     shiftValue,
    unsigned short     numKeyPoints,
    unsigned short     pblock[])
{
    int retVal = 0;

    VCOP_Multiblock_Bilinear_Interp_Intlv_7x7_S16_Context *multiblockBilinearInterpIntlv7x7S16HostContext = (VCOP_Multiblock_Bilinear_Interp_Intlv_7x7_S16_Context *)pblock;

    multiblockBilinearInterpIntlv7x7S16HostContext->pInBlock[0]             = pIntlvGradXY_A.addr;
    multiblockBilinearInterpIntlv7x7S16HostContext->pInBlock[1]             = pInpWts_X.addr;
    multiblockBilinearInterpIntlv7x7S16HostContext->pOutBlock[0]            = pGradXBilinearInterpImg_B.addr;
    multiblockBilinearInterpIntlv7x7S16HostContext->pOutBlock[1]            = pGradYBilinearInterpImg_C.addr;
    multiblockBilinearInterpIntlv7x7S16HostContext->kernelArgs.input1Stride = input1Stride;
    multiblockBilinearInterpIntlv7x7S16HostContext->kernelArgs.input2Stride = input2Stride;
    multiblockBilinearInterpIntlv7x7S16HostContext->kernelArgs.outputStride = outputStride;
    multiblockBilinearInterpIntlv7x7S16HostContext->kernelArgs.blkWidth     = blkWidth;
    multiblockBilinearInterpIntlv7x7S16HostContext->kernelArgs.blkHeight    = blkHeight;
    multiblockBilinearInterpIntlv7x7S16HostContext->kernelArgs.blkOffset    = blkOffset;
    multiblockBilinearInterpIntlv7x7S16HostContext->kernelArgs.shiftValue   = shiftValue;
    multiblockBilinearInterpIntlv7x7S16HostContext->kernelArgs.numKeyPoints = numKeyPoints;

    return retVal;
}


void vcop_multiblock_bilinear_interp_intlv_7x7_s16_vloops(unsigned short pblock[])
{
    VCOP_Multiblock_Bilinear_Interp_Intlv_7x7_S16_Context *multiblockBilinearInterpIntlv7x7S16HostContext = (VCOP_Multiblock_Bilinear_Interp_Intlv_7x7_S16_Context *)pblock;

    vcop_multiblock_bilinear_interp_intlv_7x7_s16(multiblockBilinearInterpIntlv7x7S16HostContext->pInBlock[0], multiblockBilinearInterpIntlv7x7S16HostContext->pInBlock[1],
                                multiblockBilinearInterpIntlv7x7S16HostContext->pOutBlock[0], multiblockBilinearInterpIntlv7x7S16HostContext->pOutBlock[1],
                                multiblockBilinearInterpIntlv7x7S16HostContext->kernelArgs.input1Stride, multiblockBilinearInterpIntlv7x7S16HostContext->kernelArgs.input2Stride,
                                multiblockBilinearInterpIntlv7x7S16HostContext->kernelArgs.outputStride, multiblockBilinearInterpIntlv7x7S16HostContext->kernelArgs.blkWidth,
                                multiblockBilinearInterpIntlv7x7S16HostContext->kernelArgs.blkHeight, multiblockBilinearInterpIntlv7x7S16HostContext->kernelArgs.blkOffset,
                                multiblockBilinearInterpIntlv7x7S16HostContext->kernelArgs.shiftValue, multiblockBilinearInterpIntlv7x7S16HostContext->kernelArgs.numKeyPoints);
}


unsigned int vcop_multiblock_bilinear_interp_intlv_7x7_s16_param_count(void)
{
    return (sizeof(VCOP_Multiblock_Bilinear_Interp_Intlv_7x7_S16_Context));
}

#endif
