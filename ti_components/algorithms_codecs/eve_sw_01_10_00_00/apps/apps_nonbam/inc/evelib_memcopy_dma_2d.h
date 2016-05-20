/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
*  @file       evelib_memcopy_dma_2d.h
*
*  @brief      EDMA 2D Memcopy Applet
*
* This header defines all types, constants, and functions shared by all
* implementations of the EDMA 2D Copy interface.
*
*/

#pragma CHECK_MISRA ("none")
#include <stdint.h>
#pragma RESET_MISRA ("required")

#ifndef EVELIB_MEMCOPY_DMA_2D_H
#define EVELIB_MEMCOPY_DMA_2D_H

/**
*  @brief      Used for Performing 2D copy using DMA.
*
*  @param[in] sourcePtr     Starting address of the padding data
*  @param[in] destPtr       Starting address of the location to be padded.
*  @param[in] widthBytes    Width of the buffer (in bytes).
*  @param[in] height        Height of the buffer.
*  @param[in] srcStride     Stride of the source buffer.
*  @param[in] dstStride     Stride of the destination buffer.
*
*  @code
*   void EVELIB_memcopyDMA2D(uint8_t     *sourcePtr,
*                            uint8_t     *destPtr,
*                            uint32_t     widthBytes,
*                            uint32_t     height,
*                            int32_t      srcStride,
*                            int32_t      dstStride)
*  @endcode
*
*  @return      Void
*
*/
void EVELIB_memcopyDMA2D(uint8_t     *sourcePtr,
                   uint8_t      *destPtr,
                   uint32_t     widthBytes,
                   uint32_t     height,
                   int32_t      srcStride,
                   int32_t      dstStride);
#endif
/*-----------------------------------------------------------------------*/
/*  End of file evelib_dma_copy_2d.h                                     */
/*=======================================================================*/
/*  Texas Instruments incorporated 2013.                                 */
/*-----------------------------------------------------------------------*/

