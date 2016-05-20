/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_yuv420_fir2d_separable_helper_funcs.c
 *
 *  @brief      This file defines interfaces for integrating YUV420 separable filter
 *              into BAM
 */

#include <stdio.h>
#include <stdlib.h>

#include "evealgframework.h"
#include "bam_yuv420_fir2d_separable_int.h"
#include "vcop_yuv420_fir2d_separable_kernel.h"


/* Function Prototypes */
static BAM_Status BAM_Yuv420_fir2dseparable_Y_getMemRecFunc(
                    const void *kernelArgs,
                    BAM_MemRec internalBlock[],
                    BAM_MemRec outBlock[],
                    uint8_t *numInternalBlocks,
                    uint8_t *numOutBlocks);


static BAM_Status BAM_Yuv420_fir2dseparable_Y_getMemRecFunc(
                    const void *kernelArgs,
                    BAM_MemRec internalBlock[],
                    BAM_MemRec outBlock[],
                    uint8_t *numInternalBlocks,
                    uint8_t *numOutBlocks)
{
  const BAM_Yuv420_fir2dseparable_Args * args = (const BAM_Yuv420_fir2dseparable_Args *)kernelArgs;

#if (!VCOP_HOST_EMULATION)
  internalBlock[YUV420_FIR2D_SEPARABLE_INTERNAL_PARAMS_IDX].size = 2U *
                                                  vcop_yuv420_fir2d_separable_y_param_count();
#else
  /* This field could be any non-zero number for host emulation */
  internalBlock[YUV420_FIR2D_SEPARABLE_INTERNAL_PARAMS_IDX].size = 4U;
#endif

  internalBlock[YUV420_FIR2D_SEPARABLE_INTERNAL_COEF_HORZ_IDX].size           = args->coefWidth *
                                                               sizeof(uint8_t);
  internalBlock[YUV420_FIR2D_SEPARABLE_INTERNAL_COEF_HORZ_IDX].attrs.memAttrs =
                                                              BAM_MEMATTRS_CONST;
  internalBlock[YUV420_FIR2D_SEPARABLE_INTERNAL_COEF_HORZ_IDX].space          =
                                                              BAM_MEMSPACE_WBUF;

  internalBlock[YUV420_FIR2D_SEPARABLE_INTERNAL_COEF_VERT_IDX].size           = args->coefHeight *
                                                               sizeof(uint8_t);
  internalBlock[YUV420_FIR2D_SEPARABLE_INTERNAL_COEF_VERT_IDX].attrs.memAttrs =
                                                              BAM_MEMATTRS_CONST;
  internalBlock[YUV420_FIR2D_SEPARABLE_INTERNAL_COEF_VERT_IDX].space          =
                                                              BAM_MEMSPACE_WBUF;

  internalBlock[YUV420_FIR2D_SEPARABLE_INTERNAL_INTERM_IDX].size            = (args->blockWidth +
                                                               (args->coefWidth - 1U))*
                                                              (args->blockHeight +
                                                              (args->coefHeight - 1U)) *
                                                              sizeof(uint16_t);
  internalBlock[YUV420_FIR2D_SEPARABLE_INTERNAL_INTERM_IDX].attrs.memAttrs  =
                                                              BAM_MEMATTRS_SCRATCH;
  internalBlock[YUV420_FIR2D_SEPARABLE_INTERNAL_INTERM_IDX].space           =
                                                              BAM_MEMSPACE_ANY_VCOPBUF;

  outBlock[YUV420_FIR2D_SEPARABLE_OUT_IDX].size              = args->blockWidth *
                                                                args->blockHeight;
  outBlock[YUV420_FIR2D_SEPARABLE_OUT_IDX].attrs.memAttrs    = BAM_MEMATTRS_SCRATCH;
  outBlock[YUV420_FIR2D_SEPARABLE_OUT_IDX].space             = BAM_MEMSPACE_ANY_VCOPBUF;


  return BAM_S_SUCCESS;
}


/* Function Prototypes */
static BAM_Status BAM_Yuv420_fir2dseparable_UV_getMemRecFunc(
                    const void *kernelArgs,
                    BAM_MemRec internalBlock[],
                    BAM_MemRec outBlock[],
                    uint8_t *numInternalBlocks,
                    uint8_t *numOutBlocks);


