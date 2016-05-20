/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
*  @file       evelib_edma_frame_padding.h
*
*  @brief      Border Padding Applet using EDMA.
*
*  This header defines all types, constants, and functions shared by all
*  implementations of the EDMA Padding interface.
*
*/

#pragma CHECK_MISRA ("none")
#include <stdint.h>
#pragma RESET_MISRA ("required")

#ifndef EVELIB_EDMA_FRAME_PADDING_H
#define EVELIB_EDMA_FRAME_PADDING_H

/**
*  @brief      Used for padding the top and bottom borders of the frame.
*
*  @param[in] padSourcePtr     Starting address of the padding data
*  @param[in] padDestPtr       Starting address of the location to be padded.
*  @param[in] padWidth         Padding width (in bytes).
*  @param[in] padHeight        Padding Height.
*  @param[in] srcDataStride    Stride of the source buffer.
*  @param[in] dstDataStride    Stride of the destination buffer.
*  @param[in] padPixelSize     Size of the data to be padded (in lines).
*                              A total of padPixelSize*padHeight lines will be copied.
*
*  @code
*      EVELIB_padVertEDMA(uint8_t   *padSourcePtr,
*                         uint8_t   *padDestPtr,
*                         uint32_t   padWidth,
*                         uint32_t   padHeight,
*                         int32_t    srcDataStride,
*                         int32_t    dstDataStride,
*                         int32_t    padPixelSize)
*  @endcode
*
*  @return      Void
*
*  @remarks     This functions expects dmaStateStruct and edmaCc are initialized before the call.
*
*/
void EVELIB_padVertEDMA(uint8_t     *padSourcePtr,
                       uint8_t      *padDestPtr,
                       uint32_t     padWidth,
                       uint32_t     padHeight,
                       int32_t      srcDataStride,
                       int32_t      dstDataStride,
                       int32_t      padPixelSize);

/**
*  @brief      Used for padding the left and right borders of the frame.
*
*  @param[in] padSourcePtr     Starting address of the padding data
*  @param[in] padDestPtr       Starting address of the location to be padded.
*  @param[in] padWidth         Padding width (in bytes).
*  @param[in] padHeight        Padding Height.
*  @param[in] srcDataStride    Stride of the source buffer.
*  @param[in] dstDataStride    Stride of the destination buffer.
*  @param[in] padPixelSize     Size of the data to be padded (in lines).
*                              A total of padPixelSize*padHeight lines will be copied.
*
*  @code
*      EVELIB_padHorzEDMA(uint8_t   *padSourcePtr,
*                         uint8_t   *padDestPtr,
*                         uint32_t   padWidth,
*                         uint32_t   padHeight,
*                         int32_t    srcDataStride,
*                         int32_t    dstDataStride,
*                         int32_t    padPixelSize)
*  @endcode
*
*  @return      Void
*
*  @remarks     This functions expects dmaStateStruct and edmaCc are initialized before the call.
*
*/
void EVELIB_padHorzEDMA(uint8_t     *padSourcePtr,
                       uint8_t      *padDestPtr,
                       uint32_t     padWidth,
                       uint32_t     padHeight,
                       int32_t      srcDataStride,
                       int32_t      dstDataStride,
                       int32_t      padPixelSize);

#endif
/*-----------------------------------------------------------------------*/
/*  End of file evelib_edma_frame_padding.h                              */
/*=======================================================================*/
/*  Texas Instruments incorporated 2013.                                 */
/*-----------------------------------------------------------------------*/
