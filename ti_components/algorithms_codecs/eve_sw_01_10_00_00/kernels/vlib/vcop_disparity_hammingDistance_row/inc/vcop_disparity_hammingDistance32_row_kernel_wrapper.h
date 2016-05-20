/*==========================================================================*/
/*      Copyright (C) 2009-2015 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       vcop_disparity_hammingDistance32_row_kernel_wrapper.c
 *
 *  @brief      This header file defines the prototype of wrapper functions that call the disparity kernel function corresponding
 *                 to the use case specified by rFlag.
 */

#ifndef _TI_vcop_disparity_hammingDistance32_row_kernel_wrapper_h_
#define _TI_vcop_disparity_hammingDistance32_row_kernel_wrapper_h_

#include <stdint.h>

#include "vcop_disparity_hammingDistance32_row_kernel.h"
#include "vcop_disparity_hammingDistance32_RL_row_kernel.h"

/* Basic Runner Function */
void wrapper_vcop_disparity_hammingDistance32_first_row_firstCall(
        __vptr_uint32 pLeft,
        __vptr_uint32 pRight,
        uint16_t leftStride,
        uint16_t rightStride,
        uint8_t winWidth,
        uint8_t winHeight,
        __vptr_uint8 pDisparityOutput,
        __vptr_uint16 pMinCostOutput,
        __vptr_uint16 pAllCostOutput,
        uint16_t allCostOutputStride,
        uint16_t width,
        uint8_t numDisparities,
        uint8_t disparityStep,
        __vptr_uint8 pCollateMask,
        __vptr_uint16 pOffset,
        __vptr_int16 pScratch0,
        __vptr_int16 pCarryOverOut,
        uint16_t scratchStride,
        uint8_t rlFlag);

/* Parameter Block Initialization Function */
uint32_t wrapper_vcop_disparity_hammingDistance32_first_row_firstCall_init(
        __vptr_uint32 pLeft,
        __vptr_uint32 pRight,
        uint16_t leftStride,
        uint16_t rightStride,
        uint8_t winWidth,
        uint8_t winHeight,
        __vptr_uint8 pDisparityOutput,
        __vptr_uint16 pMinCostOutput,
        __vptr_uint16 pAllCostOutput,
        uint16_t allCostOutputStride,
        uint16_t width,
        uint8_t numDisparities,
        uint8_t disparityStep,
        __vptr_uint8 pCollateMask,
        __vptr_uint16 pOffset,
        __vptr_int16 pScratch0,
        __vptr_int16 pCarryOverOut,
        uint16_t scratchStride,
        uint16_t pblock[],
        uint8_t rlFlag);

/* Basic Runner Function */
void wrapper_vcop_disparity_hammingDistance32_first_row(
        __vptr_uint32 pLeft,
        __vptr_uint32 pRight,
        uint16_t leftStride,
        uint16_t rightStride,
        uint8_t winWidth,
        uint8_t winHeight,
        __vptr_uint8 pDisparityOutput,
        __vptr_uint16 pMinCostOutput,
        __vptr_uint16 pAllCostOutput,
        uint16_t allCostOutputStride,
        uint16_t width,
        uint8_t numDisparities,
        uint8_t disparityStep,
        __vptr_uint8 pCollateMask,
        __vptr_uint16 pOffset,
        __vptr_int16 pScratch0,
        __vptr_int16 pCarryOverIn,
        __vptr_int16 pCarryOverOut,
        uint16_t scratchStride,
        uint8_t rlFlag);

/* Parameter Block Initialization Function */
uint32_t wrapper_vcop_disparity_hammingDistance32_first_row_init(
        __vptr_uint32 pLeft,
        __vptr_uint32 pRight,
        uint16_t leftStride,
        uint16_t rightStride,
        uint8_t winWidth,
        uint8_t winHeight,
        __vptr_uint8 pDisparityOutput,
        __vptr_uint16 pMinCostOutput,
        __vptr_uint16 pAllCostOutput,
        uint16_t allCostOutputStride,
        uint16_t width,
        uint8_t numDisparities,
        uint8_t disparityStep,
        __vptr_uint8 pCollateMask,
        __vptr_uint16 pOffset,
        __vptr_int16 pScratch0,
        __vptr_int16 pCarryOverIn,
        __vptr_int16 pCarryOverOut,
        uint16_t scratchStride,
        uint16_t pblock[],
        uint8_t rlFlag);

