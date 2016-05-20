/* ======================================================================
 *   Copyright (C) 2013 Texas Instruments Incorporated
 *
 *   All rights reserved. Property of Texas Instruments Incorporated.
 *   Restricted rights to use, duplicate or disclose this code are
 *   granted through contract.
 *
 *   The program may not be used without the written permission
 *   of Texas Instruments Incorporated or against the terms and conditions
 *   stipulated in the agreement under which this program has been
 *   supplied.
 * ==================================================================== */

/**
 *  \file vpshal_isscal.h
 *
 *  \brief This file defines all abstractions for CAL module of ISS.
 *  This abstraction will support multiple instances of PPI, CSI. Operates 2
 *  modes primarily. memory to memory mode and capture mode.
 *
 *  NO SUPPORT for
 *  . Circular buffer
 *  . Sub frame processing
 *  . Lane merging
 *  . PPI Grouping
 */

#ifndef VPSHAL_ISSCAL_H_
#define VPSHAL_ISSCAL_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <common/bsp_types.h>
#include <vps/vps_dataTypes.h>
#include <hal/vpshal.h>

#include <vps/iss/vps_cfgcal.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Defines the total number of opens supported*/
#define VPS_HAL_ISS_CAL_OPEN_NUM            (4U)

/* CONTROL Command Supported */
/**
 *  VPS_HAL_ISS_IOCTL_START
 *  \brief START generic command is supported.
 *   Required when in VPS_HAL_ISS_CAL_MODE_CAPTURE mode
 *   Required when in VPS_HAL_ISS_CAL_MODE_M2M mode
 *   NOT Valid when in VPS_HAL_ISS_CAL_MODE_CMPLXIO_CTRL mode
 *
 *  \param handle   A non NULL handle returned by function VpsHal_isscalOpen
 *  \param cmd      VPS_HAL_ISS_IOCTL_START
 *  \param cmdArgs  None.
 *  \param arg      Not used for now.
 *
 *  \return         Returns FVID2_SOK on success else returns error value
 */
static inline int32_t VpsHal_isscalCaptureStart(VpsHal_Handle handle, Ptr arg);

/**
 *  VPS_HAL_ISS_IOCTL_STOP
 *  \brief STOP generic command is supported.
 *
 *   Required when in VPS_HAL_ISS_CAL_MODE_CAPTURE mode
 *   NOT Valid when in VPS_HAL_ISS_CAL_MODE_M2M mode
 *   NOT Valid when in VPS_HAL_ISS_CAL_MODE_CMPLXIO_CTRL mode
 *
 *  \param handle   A non NULL handle returned by function VpsHal_isscalOpen
 *  \param cmd      VPS_HAL_ISS_IOCTL_STOP
 *  \param cmdArgs  None.
 *  \param arg      Not used for now.
 *
 *  \return         Returns FVID2_SOK on success else returns error value
 */
static inline int32_t VpsHal_isscalCaptureStop(VpsHal_Handle handle, Ptr arg);

/**
 *  VPS_HAL_ISS_IOCTL_CAL_SETCFG
 *  \brief This control is to be used to update the configuration.
 *
 *   Valid when in VPS_HAL_ISS_CAL_MODE_CAPTURE mode
 *   Valid when in VPS_HAL_ISS_CAL_MODE_M2M mode
 *   NOT Valid when in VPS_HAL_ISS_CAL_MODE_CMPLXIO_CTRL mode
 *
 *  \param handle   A non NULL handle returned by function VpsHal_isscalOpen
 *  \param cmd      VPS_HAL_ISS_IOCTL_CAL_SETCFG
 *  \param cmdArgs  A pointer of type isshalCalCfg_t. All the enabled
 *                      modules should have a valid config.
 *  \param arg      Not used for now.
 *
 *  \return         Returns FVID2_SOK on success else returns error value
 */
#define VPS_HAL_ISS_IOCTL_CAL_SETCFG (VPS_HAL_ISS_IOCTL_CAL_BEGIN + 1U)

/**
 *  VPS_HAL_ISS_IOCTL_CAL_SETCFG_CMPLXIO
 *  \brief This control is to be used to update the complex IO configuration.
 *
 *   Valid when in VPS_HAL_ISS_CAL_MODE_CAPTURE mode
 *   NOT Valid when in VPS_HAL_ISS_CAL_MODE_M2M mode
 *   Valid when in VPS_HAL_ISS_CAL_MODE_CMPLXIO_CTRL mode
 *
 *  \param handle   A non NULL handle returned by function VpsHal_isscalOpen
 *  \param cmd      VPS_HAL_ISS_IOCTL_CAL_SETCFG_CMPLXIO
 *  \param cmdArgs  A pointer of type isshalCalCmplxIoCfg_t. All the enabled
 *                      modules should have a valid config.
 *  \param arg      Not used for now.
 *
 *  \return         Returns FVID2_SOK on success else returns error value
 */
