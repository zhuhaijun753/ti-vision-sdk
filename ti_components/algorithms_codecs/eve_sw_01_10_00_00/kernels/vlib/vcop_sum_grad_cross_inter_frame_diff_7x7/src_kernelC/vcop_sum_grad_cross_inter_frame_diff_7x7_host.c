/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*                                                                          */
/*     @file : vcop_sum_grad_cross_inter_frame_diff_7x7_host.c              */
/*                                                                          */
/*     @brief : This file is being added to enable host emulation support   */
/*     with minimal changes to existing test code. Basically, this file     */
/*     re-implements the auto generated kernel C functions namely the init  */
/*     and vloops for the kernel.                                           */
/*                                                                          */
/*  @author Kumar Desappan (a0393754@ti.com)                                */
/*                                                                          */
/*  @version 1.0 (November 2013) : Base version.                            */
/*                                                                          */
/*==========================================================================*/

#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include "vcop.h"

#include "vcop_sum_grad_cross_inter_frame_diff_7x7_cn.h"

#if VCOP_HOST_EMULATION
void vcop_sum_grad_cross_inter_frame_diff_7x7(
   __vptr_int16 gradX_a,
   __vptr_int16 gradY_b,
   __vptr_uint8 im1_a,
   __vptr_uint8 im2_b,
   unsigned short gradStride,
   unsigned short imStride,
   unsigned short n,
   __vptr_int32 IxIt_a,
   __vptr_int32 IyIt_b,
   __vptr_int32 scartch_a,
   __vptr_int32 scartch_b);

typedef struct _vcop_sum_grad_cross_inter_frame_diff_7x7_args
{
   unsigned short  gradStride;
   unsigned short  imStride;
    unsigned short numBlocks;
} vcop_sum_grad_cross_inter_frame_diff_7x7_Args;


typedef struct _vcop_sum_grad_cross_inter_frame_diff_7x7_context
{
   void *pInBlock[4];
   void *pInternalBlock[2];
   void *pOutBlock[2];
    vcop_sum_grad_cross_inter_frame_diff_7x7_Args kernelArgs;
} vcop_sum_grad_cross_inter_frame_diff_7x7_Context;

unsigned short __pblock_vcop_sum_grad_cross_inter_frame_diff_7x7[sizeof(vcop_sum_grad_cross_inter_frame_diff_7x7_Context)/sizeof(unsigned short)];

/* Parameter Block Initialization Function */
unsigned int vcop_sum_grad_cross_inter_frame_diff_7x7_init(
   __vptr_int16 gradX_a,
   __vptr_int16 gradY_b,
   __vptr_uint8 im1_a,
   __vptr_uint8 im2_b,
   unsigned short gradStride,
   unsigned short imStride,
   unsigned short n,
   __vptr_int32 IxIt_a,
   __vptr_int32 IyIt_b,
   __vptr_int32 scartch_a,
   __vptr_int32 scartch_b,
   unsigned short pblock[])
{
    int retVal = 0;

    vcop_sum_grad_cross_inter_frame_diff_7x7_Context *Context = (vcop_sum_grad_cross_inter_frame_diff_7x7_Context *)pblock;

    Context->pInBlock[0]            = gradX_a.addr;
    Context->pInBlock[1]            = gradY_b.addr;
    Context->pInBlock[2]            = im1_a.addr;
    Context->pInBlock[3]            = im2_b.addr;
    Context->pOutBlock[0]           = IxIt_a.addr;
    Context->pOutBlock[1]           = IyIt_b.addr;
    Context->pInternalBlock[0]      = scartch_a.addr;
    Context->pInternalBlock[1]      = scartch_b.addr;
    Context->kernelArgs.gradStride  = gradStride;
    Context->kernelArgs.imStride    = imStride;
    Context->kernelArgs.numBlocks   = n;
    
    return retVal;
}


void vcop_sum_grad_cross_inter_frame_diff_7x7_vloops(unsigned short pblock[])
{
    vcop_sum_grad_cross_inter_frame_diff_7x7_Context *Context = (vcop_sum_grad_cross_inter_frame_diff_7x7_Context *)pblock;

#ifdef NATC
    vcop_sum_grad_cross_inter_frame_diff_7x7_cn(
      (short *)Context->pInBlock[0],
      (short *)Context->pInBlock[1],
      (unsigned char *)Context->pInBlock[2],
      (unsigned char *)Context->pInBlock[3],
      Context->kernelArgs.gradStride,
      Context->kernelArgs.imStride,
      Context->kernelArgs.numBlocks,
      (int *)Context->pOutBlock[0],
      (int *)Context->pOutBlock[1]
    );
#else
    vcop_sum_grad_cross_inter_frame_diff_7x7(
      Context->pInBlock[0],          
      Context->pInBlock[1],         
      Context->pInBlock[2],          
      Context->pInBlock[3],          
      Context->kernelArgs.gradStride,
      Context->kernelArgs.imStride,  
      Context->kernelArgs.numBlocks, 
      Context->pOutBlock[0],         
      Context->pOutBlock[1],         
      Context->pInternalBlock[0],
      Context->pInternalBlock[1]    
    );
#endif

}

unsigned int vcop_sum_grad_cross_inter_frame_diff_7x7_param_count(void)
{
    return (sizeof(vcop_sum_grad_cross_inter_frame_diff_7x7_Context));
}

#endif
