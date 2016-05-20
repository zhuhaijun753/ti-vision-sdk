/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*                                                                          */
/*     @file : vcop_median_filter_mxn_u8_host.c                             */
/*                                                                          */
/*     @brief : This file is being added to enable host emulation support   */
/*     with minimal changes to existing test code. Basically, this file     */
/*     re-implements the auto generated kernel C functions namely the init  */
/*     and vloops for the underlying kernels.                               */
/*                                                                          */
/*     Host emulation wrapper functions for median filter:                  */
/*     1. vcop_update_block_histogram_8c                                    */
/*           vcop_update_block_histogram_8c_init - Copies arguments to      */
/*             global variables                                             */
/*           vcop_update_block_histogram_8c_vloops - Invokes the API namely */
/*             vcop_update_block_histogram_8c defined in kernel file by     */
/*             passing the arguments from global variables backup           */
/*     2. vcop_select_kth_smallest_from_hist                                */
/*           vcop_select_kth_smallest_from_hist_init - Copies arguments to  */
/*             global variables                                             */
/*           vcop_select_kth_smallest_from_hist_vloops - Invokes the API    */
/*             namely vcop_select_kth_smallest_from_hist defined in kernel  */
/*             file by passing the arguments from global variables backup.  */
/*                                                                          */
/*  @author Anoop K P(a-kp@ti.com)                                          */
/*                                                                          */
/*  @version 1.0 (Sept 2013) : Base version.                                */
/*                                                                          */
/*==========================================================================*/

#ifndef _VCOP_MEDIAN_FILTER_HOST
#define _VCOP_MEDIAN_FILTER_HOST  1

#include "vcop_host.h"

#if VCOP_HOST_EMULATION

unsigned int vcop_update_block_histogram_8c_init(
    unsigned char  *inp_data_A,
    unsigned char  *last_strip_A,
    short          *histo_B,
    char           *wgt_ones_C,
    char           *wgt_delta_C,
    short          *scratch_histo_C,
    short          *blk_histo_B,
    unsigned int    blk_wdth,
    unsigned int    blk_hght,
    unsigned int    blk_stride,
    unsigned short   *pblock);

void vcop_update_block_histogram_8c_vloops(
   unsigned short  *pblock);
   
unsigned int vcop_update_block_histogram_8c_param_count(void);

unsigned int vcop_select_kth_smallest_from_hist_init(
    short          *blk_histo_B,
    short          *coarse_hist_scratch_A,
    short          *hist_scratch_C,
    unsigned char  *optr_A,
    unsigned short  k,
    unsigned short *pblock);

void vcop_select_kth_smallest_from_hist_vloops(
   unsigned short   *pblock);

unsigned int vcop_select_kth_smallest_from_hist_param_count(void);

#endif

#endif

