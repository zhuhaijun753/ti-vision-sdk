/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*                                                                          */
/*     @file : vcop_alpha_blend_yuv420nv12_host.c                           */
/*                                                                          */
/*     @brief : This file is being added to enable host emulation support   */
/*     with minimal changes to existing test code. Basically, this file     */
/*     re-implements the auto generated kernel C functions namely the init  */
/*     and vloops for the kernel.                                           */
/*                                                                          */
/*     Host emulation wrapper functions for YUV 4200NV12 Alpha Blending:    */
/*           vcop_alpha_blend_yuv420nv12_init - Copies arguments to         */
/*             parameter block memory                                       */
/*           vcop_alpha_blend_yuv420nv12_vloops - Invokes the API namely    */
/*             vcop_alpha_blend_yuv420nv12 defined in kernel file by        */
/*             passing the arguments from parameter block memory            */
/*                                                                          */
/*  @author Anoop K P(a-kp@ti.com)                                          */
/*                                                                          */
/*  @version 1.0 (Sept 2013) : Base version.                                */
/*                                                                          */
/*==========================================================================*/

#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include "vcop.h"

#if VCOP_HOST_EMULATION
#include "vcop_alpha_blend_yuv420nv12_kernel.k"

unsigned short __pblock_vcop_alpha_blend_yuv420nv12[14];

typedef struct _vcop_alpha_blend_yuv420nv12_args
{
    unsigned short width;
    unsigned short height;
    unsigned short in_img1_stride;
    unsigned short in_img2_stride;
    unsigned short out_stride;
} VCOP_Alpha_Blend_YUV420nv12_Args;


typedef struct _vcop_alpha_blend_yuv420nv12_context
{
    void *pInBlock[3];
    void *pOutBlock[1];
    VCOP_Alpha_Blend_YUV420nv12_Args kernelArgs;
} VCOP_Alpha_Blend_YUV420nv12_Context;


unsigned int vcop_alpha_blend_yuv420nv12_init(
    __vptr_uint8    in_img1,
    __vptr_uint8    in_img2,
    __vptr_uint8    alphaFrame,
    __vptr_uint8    out,
    unsigned short  width,
    unsigned short  height,
    unsigned short  in_img1_stride,
    unsigned short  in_img2_stride,
    unsigned short  out_stride,
    unsigned short pblock[])
{
    int retVal = 0;

    VCOP_Alpha_Blend_YUV420nv12_Context *alphaBlendHostContext = (VCOP_Alpha_Blend_YUV420nv12_Context *)pblock;

    alphaBlendHostContext->pInBlock[0] = in_img1.addr;
    alphaBlendHostContext->pInBlock[1] = in_img2.addr;
    alphaBlendHostContext->pInBlock[2] = alphaFrame.addr;
    alphaBlendHostContext->pOutBlock[0] = out.addr;
    alphaBlendHostContext->kernelArgs.width = width;
    alphaBlendHostContext->kernelArgs.height = height;
    alphaBlendHostContext->kernelArgs.in_img1_stride = in_img1_stride;
    alphaBlendHostContext->kernelArgs.in_img2_stride = in_img2_stride;
    alphaBlendHostContext->kernelArgs.out_stride = out_stride;
    
    return retVal;
}


void vcop_alpha_blend_yuv420nv12_vloops(unsigned short pblock[])
{
    VCOP_Alpha_Blend_YUV420nv12_Context *alphaBlendHostContext = (VCOP_Alpha_Blend_YUV420nv12_Context *)pblock;

    vcop_alpha_blend_yuv420nv12(alphaBlendHostContext->pInBlock[0], alphaBlendHostContext->pInBlock[1],
                                alphaBlendHostContext->pInBlock[2], alphaBlendHostContext->pOutBlock[0],
                                alphaBlendHostContext->kernelArgs.width, alphaBlendHostContext->kernelArgs.height,
                                alphaBlendHostContext->kernelArgs.in_img1_stride, alphaBlendHostContext->kernelArgs.in_img2_stride,
                                alphaBlendHostContext->kernelArgs.out_stride);
}


unsigned int vcop_alpha_blend_yuv420nv12_param_count(void)
{
    return (sizeof(VCOP_Alpha_Blend_YUV420nv12_Context));
}

#endif
