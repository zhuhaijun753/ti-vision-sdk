/*
 *******************************************************************************
 *
 * EVE EDMA Memcpy Utility
 *
 *  Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 *******************************************************************************
*/

/**
 *****************************************************************************
 * @file
 *  edma_utils_memcpy.h
 *
 * @brief    This file contains the data types and util function prototype for
 *              configuring EDMA memcpy usecase.
 *
 * @remarks
 *
 * @author: Anshu Jain (anshu_jain@ti.com)
 * @version 0.1 (Aug 2013) : First version of eve edma utils function
 *
 *****************************************************************************
 */


#ifndef EDMA_UTILS_MEMCPY_H_
#define EDMA_UTILS_MEMCPY_H_

#pragma CHECK_MISRA ("none")
#include <stdint.h>
#pragma RESET_MISRA ("required")


/* ==================================================
 *  @func     EDMA_UTILS_memcpy2D
 *
 *  @desc     This function used EDMA module of eve subsytem to do a 2D memcpy
 *
 *  @modif
 *
 *  @inputs   This function takes following Inputs
 *                  dstPtr :
 *                          Pointer to destination
 *                  srcPtr :
 *                          Pointer to source
 *                  width :
 *                          width of 2D block to be transfered
 *                  height :
 *                          height of 2D block to be transfered
 *                  dstStride :
 *                          Stride/Pitch for dstPtr
 *                  srcStride :
 *                          Stride/Pitch for srcPtr
 *
 *  @outputs NONE
 *
 *  @return    0 : Success
 *                  -1 : Failure
 *
 *  =======================================================
 */
/* This decleration violates MISRA-C Rule 16.7 : MISRA.PPARAM.NEEDS.CONST.
This cannot be avoided because dstPtr is actually modified by the EDMA hardware
but from the code compiler cannot detect this and hence returns a warning */
int32_t EDMA_UTILS_memcpy2D
(
    void        *dstPtr,
    const void  *srcPtr,
    uint16_t     width,
    uint16_t     height,
    int16_t      dstStride,
    int16_t      srcStride
);


#endif /*#define EDMA_UTILS_MEMCPY_H_*/

