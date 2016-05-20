/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 ********************************************************************************
 * @file:      bam_image_filter.h
 *
 * @brief:    This file defines functions for integrating filter kernels into BAM
 *
 * @author: Gajanan Ambi(gajanan.ambi@ti.com)
 *
 * @version: 0.0 (Feb 2013) : Base version.
 ********************************************************************************
 */

#ifndef BAM_IMAGE_FILTER_H_
#define BAM_IMAGE_FILTER_H_

#define INPUT_TYPE   0   /* 0 - uchar, 1 - char, 2 - ushort, 3 - short */
#define COEF_TYPE    0   /* 0 - uchar, 1 - char, 2 - ushort, 3 - short*/
#define OUTPUT_TYPE  0   /* 0 - char, 1 - short, 2 - word */

#define UCHAR_TYPE  0
#define CHAR_TYPE   1 
#define USHORT_TYPE 2
#define SHORT_TYPE  3
#define INT_TYPE    4

typedef struct _isp_bam_image_filter_args
{
  int input_blk_width;
  int coeff_blk_width;
  int coeff_blk_height;
  int compute_blk_width;
  int compute_blk_height;
  int dnSmple_vert;
  int dnSmple_horz;
  int rnd_shift;
  int input_type;
  int coeff_type;
  int output_type;
  char *filter_coefs;
}BAM_Image_filter_Args;

extern BAM_KernelHelperFuncDef gBAM_TI_filterHelperFunc;
extern BAM_KernelExecFuncDef   gBAM_TI_filterExecFunc;

extern BAM_KernelInfo gBAM_TI_filterKernel;

#define BAM_IMAGE_FILTER_INPUT_PORT  0
#define BAM_IMAGE_FILTER_OUTPUT_PORT 0
#endif