#define VPS_HAL_ISS_IOCTL_CAL_SETCFG_CMPLXIO (VPS_HAL_ISS_IOCTL_CAL_SETCFG + 1U)

/**
 *  VPS_HAL_ISS_IOCTL_CAL_UPDATE_BUFFERS
 *  \brief This control is to be used to update address of the frame to be read.
 *
 *  \warning Please ensure IPIPE IF has been configured read in a frame from
 *              memory.
 *  \param handle   A non NULL handle returned by function VpsHal_isscalOpen
 *  \param cmd      VPS_HAL_ISS_IOCTL_CAL_UPDATE_BUFFERS
 *  \param cmdArgs  A pointer of type, isshalCalBufferAddr_t.
 *  \param arg      Not used
 *
 *  \return         Returns FVID2_SOK on success else returns error value
 */
#define VPS_HAL_ISS_IOCTL_CAL_UPDATE_BUFFERS \
    (VPS_HAL_ISS_IOCTL_CAL_SETCFG_CMPLXIO + 1U)

/**
 *  VPS_HAL_ISS_IOCTL_CAL_RESET
 *  \brief This control is to be used to perform soft reset of CAL
 *
 *  \warning Ensure not active operations are in progress.
 *
 *  \param handle   A non NULL handle returned by function VpsHal_isscalOpen
 *  \param cmd      VPS_HAL_ISS_IOCTL_CAL_RESET
 *  \param cmdArgs  None.
 *  \param arg      None
 *
 *  \return         Returns FVID2_SOK on success else returns error value
 */
#define VPS_HAL_ISS_IOCTL_CAL_RESET \
    (VPS_HAL_ISS_IOCTL_CAL_UPDATE_BUFFERS + 1U)

/**
 *  VPS_HAL_ISS_IOCTL_CAL_GET_INSTANCECFG
 *  \brief Get the current CAL instance config
 *
 *  \param handle   A non NULL handle returned by function VpsHal_isscalOpen
 *  \param cmd      VPS_HAL_ISS_IOCTL_CAL_GET_INSTANCECFG
 *  \param cmdArgs  A pointer to structure of type #isshalCalInstCfg_t.
 *  \param arg      None
 *
 *  \return         Returns FVID2_SOK on success else returns error value
 */
#define VPS_HAL_ISS_IOCTL_CAL_GET_INSTANCECFG \
    (VPS_HAL_ISS_IOCTL_CAL_RESET + 1U)

/**
 *  VPS_HAL_ISS_IOCTL_CAL_SET_INSTANCECFG
 *  \brief Updated the current instance config
 *
 *  \warning Ensure not active operations are in progress.
 *
 *  \param handle   A non NULL handle returned by function VpsHal_isscalOpen
 *  \param cmd      VPS_HAL_ISS_IOCTL_CAL_SET_INSTANCECFG
 *  \param cmdArgs  A pointer to structure of type #isshalCalInstCfg_t.
 *  \param arg      None
 *
 *  \return         Returns FVID2_SOK on success else returns error value
 */
#define VPS_HAL_ISS_IOCTL_CAL_SET_INSTANCECFG \
    (VPS_HAL_ISS_IOCTL_CAL_GET_INSTANCECFG + 1U)

/**
 *  VPS_HAL_ISS_IOCTL_CAL_SET_VPORT_CFG
 *  \brief Set the Vport Configuration
 *
 *  \warning Ensure not active operations are in progress.
 *
 *  \param handle   A non NULL handle returned by function VpsHal_isscalOpen
 *  \param cmd      VPS_HAL_ISS_IOCTL_CAL_SET_VPORT_CFG
 *  \param cmdArgs  A pointer to structure of type #vpsissCalVPort_t.
 *  \param arg      None
 *
 *  \return         Returns FVID2_SOK on success else returns error value
 */
#define VPS_HAL_ISS_IOCTL_CAL_SET_VPORT_CFG \
    (VPS_HAL_ISS_IOCTL_CAL_SET_INSTANCECFG + 1U)

/**
 *  VPS_HAL_ISS_IOCTL_CAL_SET_VPORT_CFG
 *  \brief Set the Vport Configuration
 *
 *  \warning Ensure not active operations are in progress.
 *
 *  \param handle   A non NULL handle returned by function VpsHal_isscalOpen
 *  \param cmd      VPS_HAL_ISS_IOCTL_CAL_SET_VPORT_CFG
 *  \param cmdArgs  A pointer to structure of type #vpsissCalBysOut_t.
 *  \param arg      None
 *
 *  \return         Returns FVID2_SOK on success else returns error value
 */
