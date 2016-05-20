/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_gradXYmag_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating gradXYmag into a BAM graph
 */

#include <stdio.h>
#include <stdlib.h>

#include "evealgframework.h"
#include "bam_gradXYmag_int.h"
#include "vcop_vec_gradients_xy_and_magnitude_kernel.h"

/* Function Prototypes */
static BAM_Status BAM_gradXYmag_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks);

static BAM_Status BAM_gradXYmag_getMemRecFunc(const void *kernelArgs, BAM_MemRec internalBlock[],
        BAM_MemRec outBlock[], uint8_t *numInternalBlocks, uint8_t *numOutBlocks)
{

    BAM_Status status= BAM_S_SUCCESS;

#if !(VCOP_HOST_EMULATION)
    const BAM_GradXYmag_Args *args = kernelArgs;
    if(args->gradientMethod == (uint8_t)EVE_VLIB_GRADIENT_MAGNITUDE_SAT_8BITS)
    {
        internalBlock[PARAMS_IDX].size = 2u*vcop_vec_gradients_xy_and_magnitude_param_count();
    }
    else {
        if(args->gradientMethod == (uint8_t)EVE_VLIB_GRADIENT_MAGNITUDE_9BITS)
        {
            internalBlock[PARAMS_IDX].size = 2u*vcop_vec_gradients_xy_magnitudeu8_param_count();
        }
    }
#else
    const BAM_GradXYmag_Args *args = (const BAM_GradXYmag_Args *)kernelArgs;
    internalBlock[PARAMS_IDX].size = 4u;
#endif

    if(args->gradientMethod >= (uint8_t)EVE_VLIB_GRADIENT_MAGNITUDE_MAX)
    {
        status= BAM_E_FAIL;
    }
    else {
        /* The size of the output block size of args->width*(args->height-2) is rounded up to the next multiple of 2*SIMD_WIDTH
         * because the kernel-C implementation align the amount of produced output to 2*SIMD_WIDTH for best performance
         */
        outBlock[OUT_X_IDX].size = 2u*ALIGN_2SIMD(args->width*args->height);
        /* During performance fine-tuning of harris-corner applet, we concluded that larger blocks can be allocated if this output memory record goes to WBUF
         * This improvement may only be meaningful in the case of harris-corner applet. For other applet, try first with the below line removed.
         * */
        outBlock[OUT_X_IDX].space= BAM_MEMSPACE_ANY_VCOPBUF;
        outBlock[OUT_Y_IDX].size = 2u*ALIGN_2SIMD(args->width*args->height);
        outBlock[OUT_Y_IDX].space= BAM_MEMSPACE_ANY_VCOPBUF;

        if(args->gradientMethod == (uint8_t)EVE_VLIB_GRADIENT_MAGNITUDE_9BITS )
        {
            outBlock[OUT_MAG_IDX].size = 2u*ALIGN_2SIMD(args->width*args->height);
        }
        else {
            if(args->gradientMethod == (uint8_t)EVE_VLIB_GRADIENT_MAGNITUDE_SAT_8BITS )
            {
                outBlock[OUT_MAG_IDX].size = ALIGN_2SIMD(args->width*args->height);
            }
        }
        outBlock[OUT_MAG_IDX].space= BAM_MEMSPACE_ANY_VCOPBUF;
    }

    return status;
}

BAM_KernelInfo gBAM_TI_gradXYmagKernel =
{
        0,                                      /* kernelId */
        sizeof(BAM_GradXYmag_Context),
        sizeof(BAM_GradXYmag_Args),
        BAM_EVE,                                /* coreType */
        BAM_NODE_COMPUTE,                       /* nodeType */
        NUM_IN_BLOCKS,                          /* 1 */
        NUM_OUT_BLOCKS,                         /* 3 */
        NUM_INTERNAL_BLOCKS                     /* 1 */
};

BAM_KernelHelperFuncDef gBAM_TI_gradXYmagHelperFunc =
{ &BAM_gradXYmag_getMemRecFunc, NULL};

