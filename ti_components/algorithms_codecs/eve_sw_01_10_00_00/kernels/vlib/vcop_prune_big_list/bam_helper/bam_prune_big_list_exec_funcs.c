/*==========================================================================*/
/*      Copyright (C) 2009-2014 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_prune_big_list_exec_funcs.c
 *  @version 0.0 (Dec 2013) : Base version.
 *  @version 0.1 (May 2014) : Updated as per control node requirements
 *  @version 0.2 (Sept 2014) : Updated to add predication based on threshold
 *  @brief      This file defines interfaces for integrating prune
 *              big list function into BAM.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_prune_big_list_int.h"
#include "vcop_prune_big_list_kernel.h" /* compiler should take care of include path */

/* Function Prototypes */
static BAM_Status Bam_Prune_Big_List_initFrame(void *kernelContext);
static BAM_Status Bam_Prune_Big_List_initInstance(void *kernelContext);

static BAM_Status Bam_Prune_Big_List_initInstance(void *kernelContext)
{
    BAM_Prune_Big_List_Context *context = (BAM_Prune_Big_List_Context *) kernelContext;
    context->pInBlockBase_INDEX_LIST = context->pInBlock[INDEX_LIST_IDX];
    return 0 ;
}

static BAM_Status Bam_Prune_Big_List_initFrame(void *kernelContext)
{
    BAM_Prune_Big_List_Context *context = (BAM_Prune_Big_List_Context *) kernelContext;
    BAM_Status status = 0;
    uint16_t *pUpdate;
    context->pInBlock[INDEX_LIST_IDX] = context->pInBlockBase_INDEX_LIST ;

    /* CHECK_MISRA("-17.1,17.4")  -> Disable rule 17.1,17.4  */
    /* Pointer arithmetic is needed here to update the output pointer */
    /* The harmful side effect of voilating this rule (accessing outside valid memory) */
    /* shall be checked by another code checker like Klocwork */
    pUpdate = (uint16_t *)(context->pInBlock[INDEX_LIST_IDX])+((context->kernelArgs.offset)*2);
    /* RESET_MISRA("17.1,17.4")  -> Reset rule 17.1,17.4  */

    context->pInBlock[INDEX_LIST_IDX] = pUpdate;

#if (!VCOP_HOST_EMULATION)

    vcop_prune_big_list_init((uint32_t*)context->pInBlock[IN_LIST_IDX],
                             (uint16_t*)context->pInBlock[INDEX_LIST_IDX],
                             (uint32_t*)context->pInBlock[INDEX_LIST_IDX],
                             (uint32_t*)context->pOutBlock[OUT_LIST_IDX],
                             (uint32_t*)context->pOutBlock[OUT_LIST_SIZE],
                             context->kernelArgs.threshold,
                             context->kernelArgs.bestNFeaturesOut,
                             (uint16_t*)context->pInternalBlock[PARAMS_IDX]);
#endif

    return status;
}

#if VCOP_HOST_EMULATION
static BAM_Status Bam_Prune_Big_List_compute(void *kernelContext);

static BAM_Status Bam_Prune_Big_List_compute(void *kernelContext)
{
    BAM_Prune_Big_List_Context *context = (BAM_Prune_Big_List_Context *) kernelContext;
    vcop_prune_big_list((uint32_t*)context->pInBlock[IN_LIST_IDX],
                        (uint16_t*)context->pInBlock[INDEX_LIST_IDX],
                        (uint32_t*)context->pInBlock[INDEX_LIST_IDX],
                        (uint32_t*)context->pOutBlock[OUT_LIST_IDX],
                        (uint32_t*)context->pOutBlock[OUT_LIST_SIZE],
                        context->kernelArgs.threshold,
                        context->kernelArgs.bestNFeaturesOut);
    return 0;
}
#endif

static BAM_Status Bam_Prune_Big_List_control(void *kernelContext, void *kernelCtlArg);
static BAM_Status Bam_Prune_Big_List_control(void *kernelContext, void *kernelCtlArg)
{
    BAM_Prune_Big_List_Context *context = (BAM_Prune_Big_List_Context *) kernelContext;
    BAM_Prune_Big_List_ctrlArgs *ctlArg = (BAM_Prune_Big_List_ctrlArgs *) kernelCtlArg;
    BAM_Status status = 0;

    context->kernelArgs.bestNFeaturesOut = ctlArg->bestNFeaturesOut;
    context->kernelArgs.offset = ctlArg->offset;

    return status;
} 


BAM_KernelExecFuncDef gBAM_TI_prune_big_listExecFunc =
#if (!VCOP_HOST_EMULATION)
    {&Bam_Prune_Big_List_initInstance, &Bam_Prune_Big_List_initFrame, NULL, NULL, &Bam_Prune_Big_List_control, &vcop_prune_big_list_vloops};
#else
    {&Bam_Prune_Big_List_initInstance, &Bam_Prune_Big_List_initFrame, &Bam_Prune_Big_List_compute, NULL, &Bam_Prune_Big_List_control, NULL};
#endif

