/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_nonMaxSuppress_mxn_S32_.h
 *
 *  @brief      This header defines int32_terfaces for integrating non max suppression into BAM.
 */

#ifndef BAM_NONMAXSUPPRESS_MxN_S32_H_
#define BAM_NONMAXSUPPRESS_MxN_S32_H_

#include <stdint.h>

typedef struct
{
    uint16_t width;
    uint16_t height;
    uint16_t inStride;
    uint16_t outStride; /* Must be multiple of 8 */
    uint16_t winW; /* NMS window width */
    uint16_t winH; /* NMS window height */
    int32_t            threshold;
    uint8_t        outputFormat;
} BAM_NonMaxSuppress_mxn_S32_Args;

typedef struct
{
    uint8_t ctlCmdId;
    int32_t threshold;
} BAM_NonMaxSuppress_mxn_S32_CtlArgs;

extern BAM_KernelHelperFuncDef gBAM_TI_nonMaxSuppress_mxn_S32_HelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_nonMaxSuppress_mxn_S32_ExecFunc;
extern BAM_KernelInfo gBAM_TI_nonMaxSuppress_mxn_S32_Kernel;

/* helper function are same for this kernel hence use the ones defined for the previous kernels */
extern BAM_KernelExecFuncDef gBAM_TI_nonMaxSuppress_mxn_S32_binPack_ExecFunc;
extern BAM_KernelInfo gBAM_TI_nonMaxSuppress_mxn_S32_binPack_Kernel;



/* enum symbols to initialize member ctlCmdId in BAM_NonMaxSuppress_mxn_S32_Args */
typedef enum
{
  BAM_NONMAXSUPPRESS_MxN_S32_CMD_GET_THRESHOLD = 0,
  BAM_NONMAXSUPPRESS_MxN_S32_CMD_SET_THRESHOLD
} BAM_NONMAXSUPPRESS_MxN_S32BITPACK_CTRL_CMD;

/* enum symbols to initialize member ctlCmdId in BAM_NonMaxSuppress_mxn_S32_Args */
typedef enum
{
  BAM_NONMAXSUPPRESS_MxN_S32_OUTPUT_FORMAT_BYTEMAP = 0,
  BAM_NONMAXSUPPRESS_MxN_S32_OUTPUT_FORMAT_BINPACK
} BAM_NONMAXSUPPRESS_MxN_S32BITPACK_OUTPUT_FORMAT;

typedef enum
{
  BAM_NONMAXSUPPRESS_MxN_S32_INPUT_PORT   =   0,
  BAM_NONMAXSUPPRESS_MxN_S32_INPUT_BLOCKS
} BAM_NONMAXSUPPRESS_MxN_S32BITPACK_INPUT_PORTS;

typedef enum
{
  BAM_NONMAXSUPPRESS_MxN_S32_OUTPUT_PORT = 0,
  BAM_NONMAXSUPPRESS_MxN_S32_OUTPUT_BLOCKS
} BAM_NONMAXSUPPRESS_MxN_S32BITPACK_OUTPUT_PORTS;



#endif /* BAM_NONMAXSUPPRESS_MxN_S32_H_ */

