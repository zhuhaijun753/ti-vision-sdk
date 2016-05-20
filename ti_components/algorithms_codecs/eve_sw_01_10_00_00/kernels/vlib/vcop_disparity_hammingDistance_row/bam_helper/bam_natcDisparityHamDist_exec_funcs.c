/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_ntacDisparityHamDist_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating hammind distance based disparity calculation 
 *              function into BAM.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_disparityHamDist_int.h"
#include "bam_natcDisparityHamDist.h"
#include "vcop_disparity_hammingDistance32_row_kernel.h"
#include "vcop_disparity_postprocess_kernel.h"
#include "vcop_disparity_hammingDistance_row_cn.h"
#include "init_disparity_hammingDistance_row_params.h"

static BAM_Status Bam_natcDisparityHamDist_initFrame(void *kernelContext);
static BAM_Status Bam_natcDisparityHamDist_compute(void *kernelContext);
static BAM_Status BAM_natcDisparityHamDist_control(void *kernelContext, void *kernelCtlArg);

static BAM_Status BAM_natcDisparityHamDist_control(void *kernelContext, void *kernelCtlArg){

    BAM_DisparityHamDist_Context *context = (BAM_DisparityHamDist_Context *) kernelContext;
    BAM_DisparityHamDist_CtlArgs *ctlArg= (BAM_DisparityHamDist_CtlArgs *) kernelCtlArg;
    BAM_Status status = 0;

    if (ctlArg->ctlCmdId== BAM_DISPARITY_HAMDIST_CMD_SET_NUMROWS){
        context->kernelArgs.numRows= ctlArg->numRows;
    }
    else {
        status= 1;
    }

    return status;
}

static BAM_Status Bam_natcDisparityHamDist_initFrame(void *kernelContext)
{
    BAM_DisparityHamDist_Context *context = (BAM_DisparityHamDist_Context *) kernelContext;
    BAM_Status status = 0;

    context->horzBlockIdx= 0;
    context->vertBlockIdx= 0;

    return status;
}

static BAM_Status Bam_natcDisparityHamDist_compute(void *kernelContext)
{
    BAM_DisparityHamDist_Context *context = (BAM_DisparityHamDist_Context *) kernelContext;
    BAM_Status status = 0;

    /* For the first row, we call vcop_disparity_hammingDistance32_first_row_circ_cn() */
    if (context->vertBlockIdx== 0) {
        wrapper_vcop_disparity_hammingDistance32_first_row_circ_cn(
                *(uint8_t(*)[])context->pInBlock[BAM_DISPARITY_HAMDIST_INPUT_LEFT_PORT] + 4,
                *(uint8_t(*)[])context->pInBlock[BAM_DISPARITY_HAMDIST_INPUT_RIGHT_PORT] + 4,
                context->kernelArgs.leftStride,
                context->kernelArgs.rightStride,
                context->kernelArgs.winWidth,
                context->kernelArgs.winHeight,
                (uint8_t*)context->pOutBlock[DISPARITY_HAMDIST_DISP_OUT_IDX],
                (uint16_t*)context->pOutBlock[DISPARITY_HAMDIST_MINCOST_OUT_IDX],
                *(uint16_t(*)[])context->pInternalBlock[DISPARITY_HAMDIST_ALLCOST_IDX] + (context->kernelArgs.allCostOutputStride/2), /* we start from row #1, not row #0 because row#0 is a dummy row that will be used in vcop_disparity_genPrevAndNextMinCost() */
                context->kernelArgs.width,
                context->kernelArgs.width,
                context->kernelArgs.numDisparities,
                context->kernelArgs.disparityStep,
                context->vertBlockIdx,
                context->kernelArgs.winHeight + 1U,
                context->kernelArgs.direction
        );
    }
    else { /* Subsequent row call vcop_disparity_hammingDistance32_first_row_circ_cn() which is more optimized as it makes use of previous computations results */
        wrapper_vcop_disparity_hammingDistance32_nth_row_circ_cn(
                *(uint8_t(*)[])context->pInBlock[BAM_DISPARITY_HAMDIST_INPUT_LEFT_PORT] + 4,
                *(uint8_t(*)[])context->pInBlock[BAM_DISPARITY_HAMDIST_INPUT_RIGHT_PORT] + 4,
                context->kernelArgs.leftStride,
                context->kernelArgs.rightStride,
                context->kernelArgs.winWidth,
                context->kernelArgs.winHeight,
                (uint8_t*)context->pOutBlock[DISPARITY_HAMDIST_DISP_OUT_IDX],
                (uint16_t*)context->pOutBlock[DISPARITY_HAMDIST_MINCOST_OUT_IDX],
                *(uint16_t(*)[])context->pInternalBlock[DISPARITY_HAMDIST_ALLCOST_IDX] + (context->kernelArgs.allCostOutputStride/2), /* we start from row #1, not row #0 because row#0 is a dummy row that will be used in vcop_disparity_genPrevAndNextMinCost() */
                *(uint16_t(*)[])context->pInternalBlock[DISPARITY_HAMDIST_ALLCOST_IDX] + (context->kernelArgs.allCostOutputStride/2), /* we start from row #1, not row #0 because row#0 is a dummy row that will be used in vcop_disparity_genPrevAndNextMinCost() */
                context->kernelArgs.width,
                context->kernelArgs.width,
                context->kernelArgs.numDisparities,
                context->kernelArgs.disparityStep,
                context->vertBlockIdx,
                context->kernelArgs.winHeight + 1U,
                context->kernelArgs.direction
        );
    }

    if (context->kernelArgs.adjacentCosts== 1) {

        uint8_t prevIdx, nextIdx;

        if (context->kernelArgs.direction== 1) {
            prevIdx= (uint8_t)DISPARITY_HAMDIST_NEXT_ADJ_COST;
            nextIdx= (uint8_t)DISPARITY_HAMDIST_PREV_ADJ_COST;
        }
        else {
            nextIdx= (uint8_t)DISPARITY_HAMDIST_NEXT_ADJ_COST;
            prevIdx= (uint8_t)DISPARITY_HAMDIST_PREV_ADJ_COST;
        }


        vcop_disparity_genPrevAndNextMinCost_cn
        (
                (uint8_t*)context->pOutBlock[DISPARITY_HAMDIST_DISP_OUT_IDX],
                *(uint16_t(*)[])context->pInternalBlock[DISPARITY_HAMDIST_ALLCOST_IDX] + (context->kernelArgs.allCostOutputStride/2), /* we start from row #1, not row #0 because row#0 is a dummy row that will be used in vcop_disparity_genPrevAndNextMinCost() */
                (uint16_t*)context->pOutBlock[prevIdx],
                (uint16_t*)context->pOutBlock[nextIdx],
                context->kernelArgs.width, /* width */
                context->kernelArgs.numDisparities,
                context->kernelArgs.disparityStep
        );
    }

    context->vertBlockIdx++;
    if (context->vertBlockIdx== context->kernelArgs.numRows){
        context->vertBlockIdx= 0;
        context->horzBlockIdx++;
    }

    return status;
}


BAM_KernelExecFuncDef gBAM_TI_natcDisparityHamDist_ExecFunc =
{ NULL, &Bam_natcDisparityHamDist_initFrame, &Bam_natcDisparityHamDist_compute, NULL, &BAM_natcDisparityHamDist_control, NULL };

