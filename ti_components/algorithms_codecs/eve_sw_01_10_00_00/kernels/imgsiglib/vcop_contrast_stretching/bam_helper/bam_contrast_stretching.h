/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_contrast_stretching.h
 *
 *  @brief      This header defines interfaces for integrating contrast stretching
                    kernels into BAM.
 */

#ifndef BAM_CONTRAST_STRETCHING_H_
#define BAM_CONTRAST_STRETCHING_H_

/**
 *******************************************************************************
 *  @brief         This is structure defines input arguments for  contrast stretching kernel.
 *  @param [in]   blkWidth   : Block Width for input Image
 *  @param [in]   blkHeight   : Block Height for input Image
 *  @param [in]   inPitch   : Pitch of input Block
 *  @param [in]   outPitch   : Pitch of output Block
 *  @param [in]   minVal   : Minimum value of the histogram for stretching
 *  @param [in]   scaleFactorQ16   : Scaling factor in Q16 format. Scale factor is
 *                                             calculated using following formula.
 *                               1 / ( maxVal - minVal) in Q16 format;
 *
 *  @remarks
 *              -# None
 *******************************************************************************
 */
typedef struct
{
  uint16_t blkWidth;
  uint16_t blkHeight;
  uint16_t inPitch;
  uint16_t outPitch;
  uint8_t minVal;
  uint16_t scaleFactorQ16;
    /* Stats Collection parameters to be added */
} BAM_ContrastStretching_Args;

/**
 *******************************************************************************
 *  @brief         This is structure defines control arguments for  contrast stretching kernel.
 *  @param [in]   minVal   : Minimum value of the histogram for stretching
 *  @param [in]   scaleFactorQ16   : Scaling factor in Q16 format. Scale factor is
 *                                             calculated using following formula.
 *                               1 / ( maxVal - minVal) in Q16 format;
 *
 *  @remarks
 *              -# None
 *******************************************************************************
 */
typedef struct
{
  uint8_t minVal;
  uint16_t scaleFactorQ16;
    /* Stats Collection parameters to be added */
} BAM_ContrastStretching_CtrlArgs;

extern BAM_KernelHelperFuncDef gBAM_TI_contrastStretchingHelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_contrastStretchingExecFunc;

extern BAM_KernelInfo gBAM_TI_contrastStretchingKernel;

typedef enum
{
  BAM_CONTRAST_STRETCHING_INPUT_BLOCK_PORT   =   0,
  BAM_CONTRAST_STRETCHING_NUM_INPUT_BLOCKS
} eBAM_CONTRAST_STRETCHING_INPUT_PORTS;

typedef enum
{
  BAM_CONTRAST_STRETCHING_OUTPUT_BLOCK_PORT   =   0,
  BAM_CONTRAST_STRETCHING_NUM_OUTPUT_BLOCKS
} eBAM_CONTRAST_STRETCHING_OUTPUT_PORTS;

#endif /* BAM_CONTRAST_STRETCHING_H_ */

