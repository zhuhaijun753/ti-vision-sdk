/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_median_filter_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating fast9 kernel
 *              function into BAM.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_remap_merge_int.h"
#include "bam_remap_merge.h"


extern int8_t remapNumTiles;


/* Function Prototypes */
static BAM_Status Bam_RemapMerge_initFrame(void *kernelContext);
static BAM_Status Bam_RemapMerge_compute(void *kernelContext);

static BAM_Status Bam_RemapMerge_initFrame(void *kernelContext)
{

    BAM_Remap_Merge_Context            *context               =  (BAM_Remap_Merge_Context *)kernelContext;
    BAM_Remap_Context                  *remapContext          = &(context->remapContext);
    BAM_Memcpy_Context                 *memcpyContext         = &(context->memcpyContext);
    BAM_Yuv_420nv12_to_422uyvy_Context *formatConvertContext  = &(context->formatConvertContext);
    BAM_Alpha_Blend_YUV420nv12_Context *mergeContext          = &(context->mergeContext);
    BAM_Remap_Merge_Args               *args                  = &(context->kernelArgs);
    uint8_t numKernel = 0U, enableMerge, enableMemcpy = 1U;
    Format  srcFormat, dstFormat;

    srcFormat       = remapContext->kernelArgs.maps.srcFormat;
    dstFormat       = args->dstFormat;
    enableMerge     = args->enableMerge;

    context->initFuncList[numKernel](remapContext);

    context->pblockList[numKernel]    = remapContext;
    numKernel++;

    if(srcFormat != dstFormat)
    {
        enableMemcpy = 0;
        context->pblockList[numKernel]    = formatConvertContext;
        context->initFuncList[numKernel](formatConvertContext);
        numKernel++;
    }

    if(enableMerge == 1U)
    {
        enableMemcpy = 0;
        context->pblockList[numKernel]    = mergeContext;
        context->initFuncList[numKernel](mergeContext);
        numKernel++;

    }

    if(enableMemcpy == 1U)
    {
        context->pblockList[numKernel]    = memcpyContext;
        context->initFuncList[numKernel](memcpyContext);

    }

    return BAM_S_SUCCESS;
}



static BAM_Status Bam_RemapMerge_compute(void *kernelContext)
{
    BAM_Remap_Merge_Context            *context               =  (BAM_Remap_Merge_Context *)kernelContext;
    uint8_t i;

    /* Remap kernel to be called for every tile */
    context->vloopFuncList[0](context->pblockList[0]);

    /* (Format Convert [+] Merge)/Memcpy kernel to be called for every output block */
    if(remapNumTiles == 1)
    {
        for (i = 1U; i < context->numInitFunc; i++)
        {
            context->vloopFuncList[i](context->pblockList[i]);
        }
    }

    return BAM_S_SUCCESS;
}

BAM_KernelExecFuncDef gBAM_TI_remapMergeExecFunc =
    { NULL, &Bam_RemapMerge_initFrame, &Bam_RemapMerge_compute, NULL, NULL, NULL };


