/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*                                                                          */
/*     @file : vcop_calc_determinant_tensor_matrix_host.c              */
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
void vcop_calc_determinant_tensor_matrix(
  __vptr_uint16 Ix2L_a, 
  __vptr_uint16 Iy2L_b,
  __vptr_uint16 IxyL_c,
  __vptr_int16  Ix2H_a, 
  __vptr_int16  Iy2H_b,
  __vptr_int16  IxyH_c,
  __vptr_uint16 d_nrsb_a,
  __vptr_int32  d_norm_b,
  unsigned short n);

typedef struct _vcop_calc_determinant_tensor_matrix_args
{
    unsigned short numBlocks;
} vcop_calc_determinant_tensor_matrix_Args;


typedef struct _vcop_calc_determinant_tensor_matrix_context
{
   void *pInBlock[6];
   void *pOutBlock[2];
    vcop_calc_determinant_tensor_matrix_Args kernelArgs;
} vcop_calc_determinant_tensor_matrix_Context;

unsigned short __pblock_vcop_calc_determinant_tensor_matrix[sizeof(vcop_calc_determinant_tensor_matrix_Context)/sizeof(unsigned short)];

/* Parameter Block Initialization Function */
unsigned int vcop_calc_determinant_tensor_matrix_init(
  __vptr_uint16 Ix2L_a, 
  __vptr_uint16 Iy2L_b,
  __vptr_uint16 IxyL_c,
  __vptr_int16  Ix2H_a, 
  __vptr_int16  Iy2H_b,
  __vptr_int16  IxyH_c,
  __vptr_uint16 d_nrsb_a,
  __vptr_int32  d_norm_b,
   unsigned short n,
   unsigned short pblock[])
{
    int retVal = 0;

    vcop_calc_determinant_tensor_matrix_Context *Context = (vcop_calc_determinant_tensor_matrix_Context *)pblock;

    Context->pInBlock[0]            = Ix2L_a.addr;
    Context->pInBlock[1]            = Iy2L_b.addr;
    Context->pInBlock[2]            = IxyL_c.addr;
    Context->pInBlock[3]            = Ix2H_a.addr;
    Context->pInBlock[4]            = Iy2H_b.addr;
    Context->pInBlock[5]            = IxyH_c.addr;
    Context->pOutBlock[0]           = d_nrsb_a.addr;
    Context->pOutBlock[1]           = d_norm_b.addr;
    Context->kernelArgs.numBlocks   = n;
    
    return retVal;
}


void vcop_calc_determinant_tensor_matrix_vloops(unsigned short pblock[])
{
    vcop_calc_determinant_tensor_matrix_Context *Context = (vcop_calc_determinant_tensor_matrix_Context *)pblock;

    vcop_calc_determinant_tensor_matrix(
      Context->pInBlock[0],        
      Context->pInBlock[1],         
      Context->pInBlock[2],         
      Context->pInBlock[3],         
      Context->pInBlock[4],         
      Context->pInBlock[5],         
      Context->pOutBlock[0],        
      Context->pOutBlock[1],        
      Context->kernelArgs.numBlocks
      );

}

unsigned int vcop_calc_determinant_tensor_matrix_param_count(void)
{
    return (sizeof(vcop_calc_determinant_tensor_matrix_Context));
}

#endif
