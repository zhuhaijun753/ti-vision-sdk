/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
* @file bam_image_subSampling_helper_funcs.h
*
* @brief
*
* @author Gajanan Ambi(gajanan.ambi@ti.com)
*
* @version 0.0 (November 2012) : Base version.
*/
#include <vcop.h>

#include "evealgframework.h"
#include "bam_image_subSampling.h"

#define NUM_IN_BLOCKS 1
#define NUM_OUT_BLOCKS 1
#define NUM_INTERNAL_BLOCKS 1

#define PARAMS_IDX 0

typedef struct _bam_image_subsampling_context
{
    /* Must always follow this order: pInternalBlock[], pInBlock[], pOutputBlock[], args */
    void *pInternalBlock[NUM_INTERNAL_BLOCKS];
    void *pInBlock[NUM_IN_BLOCKS];
    void *pOutBlock[NUM_OUT_BLOCKS];
    ISP_BAM_Image_subSampling_Args  kernelArgs;
} BAM_Image_subSampling_Context;

