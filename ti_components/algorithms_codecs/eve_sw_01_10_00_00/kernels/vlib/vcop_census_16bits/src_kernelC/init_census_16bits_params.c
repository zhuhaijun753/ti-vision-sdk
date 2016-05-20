/*******************************************************************************
 **+--------------------------------------------------------------------------+**
 **|                            ****                                          |**
 **|                            ****                                          |**
 **|                            ******o***                                    |**
 **|                      ********_///_****                                   |**
 **|                      ***** /_//_/ ****                                   |**
 **|                       ** ** (__/ ****                                    |**
 **|                           *********                                      |**
 **|                            ****                                          |**
 **|                            ***                                           |**
 **|                                                                          |**
 **|         Copyright (c) 2007-2014 Texas Instruments Incorporated           |**
 **|                        ALL RIGHTS RESERVED                               |**
 **|                                                                          |**
 **| Permission to use, copy, modify, or distribute this software,            |**
 **| whether in part or in whole, for any purpose is forbidden without        |**
 **| a signed licensing agreement and NDA from Texas Instruments              |**
 **| Incorporated (TI).                                                       |**
 **|                                                                          |**
 **| TI makes no representation or warranties with respect to the             |**
 **| performance of this computer program, and specifically disclaims         |**
 **| any responsibility for any damages, special or consequential,            |**
 **| connected with the use of this program.                                  |**
 **|                                                                          |**
 **+--------------------------------------------------------------------------+**
 *******************************************************************************/
/*                                                                            */
/* NAME: init_census_16bits_params                                            */
/*                                                                            */
/* DESCRIPTION:                                                               */
/*                                                                            */
/* The function initializes some parameters passed to "vcop_census_16bits"    */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/* Texas Instruments Incorporated 2010-2014.                                  */
/*============================================================================*/

#include <stdlib.h>
#include <stdio.h>
#include "stdint.h"
#include "vcop_census_16bits_cn.h"
#include "init_census_16bits_params.h"

/* CHECK_MISRA("-15.1")  -> Disable rule 15.1 */
/* Goto statement is used */
/* Deviation is allowed because we use GOTO several times throughout the code but they are all forward GOTO to a single exit point */

