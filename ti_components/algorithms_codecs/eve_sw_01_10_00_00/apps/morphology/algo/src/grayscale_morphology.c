/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/** @file grayscale_morphology.c
 *
 *  @brief  This file implements an applet for grayscale morphology
 *
 *  @author Anoop K P <a-kp@ti.com>
 *
 *  @date   22 March 2013
 *
 *  Description
 *    This file contains code to perform grayscale morphological processing
 *    at the frame level.
 */


#include <stdint.h>
#include <string.h>
#include <vcop.h>
#include "xdais_types.h"
#include <stdio.h>
#include "imorphology_ti.h"
#include "morphology_dma_auto_incr.h"
#include "grayscale_morphology.h"

#include "vcop_grayscale_morphology_kernel.h"
#include "vcop_grayscale_morphology.h"
#if (VCOP_HOST_EMULATION)
#include "grayscale_morphology_host.h"
#endif

/* CHECK_MISRA("-19.7")  -> Disable rule 19.7  */
/* These are simple non-harmful macros.   */

#define ALIGN_2SIMD(a) ((((a) + (2*(int32_t)VCOP_SIMD_WIDTH) - 1)/(2*(int32_t)VCOP_SIMD_WIDTH))*(2*(int32_t)VCOP_SIMD_WIDTH))

#define BLOCK_WIDTH    (64U)
#define BLOCK_HEIGHT   (64U)

#if (VCOP_HOST_EMULATION)
#define Grayscale_Morphology_malloc(heap, size)   malloc(size)
#define Grayscale_Morphology_free(ptr)            free(ptr)
#else
#define Grayscale_Morphology_malloc(heap, size)   (vcop_malloc((heap), (size)))
#define Grayscale_Morphology_free(ptr)            (vcop_free(ptr))
#endif
/* RESET_MISRA("19.7")  -> Reset rule 19.7     */

void Grayscale_Morphology_Init(Grayscale_Morphology_Obj *handle)
{
      uint32_t pBlock_dilate_size, pBlock_erode_size, pBlock_diff_size;
      int32_t  srcBlkPadX, srcBlkPadY;
      int32_t  srcBlkWidth, srcBlkHeight, srcBlkPitch, srcBlkHeightTot;
      int32_t  dstBlkHeight, dstBlkPitch;

      srcBlkPadX      = 2*((int32_t)MORPHOLOGY_TI_MAX_GRAYSCALE_SE_WIDTH  - 1);
      srcBlkPadY      = 2*((int32_t)MORPHOLOGY_TI_MAX_GRAYSCALE_SE_HEIGHT - 1);

      srcBlkWidth     = (int32_t)BLOCK_WIDTH;
      srcBlkHeight    = (int32_t)BLOCK_HEIGHT;
      srcBlkPitch     = srcBlkWidth  + srcBlkPadX;
      srcBlkHeightTot = srcBlkHeight + srcBlkPadY;

      dstBlkHeight    = srcBlkHeightTot;
      dstBlkPitch     = srcBlkPitch;

#if (!VCOP_HOST_EMULATION)
      VCOP_BUF_SWITCH_SET (WBUF_SYST, IBUFHB_SYST, IBUFLB_SYST, IBUFHA_SYST, IBUFLA_SYST);

      pBlock_dilate_size = (vcop_grayscale_dilate_mask_param_count()  * sizeof(__pblock_vcop_grayscale_dilate_mask[0]))
                         + (vcop_grayscale_dilate_rect_param_count()  * sizeof(__pblock_vcop_grayscale_dilate_rect[0]))
                         + (vcop_grayscale_dilate_cross_param_count() * sizeof(__pblock_vcop_grayscale_dilate_cross[0]));

      pBlock_erode_size  = (vcop_grayscale_erode_mask_param_count()  * sizeof(__pblock_vcop_grayscale_erode_mask[0]))
                         + (vcop_grayscale_erode_rect_param_count()  * sizeof(__pblock_vcop_grayscale_erode_rect[0]))
                         + (vcop_grayscale_erode_cross_param_count() * sizeof(__pblock_vcop_grayscale_erode_cross[0]));

      pBlock_diff_size   = vcop_grayscale_morp_diff_param_count() * sizeof(__pblock_vcop_grayscale_morp_diff[0]);

      /* CHECK_MISRA("-12.1")  -> Disable rule 12.1  */
      /* Redundant parentheses are added for code readability and is waived.   */

      handle->stParamBlock.pblock_dilate   = (uint16_t *)Grayscale_Morphology_malloc(VCOP_WMEM, (int32_t)pBlock_dilate_size);
      handle->stParamBlock.pblock_erode    = (uint16_t *)Grayscale_Morphology_malloc(VCOP_WMEM, (int32_t)pBlock_erode_size);
      handle->stParamBlock.pblock_img_diff = (uint16_t *)Grayscale_Morphology_malloc(VCOP_WMEM, (int32_t)pBlock_diff_size);
      handle->stParamBlock_open_close.pblock_dilate = handle->stParamBlock.pblock_dilate;
      handle->stParamBlock_open_close.pblock_erode  = handle->stParamBlock.pblock_erode;
#endif
      handle->srcPtr_A     = (uint8_t *)Grayscale_Morphology_malloc(VCOP_IBUFLA, srcBlkPitch * srcBlkHeightTot);
      handle->sePtr_C      = (uint8_t *)Grayscale_Morphology_malloc(VCOP_WMEM,   (int32_t)(MORPHOLOGY_TI_MAX_GRAYSCALE_SE_WIDTH *
                                                                                 MORPHOLOGY_TI_MAX_GRAYSCALE_SE_HEIGHT));
      handle->seReflPtr_C  = (uint8_t *)Grayscale_Morphology_malloc(VCOP_WMEM,   (int32_t)(MORPHOLOGY_TI_MAX_GRAYSCALE_SE_WIDTH *
                                                                                 MORPHOLOGY_TI_MAX_GRAYSCALE_SE_HEIGHT));
      handle->scratchPtr_C = (uint8_t *)Grayscale_Morphology_malloc(VCOP_WMEM,   ALIGN_2SIMD(srcBlkPitch) * srcBlkHeightTot);
      handle->scratchPtr_A = (uint8_t *)Grayscale_Morphology_malloc(VCOP_IBUFLA, ALIGN_2SIMD(srcBlkPitch) * srcBlkHeightTot);
      handle->outputPtr_B  = (uint8_t *)Grayscale_Morphology_malloc(VCOP_IBUFHA, ALIGN_2SIMD(dstBlkPitch) * dstBlkHeight);

      /* RESET_MISRA("12.1")  -> Reset rule 12.1     */
}


