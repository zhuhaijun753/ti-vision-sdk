/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_multiblock_bilinear_interp_intlv_7x7_s16.h
 *
 *  @brief      This header defines interfaces for integrating multi block bilinear
 *              interpolation kernel for neighboorhood of 7x7 signed 16-bit gradient
 *              pixel data which includes gradient along X and Y directions in
 *              interleaved format into BAM.
 */

#ifndef BAM_MULTIBLOCK_BILINEAR_INTERP_INTLV_7X7_S16_H_
#define BAM_MULTIBLOCK_BILINEAR_INTERP_INTLV_7X7_S16_H_

typedef struct 
{
    uint16_t currLevel;
} BAM_Multiblock_Bilinear_Interp_Intlv_7x7_S16_Ctrl_Args;

typedef struct 
{
    uint16_t     input1Stride;
    uint16_t     input2Stride;
    uint16_t     outputStride;
    uint16_t     blkWidth;
    uint16_t     blkHeight;
    uint16_t     blkOffset;
    uint16_t     numKeyPoints;
    BAM_Multiblock_Bilinear_Interp_Intlv_7x7_S16_Ctrl_Args ctrlPtr;
} BAM_Multiblock_Bilinear_Interp_Intlv_7x7_S16_Args;

extern BAM_KernelHelperFuncDef gBAM_TI_multiblockBilinearInterpIntlv7x7S16HelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_multiblockBilinearInterpIntlv7x7S16ExecFunc;

extern BAM_KernelInfo gBAM_TI_multiblockBilinearInterpIntlv7x7S16Kernel;

#define BAM_MULTIBLOCK_BILINEAR_INTERP_INTLV_7X7_S16_INPUT_PORT_IMAGE    ( 0   )
#define BAM_MULTIBLOCK_BILINEAR_INTERP_INTLV_7X7_S16_INPUT_PORT_WGTS     ( 1   )

#define BAM_MULTIBLOCK_BILINEAR_INTERP_INTLV_7X7_S16_OUTPUT_PORT_GRADX   ( 0   )
#define BAM_MULTIBLOCK_BILINEAR_INTERP_INTLV_7X7_S16_OUTPUT_PORT_GRADY   ( 1   )

#endif /* BAM_MULTIBLOCK_BILINEAR_INTERP_INTLV_7X7_S16_H_ */
