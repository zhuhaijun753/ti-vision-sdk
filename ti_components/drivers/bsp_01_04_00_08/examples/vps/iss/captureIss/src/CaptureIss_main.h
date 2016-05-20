/******************************************************************************
 *                                                                            *
 * Copyright (c) 2014 Texas Instruments Incorporated - http://www.ti.com/     *
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
 *  \file CaptureIss_main.h
 *
 *  \brief Defines various strcutures / defines needed by capture demo app.
 *
 */

#ifndef CAPTURE_ISS_MAIN_H_
#define CAPTURE_ISS_MAIN_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <xdc/std.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/utils/Load.h>

#include <common/bsp_types.h>
#include <common/trace.h>
#include <common/bsp_config.h>
#include <common/bsp_utils.h>
#include <osal/bsp_osal.h>

#include <fvid2/fvid2.h>
#include <platforms/bsp_platform.h>
#include <vps/vps.h>

#include <vps/vps_capture.h>
#include <vps/vps_captureIss.h>
#include <vps/iss/vps_cfgcal.h>
#include <vps/iss/vps_isscommon.h>

#include <boards/bsp_board.h>
#include <devices/bsp_videoSensor.h>
#include <utility/bsputils_prf.h>
#include <utility/bsputils_mem.h>
#include <utility/bsputils_app.h>

#include <utility/bsputils_ub960.h>
#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**< Demo application stack size */
#define CAPT_APP_TSK_STACK_MAIN         (10U * 1024U)

/**< Demo application task priority */
#define CAPT_APP_TSK_PRI_MAIN           (10U)

#define APP_NAME                        "CAPT_ISS_APP"

/**< Default run count in seconds in case of EVM else this is in frame count. */
#define CAPT_APP_RUN_COUNT              (1000U)

/**< Number of frames per stream */
#define CAPT_APP_FRAMES_PER_STREAM      (6U)
/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 * \brief Specify different config that would be used to cpature
 */
typedef struct appCaptCfg
{
    Char                   *testDescStr;
    /**< Test description. */
    UInt32                  cfgId;
    /**< Config identifier */
    UInt32                  useIt;
    /**< Capture with this config, could be bypassed, by set this to FALSE */
    Fvid2_VideoIfMode       interfaceType;
    /**< Either CSI2, LVDS, Parallel */
    Fvid2_VideoIfWidth      interfacewidth;
    /**< 1,2,3,4 lanes for CSI2, 4 lane for LVDS, 8-16 bits for parallel */
    UInt32                  numStreams;
    /**< Should be 1 for all sensor with exception of UB960/TIDA00262 in which
     *      case it can be upto 4. */
    UInt32                  virtualChannel;
    /**< In case of CSI2 - specify the virtual channel */
    vpsissCalCsi2DataFormat inCsi2DataFormat;
    /**< Specify input data format */
    Fvid2_BitsPerPixel      inBpp;
    /**< Number of bits / pixel */
    UInt32                  numFrames;
    /**< Specify number of frames to capture */
    UInt32                  width;
    /**< Expected frame width that requires to be captured. If sensor streams
     *      frames with greater width, the extra pixels would not be written.
     *      If sensors streams frames with less line length, the received
     *      lines are written. */
    UInt32                  height;
    /**< Expected frame height requires to be captured. If sensor streams
     *      frames with higher number of lines, the extra lines would not be
     *      written / captured.*/
    UInt32                  pitch;
    UInt32                  sensorDrvId;
    /**< Associated sensor driver, that would stream */
    Fvid2_Standard          standard;
    /**< Resolution */
    Fvid2_DataFormat        dataFormat;
    /**< Standard FVID2 resolution that sensor would be configured to stream */
    Fvid2_BitsPerPixel      bpp;
    /**< bits / pixel */
    Bsp_BoardMode           boardMode;
    /**< Interface width in case of parallel capture. NA for CSI2*/
}appCaptCfg_t;