#define VPS_HAL_ISS_IOCTL_CAL_SET_BYSOUT_CFG \
    (VPS_HAL_ISS_IOCTL_CAL_SET_VPORT_CFG + 1U)

/**
 *  VPS_HAL_ISS_IOCTL_CAL_RD_FMT_UPDATE
 *  \brief Update the CAL read format, i.e. height, width, pitch and bpp.
 *          Primarily used ISP resizer driver, where luma and chroma is
 *          processed separately.
 *
 *  \warning This should be re-enterent, callable from an ISR.
 *
 *  \param handle   A non NULL handle returned by function VpsHal_isscalOpen
 *  \param cmd      VPS_HAL_ISS_IOCTL_CAL_RD_FMT_UPDATE
 *  \param cmdArgs  A pointer to structure of type #Fvid2_Format.
 *  \param arg      None
 *
 *  \return         Returns FVID2_SOK on success else returns error value
 */
#define VPS_HAL_ISS_IOCTL_CAL_RD_FMT_UPDATE \
    (VPS_HAL_ISS_IOCTL_CAL_SET_BYSOUT_CFG + 1U)


/**
 *  VpsHal_isscalCaptureStart
 *  \brief This function should be called to start capture of frames.
 *
 *  \param handle   A non NULL handle returned by function VpsHal_isscalOpen
 *  \param arg      A non NULL pointer of type isshalCalDmaVcCfg_t, with
 *                      desired / valid DMA mode of operation.
 *
 *  \return         Returns 0 on success else returns error value
 */
static inline int32_t VpsHal_isscalCaptureStart(VpsHal_Handle handle, Ptr arg);

/**
 *  VpsHal_isscalCaptureStop
 *  \brief This function should be called to stop capture of frames.
 *
 *  \param handle   A non NULL handle returned by function VpsHal_isscalOpen
 *  \param arg      A non NULL pointer of type isshalCalDmaVcCfg_t, with
 *                      DMA mode as VPS_HAL_ISS_CAL_DMA_WR_DISABLED.
 *
 *  \return         Returns 0 on success else returns error value
 */
static inline int32_t VpsHal_isscalCaptureStop(VpsHal_Handle handle, Ptr arg);

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/** \brief HAL INSTACE X in Capture mode */
#define VPS_HAL_ISS_CAL_MODE_COMPLEXIO_CTRL    (2U)

typedef enum isshalCalInstId
{
    VPS_HAL_ISS_CAL_INST_A = 0x0,
    /**< Cal Instance A */
    VPS_HAL_ISS_CAL_INST_B = 0x1,
    /**< Cal Instance B */
    VPS_HAL_ISS_CAL_INST_FORCE_INT = 0x7FFFFFFF
                                     /**< This will ensure enum is not packed,
                                             will always be contained in int */
} isshalCalInstId_t;

/**
 *  struct isshalCalMode
 *  \brief Lists the different operational modes of CAL hal.
 *
 */
typedef enum isshalCalMode
{
    VPS_HAL_ISS_CAL_MODE_MIN = 0,
    /**< Begin Marker */
    VPS_HAL_ISS_CAL_MODE_CAPTURE = 1,
    /**< Intended to be used, when we are capturing from the sensors */
    VPS_HAL_ISS_CAL_MODE_M2M = 2,
    /**< Intended to be used, when data is read from memory via CAL */
    VPS_HAL_ISS_CAL_MODE_CMPLXIO_CTRL = 3,
    /**< Intended to be used, when its required to control the complex io */
    VPS_HAL_ISS_CAL_MODE_MAX = 4,
    /**< End Marker */
    VPS_HAL_ISS_CAL_MODE_FORCE_INT = 0x7FFFFFFF
                                     /**< This will ensure enum is not packed,
                                             will always be contained in int */
}isshalCalMode_t;

/**
 *  struct isshalCalDmaWrModes
 *  \brief Different DMA write modes.
 *
 */
typedef enum isshalCalDmaWrModes
{
    VPS_HAL_ISS_CAL_DMA_WR_DISABLED = 0,
    /**< Write channel is disabled */
    VPS_HAL_ISS_CAL_DMA_WR_SHD = 1,
    /**< Shadowed, used for normal mode. */
    VPS_HAL_ISS_CAL_DMA_WR_CNT = 2,
    /**< Not supported for now */
    VPS_HAL_ISS_CAL_DMA_WR_SNT_INIT = 3,
    /**< Not supported for now */
    VPS_HAL_ISS_CAL_DMA_WR_CONST = 4,
    /**< Base address is provided for every frame */
    VPS_HAL_ISS_CAL_DMA_WR_MODES_MAX = 5,
    /**< End marker */
    VPS_HAL_ISS_CAL_DMA_WR_FORCE_INT = 0x7FFFFFFF
                                       /**< This will ensure enum is not packed,
                                               will always be contained in int */
}isshalCalDmaWrModes_t;

