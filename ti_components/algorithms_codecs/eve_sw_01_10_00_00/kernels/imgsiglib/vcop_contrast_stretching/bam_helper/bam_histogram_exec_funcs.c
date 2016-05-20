/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_histogram_exec_funcs.c
 *
 *  @brief      This file defines interfaces for integrating contrast stretching
                    kernels into BAM.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vcop.h>

#include "bam_histogram_int.h"
#include "bam_histogram.h"
#include "vcop_contrast_stretching_kernel.h" /* compiler should take care of include path */

/* Function Prototypes */
static BAM_Status Bam_Histogram_initFrame(void *kernelContext);
static BAM_Status Bam_Histogram_computeFrame(void *kernelContext);
static BAM_Status Bam_Histogram_control(void *kernelContext,
                                                        void * kernelCtlArg);

static BAM_Status Bam_Histogram_initFrame(void *kernelContext)
{
  BAM_Histogram_Context *context = (BAM_Histogram_Context *) kernelContext;

  context->blockCnt = 0;

  vcop_memset((uint32_t *)context->pInternalBlock[HISTOGRAM_INTERNAL_HISTOGRAM8COPY_IDX],
              0,
              HISTOGRAM_NUM_BINS * sizeof(uint32_t) * HISTOGRAM_NUM_COPIES);

#if (!VCOP_HOST_EMULATION)
  vcop_histogram_8c_word_init(
    context->pInBlock[BAM_HISTOGRAM_INPUT_BLOCK_PORT],
    context->kernelArgs.blkWidth,
    context->kernelArgs.blkHeight,
    context->kernelArgs.inPitch,
    context->pInternalBlock[HISTOGRAM_INTERNAL_HISTOGRAM8COPY_IDX],
    context->pInternalBlock[HISTOGRAM_INTERNAL_PARAMS_IDX]
  );
#endif

    return 0;
}

static BAM_Status Bam_Histogram_computeFrame(void *kernelContext)
{
    BAM_Histogram_Context *context = (BAM_Histogram_Context *) kernelContext;

  if ( context->blockCnt < context->totalBlockCnt)
  {
#if (!VCOP_HOST_EMULATION)
    vcop_histogram_8c_word_vloops(context->pInternalBlock[HISTOGRAM_INTERNAL_PARAMS_IDX]);
#else
    vcop_histogram_8c_word(
      context->pInBlock[BAM_HISTOGRAM_INPUT_BLOCK_PORT],
      context->kernelArgs.blkWidth,
      context->kernelArgs.blkHeight,
      context->kernelArgs.inPitch,
      context->pInternalBlock[HISTOGRAM_INTERNAL_HISTOGRAM8COPY_IDX]
    );
#endif
  }

  context->blockCnt++;
  return 0;
}

static BAM_Status Bam_Histogram_control(void *kernelContext,
                                                        void * kernelCtlArg)
{

  BAM_Histogram_Context *context = (BAM_Histogram_Context *) kernelContext;

  BAM_Histogram_CtrlArgs * args = (BAM_Histogram_CtrlArgs *)kernelCtlArg;

  if ( args->cmdId == BAM_HISTOGRAM_CTRL_CMDID_GET_HISTOGRAM8COPY_WBUF )
  {
    args->ctrlArgs = context->pInternalBlock[HISTOGRAM_INTERNAL_HISTOGRAM8COPY_IDX];
  }

  if ( args->cmdId == BAM_HISTOGRAM_CTRL_CMDID_SET_IMAGE_HEIGHT )
  {
    BAM_Histogram_ImageDim_CtrlArgs * imageDims = ( BAM_Histogram_ImageDim_CtrlArgs *)
                                                            args->ctrlArgs;
    uint16_t numHorzBlock;
    uint16_t numVertBlock;
    numHorzBlock = imageDims->imageWidth/ context->kernelArgs.blkWidth;
    numVertBlock = imageDims->imageHeight/ context->kernelArgs.blkHeight;
    context->totalBlockCnt = numHorzBlock * numVertBlock;
  }

  return 0;
}


BAM_KernelExecFuncDef gBAM_TI_histogramExecFunc =
{
  NULL,
  &Bam_Histogram_initFrame,
  &Bam_Histogram_computeFrame,
  NULL,
  &Bam_Histogram_control,
  NULL
};

