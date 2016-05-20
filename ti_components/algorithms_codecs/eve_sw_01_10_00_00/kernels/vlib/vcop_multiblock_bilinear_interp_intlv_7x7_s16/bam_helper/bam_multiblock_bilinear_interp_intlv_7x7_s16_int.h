/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_multiblock_bilinear_interp_intlv_7x7_s16_int.h
 *
 *  @brief      This header defines internal structures for multi block bilinear
 *              interpolation kernel for neighboorhood of 7x7 signed 16-bit gradient
 *              pixel data which includes gradient along X and Y directions in
 *              interleaved format into BAM.
 */
#ifndef BAM_MULTIBLOCK_BILINEAR_INTERP_INTLV_7X7_S16_INT_H_
#define BAM_MULTIBLOCK_BILINEAR_INTERP_INTLV_7X7_S16_INT_H_

#include <stdint.h>
#include <vcop.h>

#include "evealgframework.h"
#include "bam_multiblock_bilinear_interp_intlv_7x7_s16.h"

#define NUM_IN_BLOCKS             (2)
#define NUM_OUT_BLOCKS            (2)
#define NUM_INTERNAL_BLOCKS       (1)

#define PARAMS_IDX                (0)
#define VCOP_LK_Q_FORMATE_PEL_RESOLN (4)

#define IN_IDX1  (BAM_MULTIBLOCK_BILINEAR_INTERP_INTLV_7X7_S16_INPUT_PORT_IMAGE     )
#define IN_IDX2  (BAM_MULTIBLOCK_BILINEAR_INTERP_INTLV_7X7_S16_INPUT_PORT_WGTS      )

#define OUT_IDX1 (BAM_MULTIBLOCK_BILINEAR_INTERP_INTLV_7X7_S16_OUTPUT_PORT_GRADX    )
#define OUT_IDX2 (BAM_MULTIBLOCK_BILINEAR_INTERP_INTLV_7X7_S16_OUTPUT_PORT_GRADY    )

typedef struct 
{
    /* Must always follow this order: pInternalBlock[], pInBlock[], pOutputBlock[], args */
    void *pInternalBlock[NUM_INTERNAL_BLOCKS];
    void *pInBlock[NUM_IN_BLOCKS];
    void *pOutBlock[NUM_OUT_BLOCKS];
    BAM_Multiblock_Bilinear_Interp_Intlv_7x7_S16_Args kernelArgs;
} BAM_Multiblock_Bilinear_Interp_Intlv_7x7_S16_Context;

#endif /* BAM_MULTIBLOCK_BILINEAR_INTERP_INTLV_7X7_S16_INT_H_ */
