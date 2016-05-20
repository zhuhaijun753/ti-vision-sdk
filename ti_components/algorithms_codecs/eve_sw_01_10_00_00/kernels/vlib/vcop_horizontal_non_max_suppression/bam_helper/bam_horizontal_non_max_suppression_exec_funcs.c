/*==========================================================================*/
/*      Copyright (C) 2009-2014 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_horizontal_non_max_suppression_exec_funcs.c
 *  @version 0.0 (Dec 2013) : Base version.
 *  @version 0.1 (May 2014) : Updated as per control node requirements
 *  @brief      This file defines interfaces for integrating block statistics
 *              function into BAM.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_horizontal_non_max_suppression_int.h"
#include "bam_horizontal_non_max_suppression.h"
#include "vcop_horizontal_non_max_suppression_kernel.h" /* compiler should take care of include path */
#include "edma_utils_memcpy.h"

/* Function Prototypes */
static BAM_Status Bam_Horizontal_Non_Max_Suppression_initFrame(void *kernelContext);

static BAM_Status Bam_Horizontal_Non_Max_Suppression_initFrame(void *kernelContext)
{
    BAM_Horizontal_Non_Max_Suppression_Context *context = (BAM_Horizontal_Non_Max_Suppression_Context *) kernelContext;
    BAM_Status status = 0;
    uint16_t maxCorners;

    EDMA_UTILS_memcpy2D(context->pInternalBlock[ID_IDX],
                        (void *)ID_EXT_IDX,
                        sizeof(ID_EXT_IDX),
                        1U,
                        0,
                        0);

#if (!VCOP_HOST_EMULATION)
    maxCorners = context->kernelArgs.max_corners <= context->kernelArgs.num_corners_in ? (context->kernelArgs.num_corners_in + 8) : context->kernelArgs.max_corners;
    vcop_horizontal_non_max_suppression_init((uint32_t *)context->pInBlock[IN_XY_IDX],
                                              context->kernelArgs.num_corners_in,
                                              maxCorners,
                                             (uint16_t *)context->pInBlock[IN_SCORE_IDX],
                                             (uint32_t *)context->pOutBlock[OUT_XY_IDX],
                                             (uint16_t *)context->pOutBlock[OUT_SCORE_IDX],
                                             (uint8_t *)context->pInternalBlock[ID_IDX],
                                             context->pInternalBlock[PARAMS_IDX]);
#endif

    return status;
}

#if (VCOP_HOST_EMULATION)
static BAM_Status Bam_Horizontal_Non_Max_Suppression_compute(void *kernelContext);

static BAM_Status Bam_Horizontal_Non_Max_Suppression_compute(void *kernelContext)
{
    BAM_Horizontal_Non_Max_Suppression_Context *context = (BAM_Horizontal_Non_Max_Suppression_Context *) kernelContext;
    BAM_Status status = 0;

    uint32_t maxCorners;
    maxCorners = context->kernelArgs.max_corners <= context->kernelArgs.num_corners_in ? (context->kernelArgs.num_corners_in + 8) : context->kernelArgs.max_corners;
    vcop_horizontal_non_max_suppression((unsigned int*)context->pInBlock[IN_XY_IDX],
                                         context->kernelArgs.num_corners_in,
                                         maxCorners,
                                         (unsigned short*)context->pInBlock[IN_SCORE_IDX],
                                         (unsigned int*)context->pOutBlock[OUT_XY_IDX],
                                         (unsigned short*)context->pOutBlock[OUT_SCORE_IDX],
                                         (unsigned char*)context->pInternalBlock[ID_IDX]);

    return status;
}
#endif

static BAM_Status Bam_Horizontal_Non_Max_Suppression_control(void *kernelContext, void *kernelCtlArg);
static BAM_Status Bam_Horizontal_Non_Max_Suppression_control(void *kernelContext, void *kernelCtlArg)
{
    BAM_Horizontal_Non_Max_Suppression_Context *context = (BAM_Horizontal_Non_Max_Suppression_Context *) kernelContext;
    BAM_Horizontal_Non_Max_Suppression_ctrlArgs *ctlArg = (BAM_Horizontal_Non_Max_Suppression_ctrlArgs *) kernelCtlArg;
    BAM_Status status = 0;

    context->kernelArgs.num_corners_in = ctlArg->num_corners_in;

    return status;
}


BAM_KernelExecFuncDef gBAM_TI_horizontalnonmaxsuppressionExecFunc =
#if (!VCOP_HOST_EMULATION)
    { NULL, &Bam_Horizontal_Non_Max_Suppression_initFrame, NULL, NULL, &Bam_Horizontal_Non_Max_Suppression_control, &vcop_horizontal_non_max_suppression_vloops };
#else
    { NULL, &Bam_Horizontal_Non_Max_Suppression_initFrame, &Bam_Horizontal_Non_Max_Suppression_compute, NULL, &Bam_Horizontal_Non_Max_Suppression_control, NULL };
#endif