/**
 *  \brief Capture application object.
 */
typedef struct appCaptObj
{
    Task_Handle               tskHandle;
    /**< Test task handle. */

    Vps_CaptIssOpenParams_t   issOpenPrms;
    /**< ISS create time parameters */
    Fvid2_VideoIfMode         videoIfMode;
    /**< CSI2, LVDS, Parallel etc... */
    Fvid2_VideoIfWidth        videoIfWidth;
    /**< Number of lanes in case CSI2 and number of bits in case of parallel */
    UInt32                    numStream;
    /**< Number of channel in multi-ch case, must be 1 for single channel. */
    UInt32                    virtualChannel;
    /**< Virtual channel of CSI2, if mode is CSI2 */
    vpsissCalCsi2DataFormat   dataFormat;
    /**< Data format of CSI2 stream */
    UInt32                    instId;
    /**< ISS Instance ID. As defined in bspdrivers_\include\vps\vps_capture.h*/

    /* FVID2 Capture Driver parameters */
    Vps_CaptCreateParams      createPrms;
    /**< Create time parameters. */
    Vps_CaptCreateStatus      createStatus;
    /**< Create status returned by driver during Fvid2_create(). */
    Fvid2_Handle              drvHandle;
    /**< FVID2 capture driver handle. */
    Fvid2_CbParams            cbPrms;
    /**< Callback params. */

    vpsissCalCfg_t            cfg;
    /**< TODO currently done for 1 stream, update for mutiple streams */
    UInt32                    numFramesToCapture;
    /**< Number of frames to receive for a given configuration */
    UInt32                    maxWidth;
    /**< Max width in pixels - used for buffer allocation for all instance. */
    UInt32                    maxHeight;
    /**< Max height in lines - used for buffer allocation for all instance. */

    /* Sensor Parameters */
    Fvid2_Handle              sensorHandle[4];
    /**< Handle to the Sensor driver */
    UInt32                    sensorDrvId;
    /**< Sensor FVID2 Id */
    Bsp_VidSensorCreateParams sensorCreatePrms;

    appCaptCfg_t              testPrms;

    UInt32                    totalFrmCount;
    /**< Count of all frames captured. */
    UInt32                    totalCpuLoad;
    /**< Accumulated CPU load - added every frame. */
    UInt32                    cpuLoadCount;
    /**< CPU load count used to get average CPU load - incremented every
     *   accumulation. */

    UInt32                    captIssAppMaxBSSMemHeapUS;
    /**< Heap usage by demo application */

    Fvid2_Frame               frames[CAPT_APP_FRAMES_PER_STREAM * \
                                     VPS_ISS_CAL_MAX_STREAMS];
    /**< FVID2 Frames that will be used for capture. */
    Fvid2_Format              allocFmt[VPS_CAPT_STREAM_ID_MAX];
    /**< Format passed to utils frame alloc function. */

    volatile UInt32           rcvedFramesCount;
    /**< Received frames for a given config */

    UInt32                    qCount[CAPT_APP_FRAMES_PER_STREAM][8];
    /**< Track Q frames */
    UInt32                    dQCount[CAPT_APP_FRAMES_PER_STREAM][8];
    /**< Track DeQueued frames */
    UInt32                    frameWithCrcErrorCnt;
    /**< Track the number of frames with CRC errors */
    UInt32                    frameWithWarning;
    /**< Track the number of frames with warning, i.e. ecc corrected */
    UInt32                    frameErrorCnt;
    /**< Other errors in frame */
    volatile UInt32           sofIntCount;
    /**< Counts the number of Start Of Frame sync interrupts received
            CSI2 i/f */
    volatile UInt32           crcErrIntCnt;
    /**< Counts the number of CRC failure on CSI2 i/f */
    volatile UInt32           unExpectedIntCnt;
    /**< in case we receive un expected interrupt */
}appCaptObj_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef CAPTURE_ISS_MAIN_H_ */
