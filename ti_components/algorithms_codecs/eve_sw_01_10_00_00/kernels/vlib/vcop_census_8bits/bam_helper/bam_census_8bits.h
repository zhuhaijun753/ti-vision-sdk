/*==========================================================================*/
/*      Copyright (C) 2009-2014 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_census_8bits.h
 *
 *  @brief      This header defines interfaces for integrating census transform kernel
 *              into BAM.
 */

#ifndef BAM_CENSUS_8BITS_H_
#define BAM_CENSUS_8BITS_H_

/* CHECK_MISRA("-20.2")  -> Disable rule 20.2 */
/* Usage of a reserved name for naming a language entity */
/* Deviation allowed because _bam_census_8bits_args is not reserved */
typedef struct _bam_census_8bits_args
{
  uint16_t in_w; /* Must be multiple fo 16 */
  uint16_t in_h; /* for best performance should be multiple of 8 */
  uint8_t winWidth; /* width of the support window, that defines the neighborhood in which census transform is applied around each pixel. */
  uint8_t winHeight; /* height of the support window, that defines the neighborhood in which census transform is applied around each pixel. */
  uint8_t winHorzStep; /* horizontal step between each orientation in the support window. Typically 1 or 2. */
  uint8_t winVertStep; /* vertical step between each orientation in the support window. Typically 1 or 2. */
  uint16_t in_pitch; /* Must be >= in_w + winWidth - 1 and must be even */
  uint16_t out_pitch; /* stride of the output in bytes, must be >= (in_w * codeWordLenBytes) and must be multiple of 4 but not multiple of 32*/
} BAM_Census_8bits_Args;
/*RESET_MISRA("20.2")  -> Reset rule 20.2 */

extern BAM_KernelHelperFuncDef gBAM_TI_census_8bits_HelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_census_8bits_ExecFunc;

extern BAM_KernelInfo gBAM_TI_census_8bits_Kernel;

#define BAM_CENSUS_8BITS_INPUT_PORT     0

#define BAM_CENSUS_8BITS_OUTPUT_PORT    0


#endif /* BAM_CENSUS_8BITS_H_ */

