/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_bin_image_to_list_int.h
 *
 *  @brief      This header defines internal structures for binary image to
 *              (X, Y) co-ordinate list creation into BAM.
 */
#ifndef BAM_BIN_IMAGE_TO_LIST_INT_H_
#define BAM_BIN_IMAGE_TO_LIST_INT_H_

#include <stdint.h>
#include <vcop.h>

#include "evealgframework.h"
#include "bam_bin_image_to_list.h"

#define BAM_BIN_IMAGE_TO_LIST_NUM_IN_BLOCKS       (1U)
#define BAM_BIN_IMAGE_TO_LIST_NUM_OUT_BLOCKS      (2U)
#define BAM_BIN_IMAGE_TO_LIST_NUM_INTERNAL_BLOCKS (3U)

#define IN_IMG_IDX    (BAM_BIN_IMAGE_TO_LIST_INPUT_PORT_IMG)          /* 0 */

#define OUT_XY_IDX    (BAM_BIN_IMAGE_TO_LIST_OUTPUT_PORT_XY)          /* 0 */
#define OUT_SIZE_IDX  (BAM_BIN_IMAGE_TO_LIST_OUTPUT_PORT_SIZE)        /* 1 */

#define PARAMS_IDX    (BAM_BIN_IMAGE_TO_LIST_TEMP_PARAM)             /* 0 */
#define STARTXY_IDX   (BAM_BIN_IMAGE_TO_LIST_TEMP_PORT_STARTXY)      /* 1 */
#define XSEQ_IDX      (BAM_BIN_IMAGE_TO_LIST_TEMP_XSEQ)              /* 2 */

typedef struct bam_bin_image_to_list_context
{
    /* Must always follow this order: pInternalBlock[], pInBlock[], pOutputBlock[], args */
    void *pInternalBlock[BAM_BIN_IMAGE_TO_LIST_NUM_INTERNAL_BLOCKS];
    void *pInBlock[BAM_BIN_IMAGE_TO_LIST_NUM_IN_BLOCKS];
    void *pOutBlock[BAM_BIN_IMAGE_TO_LIST_NUM_OUT_BLOCKS];
    BAM_Bin_image_to_list_Args kernelArgs;
    uint8_t outputQformat;
} BAM_Bin_image_to_list_Context;

#endif /* BAM_BIN_IMAGE_TO_LIST_INT_H_ */

