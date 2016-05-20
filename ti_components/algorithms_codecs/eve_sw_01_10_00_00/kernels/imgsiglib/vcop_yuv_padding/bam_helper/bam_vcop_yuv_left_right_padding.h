/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_vcop_yuv_left_right_padding.h
 *
 *  @brief      This header defines interfaces for integrating YUV
 *              padding into BAM.
 */

#ifndef BAM_VCOP_YUV_PADDING_H_
#define BAM_VCOP_YUV_PADDING_H_

typedef struct
{
	uint16_t width;
	uint16_t height;
	uint16_t out_stride;
} BAM_yuvLeftRightPadding_Args;

extern BAM_KernelHelperFuncDef gBAM_TI_yuvLeftRightPaddingHelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_yuvLeftRightPaddingExecFunc;

extern BAM_KernelInfo gBAM_TI_yuvLeftRightPaddingKernel;

#define BAM_YUV_PADDING_INPUT_PORT_LEFT              (0)
#define BAM_YUV_PADDING_INPUT_PORT_RIGHT             (1)
#define BAM_YUV_PADDING_CHROMA_INPUT_PORT_LEFT       (2)
#define BAM_YUV_PADDING_CHROMA_INPUT_PORT_RIGHT      (3)
#define BAM_YUV_PADDING_OUTUT_PORT_LEFT              (0)
#define BAM_YUV_PADDING_OUTUT_PORT_RIGHT             (1)
#define BAM_YUV_PADDING_CHROMA_OUTUT_PORT_LEFT       (2)
#define BAM_YUV_PADDING_CHROMA_OUTUT_PORT_RIGHT      (3)
 
 

#endif /* BAM_VCOP_YUV_PADDING_H_ */
