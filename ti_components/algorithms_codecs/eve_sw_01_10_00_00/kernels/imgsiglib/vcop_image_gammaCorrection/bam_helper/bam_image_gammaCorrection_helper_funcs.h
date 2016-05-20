/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
* @file bam_image_gammaCorrection_helper_funcs.h
*
* @brief
*
* @author Gajanan Ambi(gajanan.ambi@ti.com)
*
* @version 0.0 (November 2012) : Base version.
*/
#include "evealgframework.h"
#include "bam_image_gammaCorrection.h"

#define NUM_IN_BLOCKS 3
#define NUM_OUT_BLOCKS 3
#define NUM_INTERNAL_BLOCKS 5

#define IN_R_IDX BAM_IMAGE_GAMMA_CORRECTION_INPUT_PORT_R /* 0 */
#define IN_G_IDX BAM_IMAGE_GAMMA_CORRECTION_INPUT_PORT_G /* 1 */
#define IN_B_IDX BAM_IMAGE_GAMMA_CORRECTION_INPUT_PORT_B /* 2 */

#define OUT_R_IDX BAM_IMAGE_GAMMA_CORRECTION_OUTPUT_PORT_R /* 0 */
#define OUT_G_IDX BAM_IMAGE_GAMMA_CORRECTION_OUTPUT_PORT_G /* 1 */
#define OUT_B_IDX BAM_IMAGE_GAMMA_CORRECTION_OUTPUT_PORT_B /* 2 */

#define PARAMS_IDX 0
#define TEMP_R_IDX 1
#define TEMP_G_IDX 2
#define TEMP_B_IDX 3
#define LUT_IDX    4

typedef struct _bam_image_gammacorrection_context
{
    void *pInternalBlock[NUM_INTERNAL_BLOCKS];
    void *pInBlock[NUM_IN_BLOCKS];
    void *pOutBlock[NUM_OUT_BLOCKS];
    ISP_BAM_Image_gammaCorrection_Args  kernelArgs;
} BAM_Image_gammaCorrection_Context;

