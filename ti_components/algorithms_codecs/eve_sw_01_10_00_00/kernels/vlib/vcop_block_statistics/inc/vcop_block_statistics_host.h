/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*                                                                          */
/*     @file : vcop_block_statistics_host.h                                 */
/*                                                                          */
/*     @brief : This file is being added to enable host emulation support   */
/*     with minimal changes to existing test code. Basically, this file     */
/*     re-implements the auto generated kernel C functions namely the init  */
/*     and vloops for the kernel                                            */
/*                                                                          */
/*     Host emulation wrapper functions for block statistics:               */
/*           vcop_block_statistics_init - Copies arguments to global        */
/*             variables                                                    */
/*           vcop_block_statistics_vloops - Invokes the API namely          */
/*             vcop_block_statistics defined in kernel file by passing the  */
/*             arguments from global variables backup                       */
/*                                                                          */
/*  @author Anoop K P(a-kp@ti.com)                                          */
/*                                                                          */
/*  @version 1.0 (Sept 2013) : Base version.                                */
/*                                                                          */
/*==========================================================================*/

#ifndef _VCOP_BLOCK_STATISTICS_HOST
#define _VCOP_BLOCK_STATISTICS_HOST  1

#include "vcop_host.h"

#if VCOP_HOST_EMULATION

/* Dummy Parameter Register Block For Enabling Host Emulation Support */
unsigned short __pblock_vcop_block_statistics[1];

unsigned int vcop_block_statistics_init(
    unsigned char   *im_A,
    unsigned short   blockStride,
    unsigned short   blockWidth,
    unsigned short   blockHeight,
    unsigned short   statBlockWidth,
    unsigned short   statBlockHeight,
    unsigned char   *scratch_C,
    unsigned short  *scratchSum_A,
    unsigned int    *scratchSumSq_B,
    unsigned int    *scratchSumSq_C,
    unsigned short  *scratchSumSq_C_lo,
    unsigned short  *scratchSumSq_C_hi,
    unsigned char   *min_B,
    unsigned char   *max_B,
    unsigned short  *mean_B,
    unsigned int    *variance_A,
   unsigned short   *pblock);

void vcop_block_statistics_vloops(
   unsigned short  *pblock);

#endif

#endif

