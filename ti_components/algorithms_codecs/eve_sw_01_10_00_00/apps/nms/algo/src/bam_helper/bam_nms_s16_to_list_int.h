/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_nms_s16_to_list_int.h
 *
 *  @brief      This header defines internal structures for integrating the combination of
 *                NMS 16 bit signed kernel and bin to image list kernel  into BAM.
 */
#ifndef BAM_NMS_S16_TO_LIST_INT_H_
#define BAM_NMS_S16_TO_LIST_INT_H_

#include <stdint.h>
#include <vcop.h>

#include "evealgframework.h"
#include "bam_bin_image_to_list_int.h"
#include "bam_nonMaxSuppress_mxn_S16bitPack_int.h"
#include "bam_bin_image_to_list.h"
#include "bam_nonMaxSuppress_mxn_S16bitPack.h"

typedef enum
{
  NMS_MXN_S16_TO_LIST_INTERNAL_NMSBINPACK_PARAM_IDX        =    0,
  NMS_MXN_S16_TO_LIST_INTERNAL_BINTOLIST_PARAM_IDX,
  NMS_MXN_S16_TO_LIST_INTERNAL_UPDATE_DST_PARAM_IDX,
  NMS_MXN_S16_TO_LIST_INTERNAL_SCRATCHBUF1_IDX ,
  NMS_MXN_S16_TO_LIST_INTERNAL_BINPACK_BUF_IDX ,
  NMS_MXN_S16_TO_LIST_INTERNAL_XSEQ_IDX ,
  NMS_MXN_S16_TO_LIST_INTERNAL_STARTXY_IDX,
  NMS_MXN_S16_TO_LIST_INTERNAL_DSTPTR_OFFSET_IDX,
  NMS_MXN_S16_TO_LIST_INTERNAL_NUM_BLOCK
} eBAM_NMS_MXN_S16_TO_LIST_INTERNAL_BLOCKS;


#define NUM_IN_BLOCKS (BAM_NMS_MXN_S16_TO_LIST_NUM_INPUT_BLOCKS)
#define NUM_OUT_BLOCKS (BAM_NMS_MXN_S16_TO_LIST_NUM_OUTPUT_BLOCKS)
#define NUM_INTERNAL_BLOCKS (NMS_MXN_S16_TO_LIST_INTERNAL_NUM_BLOCK)

typedef struct bam_nms_16s_to_list_context
{
  /* Must always follow this order: pInternalBlock[], pInBlock[], pOutputBlock[], args */
  void *pInternalBlock[NUM_INTERNAL_BLOCKS];
  void *pInBlock[NUM_IN_BLOCKS];
  void *pOutBlock[NUM_OUT_BLOCKS];
  BAM_Nms_16s_to_list_CtrlArgs  kernelArgs;
  BAM_Bin_image_to_list_Context  binImgToListContext;
  BAM_NonMaxSuppress_mxn_S16bitPack_Context  nms16sbitPackContext;
  uint16_t blockCount;
  uint16_t numHorzBlocks;
  uint16_t numNms16sbitPackParamCnt;
  uint16_t nmsBinPackPrmBlockOffset1;
  uint16_t nmsBinPackPrmBlockOffset2;
  uint16_t   *pNmsBinPackDstOffset[2];
  uint8_t     pingPongFlag;
  uint16_t     nmsBinPackblockJump;
} BAM_Nms_16s_to_list_Context;


#endif /* BAM_NMS_S16_TO_LIST_INT_H_*/

