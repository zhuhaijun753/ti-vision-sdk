/*==========================================================================*/
/*      Copyright (C) 2009-2013 Texas Instruments Incorporated.             */
/*                      All Rights Reserved                                 */
/*==========================================================================*/

/**
 *  @file       bam_histogram.h
 *
 *  @brief      This header defines interfaces for integrating histogram
                    kernel into BAM.
 */

#ifndef BAM_HISTOGRAM_H_
#define BAM_HISTOGRAM_H_

#define HISTOGRAM_MAX_PIXEL_VAL (255U)
#define HISTOGRAM_NUM_BINS      (256U)

#define HISTOGRAM_NUM_COPIES    (8U)

/**
 *******************************************************************************
 *  @brief         This is structure defines input arguments for  histogram kernel.
 *  @param [in]   blkWidth   : Block Width for input Image
 *  @param [in]   blkHeight   : Block Height for input Image
 *  @param [in]   inPitch   : Pitch of input Block
 *  @remarks
 *              -# None
 *******************************************************************************
 */
typedef struct
{
  uint16_t blkWidth;
  uint16_t blkHeight;
  uint16_t inPitch;
    /* Stats Collection parameters to be added */
} BAM_Histogram_Args;

/**
 *******************************************************************************
 *  @brief         These enums are to be used for control commands
 * BAM_HISTOGRAM_CTRL_CMDID_GET_HISTOGRAM8COPY_WBUF :
 *                    This ctrl command can be used to get the WBUF pointer
 *                    containing 8 channel histogram. ctrlArgs for this enum should be
 *                    a pointer,
 * BAM_HISTOGRAM_CTRL_CMDID_SET_IMAGE_HEIGHT
 *                   This ctrl command is used to set the image dimension for the histogram
 *                   This is needed to make sure that histogram doesnt update anything beyond
 *                   image region. ctrlArgs for this particular control command should  be
 *                  BAM_Histogram_ImageDim_CtrlArgs
 *  @remarks
 *              -# None
 *******************************************************************************
 */
typedef enum
{
  BAM_HISTOGRAM_CTRL_CMDID_GET_HISTOGRAM8COPY_WBUF,
  BAM_HISTOGRAM_CTRL_CMDID_SET_IMAGE_HEIGHT
} BAM_HISTOGRAM_CTRL_CMDID_TYPE;

/**
 *******************************************************************************
 *  @brief         These enums are to be used for control commands
 *  @param [in]   cmdId   : Refer BAM_HISTOGRAM_CTRL_CMDID_TYPE enum for valid enteries
 *  @param [in]   ctrlArgs : Pointer to the control args corresponding to cmdId
 *  @remarks
 *              -# None
 *******************************************************************************
 */
typedef struct
{
  uint8_t    cmdId;
  void       * ctrlArgs;
}BAM_Histogram_CtrlArgs;

typedef struct
{
  uint16_t     imageWidth;
  uint16_t     imageHeight;
}BAM_Histogram_ImageDim_CtrlArgs;


extern BAM_KernelHelperFuncDef gBAM_TI_histogramHelperFunc;
extern BAM_KernelExecFuncDef gBAM_TI_histogramExecFunc;

extern BAM_KernelInfo gBAM_TI_histogramKernel;

typedef enum
{
  BAM_HISTOGRAM_INPUT_BLOCK_PORT   =   0,
  BAM_HISTOGRAM_NUM_INPUT_BLOCKS
} eBAM_HISTOGRAM_INPUT_PORTS;

typedef enum
{
  BAM_HISTOGRAM_OUTPUT_DUMMY_PORT   =   0,
  BAM_HISTOGRAM_NUM_OUTPUT_BLOCKS
} eBAM_HISTOGRAM_OUTPUT_PORTS;

#endif /* BAM_HISTOGRAM_H_ */