/* Basic Runner Function */
void wrapper_vcop_disparity_hammingDistance32_nth_row_firstCall(
        __vptr_uint32 pLeft_prevRow,
        __vptr_uint32 pLeft_lastRow,
        __vptr_uint32 pRight_prevRow,
        __vptr_uint32 pRight_lastRow,
        uint16_t leftStride,
        uint16_t rightStride,
        uint8_t winWidth,
        uint8_t winHeight,
        __vptr_uint8 pDisparityOutput,
        __vptr_uint16 pMinCostOutput,
        __vptr_uint16 pAllCostOutput,
        uint16_t allCostOutputStride,
        uint16_t width,
        uint8_t numDisparities,
        uint8_t disparityStep,
        __vptr_uint8 pCollateMask,
        __vptr_uint16 pOffset,
        __vptr_int16 pScratch0,
        __vptr_int16 pScratch1,
        __vptr_int16 pScratch2,
        __vptr_int16 pCarryOverOut,
        uint16_t scratchStride,
        uint8_t rlFlag);

/* Parameter Block Initialization Function */
uint32_t wrapper_vcop_disparity_hammingDistance32_nth_row_firstCall_init(
        __vptr_uint32 pLeft_prevRow,
        __vptr_uint32 pLeft_lastRow,
        __vptr_uint32 pRight_prevRow,
        __vptr_uint32 pRight_lastRow,
        uint16_t leftStride,
        uint16_t rightStride,
        uint8_t winWidth,
        uint8_t winHeight,
        __vptr_uint8 pDisparityOutput,
        __vptr_uint16 pMinCostOutput,
        __vptr_uint16 pAllCostOutput,
        uint16_t allCostOutputStride,
        uint16_t width,
        uint8_t numDisparities,
        uint8_t disparityStep,
        __vptr_uint8 pCollateMask,
        __vptr_uint16 pOffset,
        __vptr_int16 pScratch0,
        __vptr_int16 pScratch1,
        __vptr_int16 pScratch2,
        __vptr_int16 pCarryOverOut,
        uint16_t scratchStride,
        uint16_t pblock[],
        uint8_t rlFlag);

/* Basic Runner Function */
void wrapper_vcop_disparity_hammingDistance32_nth_row(
        __vptr_uint32 pLeft_prevRow,
        __vptr_uint32 pLeft_lastRow,
        __vptr_uint32 pRight_prevRow,
        __vptr_uint32 pRight_lastRow,
        uint16_t leftStride,
        uint16_t rightStride,
        uint8_t winWidth,
        uint8_t winHeight,
        __vptr_uint8 pDisparityOutput,
        __vptr_uint16 pMinCostOutput,
        __vptr_uint16 pAllCostOutput,
        uint16_t allCostOutputStride,
        uint16_t width,
        uint8_t numDisparities,
        uint8_t disparityStep,
        __vptr_uint8 pCollateMask,
        __vptr_uint16 pOffset,
        __vptr_int16 pScratch0,
        __vptr_int16 pScratch1,
        __vptr_int16 pScratch2,
        __vptr_int16 pCarryOverIn,
        __vptr_int16 pCarryOverOut,
        uint16_t scratchStride,
        uint8_t rlFlag);

/* Parameter Block Initialization Function */
uint32_t wrapper_vcop_disparity_hammingDistance32_nth_row_init(
        __vptr_uint32 pLeft_prevRow,
        __vptr_uint32 pLeft_lastRow,
        __vptr_uint32 pRight_prevRow,
        __vptr_uint32 pRight_lastRow,
        uint16_t leftStride,
        uint16_t rightStride,
        uint8_t winWidth,
        uint8_t winHeight,
        __vptr_uint8 pDisparityOutput,
        __vptr_uint16 pMinCostOutput,
        __vptr_uint16 pAllCostOutput,
        uint16_t allCostOutputStride,
        uint16_t width,
        uint8_t numDisparities,
        uint8_t disparityStep,
        __vptr_uint8 pCollateMask,
        __vptr_uint16 pOffset,
        __vptr_int16 pScratch0,
        __vptr_int16 pScratch1,
        __vptr_int16 pScratch2,
        __vptr_int16 pCarryOverIn,
        __vptr_int16 pCarryOverOut,
        uint16_t scratchStride,
        uint16_t pblock[],
        uint8_t rlFlag);

/***********************************************************/
#endif

