/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_bin_image_to_list.h
 *
 *  @brief      This header defines interfaces for integrating binary image to
 *              (X, Y) co-ordinate list creation into BAM.
 */

#ifndef BAM_BIN_IMAGE_TO_LIST_H_
#define BAM_BIN_IMAGE_TO_LIST_H_

#include "bam_kernel_interface.h"
/**
  Maximum number of pixels in a block. Output requires 4 bytes per pix. Reserving 32 bytes
  for VCOP malloc header and 32 byte for buffer alignment.
*/
#define BIN_IMAGE_TO_LIST_MAX_PIXELS                 (4080U)

#define BIN_IMAGE_TO_LIST_MAX_BLK_WIDTH               (1920U)

typedef struct bam_bin_image_to_list_ctrlArgs
{
    uint16_t frameStartX;
    uint16_t frameStartY;
    uint16_t blkWidth;
    uint16_t blkHeight;
    uint16_t blkStride;
    uint8_t  outputQformat;
    uint8_t  xyOrder;/* Refer BAM_BIN_IMAGE_TO_LIST_XY_ORDER for valid values of it */
} BAM_Bin_image_to_list_ctrlArgs;

typedef struct bam_bin_image_to_list_args
{
    uint16_t frameStartX;
    uint16_t frameStartY;
    uint16_t blkWidth;
    uint16_t blkHeight;
    uint16_t blkStride;
    uint8_t  outputQformat;
    uint8_t  xyOrder;/* Refer BAM_BIN_IMAGE_TO_LIST_XY_ORDER for valid values of it */
} BAM_Bin_image_to_list_Args;

typedef enum
{
  BAM_BIN_IMAGE_TO_LIST_XY,
  BAM_BIN_IMAGE_TO_LIST_YX
} BAM_BIN_IMAGE_TO_LIST_XY_ORDER;


extern BAM_KernelHelperFuncDef gBAM_TI_binImageToListHelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_binImageToListExecFunc;

extern BAM_KernelInfo gBAM_TI_binImageToListKernel;

#define BAM_BIN_IMAGE_TO_LIST_INPUT_PORT_IMG       (0)

#define BAM_BIN_IMAGE_TO_LIST_OUTPUT_PORT_XY       (0)
#define BAM_BIN_IMAGE_TO_LIST_OUTPUT_PORT_SIZE     (1U)

#define BAM_BIN_IMAGE_TO_LIST_TEMP_PARAM           (0)
#define BAM_BIN_IMAGE_TO_LIST_TEMP_PORT_STARTXY    (1U)
#define BAM_BIN_IMAGE_TO_LIST_TEMP_XSEQ            (2U)

#endif /* BAM_BIN_IMAGE_TO_LIST_H_ */

