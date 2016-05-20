/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/* ===========================================================================*/
/*   @file : median_filter_cn.c                                               */
/*                                                                            */
/*   @brief  : This file contains all functions calls for median filtering    */
/*             reference                                                      */
/*                                                                            */
/*   @version 0.1 (Sept 2013) : Base version.                                 */
/*                                                                            */
/*============================================================================*/

#include "median_filter_cn.h"

/* Function prototypes */
void vcop_select_kth_smallest_from_hist_cn(short *hist_ptr, unsigned char *optr,
    unsigned short k);

void vcop_compute_block_histogram_8c_cn(unsigned char *inp_data, short *histo, 
    unsigned int blk_wdth, unsigned int blk_hght, unsigned int blk_stride);

void medianFilter_cn
(
    MEDIAN_FILTER_TI_CreateParams *createParams,
    uint16_t  imagePitch,
    uint8_t  *pInput,
    uint8_t  *pMedian,
    int16_t  *histo
)
{
    int i, j;
    unsigned short out_width, out_height;

    out_width = ((createParams->imageWidth - createParams->blockWidth)/createParams->stepSizeHorz) + 1;
    out_height = ((createParams->imageHeight - createParams->blockHeight)/createParams->stepSizeVert) + 1;

    for(i = 0; i < out_height; i++) {
        for(j = 0; j < out_width; j++) {
            vcop_compute_block_histogram_8c_cn(&(pInput[i*createParams->stepSizeVert*imagePitch + j*createParams->stepSizeHorz]),
                                              histo, createParams->blockWidth, createParams->blockHeight, imagePitch);
            vcop_select_kth_smallest_from_hist_cn(histo, &pMedian[i*out_width+j],
                                              (createParams->blockWidth*createParams->blockHeight+1)/2);
        }
    }

    return;
}


void vcop_select_kth_smallest_from_hist_cn
(
    short           *hist_ptr,         /* Transposed histogram: 16 bins of 16-bit values in each row */
    unsigned char   *optr,             /* Output data pointer: 1 8-bit value */
    unsigned short   k                 /* Order statistic required */
)
{
    int i, hist_sum;

    hist_sum = 0;
    for(i = 0; i < 256; i++) {
        hist_sum += hist_ptr[i];
        if(hist_sum >= k) {
            *optr = i;
            break;
        }
    }

    return;
}


void vcop_compute_block_histogram_8c_cn
(
    unsigned char   *inp_data,    /* Block input */
    short           *histo,       /* Block histogram array output: 256 bins of 16-bit values */
    unsigned int     blk_wdth,
    unsigned int     blk_hght,
    unsigned int     blk_stride
)
{
    int i, j;

    memset(histo, 0, 8*2*256);

    for(i = 0; i < blk_hght; i++) {
        for(j = 0; j < blk_wdth; j++) {
            histo[inp_data[i*blk_stride+j]]++;
        }
    }
}

