/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_nonMaxSuppress_mxn_S16bitPack.h
 *
 *  @brief      This header defines interfaces for integrating non max suppression into BAM.
 */

#ifndef BAM_NONMAXSUPPRESS_MXN_S16BITPACK_H_
#define BAM_NONMAXSUPPRESS_MXN_S16BITPACK_H_

#include <stdint.h>

#define BAM_NONMAXSUPPRESS_MXN_S16BITPACK_MAX_BLOCKSIZE (8100U)


typedef struct
{
  int16_t  threshold;
  uint16_t computeWidth;
  uint16_t computeHeight;
  uint16_t winW; /* NMS window width */
  uint16_t winH; /* NMS window height */
  uint16_t inStride;
  uint16_t outStride; /* Must be multiple of 8 */
} BAM_NonMaxSuppress_mxn_S16bitPack_CtlArgs;

extern BAM_KernelHelperFuncDef gBAM_TI_nonMaxSuppress_mxn_S16bitPack_HelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_nonMaxSuppress_mxn_S16bitPack_ExecFunc;

extern BAM_KernelInfo gBAM_TI_nonMaxSuppress_mxn_S16bitPack_Kernel;

/* Macro symbols to initialize member ctlCmdId in BAM_NonMaxSuppress_mxn_S16bitPack_Args */
typedef enum
{
  BAM_NONMAXSUPPRESS_MXN_S16BITPACK_CMD_GET_THRESHOLD = 0,
  BAM_NONMAXSUPPRESS_MXN_S16BITPACK_CMD_SET_THRESHOLD
} eBAM_NONMAXSUPPRESS_MXN_S16BITPACK_CTRL_CMD;


typedef enum
{
  BAM_NONMAXSUPPRESS_MXN_S16BITPACK_INPUT_PORT   =   0,
  BAM_NONMAXSUPPRESS_MXN_S16BITPACK_NUM_INPUT_BLOCKS
} eBAM_NONMAXSUPPRESS_MXN_S16BITPACK_INPUT_PORTS;

typedef enum
{
  BAM_NONMAXSUPPRESS_MXN_S16BITPACK_OUTPUT_PORT = 0,
  BAM_NONMAXSUPPRESS_MXN_S16BITPACK_NUM_OUTPUT_BLOCKS
} eBAM_NONMAXSUPPRESS_MXN_S16BITPACK_OUTPUT_PORTS;

typedef enum
{
  BAM_NONMAXSUPPRESS_MXN_S16BITPACK_INTERNAL_PARAMS_IDX   =    0,
  BAM_NONMAXSUPPRESS_MXN_S16BITPACK_INTERNAL_SCRATCHBUF1,
  BAM_NONMAXSUPPRESS_MXN_S16BITPACK_INTERNAL_SCRATCHBUF2,
  BAM_NONMAXSUPPRESS_MXN_S16BITPACK_INTERNAL_NUM_BLOCK
} eBAM_NONMAXSUPPRESS_MXN_S16BITPACK_INTERNAL_BLOCKS;



#endif /* BAM_NONMAXSUPPRESS_MXN_S16BITPACK_H_ */

