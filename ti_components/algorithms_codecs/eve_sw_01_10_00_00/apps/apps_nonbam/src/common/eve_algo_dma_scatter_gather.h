/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
#ifndef EVE_ALGO_DMA_SCATTER_GATHER_H
#define EVE_ALGO_DMA_SCATTER_GATHER_H

#include <vcop/vcop.h>
#include <stdint.h>
#include "evestarterware.h"
#include "dma_funcs.h"


typedef void (*EVELIB_KernelFuncType)(void *context);
typedef unsigned char * EVELIB_KernelContextType;


/* --------------------------------------------------------------------- */
/*  Start of the main test_harness code.                                 */
/* --------------------------------------------------------------------- */
int EVELIB_algoDMAScatterGatherInit(
    DMA_resourceStruct  *edmaResources,
    CSL_EdmaccRegsOvly  edmaCc,
    int                 numTransfersIn,
    unsigned int        srcImageWidth,
    unsigned int        srcImageHeight,
    int                 srcImagePitch,
    int                 numTransfersOut,
    unsigned int        dstImageWidth,
    unsigned int        dstImageHeight,
    int                 dstImagePitch,
    unsigned int        srcBlkWidth,
    unsigned int        srcBlkHeight,
    int                 srcBlkPitch,
    unsigned int        dstBlkWidth,
    unsigned int        dstBlkHeight,
    int                 dstBlkPitch,
    unsigned int        srcBlkPadX,
    unsigned int        srcBlkPadY);


void EVELIB_algoDMAScatterGatherDeInit(
    DMA_resourceStruct  * edmaResources,
    CSL_EdmaccRegsOvly  edmaCc);



void EVELIB_algoDMAScatterGatherProcess
(
    DMA_resourceStruct  *edmaResources,
    CSL_EdmaccRegsOvly  edmaCc,
    unsigned char       **srcPtrList,
    int                 numTransfersIn,
    unsigned int        srcImageWidth,
    unsigned int        srcImageHeight,
    int                 srcImagePitch,
    unsigned char       **dstPtrList,
    int                 numTransfersOut,
    unsigned int        dstImageWidth,
    unsigned int        dstImageHeight,
    int                 dstImagePitch,
    unsigned char       **srcBlkPtrList,
    unsigned int        srcBlkWidth,
    unsigned int        srcBlkHeight,
    int                 srcBlkPitch,
    unsigned char       **dstBlkPtrList,
    unsigned int        dstBlkWidth,
    unsigned int        dstBlkHeight,
    int                 dstBlkPitch,
    unsigned int        srcBlkPadX,
    unsigned int        srcBlkPadY,
    unsigned int        numBlocks,
    EVELIB_KernelFuncType execFunc[],
    EVELIB_KernelContextType context[],
    unsigned int        numKernels,
    int32_t             sequential
);


#endif
/*-----------------------------------------------------------------------*/
/*  End of file eve_algo_scatter_gather_incr.h                                     */
/*=======================================================================*/
/*  Texas Instruments incorporated 2013.                                 */
/*-----------------------------------------------------------------------*/


