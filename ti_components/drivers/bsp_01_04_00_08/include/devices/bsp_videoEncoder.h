/******************************************************************************
 *                                                                            *
 * Copyright (c) 2012 Texas Instruments Incorporated - http://www.ti.com/     *
 *                                                                            *
 * All rights reserved. Property of Texas Instruments Incorporated.           *
 * Restricted rights to use, duplicate or disclose this code are              *
 * granted through contract.                                                  *
 *                                                                            *
 * The program may not be used without the written permission                 *
 * of Texas Instruments Incorporated or against the terms and conditions      *
 * stipulated in the agreement under which this program has been              *
 * supplied.                                                                  *
 *                                                                            *
 *****************************************************************************/

/**
 *  \ingroup BSP_DRV_DEVICE_API
 *  \defgroup BSP_DRV_DEVICE_VID_ENC_API External Video Encoder API
 *
 *  This modules define API to configure and control external video
 *  encoders like HDMI transmitters. Typically the external video encoders
 *  interface to the host via one of the DPI ports. I2C is used to send
 *  control commands to the video encoder.
 *
 *  User application controls and configures the video encoder
 *  and based on this in turn configures the DPI ports.
 *
 *  The following video encoder's are currently supported
 *  - SII9022a - HDMI HD transmitter
 *
 *  The API interface used in the FVID2 interface (See also \ref
 *  BSP_DRV_FVID2_API)
 *
 *  The following FVID2 APIs are supported by video encoder device drivers,
 *
 *
 * - <b> Creating the driver </b> - Fvid2_create()
 *   <table border="1">
 *     <tr>
 *       <th>Parameter</th>
 *       <th>Value</th>
 *     </tr>
 *     <tr>
 *       <td>drvId</td>
 *       <td>
 *       \ref FVID2_VID_ENC_SII9022A_DRV <br>
 *       </td>
 *     </tr>
 *     <tr>
 *       <td>instanceId</td>
 *       <td> Set to 0
 *       </td>
 *     </tr>
 *     <tr>
 *       <td>createArgs</td>
 *       <td>
 *       Bsp_VidEncCreateParams *
 *       </td>
 *     </tr>
 *     <tr>
 *       <td>createStatusArgs</td>
 *       <td>
 *       Bsp_VidEncCreateStatus *
 *       </td>
 *     </tr>
 *     <tr>
 *       <td>cbParams</td>
 *       <td>
 *       NOT USED, Set to NULL.
 *       </td>
 *     </tr>
 *   </table>
 *  \ref Fvid2_Handle returned by Fvid2_create() is used in subsequent FVID2
 *  APIs
 *
 * - <b> Deleting the driver </b> - Fvid2_delete()
 *  <table border="1">
 *    <tr>
 *      <th>Parameter</th>
 *      <th>Value</th>
 *    </tr>
 *    <tr>
 *      <td>deleteArgs</td>
 *      <td>NOT USED, set to NULL</td>
 *    </tr>
 *  </table>
 *
 * - <b> Starting the driver </b> - Fvid2_start()
 *  <table border="1">
 *    <tr>
 *      <th>Parameter</th>
 *      <th>Value</th>
 *    </tr>
 *    <tr>
 *      <td>cmdArgs</td>
 *      <td>NOT USED, set to NULL</td>
 *    </tr>
 *  </table>
 *
 * - <b> Stopping the driver </b> - Fvid2_stop()
 *  <table border="1">
 *    <tr>
 *      <th>Parameter</th>
 *      <th>Value</th>
 *    </tr>
 *    <tr>
 *      <td>cmdArgs</td>
 *      <td>NOT USED, set to NULL</td>
 *    </tr>
 *  </table>
 *
 * - <b> Controlling the driver </b> - Fvid2_control() <br>
 * See \ref BSP_DRV_IOCTL_DEVICE_VID_ENC for the list of IOCTLs supported by the
 * driver. <br>
 * All supported video encoders implement these IOCTLs. <br> <br>
 *  - SII9022A supports further additional specific IOCTLs (See \ref
 *  BSP_DRV_DEVICE_VID_ENC_SII9022A_API)
 *
 *  @{
 **/

/**
 *  \file bsp_videoEncoder.h
 *
 *  \brief External Video Encoder API
 */

