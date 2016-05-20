/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_normalizedGradXyList_int.h
 *
 *  @brief      This header defines internal structures  for integrating calculation of normalized
  *                  gradient X and Y into BAM

 */
#ifndef BAM_NORMALIZEDGRADXYLIST_INT_H_

#define BAM_NORMALIZEDGRADXYLIST_INT_H_

#include <stdint.h>
#include <vcop.h>


#include "bam_normalizedGradXyList.h"

/* LUT is storing the value of 1 / (sqrt ( y / 4^((int)log4(y) )*/
#define RECI_SQRT_LUT_SIZE      (768)
#define RECI_SQRT_LUT_NUM_CPY   (8)

typedef struct
{
    /* Must always follow this order: pInternalBlock[], pInBlock[], pOutputBlock[], args */
    void *pInternalBlock[BAM_NORMALIZED_GRADXY_LIST_INTERNAL_NUM_BLOCK];
    void *pInBlock[BAM_NORMALIZED_GRADXY_LIST_NUM_INPUT_BLOCKS];
    void *pOutBlock[BAM_NORMALIZED_GRADXY_LIST_NUM_OUTPUT_BLOCKS];
    BAM_NormalizedGradXyList_Args kernelArgs;
    BAM_NormalizedGradXyList_CtrlArgs ctrlArgs;
    uint8_t * pBlockGradientsXyList;
    uint8_t * pBlockGradientsXyMagLutIndexCalulcation;
    uint8_t * pBlockReciprocalSqrtLookup;
    uint8_t * pBlockGradientsXyUnitVecs;
    uint8_t * pBlockListSizeUpdate;
    uint8_t * pGradXyPtr;
    uint8_t * pLutIdxPtr;
    uint8_t * pReciSqrtLut;
    uint8_t * pXsequence;
    uint8_t * pLog4aPtr;
    uint16_t * pListSizePtr;
    uint16_t * pListSizeWbufPtr;
    uint8_t * pReciprocalLutOutput;
    uint32_t * pUpperLeftXyPtr[2];
    uint8_t  pingPongFlag;
    uint16_t blockCnt;
    uint16_t blockStartX;
    uint16_t blockStartY;
    uint16_t currentListSize;
} BAM_NormalizedGradXyList_Context;

#endif /* BAM_NORMALIZEDGRADXYLIST_INT_H_ */

