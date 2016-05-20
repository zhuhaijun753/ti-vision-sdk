/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*                                                                          */
/*     @file : vcop_sad_error_measure_lk_host.c                             */
/*                                                                          */
/*     @brief : This file is being added to enable host emulation support   */
/*     with minimal changes to existing test code. Basically, this file     */
/*     re-implements the auto generated kernel C functions namely the init  */
/*     and vloops for the kernel.                                           */
/*                                                                          */
/*     Host emulation wrapper functions for SAD Based Error Measure for LK: */
/*           vcop_sad_error_measure_lk_init - Copies arguments to           */
/*             parameter block memory                                       */
/*           vcop_sad_error_measure_lk_vloops - Invokes the API namely      */
/*             vcop_sad_error_measure_lk defined in kernel file by          */
/*             passing the arguments from parameter block memory            */
/*                                                                          */
/*  @version 1.0 (January 2014) : Base version.                            */
/*                                                                          */
/*==========================================================================*/

#include  <stdint.h>
#include "vcop.h"

#include "vcop_sad_error_measure_lk_cn.h"

#if VCOP_HOST_EMULATION
void vcop_sad_error_measure_lk
(
   __vptr_uint8      pPrevBiLinImg_A   ,
   __vptr_uint8      pCurrBiLinImg_B   ,
   __vptr_uint16     pNewXYList_X      ,
   __vptr_uint16     pOutErrorMeasure_C,
   uint16_t          inputStride       ,
   uint16_t          frmWidth          ,
   uint16_t          frmHeight         ,
   uint16_t          blkWidth          ,
   uint16_t          blkHeight         ,
   uint16_t          numKeyPoints      ,
   uint16_t          shiftValue        ,
   __vptr_uint16     scratch_a
);

typedef struct _vcop_sad_error_measure_lk_args
{
   uint16_t          inputStride ;
   uint16_t          frmWidth    ;
   uint16_t          frmHeight   ;
   uint16_t          blkWidth    ;
   uint16_t          blkHeight   ;
   uint16_t          numKeyPoints;
   uint16_t          shiftValue  ;
} VCOP_SAD_ERROR_MEASURE_LK_Args;

typedef struct _vcop_sad_error_measure_lk_context
{
    void *pInBlock[3] ;
    void *pOutBlock[1];
    void *pInternalBlock[1];
    VCOP_SAD_ERROR_MEASURE_LK_Args kernelArgs;
} VCOP_SAD_ERROR_MEASURE_LK_Context;

unsigned short __pblock_vcop_sad_error_measure_lk[sizeof(VCOP_SAD_ERROR_MEASURE_LK_Context)/sizeof(uint16_t)];

unsigned int vcop_sad_error_measure_lk_init(
   __vptr_uint8      pPrevBiLinImg_A   ,
   __vptr_uint8      pCurrBiLinImg_B   ,
   __vptr_uint16     pNewXYList_X      ,
   __vptr_uint16     pOutErrorMeasure_C,
   uint16_t          inputStride       ,
   uint16_t          frmWidth          ,
   uint16_t          frmHeight         ,
   uint16_t          blkWidth          ,
   uint16_t          blkHeight         ,
   uint16_t          numKeyPoints      ,
   uint16_t          shiftValue        ,
   __vptr_uint16     scratch_a         ,
   uint16_t          pblock[])
{
    int retVal = 0;

    VCOP_SAD_ERROR_MEASURE_LK_Context *sadErrorMeasureLKHostContext = (VCOP_SAD_ERROR_MEASURE_LK_Context *)pblock;

    sadErrorMeasureLKHostContext->pInBlock[0]                 = pPrevBiLinImg_A.addr   ;
    sadErrorMeasureLKHostContext->pInBlock[1]                 = pCurrBiLinImg_B.addr   ;
    sadErrorMeasureLKHostContext->pInBlock[2]                 = pNewXYList_X.addr      ;
    sadErrorMeasureLKHostContext->pOutBlock[0]                = pOutErrorMeasure_C.addr;
    sadErrorMeasureLKHostContext->pInternalBlock[0]           = scratch_a.addr         ;
    sadErrorMeasureLKHostContext->kernelArgs.inputStride      = inputStride            ;
    sadErrorMeasureLKHostContext->kernelArgs.frmWidth         = frmWidth               ;
    sadErrorMeasureLKHostContext->kernelArgs.frmHeight        = frmHeight              ;
    sadErrorMeasureLKHostContext->kernelArgs.blkWidth         = blkWidth               ;
    sadErrorMeasureLKHostContext->kernelArgs.blkHeight        = blkHeight              ;
    sadErrorMeasureLKHostContext->kernelArgs.numKeyPoints     = numKeyPoints           ;
    sadErrorMeasureLKHostContext->kernelArgs.shiftValue       = shiftValue             ;

    return retVal;
}

void vcop_sad_error_measure_lk_vloops(unsigned short pblock[])
{
    VCOP_SAD_ERROR_MEASURE_LK_Context *sadErrorMeasureLKHostContext = (VCOP_SAD_ERROR_MEASURE_LK_Context *)pblock;

#ifdef NATC
    vcop_sad_error_measure_lk_cn((unsigned char *)sadErrorMeasureLKHostContext->pInBlock[0],
                              (unsigned char *)sadErrorMeasureLKHostContext->pInBlock[1],
                              (unsigned short *)sadErrorMeasureLKHostContext->pInBlock[2],
                              (unsigned short *)sadErrorMeasureLKHostContext->pOutBlock[0],
                              sadErrorMeasureLKHostContext->kernelArgs.inputStride,
                              sadErrorMeasureLKHostContext->kernelArgs.frmWidth,
                              sadErrorMeasureLKHostContext->kernelArgs.frmHeight,
                              sadErrorMeasureLKHostContext->kernelArgs.blkWidth,
                              sadErrorMeasureLKHostContext->kernelArgs.blkHeight,
                              sadErrorMeasureLKHostContext->kernelArgs.numKeyPoints,
                              sadErrorMeasureLKHostContext->kernelArgs.shiftValue);
#else
    vcop_sad_error_measure_lk(sadErrorMeasureLKHostContext->pInBlock[0],
                              sadErrorMeasureLKHostContext->pInBlock[1],
                              sadErrorMeasureLKHostContext->pInBlock[2],
                              sadErrorMeasureLKHostContext->pOutBlock[0],
                              sadErrorMeasureLKHostContext->kernelArgs.inputStride,
                              sadErrorMeasureLKHostContext->kernelArgs.frmWidth,
                              sadErrorMeasureLKHostContext->kernelArgs.frmHeight,
                              sadErrorMeasureLKHostContext->kernelArgs.blkWidth,
                              sadErrorMeasureLKHostContext->kernelArgs.blkHeight,
                              sadErrorMeasureLKHostContext->kernelArgs.numKeyPoints,
                              sadErrorMeasureLKHostContext->kernelArgs.shiftValue,
                              sadErrorMeasureLKHostContext->pInternalBlock[0]);
#endif
}

unsigned int vcop_sad_error_measure_lk_param_count(void)
{
    return (sizeof(VCOP_SAD_ERROR_MEASURE_LK_Context));
}
#endif