#ifndef BSP_VIDEO_ENCODER_H_
#define BSP_VIDEO_ENCODER_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <devices/bsp_device.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \addtogroup BSP_DRV_IOCTL_DEVICE_VID_ENC
 *  @{
 */

/**
 *  \brief Get Chip ID
 *
 *  This IOCTL can be used to get video encoder chip information
 *  like chip number, revision, firmware/patch revision
 *
 *  \param cmdArgs       [IN/OUT]  const Bsp_VidEncChipIdParams *
 *  \param cmdArgsStatus [OUT]     Bsp_VidEncChipIdStatus *
 *
 *  \return FVID2_SOK on success, else failure.
 */
#define IOCTL_BSP_VID_ENC_GET_CHIP_ID       (BSP_VID_ENC_IOCTL_BASE + 0x00U)

/**
 *  \brief Configure Video mode
 *
 *  This IOCTL can be used to configure encoder for mode.
 *
 *  \param cmdArgs       [IN]  Bsp_VidEncConfigParams *
 *  \param cmdArgsStatus [OUT] NULL
 *
 *  \return FVID2_SOK on success, else failure.
 */
#define IOCTL_BSP_VID_ENC_SET_MODE          (BSP_VID_ENC_IOCTL_BASE + 0x01U)

/* @} */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief Arguments for Fvid2_create().
 */
typedef struct
{
    UInt32 deviceI2cInstId;
    /**< I2C device instance ID to use. */
    UInt32 deviceI2cAddr;
    /**< I2C device address for each device */
    UInt32 inpClk;
    /**< input clock. */
    UInt32 hotPlugGpioIntrLine;
    /**< Hot plug GPIO interrupt line no - if supported by encoder. */
    UInt32 clkEdge;
    /**< Specifies the clock edge to be used to latch data on.
         FALSE spacifies to latch on falling edge, raising edge otherwise. */
} Bsp_VidEncCreateParams;

/**
 *  \brief Status of Fvid2_create().
 */
typedef struct
{
    Int32 retVal;
    /**< FVID2_SOK on success, else failure. */
} Bsp_VidEncCreateStatus;

/**
 * \brief Arguments for \ref IOCTL_BSP_VID_ENC_GET_CHIP_ID
 */
typedef struct
{
    UInt32 deviceNum;
    /**< Device number for which chip ID is required.
     *
     *   Device number will be 0 in most cases, unless multiple devices
     *   are cascaded together. */
} Bsp_VidEncChipIdParams;

/**
 * \brief Structure for getting encoder chip identification Id.
 */
typedef struct
{
    UInt32 chipId;
    /**< Chip ID, value is device specific. */
    UInt32 chipRevision;
    /**< Chip revision, value is device specific. */
    UInt32 firmwareVersion;
    /**< Chip internal patch/firmware revision, value is device specific. */
} Bsp_VidEncChipIdStatus;

/**
 *  \brief Configuration paramters for encoder.
 */
typedef struct
{
    UInt32 standard;
    /**< Video standard. For valid values see #Fvid2_Standard. */
    Uint32 videoIfMode;
    /**< Select the video mode, like Embedded sync, different type of
      *  Discrete sync modes.
      *  For valid values see #Fvid2_VideoIfMode.*/
    UInt32 videoIfWidth;
    /**<
     *   <b>videoIfWidth</b>:<br>
     *   Video Interface width , valid options are<br>
     *   FVID2_VIFW_8BIT,<br>
     *   FVID2_VIFW_10BIT,<br>
     *   FVID2_VIFW_16BIT,<br>
     *   FVID2_VIFW_24BIT,<br>
     *   For valid values see #Fvid2_VideoIfWidth.<br>.
     */
    UInt32 videoDataFormat;
    /**<
     *  RGB or YUV data format. valid values are given below \n
     *  For valid values see #Fvid2_DataFormat.
     *  For Sil9022a Encoder following data formats are supported
     *  <b>videoDataFormat</b>:<br>
     *  Output Data format, valid options are<br>
     *  FVID2_DF_YUV422I_YUYV,<br>
     *  FVID2_DF_RGB24_888,<br>*/
} Bsp_VidEncConfigParams;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief Bsp_VidEncConfigParams structure init function.
 *
 *  \param vidEncConfig   [IN] Pointer to #Bsp_VidEncConfigParams structure.
 *
 */
static inline void BspVidEncConfigParams_init(Bsp_VidEncConfigParams *vidEncConfig);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

static inline void BspVidEncConfigParams_init(Bsp_VidEncConfigParams *vidEncConfig)
{
    if (NULL != vidEncConfig)
    {
        vidEncConfig->standard = FVID2_STD_1080P_60;
        vidEncConfig->videoIfMode = FVID2_VIFM_SCH_DS_AVID_VSYNC;
        vidEncConfig->videoIfWidth = FVID2_VIFW_24BIT;
        vidEncConfig->videoDataFormat = FVID2_DF_RGB24_888;
    }

}

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef BSP_VIDEO_ENCODER_H_ */

/* @} */

