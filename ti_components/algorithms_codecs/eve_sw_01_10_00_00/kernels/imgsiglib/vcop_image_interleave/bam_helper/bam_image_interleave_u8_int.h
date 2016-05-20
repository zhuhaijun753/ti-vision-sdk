/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_image_pyramid_u8_int.h
 *
 *  @brief      This header defines internal structures for one level puramid function used for integrating into BAM
 */

#include <stdint.h>
#include <vcop.h>

#include "evealgframework.h"
#include "bam_image_interleave_u8.h"

#define NUM_IN_BLOCKS 2
#define NUM_OUT_BLOCKS 1
#define NUM_INTERNAL_BLOCKS 1

#define Y_IDX  BAM_IMAGE_INTERLEAVE_U8_INPUT_PORT1
#define UV_IDX BAM_IMAGE_INTERLEAVE_U8_INPUT_PORT2
#define PARAMS_IDX 0

typedef struct _bam_image_interleave_u8_context
{
    /* Must always follow this order: pInternalBlock[], pInBlock[], pOutputBlock[], args */
    void *pInternalBlock[NUM_INTERNAL_BLOCKS];
    void *pInBlock[NUM_IN_BLOCKS];
    void *pOutBlock[NUM_OUT_BLOCKS];
    BAM_Image_Interleave_U8_Args kernelArgs;
} BAM_Image_Interleave_U8_Context;
