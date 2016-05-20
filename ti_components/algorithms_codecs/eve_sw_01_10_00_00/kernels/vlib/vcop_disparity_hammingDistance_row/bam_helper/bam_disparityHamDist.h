/*==========================================================================*/
/*      Copyright (C) 2009-2014 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_disparityHamDist.h
 *
 *  @brief      This header defines interfaces for integrating disparity calculation based on hamming distance kernel
 *              into BAM.
 */

#ifndef BAM_DISPARITY_HAMDIST_H_
#define BAM_DISPARITY_HAMDIST_H_

/*
 * Public kernel argument structure interface exposed to the kernel consumer/integrator
 */
/* CHECK_MISRA("-20.2")  -> Disable rule 20.2  */
/* Usage of a reserved name for naming a language entity */
/* Deviation allowed as name is not used for any language entiry */
typedef struct _bam_disparityHamDist_args
{
  uint8_t codeWordByteLen; /* Number of bytes per codeword, only 4 bytes (32-bits) hamming distance is currently supported. */
  uint16_t leftStride; /* Stride of the left row in bytes, need to be greater or equal to codeWordByteLen * (width + winWidth-1) */
  uint16_t rightStride; /* Stride of the right row in bytes , need to be greater or equal to codeWordByteLen * (width + numDisparities - 1 + winWidth - 1) */
  uint8_t winWidth; /* width of the support window used for cost calculation  */
  uint8_t winHeight; /* height of the support window used for cost calculation */
  uint16_t width; /* Must be multiple of 16, number of pixels in the row for which disparities are produced */
  uint8_t numDisparities; /* Number of disparities to inspect. Note that actual number of disparities produced is numDisparities/disparityStep which must be multiple of 8 */
  uint8_t disparityStep; /* Disparity step, for faster computation */
  uint16_t numRows; /* Number of rows in the input frames for which disparities will be produced */
  uint16_t allCostOutputStride; /* stride in bytes of the allCostOutput output, must be multiple of 4 but not be multiple of 32, in order to avoid bank conflict because of p-scatter usage */ 
  uint8_t direction; /* 0: left to right (default), 1: right to left */
  uint8_t adjacentCosts;
} BAM_DisparityHamDist_Args;
/* RESET_MISRA("20.2")  -> Reset rule 20.2*/

typedef struct
{
    uint8_t ctlCmdId;
    uint16_t numRows;
} BAM_DisparityHamDist_CtlArgs;

extern BAM_KernelHelperFuncDef gBAM_TI_disparityHamDist_HelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_disparityHamDist_ExecFunc;

extern BAM_KernelInfo gBAM_TI_disparityHamDist_Kernel;

#define BAM_DISPARITY_HAMDIST_INPUT_LEFT_PORT         0
#define BAM_DISPARITY_HAMDIST_INPUT_RIGHT_PORT        1
#define BAM_DISPARITY_HAMDIST_INPUT_CARRYOVER_PORT    2

#define BAM_DISPARITY_HAMDIST_OUTPUT_DISP_PORT            0
#define BAM_DISPARITY_HAMDIST_OUTPUT_MINCOST_PORT         1
#define BAM_DISPARITY_HAMDIST_OUTPUT_CARRYOVER_PORT       2
#define BAM_DISPARITY_HAMDIST_OUTPUT_PREV_ADJ_COST_PORT   3
#define BAM_DISPARITY_HAMDIST_OUTPUT_NEXT_ADJ_COST_PORT   4
/* Don't support for now
#define BAM_DISPARITY_HAMDIST_OUTPUT_RL_DISP_PORT    5
#define BAM_DISPARITY_HAMDIST_OUTPUT_RL_MINCOST_PORT 6
*/

/* Macro symbols to initialize member ctlCmdId in BAM_DisparityHamDist_CtlArgs */
#define BAM_DISPARITY_HAMDIST_CMD_SET_NUMROWS 0

#endif /* BAM_DISPARITY_HAMDIST_H_ */

