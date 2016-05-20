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
* @file bam_image_integralImage_u8_helper_funcs.h
*
* @brief
*
*  @author Kumar Desappan(kumar.desappan@ti.com)
*
* @version 0.0 (Jul 2013) : Base version.
*/
#ifndef BAM_IMAGE_INTEGRAL_U8_H_
#define BAM_IMAGE_INTEGRAL_U8_H_


#include "evealgframework.h"
#include "bam_image_integralimage_u8.h"
#include <vcop.h>
#include <stdint.h>

#define NUM_IN_BLOCKS         (2)
#define NUM_OUT_BLOCKS        (2)
#define NUM_INTERNAL_BLOCKS   (7)

#define IN_IMG_IDX            (0)
#define IN_HOR_ACC_IDX        (1)

#define OUT_INTG_IMG_IDX      (0)
#define OUT_HOR_ACC_IDX       (1)

#define PARAMS_IDX            (0)
#define PARAMS_RESET_ACCV_IDX (1)
#define SCRATCH_VER_ACC_IDX   (2)
#define SCRATCH_B0_IDX        (3)
#define SCRATCH_B1_IDX        (4)
#define SCRATCH_C0_IDX        (5)
#define SCRATCH_C1_IDX        (6)

typedef struct
{
    void *pInternalBlock[NUM_INTERNAL_BLOCKS];
    void *pInBlock[NUM_IN_BLOCKS];
    void *pOutBlock[NUM_OUT_BLOCKS];
    BAM_Image_integralImage_u8_Args  kernelArgs;
    uint16_t     currHorBlkIdx;
} BAM_Image_integralImage_u8_Context;

#endif

