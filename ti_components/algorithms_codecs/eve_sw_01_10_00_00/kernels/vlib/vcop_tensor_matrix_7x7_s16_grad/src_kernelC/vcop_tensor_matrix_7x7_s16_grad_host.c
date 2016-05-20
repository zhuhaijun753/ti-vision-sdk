/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*                                                                          */
/*     @file : vcop_tensor_matrix_7x7_s16_grad_host.c                       */
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

#if VCOP_HOST_EMULATION
void vcop_tensor_matrix_7x7_s16_grad(
   __vptr_int16 gradX_a,
   __vptr_int16 gradY_b,
   unsigned short stride,
   unsigned short n,
   __vptr_int32 Ix2_a,
   __vptr_int32 Iy2_b,
   __vptr_int32 Ixy_c,
   __vptr_int32 scartch_a,
   __vptr_int32 scartch_b,
   __vptr_int32 scartch_c);

typedef struct _vcop_tensor_matrix_7x7_s16_grad_args
{
    unsigned short inputStride;
    unsigned short numBlocks;
} VCOP_tensor_matrix_7x7_s16_grad_Args;


typedef struct _vcop_tensor_matrix_7x7_s16_grad_context
{
   void *pInBlock[2];
   void *pInternalBlock[3];
   void *pOutBlock[3];
    VCOP_tensor_matrix_7x7_s16_grad_Args kernelArgs;
} VCOP_tensor_matrix_7x7_s16_grad_Context;

unsigned short __pblock_vcop_tensor_matrix_7x7_s16_grad[sizeof(VCOP_tensor_matrix_7x7_s16_grad_Context)/sizeof(unsigned short)];

/* Parameter Block Initialization Function */
unsigned int vcop_tensor_matrix_7x7_s16_grad_init(
   __vptr_int16 gradX_a,
   __vptr_int16 gradY_b,
   unsigned short stride,
   unsigned short n,
   __vptr_int32 Ix2_a,
   __vptr_int32 Iy2_b,
   __vptr_int32 Ixy_c,
   __vptr_int32 scartch_a,
   __vptr_int32 scartch_b,
   __vptr_int32 scartch_c,
   unsigned short pblock[]
)
{
    int retVal = 0;

    VCOP_tensor_matrix_7x7_s16_grad_Context *Context = (VCOP_tensor_matrix_7x7_s16_grad_Context *)pblock;

    Context->pInBlock[0]            = gradX_a.addr;
    Context->pInBlock[1]            = gradY_b.addr;
    Context->pOutBlock[0]           = Ix2_a.addr;
    Context->pOutBlock[1]           = Iy2_b.addr;
    Context->pOutBlock[2]           = Ixy_c.addr;
    Context->pInternalBlock[0]      = scartch_a.addr;
    Context->pInternalBlock[1]      = scartch_b.addr;
    Context->pInternalBlock[2]      = scartch_c.addr;
    Context->kernelArgs.inputStride = stride;
    Context->kernelArgs.numBlocks   = n;
    
    return retVal;
}


void vcop_tensor_matrix_7x7_s16_grad_vloops(unsigned short pblock[])
{
    VCOP_tensor_matrix_7x7_s16_grad_Context *Context = (VCOP_tensor_matrix_7x7_s16_grad_Context *)pblock;

    vcop_tensor_matrix_7x7_s16_grad(
          Context->pInBlock[0],           
          Context->pInBlock[1],           
          Context->kernelArgs.inputStride,
          Context->kernelArgs.numBlocks,  
          Context->pOutBlock[0],          
          Context->pOutBlock[1],          
          Context->pOutBlock[2],          
          Context->pInternalBlock[0],     
          Context->pInternalBlock[1],     
          Context->pInternalBlock[2]
    );



}

unsigned int vcop_tensor_matrix_7x7_s16_grad_param_count(void)
{
    return (sizeof(VCOP_tensor_matrix_7x7_s16_grad_Context));
}

#endif
