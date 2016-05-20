/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/
/*-----------------------------------------------------------------------*/
/*  NAME : image_dims.h                                                  */
/*                                                                       */
/*  DESCRIPTION:                                                         */
/*                                                                       */
/*  This header files defines the dimensions of the source image and DMA */
/* block transfers.                                                      */
/*                                                                       */
/*=======================================================================*/
/*  Texas Instruments Incorporated 2012.                                 */
/*-----------------------------------------------------------------------*/


/* ------------------------------------------------------------- */
/* Source image dimensions                                       */
/* ------------------------------------------------------------- */

#define IMG_WIDTH        720
#define IMG_HEIGHT       372
#define IMG_LINE_PITCH   720


/* ------------------------------------------------------------- */
/* DMA Block Transfer Sizes                                      */
/* Since processing on VCOP, blocks widths should be a multiple  */
/* of 8.                                                         */ 
/* ------------------------------------------------------------- */

#define NUM_ROI       6
#define NUM_ITER      2
#define DMA_BLOCK_W   64   // 64 // 32  // 16 // 128
#define DMA_BLOCK_H   64   // 64 // 23  // 45 // 10
#define NUM_AUTO_INCR (NUM_ROI*NUM_ITER) + 2



