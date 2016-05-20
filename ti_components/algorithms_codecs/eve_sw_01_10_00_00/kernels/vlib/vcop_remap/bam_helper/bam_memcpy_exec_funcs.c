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

#include "bam_memcpy_int.h"
#include "bam_memcpy.h"
#include "vcop_memcpy.h"
#include "remap_common.h"
#include "remap.h"

/* Function Prototypes */

static BAM_Status Bam_Memcpy_initFrame(void *kernelContext);

static BAM_Status Bam_Memcpy_initFrame(void *kernelContext)
{
    BAM_Memcpy_Context  *context     = (BAM_Memcpy_Context *) kernelContext;
    BAM_Memcpy_Args     *args        = (BAM_Memcpy_Args *)&(context->kernelArgs);
    uint16_t blocksize;
    Format   format;

    format    = args->format;
    blocksize = args->width*args->height*sizeofFormat(format);

    if (format == YUV_420SP)
    {
        blocksize         = (3U*blocksize)/2U;
    }

#if (!VCOP_HOST_EMULATION)
    vcop_memcpy_init((uint32_t *)context->pInBlock[MEMCPY_INPUT_BLOCK_PTR_IDX],
                     (uint32_t *)context->pOutBlock[MEMCPY_OUTPUT_BLOCK_PTR_IDX],
                     blocksize,
                     (uint16_t *)context->pInternalBlock[MEMCPY_PBLOCK_PTR_IDX]);
#endif
    return BAM_S_SUCCESS;
}


#if (VCOP_HOST_EMULATION)
static BAM_Status Bam_Memcpy_compute(void *kernelContext);

static BAM_Status Bam_Memcpy_compute(void *kernelContext)
{
    BAM_Memcpy_Context  *context     = (BAM_Memcpy_Context *) kernelContext;
    BAM_Memcpy_Args     *args        = (BAM_Memcpy_Args *)&(context->kernelArgs);
    uint32_t blocksize;
    Format   format;

    format    = args->format;
    blocksize = args->width*args->height*sizeofFormat(format);

    if (format == YUV_420SP)
    {
        blocksize         = (3U*blocksize)/2U;
    }

    vcop_memcpy(context->pInBlock[MEMCPY_INPUT_BLOCK_PTR_IDX], context->pOutBlock[MEMCPY_OUTPUT_BLOCK_PTR_IDX], blocksize);

    return BAM_S_SUCCESS;
}
#else
static BAM_Status Bam_Memcpy_compute(void *kernelContext);

static BAM_Status Bam_Memcpy_compute(void *kernelContext)
{
    BAM_Memcpy_Context  *context     = (BAM_Memcpy_Context *) kernelContext;
    vcop_memcpy_vloops((uint16_t*)context->pInternalBlock[MEMCPY_PBLOCK_PTR_IDX]);

    return BAM_S_SUCCESS;
}
#endif


BAM_KernelExecFuncDef gBAM_TI_memcpyExecFunc =
#if (VCOP_HOST_EMULATION || NATC)
    { NULL, &Bam_Memcpy_initFrame, &Bam_Memcpy_compute, NULL, NULL, NULL };
#else
    { NULL, &Bam_Memcpy_initFrame, &Bam_Memcpy_compute, NULL, NULL, &vcop_memcpy_vloops};
#endif

