/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_multiblock_bilinear_interp_7x7_u8.h
 *
 *  @brief      This header defines interfaces for integrating multi block bilinear
 *              interpolation kernel for neighboorhood of 7x7 8-bit pixel data into BAM.
 */

#ifndef BAM_MULTIBLOCK_BILINEAR_INTERP_7X7_U8_H_
#define BAM_MULTIBLOCK_BILINEAR_INTERP_7X7_U8_H_
#include <stdint.h>

typedef struct 
{
    uint16_t currLevel;
} BAM_Multiblock_Bilinear_Interp_7x7_U8_Ctrl_Args;

typedef struct 
{
    uint16_t     input1Stride;
    uint16_t     input2Stride;
    uint16_t     outputStride;
    uint16_t     blkWidth;
    uint16_t     blkHeight;
    uint16_t     blkOffset;
    uint16_t     numKeyPoints;
    BAM_Multiblock_Bilinear_Interp_7x7_U8_Ctrl_Args ctrlPtr;
} BAM_Multiblock_Bilinear_Interp_7x7_U8_Args;

extern BAM_KernelHelperFuncDef gBAM_TI_multiblockBilinearInterp7x7U8HelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_multiblockBilinearInterp7x7U8ExecFunc;

extern BAM_KernelInfo gBAM_TI_multiblockBilinearInterp7x7U8Kernel;

#define BAM_MULTIBLOCK_BILINEAR_INTERP_7X7_U8_INPUT_PORT_INP1    ( 0 )
#define BAM_MULTIBLOCK_BILINEAR_INTERP_7X7_U8_INPUT_PORT_INP2    ( 1 )

#define BAM_MULTIBLOCK_BILINEAR_INTERP_7X7_U8_OUTPUT_PORT        ( 0 )

#endif /* BAM_MULTIBLOCK_BILINEAR_INTERP_7X7_U8_H_ */
