/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_intensity_scaling_int.h
 *
 *  @brief      This header defines internal structures for intensity
 *              scaling kernel into BAM.
 */

#ifndef BAM_INTENSITY_SCALING_INT_H_
#define BAM_INTENSITY_SCALING_INT_H_


#include <stdint.h>
#include <vcop.h>

#include "evealgframework.h"
#include "bam_intensity_scaling.h"

#define NUM_IN_BLOCKS (BAM_INTENSITY_SCALING_NUM_INPUT_BLOCKS)
#define NUM_OUT_BLOCKS (BAM_INTENSITY_SCALING_NUM_OUTPUT_BLOCKS)

#define IN_IMG_IDX (BAM_INTENSITY_SCALING_INPUT_PORT_IMG)          /* 0 */

#define OUT_IMG_IDX (BAM_INTENSITY_SCALING_OUTPUT_PORT_IMG)        /* 0 */

#define NUM_SCALING_TBLS  (8U)
#define SCALING_TBL_SIZE  (256U)

typedef enum
{
  PARAMS_IDX   =    0,
  LUT_IDX,
  NUM_INTERNAL_BLOCKS
} eBAM_INTENSITY_SCALING_TEMP_PORTS ;

typedef struct bam_intensity_scaling_context
{
    /* Must always follow this order: pInternalBlock[], pInBlock[], pOutputBlock[], args */
    void *pInternalBlock[NUM_INTERNAL_BLOCKS];
    void *pInBlock[NUM_IN_BLOCKS];
    void *pOutBlock[NUM_OUT_BLOCKS];
    BAM_Intensity_scaling_Args kernelArgs;
} BAM_Intensity_scaling_Context;

#endif /* BAM_INTENSITY_SCALING_INT_H_ */

