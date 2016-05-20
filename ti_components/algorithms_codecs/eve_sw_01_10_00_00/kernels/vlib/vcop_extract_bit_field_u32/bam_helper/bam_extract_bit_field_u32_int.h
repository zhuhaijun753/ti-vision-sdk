/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_extract_bit_field_u32_int.h
 *
 *  @brief      This header defines internal BAM structures for extract
 *              bit field function.
 */

#ifndef BAM_EXTRACT_BIT_FIELD_INT_H_
#define BAM_EXTRACT_BIT_FIELD_INT_H_

#include <stdint.h>
#include <vcop.h>

#include "evealgframework.h"
#include "bam_extract_bit_field_u32.h"

#define NUM_IN_BLOCKS (1U)
#define NUM_OUT_BLOCKS (1U)
#define NUM_INTERNAL_BLOCKS (1U)

#define IN_LIST_IDX (BAM_EXTRACT_BIT_FIELD_U32_INPUT_PORT_IN_LIST)
#define OUT_LIST_IDX (BAM_EXTRACT_BIT_FIELD_U32_OUTPUT_PORT_OUT_LIST)
#define PARAMS_IDX (BAM_EXTRACT_BIT_FIELD_U32_TEMP_PARAM)

typedef struct bam_extract_bit_field_u32_context
{
    /* Must always follow this order: pInternalBlock[], pInBlock[], pOutputBlock[], args */
    void *pInternalBlock[NUM_INTERNAL_BLOCKS];
    void *pInBlock[NUM_IN_BLOCKS];
    void *pOutBlock[NUM_OUT_BLOCKS];
    BAM_Extract_Bit_Field_Args kernelArgs;
} BAM_Extract_Bit_Field_Context;

#endif /* BAM_EXTRACT_BIT_FIELD_INT_H_ */
