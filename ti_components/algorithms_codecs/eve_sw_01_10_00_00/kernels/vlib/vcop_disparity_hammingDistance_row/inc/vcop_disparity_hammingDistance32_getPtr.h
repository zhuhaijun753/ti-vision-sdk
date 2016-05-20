/*==========================================================================*/
/*      Copyright (C) 2009-2014 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       vcop_disparity_hammingDistance32_getPtr.h
 *
 *  @brief      This file defines interfaces for functions used for updating the param registers corresponding to pointers
 *              to some rows belonging to the left and right images. These functions are useful in case a line circular buffer
 *              is used to limit the amount of input data that needs to be brought in for every row calculation. When a line circular
 *              buffer is implemented, a sliding window mechanism is used and thus row pointers must be updated.
 */
#ifndef _VCOP_DISPARITY_HAMMING_DISTANCE32_COPY_GETPTR
#define _VCOP_DISPARITY_HAMMING_DISTANCE32_COPY_GETPTR

#include <stdint.h>

/*
 * vcop_disparity_hammingDistance32_nth_row_firstCall_getPtr() returns the half-word offsets 
 * from the pblock pointer associated to vcop_disparity_hammingDistance32_nth_row_firstCall().
 * Each offset corresponds to the location where pointers pLeft_prevRow, pLeft_lastRow,
 * pRight_prevRow, pRight_lastRow are used. Each pointer is used 5 times and thus leftPrevRowOffset, 
 * leftLastRowOffset, rightPrevRowOffset, rightLastRowOffset are empty arrays of 5 elements that are filled
 * by the function. The parameter sizeOffsetArray should be >= 5.
 * winWidth input parmeter is used because pLeft_prevRow, pLeft_lastRow, pRight_prevRow, pRight_lastRow
 * are not used as raw values but instead get massaged with winWidth before being incorporated in the param registers
 * block.
 * If the function does not find anyone of the locations, -1 is returned instead of 0. 
 */
int32_t vcop_disparity_hammingDistance32_nth_row_firstCall_getPtr(
        const uint16_t* pblock,
        const uint16_t    paramCount,
        const uint32_t    pLeft_prevRow,
        const uint32_t    pLeft_lastRow,
        const uint32_t    pRight_prevRow,
        const uint32_t    pRight_lastRow,
        const uint16_t    winWidth,
        const uint8_t     disparityStep,
        uint16_t    *leftPrevRowOffset,
        uint16_t    *leftLastRowOffset,
        uint16_t    *rightPrevRowOffset,
        uint16_t    *rightLastRowOffset,
        const uint8_t sizeOffsetArray,
        const uint8_t rlFlag
);

/*
 * vcop_disparity_hammingDistance32_nth_row_firstCall_setPtr() take the input pointers pLeft_prevRow, pLeft_lastRow,
 * pRight_prevRow, pRight_lastRow and write them at locations specified in the arrays of 5 pointers leftPrevRowPtr,
 * leftLastRowPtr, rightPrevRowPtr, rightLastRowPtr. The function does not write the raw values of these pointers but
 * instead massage them with the parameter winWidth.
 */
void vcop_disparity_hammingDistance32_nth_row_firstCall_setPtr(
        const uint32_t    pLeft_prevRow,
        const uint32_t    pLeft_lastRow,
        const uint32_t    pRight_prevRow,
        const uint32_t    pRight_lastRow,
        const uint16_t    winWidth,
        const uint8_t     disparityStep,
        uint32_t    **leftPrevRowPtr,
        uint32_t    **leftLastRowPtr,
        uint32_t    **rightPrevRowPtr,
        uint32_t    **rightLastRowPtr,
        const uint8_t rlFlag
);

/*
 * vcop_disparity_hammingDistance32_nth_row_getPtr() returns the half-word offsets 
 * from the pblock pointer associated to vcop_disparity_hammingDistance32_nth_row().
 * Each offset corresponds to the location where pointers pLeft_prevRow, pLeft_lastRow,
 * pRight_prevRow, pRight_lastRow are used. Each pointer is used 4 times and thus leftPrevRowOffset, 
 * leftLastRowOffset, rightPrevRowOffset, rightLastRowOffset are empty arrays of 4 elements that are filled
 * by the function. The parameter sizeOffsetArray should be >= 4.
 * winWidth input parmeter is used because pLeft_prevRow, pLeft_lastRow, pRight_prevRow, pRight_lastRow
 * are not used as raw values but instead get massaged with winWidth before being incorporated in the param registers
 * block.
 * If the function does not find anyone of the locations, -1 is returned instead of 0. 
 */
int32_t vcop_disparity_hammingDistance32_nth_row_getPtr(
        const uint16_t* pblock,
        const uint16_t    paramCount,
        const uint32_t    pLeft_prevRow,
        const uint32_t    pLeft_lastRow,
        const uint32_t    pRight_prevRow,
        const uint32_t    pRight_lastRow,
        const uint16_t    winWidth,
        const uint8_t     disparityStep,
        uint16_t    *leftPrevRowOffset,
        uint16_t    *leftLastRowOffset,
        uint16_t    *rightPrevRowOffset,
        uint16_t    *rightLastRowOffset,
        const uint8_t sizeOffsetArray,
        const uint8_t rlFlag
);

/*
 * vcop_disparity_hammingDistance32_nth_row_setPtr() take the input pointers pLeft_prevRow, pLeft_lastRow,
 * pRight_prevRow, pRight_lastRow and write them at locations specified in the arrays of 4 pointers leftPrevRowPtr,
 * leftLastRowPtr, rightPrevRowPtr, rightLastRowPtr. The function does not write the raw values of these pointers but
 * instead massage them with the parameter winWidth.
 */
void vcop_disparity_hammingDistance32_nth_row_setPtr(
        const uint32_t    pLeft_prevRow,
        const uint32_t    pLeft_lastRow,
        const uint32_t    pRight_prevRow,
        const uint32_t    pRight_lastRow,
        const uint16_t    winWidth,
        const uint8_t     disparityStep,
        uint32_t    **leftPrevRowPtr,
        uint32_t    **leftLastRowPtr,
        uint32_t    **rightPrevRowPtr,
        uint32_t    **rightLastRowPtr,
        const uint8_t rlFlag
);


#endif