/**
 *  struct isshalCalBufferAddr
 *  \brief Provide the various buffer address required
 *
 */
typedef struct isshalCalBufferAddr
{
    uint32_t numBuff;
    /**< Number of valid buffers */
    uint32_t cPortId[VPS_ISS_CAL_MAX_STREAMS];
    /**< Associated C Port IDs */
    uint32_t wrDmaCtx[VPS_ISS_CAL_MAX_STREAMS];
    /**< Used only for write DMA. Not used to read DMA.
     *      Specify the context of DMA to be used */
    uint32_t buffAddr[VPS_ISS_CAL_MAX_STREAMS];
    /**< Pointer of type uint32_t, aligned on 32 bytes boundary */
    uint32_t pitch[VPS_ISS_CAL_MAX_STREAMS];
    /**< Pointer of type uint32_t, aligned on 32 bytes boundary */
}isshalCalBufferAddr_t;

/**
 *  struct isshalCalCsi2Timing
 *  \brief CSI2 timing configuration parameters
 */
typedef struct isshalCalCsi2Timing
{
    uint32_t force_rx_mode_0I01;
    /**< The value supplied in this is not used. This member will be removed
            ISS_TODO */
    uint32_t stop_state_x16_I01;
    /**< Refer the spec for details, breaking the coding guidelines to match
     *      config name used in manuals */
    uint32_t stop_state_x4_I01;
    /**< Refer the spec for details, breaking the coding guidelines to match
     *      config name used in manuals */
    uint32_t stop_state_counter_I01;
    /**< Refer the spec for details, breaking the coding guidelines to match
     *      config name used in manuals */
} isshalCalCsi2Timing_t;

/**
 *  struct isshalCalPpiCfg
 *  \brief Configure control of the PHY.
 *
 */
typedef struct isshalCalPpiCfg
{
    uint32_t              enable;
    /** TRUE enables PPI, configurations specified below is valid and would
     *      be applied. */
    uint32_t              instance;
    /**< Configure the instance of PPI to be used. Max value is
     *      VPS_ISS_CAL_MAX_PPI_INST */
    uint32_t              frame;
    /**< TRUE configure the PHY complete reception of a frame, before it can
     *      be stopped. i.e. STOP will not partial frame capture. Always ends
     *      on a frame boundary.
     *   Otherwise, partial frame could be captured, while stopping */
    uint32_t              ecc;
    /**< TRUE enables the ECC block, ECC checks is done for short / long packets
     *      for all virtual channels.
     *  otherwise, EC is disabled. */
    isshalCalCsi2Timing_t csi2Cfg;
    /**< CSI 2 Config. Applicable when enabled only  */
}isshalCalPpiCfg_t;

/**
 *  struct isshalCalCsi2VcCfg
 *  \brief CSI2 virtual channel configuration parameters
 */
typedef struct isshalCalCsi2VcCfg
{
    uint32_t instance;
    /**< There are VPS_ISS_CAL_MAX_PPI_INST possible  */
    uint32_t contextToBeUsed;
    /**< Specify the CSI context processing to be used.
     *      Valid values are 0 to 7*/
    uint32_t virtualChanNum;
    /**< Virtual channel number, to be used */
    uint32_t dt;
    /**< Configure to receive data types
     *  0x0 - Virtual channel disabled, no data is to be received. Should be
     *          0x0, when not used.
     *  0x1 - Receive any type of data.
     *  0x2 - 0xF - no valid
     *  0x10 to 0x3F - receive all data tagged as Data Type */
    uint32_t att;
    /**< TRUE configures the received data as attribute for further processing
     *      otherwise, data is tagged as Pixel Data */
    uint32_t lines;
    /**< Expected number of lines to be received. 0x0 if the number of lines
     *      to be received is unknown. */
} isshalCalCsi2VcCfg_t;

/**
 *  struct isshalCalWrDmaCfg
 *  \brief CAL DMA write configurations
 */
