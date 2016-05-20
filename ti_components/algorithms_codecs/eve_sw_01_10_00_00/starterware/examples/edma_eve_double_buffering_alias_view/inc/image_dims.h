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
/* of 8. Also, the block width and height must be a multiple of  */
/* the source dimensions.                                        */
/* ------------------------------------------------------------- */

#define BLK_WIDTH   120    // 16  // 40  // 72  // 120 // 144
#define BLK_HEIGHT  62    // 62  // 31  // 12  // 62 // 31

