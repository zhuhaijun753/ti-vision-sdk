/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 ********************************************************************************
 * @file:      bam_image_filter_helper_funcs.h
 *
 * @brief:    This file defines functions for integrating rgb2yuv kernels into BAM
 *
 * @author:  Gajanan Ambi(gajanan.ambi@ti.com)
 *
 * @version:  0.0 (Feb 2013) : Base version.
 ********************************************************************************
 */

#include "bam_image_filter.h"
#include <vcop.h>

#define NUM_IN_BLOCKS 1
#define NUM_OUT_BLOCKS 1
#define NUM_INTERNAL_BLOCKS 2

#define PARAMS_IDX 0
#define COEFFS_IDX 1

typedef struct _bam_image_filter_context
{
    /* Must always follow this order: pInternalBlock[], pInBlock[], pOutputBlock[], args */
    void *pInternalBlock[NUM_INTERNAL_BLOCKS];
    void *pInBlock[NUM_IN_BLOCKS];
    void *pOutBlock[NUM_OUT_BLOCKS];
    BAM_Image_filter_Args kernelArgs;
} BAM_Image_filter_Context;

