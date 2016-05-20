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
 *  \ingroup BSPUTILS_API
 *  \defgroup BSPUTILS_APP_API Application helper APIs
 *  @{
 */

/**
 *  \file bsputils_app.h
 *
 *  \brief Header file to use application level helper functions.
 */

#ifndef BSPUTILS_APP_H_
#define BSPUTILS_APP_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <common/trace.h>
#include <common/bsp_common.h>
#include <fvid2/fvid2.h>
#include <platforms/bsp_platform.h>
#include <vps/vps.h>
#if (defined(VPS_VIP_BUILD) || defined(VPS_ISS_BUILD))
#include <vps/vps_capture.h>
#endif  /* #ifdef VPS_VIP_BUILD */
#ifdef VPS_VPE_BUILD
#include <vps/vps_m2m.h>
#endif  /* #ifdef VPS_VPE_BUILD */
#ifdef VPS_DSS_BUILD
#include <vps/vps_display.h>
#endif  /* #ifdef VPS_DSS_BUILD */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief BSP application utils init function.
 *
 *  Init function which allocates semaphore and initializes
 *  global objects.
 *
 *  This function should be called before calling any of the below API's and
 *  should be called only once after doing all other module initialization
 *  like FIVD2 init, device init and platform init.
 *
 *  \return BSP_SOK on success else appropiate error code on failure.
 */
Int32 BspUtils_appInit(void);

/**
 *  \brief BSP application utils deinit function.
 *
 *  De-init function which frees already allocated objects.
 *
 *  \return BSP_SOK on success else appropriate error code on failure.
 */
Int32 BspUtils_appDeInit(void);

/**
 *  \brief BSP application utils function to call all the default init
 *  functions.
 *
 *  Note that this function calls the BspUtils_appInit() as well
 *  and hence the application should not call BspUtils_appInit() separately.
 *
 *  \param isI2cInitReq     [IN]    TRUE  -> Calls I2C/device init.
 *                                  FALSE -> I2C and device init are not called.
 *                                  This will be overridden for non-EVM based
 *                                  platforms and FALSE will be used.
 *
 *  \return BSP_SOK on success else appropriate error code on failure.
 */
Int32 BspUtils_appDefaultInit(UInt32 isI2cInitReq);

/**
 *  \brief BSP application utils function to call all the default de-init
 *  functions.
 *
 *  Note that this function calls the BspUtils_appDeInit() as well
 *  and hence the application should not call BspUtils_appDeInit() separately.
 *
 *  \param isI2cDeInitReq   [IN]    TRUE  -> Calls I2C/device init.
 *                                  FALSE -> I2C/device deinit are not called.
 *                                  This will be overridden for non-EVM based
 *                                  platforms and FALSE will be used.
 *
 *  \return BSP_SOK on success else appropriate error code on failure.
 */
Int32 BspUtils_appDefaultDeInit(UInt32 isI2cDeInitReq);

/**
 *  \brief BSP application utils function to call all the default init
 *  functions related to serial driver. This doesn't call VPS init.
 *
 *  Note that this function calls the BspUtils_appInit() as well
 *  and hence the application should not call BspUtils_appInit() separately.
 *
 *  \param isI2cInitReq     [IN]    TRUE  -> Calls I2C/device init.
 *                                  FALSE -> I2C and device init are not called.
 *                                  This will be overridden for non-EVM based
 *                                  platforms and FALSE will be used.
 *
 *  \return BSP_SOK on success else appropriate error code on failure.
 */
Int32 BspUtils_appDefaultSerialInit(UInt32 isI2cInitReq);

/**
 *  \brief BSP application utils function to call all the default de-init
 *  functions related to serial driver. This doesn't call VPS de-init.
 *
 *  Note that this function calls the BspUtils_appDeInit() as well
 *  and hence the application should not call BspUtils_appDeInit() separately.
 *
 *  \param isI2cDeInitReq   [IN]    TRUE  -> Calls I2C/device init.
 *                                  FALSE -> I2C/device deinit are not called.
 *                                  This will be overridden for non-EVM based
 *                                  platforms and FALSE will be used.
 *
 *  \return BSP_SOK on success else appropriate error code on failure.
 */
Int32 BspUtils_appDefaultSerialDeInit(UInt32 isI2cDeInitReq);

/**
 *  \brief Prints memory status liek OSAL objects, peak mem used etc...
 */
void BspUtils_appPrintMemStatus(void);

/**
 *  \brief Function to print the loadRaw command used to load buffers from file
 *  through CCS scripting console.
 *
 *  \param fileStr          [IN]    File name string.
 *  \param bufAddr          [IN]    Buffer address.
 *  \param dataFormat       [IN]    FVID2 Data format.
 *  \param width            [IN]    Width of buffer in pixels.
 *  \param height           [IN]    Height of buffer in lines.
 */
void BspUtils_appPrintLoadRawCmd(const Char *fileStr,
                                 const void *bufAddr,
                                 UInt32      dataFormat,
                                 UInt32      width,
                                 UInt32      height);

/**
 *  \brief Function to print the saveRaw command used to save buffers to file
 *  through CCS scripting console.
 *
 *  \param fileStr          [IN]    File name string.
 *  \param bufAddr          [IN]    Buffer address.
 *  \param dataFormat       [IN]    FVID2 Data format.
 *  \param width            [IN]    Width of buffer in pixels.
 *  \param height           [IN]    Height of buffer in lines.
 *  \param bufSize          [IN]    Buffer size in bytes so that multiple
 *                                  buffers could be saved.
 */
void BspUtils_appPrintSaveRawCmd(const Char *fileStr,
                                 const void *bufAddr,
                                 UInt32      dataFormat,
                                 UInt32      width,
                                 UInt32      height,
                                 UInt32      bufSize);

/* ========================================================================== */
/*                VIP Capture Driver Related Helper functions                 */
/* ========================================================================== */

#if (defined(VPS_VIP_BUILD) || defined(VPS_ISS_BUILD))

/**
 *  \brief Prints the capture instance status information by calling the
 *  driver get status IOCTL.
 *
 *  \param fvidHandle   [IN] Valid capture driver handle.
 *  \param instId       [IN] Instance ID used for print.
 *  \param numStream    [IN] Number of stream opened.
 *  \param numCh        [IN] Number of channels per stream.
 *  \param execTime     [IN] Execution time from capture start to capture
 *                           stop in msec.
 *
 */
void BspUtils_appPrintCaptStatus(Fvid2_Handle fvidHandle,
                                 UInt32       instId,
                                 UInt32       numStream,
                                 UInt32       numCh,
                                 UInt32       execTime);

#endif  /* #ifdef VPS_VIP_BUILD */

/* ========================================================================== */
/*                  M2M VPE Driver Related Helper functions                   */
/* ========================================================================== */

#ifdef VPS_VPE_BUILD
/**
 *  \brief Allocate context buffer according to the VPE driver need and
 *  provide it to the driver.
 *
 *  This function internally uses BspUtils_memAlloc() to allocate buffer memory.
 *
 *  \param fvidHandle   [IN] Valid M2M VPE driver handle.
 *  \param numCh        [IN] Number of channel to configure. This is typically
 *                      the number of channels provided at create time.
 *
 *  \return FVID2_SOK on success, else appropriate FVID2 error code on failure.
 */
Int32 BspUtils_appAllocDeiCtxBuffer(Fvid2_Handle fvidHandle, UInt32 numCh);

/**
 *  \brief Get the context buffers back from the VPE driver and free them.
 *
 *  This function internally uses BspUtils_memFree() to free buffer memory.
 *
 *  \param fvidHandle   [IN] Valid M2M VPE driver handle.
 *  \param numCh        [IN] Number of channel to configure. This is typically
 *                      the number of channels provided at create time.
 *
 *  \return FVID2_SOK on success, else appropriate FVID2 error code on failure.
 */
Int32 BspUtils_appFreeDeiCtxBuffer(Fvid2_Handle fvidHandle, UInt32 numCh);

/**
 *  \brief Prints the M2M VPE driver create status information.
 *
 *  \param createStatus [IN] Pointer to M2M VPE driver create status.
 */
void BspUtils_appPrintM2mVpeCreateStatus(
    const Vps_M2mCreateStatus *createStatus);

/**
 *  \brief Sets the VPE lazy loading parameters through the VPS control driver.
 *
 *  \param vpeInstId    [IN] VPE driver instance ID.
 *  \param scalerId     [IN] Scaler ID.
 *  \param lazyLoadingEnable [IN] Indicates whether lazy loading is to be
 *                                enabled.
 *
 *  \return FVID2_SOK on success, else appropriate FVID2 error code on failure.
 */
Int32 BspUtils_appSetVpeLazyLoad(UInt32 vpeInstId,
                                 UInt32 scalerId,
                                 Bool   lazyLoadingEnable);

#endif  /* #ifdef VPS_VPE_BUILD */

/* ========================================================================== */
/*                DSS Display Driver Related Helper functions                 */
/* ========================================================================== */

#ifdef VPS_DSS_BUILD

/**
 *  \brief Prints the display instance status information by calling the
 *  driver get status IOCTL.
 *
 *  \param fvidHandle   [IN] Valid display driver handle.
 *  \param instId       [IN] Instance ID used for print.
 *  \param execTime     [IN] Execution time from display start to display
 *                           stop in msec.
 *
 */
void BspUtils_appPrintDispStatus(Fvid2_Handle fvidHandle,
                                 UInt32       instId,
                                 UInt32       execTime);


/**
 *  \brief Prints the display controller error status information by calling the
 *  driver get error stat IOCTL.
 *
 *  \param fvidHandle   [IN] Valid display controller driver handle.
 *
 */
void BspUtils_appPrintDctrlStatus(Fvid2_Handle fvidHandle);
/**
 *  \brief Prints the display driver create status information.
 *
 *  \param createStatus [IN] Pointer to display driver create status.
 */
void BspUtils_appPrintDispCreateStatus(
    const Vps_DispCreateStatus *createStatus);

#endif  /* #ifdef VPS_DSS_BUILD */

#ifdef __cplusplus
}
#endif

#endif  /* #define BSPUTILS_APP_H_ */

/* @} */

/**
 *  \defgroup BSPEXAMPLE_API Sample Example API
 *
 *  The API defined in this module are utility APIs OUTSIDE of the device
 *  drivers.
 *
 *  Example code makes use of these APIs to implement sample application which
 *  demonstrate the driver in different ways.
 */

/**
 *  \ingroup BSPEXAMPLE_API
 *  \defgroup BSPUTILS_API Sample Example - Utility library API
 */