typedef struct isshalCalWrDmaCfg
{
    uint32_t              contextToBeUsed;
    /**< Configure the write context to be used */
    isshalCalDmaWrModes_t mode;
    /**< Configure the mode, disable is one of the valid mode */
    vpsissCalStreamType_t stream;
    /**< Configure the stream to capture */
    uint32_t              stallM2MRd;
    /**< TRUE configure Read DMA to stall, if the write DMA context is stalled.
     *      Required to ensure real-time stream (write DAM) has higher
     *      processing priority over read DMA */
    uint32_t              ySkipMode;
    /**< 0x0 - No line skips done
     *   0x2 - Writes 2 lines, skips next 2 lines
     *   0x3 - Writes 2 lines, skips next 4 lines */

    uint32_t              xPixelSkip;
    /**< Number of pixels to skip, should be a multiple of 64 bits */
    Fvid2_Format          format;
    /**< Following member of this structure is used & should be valid.
     *      format.width    Maximum line length, Should be multiple of 64 bits.
     *                          line length in bytes / 8.
     *                          0 for unlimited line length
     *      format.height   Maximum lines of video / data expected for a frame
     *                          0 is for unlimited
     *      format.pitch[0] Pitch, should be multiple of 128 bits.
     *                          pitch in byte count / 16
     */
} isshalCalWrDmaCfg_t;

/**
 *  struct isshalCalRdDmaCfg
 *  \brief CAL Read DMA configuration
 */
typedef struct isshalCalRdDmaCfg
{
    uint32_t     enable;
    /**< TRUE, Read from memory. When enabled following configurations are
     *      applied. Disabled otherwise */
    uint32_t     pixClock;
    /**< Configure the pixel clock required to read. Essentially controlling DMA
     *      read data rate. 0x0, will disable READ DMA. */
    uint32_t     bwLimit;
    /**< Minimum number of cycles between two consecutive DMA read operations.
     *      Could be used limit DMA read rate */
    uint32_t     ocpTagCnt;
    /**< Maximum number of READ request that could pend */
    uint32_t     bysOutLeWait;
    /**< If BYS Out port is used and its inserting line blanking,
     *  TRUE configures the DMA read to wait until line blanking done before the
     *      the next read.
     *  Otherwise, will not wait for end of line blanking period (generated
     *      by the BYS Out ) */
    uint32_t     ySkipMode;
    /**<    0x0 No lines are skipped, linear data
     *      0x1 Data type of YUV 420, planar data.
     *      0x2 Read 2 line and skip 2 lines
     *      0x3 Read 2 line and skip 4 lines */
    Fvid2_Format format;
    /**< Following member of this structure is used & should be valid.
     *      format.width    - expressed as byte count and not PIXELS
     *      format.height
     *      format.pitch
     *      format.dataFormat - only in case of CAL Read.
     *                          FVID2_DF_YUV420SP_VU or FVID2_DF_BAYER_RAW */
} isshalCalRdDmaCfg_t;

/**
 *  struct isshalCalDmaVcCfg
 *  \brief CAL config, used to control all the modules of CAL. When the HAL
 *      is opened as CAPTURE device,
 *      i.e. isshalCalOpenParams_t.mode == VPS_HAL_ISS_CAL_MODE_CAPTURE
 *          rdDmaCfg configuration parameters are not applied.
 *      When opened in M2M mode
 *      i.e. isshalCalOpenParams_t.mode == VPS_HAL_ISS_CAL_MODE_M2M, csi2VcCfg
 *      configuration is not applied
 *      When opened in complex IO control mode
 *      isshalCalOpenParams_t.mode == VPS_HAL_ISS_CAL_MODE_CMPLXIO_CTRL
 *      None of the parameters is applied.
 *
 */
typedef struct isshalCalDmaVcCfg
{
    uint32_t             numCPortId;
    /**< Defines the total number of DMA contexts. Should 0x0 or <
     *      VPS_ISS_CAL_MAX_STREAMS */
    uint32_t             cportId[VPS_ISS_CAL_MAX_STREAMS];
    /**< Associated CPORT IDs. All other members of this struct uses the
     *  conents of cportId[] as index. */

    uint32_t             isCsi2VcCfgValid[VPS_ISS_CAL_MAX_STREAMS];
    /**< TRUE indicates valid CSI2 virtual channel config, otherwise invalid
     *      config, not used. */
    isshalCalCsi2VcCfg_t csi2VcCfg[VPS_ISS_CAL_MAX_STREAMS];
    /**< Configure CSI2 Virtual channel parameters. There are 4 virtual channels
     *      available. */

    uint32_t             isWrDmaCfgValid[VPS_ISS_CAL_MAX_STREAMS];
    /**< TRUE indicates valid DMA write channel config, otherwise invalid config
     *      not used. */
    isshalCalWrDmaCfg_t  wrDmaCfg[VPS_ISS_CAL_MAX_STREAMS];
    /**< DMA Channel configurations */

    uint32_t             isRdDmaCfgValid[VPS_ISS_CAL_MAX_STREAMS];
    /**< TRUE indicates valid Read DMA config, otherwise invalid config
     *        not used. */
    isshalCalRdDmaCfg_t  rdDmaCfg[VPS_ISS_CAL_MAX_STREAMS];
    /**< Configure Read DMA configurations. If enabled, will always be read on
     *      cportId as 0x0.
     *  which means, pixProcCfg[0] and wrDmaCfg[0] should be valid and will be
     *  applied. */
} isshalCalDmaVcCfg_t;

