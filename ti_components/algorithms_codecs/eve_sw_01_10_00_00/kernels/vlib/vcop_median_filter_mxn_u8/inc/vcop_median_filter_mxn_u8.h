/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file   vcop_median_filter_mxn_u8.h
 *
 *  @brief  Interface for histogram-sort based median filtering with
 *          large filtering kernels.
 *
 */

/*#define __DEBUG */

#ifndef VCOP_MEDIAN_FILTER_MXN_U8_H_
#define VCOP_MEDIAN_FILTER_MXN_U8_H_

typedef struct median_filter_context
{
    uint16_t *pBlockHist;
    uint16_t *pBlockSelect;
#ifdef __DEBUG
    int16_t *pBlk_hist_C;
#endif

} median_kernel_context;

uint32_t vcop_large_kernel_median_wrapper_param_count(void);

void vcop_large_kernel_median_wrapper_init
(
    uint8_t   pInput_A[],
    uint8_t   pMedian_B[],
    uint16_t  blkPitch,
    uint16_t  blkWidth,
    uint16_t  blkHeight,
    uint8_t   kernelWidth,
    uint8_t   kernelHeight,
    uint16_t  stepSizeHorz,
    uint16_t  stepSizeVert,
    int16_t   histo_C[],                /* 4096 bytes */
    int8_t    scratch_wgt_B[],          /* 16 bytes */
    int16_t   scratch_histo_B[],        /* 8*36*8 bytes */
    int16_t   blk_hist_C[],             /* 18*16 bytes */
    int16_t   coarse_hist_scratch_A[],  /* 2*16 bytes */
    uint16_t *pBlock,
    median_kernel_context *context
);

void vcop_large_kernel_median_wrapper_vloops(median_kernel_context *context);

#endif /* VCOP_MEDIAN_FILTER_MXN_U8_H_ */

