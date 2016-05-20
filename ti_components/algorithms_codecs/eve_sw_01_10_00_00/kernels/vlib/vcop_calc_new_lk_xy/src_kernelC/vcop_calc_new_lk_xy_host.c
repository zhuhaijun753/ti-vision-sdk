/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*                                                                          */
/*     @file : vcop_calc_new_lk_xy_host.c                                   */
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

#include "vcop_calc_new_lk_xy_cn.h"

#if VCOP_HOST_EMULATION
void vcop_calc_new_lk_xy(
    __vptr_uint16 IxItL_a,         
    __vptr_uint16 IyItL_b,        
    __vptr_int16 IxItH_a,         
    __vptr_int16 IyItH_b,        
    __vptr_int16 Ix2_a,        
    __vptr_int16 Iy2_b,        
    __vptr_int16 Ixy_c,        
    __vptr_int16 X_c,
    __vptr_int16 Y_c,
    __vptr_int16 localXY_b,
    __vptr_int16 frameXY_b,
    __vptr_uint16 numValidPoints,
    __vptr_uint8  currValidPoints,        
    __vptr_uint32 pBaseAddrList ,
    __vptr_uint32 pValidAddrList,
    __vptr_uint32 pOutAddrList     ,
    __vptr_uint32 pValidOutAddrList,
    __vptr_int32  vx,
    __vptr_int32  vy,
    unsigned short  qFormatePel,
    unsigned short  minErrValue,
    unsigned char   searchRange,
    unsigned short n);

typedef struct _vcop_calc_new_lk_xy_args
{
    unsigned short  numBlocks;
    unsigned short  qFormatePel;
    short  minErrValue;
    unsigned char   searchRange;
} vcop_calc_new_lk_xy_Args;


typedef struct _vcop_calc_new_lk_xy_context
{
   void *pInBlock[17];
   void *pInternalBlock[2];
    vcop_calc_new_lk_xy_Args kernelArgs;
} vcop_calc_new_lk_xy_Context;

unsigned short __pblock_vcop_calc_new_lk_xy[sizeof(vcop_calc_new_lk_xy_Context)/sizeof(unsigned short)];

/* Parameter Block Initialization Function */
unsigned int vcop_calc_new_lk_xy_init(
    __vptr_uint16 IxItL_a,         
    __vptr_uint16 IyItL_b,        
    __vptr_int16  IxItH_a,         
    __vptr_int16  IyItH_b,        
    __vptr_int16  Ix2_a,        
    __vptr_int16  Iy2_b,        
    __vptr_int16  Ixy_c,        
    __vptr_int16  X_c,
    __vptr_int16  Y_c,
    __vptr_int16  localXY_b,
    __vptr_int16  frameXY_b,
    __vptr_uint16 numValidPoints,
    __vptr_uint8  currValidPoints,        
    __vptr_uint32 pBaseAddrList ,
    __vptr_uint32 pValidAddrList,
    __vptr_uint32 pOutAddrList     ,
    __vptr_uint32 pValidOutAddrList,
    __vptr_int32  vx,
    __vptr_int32  vy,
    unsigned short  qFormatePel,
    unsigned short  minErrValue,
    unsigned char   searchRange,
    unsigned short n,
   unsigned short pblock[])
{
    int retVal = 0;

    vcop_calc_new_lk_xy_Context *Context = (vcop_calc_new_lk_xy_Context *)pblock;

    Context->pInBlock[0]            = IxItL_a.addr;
    Context->pInBlock[1]            = IyItL_b.addr;
    Context->pInBlock[2]            = IxItH_a.addr;
    Context->pInBlock[3]            = IyItH_b.addr;
    Context->pInBlock[4]            = Ix2_a.addr;
    Context->pInBlock[5]            = Iy2_b.addr;
    Context->pInBlock[6]            = Ixy_c.addr;
    Context->pInBlock[7]            = X_c.addr;
    Context->pInBlock[8]            = Y_c.addr;
    Context->pInBlock[9]            = localXY_b.addr;
    Context->pInBlock[10]           = frameXY_b.addr;
    Context->pInBlock[11]           = numValidPoints.addr;
    Context->pInBlock[12]           = currValidPoints.addr;
    Context->pInBlock[13]           = pBaseAddrList.addr;
    Context->pInBlock[14]           = pValidAddrList.addr;
    Context->pInBlock[15]           = pOutAddrList.addr;
    Context->pInBlock[16]           = pValidOutAddrList.addr;
    Context->pInternalBlock[0]      = vx.addr;
    Context->pInternalBlock[1]      = vy.addr;
    Context->kernelArgs.qFormatePel = qFormatePel;
    Context->kernelArgs.minErrValue = minErrValue;
    Context->kernelArgs.numBlocks   = n;
    Context->kernelArgs.searchRange   = searchRange;
   
    return retVal;
}


void vcop_calc_new_lk_xy_vloops(unsigned short pblock[])
{
    vcop_calc_new_lk_xy_Context *Context = (vcop_calc_new_lk_xy_Context *)pblock;

#ifdef NATC
//#if 0
    vcop_calc_new_lk_xy_cn(
      (int *)Context->pInBlock[0],
      (int *)Context->pInBlock[1],
      (short *)Context->pInBlock[4],
      (short *)Context->pInBlock[5],
      (short *)Context->pInBlock[6],
      (unsigned short *)Context->pInBlock[7],
      (unsigned short *)Context->pInBlock[8],
      (unsigned short *)Context->pInBlock[10],
      (unsigned short *)Context->pInBlock[11],
      (unsigned char *)Context->pInBlock[12],
      Context->kernelArgs.qFormatePel,
      Context->kernelArgs.minErrValue,
      Context->kernelArgs.searchRange,
      Context->kernelArgs.numBlocks
      );
#else
    vcop_calc_new_lk_xy(
      Context->pInBlock[0],          
      Context->pInBlock[1],          
      Context->pInBlock[2],          
      Context->pInBlock[3],          
      Context->pInBlock[4],          
      Context->pInBlock[5],          
      Context->pInBlock[6],          
      Context->pInBlock[7],          
      Context->pInBlock[8],          
      Context->pInBlock[9],          
      Context->pInBlock[10],          
      Context->pInBlock[11],          
      Context->pInBlock[12],          
      Context->pInBlock[13],          
      Context->pInBlock[14],          
      Context->pInBlock[15],          
      Context->pInBlock[16],          
      Context->pInternalBlock[0],    
      Context->pInternalBlock[1],  
      Context->kernelArgs.qFormatePel,
      Context->kernelArgs.minErrValue,
      Context->kernelArgs.searchRange, 
      Context->kernelArgs.numBlocks 
      );
#endif
}

unsigned int vcop_calc_new_lk_xy_param_count(void)
{
    return (sizeof(vcop_calc_new_lk_xy_Context));
}

#endif
