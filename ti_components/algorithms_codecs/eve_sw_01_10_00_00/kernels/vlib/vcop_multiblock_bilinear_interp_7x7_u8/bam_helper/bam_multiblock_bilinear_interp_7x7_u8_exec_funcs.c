/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_multiblock_bilinear_interp_7x7_u8_exec_funcs.c
 *
 *  @brief      This file defines interfaces integrating multi block bilinear
 *              interpolation kernel for neighboorhood of 7x7 8-bit pixel data into BAM.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_multiblock_bilinear_interp_7x7_u8_int.h"
#include "bam_multiblock_bilinear_interp_7x7_u8.h"
#include "vcop_multiblock_bilinear_interp_7x7_u8_kernel.h" /* compiler should take care of include path */
#include "vcop_multiblock_bilinear_interp_7x7_u8_cn.h"

/* Function Prototypes */
static BAM_Status Bam_Multiblock_Bilinear_Interp_7x7_U8_initFrame(void *kernelContext);
static BAM_Status Bam_Multiblock_Bilinear_Interp_7x7_U8_control(void *kernelContext, void *ctlArg);

static BAM_Status Bam_Multiblock_Bilinear_Interp_7x7_U8_initFrame(void *kernelContext)
{
    BAM_Multiblock_Bilinear_Interp_7x7_U8_Context *context = (BAM_Multiblock_Bilinear_Interp_7x7_U8_Context *) kernelContext;
    BAM_Status status = 0;
    int32_t shiftValue = 2*(VCOP_LK_Q_FORMATE_PEL_RESOLN + context->kernelArgs.ctrlPtr.currLevel);
    /* Return error if assumptions in kernel are not satisfied*/
    if((context->kernelArgs.input1Stride < (context->kernelArgs.numKeyPoints*context->kernelArgs.blkOffset)) ||
        ((context->kernelArgs.blkWidth) < 1) || ((context->kernelArgs.blkHeight) < 1) ||
        ((context->kernelArgs.blkOffset) < 1) || ((context->kernelArgs.numKeyPoints) < 1) ||
        ((context->kernelArgs.input2Stride) < (context->kernelArgs.numKeyPoints))) {
        status = 1;
    }

    if(shiftValue > 16)
    {
      shiftValue = 16;
    }
    if(status == 0) {
        /* CHECK_MISRA("-17.1,-17.4")  -> Disable rule 17.1 and 17.4  */
        /* Pointer is used in arithmetic or array index expression */
        /* Deviation allowed since, this same address needs to be accessed with an offset  */
        uint8_t* addr = ((uint8_t*)(context->pInBlock[INP_IDX1]) + context->kernelArgs.input1Stride + 1);
        vcop_multiblock_bilinear_interp_7x7_u8_init((uint8_t*)addr,
                               (uint16_t*)context->pInBlock[INP_IDX2],
                               (uint8_t*)context->pOutBlock[OUT_IDX],
                               context->kernelArgs.input1Stride,
                               context->kernelArgs.input2Stride,
                               context->kernelArgs.outputStride,
                               context->kernelArgs.blkWidth,
                               context->kernelArgs.blkHeight,
                               context->kernelArgs.blkOffset,
                               (uint16_t)shiftValue,
                               context->kernelArgs.numKeyPoints,
                               (uint16_t*)context->pInternalBlock[PARAMS_IDX]);
        /* RESET_MISRA("17.1,17.4")  -> Reset rule 17.1 and 17.4*/
    }

    return status;
}

#ifdef NATC
static BAM_Status Bam_Multiblock_Bilinear_Interp_7x7_U8_computeFrame(void *kernelContext);

static BAM_Status Bam_Multiblock_Bilinear_Interp_7x7_U8_computeFrame(void *kernelContext)
{
    BAM_Multiblock_Bilinear_Interp_7x7_U8_Context *context = (BAM_Multiblock_Bilinear_Interp_7x7_U8_Context *) kernelContext;
    BAM_Status status = 0;
    int shiftValue = 2*(VCOP_LK_Q_FORMATE_PEL_RESOLN + context->kernelArgs.ctrlPtr.currLevel);
    
    if(shiftValue > 16)
    {
      shiftValue = 16;
    }
    vcop_multiblock_bilinear_interp_7x7_u8_cn((((uint8_t*)context->pInBlock[INP_IDX1]) + context->kernelArgs.input1Stride + 1),
                           (uint16_t*)context->pInBlock[INP_IDX2],
                           (uint8_t*)context->pOutBlock[OUT_IDX],
                           context->kernelArgs.input1Stride,
                           context->kernelArgs.input2Stride,
                           context->kernelArgs.outputStride,
                           context->kernelArgs.blkWidth,
                           context->kernelArgs.blkHeight,
                           context->kernelArgs.blkOffset,
                           shiftValue,
                           context->kernelArgs.numKeyPoints);

    return status;
}
#endif

static BAM_Status Bam_Multiblock_Bilinear_Interp_7x7_U8_control(void *kernelContext, void *ctlArg)
{
  BAM_Status status = 0;
  BAM_Multiblock_Bilinear_Interp_7x7_U8_Context *context = (BAM_Multiblock_Bilinear_Interp_7x7_U8_Context *) kernelContext;
  BAM_Multiblock_Bilinear_Interp_7x7_U8_Ctrl_Args *args  = (BAM_Multiblock_Bilinear_Interp_7x7_U8_Ctrl_Args *) ctlArg;
  context->kernelArgs.ctrlPtr = *args;
  return status;
}
BAM_KernelExecFuncDef gBAM_TI_multiblockBilinearInterp7x7U8ExecFunc =
#ifdef NATC
    { NULL, &Bam_Multiblock_Bilinear_Interp_7x7_U8_initFrame, &Bam_Multiblock_Bilinear_Interp_7x7_U8_computeFrame, NULL, &Bam_Multiblock_Bilinear_Interp_7x7_U8_control, NULL };
#else
    { NULL, &Bam_Multiblock_Bilinear_Interp_7x7_U8_initFrame, NULL, NULL, &Bam_Multiblock_Bilinear_Interp_7x7_U8_control, &vcop_multiblock_bilinear_interp_7x7_u8_vloops };
#endif
