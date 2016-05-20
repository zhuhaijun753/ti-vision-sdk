/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_image_pyramid_uv_u8_int.h
 *
 *  @brief      This header defines interfaces for integrating one level puramid function into BAM
 */

#include <stdint.h>
#include <vcop.h>

#include "evealgframework.h"
#include "bam_image_pyramid_uv_u8.h"

#define NUM_IN_BLOCKS 1
#define NUM_OUT_BLOCKS 1
#define NUM_INTERNAL_BLOCKS 1

#define PARAMS_IDX 0

typedef struct _bam_image_pyramid_uv_u8_context
{
    /* Must always follow this order: pInternalBlock[], pInBlock[], pOutputBlock[], args */
    void *pInternalBlock[NUM_INTERNAL_BLOCKS];
    void *pInBlock[NUM_IN_BLOCKS];
    void *pOutBlock[NUM_OUT_BLOCKS];
    BAM_Image_Pyramid_UV_U8_Args kernelArgs;
} BAM_Image_Pyramid_UV_U8_Context;
