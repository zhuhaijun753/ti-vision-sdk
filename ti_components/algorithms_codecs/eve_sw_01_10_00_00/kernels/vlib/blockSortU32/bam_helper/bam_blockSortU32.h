/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_blockSortU32.h
 *
 *  @brief      This header defines interfaces for integrating blockSort into BAM.
 */

#ifndef BAM_BLOCKSORTU32_H_
#define BAM_BLOCKSORTU32_H_

typedef struct
{
    uint16_t numElmts; /* Number of unsigned long elements to sort, must be either 64, 128, 256, 512, 1024 or 2048 */
} BAM_BlockSortU32_Args;

/* This control structure is used in case single block processing must be enabled, in which the applet needs to override the value
 * of the input and output's block pointer that has been found by BAM, with its own value passed in inputPtr and outputPtr of the control structure.
 */ 
typedef struct
{
    uint8_t ctlCmdId; /* Can only be set to BAM_BLOCKSORT_U32_CMD_SET_PTR */
    void *inputPtr;
    void *outputPtr;
} BAM_BlockSortU32_CtlArgs;

extern BAM_KernelHelperFuncDef gBAM_TI_blockSortU32HelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_blockSortU32ExecFunc;

extern BAM_KernelInfo gBAM_TI_blockSortU32Kernel;

#define BAM_BLOCKSORTU32_INPUT_PORT      0
#define BAM_BLOCKSORTU32_OUTPUT_PORT     0

#define BAM_BLOCKSORT_U32_CMD_SET_PTR 0

#endif /* BAM_BLOCK_SORT_H_ */

