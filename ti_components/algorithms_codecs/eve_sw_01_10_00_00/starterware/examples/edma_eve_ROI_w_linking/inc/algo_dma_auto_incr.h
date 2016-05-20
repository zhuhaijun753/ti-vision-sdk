/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*-----------------------------------------------------------------------*/
/*  NAME : algo_dma_auto_incr.c                                          */
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
/*=======================================================================*/
/*  Texas Instruments incorporated 2012.                                 */
/*-----------------------------------------------------------------------*/


#include "dma_funcs.h"
#include "dma_resource.h"


void algo_dma_auto_incr
(
    CSL_EdmaccRegsOvly  edma_cc,
    DMA_resourceStruct *edmaResources,
    unsigned char       *src_proc,
    unsigned char       *dst_proc,
    unsigned int        chan_in,
    unsigned int        chan_out,
    Bool                *trf_pend
);