/**
 *  struct isshalCalCfg
 *  \brief CAL config, Primarily used by core to convey CAL config to HAL.
 */
typedef struct isshalCalCfg
{
    uint32_t     numCPortId;
    /**< Defines the total number of streams that are required. Should 0x0 or <
            VPS_ISS_CAL_MAX_STREAMS */
    uint32_t     cportId[VPS_ISS_CAL_MAX_STREAMS];
    /**< Associated CPORT IDs. All other members of this struct uses the
        contents of cportId[] as index.
        Valid values are 1 to 7 */
    Fvid2_Format streamFmt[VPS_ISS_CAL_MAX_STREAMS];
    /**< Specify the characteristics of streams that has to be received.
            Valid member of this structure are
            .width  - specify the width if known, else 0x0.
                        WARNING - Sufficient buffer should be allocated to acco
                            modate max line length.
            .height - expected number of lines, 0x0 for unknown
                        WARNING - Sufficient buffer should be allocated to acco
                            modate max lines.
            .pitch  - pitch
            In case of CSI capture using CAL,
              .bpp        - Bits per pixel #Fvid2_BitsPerPixel
              .dataFormat - Not used, ignored. Instead use csiDataType
            In case of M2M paths using CAL,
              .bpp        - Bits Per Pixel #Fvid2_BitsPerPixel
              .dataFormat - dataformat as per #Fvid2_DataFormat */
    uint32_t              csiDataType[VPS_ISS_CAL_MAX_STREAMS];
    /**< Specify the CSI Type of streams that has to be received.
         Use #vpsissCalCsi2DataFormat. */
    uint32_t              isCsi2BasedCapture[VPS_ISS_CAL_MAX_STREAMS];
    /**< Identify if CSI2 based captured is to be used. TRUE configures for CSI2
            based, otherwise it could be LVDS, BYS In based. In which
            case virtualChanNum is not used.
            For CSI2 based capture virtualChanNum should hold a valid value.
            For CSI2 based capture stream should hold a valid type */
    uint32_t              virtualChanNum[VPS_ISS_CAL_MAX_STREAMS];
    /**< Applicable when capturing via CSI2 interface only.
            Specify the virtual channel number to be used. Valid rage 0 - 3 */
    vpsissCalStreamType_t stream[VPS_ISS_CAL_MAX_STREAMS];
    /**< Applicable when capturing via CSI2 interface only.
            Specify the streams that required to be captured */
    uint32_t              isPixProcCfgValid[VPS_ISS_CAL_MAX_STREAMS];
    /**< TRUE indicates valid pixel processing config, otherwise invalid config
            not used. */
    vpsissCalPixProc_t    pixProcCfg[VPS_ISS_CAL_MAX_STREAMS];
    /**< Configure pixel processing contexts. There are 4 pixel processing
            contexts available. */

    /* NOTE there is one instance of BYS Out, BYS In, Video Port and RD DMA.
        At any point only one configuration should be valid, otherwise, the last
        config would be active. */
    uint32_t              isBysOutCfgValid[VPS_ISS_CAL_MAX_STREAMS];
    /**< TRUE indicates valid BYS Out config, otherwise invalid config
              not used. */
    vpsissCalBysOut_t     bysOutCfg[VPS_ISS_CAL_MAX_STREAMS];
    /**< Configure BYS Out */

    uint32_t              isBysInCfgValid[VPS_ISS_CAL_MAX_STREAMS];
    /**< TRUE indicates valid BYS In config, otherwise invalid config
              not used. */
    uint32_t              bysInEnable[VPS_ISS_CAL_MAX_STREAMS];
    /**< Configure BYS In. */

    uint32_t              isVportCfgValid[VPS_ISS_CAL_MAX_STREAMS];
    /**< TRUE indicates valid Video Port In config, otherwise invalid config
              not used. */
    vpsissCalVPort_t      vportCfg[VPS_ISS_CAL_MAX_STREAMS];
    /**< Configure Video Port */

    uint32_t              writeToMem[VPS_ISS_CAL_MAX_STREAMS];
    /**< TRUE indicates that the captured stream should be written to memory */

    Ptr                   pDmaVcCfg;
    /**< HAL config computed by core based on the config */

    Ptr                   otfPrms;
    /**< Open Parameters for ISP */
} isshalCalCfg_t;

