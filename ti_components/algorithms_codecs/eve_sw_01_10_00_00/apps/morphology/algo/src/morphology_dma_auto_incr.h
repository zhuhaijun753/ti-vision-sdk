/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*-----------------------------------------------------------------------*/
/*  NAME : morphology_dma_auto_incr.h                                          */
/*                                                                       */
/*  DESCRIPTION:                                                         */
/*                                                                       */
/*  This file demonstrates double buffering of data from external ->     */
/*  internal memory, and internal -> external memory on an image frame.  */
/*  Data from the image frame is transferred to internal memory on a     */
/*  block by block basis.                                                */
/*                                                                       */
/*  2D -> 1D transfers are used for incoming data and 1D -> 2D transfers */
/*  are used for outgoing data. Two parameter registers are used, 1 for  */
/*  the incoming ping/pong buffers and 1 for the outgoing ping/pong      */
/*  buffers.                                                             */
/*                                                                       */
/*  Autoincrementing at each DMA block transfer completion is used to    */
/*  to reduce the number of times entries in the parameter ram need to   */
/*  be updated. At the end of each block-row, the src and dst pointers   */
/*  are updated in the parameter ram to reflect the starting addresses   */
/*  of the next row of blocks.                                           */
/*-----------------------------------------------------------------------*/

#ifndef MORPHOLOGY_DMA_AUTOINCR_H
#define MORPHOLOGY_DMA_AUTOINCR_H

#include <vcop.h>
#include <stdint.h>

typedef uint16_t *EVELIB_KernelContextType;
typedef void    (*EVELIB_KernelFuncType)(EVELIB_KernelContextType pblock);

/* --------------------------------------------------------------------- */
/*  Start of the main test_harness code.                                 */
/* --------------------------------------------------------------------- */
int32_t morphology_DMAAutoIncrInit(
      uint8_t       *autoIncrementContext,
      uint8_t       *src,
      uint32_t       srcImageWidth,
      uint32_t       srcImageHeight,
      int32_t        srcImagePitch,
      uint8_t       *dst,
      uint32_t       dstImageWidth,
      uint32_t       dstImageHeight,
      int32_t        dstImagePitch,
      uint8_t       *srcBlk,
      uint32_t       srcBlkWidth,
      uint32_t       srcBlkHeight,
      int32_t        srcBlkPitch,
      uint8_t       *dstBlk,
      uint32_t       dstBlkWidth,
      uint32_t       dstBlkHeight,
      int32_t        dstBlkPitch,
      uint32_t       srcBlkPadX,
      uint32_t       srcBlkPadY);


void morphology_DMAAutoIncrDeInit(void);


void morphology_DMAAutoIncrExec(
    uint8_t                 *autoIncrementContext,
    EVELIB_KernelFuncType    execFunc[],
    EVELIB_KernelContextType context[],
    uint8_t                  numKernels);

#endif /* MORPHOLOGY_DMA_AUTOINCR_H */

