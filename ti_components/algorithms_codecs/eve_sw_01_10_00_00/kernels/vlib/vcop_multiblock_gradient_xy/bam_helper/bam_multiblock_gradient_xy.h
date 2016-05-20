/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_multiblock_gradient_xy.h
 *
 *  @brief      This header defines interfaces for integrating multi block gradient
 *              XY compute kernel into BAM.
 */

#ifndef BAM_MULTIBLOCK_GRADIENT_XY_H_
#define BAM_MULTIBLOCK_GRADIENT_XY_H_

typedef struct 
{
    uint16_t currLevel;
} BAM_Multiblock_Gradient_XY_Ctrl_Args;

typedef struct 
{
   uint16_t  inputStride;
   uint16_t  blkWidth;
   uint16_t  blkHeight;
   uint16_t  blkOffset;
   uint16_t  numBlocks;
   BAM_Multiblock_Gradient_XY_Ctrl_Args ctrlPtr;
} BAM_Multiblock_Gradient_XY_Args;

extern BAM_KernelHelperFuncDef gBAM_TI_multiblockGradientXYHelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_multiblockGradientXYExecFunc;

extern BAM_KernelInfo gBAM_TI_multiblockGradientXYKernel;

#define BAM_MULTIBLOCK_GRADIENT_XY_INPUT_PORT    ( 0 )

#define BAM_MULTIBLOCK_GRADIENT_XY_OUTPUT_PORT   ( 0 )

#endif /* BAM_MULTIBLOCK_GRADIENT_XY_H_ */
