/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*                                                                          */
/*     @file : vcop_block_statistics_host.c                                 */
/*                                                                          */
/*     @brief : This file is being added to enable host emulation support   */
/*     with minimal changes to existing test code. Basically, this file     */
/*     re-implements the auto generated kernel C functions namely the init  */
/*     and vloops for the kernel.                                           */
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

#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include "vcop.h"

#if VCOP_HOST_EMULATION
#include "vcop_block_statistics_kernel.k"

static unsigned char     *gim_A;
static unsigned short     gblockStride;
static unsigned short     gblockWidth;
static unsigned short     gblockHeight;
static unsigned short     gstatBlockWidth;
static unsigned short     gstatBlockHeight;
static unsigned char     *gscratch_C;
static unsigned short    *gscratchSum_A;
static unsigned int      *gscratchSumSq_B;
static unsigned int      *gscratchSumSq_C;
static unsigned short    *gscratchSumSq_C_lo;
static unsigned short    *gscratchSumSq_C_hi;
static unsigned char     *gmin_B;
static unsigned char     *gmax_B;
static unsigned short    *gmean_B;
static unsigned int      *gvariance_A;

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
   unsigned short   *pblock)
{
   int retVal = 0;

    gim_A = im_A;
    gblockStride = blockStride;
    gblockWidth = blockWidth;
    gblockHeight = blockHeight;
    gstatBlockWidth = statBlockWidth;
    gstatBlockHeight = statBlockHeight;
    gscratch_C = scratch_C;
    gscratchSum_A = scratchSum_A;
    gscratchSumSq_B = scratchSumSq_B;
    gscratchSumSq_C = scratchSumSq_C;
    gscratchSumSq_C_lo = scratchSumSq_C_lo;
    gscratchSumSq_C_hi = scratchSumSq_C_hi;
    gmin_B = min_B;
    gmax_B = max_B;
    gmean_B = mean_B;
    gvariance_A = variance_A;

   return retVal;
}

void vcop_block_statistics_vloops(
   unsigned short   *pblock)
{
   vcop_block_statistics(gim_A, gblockStride, gblockWidth, gblockHeight,
                         gstatBlockWidth, gstatBlockHeight, gscratch_C,
                         gscratchSum_A, gscratchSumSq_B, gscratchSumSq_C,
                         gscratchSumSq_C_lo, gscratchSumSq_C_hi, gmin_B,
                         gmax_B, gmean_B, gvariance_A);
}

#endif