void Grayscale_Morphology_Process(
                         Grayscale_Morphology_Obj *handle,
                         uint8_t      *src,
                         uint16_t      srcImageWidth,
                         uint16_t      srcImageHeight,
                         uint16_t      srcImagePitch,
                         uint8_t      *dst,
                         uint16_t      dstImageWidth,
                         uint16_t      dstImageHeight,
                         uint16_t      dstImagePitch,
                         uint8_t       struct_elem[],
                         uint16_t      se_width,
                         uint16_t      se_height,
                         uint8_t       seShape,
                         uint8_t       operation)
{
    uint8_t *srcPtr_A, *scratchPtr_C, *scratchPtr_A, *outputPtr_B;
    uint8_t (*sePtr_C)[], (*seReflPtr_C)[];
    uint8_t *autoIncrementContext;
    EVELIB_KernelFuncType    execFunc[3];
    EVELIB_KernelContextType context[3];
    uint16_t i, numKernels = 0U;
    uint16_t srcBlkPadX, srcBlkPadY;
    uint16_t srcBlkWidth, srcBlkHeight, srcBlkPitch, srcBlkHeightTot;
    uint16_t dstBlkWidth, dstBlkHeight, dstBlkPitch;
#if (!VCOP_HOST_EMULATION)
    stblock_morph_t          *stParamBlock;
    stblock_open_close_t     *stParamBlock_open_close;
#else
    Grayscale_Morphology_ExecParams execParams;
#endif

    srcPtr_A                = handle->srcPtr_A;
    sePtr_C                 = (uint8_t (*)[])(void *)handle->sePtr_C;
    seReflPtr_C             = (uint8_t (*)[])(void *)handle->seReflPtr_C;
    scratchPtr_C            = handle->scratchPtr_C;
    scratchPtr_A            = handle->scratchPtr_A;
    outputPtr_B             = handle->outputPtr_B;
    autoIncrementContext    = handle->autoIncrementContext;
#if (!VCOP_HOST_EMULATION)
    stParamBlock            = &handle->stParamBlock;
    stParamBlock_open_close = &handle->stParamBlock_open_close;
#endif

    srcBlkPadX = ((operation == MORPHOLOGY_TI_DILATE) ||
                  (operation == MORPHOLOGY_TI_ERODE)  ||
                  (operation == MORPHOLOGY_TI_GRADIENT)) ? (se_width - (uint16_t)1)  : (uint16_t)2*(se_width - (uint16_t)1);
    srcBlkPadY = ((operation == MORPHOLOGY_TI_DILATE) ||
                  (operation == MORPHOLOGY_TI_ERODE)  ||
                  (operation == MORPHOLOGY_TI_GRADIENT)) ? (se_height - (uint16_t)1) : (uint16_t)2*(se_height - (uint16_t)1);

    srcBlkWidth     = BLOCK_WIDTH;
    srcBlkHeight    = BLOCK_HEIGHT;
    srcBlkPitch     = srcBlkWidth  + srcBlkPadX;
    srcBlkHeightTot = srcBlkHeight + srcBlkPadY;

    dstBlkWidth     = srcBlkWidth;
    dstBlkHeight    = srcBlkHeight;
    dstBlkPitch     = srcBlkPitch;

    /* CHECK_MISRA("-12.1")  -> Disable rule 12.1  */
    /* Redundant parentheses are added for code readability and is waived.   */

    if ( seShape == MORPHOLOGY_TI_CUSTOM_SE )
    {
        memcpy(*sePtr_C, struct_elem, se_height * se_width);

        /* Reflective Structuring Element. */
        for(i = 0U; i < (se_height * se_width); i++)
        {
            (*seReflPtr_C)[i] = (*sePtr_C)[((se_height * se_width) - 1U) - i];
        }

    }
    /* RESET_MISRA("12.1")  -> Reset rule 12.1     */

#if (VCOP_HOST_EMULATION)
    execParams.morphologyMode = (MORPHOLOGY_TI_Operation)operation;
    execParams.seShape      = (MORPHOLOGY_TI_StructuringElementShape)seShape;
    execParams.blkWidth     = srcBlkPitch;
    execParams.blkStride    = srcBlkPitch;
    execParams.blkHeight    = srcBlkHeightTot;
    execParams.dataPtr_A    = srcPtr_A;
    execParams.seWidth      = se_width;
    execParams.seHeight     = se_height;
    execParams.sePtr_C      = *sePtr_C;
    execParams.seReflPtr_C  = *seReflPtr_C;
    execParams.scratchPtr_C = scratchPtr_C;
    execParams.scratchPtr_A = scratchPtr_A;
    execParams.outputPtr_B  = outputPtr_B;

    execFunc[0] = (EVELIB_KernelFuncType)Grayscale_Morphology_exec;
    context[0] = (EVELIB_KernelContextType)&execParams;
    numKernels = 1U;

#else

    switch( operation ) {
        case MORPHOLOGY_TI_DILATE:

            switch ( seShape )
            {
                case MORPHOLOGY_TI_CUSTOM_SE:
                    execFunc[0] = &vcop_grayscale_dilate_mask_vloops;
                    context[0] = (EVELIB_KernelContextType)stParamBlock->pblock_dilate;
                    numKernels = 1U;

                    vcop_grayscale_dilate_mask_init((uint16_t)srcBlkPitch, (uint16_t)srcBlkPitch, (uint16_t)srcBlkHeightTot, srcPtr_A,
                        se_width, se_height, *seReflPtr_C, outputPtr_B, stParamBlock->pblock_dilate);

                break;
                case MORPHOLOGY_TI_RECT_SE:
                    execFunc[0] = &vcop_grayscale_dilate_rect_vloops;
                    context[0] = (EVELIB_KernelContextType)stParamBlock->pblock_dilate;
                    numKernels = 1U;

                    vcop_grayscale_dilate_rect_init(srcBlkPitch, srcBlkPitch, srcBlkHeightTot, srcPtr_A,
                        se_width, se_height, scratchPtr_C, outputPtr_B, stParamBlock->pblock_dilate);

                break;
                case MORPHOLOGY_TI_CROSS_SE:
                    execFunc[0] = &vcop_grayscale_dilate_cross_vloops;
                    context[0] = (EVELIB_KernelContextType)stParamBlock->pblock_dilate;
                    numKernels = 1U;

                    vcop_grayscale_dilate_cross_init(srcBlkPitch, srcBlkPitch, srcBlkHeightTot, srcPtr_A,
                        se_width, se_height, (se_height - 1U)/2U, (se_width - 1U)/2U, scratchPtr_C, outputPtr_B,
                        stParamBlock->pblock_dilate);

                break;
                default:
                break;
            }

            break;

        case MORPHOLOGY_TI_ERODE:

            switch ( seShape )
            {
                case MORPHOLOGY_TI_CUSTOM_SE:
                    execFunc[0] = &vcop_grayscale_erode_mask_vloops;
                    context[0] = (EVELIB_KernelContextType)stParamBlock->pblock_erode;
                    numKernels = 1U;

                    vcop_grayscale_erode_mask_init(srcBlkPitch, srcBlkPitch, srcBlkHeightTot, srcPtr_A,
                        se_width, se_height, *sePtr_C, outputPtr_B, stParamBlock->pblock_erode);

                break;
                case MORPHOLOGY_TI_RECT_SE:
                    execFunc[0] = &vcop_grayscale_erode_rect_vloops;
                    context[0] = (EVELIB_KernelContextType)stParamBlock->pblock_erode;
                    numKernels = 1U;

                    vcop_grayscale_erode_rect_init(srcBlkPitch, srcBlkPitch, srcBlkHeightTot, srcPtr_A,
                        se_width, se_height, scratchPtr_C, outputPtr_B, stParamBlock->pblock_erode);

                break;
                case MORPHOLOGY_TI_CROSS_SE:
                    execFunc[0] = &vcop_grayscale_erode_cross_vloops;
                    context[0] = (EVELIB_KernelContextType)stParamBlock->pblock_erode;
                    numKernels = 1U;

                    vcop_grayscale_erode_cross_init(srcBlkPitch, srcBlkPitch, srcBlkHeightTot, srcPtr_A,
                        se_width, se_height, (se_height - 1U)/2U, (se_width - 1U)/2U, scratchPtr_C, outputPtr_B,
                        stParamBlock->pblock_erode);

                break;
                default:
                break;
            }

            break;

        case MORPHOLOGY_TI_OPEN:

            switch ( seShape )
            {
                case MORPHOLOGY_TI_CUSTOM_SE:
                    execFunc[0] = &vcop_grayscale_open_mask_vloops;
                    context[0] = (EVELIB_KernelContextType)(void *)stParamBlock_open_close;
                    numKernels = 1U;

                    vcop_grayscale_open_mask_init(srcBlkPitch, srcBlkPitch, srcBlkHeightTot, srcPtr_A,
                        se_width, se_height, *sePtr_C, *seReflPtr_C, scratchPtr_C, outputPtr_B, stParamBlock_open_close);
                break;

                case MORPHOLOGY_TI_RECT_SE:
                    execFunc[0] = &vcop_grayscale_open_rect_vloops;
                    context[0] = (EVELIB_KernelContextType)(void *)stParamBlock_open_close;
                    numKernels = 1U;

                    vcop_grayscale_open_rect_init(srcBlkPitch, srcBlkPitch, srcBlkHeightTot, srcPtr_A,
                        se_width, se_height, scratchPtr_C, scratchPtr_A, outputPtr_B, stParamBlock_open_close);
                break;

                case MORPHOLOGY_TI_CROSS_SE:
                    execFunc[0] = &vcop_grayscale_open_cross_vloops;
                    context[0] = (EVELIB_KernelContextType)(void *)stParamBlock_open_close;
                    numKernels = 1U;

                    vcop_grayscale_open_cross_init(srcBlkPitch, srcBlkPitch, srcBlkHeightTot, srcPtr_A,
                        se_width, se_height, scratchPtr_C, scratchPtr_A, outputPtr_B, stParamBlock_open_close);
                break;
                default:
                break;
            }
            break;

        case MORPHOLOGY_TI_CLOSE:

            switch ( seShape )
            {
                case MORPHOLOGY_TI_CUSTOM_SE:
                    execFunc[0] = &vcop_grayscale_close_mask_vloops;
                    context[0] = (EVELIB_KernelContextType)(void *)stParamBlock_open_close;
                    numKernels = 1U;

                    vcop_grayscale_close_mask_init(srcBlkPitch, srcBlkPitch, srcBlkHeightTot, srcPtr_A,
                        se_width, se_height, *sePtr_C, *seReflPtr_C, scratchPtr_C, outputPtr_B, stParamBlock_open_close);
                break;

                case MORPHOLOGY_TI_RECT_SE:
                    execFunc[0] = &vcop_grayscale_close_rect_vloops;
                    context[0] = (EVELIB_KernelContextType)(void *)stParamBlock_open_close;
                    numKernels = 1U;

                    vcop_grayscale_close_rect_init(srcBlkPitch, srcBlkPitch, srcBlkHeightTot, srcPtr_A,
                        se_width, se_height, scratchPtr_C, scratchPtr_A, outputPtr_B, stParamBlock_open_close);

                break;

                case MORPHOLOGY_TI_CROSS_SE:
                    execFunc[0] = &vcop_grayscale_close_cross_vloops;
                    context[0] = (EVELIB_KernelContextType)(void *)stParamBlock_open_close;
                    numKernels = 1U;

                    vcop_grayscale_close_cross_init(srcBlkPitch, srcBlkPitch, srcBlkHeightTot, srcPtr_A,
                        se_width, se_height, scratchPtr_C, scratchPtr_A, outputPtr_B, stParamBlock_open_close);
                break;
                default:
                break;
            }
            break;

        case MORPHOLOGY_TI_TOPHAT:

            switch ( seShape )
            {
                case MORPHOLOGY_TI_CUSTOM_SE:
                    execFunc[0] = &vcop_grayscale_tophat_mask_vloops;
                    context[0] = (EVELIB_KernelContextType)(void *)stParamBlock;
                    numKernels = 1U;

                    vcop_grayscale_tophat_mask_init(srcBlkPitch, srcBlkPitch, srcBlkHeightTot, srcPtr_A,
                        se_width, se_height, *sePtr_C, *seReflPtr_C, scratchPtr_C, outputPtr_B, stParamBlock);
                break;

                case MORPHOLOGY_TI_RECT_SE:
                    execFunc[0] = &vcop_grayscale_tophat_rect_vloops;
                    context[0] = (EVELIB_KernelContextType)(void *)stParamBlock;
                    numKernels = 1U;

                    vcop_grayscale_tophat_rect_init(srcBlkPitch, srcBlkPitch, srcBlkHeightTot, srcPtr_A,
                        se_width, se_height, scratchPtr_C, scratchPtr_A, outputPtr_B, stParamBlock);
                break;

                case MORPHOLOGY_TI_CROSS_SE:
                    execFunc[0] = &vcop_grayscale_tophat_cross_vloops;
                    context[0] = (EVELIB_KernelContextType)(void *)stParamBlock;
                    numKernels = 1U;

                    vcop_grayscale_tophat_cross_init(srcBlkPitch, srcBlkPitch, srcBlkHeightTot, srcPtr_A,
                        se_width, se_height, scratchPtr_C, scratchPtr_A, outputPtr_B, stParamBlock);
                break;
                default:
                break;
            }
            break;

        case MORPHOLOGY_TI_BOTTOMHAT:

            switch ( seShape )
            {
                case MORPHOLOGY_TI_CUSTOM_SE:
                    execFunc[0] = &vcop_grayscale_bottomhat_mask_vloops;
                    context[0] = (EVELIB_KernelContextType)(void *)stParamBlock;
                    numKernels = 1U;

                    vcop_grayscale_bottomhat_mask_init(srcBlkPitch, srcBlkPitch, srcBlkHeightTot, srcPtr_A,
                        se_width, se_height, *sePtr_C, *seReflPtr_C, scratchPtr_C, outputPtr_B, stParamBlock);
                break;

                case MORPHOLOGY_TI_RECT_SE:
                    execFunc[0] = &vcop_grayscale_bottomhat_rect_vloops;
                    context[0] = (EVELIB_KernelContextType)(void *)stParamBlock;
                    numKernels = 1U;

                    vcop_grayscale_bottomhat_rect_init(srcBlkPitch, srcBlkPitch, srcBlkHeightTot, srcPtr_A,
                        se_width, se_height, scratchPtr_C, scratchPtr_A, outputPtr_B, stParamBlock);
                break;

                case MORPHOLOGY_TI_CROSS_SE:
                    execFunc[0] = &vcop_grayscale_bottomhat_cross_vloops;
                    context[0] = (EVELIB_KernelContextType)(void *)stParamBlock;
                    numKernels = 1U;

                    vcop_grayscale_bottomhat_cross_init(srcBlkPitch, srcBlkPitch, srcBlkHeightTot, srcPtr_A,
                        se_width, se_height, scratchPtr_C, scratchPtr_A, outputPtr_B, stParamBlock);
                break;
                default:
                break;
            }
            break;

        case MORPHOLOGY_TI_GRADIENT:

            switch ( seShape )
            {
                case MORPHOLOGY_TI_CUSTOM_SE:
                    execFunc[0] = &vcop_grayscale_morph_grad_mask_vloops;
                    context[0] = (EVELIB_KernelContextType)(void *)stParamBlock;
                    numKernels = 1U;

                    vcop_grayscale_morph_grad_mask_init(srcBlkPitch, srcBlkPitch, srcBlkHeightTot, srcPtr_A,
                        se_width, se_height, *sePtr_C, *seReflPtr_C, scratchPtr_C, scratchPtr_A, outputPtr_B, stParamBlock);
                break;

                case MORPHOLOGY_TI_RECT_SE:
                    execFunc[0] = &vcop_grayscale_morph_grad_rect_vloops;
                    context[0] = (EVELIB_KernelContextType)(void *)stParamBlock;
                    numKernels = 1U;

                    vcop_grayscale_morph_grad_rect_init(srcBlkPitch, srcBlkPitch, srcBlkHeightTot, srcPtr_A,
                        se_width, se_height, scratchPtr_C, scratchPtr_A, outputPtr_B, stParamBlock);
                break;

                case MORPHOLOGY_TI_CROSS_SE:
                    execFunc[0] = &vcop_grayscale_morph_grad_cross_vloops;
                    context[0] = (EVELIB_KernelContextType)(void *)stParamBlock;
                    numKernels = 1U;

                    vcop_grayscale_morph_grad_cross_init(srcBlkPitch, srcBlkPitch, srcBlkHeightTot, srcPtr_A,
                        se_width, se_height, scratchPtr_C, scratchPtr_A, outputPtr_B, stParamBlock);
                break;
                default:
                break;
            }
            break;
            default:
            break;
    }
#endif


    morphology_DMAAutoIncrInit(
        autoIncrementContext,
        src,
        (uint32_t)srcImageWidth,
        (uint32_t)srcImageHeight,
        (int32_t) srcImagePitch,
        dst,
        (uint32_t)dstImageWidth,
        (uint32_t)dstImageHeight,
        (int32_t) dstImagePitch,
        srcPtr_A,
        (uint32_t)srcBlkWidth,
        (uint32_t)srcBlkHeight,
        (int32_t) srcBlkPitch,
        outputPtr_B,
        (uint32_t)dstBlkWidth,
        (uint32_t)dstBlkHeight,
        (int32_t) dstBlkPitch,
        (uint32_t)srcBlkPadX,
        (uint32_t)srcBlkPadY);

    morphology_DMAAutoIncrExec(
        autoIncrementContext,
        execFunc,
        context,
        (uint8_t)numKernels);

    morphology_DMAAutoIncrDeInit();

}


void Grayscale_Morphology_Deinit(Grayscale_Morphology_Obj *handle)
{
#if (!VCOP_HOST_EMULATION)
      Grayscale_Morphology_free(handle->stParamBlock.pblock_dilate);
      Grayscale_Morphology_free(handle->stParamBlock.pblock_erode);
      Grayscale_Morphology_free(handle->stParamBlock.pblock_img_diff);
#endif
      Grayscale_Morphology_free(handle->srcPtr_A);
      Grayscale_Morphology_free(handle->sePtr_C);
      Grayscale_Morphology_free(handle->seReflPtr_C);
      Grayscale_Morphology_free(handle->scratchPtr_C);
      Grayscale_Morphology_free(handle->scratchPtr_A);
      Grayscale_Morphology_free(handle->outputPtr_B);
}