static BAM_Status BAM_Yuv420_fir2dseparable_UV_getMemRecFunc(
                    const void *kernelArgs,
                    BAM_MemRec internalBlock[],
                    BAM_MemRec outBlock[],
                    uint8_t *numInternalBlocks,
                    uint8_t *numOutBlocks)
{
  const BAM_Yuv420_fir2dseparable_Args * args = (const BAM_Yuv420_fir2dseparable_Args *)kernelArgs;

#if (!VCOP_HOST_EMULATION)
  internalBlock[YUV420_FIR2D_SEPARABLE_INTERNAL_PARAMS_IDX].size = 2U *
                                                  vcop_yuv420_fir2d_separable_uv_param_count();
#else
  /* This field could be any non-zero number for host emulation */
  internalBlock[YUV420_FIR2D_SEPARABLE_INTERNAL_PARAMS_IDX].size = 4U;
#endif

  internalBlock[YUV420_FIR2D_SEPARABLE_INTERNAL_COEF_HORZ_IDX].size           = args->coefWidth *
                                                               sizeof(uint8_t);
  internalBlock[YUV420_FIR2D_SEPARABLE_INTERNAL_COEF_HORZ_IDX].attrs.memAttrs =
                                                              BAM_MEMATTRS_CONST;
  internalBlock[YUV420_FIR2D_SEPARABLE_INTERNAL_COEF_HORZ_IDX].space          =
                                                              BAM_MEMSPACE_WBUF;

  internalBlock[YUV420_FIR2D_SEPARABLE_INTERNAL_COEF_VERT_IDX].size           = args->coefHeight *
                                                               sizeof(uint8_t);
  internalBlock[YUV420_FIR2D_SEPARABLE_INTERNAL_COEF_VERT_IDX].attrs.memAttrs =
                                                              BAM_MEMATTRS_CONST;
  internalBlock[YUV420_FIR2D_SEPARABLE_INTERNAL_COEF_VERT_IDX].space          =
                                                              BAM_MEMSPACE_WBUF;

  internalBlock[YUV420_FIR2D_SEPARABLE_INTERNAL_INTERM_IDX].size            = (args->blockWidth +
                                                               ((2U * args->coefWidth) - 1U)) *
                                                              ( args->blockHeight +
                                                              ((2U * args->coefHeight) - 1U)) *
                                                              sizeof(uint16_t);
  internalBlock[YUV420_FIR2D_SEPARABLE_INTERNAL_INTERM_IDX].attrs.memAttrs  =
                                                              BAM_MEMATTRS_SCRATCH;
  internalBlock[YUV420_FIR2D_SEPARABLE_INTERNAL_INTERM_IDX].space           =
                                                              BAM_MEMSPACE_ANY_VCOPBUF;

  outBlock[YUV420_FIR2D_SEPARABLE_OUT_IDX].size              = args->blockWidth *
                                                                args->blockHeight;
  outBlock[YUV420_FIR2D_SEPARABLE_OUT_IDX].attrs.memAttrs    = BAM_MEMATTRS_SCRATCH;
  outBlock[YUV420_FIR2D_SEPARABLE_OUT_IDX].space             = BAM_MEMSPACE_ANY_VCOPBUF;


  return BAM_S_SUCCESS;
}



BAM_KernelInfo gBAM_TI_yuv420Fir2dSeparableYKernel =
{
    0,                                      /* kernelId */
    sizeof(BAM_Yuv420_fir2dseparable_Context),
    sizeof(BAM_Yuv420_fir2dseparable_Args),
    BAM_EVE,                                /* coreType */
    BAM_NODE_COMPUTE,                       /* nodeType */
    NUM_IN_BLOCKS,                          /* 1 */
    NUM_OUT_BLOCKS,                         /* 1 */
    NUM_INTERNAL_BLOCKS                     /* 4 */
};

BAM_KernelHelperFuncDef gBAM_TI_yuv420Fir2dSeparableYHelperFunc =
{ &BAM_Yuv420_fir2dseparable_Y_getMemRecFunc, NULL};


BAM_KernelInfo gBAM_TI_yuv420Fir2dSeparableUvKernel =
{
    0,                                      /* kernelId */
    sizeof(BAM_Yuv420_fir2dseparable_Context),
    sizeof(BAM_Yuv420_fir2dseparable_Args),
    BAM_EVE,                                /* coreType */
    BAM_NODE_COMPUTE,                       /* nodeType */
    NUM_IN_BLOCKS,                          /* 1 */
    NUM_OUT_BLOCKS,                         /* 1 */
    NUM_INTERNAL_BLOCKS                     /* 4 */
};

BAM_KernelHelperFuncDef gBAM_TI_yuv420Fir2dSeparableUvHelperFunc =
{ &BAM_Yuv420_fir2dseparable_UV_getMemRecFunc, NULL};