int32_t init_census_16bits_params
(
        uint8_t winWidth, 
        uint8_t winHeight,
        uint8_t winHorzStep,
        uint8_t winVertStep,
        uint16_t computeWidth,
        uint16_t computeHeight,
        uint16_t outStride, /* in bytes, must multiple of 4 but not multiple of 32 bytes*/
        uint16_t pOffset[], /* Point to an array of 8 bytes. Call init_census_8bits_params() to initialize content pointed by pOffset*/
        uint8_t sizeOffsetArray, /* Should be 32 */
        uint8_t  pCodeWordMask[], /* Point to an array of (winWidth*winHeight+7)/8 bytes. Call init_census_8bits_params() to initialize content pointed by pCodeWordMask */
        int32_t sizeCodeWordMarkArray, /* Should be (winWidth*winHeight+7)/8 */
        uint8_t  pRowMask[],/* Point to an array of (computeHeight+7)/8 bytes. Call init_census_8bits_params() to initialize content pointed by pRowMask */
        int32_t sizeRowMaskArray, /* Should be (computeHeight+7)/8 */
        uint16_t *scratchStride
) {
    int32_t i, j;
    uint8_t bank[8];
    uint16_t numCensusOrientations= (uint16_t)_CENSUS_WIN_SIZE((uint16_t)winWidth, (uint16_t)winHeight,(uint16_t) winHorzStep, (uint16_t)winVertStep);
    uint16_t numBytesPerCensus= (numCensusOrientations + 7u) / 8u;
    int32_t errorCode= 0;
    
    if (outStride < (numBytesPerCensus*computeWidth)) {
        errorCode= -1;
        goto exitFunc;
    }
    
    if (outStride & 3u) {/* If outStride not multiple of 4, return error */
        errorCode= -2;
        goto exitFunc;
    }
    
    if ((outStride & 31u)== 0) {/* If outStride multiple of 32, return error */
        errorCode= -3;
        goto exitFunc;
    }
    
    if (sizeOffsetArray < 32u) {
        errorCode= -4;
        goto exitFunc;
    }
    
    if (sizeCodeWordMarkArray < (int32_t)numBytesPerCensus) {
        errorCode= -5;
        goto exitFunc;
    }
    
    if (sizeRowMaskArray < (((int32_t)computeHeight+7)/8)) {
        errorCode= -6;
        goto exitFunc;
    }

#if 1
    /*Calculate size of one line used in the first p-scatter, need to be (n*8 + 1) banks or (n*8*4 + 4)=  n*32 + 4 bytes) wide to avoid p-scatter error*/
    *scratchStride= (uint16_t)(((computeHeight + 31u) & (uint16_t)(~31u)) + (uint16_t)4u); /* Round up to next multiple of 32 and then add 4 bytes */ 

    /* Fill the offset array that will be used by p-scatter */
    for(i=0;i<8;i++) {
        pOffset[i]=i*(*scratchStride);
    }
    
    /* Fill the offset array that will be used by p-scatter */
    for(i=0;i<8;i++) {
        pOffset[i+8]=(uint16_t)i*outStride;
    }
#else        
    /* Fill the offset array that will be used by p-scatter */
    for(i=0;i<8;i++) {
        pOffset[i]=i*outStride;
    }
#endif
    /* Verify that all offsets belong to a different bank, otherwise p-scatter will thrown an error */
    
    /* First calculate the bank */
    for(i=0;i<8;i++) {
        bank[i]= (pOffset[i]%32)/4;
    }

    /* Verify bank constraints */
    for(i=0;i<8;i++) {
        for(j=i+1;j<8;j++) {
            if (bank[i]==bank[j]) {
                errorCode= -7; /* return error if bank conflict arises, normally should not happen it code runs up to here without returning previous error code */
                goto exitFunc;
            }
        }
    }
    
    /* First calculate the bank */
    for(i=0;i<8;i++) {
        bank[i]= (pOffset[i+8]%32)/4;
    }

    /* Verify bank constraints */
    for(i=0;i<8;i++) {
        for(j=i+1;j<8;j++) {
            if (bank[i]==bank[j]) {
                errorCode= -8; /* return error if bank conflict arises, normally should not happen it code runs up to here without returning previous error code */
                goto exitFunc;
            }
        }
    }

    /* Initialize mask that will be used to zero-out bits that don't correspond to any valid orientation. Indeed alignment to byte boundary will produce extra
     * orientation bits to be ignored. */
    for(i=0;i<((int32_t)numBytesPerCensus-1);i++) {
        pCodeWordMask[i]= 0xFF;
    }

    /* If numCensusOrientations is not multiple of 8, last codeword mask is not 0xFF but has some bits masked to 0 */
    if (numCensusOrientations & 7u) {
        pCodeWordMask[numBytesPerCensus-1u]= (uint8_t)((uint16_t)((uint16_t)1u<<(numCensusOrientations & (uint16_t)7u)) - (uint16_t)1u);
    }
    else {
        pCodeWordMask[numBytesPerCensus-1u]= (uint8_t)0xFFu;
    }

    /* Initialize row mask. Will be used by predicated store to prevent extra values from being written out, due to usage of p-scatter. */
    for(i=0; i<(((int32_t)computeHeight+7)/8); i++) {
        pRowMask[i]=0xFF;
    }
    
    if (computeHeight & 7u) {
        pRowMask[((computeHeight+7u)/8u) - 1u]= (uint8_t)((uint16_t)(1u<<(computeHeight & (uint16_t)7u))-(uint16_t)1u);
    }

 exitFunc:
    return errorCode;
}

/*RESET_MISRA("15.1")  -> Reset rule 15.1 for GOTO */

