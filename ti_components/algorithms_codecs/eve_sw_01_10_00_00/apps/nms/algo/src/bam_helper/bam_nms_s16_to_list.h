/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_nms_s16_to_list.h
 *
 *  @brief     This header defines interfaces for integrating the combination of
 *                NMS 16 bit signed kernel and bin to image list kernel  into BAM.
 */

#ifndef BAM_NMS_S16_TO_LIST_H_
#define BAM_NMS_S16_TO_LIST_H_

#include "bam_bin_image_to_list.h"
#include "bam_nonMaxSuppress_mxn_S16bitPack.h"

#define NMS_16S_IMG_BUF_A_B_OFFSET (0x20000U)


/** ========================================================
 *  @name   BAM_Nms_16s_to_list_Args
 *
 *  @desc   This structure specifies the properties needed for configuring NMS 16 bit signed kernel
 *
 *  @field remapKernelArgs
 *          parameters to configure Remap kernel
 *
 *  @field enableMerge
 *          enable or disable Alpha blending kernel
 *
 *  @field dstFormat
 *          Format of output
 *
 *  @field memcpyKernelArgs
 *          parameters to configure Memcpy kernel
 *
 *  @field formatConvertKernelArgs
 *          parameters to configure Format Convert kernel
 *
 *  @field alphaBlendKernelArgs
 *          parameters to configure Alpha Blend kernel
 *  ===============================================================
 */
typedef struct bam_nms16s_to_list_ctrlargs
{
  BAM_Bin_image_to_list_ctrlArgs              binToImgListKernelArgs;
  BAM_NonMaxSuppress_mxn_S16bitPack_CtlArgs   nmsMxnS16bitPackKernelArgs;
} BAM_Nms_16s_to_list_CtrlArgs;


extern BAM_KernelHelperFuncDef gBAM_TI_nms16sToListHelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_nms16sToListExecFunc;

extern BAM_KernelInfo gBAM_TI_nms16sToListKernel;

typedef enum
{
  BAM_NMS_MXN_S16_TO_LIST_INPUT_BLOCK_PORT   =   0,
  BAM_NMS_MXN_S16_TO_LIST_NUM_INPUT_BLOCKS
} eBAM_NMS_MXN_S16_TO_LIST_INPUT_PORTS;

typedef enum
{
  BAM_NMS_MXN_S16_TO_LIST_OUTPUT_XY_LIST_PORT = 0,
  BAM_NMS_MXN_S16_TO_LIST_OUTPUT_LIST_SIZE_PORT,
  BAM_NMS_MXN_S16_TO_LIST_NUM_OUTPUT_BLOCKS
} eBAM_NMS_MXN_S16_TO_LIST_OUTPUT_PORTS;


#endif /* BAM_NMS_S16_TO_LIST_H_ */

