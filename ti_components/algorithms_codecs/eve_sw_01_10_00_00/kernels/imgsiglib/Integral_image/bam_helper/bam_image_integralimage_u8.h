/*
 * Copyright (c) 2011, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/**
* @file bam_image_integralimage_u8.h
*
* @brief
*
*  @author Kumar Desappan(kumar.desappan@ti.com)
*
* @version 0.0 (Jul 2013) : Base version.
*/


#ifndef BAM_IMAGE_INTEGRAL_IMAGE_UCHAR_H_
#define BAM_IMAGE_INTEGRAL_IMAGE_UCHAR_H_

#include "bam_common.h"


typedef struct
{
  uint16_t blk_width;
  uint16_t blk_height;
  uint16_t input_stride;
  uint16_t num_hor_blocks;
} BAM_Image_integralImage_u8_Args;

extern BAM_KernelHelperFuncDef gBAM_TI_integralImage_u8HelperFunc;
extern BAM_KernelExecFuncDef   gBAM_TI_integralImage_u8KernelExecFunc;

extern BAM_KernelInfo gBAM_TI_integralImage_u8Kernel;

#define BAM_INTEGRAL_IMAGE_TI_U8_INPUT_PORT_IN     (0)
#define BAM_INTEGRAL_IMAGE_TI_U8_INPUT_PORT_ACC_H  (1)


#define BAM_INTEGRAL_IMAGE_TI_U8_OUTPUT_PORT_OUT1   (0)
#define BAM_INTEGRAL_IMAGE_TI_U8_OUTPUT_PORT_OUT2   (1)


#endif /* BAM_IMAGE_INTEGRAL_IMAGE_U8_H_ */

