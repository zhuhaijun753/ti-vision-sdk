/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_multiblock_bilinear_interp_7x7_u8_int.h
 *
 *  @brief      This header defines internal structures for multi block bilinear
 *              interpolation kernel for neighboorhood of 7x7 8-bit pixel data into BAM.
 */
#ifndef BAM_MULTIBLOCK_BILINEAR_INTERP_7X7_U8_INT_H_
#define BAM_MULTIBLOCK_BILINEAR_INTERP_7X7_U8_INT_H_

#include <stdint.h>
#include <vcop.h>

#include "evealgframework.h"
#include "bam_multiblock_bilinear_interp_7x7_u8.h"

#define NUM_IN_BLOCKS       (2 )
#define NUM_OUT_BLOCKS      (1 )
#define NUM_INTERNAL_BLOCKS (1 )

#define PARAMS_IDX          (0 )
#define VCOP_LK_Q_FORMATE_PEL_RESOLN (4)

#define INP_IDX1 (BAM_MULTIBLOCK_BILINEAR_INTERP_7X7_U8_INPUT_PORT_INP1)  
#define INP_IDX2 (BAM_MULTIBLOCK_BILINEAR_INTERP_7X7_U8_INPUT_PORT_INP2)  

#define OUT_IDX  (BAM_MULTIBLOCK_BILINEAR_INTERP_7X7_U8_OUTPUT_PORT    ) 

typedef struct 
{
    /* Must always follow this order: pInternalBlock[], pInBlock[], pOutputBlock[], args */
    void *pInternalBlock[NUM_INTERNAL_BLOCKS];
    void *pInBlock[NUM_IN_BLOCKS];
    void *pOutBlock[NUM_OUT_BLOCKS];
    BAM_Multiblock_Bilinear_Interp_7x7_U8_Args kernelArgs;
} BAM_Multiblock_Bilinear_Interp_7x7_U8_Context;

#endif /* BAM_MULTIBLOCK_BILINEAR_INTERP_7X7_U8_INT_H_ */