/**
 *  struct isshalCalInstCfg
 *  \brief Instance specific configuration. Applies to instance of CAL, expected
 *          to be configured once.
 *          All possible use cases of this module should be comprehended before
 *          the config is decided.
 */
typedef struct isshalCalInstCfg
{
    /* Generic config applicable for all memory 2 memory mode of CAL. These
     *  config are to have a valid value when operated in m2m mode. */
    uint32_t              mFlagH;
    /**< When no real time data is received, this should be 0xFF. A 8 bit value,
     *  please refer spec for details while capturing real time data. */
    uint32_t              mFlagL;
    /**< When no real time data is received, this should be 0xFF. A 8 bit value,
     *  please refer spec for details while capturing real time data. */
    uint32_t              rdDmaStall;
    /**< TRUE configures read dma to stall while stall flag (MFlag) is asserted
     *      FALSE/Others dosent stall DMA read on stall assertion.
     *      Recommended to be set to TRUE if CAL is also used capture data from
     *      sensors (i.e. real time data) */
    uint32_t              pwrScpClk;
    /**< TRUE configure pwrScpClk to be free running mode, even when not its not
     *      needed. FALSE gates it when not needed */
    uint32_t              llForceState;
    /**< Not used - reserved */
    uint32_t              dmaBurstSize;
    /**< maximum burst size of DMA write. Valid range is 0 to 3. 0 for 16 bytes
     *  1 for 32, 2 for 64 and 3 for 128 bytes per burst */
    uint32_t              tagCnt;
    /**< Maximum number of outstanding OCP transactions. tagCnt = tagCnt + 1.
     *      Maximum value supported is 0xF */
    uint32_t              postedWrites;
    /**< TRUE configures for posted writes only, non-posted writes otherwise */

    /* Applicable only when CAL is used to interface to sensor (via the
     *  complex IO, which is normal expected connection.
     * These config are to have a valid value when operated in capture mode.
     * Maps to following registers CAL_CSI2_COMPLEXIO_CFG_XX */

    uint32_t              numCmplxIoInst;
    /**< Number of complex IO used */
    vpsissCalCmplxIoCfg_t cmplxIoCfg[VPS_ISS_CAL_MAX_CMPLXIO_INST];
    /**< Complex IO config */
    uint32_t              numPpiInst;
    /**< Configure the instance of PPI used */
    isshalCalPpiCfg_t     ppiCfg[VPS_ISS_CAL_MAX_PPI_INST];
    /**< PHY Configurations */
    uint32_t              csi2PhyClock;
    /**< Specify the CSI2 PHY Clock in MHz. e.g. if 400 MHz is the clock
            \code csi2PhyClock = 400; */
} isshalCalInstCfg_t;

/**
 *  struct isshalCalInstParams
 *  \brief Initialization parameters, These parameters cannot be changed once
 *          initialized.
 */
typedef struct isshalCalInstParams
{
    uint32_t instId;
    /**< CAL instance ID */
    uint32_t baseAddress;
    /**< CAL registers base address */
    uint32_t phyBaseAddress;
    /**< CAL PHY base */
    uint32_t prms;
    /**< Not used */
} isshalCalInstParams_t;

/**
 *  struct isshalCalOpenParams
 *  \brief Configuration required while opening.
 *
 */
typedef struct isshalCalOpenParams
{
    uint32_t        instId;
    /**< Identifies the instance of CAL. */
    isshalCalMode_t mode;
    /**< Configure the mode of operation. */
}isshalCalOpenParams_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief Initializes CAL module and initializes the hal state.
 *
 *  \param numInst  Number of instances of CAL that requires to be initialized.
 *  \param initPrms Pointer to array of #isshalCalInstParams_t. This array
 *                      should contain numInst valid entries.
 *  \param arg      Not used for now. Should be NULL
 *
 *  \return         Returns FVID2_SOK on success else returns error value
 */
int32_t VpsHal_isscalInit(uint32_t numInst,
                          const isshalCalInstParams_t *initPrms, Ptr arg);

/**
 *  \brief De-initializes the CAL modules
 *
 *  \param arg  Not used for now. Should be NULL
 *
 *  \return     Returns FVID2_SOK on success else returns error value
 */
int32_t VpsHal_isscalDeInit(Ptr arg);

