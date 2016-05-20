/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/


/**
 * @file isp_bam_image_bayer2rgb_Helper_Funcs.h
 *
 * @brief
 * @author Gajanan Ambi(gajanan.ambi@ti.com)
 * @version 0.0 (November 2012) : Base version.
 */

#include "evealgframework.h"
#include "bam_image_bayer2rgb.h"
#include <vcop.h>

#define NUM_IN_BLOCKS 1
#define NUM_OUT_BLOCKS 3
#define NUM_INTERNAL_BLOCKS 1

#define IN_IDX 0

#define OUT_R_IDX BAM_IMAGE_BAYER2RGB_OUTPUT_PORT_R /* 0 */
#define OUT_G_IDX BAM_IMAGE_BAYER2RGB_OUTPUT_PORT_G /* 1 */
#define OUT_B_IDX BAM_IMAGE_BAYER2RGB_OUTPUT_PORT_B /* 2 */

#define PARAMS_IDX 0

#define BGGR 1
#define GRBG 2
#define RGGB 3
#define GBRG 4

typedef struct _bam_image_bayer2rgb_context
{
    /* Must always follow this order: pInternalBlock[], pInBlock[], pOutputBlock[], args */
    void *pInternalBlock[NUM_INTERNAL_BLOCKS];
    void *pInBlock[NUM_IN_BLOCKS];
    void *pOutBlock[NUM_OUT_BLOCKS];
    ISP_BAM_Image_Bayer2rgb_Args kernelArgs;
} BAM_Image_bayer2rgb_Context;

