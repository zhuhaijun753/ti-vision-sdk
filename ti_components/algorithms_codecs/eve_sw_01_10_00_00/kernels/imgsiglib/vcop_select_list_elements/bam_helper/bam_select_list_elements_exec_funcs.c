/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_select_list_elements_exec_funcs.c
 *
 *  @brief      This file implements interfaces for integrating select list elements
 *              kernel into BAM.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_select_list_elements_int.h"
#include "vcop_select_list_elements_kernel.h" /* compiler should take care of include path */

/* CHECK_MISRA("-19.7")  -> Disable rule 19.7  */
/* These are simple non-harmful macros.   */
#define BAM_SELECT_LIST_ELEMENTS_CEIL(x,y) ((( (x) + (y) - 1U) / (y)) * (y))
/* RESET_MISRA("19.7")  -> Reset rule 19.7  */

/* Function Prototypes */
static BAM_Status Bam_Select_list_elements_initFrame(void *kernelContext);

static BAM_Status Bam_Select_list_elements_initFrame(void *kernelContext)
{
    BAM_Select_list_elements_Context *context = (BAM_Select_list_elements_Context *) kernelContext;
    BAM_Status status = BAM_S_SUCCESS;
    uint16_t pReg4Val;
    uint16_t pReg14Val;

    if ( (context->ctrlArgs.selectionMaskSize % VCOP_SIMD_WIDTH) != 0 )
    {
      status = BAM_E_FAIL;
      /* CHECK_MISRA("-14.4")  -> Disable rule 14.4  */
      /* GOTO is used at error check to jump to end of function, to exit.   */
      goto EXIT;
      /* RESET_MISRA("14.4")  -> Reset rule 14.4     */

    }
    memcpy( context->pInternalBlock[SELECT_LIST_ELEMENTS_INTERNAL_SELECTION_MASK_PTR_IDX],
            context->ctrlArgs.selectionMaskPtr,
            context->ctrlArgs.selectionMaskSize * sizeof(uint8_t));

    context->blkIdx = 0;
    context->numBlks = BAM_SELECT_LIST_ELEMENTS_CEIL(context->ctrlArgs.listSize, context->ctrlArgs.listChunkSize) /
                          context->ctrlArgs.listChunkSize;

    context->numElemsInLaskBlk = context->ctrlArgs.listSize -
            ((context->numBlks - 1U) * context->ctrlArgs.listChunkSize);

    /* make the last list chunk size to be multiple of selectionMaskSize as per the requirement of the kernel */
    /* Because of this few extra corners will be detected whcih we should take care */
    context->numElemsInLaskBlk = BAM_SELECT_LIST_ELEMENTS_CEIL(context->numElemsInLaskBlk, context->ctrlArgs.selectionMaskSize);

#if (!VCOP_HOST_EMULATION)
      pReg4Val = ((context->numElemsInLaskBlk / context->ctrlArgs.selectionMaskSize))- (uint16_t)1U;
      pReg14Val = (uint16_t)0 - ((uint16_t)1U * (((context->ctrlArgs.selectionMaskSize*sizeof(uint32_t))*(((context->numElemsInLaskBlk /
                        context->ctrlArgs.selectionMaskSize))- (uint16_t)1U)) - (((uint16_t) 8U * sizeof(uint32_t)) *
                        (((context->ctrlArgs.selectionMaskSize / (uint16_t)(8U)))- (uint16_t)1U))));

      vcop_select_list_elements_init((uint32_t*)context->pInBlock[BAM_SELECT_LIST_ELEMENTS_INPUT_LIST_PORT],
                                 (uint32_t*)context->pOutBlock[BAM_SELECT_LIST_ELEMENTS_OUTPUT_LIST_PORT],
                                 (uint8_t*)context->pInternalBlock[SELECT_LIST_ELEMENTS_INTERNAL_SELECTION_MASK_PTR_IDX],
                                 (uint16_t*)context->pOutBlock[BAM_SELECT_LIST_ELEMENTS_OUTPUT_LIST_SIZE_PORT],
                                 context->ctrlArgs.listChunkSize,
                                 context->ctrlArgs.selectionMaskSize,
                                 (uint16_t*)context->pInternalBlock[SELECT_LIST_ELEMENTS_INTERNAL_PARAMS_IDX]);
      vcop_select_list_elements_param_block_update_init((uint16_t*)context->pInternalBlock[SELECT_LIST_ELEMENTS_INTERNAL_PARAMS_IDX],
                                                        pReg4Val,
                                                        pReg14Val,
                                                        (uint16_t*)context->pInternalBlock[SELECT_LIST_ELEMENTS_INTERNAL_PBLOCK_UPDATE_PARAMS_IDX]);

#endif
EXIT:

    return status;
}

static BAM_Status Bam_Select_list_elements_computeFrame(void *kernelContext);

static BAM_Status Bam_Select_list_elements_computeFrame(void *kernelContext)
{
    BAM_Select_list_elements_Context *context = (BAM_Select_list_elements_Context *) kernelContext;
#if VCOP_HOST_EMULATION
    uint16_t numElemsPerBlock;
    numElemsPerBlock = (context->blkIdx == context->numBlks - 1) ?
                         context->numElemsInLaskBlk :
                         context->ctrlArgs.listChunkSize;

    vcop_select_list_elements((uint32_t*)context->pInBlock[BAM_SELECT_LIST_ELEMENTS_INPUT_LIST_PORT],
                                 (uint32_t*)context->pOutBlock[BAM_SELECT_LIST_ELEMENTS_OUTPUT_LIST_PORT],
                                 (uint8_t*)context->pInternalBlock[SELECT_LIST_ELEMENTS_INTERNAL_SELECTION_MASK_PTR_IDX],
                                 (uint16_t*)context->pOutBlock[BAM_SELECT_LIST_ELEMENTS_OUTPUT_LIST_SIZE_PORT],
                                 numElemsPerBlock,
                                 context->ctrlArgs.selectionMaskSize);

#else
    vcop_select_list_elements_vloops((uint16_t*)context->pInternalBlock[SELECT_LIST_ELEMENTS_INTERNAL_PARAMS_IDX]);

    if( context->blkIdx == (context->numBlks - 2) )
    {
      vcop_select_list_elements_param_block_update_vloops((uint16_t*)context->pInternalBlock[SELECT_LIST_ELEMENTS_INTERNAL_PBLOCK_UPDATE_PARAMS_IDX]);
    }
#endif
    context->blkIdx++;

    return 0;

}


static BAM_Status Bam_Select_list_elements_control(void *kernelContext, void *kernelCtlArg);

static BAM_Status Bam_Select_list_elements_control(void *kernelContext, void *kernelCtlArg){

    BAM_Select_list_elements_Context *context   = (BAM_Select_list_elements_Context *) kernelContext;
    BAM_Select_list_elements_ctrlArgs *ctrlArgs = (BAM_Select_list_elements_ctrlArgs *) kernelCtlArg;
    BAM_Status status = BAM_S_SUCCESS;

    if ( (ctrlArgs->listChunkSize <= context->kernelArgs.maxListChunkSize) &&
          (ctrlArgs->selectionMaskSize <= context->kernelArgs.maxSelectionMaxSize) )
    {
      context->ctrlArgs = *ctrlArgs;
    }
    else
    {
      status = BAM_E_FAIL;
    }

    return status;
}


BAM_KernelExecFuncDef gBAM_TI_selecListElementsExecFunc =
{
    NULL,
    &Bam_Select_list_elements_initFrame,
    &Bam_Select_list_elements_computeFrame,
    NULL,
    &Bam_Select_list_elements_control,
    NULL
};

