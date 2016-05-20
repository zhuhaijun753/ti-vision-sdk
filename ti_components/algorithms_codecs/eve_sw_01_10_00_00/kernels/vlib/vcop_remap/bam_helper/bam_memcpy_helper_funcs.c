/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_median_filter_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating fast9 kernel
 *              into BAM
 */

#include <stdio.h>
#include <stdlib.h>

#include "evealgframework.h"

#include "bam_memcpy_int.h"
#include "bam_memcpy.h"
#include "vcop_memcpy.h"

/* CHECK_MISRA("-19.7")  -> Disable rule 19.7  */
/* These are simple non-harmful macros.   */
#define ALIGN_4SIMD(a)    (((a) + 4U*VCOP_SIMD_WIDTH-1U) & ~(4U*VCOP_SIMD_WIDTH-1U))
/* RESET_MISRA("19.7")  -> Reset rule 19.7     */


/* Function Prototypes */
static BAM_Status BAM_Memcpy_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks);


static BAM_Status BAM_Memcpy_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks)
{
#if (VCOP_HOST_EMULATION)
    const BAM_Memcpy_Args *args = (const BAM_Memcpy_Args *)kernelArgs;
#else
    /* Typecasting by (const BAM_Memcpy_Args *) will lead to MISRA C 11.5. */
    const BAM_Memcpy_Args *args = kernelArgs;
#endif
    Format           format;

    format    = args->format;

#if (!VCOP_HOST_EMULATION)
    internalBlock[MEMCPY_PBLOCK_PTR_IDX].size = vcop_memcpy_param_count() * sizeof(__pblock_vcop_memcpy[0]);
#else
    internalBlock[MEMCPY_PBLOCK_PTR_IDX].size = 4U;
#endif
    internalBlock[MEMCPY_PBLOCK_PTR_IDX].attrs.memAttrs    = BAM_MEMATTRS_SCRATCH;
    internalBlock[MEMCPY_PBLOCK_PTR_IDX].space             = BAM_MEMSPACE_WBUF;

    /* Memory for Remapped Output */
    outBlock[MEMCPY_OUTPUT_BLOCK_PTR_IDX].size              = (uint32_t)sizeofFormat(format) * ALIGN_4SIMD(args->width * args->height);
    outBlock[MEMCPY_OUTPUT_BLOCK_PTR_IDX].alignment         = 32U;
    outBlock[MEMCPY_OUTPUT_BLOCK_PTR_IDX].attrs.memAttrs    = BAM_MEMATTRS_SCRATCH;
    outBlock[MEMCPY_OUTPUT_BLOCK_PTR_IDX].space             = BAM_MEMSPACE_IBUFHA;
    if(format == YUV_420SP)
    {
        outBlock[MEMCPY_OUTPUT_BLOCK_PTR_IDX].size         += ((ALIGN_4SIMD(args->width * args->height))/2U);
    }
    return BAM_S_SUCCESS;
}


BAM_KernelInfo gBAM_TI_memcpyKernel =
{
    0,                                      /* kernelId */
    sizeof(BAM_Memcpy_Context),
    sizeof(BAM_Memcpy_Args),
    BAM_EVE,                                /* coreType */
    BAM_NODE_COMPUTE,                       /* nodeType */
    MEMCPY_NUM_IN_BLOCKS,                    /* 1 */
    MEMCPY_NUM_OUT_BLOCKS,                   /* 1 */
    MEMCPY_NUM_INTERNAL_BLOCKS               /* 1 */
};

BAM_KernelHelperFuncDef gBAM_TI_memcpyHelperFunc =
{ &BAM_Memcpy_getMemRecFunc, NULL};

