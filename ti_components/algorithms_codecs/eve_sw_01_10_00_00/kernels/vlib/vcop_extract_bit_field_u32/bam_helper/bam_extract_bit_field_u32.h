/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_extract_bit_field_u32.h
 *
 *  @brief      This header defines interfaces for integrating extract
 *              bit field function into BAM.
 */

#ifndef BAM_EXTRACT_BIT_FIELD_U32_H_
#define BAM_EXTRACT_BIT_FIELD_U32_H_

typedef struct bam_extract_bit_field_u32_args
{
    uint16_t  length;
    uint32_t  bit_mask;
    uint8_t   shift;
} BAM_Extract_Bit_Field_Args;

extern BAM_KernelHelperFuncDef gBAM_TI_extract_bit_field_u32HelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_extract_bit_field_u32ExecFunc;

extern BAM_KernelInfo gBAM_TI_extract_bit_field_u32Kernel;

#define BAM_EXTRACT_BIT_FIELD_U32_INPUT_PORT_IN_LIST       (0)
#define BAM_EXTRACT_BIT_FIELD_U32_OUTPUT_PORT_OUT_LIST     (0)
#define BAM_EXTRACT_BIT_FIELD_U32_TEMP_PARAM               (0)

#endif /* BAM_EXTRACT_BIT_FIELD_U32_H_ */

