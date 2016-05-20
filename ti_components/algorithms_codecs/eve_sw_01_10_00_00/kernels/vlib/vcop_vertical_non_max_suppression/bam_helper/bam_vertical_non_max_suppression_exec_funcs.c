/*==========================================================================*/
/*      Copyright (C) 2009-2014 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_vertical_non_max_suppression_exec_funcs.c
 *  @version 0.0 (Dec 2013) : Base version.
 *  @version 0.1 (May 2014) : Updated as per control node requirements
 *  @brief      This file defines interfaces for integrating vertical nms
 *              function into BAM.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_vertical_non_max_suppression_int.h"
#include "bam_vertical_non_max_suppression.h"
#include "vcop_vertical_non_max_suppression_kernel.h" /* compiler should take care of include path */
#include "edma_utils_memcpy.h"


/* Function Prototypes */
static BAM_Status Bam_Vertical_Non_Max_Suppression_initInstance(void *kernelContext);
static BAM_Status Bam_Vertical_Non_Max_Suppression_initFrame(void *kernelContext);

static BAM_Status Bam_Vertical_Non_Max_Suppression_initInstance(void *kernelContext)
{
    BAM_Vertical_Non_Max_Suppression_Context *context = (BAM_Vertical_Non_Max_Suppression_Context *) kernelContext;
    context->pInBlockBase_INDEX_LIST = context->pInBlock[IN_XY_IDX];
    return 0;
}


static BAM_Status Bam_Vertical_Non_Max_Suppression_initFrame(void *kernelContext)
{
    BAM_Vertical_Non_Max_Suppression_Context *context = (BAM_Vertical_Non_Max_Suppression_Context *) kernelContext;
    BAM_Status status = 0;
    uint32_t *pUpdate;
    uint16_t maxCorners;


    EDMA_UTILS_memcpy2D(context->pInternalBlock[ID_IDX],
                        (void *)IN_ID_IDX,
                        sizeof(IN_ID_IDX),
                        1U,
                        0,
                        0);


    context->pInBlock[IN_XY_IDX] = context->pInBlockBase_INDEX_LIST ;

    /* CHECK_MISRA("-17.1,17.4")  -> Disable rule 17.1,17.4  */
    /* Pointer arithmetic is needed here to update the output pointer */
    /* The harmful side effect of voilating this rule (accessing outside valid memory) */
    /* shall be checked by another code checker like Klocwork */
    pUpdate = (uint32_t *)(context->pInBlock[IN_XY_IDX])+((context->kernelArgs.offset));
    /* RESET_MISRA("17.1,17.4")  -> Reset rule 17.1,17.4  */

    context->pInBlock[IN_XY_IDX] = pUpdate;
    maxCorners = context->kernelArgs.max_corners <= context->kernelArgs.num_corners_in ? (context->kernelArgs.num_corners_in + 8) : context->kernelArgs.max_corners;
    
#if (!VCOP_HOST_EMULATION)
    vcop_vertical_non_max_suppression_kernel_init((uint32_t *)context->pInBlock[IN_XY_IDX],
                                        context->kernelArgs.num_corners_in,
                                        maxCorners,
                                        (uint16_t *)context->pInBlock[IN_SCORE_IDX],
                                        (uint16_t *)context->pInternalBlock[NMS_ID_IDX],
                                        (uint16_t *)context->pInternalBlock[NMS_Y_SCORE_IDX],
                                        (uint16_t *)context->pOutBlock[OUT_XY_IDX],
                                        (uint32_t *)context->pOutBlock[OUT_XY_IDX],
                                        (uint32_t *)context->pOutBlock[OUT_SCORE_IDX],
                                        (uint8_t *)context->pInternalBlock[ID_IDX],
                                         context->pInternalBlock[PARAMS_IDX]);

#endif

    return status;
}

#if (VCOP_HOST_EMULATION)

static BAM_Status Bam_Vertical_Non_Max_Suppression_compute(void *kernelContext);

static BAM_Status Bam_Vertical_Non_Max_Suppression_compute(void *kernelContext)
{
    BAM_Vertical_Non_Max_Suppression_Context *context = (BAM_Vertical_Non_Max_Suppression_Context *) kernelContext;
    BAM_Status status = 0;

    uint32_t *pUpdate;
    uint16_t maxCorners;

    maxCorners = context->kernelArgs.max_corners <= context->kernelArgs.num_corners_in ? (context->kernelArgs.num_corners_in + 8) : context->kernelArgs.max_corners;

    vcop_vertical_non_max_suppression_kernel((uint32_t *)context->pInBlock[IN_XY_IDX],
                                        context->kernelArgs.num_corners_in,
                                        maxCorners,
                                       (uint16_t *)context->pInBlock[IN_SCORE_IDX],
                                       (uint16_t *)context->pInternalBlock[NMS_ID_IDX],
                                       (uint16_t *)context->pInternalBlock[NMS_Y_SCORE_IDX],
                                       (uint16_t *)context->pOutBlock[OUT_XY_IDX],
                                       (uint32_t *)context->pOutBlock[OUT_XY_IDX],
                                       (uint32_t *)context->pOutBlock[OUT_SCORE_IDX],
                                       (uint8_t *)context->pInternalBlock[ID_IDX]);
    return status;
}
#endif

static BAM_Status Bam_Vertical_Non_Max_Suppression_control(void *kernelContext, void *kernelCtlArg);
static BAM_Status Bam_Vertical_Non_Max_Suppression_control(void *kernelContext, void *kernelCtlArg)
{
    BAM_Vertical_Non_Max_Suppression_Context *context = (BAM_Vertical_Non_Max_Suppression_Context *) kernelContext;
    BAM_Vertical_Non_Max_Suppression_ctrlArgs *ctlArg = (BAM_Vertical_Non_Max_Suppression_ctrlArgs *)kernelCtlArg;
    BAM_Status status = 0;

    context->kernelArgs.num_corners_in = ctlArg->num_corners_in;
    context->kernelArgs.offset = ctlArg->offset;

    return status;
}


BAM_KernelExecFuncDef gBAM_TI_verticalnonmaxsuppressionExecFunc =
#if (!VCOP_HOST_EMULATION)
    { &Bam_Vertical_Non_Max_Suppression_initInstance, &Bam_Vertical_Non_Max_Suppression_initFrame, NULL, NULL, &Bam_Vertical_Non_Max_Suppression_control, &vcop_vertical_non_max_suppression_kernel_vloops };
#else
    { &Bam_Vertical_Non_Max_Suppression_initInstance, &Bam_Vertical_Non_Max_Suppression_initFrame, &Bam_Vertical_Non_Max_Suppression_compute, NULL, &Bam_Vertical_Non_Max_Suppression_control, NULL };
#endif