/**
 *  VpsHal_isscalOpen
 *  \brief This function should be called prior to calling any of the CAL
 *  abstraction APIs are used. This should be called post initialization of
 *  CAL module.
 *
 *  \param openPrms Open Parameters
 *  \param arg      Not used for now. Should be NULL
 *
 *  \return         A non NULL pointers, NULL on errors.
 */
VpsHal_Handle VpsHal_isscalOpen(const isshalCalOpenParams_t *openPrms,
                                Ptr                          arg);

/**
 *  VpsHal_isscalClose
 *  \brief This function should be called to close previously opened abstraction
 *
 *  \param handle   A non NULL handle returned by function VpsHal_isscalOpen
 *  \param arg      Not used for now. Should be NULL
 *
 *  \return         Returns 0 on success else returns error value
 */
int32_t VpsHal_isscalClose(VpsHal_Handle handle, Ptr arg);

/**
 *  VpsHal_isscalControl
 *  \brief CAL specific control commands.
 *
 *  \param handle   A non NULL handle returned by function VpsHal_isscalOpen
 *  \param cmd      A valid control command, refer above for valid commands
 *  \param cmdArgs  Arguments for the control command, depends on the control
 *                  command used.
 *  \param arg      Arguments for the control command, depends on the control
 *                  command used.
 *
 *  \return         Returns 0 on success else returns error value
 */
int32_t VpsHal_isscalControl(VpsHal_Handle handle,
                             UInt32        cmd,
                             Ptr           cmdArgs,
                             Ptr           arg);

/**
 *  VpsHal_isscalRdDmaStart
 *  \brief This function should be called start DMA read.
 *
 *  \param handle   A non NULL handle returned by function VpsHal_isscalOpen
 *  \param arg      Not used for now. Should be NULL
 *
 *  \return         Returns 0 on success else returns error value
 */
int32_t VpsHal_isscalRdDmaStart(
    VpsHal_Handle     handle,
    issCtrlProcMode_t procMode,
    Ptr               arg);

/* MISRA.ONEDEFRULE.FUNC
 * MISRAC_2004 Rule_8.5
 * Function definition 'VpsHal_isscalCaptureStart' in header file.
 * KW State: Ignore -> Waiver -> Case by case
 * MISRAC_WAIVER:
 *  Calls internally Control Function.
 */
/**
 *  VpsHal_isscalCaptureStart
 *  \brief This function should be called to start capture of frames.
 *
 *  \param handle   A non NULL handle returned by function VpsHal_isscalOpen
 *  \param arg      A non NULL pointer of type isshalCalDmaVcCfg_t, with
 *                      desired / valid DMA mode of operation.
 *
 *  \return         Returns 0 on success else returns error value
 */
static inline int32_t VpsHal_isscalCaptureStart(VpsHal_Handle handle, Ptr arg)
{
    return (VpsHal_isscalControl(handle, VPS_HAL_ISS_IOCTL_START, arg, NULL));
}

/* MISRA.ONEDEFRULE.FUNC
 * MISRAC_2004 Rule_8.5
 * Function definition 'VpsHal_isscalCaptureStop' in header file.
 * KW State: Ignore -> Waiver -> Case by case
 * MISRAC_WAIVER:
 *  Calls internally Control Function.
 */
/**
 *  VpsHal_isscalCaptureStop
 *  \brief This function should be called to stop capture of frames.
 *
 *  \param handle   A non NULL handle returned by function VpsHal_isscalOpen
 *  \param arg      A non NULL pointer of type isshalCalDmaVcCfg_t, with
 *                      DMA mode as VPS_HAL_ISS_CAL_DMA_WR_DISABLED.
 *
 *  \return         Returns 0 on success else returns error value
 */
static inline int32_t VpsHal_isscalCaptureStop(VpsHal_Handle handle, Ptr arg)
{
    return (VpsHal_isscalControl(handle, VPS_HAL_ISS_IOCTL_STOP, arg, NULL));
}

/**
 *  VpsHal_isscalUpdateBufAddr
 *  \brief This function should be called to updated the buffer address of the
 *          frame to be captured.
 *          This function will not update the buffer address only, pitch
 *          supplied will be IGNORED.
 *
 *  \param handle   A non NULL handle returned by function VpsHal_isscalOpen
 *  \param arg      Not used for now. Should be NULL
 *
 *  \return         Returns 0 on success else returns error value
 */
int32_t VpsHal_isscalUpdateBufAddr(VpsHal_Handle          handle,
                                   isshalCalBufferAddr_t *bufPtrs);
#ifdef __cplusplus
}
#endif

#endif  /* #ifndef VPSHAL_ISSCAL_H_ */
